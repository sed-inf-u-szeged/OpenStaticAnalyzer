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

#include "common.h"
#include <genealogy/inc/genealogy.h>
#include <lim/inc/lim.h>
#include <lim/inc/Factory.h>
#include <common/inc/Stat.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/GraphRangeIndexer.h>
#include <graphsupport/inc/CsvExporter.h>
#include <suffixarray/inc/suffix_array.h>
#include <rul/inc/RulHandler.h>

#ifdef SCHEMA_JAVA
#include "Visitors/JNodeEmbeddednessVisitor.h"
#endif

#ifdef SCHEMA_PYTHON
#include "Visitors/PNodeEmbeddednessVisitor.h"
#endif

#ifdef SCHEMA_CSHARP
#include "Visitors/CSNodeEmbeddednessVisitor.h"
#endif

#ifdef SCHEMA_JAVASCRIPT
#include "Visitors/JSNodeEmbeddedVisitor.h"
#endif

#include "common/inc/math/common.h"
#include <boost/bimap.hpp>
#include <fstream>
#include "LanguageFactory.h"

//the original sequitur algorithm is used!

#define SEQUITUR_ORIG
#define SYNTAX_ALIGN
using namespace std;

class AbstractFilter;


namespace columbus { namespace dcf {

  enum DCFState {
    DCFS_NORMAL,
    DCFS_COVERED,
    DCFS_FILTERED
  };

  struct CorrectedPos {
    CorrectedPos(
      const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned* node,
      columbus::Key uniformPath):node(node),uniformPath(uniformPath) {

    }
    const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned* node;
    columbus::Key uniformPath;
  };

  struct sortCloneInstancesByComponentId {
    inline bool operator() (genealogy::CloneInstance* struct1, genealogy::CloneInstance* struct2) {
      return (struct1->getComponent()->getId() < struct2->getComponent()->getId());
    }
  };

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
  
  int getCloneClassNum()   const ;
  int getCloneInstanceNum()const;
  void saveGenealogy();
  void setStatementFilter(bool val);

protected:
  bool statementFilter;

  // genealogy file name
  Config&                                     config;
  // string table for genealogy factory
  columbus::RefDistributorStrTable*           strTable;
  // genealogy factory
  columbus::genealogy::Factory*               genealogyFact;
  // the lim factory
  columbus::lim::asg::Factory*                limFact;
  NodeId                                      rootComponenetID;
  std::set<NodeId>                            visitedLimNodes;
  std::set<LineIdentifier>                    visitedLines;
  std::set<LineIdentifier>                    logicalLines;
  std::map<NodeId, std::set<  columbus::Key > >          fileNamesByComponent;
  
  
  std::map<std::string, unsigned long long >  serializedAsgNodeNumberByComponenet;
  LimOrigin                                   limOrigin;
  
  std::map<NodeId,std::set<NodeId> >          limNodeClineInstanceMap;
  std::map<NodeId,std::set<NodeId> >          limComponentClineInstanceMap;

  //this map is conatin the version of lim node
  columbus::lim::asg::MangledNameKey2LimId nameMap;

  // the currently builded system
  columbus::genealogy::System* currentSystem;
  // the previous system in the genealogy file
  const columbus::genealogy::System* lastSystem;

  unsigned int currentSystemMaxNDC;
  // rul handler
  columbus::rul::RulHandler* rulHandler;
  // the output graph
  columbus::graph::Graph graph;

  // factory manager for asg-s
  LanguageFactory currentFactory;

  // graph indexer
  columbus::graphsupport::GraphRangeIndexer* indexer;

  //v1 vector will contain the sequence of node kinds
  std::vector<int> nodeKindSequence;

  //v2 vector will contain the sequence of nodeIds together with the depth information
  std::vector<ClonePositioned*> nodeIdSequence;

  // there is the map for the node  and the connected nodes with is NDC-s
  NodeEmbeddednessVisitorBase::ConectedEdgesMap conectedEdgesMap;

  struct SerializedAsg {
    std::vector<int> nodeKindSequence;
    std::vector<ClonePositioned*> nodeIdSequence;
    std::map<NodeId, unsigned int> positionCache;
    int decDepthSign;
  };

  struct PotentialCloneInstance {
    unsigned startPosition;
    Interval I;
    PotentialCloneInstance(unsigned startPosition, Interval I): startPosition(startPosition), I(I) { }
    
    bool operator<(const PotentialCloneInstance& pci) const {
      return startPosition + I.a < pci.startPosition + pci.I.a;
    }
    
    PotentialCloneInstance(const PotentialCloneInstance& pci): startPosition(pci.startPosition), I(pci.I) { }

    private:
      const PotentialCloneInstance& operator=(const PotentialCloneInstance& pci); // Intentionally not implemented!

  };
  
  typedef std::map<columbus::NodeId, std::set<PotentialCloneInstance> > CloneClassPotentialCloneInstanceMap;
  
  //the map of genealogy CloneInstance loaction to asg
  std::map<std::string, SerializedAsg> serializedAsgMap;
  

