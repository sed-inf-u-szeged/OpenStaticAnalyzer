/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#ifndef __DCM_H
#define __DCM_H

#include <genealogy/inc/genealogy.h>
#include <lim/inc/lim.h>
#include <lim/inc/Factory.h>
#include <common/inc/Stat.h>
#include <common/inc/math/common.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/GraphRangeIndexer.h>
#include <graphsupport/inc/CsvExporter.h>
#include <suffixarray/inc/suffix_array.h>
#include <rul/inc/RulHandler.h>
#include <clangsupport/ASTIDMapGenerator.h>
#include <clangsupport/ASTLoader.h>

#include <boost/bimap.hpp>
#include <fstream>

#include "Config.h"
#include "ClonePositioned.h"
#include "Interval.h"
#include "CppSerializeAST.h"
#include "Aligner.h"
#include "LanguageFactory.h"
#include "Types.h"


//the original sequitur algorithm is used!

#define SEQUITUR_ORIG
#define SYNTAX_ALIGN

using namespace std;

class AbstractFilter;
class CppCloneVisitor;

namespace columbus {

enum DCFState {
  DCFS_NORMAL,
  DCFS_COVERED,
  DCFS_FILTERED
};

/**
 *\brief This map contains which clone instances' IDs and AST paths.
 */
extern std::map<NodeId, std::string> ciIdToAST;


struct sortCloneInstancesByComponentId {
  inline bool operator() (genealogy::CloneInstance* struct1, genealogy::CloneInstance* struct2) {
    return (struct1->getComponent()->getId() < struct2->getComponent()->getId());
  }
};


void dump(const genealogy::CloneInstance& ci, std::ostream& out);

/**
 * \internal
 * \brief update the memory usage statistics
 */
void updateMemoryStat(Config &config, const char* msg = nullptr);


class DuplicatedCodeMiner {
private:
  //the not implemented constructors it may be deny the copy of object
  DuplicatedCodeMiner(const DuplicatedCodeMiner&);
  const DuplicatedCodeMiner& operator=(const DuplicatedCodeMiner&);
public:
  /**
   * \brief constructor
   * \param blockedPaths  this path is not serialized.
   * \param genealogy [in] the genealogy file name
   * \param metOut [in] prepare to metrics/graph out
   * \param rulHandler [in] handler for rul configuration file
   * \param files [in] list of
   * \param limFile the name of the lim file
   * 
   */
  DuplicatedCodeMiner(Config& config, columbus::rul::RulHandler* rulHandler);

  /**
   * \brief destructor
   */
  virtual ~DuplicatedCodeMiner();

  int getCloneClassNum()   const;
  int getCloneInstanceNum()const;
  void saveGenealogy();

  void setStatementFilter(bool val);
  
  int getNodeKindSequenceSize(); 
  
protected:
  bool statementFilter;

  // genealogy file name
  Config&                                         config;
  // string table for genealogy factory
  columbus::RefDistributorStrTable*               strTable;
  // genealogy factory
  columbus::genealogy::Factory*                   genealogyFact;
  // the lim factory
  columbus::lim::asg::Factory*                    limFact;
  std::set<NodeId>                                visitedLimNodes;  // TODO: remove?
  std::map<NodeId, std::set<  columbus::Key > >   fileNamesByComponent;  // TODO: remove?

  struct ComponentMetrics
  {
    double CR;
    double CEE;
  };

  std::map<NodeId /* LIM component id */,
           ComponentMetrics>                      componentMetrics;

  /**
   * \brief Matching AST path to < component id, translation unit id >
   */
  std::map<std::string, std::pair<NodeId, NodeId>> tuPathToCompAndTuId;

  
  std::map<std::string, unsigned long long >  serializedAsgNodeNumberByComponenet;
  LimOrigin                                   limOrigin;