  //instead of MD% sum using just the sequence positions only
  std::map<std::string, genealogy::CloneClass*> cloneClassMap;

  // clone visitor
  CloneVisitorBase* theCloneVisitor;

  ostream* filterOut;

  // number of trivial pairs at evolution mapping
#ifdef GENEALOGY
  unsigned int trivial_pairs;
  bool dumpGraphml;
#endif

  // clone instance position at serialized asg
  std::map<NodeId, unsigned int> positions;

  // clone classes length
  std::map<NodeId, unsigned int> lengths;

  std::map<std::string, std::set<columbus::NodeId> > filteredNodes;
  std::set<LineIdentifier>  coveredLines;
  std::map<std::string, std::set<columbus::NodeId> >  coveredNodes;

  CoverageVisitorBase::CCMap coverage;

protected:

  /**
   * \internal
   * \brief update the memory usage statistic 
   */
  void updateMemoryStat();
  /**
   * \internal
   * \brief detect clones in serialized asg
   * \param coveredNodes [out] calculate the covered nodes in asgs
   * \param maxCCSize [in] max clone class item size
   * \param needToSkip [inout] skipped paths
   * \param overlap [in] allow overlapped clone instances
   */
  void detectClones(std::map<std::string, std::set<NodeId> >& coveredNodes, unsigned int maxCCSize, std::set<std::string>& needToSkip) ;

  bool isFilteredCC(const genealogy::CloneClass& cc);

  /**
   * \internal
   * \brief return true, if metric is turned on in rul file
   * \return true, is metric calculation is needed, otherwise return false
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
  void addValue(const string& name, const std::list<columbus::graph::Edge::EdgeType>& relType, const columbus::graph::Node& node, int value, bool sumUp) ;

  /**
   * \internal
   * \brief get node parents
   * \param node [in] the start node
   * \param edgeType [in] get parents along edgetype edges
   * \param nodes [out] parents of the node
   */
  void getParent(const columbus::graph::Node& node, const std::list<columbus::graph::Edge::EdgeType>& relType, std::list<columbus::graph::Node>& nodes) ;

   /**
   * \internal
   * \brief get node parents and parenets parenet too 
   * \param node [in] the start node
   * \param edgeType [in] get parents along edgetype edges
   * \param nodes [out] parents of the node
   */
  void getParentTransitve(const columbus::graph::Node& node, const std::list<columbus::graph::Edge::EdgeType>& relType, std::set<columbus::graph::Node>& nodes) ;

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
   * \brief build clones into output graph and calculate some metrics
   */
  void build_clones_tree() ;

  void incCSOnPrevCloneClass( columbus::genealogy::CloneInstance &ci );

  /**
   * \internal
   * \brief calculate clone coverage metrics
   * \param graph [inout] the output graph
   * \param coverage [in] covered nodes
   */
  void finalize() ;

  void calculateCLLOC();

  void collectContainerFiles( const lim::asg::logical::Package &package, std::set<columbus::Key> &fileNames );

  void addParentComponents( std::set<NodeId> &componentsOfTheClass, NodeId currentComp );

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
   * \param position [in] the start position in serialized asd
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
  genealogy::CloneInstance* createCloneInstance(unsigned int position, unsigned int length, unsigned int intervalStart , std::vector<unsigned int>* intervals, genealogy::CloneClass& parent);

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
   * \brief apply filter in founded clones
   * \param filter [in] the clone filter
   */
  void applyFilter(AbstractFilter* filter);

  /**
   * \internal
   * \breif return first node position at specified interval
   * \param from [in] interval begin
   * \param to [in] interval end
   * \return the node position
   */
  const ClonePositioned* getFirstNode(unsigned int from, unsigned int to) const;

  /**
   * \internal
   * \breif return end node position at specified interval
   * \param from [in] interval begin
   * \param to [in] interval end
   * \return the node position
   */
  const ClonePositioned* getEndNode(unsigned int from, unsigned int to) const;

  /**
   * \internal
   * \brief compute covered nodes
   * \param covertdNodes [out] covered nodes
   */
  void computeCoveredNodes(std::map<std::string, std::set<columbus::NodeId> >& coveredNodes);

  /**
   * \internal
   * \brief evolution mapping
   * \brief systemRef [inout] current system
   * \brief genealogyBase [in] the project
   */
  void evolutionMapping(columbus::genealogy::System& systemRef, columbus::genealogy::Project& genealogyBase);

  /**
   * \internal
   * \brief set clone classes and clone instances unique name
   */
  void setClonesUniqueName();

  /**
   * \internal
   * \brief generate the unique name for genealogy node
   */
  std::string getGraphNameOfGenelogyNode(const columbus::genealogy::Base& genealogyBase);