  std::map<NodeId, std::set<NodeId> >          limNodeCloneInstanceMap;        // NodeId of the clone instance in the genealogy ASG -> set of NodeIds of source code elements in the LIM ASG
  std::map<NodeId, std::set<NodeId> >          limComponentCloneInstanceMap;   // NodeId of the clone instance in the genealogy ASG -> set of NodeIds of component nodes in the LIM ASG

  // Temporal storages to set string attributes after the filtering stage not to fill the stringtable as they are not removed during the node deletion.
  std::map<NodeId, string>  cloneClassFingerprintMap; // NodeId of the clone class in the genealogy ASG -> Fingerprint of the class.
  std::map<NodeId, string>  cloneInstanceRootNodesMap; // NodeId of the clone instance in the genealogy ASG -> Root nodes of the clone instance.

  //this map is conatin the version of lim node
  columbus::lim::asg::MangledNameKey2LimId nameMap;

  // the currently builded system
  columbus::genealogy::System* currentSystem;
  // the previous system in the genealogy file
  const columbus::genealogy::System* lastSystem;

  unsigned int currentSystemMaxNDC;
  // rul handler
  columbus::rul::RulHandler* rulHandler;
  // output graph
  columbus::graph::Graph graph;

  // factory manager for asg-s
  LanguageFactory currentFactory;

  // graph indexer
  columbus::graphsupport::GraphRangeIndexer* indexer;

  // information collected during serialization of the ASTs
  SerializationData serializationData;

  //lim node -> <code lloc, clone lloc>
  std::map<NodeId, std::pair<int, int>> lineMetrics; 
  
  //compilation unit -> Clone logical lines of code
  std::map<std::string, int> astCloneLogicalLines;

  // map for the node and its connected nodes with NDCs
  //NodeEmbeddednessVisitorBase::ConectedEdgesMap conectedEdgesMap;

  struct SerializedAsg {
    std::vector<int> nodeKindSequence;
    std::vector<ASTNodeInfo*> nodeInfoSequence;
    std::map<NodeId, unsigned int> positionCache;
    int decDepthSign;
  };

  struct PotentialCloneInstance {
    unsigned startPosition;
    std::shared_ptr<Interval> I;
    PotentialCloneInstance(unsigned startPosition, std::shared_ptr<Interval> I) : startPosition(startPosition), I(I) { }

    bool operator<(const PotentialCloneInstance& pci) const {
      return startPosition + I->a < pci.startPosition + pci.I->a;
    }

    PotentialCloneInstance(const PotentialCloneInstance& pci) : startPosition(pci.startPosition), I(pci.I) { }

    void dump()
    {
        printf("PCI:%u   I.a:%u I.b:%u\n", startPosition, I->a, I->b);
        if (I->intervals != nullptr)
        {
          printf("Intervals:");
          for (auto& i: *I->intervals)
            printf("%u, ", i);
          printf("\n");
        }

    }
    private:
      const PotentialCloneInstance& operator=(const PotentialCloneInstance& pci); // Intentionally not implemented!

  };

  // maps a clone class to the set of its potential clone instances
  typedef std::map<columbus::NodeId, std::set<PotentialCloneInstance> > CloneClassPotentialCloneInstanceMap;

  // the map of genealogy CloneInstance location for asg
  std::map<std::string, SerializedAsg> serializedAsgMap;
  


  // instead of MD% sum using the sequence positions only
  std::map<std::string, genealogy::CloneClass*> cloneClassMap;

  // clone visitor
  CppCloneVisitor* theCloneVisitor;
  ostream* filterOut;

  // number of trivial pairs at evolution mapping
  unsigned int trivial_pairs;
  bool dumpGraphml;

  // clone instance position at serialized asg
  std::map<NodeId, unsigned int> positions;

  // clone classes length
  std::map<NodeId, unsigned int> lengths;

  std::map<std::string, std::set<columbus::NodeId> > filteredNodes;
  std::set<LineIdentifier>  coveredLines;
  std::map<std::string, std::set<columbus::NodeId> >  coveredNodes;

  common::Cache<NodeId, int> nodeDepthCache;

protected:

  void dumpNodeIdSequence(const std::string filename);
  void dumpNodeKindSequence(const std::string filename);
  void dumpCloneInstanceInformation();

  /**
   * \internal
   * \brief detect clones in serialized asg
   * \param coveredNodes [out] calculate the covered nodes in asg-s
   * \param needToSkip [inout] skipped paths
   * \param overlap [in] allow overlapped clone instances
   */
  void detectClones(std::map<std::string, std::set<NodeId> >& coveredNodes, std::set<std::string>& needToSkip);

  bool isFilteredCC(const genealogy::CloneClass& cc);

  /**
   * \internal
   * \brief return true, if metric is turned on in rul file
   * \return true if metric calculation is needed, otherwise return false
   */
  bool getIsNeeded(const std::string& id) const;

  /**
   * \internal
   * \brief add metric and summarize along relType edges if it is needed
   * \param name [in] the metric name
   * \param relType [in] the edge type
   * \param node [in] node in output graph
   * \param value [in] the metric value
   * \param sumUp [in] summarize metric to parents
   */
  void addValue(const string& name, const std::list<columbus::graph::Edge::EdgeType>& relType, const columbus::graph::Node& node, int value, bool sumUp);

  /**
   * \internal
   * \brief get node parents
   * \param node [in] the start node
   * \param edgeType [in] get parents along edgetype edges
   * \param nodes [out] parents of the node
   */
  void getParent(const columbus::graph::Node& node, const std::list<columbus::graph::Edge::EdgeType>& relType, std::list<columbus::graph::Node>& nodes);

  /**
   * \internal
   * \brief get node parents and parenets' parenets too
   * \param node [in] the start node
   * \param edgeType [in] get parents along edgetype edges
   * \param nodes [out] parents of the node
   */
  void getParentTransitve(const columbus::graph::Node& node, const std::list<columbus::graph::Edge::EdgeType>& relType, std::set<columbus::graph::Node>& nodes);

  /**
   * \internal
   * \brief find node in graph by source code position
   * \param graph [inout] the output graph
   * \param path [in] node path
   * \param line [in] line
   * \param col [in] column
   * \param endLine [in] end line
   * \param endCol [in] end column
   * \return node at specified position
   */
  columbus::graph::Node findNodeByRange(columbus::graph::Graph& graph, const string& path, int line, int col, int endLine, int endCol);


  /**
   * \internal
   * \brief build clone tree into output graph
   */
  void buildBaseCloneTree();

  void incCSOnPrevCloneClass(columbus::genealogy::CloneInstance &ci);

  void collectContainerFiles(const lim::asg::logical::Package &package, std::set<columbus::Key> &fileNames);

  /**
   * \internal
   * \brief save component and its parent components
   * \param componentsOfTheClass [out] the output set of (parent) components
   * \param currentComp [in] the current component to be added
   */
  void addParentComponents(std::set<NodeId> &componentsOfTheClass, NodeId currentComp);

  /**
   * \internal
   * \brief compute finger print from serialized asg
   * \param pos [in] clone start position in asg
   * \param length [in] clone length
   * \return the clone class finger print
   */
  std::string computeCloneClassCode(unsigned int pos, unsigned int length);

  /**
   * \internal
   * \brief align clone class begin and end to positioned nodes
   * \param alignKind [in] the alignment kind
   * \param suffixCl [in] clone class from suffix array
   */
  void alignCloneClass(Aligner::AlignKind alignKind, const suffix_array::SuffixArray<int>::CloneClass& suffixCl, CloneClassPotentialCloneInstanceMap& potentialCloneInstances);

  /**
   * \internal
   * \brief create clone class by position in serialized asg and length
   * \param position [in] the start position in serialized asg
   * \param length [in] clone class length
   * \param isNewClass [out] return true, if class instance is created, otherwise return false
   * \return clone class for specified position and length
   */
  genealogy::CloneClass* createCloneClass(unsigned int position, unsigned int length, bool& isNewClass);