  /**
   * \internal
   * \brief init genealogy graph
   * \param errorAtLoad [out] true, it genealogy file load is failed
   * \return the created/loaded project
   */
  columbus::genealogy::Project& initGenealogy(bool& errorAtLoad);
  /**
     * \internal
     * \brief init/load lim graph
     * \return the success
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
   * \brief compute coverage to asg-s and build output graph
   * \param cv2 [in] coverage visitor
   * \param  coveredNodes [in] the covered nodes
   */
  void computeCoverage(COVERAGE_VISITOR* cv2, std::map<std::string, std::set<NodeId> >& coveredNodes);

  /**
   * \internal
   * \brief create backup form components to 'backup' directory
   * \param backup [out] the output directory
   */
  void createBackup(const std::string& backup);

  /**
   * \internal
   * \brief use pattern filter and re serialize the asg.
   */
  void patternFilter();

   /**
   * \internal
   * \brief serialize the all given asg-es.
   * \param createComponent create new component for the genealogy
   */

  int serializeAsg(bool createComponent);

  
   /**
   * \internal
   * \brief serialize the a given asg. 
            (This is used by the getInstanceIds to find the old instance of clones.)
   * \param factory the asg factory which need to serialize 
   * \param name the location of component.
   * \param nodeKindSequence the vectors to fill
   * \param nodeIdSequence the vectors to fill
   * \param decDepthSign 
   */
  void serializeAsg(Factory& factory, NodeId componentLimId, std::vector<int>& nodeKindSequence, std::vector<ClonePositioned*>& nodeIdSequence, int& decDepthSign,columbus::lim::asg::Factory*  limFact);




  /**
   * \internal
   * \brief The cpp schema is more complex the other. It has the position data structure which need to traversal to the right order of position nodes. 
   *         This function is do the traversal of nodes by this structure. It call the visitor for all position nodes in the right order.
   */
  void traversalPosiotionedNodes(LANGUAGE_NAMESPACE::Factory& rCurFact, LANGUAGE_NAMESPACE::VisitorAbstractNodes* cloneVisitor,const std::string& componentID, const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned* inner = NULL );

  void fillPositionnodesVektor( LANGUAGE_NAMESPACE::Factory &rCurFact, std::vector<CorrectedPos> &sortedPostitionNodes, const std::string& componenetId);

  bool isNodeAfter( const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned &reference , const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned &questionNode );

  bool PutBeginSignToNode( std::stack<const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned*> &nodeStack, const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned* node, LANGUAGE_NAMESPACE::VisitorAbstractNodes*  cloneVisitor);

  void PutEndSignToNode( std::stack<const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned*> &nodeStack,LANGUAGE_NAMESPACE::VisitorAbstractNodes*  cloneVisitor );


  std::vector<NodeId> getInstanceIds(const genealogy::CloneInstance&);


#ifdef GENEALOGY


  /**
   * \internal
   * \brief compute the F1...F6 atrtibutes on which the similarity is rested.
   */
    
  void computeSimilarityAttributes(columbus::genealogy::CloneInstance& ci);

  /**
   * \internal
   * \brief compute similarity between clone instances
   */
  double similarity(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to);
  /**
   * \internal
   * \return the id of the component or 0
   */
  NodeId getLimComponenetIdByName(const std::string& name , const columbus::lim::asg::Factory& factory);

  const std::string& getAsgNameByLimId(columbus::NodeId limId, const columbus::lim::asg::Factory& factory) const;
  
  std::vector<genealogy::CloneInstance*> getInstancesOfaSystem(const genealogy::System& system) const;
  
#endif
public:

  

  /**
   * \brief start duplicate code mining
   * \param bpaths [inout] blocked paths
   * \param maxCCSize [in] maximum Clone Class size
   * \param backup [in] backup directory (empty string is disabled backup)
   */
  int dcminer(int maxCCSize, const std::string& backup);

  bool isItFilteredInLim( NodeId compId,const columbus::LANGUAGE_NAMESPACE::BASE_NAMESPACE::Base& AsgNode ) const ;

  NodeId getLimNodeIdByNode( NodeId compId, const columbus::LANGUAGE_NAMESPACE::BASE_NAMESPACE::Base& node ) const;

#ifdef GENEALOGY
  /**
   * \internal
   * \brief set dump genealogy to graphml
   */
  void setDumpgraphml( bool dump);

  #endif

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
  const ClonePositioned* getNode(unsigned int sequencePosition) const;

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
   * \brief return true, if id at sequencePosition is asg node (Not a special node kind ex: the end of node sign )
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

  static columbus::Key getUniformPathKey(columbus::Key key, StrTable& strtable );


  /**
   * \brief calculate clone class length
   * \param cc [in] clone class
   * \return the clone class length
   */

  static unsigned int getLength(const genealogy::CloneClass& cc);

  static unsigned int getRealNumberCi(const genealogy::CloneClass& cc);
  static unsigned int getRealNumberCC(const genealogy::System& sys);

  void setFilterOut(std::ostream& out);
  void computeCoveredLines();
  void calculateCOOForLangASG( columbus::NodeId componenetId,const std::string& );

  friend class ProcessCC;
  friend class ProcessPatternFilter;

};

}}

#endif