  /**
   * \internal
   * \brief create clone instance by position and length
   * \param position [in] the start position
   * \param length [in] the instance length
   * \param parent [in] instance parent
   * \return created clone instance
   */
  genealogy::CloneInstance* createCloneInstance(unsigned int position, unsigned int length, unsigned int intervalStart, std::vector<unsigned int>* intervals, genealogy::CloneClass& parent);

  /**
   * \internal
   * \brief find clone instance in clone class
   * \param position [in] clone instance position
   * \param cc [in] clone class
   * \return true, if clone instance founded, otherwise return false
   */
  bool containsInstanceAtPositon(unsigned int position, const genealogy::CloneClass& cc);

  /**
   * \internal
   * \breif return first node position at specified interval
   * \param from [in] interval begin
   * \param to [in] interval end
   * \return the node position
   */
  const ASTNodeInfo* getFirstNode(unsigned int from, unsigned int to) const;

  /**
   * \internal
   * \breif return end node position at specified interval
   * \param from [in] interval begin
   * \param to [in] interval end
   * \return the node position
   */
  const ASTNodeInfo* getEndNode(unsigned int from, unsigned int to) const;

  /**
   * \internal
   * \brief compute nodes covered by clones
   */
  void computeCoveredNodes();

  /**
   * \internal
   * \brief depth of the given node in the logical tree if it is a sourcecode element or in the component tree if it is a component node
   * \return the depth of the given LIM node
   */
  int getLimNodeDepth(NodeId);


  /**
   * \internal
   * \brief evolution mapping of clones
   * \brief systemRef [inout] current system
   * \brief genealogyBase [in] the project
   */
  void evolutionMapping(columbus::genealogy::System& systemRef, columbus::genealogy::Project& genealogyBase);

  /**
   * \internal
   * \brief set the unique name of clone classes/instances and clone smells
   */
  void setClonesUniqueNameAndCloneSmells();

  /**
   * \internal
   * \brief generate the unique name for genealogy node
   */
  std::string getGraphNameOfGenelogyNode(const columbus::genealogy::Base& genealogyBase);

  /**
   * \internal
   * \brief initialize genealogy graph
   * \param errorAtLoad [out] true if genealogy file load failed
   * \return the created/loaded project
   */
  columbus::genealogy::Project& initGenealogy(bool& errorAtLoad);

  /**
   * \internal
   * \brief initialize/load lim graph
   * \return true if succeeded
   */
  bool initLim();

  /**
   * \internal
   * \brief createSystem node in the genelogy factory
   * \return the created node
   */
  columbus::genealogy::System* createSystem();

  /**
   * \internal
   * \brief compute coverage for asg-s and build output graph
   * \param cv2 [in] coverage visitor
   * \param  coveredNodes [in] the covered nodes
   */
  //void computeCoverage(COVERAGE_VISITOR* cv2, std::map<std::string, std::set<NodeId> >& coveredNodes);

  /**
   * \internal
   * \brief create backup form components to 'backup' directory
   * \param backup [out] the output directory
   */
  void createBackup(const std::string& backup);

  /**
   * \internal
   * \brief use pattern filter and reserialize the asg.
   */
  void patternFilter();

  /**
   * \internal
   * \brief serialize all the given asg-s.
   * \param createComponent create new component for the genealogy
   */

  int serializeAsg(bool createComponent);

  std::vector<NodeId> getInstanceIds(const genealogy::CloneInstance&);

  /**
   * \internal
   * \brief It calculates clone complexity for clones.
   */
  void calculateCCO();

  /**
   * \internal
   * \brief It calculates CCL metrics.
   */
  void calculateCCL();

  /**
   * \internal
   * \brief It calculates CCL metrics.
   */
  void calculateCC();

  /**
   * \internal
   * \brief It calculates CI metrics.
   */
  void calculateCI();

  /**
   * \internal
   * \brief It calculates CLC and LLDC metrics.
   */
  void calculateCLC_LDC();

  /**
   * \internal
   * \brief It calculates CLLC and LLDC metrics.
   */
  void calculateCLLC_LLDC();

  /**
   * \internal
   * @brief It calculates CLLOC metrics
   */
  void calculateCLLOC();

  /**
   * \internal
   * @brief It calculates NCR metrics
   */
  void calculateNCR();

  /**
   * \internal
   * @brief It calculates CE metrics
   */
  void calculateCE();

  /**
   * \internal
   * @brief It calculates CE metrics
   */
  void calculateCEE();

  /**
   * \internal
   * @brief It calculates CEG metrics
   */
  void calculateCEG();

  /**
   * \internal
   * @brief It calculates CR metrics
   */
  void calculateCR();

  /**
   * \internal
   * @brief It calculates CA metrics
   */
  void calculateCA();

  /**
   * \internal
   * @brief It calculates CV metrics
   */
  void calculateCV();


  /**
   * \internal
   * \brief It calculates the clone metrics
   */
  void calculateMetrics();

  /**
   * \internal
   * \brief It calculates the evolution dependent clone metrics
   */
  void calculateEvolutionDependentMetrics();

  /**
   * \internal
   * \brief It adds the clone metrics with default values for nodes not related
   *        to any clone instances.
   */
  void addDefaultMetricsForTheNodes();

  /**
   * \internal
   * \brief It gives back CLLC metric
   * \param limNodeId [in] The LIM node identifier for which CLLC is calculated
   * \param codeLLOC [out] The LLOC metric of the code fragment which represented by LIM node.
   * \param cloneLLOC [out] The sum of those clones' LLOC which are contained by the give LIM node.
   * \return CLLC value
   */
  float getCLLC(NodeId limNodeId, int& codeLLOC, int& cloneLLOC);

  /**
   * \internal
   * \brief
   * \param astWithNodeIdMaps [in]
   * \param cloneRootsByElements [in]
   */
  void fillLineMetrics(const columbus::ASTWithNodeIDMaps& astWithNodeIdMaps, const std::map<NodeId, std::vector<NodeId>>& cloneRootsByElements);

  /**
   * \internal
   * \brief Calculates CLLC metric and stores it into lineMetrics map.
   */
  void computeCLLC();
  
  /**
   * \internal
   * \brief This method fills the parents set recursively of the given lim node.
   */
  void getLimNodeParents(NodeId limId, std::set<NodeId>& parents);

  /**
   * \internal
   * \brief This method gives back the parent of the given lim node.
   */
  NodeId getLimNodeParent(NodeId limId) const;
  
  /**
   * \internal
   * \brief Sorts the nodes into declarations and statements.
   * \param idMaps [in] The maps which contain the mapping between the ids and the nodes
   * \param nodes [in] A vector which contains the sortable node ids
   * \param declarations [out] A vector which will contain clang::Decl* nodes
   * \param statements [out] A vector which will contain clang::Stmt* nodes
   */
  void sortNodesByType(const NodeIDMaps &idMaps
    , std::vector<NodeId> &nodes
    , std::vector<clang::Decl*> &declarations
    , std::vector<clang::Stmt*> &statements
    );



  void computeSimilarityAttributes(columbus::genealogy::CloneInstance& ci);

  enum F_attributes { F1 = 1, F2, F3, F4, F5, F6 };
  const std::string* getFString(F_attributes F, const columbus::genealogy::CloneInstance& ci) {
    switch (F) {
    case F1: return &ci.getPath();
    case F2: return nullptr;
    case F3: return &ci.getF3_HeadNodeUniqueName();
    case F4: return &ci.getF4_AncestorUniqueName();
    case F5: return &ci.getF4_AncestorUniqueName();
    case F6: return &ci.getF6_LexicalStructure();
    default: return nullptr;
    }
  }
  double getStringSimilarity(std::string& s1, std::string& s2, double& dist, double* alpha, unsigned int limit);
  double distanceF(F_attributes F, const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to, double& dist, const double& bound, double* alpha);


  /**
   * \internal
   * \brief compute F3 distance between clone intances
   */
  double distanceF3(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to, double& dist, double& bound, double* alpha);

  double distanceF1(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to, double& dist, double& bound, double* alpha);

  double distanceF4(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to, double& dist, double& bound, double* alpha);

  double distanceF2(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to, double& dist, double& bound, double* alpha);

  double distanceF5(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to, double& dist, double& bound, double* alpha);

  double distanceF6(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to, double& dist, double& bound, double* alpha);
  /**
   * \internal
   * \brief compute similarity between clone instances
   */
  double similarity(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to);

  /**
   * \internal
   * \return the id of the component or 0
   */
  NodeId getLimComponenetIdByName(const std::string& name, const columbus::lim::asg::Factory& factory);

  const std::string& getComponentName(columbus::NodeId limId, const columbus::lim::asg::Factory& factory) const;

  /**
   * \internal
   * \brief get clone instances of 'system'
   * \return vector of clone instances
   */
  std::vector<genealogy::CloneInstance*> getInstancesOfaSystem(const genealogy::System& system) const;
  

public:
  /**
   * \brief start duplicate code mining
   */
  int dcminer();

  /**
   * \internal
   * \brief set dump genealogy to graphml
   */
  void setDumpgraphml(bool dump);

  /**
   * \brief gives back node kind at 'position' from serialized asg
   * \param position [in] node position
   * \return node kind
   */
  int getNodeKindAt(unsigned int position) const;

  /**
   * \brief get node at 'position' from serialized asg
   * \param position [in] node position
   * \return node
   */
  const ASTNodeInfo* getNode(unsigned int sequencePosition) const;

  /**
   * \brief return true, if parameter is separator
   * \param value [in] value parameter
   * \return true, if value is separator, otherwise is false
   */
  bool isSeparator(int value) const;

  /**
   * \brief return true, if parameter is depth sign
   * \param value [in] value parameter
   * \return true, if value is depth sign, otherwise is false
   */
  bool isDecDepthSign(int value) const;

  /**
   * \brief return true, if the id at 'sequencePosition' is an asg node (Not a special node kind ex: the end of node sign)
   * \param value [in] value parameter
   * \return true, if id at sequencePosition is node, otherwise is false
   */
  bool isASGNode(unsigned int sequencePosition) const;

  /**
   * \brief dump last system to output stream
   * \param o [in] output stream
   */
  void dumpLastSystem(std::ostream& o);

  /**
   * \brief export binary graph
   * \param filename [in] file name
   */
  void exportGraph(const std::string& filename);

  /**
   * \brief get clone instance start position in serialized asg
   * \param id [in] node id
   * \return ci position
   */
  unsigned int getPosition(NodeId id) const;

  /**
   * \brief get clone class length in serialized asg
   * \param id [in] node id
   * \return ci length
   */
  unsigned int getLength(NodeId id) const;

  static columbus::Key getUniformPathKey(columbus::Key key, StrTable& strtable);


  /**
   * \brief calculate clone class length
   * \param cc [in] clone class
   * \return the clone class length
   */
  static unsigned int getLength(const genealogy::CloneClass& cc);

  /**
   * \brief get the number of the clone instances of 'cc' i.e. the parameter clone class
   * \param cc [in] clone class
   * \return the number of instances of 'cc'
   */
  static unsigned int getRealNumberCi(const genealogy::CloneClass& cc);

  /**
   * \brief get the calculate number of the clone classes of 'sys' i.e. the parameter system
   * \param sys [in] system
   * \return the number of clone classes of 'sys'
   */
  static unsigned int getRealNumberCC(const genealogy::System& sys);

  /**
   * \brief set filterout
   * \param out [in] the filterout to be set
   */
  void setFilterOut(std::ostream& out);

  /**
   * \brief compute covered lines of clones
   */
  void computeCoveredLines();

  /**
   * \brief calculate CCO metric
   */
  // TODO rename
  void calculateCOOForLangASG(columbus::NodeId componenetId, const std::string&);

  friend class ProcessCC;
  friend class ProcessPatternFilter;

};


}

#endif

