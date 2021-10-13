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

#include "../inc/common.h"
#include "../inc/dcm.h"
#include "../inc/StatementFilter.h"
#include <algorithm>
#include <cmath>
#include <common/inc/math/linear/hungarian_method.h>
#include <lim2graph/inc/VisitorGraphConverter.h>
#include <graphsupport/inc/RulBuilder.h>
#include <graphsupport/inc/GraphConstants.h>

#include <common/inc/Stat.h>
#include <iomanip> 
#include <lim/inc/visitors/Visitor.h>
#include <boost/filesystem/path.hpp>
#include <vector>

using namespace common;
#define ROOT_COMPONENT_NAME "<System>"
namespace columbus {
  namespace dcf {
    using namespace suffix_array;


#ifdef SCHEMA_CSHARP
    string  getUniqueNameForMember(const columbus::csharp::asg::base::Base& node) {
        using namespace columbus::csharp::asg;
        string ret = AlgorithmCommon::getName(node);
        base::Positioned* n = dynamic_cast<base::Positioned*>(Common::getScopeParent(&node.getFactory(), node.getId(), AlgorithmCommon::getIsMemberDeclarationSyntax));
        while (n != NULL) {
            if (n->getNodeKind() == ndkNamespaceDeclarationSyntax) {
                structure::NamespaceDeclarationSyntax* nspace = dynamic_cast<structure::NamespaceDeclarationSyntax*>(n);
                expression::NameSyntax* nameSyntax = nspace->getName();
                ret = QualifiedNameSyntaxParser(nameSyntax, ret);
            } else if (n->getNodeKind() == ndkIndexerDeclarationSyntax) {
                structure::IndexerDeclarationSyntax* indexer = dynamic_cast<structure::IndexerDeclarationSyntax*>(n);
                auto paramList = indexer->getParameterList();
                auto params = paramList->getParametersListIteratorBegin();
                string paramListStr;
                unsigned i = 0;
                for (; params != paramList->getParametersListIteratorEnd(); ++params){
                    if (params->getType()->getNodeKind() == ndkPredefinedTypeSyntax){
                        paramListStr += Common::toString(params->getType()->getId())+  " " + params->getIdentifier();
                    } else {
                        paramListStr += AlgorithmCommon::getName(*params->getType()) +  " " + params->getIdentifier();
                    }
                    if (i + 1 < paramList->getParametersSize()) {
                        paramListStr += ", ";
                    }
                    i++;
                }
                ret = "this[" + paramListStr + "]";
            }
            else if (AlgorithmCommon::getIsNamed(*n)) {
                ret = AlgorithmCommon::getName(*n) + "." + ret;
            }
            n = dynamic_cast<base::Positioned*>(Common::getScopeParent(&n->getFactory(), n->getId(), AlgorithmCommon::getIsMemberDeclarationSyntax));
        }

        return ret;
    }
#endif

#ifdef SCHEMA_JAVASCRIPT
    bool getIsMember(const columbus::javascript::asg::base::Base& node) {
      using namespace columbus::javascript::asg;
      return Common::getIsFunctionDeclaration(node) 
        || Common::getIsClassDeclaration(node) 
        || Common::getIsVariableDeclarator(node) 
        || Common::getIsMethodDefinition(node);
    }
    
    const std::string getName(const columbus::javascript::asg::base::Base &node) {
      using namespace columbus::javascript::asg;
      switch (node.getNodeKind()) {
      case NodeKind::ndkFunctionDeclaration:
        if (dynamic_cast<const declaration::FunctionDeclaration&>(node).getIdentifier()) {
          return dynamic_cast<const declaration::FunctionDeclaration&>(node).getIdentifier()->getName();
        }
        common::WriteMsg::write(WriteMsg::mlDebug, "Debug: FunctionDeclaration has no identifier");
        return "";
      case NodeKind::ndkClassDeclaration:
        if (dynamic_cast<const declaration::ClassDeclaration&>(node).getIdentifier()) {
          return dynamic_cast<const declaration::ClassDeclaration&>(node).getIdentifier()->getName();
        }
        common::WriteMsg::write(WriteMsg::mlDebug, "Debug: ClassDeclaration has no identifier");
        return "";
      case NodeKind::ndkVariableDeclarator:
      {
        const declaration::VariableDeclarator& vd = dynamic_cast<const declaration::VariableDeclarator&>(node);
        if (vd.getIdentifier()) {
          if (vd.getIdentifier()->getNodeKind() == NodeKind::ndkIdentifier) {
            const expression::Identifier& identifier = dynamic_cast<const expression::Identifier&>(*(vd.getIdentifier()));
            return identifier.getName();
          }
        }
        return "";
      }

      case NodeKind::ndkMethodDefinition:
      {
        const structure::MethodDefinition& md = dynamic_cast<const structure::MethodDefinition&>(node);
        if (md.getKey()) {
          if (md.getKey()->getNodeKind() == NodeKind::ndkIdentifier) {
            const expression::Identifier& identifier = dynamic_cast<const expression::Identifier&>(*(md.getKey()));
            return identifier.getName();
          }
        }
        return "";
      }
      case NodeKind::ndkProgram:
      {
        const base::Program& pr = dynamic_cast<const base::Program&>(node);
        return pr.getName();
      }
      default:
        return "";
      }
    }
    const std::string getUniqueNameForBase(const columbus::javascript::asg::base::Base& node) {
      std::string ret = getName(node);
      return ret;
    }

    columbus::javascript::asg::base::Base* getScopeParent(const columbus::javascript::asg::base::Base& node) {
      using namespace columbus::javascript::asg;
      Factory& fact = node.getFactory();
      if (&node == fact.getRoot())
        return NULL;

      base::Base* n = node.getParent();
      while (n) {
        if (Common::getIsProgram(*n) || getIsMember(*n)) {
          return n;
        }
        n = n->getParent();
      }
      return NULL;
    }
#endif

#ifdef GENEALOGY
    //when genealogy is maintained the previous factory is also needed

    void DuplicatedCodeMiner::setDumpgraphml( bool dump )
    {
      dumpGraphml = dump;
    }

#define DEBUGPRINTF(x)
#define DEBUGPRINTF2(x)
#define DEBUGPRINTF3(x)

    void DuplicatedCodeMiner::computeSimilarityAttributes(columbus::genealogy::CloneInstance& ci) {

      columbus::genealogy::CloneClass* cc = ci.getCloneClass();
      vector<NodeId> ciRootsList   = getInstanceIds(ci);

      columbus::genealogy::Component* component  = ci.getComponent();
      if (component == NULL)
        throw Exception(COLUMBUS_LOCATION, CMSG_EX_MISSING_COMPONENT_FOR_CI);
      
      Factory* factory = currentFactory.operator ()(component->getLocation());

      // For computing F1, F2, F3, F4, F5 only the first subtree is used!
      columbus::NodeId ciFirstRootId   = ciRootsList[0];
      Base& ciFirstRootNode = factory->getRef(ciFirstRootId);

      /*
      F1: Name of the file containing the clone instance.
      F2: Position of the clone instance inside the clone class.
      F3: The unique name of the head node - if the unique name exists (just for named entities).
      F4: Otherwise, the unique name of the first named ancestor in the AST.
      F5: The relative position of the code segment inside its first named ancestor.
      F6: Lexical structure of the clone instance.
      */
      
      // ============================ Computing F1 Attribute =========================================
      // The path (F1) is always stored 
      // ============================ Computing F2 Attribute =========================================

      if (ci.getF2_OrdinalNumber() == 0) {
        int order = 1;
        for (columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> lIter1=cc->getItemsListIteratorBegin();lIter1!=cc->getItemsListIteratorEnd();++lIter1) {
          if (lIter1->getId()==ci.getId())
            break;
          order++;
        }
        common::WriteMsg::write(WriteMsg::mlDDDDebug,"the F2 is %d for %d\n",order,ci.getId());
        ci.setF2_OrdinalNumber(order);
      }

      // ========================= Computing F3 Attribute ==========================================
#if  defined SCHEMA_JAVA
      if (AlgorithmCommon::getIsNamed(ciFirstRootNode) && AlgorithmCommon::getIsMember(ciFirstRootNode)) {
        Named& toP=dynamic_cast<Named&>(ciFirstRootNode);
#elif  defined SCHEMA_PYTHON
      if (AlgorithmCommon::getIsMemberNode(ciFirstRootNode) ) {
        Base& toP=dynamic_cast<Base&>(ciFirstRootNode);
#elif defined SCHEMA_CSHARP
      if (AlgorithmCommon::getIsNamed(ciFirstRootNode) && AlgorithmCommon::getIsMemberDeclarationSyntax(ciFirstRootNode)) {
          Base& toP = dynamic_cast<Base&>(ciFirstRootNode);
#elif defined SCHEMA_JAVASCRIPT
      if (getIsMember(ciFirstRootNode)) {
        Base& toP=dynamic_cast<Base&>(ciFirstRootNode);
#endif
        if (ci.getF3_HeadNodeUniqueName().empty())  {
          ci.setF3_HeadNodeUniqueName(UNIQUE_NAME_FOR_MEMBER(toP));
          common::WriteMsg::write(WriteMsg::mlDDDDebug,"the F3 is %s for %d\n",ci.getF3_HeadNodeUniqueName().c_str(),ci.getId());
        }
      }

      // ============================ Computing F4 Attribute =======================================
#if defined SCHEMA_PYTHON || defined SCHEMA_JAVASCRIPT
      Base* namedAncestor = NULL;
#else
      Named* namedAncestor = NULL;
#endif
      if (ci.getF4_AncestorUniqueName().empty()) {
#ifdef SCHEMA_JAVA
        namedAncestor = dynamic_cast<Named*>(AlgorithmCommon::getScopeOrMethodDeclarationParent(ciFirstRootNode));
#elif defined SCHEMA_PYTHON
        namedAncestor = dynamic_cast<Base*>(AlgorithmCommon::getScopeParent(ciFirstRootNode));
#elif defined SCHEMA_CSHARP
          namedAncestor = dynamic_cast<Base*>(AlgorithmCommon::getScopeParent(factory, ciFirstRootId, AlgorithmCommon::getIsNamed));
#elif defined SCHEMA_JAVASCRIPT
        namedAncestor = dynamic_cast<Base*>(getScopeParent(ciFirstRootNode));
#endif
        if (namedAncestor != NULL) {
          ci.setF4_AncestorUniqueName(UNIQUE_NAME_FOR_MEMBER(*namedAncestor));
          common::WriteMsg::write(WriteMsg::mlDDDDebug,"the F4 is %s for %d\n",ci.getF4_AncestorUniqueName().c_str(),ci.getId());
        }
      }

      // ================================= Computing F5 Attribute ==================================
      // The L2 is the node count of the instanse so normally it can not be 0. If it is zero then it means that it is not calculated yet.
      if (ci.getF5_L2() == 0 && namedAncestor != NULL) {
#if defined SCHEMA_JAVA || SCHEMA_PYTHON
        if (!AlgorithmCommon::getIsPackage(ciFirstRootNode)) {
#elif defined SCHEMA_CSHARP
        if (!AlgorithmCommon::getIsCompilationUnitSyntax(ciFirstRootNode)) {
#elif defined SCHEMA_JAVASCRIPT
        if (!AlgorithmCommon::getIsSystem(ciFirstRootNode)) {
#endif
          DistanceVisitor dv(ciFirstRootNode.getId());       // All the subtrees should be considered !

          AlgorithmPreorder ap;
#if defined SCHEMA_JAVA || defined SCHEMA_PYTHON
          ap.setVisitSpecialNodes(false, false);
#endif
          ap.run(*factory, dv, *namedAncestor);
        
          ci.setF5_L1(dv.getL1());
          ci.setF5_L2(dv.getL2());
          ci.setF5_L3(dv.getL3());
          common::WriteMsg::write(WriteMsg::mlDDDDebug,"the F5 is L1 %d L2 %d L3 %d for %d\n",dv.getL1(),dv.getL2(),dv.getL3(),ci.getId());
        }
      }

      // ================================ Computing F6 Attribute ===================================
      if (ci.getF6_LexicalStructure().empty()) {
        std::string source;
        for(vector<NodeId>::const_iterator ciRootsListIt = ciRootsList.begin(); ciRootsListIt != ciRootsList.end(); ++ciRootsListIt) {
          NAMED_VISITOR NS;

          AlgorithmPreorder ap;
#if defined SCHEMA_JAVA || defined SCHEMA_PYTHON
          ap.setVisitSpecialNodes(false, false);
#endif
          ap.run(*factory, NS, factory->getRef(*ciRootsListIt));
          source += NS;
        }
        ci.setF6_LexicalStructure(source);
        common::WriteMsg::write(WriteMsg::mlDDDDebug,"the F6 is %s for %d\n",ci.getF6_LexicalStructure().c_str(),ci.getId());

      }

    }
    
    double DuplicatedCodeMiner::similarity(const columbus::genealogy::CloneInstance& from, const columbus::genealogy::CloneInstance& to) {
      static unsigned long counter = 0;
      double inf=std::numeric_limits<double>::infinity();
      ++counter;
      DEBUGPRINTF(printf("[%lu]Similarity:%d -> %d:", counter, from.getId(), to.getId());)

      double dist = 0.0;
      double bound = 0.1;

      double alpha[7]={ 0.0, 0.3122, 0.6365, 0.2066, 0.4293, 0.1101, 0.5080};

      columbus::genealogy::CloneClass& fromClass=*(from.getCloneClass());
      columbus::genealogy::CloneClass& toClass=*(to.getCloneClass());

      if (fromClass.getHeadNodeKind() != toClass.getHeadNodeKind()) {
        DEBUGPRINTF(printf("head mismatch (inf)\n");)
        dist = inf;
      }
      // when the instances don't share the same number of root nodes
      if(from.getRootLength() != to.getRootLength()) {
        common::WriteMsg::write(WriteMsg::mlDDDDebug,"root length mismatch (inf) [%d][%d]\n", from.getRootLength(), to.getRootLength());
        dist = inf;
      }

      double partial[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

      // ========================= Computing F3 ==========================================
      if (dist < bound) {
        if (!from.getF3_HeadNodeUniqueName().empty()) {
          if (!to.getF3_HeadNodeUniqueName().empty()) {

            std::string uniqueNameFrom = from.getF3_HeadNodeUniqueName();
            std::string uniqueNameTo = to.getF3_HeadNodeUniqueName();

            if (uniqueNameFrom != uniqueNameTo) {

              unsigned int n_max=max(uniqueNameFrom.size(),uniqueNameTo.size());

              double similarity = ((double)common::math::editDistance(uniqueNameFrom, uniqueNameTo)) / n_max;
              dist+=alpha[3]*similarity;
              partial[3] = alpha[3]*similarity;
            }
            
          } else {   // to is not named
            dist += alpha[3];
            partial[3] = alpha[3];
          }
        } else if (!to.getF3_HeadNodeUniqueName().empty()) {   // from is not named but to is named
          dist += alpha[3];
          partial[3] = alpha[3];
        } 
      }
      // ======================== Computing F1=============================================
      if (dist < bound) {
        string fromPath = from.getPath();
        string toPath = to.getPath();

        if (!fromPath.empty()) {
          if (!toPath.empty()) {
            boost::filesystem::path p1(fromPath);
            fromPath = (*--p1.end()).string();
            boost::filesystem::path p2(toPath);
            toPath = (*--p2.end()).string();
            if (fromPath != toPath) {
              unsigned int n_max=max(fromPath.size(),toPath.size());
              double pathDistance=((double)common::math::editDistance(fromPath, toPath)) / n_max;
              dist += alpha[1] * pathDistance;
              partial[1] = alpha[1] * pathDistance;
            }
          } else {
            dist += alpha[1];
            partial[1] = alpha[1];
          }
        } else if (!toPath.empty()) {
          dist += alpha[1];
          partial[1] = alpha[1];
        }
      }
      // ============================ Computing F2 =========================================
      if (dist < bound) {
        int order1 = from.getF2_OrdinalNumber();
        int order2 = to.getF2_OrdinalNumber();

        if (order1 != order2) {
          double lineDistance=fabs((double)order1-order2);
          dist += alpha[2] * lineDistance;
          partial[2] = alpha[2] * lineDistance;
        }
      }
      // ============================ Computing F4 ==========================================
      if (dist < bound) {
        if (!from.getF4_AncestorUniqueName().empty()) {
          if (!to.getF4_AncestorUniqueName().empty()) {
            std::string uniqueNameFrom = from.getF4_AncestorUniqueName();
            std::string uniqueNameTo = to.getF4_AncestorUniqueName();
            if (uniqueNameFrom != uniqueNameTo) {
              unsigned int n_max=max(uniqueNameFrom.size(),uniqueNameTo.size());
              double similarity = ((double)common::math::editDistance(uniqueNameTo,uniqueNameFrom)) / n_max;
              dist += alpha[4] * similarity;
              partial[4] = alpha[4] * similarity;
            }
          } else {
            dist += alpha[4];
            partial[4] = alpha[4];
          }
        } else if (!to.getF4_AncestorUniqueName().empty()) {
          dist += alpha[4];
          partial[4] = alpha[4];
        }
      }
      // ================================= Computing F5 ================================================
      if (dist < bound) {
        if (!from.getF4_AncestorUniqueName().empty()) {
          if (!to.getF4_AncestorUniqueName().empty()) {

            unsigned int L = from.getF5_L1() + from.getF5_L2() + from.getF5_L3();
            unsigned int Lv= to.getF5_L1() + to.getF5_L2() + to.getF5_L3();
            double LvpL=(double)Lv/((double)L);
            double similarity=pow(((double)(to.getF5_L1() +1 ) / (from.getF5_L1() +1 ))-LvpL, 2)+
              pow(((double)(to.getF5_L3()+1)/(from.getF5_L3() + 1))-LvpL,2);

            dist += alpha[5]*similarity;
            partial[5] = alpha[5] * similarity;
          } else {
            common::WriteMsg::write(WriteMsg::mlDDDDebug,"F5 FAIL (inf): %lf\n", dist);
            dist = inf;
          }
        } else if (!to.getF4_AncestorUniqueName().empty()) {
          common::WriteMsg::write(WriteMsg::mlDDDDebug,"F5 FAIL (inf): %lf\n", dist);
          dist = inf;
        }
      }

      // ================================ Computing F6 ==========================================
      if (dist < bound) {
        string fromSource = from.getF6_LexicalStructure();
        string toSource = to.getF6_LexicalStructure();

        if (!fromSource.empty()) {
          if (!toSource.empty()) {
            if (fromSource != toSource) {
              unsigned int n_max=max(fromSource.size(),toSource.size());
              unsigned int limit = (unsigned int)(((bound-dist)/alpha[6])*n_max)+1;
              unsigned int edit=common::math::editDistance(fromSource, toSource, limit);
              common::WriteMsg::write(WriteMsg::mlDDDDebug,"F6:[%s][%s][%d]:%d\n",fromSource.c_str(), toSource.c_str(), limit, edit);

              double similarity=((double)edit)/n_max;
              dist += alpha[6] * similarity;
              partial[6] = alpha[6] * similarity;
            }
            common::WriteMsg::write(WriteMsg::mlDDDDebug,"F6:[%s]\n",fromSource.c_str());
          } else {
            dist += alpha[6];
            partial[6] = alpha[6];
          }
        } else if (!toSource.empty()) {
          dist += alpha[6];
          partial[6] = alpha[6];
        }
      }

      common::WriteMsg::write(WriteMsg::mlDDDDebug,"SIMILARITY(%lu): %lf  (1:%lf, 2:%f, 3:%f, 4:%f, 5:%f, 6:%f)\n", counter, dist, partial[1], partial[2], partial[3], partial[4], partial[5], partial[6]);
      DEBUGPRINTF2(fflush(stdout);)

      if (dist > bound)
        return inf;

      return dist;
    }

    vector<genealogy::CloneInstance*> DuplicatedCodeMiner::getInstancesOfaSystem(const genealogy::System& system) const {
      vector<genealogy::CloneInstance*> instances;
      for (genealogy::ListIterator<genealogy::CloneClass> classItemsIter = system.getCloneClassesListIteratorBegin(); classItemsIter != system.getCloneClassesListIteratorEnd(); ++classItemsIter)
        for (genealogy::ListIterator<genealogy::CloneInstance> instanceItemsIter = classItemsIter->getItemsListIteratorBegin();  instanceItemsIter != classItemsIter->getItemsListIteratorEnd(); ++instanceItemsIter) 
          instances.push_back(const_cast<genealogy::CloneInstance*>(&(*instanceItemsIter)));
      return instances;
    }

#endif //GENEALOGY


    inline static void clearNodeIdSequence(std::vector<ClonePositioned*>& nodeIdSequence);

    class ProcessCC : public SuffixArray<int>::CloneVisitor {
    public:
      ProcessCC(const ProcessCC&);
      ProcessCC operator=(const ProcessCC&);
      ProcessCC()
        : needToSkip(NULL)
        , clone_counter(NULL)
        , dcm(NULL)
        , maxCCSize(0)
      {}
      virtual ~ProcessCC(){}
      std::set<std::string>* needToSkip;
      std::map<std::string, unsigned int>* clone_counter;
      DuplicatedCodeMiner *dcm;
      unsigned int maxCCSize;
      DuplicatedCodeMiner::CloneClassPotentialCloneInstanceMap potentialCloneInstances;

    public:
      virtual void visit(SuffixArray<int>::CloneClass& suffixCl) {
        if(!dcm)
          return;
        unsigned int position = suffixCl.position[0];
        unsigned int length = suffixCl.length;
        unsigned int ctl=0;
        bool foundl=false;
        while (ctl<length) {
          if (dcm->isASGNode(position+ctl)) {
            foundl=true;
            break;
          } else
            ctl++;
        }
        if (!foundl) {
          //the pattern does not contain any CPP nodes
          return;
        }
        if (maxCCSize) {
          const ClonePositioned* cp = dcm->getNode(position+ctl);
          std::string path = cp->getStringPath();
          std::map<std::string, unsigned int>::iterator iter=clone_counter->find(path);
          if (needToSkip->find(boost::to_lower_copy(path))==needToSkip->end()) {
            if (iter==clone_counter->end()) {
              clone_counter->insert(std::map<std::string, unsigned int>::value_type(path,1));
            } else {
              if (++(*iter).second == maxCCSize) {
                needToSkip->insert(boost::to_lower_copy(path));
                common::WriteMsg::write(CMSG_NEED_TO_SKIP, path.c_str());
                return;
              }
            }
          } else
            return;
        }

        dcm->alignCloneClass(Aligner::SyntaxBoundary, suffixCl, potentialCloneInstances);
      }

      void buildCloneInstances() {
        for (DuplicatedCodeMiner::CloneClassPotentialCloneInstanceMap::const_iterator ccIt = potentialCloneInstances.begin(); ccIt != potentialCloneInstances.end(); ++ccIt) {
          unsigned lastend = 0;
          for (set<DuplicatedCodeMiner::PotentialCloneInstance>::const_iterator ciIt = ccIt->second.begin(); ciIt != ccIt->second.end(); ++ciIt) {
            if (lastend > 0 && ciIt->startPosition + ciIt->I.a <= lastend)
              continue;

            genealogy::CloneClass& cc = (genealogy::CloneClass&)dcm->genealogyFact->getRef(ccIt->first);
            if (!dcm->containsInstanceAtPositon(ciIt->startPosition + ciIt->I.a, cc)) {
              lastend = ciIt->startPosition + ciIt->I.b;
              dcm->createCloneInstance(ciIt->startPosition + ciIt->I.a, ciIt->I.b - ciIt->I.a + 1, ciIt->startPosition, ciIt->I.intervals, cc);
            }
          }

        }
      }
    };

    class ProcessPatternFilter : public SuffixArray<int>::CloneVisitor {
    public:
      ProcessPatternFilter()
        : sequence(NULL)
        , min_inst_length(0)
        , filteredNodes(NULL)
        , dcm(NULL)
      {

      }
      virtual ~ProcessPatternFilter(){}
      ProcessPatternFilter(const ProcessPatternFilter&);
      ProcessPatternFilter operator= (const ProcessPatternFilter&);
      Sequence<int>* sequence;
      unsigned min_inst_length;


      std::map<std::string, std::set<columbus::NodeId> >* filteredNodes;
      DuplicatedCodeMiner *dcm;

    public:
      virtual void visit(SuffixArray<int>::CloneClass& suffixCl) {
        unsigned int drop_begin = 0;
        unsigned int drop_end = 0;

        unsigned length = suffixCl.length;


        //for(set<unsigned int>::iterator it = suffixCl.position.begin(), prevPos = suffixCl.position.begin(); it != suffixCl.position.end(); ++it) {
        sort(suffixCl.position, suffixCl.position+suffixCl.num);
        for(unsigned it = 0, prevPos = 0; it < suffixCl.num; ++it) {

          if((suffixCl.position[it] - suffixCl.position[prevPos]) == length ) {

            if(drop_begin == 0)
              drop_begin = suffixCl.position[prevPos];
            else
              drop_end = suffixCl.position[it]+length;
          } else {
            if(drop_end !=0 && ( (drop_end - drop_begin) >= min_inst_length ) ) {
              // drop node at x position
              for(unsigned i = drop_begin; i < drop_end; i++) {
                ClonePositioned* clonePos = dcm->nodeIdSequence[i];
                if(clonePos != NULL) {
                  (*filteredNodes)[dcm->getAsgNameByLimId(clonePos->getLimComponentId(), *dcm->limFact)].insert(clonePos->getId());
                }
              }
            }
            drop_begin = 0;
            drop_end = 0;
          }
          prevPos = it;
        }

        if(drop_end !=0 && ( (drop_end - drop_begin) >= min_inst_length ) ) {
          // drop node at x position
          for(unsigned i = drop_begin; i < drop_end; i++) {
            ClonePositioned* clonePos = dcm->nodeIdSequence[i];
            if(clonePos != NULL) {
              (*filteredNodes)[dcm->getAsgNameByLimId(clonePos->getLimComponentId(), *dcm->limFact)].insert(clonePos->getId());
            }
          }
        }
      }
    };


    void DuplicatedCodeMiner::patternFilter() {
      if(config.patternMaxSingleLength == 0 || config.patternMinFullLength == 0)
        return;

      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("patternFilter()");

      common::timestat time = common::getProcessUsedTime();
      Sequence<int> sequence(nodeKindSequence);
      ProcessPatternFilter ppf;
      ppf.sequence = &sequence;
      ppf.min_inst_length = config.patternMinFullLength;
      ppf.dcm = this;
      ppf.filteredNodes = &filteredNodes;

      LinearSuffixArray<int> suffixArray(sequence);
      LinearSuffixArray<int>::Duplicateiterator lduplicateIterator = suffixArray.iterator(1, config.patternMaxSingleLength, config.patternMinFullLength, false);


      lduplicateIterator.run(ppf);
      size_t count = 0;
      for(std::map<string, std::set<columbus::NodeId> >::iterator it = filteredNodes.begin(); it != filteredNodes.end(); ++it) {
        count+=it->second.size();
      }

      auto filterTime = common::getProcessUsedTime().user - time.user;
      common::WriteMsg::write(CMSG_NODE_FILTERED_OUT, count, filterTime);

      config.stat.filterTime += filterTime;


      perfSectionHandler.addTimeStamp("reserialize");
      // re serialize the asg/ast with filter
      if(count > 0)
        serializeAsg(false);


    }

    
    void DuplicatedCodeMiner::dumpNodeIdSequence(const std::string filename)
    {
      ofstream out;
      out.open(filename, ios::out | ios::trunc);
      
      unsigned indent_size = 0;
      if(out.is_open())
      {
        for(auto node : nodeIdSequence)
        {
          if(node)
          {
            for(unsigned i = 0; i < indent_size; ++i){
              out << " ";
            }
            out <<  node->getStringPath() << " : " << node->getLine() << ":" << node->getCol() << " | " << node->getEndLine() << ":" << node->getEndCol() << endl;
            indent_size += 2;
          }else{
            out << endl;
            indent_size -= 2;
          }
        }
        out.close();
      }
      
    }
    void DuplicatedCodeMiner::dumpNodeKindSequence(const std::string filename){
      ofstream out;
      out.open(filename);
      int indent_size = 0;
      if(out.is_open())
      {
        for(auto kind : nodeKindSequence)
        {
          if(kind == -2){
            indent_size -= 2;
          }
          for(int i = 0; i < indent_size; ++i){
            out << " ";
          }
          out << kind << endl;
          
          if(kind != -2)
            indent_size += 2;
          
        }
        out.close();
      }
    }
    
    void DuplicatedCodeMiner::detectClones(std::map<std::string, std::set<NodeId> >& coveredNodes, unsigned int maxCCSize, std::set<std::string>& needToSkip)
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("detectClones()");

      common::timestat time = common::getProcessUsedTime();

      common::WriteMsg::write(CMSG_USE_PATTERNFILTER);
      patternFilter();

      config.stat.serializedASGLengthFiltered = nodeIdSequence.size();

      common::WriteMsg::write(CMSG_DETECTING_CLONES);
      nodeKindSequence.push_back(theCloneVisitor->getUniqueValue());

      /**
      * suffix array patch
      */

      time = common::getProcessUsedTime();

      std::map<std::string, unsigned int> clone_counter;
      Sequence<int> sequence(nodeKindSequence);

      LinearSuffixArray<int> suffixArray(sequence);
      common::WriteMsg::write(CMSG_CLONE_DETECTION_DONE_IN, common::getProcessUsedTime().user - time.user);

      common::WriteMsg::write(CMSG_GENERATING_CLONE_INSTANCES);


      perfSectionHandler.addTimeStamp("clone detection");

      time = common::getProcessUsedTime();
      LinearSuffixArray<int>::Duplicateiterator lduplicateIterator = suffixArray.iterator( config.minAsgNodes, 0, 0, true);

      ProcessCC processCC;

      processCC.clone_counter = &clone_counter;
      processCC.dcm = this;
      processCC.maxCCSize = maxCCSize;
      processCC.needToSkip = &needToSkip;

      lduplicateIterator.run(processCC);

      updateMemoryStat();
      common::WriteMsg::write(CMSG_PROBALBLY_CLONES_FOUND);
      processCC.buildCloneInstances();

      common::WriteMsg::write(CMSG_DONE_IN, common::getProcessUsedTime().user - time.user);

      config.stat.cloneFindTime += common::getProcessUsedTime().user - time.user;

      updateMemoryStat();
      common::memstat m = common::getProcessUsedMemSize();
      common::WriteMsg::write(CMSG_MEM_USED, m.size / ( 1024 * 1024));

      time = common::getProcessUsedTime();
      /**
      * The results are being filtered based on different approaches
      **/

      perfSectionHandler.addTimeStamp("clone instances");
      updateMemoryStat();
      common::WriteMsg::write(CMSG_APPLYING_FILTERS);
      CloneOccuranceFilter cof(config.minOccur);
      CloneLengthFilter clf(config.minLines);
      RepeatingLinesFilter rlf(*this);


      StatementFilter      stf(*this);

      applyFilter(&cof);
      applyFilter(&clf);
      applyFilter(&rlf);

      if (statementFilter) {
        applyFilter(&stf);
      }


      config.stat.cloneClassFilterTime = common::getProcessUsedTime().user - time.user;
      time = common::getProcessUsedTime();

      perfSectionHandler.addTimeStamp("clone filtering");

      //calculating coverage
      if (config.metrics) {
        updateMemoryStat();
        common::WriteMsg::write(CMSG_COMPUTING_COVERED_NODES);
        computeCoveredNodes(coveredNodes);
        perfSectionHandler.addTimeStamp("computeCoveredNodes");
        computeCoveredLines();
        perfSectionHandler.addTimeStamp("computeCoveredLines");
        updateMemoryStat();
        common::WriteMsg::write(CMSG_DONE_D);
      }
      config.stat.calculateMetricsTime += common::getProcessUsedTime().user - time.user;
      perfSectionHandler.addTimeStamp("clone metrics");
    }

    void DuplicatedCodeMiner::computeCoveredNodes(std::map<std::string, std::set<columbus::NodeId> >& coveredNodes) {
      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIt != currentSystem->getCloneClassesListIteratorEnd();++cloneClassIt) { //clone class
        const genealogy::CloneClass& cc = *cloneClassIt;
        if (cc.getIsVirtual())
          continue;
        unsigned int length =  lengths[cc.getId()];
        for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt) { //clone instance
          const genealogy::CloneInstance& ci = *cloneInstanceIt;
          unsigned int pos = positions[ci.getId()];
          for(unsigned int i = 0; i < length; ++i) {
            const ClonePositioned* position = getNode(pos + i);
            if(position) {
              map<std::string, std::set<columbus::NodeId> >::iterator coverageIt=coveredNodes.find(getAsgNameByLimId(position->getLimComponentId(),*limFact));
              if(coverageIt == coveredNodes.end()) {
                set<NodeId> nodeSet;
                nodeSet.insert(position->getId());
                coveredNodes.insert(make_pair(getAsgNameByLimId(position->getLimComponentId(),*limFact), nodeSet));
              } else {
                (coverageIt->second).insert(position->getId());
              }
            }
          }
        } //clone instances
      } // clone classes
    }

    void DuplicatedCodeMiner::computeCoveredLines() {

      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIt != currentSystem->getCloneClassesListIteratorEnd();++cloneClassIt) {
        const genealogy::CloneClass& cc = *cloneClassIt;
        if (cc.getIsVirtual())
          continue;

        for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt) {
          const genealogy::CloneInstance& ci = *cloneInstanceIt;
          std::string path =  ci.getPath();
            unsigned int pos = positions[ci.getId()];
          if (ci.getRootBegin() && nodeIdSequence[pos] ) {
            columbus::lim::asg::logical::Member& node = (columbus::lim::asg::logical::Member&)limFact->getRef((nodeIdSequence [pos]->getLimNodeId()));

            if ( columbus::lim::asg::Common::getIsClass(node) 
              || columbus::lim::asg::Common::getIsMethod(node)
              || columbus::lim::asg::Common::getIsPackage(node)
              || columbus::lim::asg::Common::getIsComponent(node)) {

                if (!node.getIsContainedInIsEmpty()) {
                  path = columbus::lim::asg::Common::getFullPath (*node.getIsContainedInListIteratorAssocBegin());
                }
            }
          }
          LowerStringOnWindows(path);
          Key fileId = limFact->getStringTable().set(path);

          for(unsigned int i = ci.getLine(); i <= ci.getEndLine(); ++i) {
            coveredLines.insert(LineIdentifier(fileId,i));
          }
        }
      }
    }

    void DuplicatedCodeMiner::build_clones_tree() {
      common::timestat time = common::getProcessUsedTime();
      // create clone instance and clone class nodes in the graph and set its metrics.
      common::WriteMsg::write(CMSG_BUILD_CLONE_TREE);
      columbus::genealogy::System& lastSystemRef = (columbus::genealogy::System&)*currentSystem;
      columbus::graph::Node        cloneRootNode = graph.findNode(graphsupport::graphconstants::UID_CLONE_ROOT);
      std::set<NodeId>             componentsOfTheClass;  // Container to store the components of all the corresponding clone instance nodes

      for (columbus::genealogy::ListIterator< columbus::genealogy::CloneClass> groupsIter=lastSystemRef.getCloneClassesListIteratorBegin();groupsIter!=lastSystemRef.getCloneClassesListIteratorEnd();++groupsIter) { // clone classes
        columbus::genealogy::CloneClass& cc= (columbus::genealogy::CloneClass&) groupsIter->getFactory().getRef(  groupsIter->getId());
        componentsOfTheClass.clear();

        columbus::graph::Node classItem = graph.findNode(getGraphNameOfGenelogyNode(cc));
        if(classItem == columbus::graph::Graph::invalidNode) {
          classItem = graph.createNode(getGraphNameOfGenelogyNode(cc), columbus::graph::Node::NodeType(graphsupport::graphconstants::NTYPE_DCF_CLONECLASS));
          graphsupport::addNodeNameAttribute(graph,classItem,cc.getUniqueName());
          graph.createDirectedEdge(cloneRootNode, classItem, graphsupport::graphconstants::ETYPE_DCF_CLONETREE, true);
        }
        columbus::graphsupport::setStringAttribute(graph,classItem, graphsupport::graphconstants::ATTR_DCF_CLONESMELLTYPE,  columbus::genealogy::Common::toString( cc.getCloneSmellType()));

        std::vector<const columbus::genealogy::CloneInstance*> instances;

        // first deal with clone instances
        for (columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> itemsIter=cc.getItemsListIteratorBegin();itemsIter!=cc.getItemsListIteratorEnd();++itemsIter) {
          columbus::genealogy::CloneInstance& ci = (columbus::genealogy::CloneInstance&)((*itemsIter).getFactory().getRef((*itemsIter).getId()));
          std::list<columbus::graph::Node> nodes;

          columbus::graph::Node instanceItem = graph.findNode(getGraphNameOfGenelogyNode(ci));
          if(instanceItem == columbus::graph::Graph::invalidNode) {
            instanceItem = graph.createNode(getGraphNameOfGenelogyNode(ci), columbus::graph::Node::NodeType(graphsupport::graphconstants::NTYPE_DCF_CLONEINSTANCE));
            graphsupport::addNodeNameAttribute(graph,instanceItem, ci.getUniqueName());
          }
          graph.createDirectedEdge(classItem, instanceItem, graphsupport::graphconstants::ETYPE_DCF_CLONETREE, true);

          if (ci.getIsVirtual()) {
            columbus::graphsupport::setStringAttribute(graph, instanceItem, graphsupport::graphconstants::ATTR_DCF_CLONESMELLTYPE,  columbus::genealogy::Common::toString( ci.getCloneSmellType()));
            continue;
          }

          columbus::graphsupport::addPositionAttribute(graph, instanceItem, ci.getPath(), ci.getLine(), ci.getCol(), ci.getEndLine(), ci.getEndCol());
          instances.push_back(&ci);

          // set metrics of clone instances
          if (getIsNeeded("CLLOC")) {
            unsigned int loc=ci.getEndLine()-ci.getLine()+1;
            columbus::graphsupport::setMetricInt(graph, instanceItem, "CLLOC", loc);
          }

          if (getIsNeeded("CCO")) {
            columbus::graphsupport::setMetricInt(graph, instanceItem, "CCO", ci.getCco());
          }

          if (getIsNeeded("CA")) {
            columbus::graphsupport::setMetricInt(graph, instanceItem, "CA",  ci.getCa());
          }

          columbus::graphsupport::setStringAttribute(graph, instanceItem, graphsupport::graphconstants::ATTR_DCF_CLONESMELLTYPE,  columbus::genealogy::Common::toString( ci.getCloneSmellType()));

          if (getIsNeeded("CV")) {
            columbus::graphsupport::setMetricFloat(graph, instanceItem, "CV",  (float)ci.getCv());
          }

          if (getIsNeeded("CE")) {
            columbus::graphsupport::setMetricInt(graph, instanceItem, "CE",  ci.getCe());
          }

          std::map<NodeId,std::set<NodeId> >::iterator itLimNodes          = limNodeClineInstanceMap.find(ci.getId());
          std::map<NodeId,std::set<NodeId> >::iterator itLimComponent      = limComponentClineInstanceMap.find(ci.getId());
          const std::set<NodeId >& componentsOfTheInstance                 = itLimComponent->second;

          if (itLimNodes != limNodeClineInstanceMap.end() ) {
            std::set<columbus::NodeId>& nodes = itLimNodes->second;
            for (std::set<columbus::NodeId>::iterator itLimNodes = nodes.begin();itLimNodes != nodes.end();++itLimNodes ) {
              std::string gaphNodeUUid =  columbus::lim2graph::VisitorGraphConverter::determineNodeName(limFact->getRef(*itLimNodes));
              columbus::graph::Node theItem = graph.findNode(gaphNodeUUid); 
              if (theItem != columbus::graph::Graph::invalidNode) {
                graph.createDirectedEdge(theItem, instanceItem, graphsupport::graphconstants::ETYPE_DCF_HASCLONE, true);
              }
            }
          }

          // Create the component edges of the clone instance nodes
          for (std::set<NodeId >::const_iterator componentsIt = componentsOfTheInstance.begin(); componentsIt != componentsOfTheInstance.end(); ++componentsIt) {
            std::string gaphNodeUUid =  columbus::lim2graph::VisitorGraphConverter::determineNodeName(limFact->getRef(*componentsIt));
            columbus::graph::Node theCommponent = graph.findNode(gaphNodeUUid); 
            if (theCommponent != columbus::graph::Graph::invalidNode) {
              graph.createDirectedEdge(instanceItem, theCommponent, graphsupport::graphconstants::ETYPE_LIM_COMPONENT, true);
            } else {
              common::WriteMsg::write(WriteMsg::mlWarning,"The commponent not found for cc %d componenet uuid %s",cc.getId(),gaphNodeUUid.c_str());
            }
          }

          // Adding the components of the instance to the component set of the clone class
          componentsOfTheClass.insert(componentsOfTheInstance.begin(), componentsOfTheInstance.end());
        } //loop clone instance

        // deal with clone classes
        // Create the component edges of the clone class nodes
        for (std::set<NodeId>::const_iterator componentsIt = componentsOfTheClass.begin(); componentsIt != componentsOfTheClass.end(); ++componentsIt) {
          std::string gaphNodeUUid =  columbus::lim2graph::VisitorGraphConverter::determineNodeName(limFact->getRef(*componentsIt));
          columbus::graph::Node theComponent = graph.findNode(gaphNodeUUid); 
          graph.createDirectedEdge(classItem, theComponent, graphsupport::graphconstants::ETYPE_LIM_COMPONENT, true);
        }
        // set clone class metrics
        if (!cc.getIsVirtual()){

          if (getIsNeeded("CLLOC")) {
            columbus::graphsupport::setMetricFloat(graph, classItem, "CLLOC", (float)cc.getClloc());
          }

          if (getIsNeeded("CI")) {
            columbus::graphsupport::incMetricInt(graph, classItem, "CI", instances.size());
          }

          if (getIsNeeded("CCO")) {
            columbus::graphsupport::setMetricInt(graph, classItem, "CCO", cc.getCco());
          }

          if (getIsNeeded("CE")) {
            columbus::graphsupport::setMetricInt(graph, classItem, "CE", cc.getCe());
          }

          if (getIsNeeded("CA")) {
            columbus::graphsupport::setMetricInt(graph, classItem, "CA", cc.getCa());
          }

          if (getIsNeeded("NCR")) {
            columbus::graphsupport::incMetricFloat(graph, classItem, "NCR", (float)cc.getNcrad());
          }
          
          //CLLOC * CI * CCO * NCR * CS
          if (getIsNeeded("CR")) {
            columbus::graphsupport::setMetricFloat(graph, classItem, "CR", (float)cc.getRisk());
          }

          //CI * CED * NCR
          if (getIsNeeded("CEE")) {
            columbus::graphsupport::setMetricFloat(graph, classItem, "CEE", (float)cc.getEffort());
          }

          // CR / CEE
          if (getIsNeeded("CEG")) {
            columbus::graphsupport::setMetricFloat(graph, classItem, "CEG", (float)cc.getGain());
          }

          if (getIsNeeded("CV")) {
            columbus::graphsupport::setMetricFloat(graph, classItem, "CV", (float)cc.getCv());
          }
        }
      }

      common::WriteMsg::write(CMSG_DONE_D);
      config.stat.buildCloneTreeTime += common::getProcessUsedTime().user - time.user;
    }

    struct CollectedMetricsForComponent {
      double sumNCR;
      double numNCR;
      double sumCR;
      double CEE;
      CollectedMetricsForComponent(): sumNCR(0), numNCR(0), sumCR(0), CEE (0){};
    };

    void DuplicatedCodeMiner::finalize() {
      common::timestat time = common::getProcessUsedTime();
      int time_lineMetrics = 0;
      
      common::WriteMsg::write(CMSG_START_FINALIZING);
      map<NodeId, CollectedMetricsForComponent> componenetMetrics; //TODO rename

      // intialize clone metrics for the <System> component
      columbus::graph::Node systemComponentGraphNode = graph.findNode(columbus::lim2graph::VisitorGraphConverter::determineNodeName(limFact->getRef(rootComponenetID)));
      if (systemComponentGraphNode != columbus::graph::Graph::invalidNode)
      {
        if (getIsNeeded("CCL"))
          columbus::graphsupport::setMetricInt(graph, systemComponentGraphNode, "CCL", 0);

        if (getIsNeeded("CCO"))
          columbus::graphsupport::setMetricInt(graph, systemComponentGraphNode, "CCO", 0);

        if (getIsNeeded("CC"))
          columbus::graphsupport::setMetricINVALID(graph, systemComponentGraphNode, "CC");

        if (getIsNeeded("CEE"))
          columbus::graphsupport::setMetricFloat(graph, systemComponentGraphNode, "CEE", 0);

        if (getIsNeeded("CEG"))
          columbus::graphsupport::setMetricINVALID(graph, systemComponentGraphNode, "CEG");

        if (getIsNeeded("CI"))
          columbus::graphsupport::setMetricInt(graph, systemComponentGraphNode, "CI", 0);

        if (getIsNeeded("CLC"))
          columbus::graphsupport::setMetricINVALID(graph, systemComponentGraphNode, "CLC");

        if (getIsNeeded("CLLC"))
          columbus::graphsupport::setMetricINVALID(graph, systemComponentGraphNode, "CLLC");

        if (getIsNeeded("CR"))
          columbus::graphsupport::setMetricINVALID(graph, systemComponentGraphNode, "CR");

        if (getIsNeeded("LDC"))
          columbus::graphsupport::setMetricInt(graph, systemComponentGraphNode, "LDC", 0);

        if (getIsNeeded("LLDC"))
          columbus::graphsupport::setMetricInt(graph, systemComponentGraphNode, "LLDC", 0);

        if (getIsNeeded("NCR"))
          columbus::graphsupport::setMetricINVALID(graph, systemComponentGraphNode, "NCR");

      }


      // Initialize those metrics which are additive metrics 
      for (columbus::lim::asg::Factory::const_iterator it = limFact->begin() ;it != limFact->end();++it) {
        std::string UUI = columbus::lim2graph::VisitorGraphConverter::determineNodeName(**it);
        // component
        if (columbus::lim::asg::Common::getIsComponent(**it)) {
          if (getIsNeeded("CI")) {
            columbus::graphsupport::setMetricInt(graph, UUI, "CI", 0);
          }
          if (getIsNeeded("CCO")) {
            columbus::graphsupport::setMetricInt(graph, UUI, "CCO", 0);
          }
          if (getIsNeeded("CCL")) {
            columbus::graphsupport::setMetricInt(graph, UUI, "CCL", 0);
          }
        }
        // package, class, method
        if (columbus::lim::asg::Common::getIsPackage(**it) || columbus::lim::asg::Common::getIsClass(**it) || columbus::lim::asg::Common::getIsMethod(**it)  ) {

          bool isDecl = false;
          if ( columbus::lim::asg::Common::getIsMethod(**it)) {
            const columbus::lim::asg::logical::Method* asMethode = dynamic_cast<const columbus::lim::asg::logical::Method*>(*it);
            if (!asMethode->getIsContainedInIsEmpty()) {
              if (asMethode->getIsContainedInListIteratorAssocBegin().getAssocClass().getRealizationLevel() == columbus::lim::asg::relDeclares) {
                isDecl = true;
              }
            }
            if (getIsNeeded("CLLC")) {
              columbus::graphsupport::setMetricFloat(graph, UUI, "CLLC",0);
            }
          }

          if (isDecl) {
            if (getIsNeeded("CC")) {
              columbus::graphsupport::setMetricINVALID(graph, UUI, "CC");
            }

            if (getIsNeeded("CI")) {
              columbus::graphsupport::setMetricINVALID(graph, UUI, "CI");
            }

            if (getIsNeeded("CCL")) {
              columbus::graphsupport::setMetricINVALID(graph, UUI, "CCL");
            }

            if (getIsNeeded("CCO")) {
              columbus::graphsupport::setMetricINVALID(graph, UUI, "CCO");
            }
          } else {
            if (visitedLimNodes.count((**it).getId()) ) {
              if (getIsNeeded("CC")) {
                  columbus::graphsupport::setMetricFloat(graph, UUI, "CC", 0);
              }

              if (getIsNeeded("CI")) {
                  columbus::graphsupport::setMetricInt(graph, UUI, "CI", 0);

              }

              if (getIsNeeded("CCL")) {
                  columbus::graphsupport::setMetricInt(graph, UUI, "CCL", 0);
              }

              if (getIsNeeded("CCO")) {
                  columbus::graphsupport::setMetricInt(graph, UUI, "CCO", 0);
              }
            
            }
          }
        }
      } //Init end

      std::map<NodeEmbeddednessVisitorBase::NodeGlobalId, unsigned int> positionCache;
      if (getIsNeeded("CE")) {
        //fill pos cache
        for(size_t i = 0; i < nodeIdSequence.size(); i++) {
          if(nodeIdSequence[i]) {
            positionCache[NodeEmbeddednessVisitorBase::NodeGlobalId(nodeIdSequence[i]->getLimComponentId(),nodeIdSequence[i]->getId())] = i;
          }
        }
      }

      /**
      * Generating metrics for lim nodes.
      **/
      if (getIsNeeded("CC")) {
        for (CoverageVisitorBase::CCMap::const_iterator iter=coverage.begin();iter!=coverage.end();++iter) {
          const UniqueNameWithPath& uname =(*iter).first;
          float d = (*iter).second.cc;

          common::WriteMsg::write(CMSG_SETTING_METRICS_FOR, uname.path.c_str(), uname.line, uname.uniqueName.c_str());

          if (uname.limNodeId) {
            lim::asg::base::Base& base = limFact->getRef(uname.limNodeId);
            std::string gaphNodeUUid =  columbus::lim2graph::VisitorGraphConverter::determineNodeName(base);
            graph::Node gNode = graph.findNode(gaphNodeUUid);
            if (gNode != columbus::graph::Graph::invalidNode) {
              columbus::graphsupport::removeMetric (graph, gNode, "CC");
              columbus::graphsupport::setMetricFloat(graph, gNode, "CC", d);

              common::WriteMsg::write(CMSG_M_CLONECOVERAGE, d);
              common::timestat time_calculateLineMetrics = common::getProcessUsedTime();              
              if (uname.line != UniqueNameWithPath::BAD_PATH ){
                std::string path;
                int line, col, endline, endcol;
                if (graphsupport::getPositionAttribute(gNode, path, line, col, endline, endcol)) {
                  if (uname.line == line && uname.path == path) {
                    std::string lowpath =path;
                    LowerStringOnWindows(lowpath);
                    columbus::Key filekey = limFact->getStringTable().set(lowpath.c_str());
                    int numCoveredLines = 0;
                    int numCoveredLogicalLines = 0;
                    int numLogicalLines = 0;


                    for (int i =line;i<(endline+1);i++){
                      LineIdentifier lineId(filekey,i);
                      bool isCoveredLines = (coveredLines.count(lineId) > 0);
                      bool islogicallines = (logicalLines.count(lineId) > 0);

                      if (isCoveredLines){
                        numCoveredLines++;
                      }

                      if (islogicallines) {
                        numLogicalLines++;
                      }

                      if (islogicallines && isCoveredLines) {
                        numCoveredLogicalLines++;
                      }
                    }

                    int lines = endline-line+1;

                    if (getIsNeeded("CLLC")){
                      columbus::graphsupport::removeMetric(graph, gNode, "CLLC");
                      columbus::graphsupport::setMetricFloat(graph, gNode, "CLLC", (float)numCoveredLogicalLines/numLogicalLines);
                    }

                  
                    if (getIsNeeded("LLDC")){
                      columbus::graphsupport::setMetricInt(graph, gNode, "LLDC", numCoveredLogicalLines);
                    }
                    if (getIsNeeded("LDC")){
                      columbus::graphsupport::setMetricInt(graph, gNode, "LDC", numCoveredLines);
                    }
                    if (getIsNeeded("CLC")){
                      columbus::graphsupport::setMetricFloat(graph, gNode, "CLC", (float)numCoveredLines/lines);
                    }
                  }else {
                    common::WriteMsg::write(WriteMsg::mlWarning,"Something is not good when find a node");
                  }
                } else {
                  if (uname.line == 0 && uname.path.empty())  {
                    if (lim::asg::Common::getIsComponent( base)) {
                      const lim::asg::base::Component& component = dynamic_cast<const lim::asg::base::Component&> (base);
                      std::map<NodeId,std::set<columbus::Key> >::iterator itFile = fileNamesByComponent.find(base.getId());
                      if (itFile != fileNamesByComponent.end()) {
                        int numCoveredLines = 0;
                        int numCoveredLogicalLines = 0;

                        for (std::set<LineIdentifier>::iterator it = coveredLines.begin() ;it != coveredLines.end();++it){
                          if (itFile->second.count(it->path) ) {
                            numCoveredLines++;
                          }
                        }

                        std::vector<LineIdentifier> itersection(max(coveredLines.size(),logicalLines.size()));
                        std::vector<LineIdentifier>::iterator retIterator;
                        retIterator = std::set_intersection(coveredLines.begin(),coveredLines.end(),logicalLines.begin(),logicalLines.end(),itersection.begin());
                        itersection.resize(retIterator-itersection.begin());  


                        for ( std::vector<LineIdentifier>::iterator it = itersection.begin() ;it != itersection.end();++it){
                          if (itFile->second.count(it->path) ) {
                            numCoveredLogicalLines++;
                          }
                        }

                        if (getIsNeeded("CLLC")){
                          columbus::graphsupport::removeMetric(graph, gNode, "CLLC");
                          columbus::graphsupport::setMetricFloat(graph, gNode, "CLLC", (float)numCoveredLogicalLines/component.getTLLOC());
                        }
                        if (getIsNeeded("LLDC")){
                          columbus::graphsupport::setMetricInt(graph, gNode, "LLDC", numCoveredLogicalLines);
                        }

                        if (getIsNeeded("LDC")){
                          columbus::graphsupport::setMetricInt(graph, gNode, "LDC", numCoveredLines);
                        }

                        if (getIsNeeded("CLC")){
                          columbus::graphsupport::setMetricFloat(graph, gNode, "CLC", (float)numCoveredLines/component.getTLOC());
                        }
                        
                      } else {
                        if (getIsNeeded("CLLC")){
                          columbus::graphsupport::setMetricFloat(graph, gNode, "CLLC", 0);
                        }
                        if (getIsNeeded("LLDC")){
                          columbus::graphsupport::setMetricInt(graph, gNode, "LLDC", 0);
                        }
                        if (getIsNeeded("LDC")){
                          columbus::graphsupport::setMetricInt(graph, gNode, "LDC", 0);
                        }

                        if (getIsNeeded("CLC")){
                          columbus::graphsupport::setMetricFloat(graph, gNode, "CLC",0);
                        }
                      }

                    //package / namespace node metrics
                    } else  if (lim::asg::Common::getIsPackage(base)) {
                      const lim::asg::logical::Package& package = (const lim::asg::logical::Package&) base;
                      std::set<columbus::Key> fileNames;
                      collectContainerFiles(package, fileNames);

                      int numCoveredLines = 0;
                      int numCoveredLogicalLines = 0;
                      int numLogicalLines = 0;

                      for (std::set<LineIdentifier>::iterator it = coveredLines.begin() ;it != coveredLines.end();++it){
                        if (fileNames.count(it->path)) {
                          numCoveredLines++;
                        }
                      }

                      for (std::set<LineIdentifier>::iterator it = logicalLines.begin() ;it != logicalLines.end();++it){
                        if (fileNames.count(it->path)) {
                          numLogicalLines++;
                        }
                      }

                      std::vector<LineIdentifier> itersection(max(coveredLines.size(),logicalLines.size()));
                      std::vector<LineIdentifier>::iterator retIterator;
                      retIterator = std::set_intersection(coveredLines.begin(),coveredLines.end(),logicalLines.begin(),logicalLines.end(),itersection.begin());
                      itersection.resize(retIterator-itersection.begin());  


                      for ( std::vector<LineIdentifier>::iterator it = itersection.begin() ;it != itersection.end();++it){
                        if (fileNames.count(it->path)) {
                          numCoveredLogicalLines++;
                        }
                      }

                      if (getIsNeeded("CLLC")){
                        columbus::graphsupport::removeMetric(graph, gNode, "CLLC");
                        columbus::graphsupport::setMetricFloat(graph, gNode, "CLLC", (float)numCoveredLogicalLines/numLogicalLines);
                      }
                      if (getIsNeeded("LLDC")){
                        columbus::graphsupport::setMetricInt(graph, gNode, "LLDC", numCoveredLogicalLines);
                      }
                      if (getIsNeeded("LDC")){
                        columbus::graphsupport::setMetricInt(graph, gNode, "LDC", numCoveredLines);
                      }
                      if (getIsNeeded("CLC")){
                        columbus::graphsupport::setMetricFloat(graph, gNode, "CLC", (float)numCoveredLines/package.getTLOC());
                      }

                    }
                  }
                }
              }
              time_lineMetrics += common::getProcessUsedTime().user - time_calculateLineMetrics.user;
              
            }
          } 
        }
      }

      //calculate CC and CCO metrics for clone instances and classes and set it on the genealogy.

      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin();cloneClassIt != currentSystem->getCloneClassesListIteratorEnd();++cloneClassIt) {
        columbus::genealogy::CloneClass& cc= (columbus::genealogy::CloneClass&) cloneClassIt->getFactory().getRef(  cloneClassIt->getId());
        if (cc.getIsVirtual())
          continue;

        unsigned int length = lengths[cc.getId()];

        std::set<columbus::graph::Node> allCloneClassParentsList;
        std::set<NodeId>                componentsOfTheClass;
        std::vector<const columbus::genealogy::CloneInstance*> instances;
        unsigned int avgLocSum = 0;

        for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin(); cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt) {
          columbus::genealogy::CloneInstance& ci=  (columbus::genealogy::CloneInstance&)((*cloneInstanceIt).getFactory().getRef((*cloneInstanceIt).getId()));
          if (ci.getIsVirtual())
            continue;
          instances.push_back(&ci);
          std::set<columbus::NodeId>* nodes = NULL;
          std::set<columbus::graph::Node> allParentsList; // contains the transitive parents too 


          if (getIsNeeded("CLLOC")) {
            unsigned int loc=ci.getEndLine()-ci.getLine()+1;
            avgLocSum += loc;
          }

          std::map<NodeId,std::set<NodeId> >::iterator itLimNodes = limNodeClineInstanceMap.find(ci.getId());
          if (itLimNodes != limNodeClineInstanceMap.end() ) {
            nodes = &itLimNodes->second;
            for (std::set<columbus::NodeId>::iterator itLimNodes = (*nodes).begin();itLimNodes != (*nodes).end();++itLimNodes ) {
              std::string gaphNodeUUid =  columbus::lim2graph::VisitorGraphConverter::determineNodeName(limFact->getRef(*itLimNodes));
              columbus::graph::Node theItem = graph.findNode(gaphNodeUUid); 
              if (theItem !=  columbus::graph::Graph::invalidNode) {
                allParentsList.insert(theItem);

                std::list<columbus::graph::Edge::EdgeType> list(1,
                  columbus::graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE,columbus::graph::Edge::edtReverse)) ;
                list.push_back(columbus::graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_VARIANT,columbus::graph::Edge::edtReverse));
                getParentTransitve(theItem,list,allParentsList);

                std::list<columbus::graph::Edge::EdgeType> list2(1, columbus::graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT,columbus::graph::Edge::edtDirectional)) ;
                list2.push_back(columbus::graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENTTREE ,columbus::graph::Edge::edtReverse));
                getParentTransitve(theItem,list2,allParentsList);
              }
            }
          }

          std::map<NodeId,std::set<NodeId> >::iterator itLimComponent = limComponentClineInstanceMap.find(ci.getId());
          if (itLimComponent != limComponentClineInstanceMap.end()) {

            if (itLimComponent->second.empty()) {
              common::WriteMsg::write(WriteMsg::mlDebug, "Debug: The ci %d has no component\n", ci.getId());
            }

            for (std::set<NodeId>::iterator itLimComponents = itLimComponent->second.begin();
              itLimComponents != itLimComponent->second.end();++itLimComponents ) {
                NodeId currentComp = *itLimComponents;
                addParentComponents(componentsOfTheClass, currentComp);
                common::WriteMsg::write(WriteMsg::mlDDebug,"Debug: The ci %d is counted to component %d\n " ,ci.getId(), currentComp );
            }


          }

          allCloneClassParentsList.insert(allParentsList.begin(),allParentsList.end());
          if (getIsNeeded("CCO")) {
            cc.setCco(cc.getCco()+ci.getCco());
          }
          for (std::set<columbus::graph::Node>::iterator it = allParentsList.begin();it != allParentsList.end();++it){
            std::list<columbus::graph::Edge::EdgeType> emptyList;
            if (getIsNeeded("CI")) {
              addValue("CI", emptyList, *it, 1, false);
            }
            if (getIsNeeded("CCO")) {
              addValue("CCO", emptyList, *it, ci.getCco(), false);
            }
          }

          // ------ CV and CA---------------------------------------------
          if (!ci.getPrevIsEmpty()) {

            const columbus::genealogy::CloneInstance& prevInstance = (const columbus::genealogy::CloneInstance&)*ci.getPrevListIteratorBegin();
            // check if there were changes in structure
            if ((ci.getEndLine() - ci.getLine()) != ( prevInstance.getEndLine() -  prevInstance.getLine()) || 
              ci.getCco() != prevInstance.getCco()) 
            {
              ci.setCvMetricVariability(prevInstance.getCvMetricVariability() + 1);
            } else
              ci.setCvMetricVariability(prevInstance.getCvMetricVariability());

            ci.setCa(prevInstance.getCa() + 1);
          } else {
            //initialize
            ci.setCvMetricVariability(0);
            ci.setCa(1);
          }

          // CV is computed as the ratio of the number of changes (i.e. if there was a change in structure compared to the previous revision )
          // to the CA of the instance
          ci.setCv((1.0 + ci.getCvMetricVariability()) / ci.getCa());
          //-------------------CE---------------------
          if (getIsNeeded("CE")) {
            unsigned pos = positions[ci.getId()];
            int ce = 0;

            std::set<NodeEmbeddednessVisitorBase::NodeGlobalId> countedUniqueNodes;

            for(unsigned int i = 0; i < length; ++i) {
              const ClonePositioned* position = getNode(pos + i);
              if (position) {
                NodeEmbeddednessVisitorBase::ConectedEdgesMap::iterator itConnectedEdge = conectedEdgesMap.find(NodeEmbeddednessVisitorBase::NodeGlobalId(position->getLimComponentId() ,position->getId()));
                if (itConnectedEdge != conectedEdgesMap.end()) {
                  for (std::list< NodeEmbeddednessVisitorBase::NodeWithWeight >::iterator it = itConnectedEdge->second.begin(); it != itConnectedEdge->second.end();++it) {
                    std::map<NodeEmbeddednessVisitorBase::NodeGlobalId, unsigned int>::iterator itPosCache = positionCache.find((*it).nodeUniqueId);
                    if (itPosCache != positionCache.end()) {
                      bool matter = true;
                      if (!((*it).ndcWeight.multiplicity)) {  // when multiplicity is true, then all occurrences should be calculated for the clone instance.
                        if (countedUniqueNodes.count((*it).nodeUniqueId) == 0){
                          countedUniqueNodes.insert((*it).nodeUniqueId);
                        } else {
                          matter = false;
                        }
                      }

                      if (matter && ((itPosCache->second < pos ) || (itPosCache->second > (pos+length) ) )) {
                        ce+= (*it).ndcWeight.ndc;
                        common::WriteMsg::write(CMSG_INC_CE
                          ,ci.getId()
                          ,(*it).nodeUniqueId.componenetId
                          ,(*it).nodeUniqueId.nodeId
                          ,(*it).ndcWeight.ndc
                          ,(*it).ndcWeight.multiplicity ? CMSG_INC_CE_ALWAYS : CMSG_INC_CE_ONCE );
                      }
                    } else {
                      common::WriteMsg::write( CMSG_NODE_NO_POS_CACHE,it->nodeUniqueId.componenetId, it->nodeUniqueId.nodeId);
                    }
                  }
                }
              }
            }
            ci.setCe(ce);
            cc.setCe(cc.getCe()+ce);
          }
        } // end instance loop


        if (getIsNeeded("CLLOC")) {
          cc.setClloc(((float)avgLocSum) / instances.size());
        }
        // NCR, CE, CV, CR, CEE, CEG
        if (getIsNeeded("NCR")) {

          float radius = 0;
          int numofPair = 0;
          for (unsigned int i=0; i < instances.size(); i++) {
            for (unsigned int j=i+1; j<instances.size();j++) {
              std::string path1=instances[i]->getPath();
              std::string path2=instances[j]->getPath();
              radius += NodeEmbeddednessVisitorBase::calculateNDC(path1,path2);
              numofPair++;
            }
          }

          radius /= numofPair;
          radius /= currentSystemMaxNDC;
          cc.setNcrad(radius) ;

          for (std::set<NodeId>::iterator it = componentsOfTheClass.begin();it != componentsOfTheClass.end();++it){
            componenetMetrics[*it].sumNCR += radius;
            componenetMetrics[*it].numNCR++;
          }

          //componenetMetrics[rootComponenetID].sumNCR += radius;
          //componenetMetrics[rootComponenetID].numNCR++;
        }

        if (getIsNeeded("CE")) {
          cc.setCe(cc.getCe() + 1);
        }

        // ---------------------CV--------------------
        // Clone Class CV: instability of the clone class since it appeared. 
        // It is computed as the ratio of the number of previously analyzed revisions when its clone instances were moved, deleted, or added, 
        // to its age (CA), plus the average CV of its clone instances.

        // check wether there is an istance with a clone smell (suspicious, inconsistently changing code copies)
        int hasSmell = 0;
        for (columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> itemsIter = cc.getItemsListIteratorBegin(); itemsIter != cc.getItemsListIteratorEnd();++itemsIter) {
          if (itemsIter->getCloneSmellType() != columbus::genealogy::cstNone) {
            hasSmell = 1;
            break;
          }
        }
        if (!cc.getPrevIsEmpty()) {
          const columbus::genealogy::CloneClass& prevClass = (const columbus::genealogy::CloneClass&)*cc.getPrevListIteratorBegin();
          cc.setCa(prevClass.getCa() + 1);
          cc.setCvCiSmells(prevClass.getCvCiSmells() + hasSmell);
        } else {
          cc.setCa(1);
          cc.setCvCiSmells(hasSmell);
        }


        if (getIsNeeded("CV")) {
          //compute average CV of clone instances of the given clone class
          double cvsum = 0;
          for (columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> itemsIter=cc.getItemsListIteratorBegin(); itemsIter != cc.getItemsListIteratorEnd(); ++itemsIter) {
            cvsum += itemsIter->getCv();
          }

          cc.setCv(((double)cc.getCvCiSmells()) / cc.getCa() + (cvsum / cc.getInstances()));
        }

        if (getIsNeeded("CR")) {
          // compute CR for clone class
          double cr = cc.getClloc() * getRealNumberCi(cc) * cc.getCco()*cc.getNcrad() * cc.getCv();
          cc.setRisk(cr);

          // compute CR for component
          for (std::set<NodeId>::iterator it = componentsOfTheClass.begin();it != componentsOfTheClass.end();++it){
            componenetMetrics[*it].sumCR += cr;
          }
        }

        if (getIsNeeded("CEE")) {
          // CEE=CI*CE*NCR
          double ceffort = getRealNumberCi(cc) * cc.getCe() *cc.getNcrad();
          cc.setEffort(ceffort);
          for (std::set<NodeId>::iterator it = componentsOfTheClass.begin();it != componentsOfTheClass.end();++it){
            componenetMetrics[*it].CEE += ceffort;
          }
        }

        if (getIsNeeded("CEG")) {
          // CR/CEE
          double celimination_gain = cc.getRisk() / cc.getEffort();
          cc.setGain(celimination_gain);
        }



        for (std::set<columbus::graph::Node>::iterator it = allCloneClassParentsList.begin();it !=allCloneClassParentsList.end();++it) {
          if (getIsNeeded("CCL")) {
            std::list<columbus::graph::Edge::EdgeType> emptyList;
            common::WriteMsg::write(WriteMsg::mlDDebug,"The cc %d is counted to  L%s\n " ,cc.getId(), it->getUID().c_str() );
            addValue("CCL",emptyList , *it, 1, false);
          }
        }

      }//clone class loop
      //CC an CCO metrics end

      // set component metrics - NCR, CR, CEE, CEG
      for (columbus::lim::asg::Factory::const_iterator it = limFact->begin();it != limFact->end();++it) {
        if (columbus::lim::asg::Common::getIsComponent(**it)) {
          std::string gaphSysNodeUUid =  columbus::lim2graph::VisitorGraphConverter::determineNodeName(**it);
          const columbus::lim::asg::base::Component* componentNode 
            = dynamic_cast<const columbus::lim::asg::base::Component*>(*it);
          CollectedMetricsForComponent& collectedMetrics = componenetMetrics[componentNode->getId()];

          if (getIsNeeded("NCR")){
            columbus::graphsupport::setMetricFloat(graph, gaphSysNodeUUid, "NCR", (float)(collectedMetrics.sumNCR/collectedMetrics.numNCR));
          }

          if (getIsNeeded("CR")) {
            columbus::graphsupport::setMetricFloat(graph, gaphSysNodeUUid, "CR", (float)(collectedMetrics.sumCR/ componentNode->getTLLOC()));
          }

          if (getIsNeeded("CEE")) {
            columbus::graphsupport::setMetricFloat(graph, gaphSysNodeUUid, "CEE", (float)collectedMetrics.CEE);
          }
          if (getIsNeeded("CEG")) {
            /* (((1 / (1+  e^(-2*CR/ln(CEE)) )*100)-50)*2) */
            if ((limFact->getRoot()->getTLLOC() > 0) && (collectedMetrics.CEE > std::numeric_limits<double>::epsilon()))
            {
              double componentCR = (double)collectedMetrics.sumCR / limFact->getRoot()->getTLLOC();
              columbus::graphsupport::setMetricFloat(graph, gaphSysNodeUUid, "CEG", (float)(((100.0 / ( 1.0 + exp(-2.0 * componentCR / log(collectedMetrics.CEE)))) - 50.0) * 2.0));
            }
            else
              columbus::graphsupport::setMetricINVALID(graph, gaphSysNodeUUid, "CEG");

          }
        }
      }
      common::WriteMsg::write(CMSG_FINALIZE_DONE_IN, common::getProcessUsedTime().user - time.user);
      config.stat.finalizeTime += common::getProcessUsedTime().user - time.user;
    }

    std::vector<NodeId> DuplicatedCodeMiner::getInstanceIds(const genealogy::CloneInstance& ci) {
      vector<NodeId> instanceRootIds;

      unsigned int length = ci.getRootLength();
      if(length == 1) {
        instanceRootIds.push_back(ci.getRootBegin());
      } else {
        stringstream inputStreamOfInstances(ci.getRootNodes());
        char buffer [11]  = "0x00000000";
        while (inputStreamOfInstances.get(buffer+2,9)) {
          std::istringstream in(buffer);
          NodeId nodeid ;
          in >>std::hex >>nodeid;
          instanceRootIds.push_back(nodeid);
        }
      }
      return instanceRootIds;
    }

    void DuplicatedCodeMiner::serializeAsg(Factory& factory, NodeId componentLimId, std::vector<int>& nodeKindSequence, std::vector<ClonePositioned*>& nodeIdSequence, int& decDepthSign, columbus::lim::asg::Factory*  _limFact) {

      CloneVisitorBase* cloneVisitor = new CloneVisitorBase(visitedLines, visitedLimNodes,limOrigin ,nodeKindSequence, nodeIdSequence, CloneVisitorBase::schemaOnly, config.ofc, false, _limFact);

      cloneVisitor->setFactory(&factory, componentLimId);
      //  factory.turnFilterOff(); // the lim filter is the valid. 
      WriteMsg::write(CMSG_LOAD_ASG_DONE);
      updateMemoryStat();
      nodeKindSequence.clear();
      clearNodeIdSequence(nodeIdSequence);

      traversalPosiotionedNodes(factory, cloneVisitor,"");

      decDepthSign = cloneVisitor->getDecDepthSign();
      delete cloneVisitor;
    }

    int DuplicatedCodeMiner::serializeAsg(bool createComponent)
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("serializeAsg()");

      common::timestat serializeTime = common::getProcessUsedTime();
      int exit_code = EXIT_SUCCESS;

      nodeKindSequence.clear();
      clearNodeIdSequence(nodeIdSequence);
      visitedLimNodes.clear();
      visitedLines.clear();

      delete theCloneVisitor;
      theCloneVisitor=new CloneVisitorBase(visitedLines,visitedLimNodes, limOrigin,nodeKindSequence, nodeIdSequence, CloneVisitorBase::schemaOnly, config.ofc, false, limFact);
      theCloneVisitor->setOutputStream(*filterOut);

      if (createComponent) {
        theCloneVisitor->setLogicalLines(&logicalLines);
        theCloneVisitor->setFileNamesByComponent(&fileNamesByComponent);
      } else {
        theCloneVisitor->setLogicalLines(NULL);
        theCloneVisitor->setFileNamesByComponent(NULL);
      }

      std::list<std::string>::const_iterator bp_iter=config.bpaths.begin();
      while (bp_iter!=config.bpaths.end()) {
        theCloneVisitor->addBlockPath((*bp_iter++));
      }
      float numberOfComponents = config.files.size();
      int componentCounter = 0;
      for  (std::list<std::string>::iterator fileIter=config.files.begin();fileIter!=config.files.end();fileIter++)
      {
        ++componentCounter;
        std::string fname=(*fileIter);
        std::string componenetID;
        common::WriteMsg::write(CMSG_LOADING_AND_PERCENTAGE, componentCounter / numberOfComponents, fname.c_str());
        try {
          currentFactory.loadComponent(fname,false,NULL,&componenetID);
          perfSectionHandler.addTimeStamp("loadComponent");
          if(createComponent) {
            // create component to genealogy
            columbus::genealogy::Component* componentRef=genealogyFact->createComponentNode();
            componentRef->setLocation(fname);
            componentRef->setName(componenetID);
            currentSystem->addComponents(componentRef);
            //calculate hash
            std::size_t hash = currentFactory.calculateHash(currentFactory.operator ()(fname), fname);
            perfSectionHandler.addTimeStamp("calculateHash");
            componentRef->setCode(hash);
          }
        } catch(columbus::Exception& e) {
          common::WriteMsg::write(CMSG_SIMPLE_STRING_TRANSMIT_ERR,e.getMessage().c_str());
          fileIter=config.files.erase(fileIter);
          exit_code = EXIT_FAILURE;
          continue;
        } catch(...) {
          common::WriteMsg::write(CMSG_FAILED_OPEN_FILE,fname.c_str());
          fileIter=config.files.erase(fileIter);
          exit_code = EXIT_FAILURE;
          continue;
        }

        theCloneVisitor->setFactory(currentFactory.operator ()(fname), getLimComponenetIdByName( componenetID,*limFact) );
        // find filter
        std::map<std::string, std::set<columbus::NodeId> >::iterator it = filteredNodes.find(componenetID);
        if(it != filteredNodes.end()) {
          theCloneVisitor->setFilter(it->second);
        } else {
          theCloneVisitor->clearFilter();
        }
        common::timestat time = common::getProcessUsedTime();
        common::WriteMsg::write(CMSG_CLONE_VISITOR_RUNNING);
        theCloneVisitor->resetVisitedNodesNumber();

        WriteMsg::write(CMSG_LOAD_ASG_DONE);
        updateMemoryStat();

        traversalPosiotionedNodes( (*currentFactory.operator ()(fname)),theCloneVisitor, componenetID); //main serialize method for other languages
        perfSectionHandler.addTimeStamp("traversalPosiotionedNodes");
        common::WriteMsg::write(CMSG_DONE_D);

        serializedAsgNodeNumberByComponenet[fname] = theCloneVisitor->getVisitedNodesNumber();


        common::WriteMsg::write(CMSG_DONE_IN, common::getProcessUsedTime().user - time.user );
        updateMemoryStat();
        currentFactory.release();
        common::WriteMsg::write(CMSG_DONE_D);
      }

      config.stat.asgSerializationTime += common::getProcessUsedTime().user - serializeTime.user;

      return exit_code;
    }

    int DuplicatedCodeMiner::dcminer(int maxCCSize, const std::string& backup) {
      bool errorAtLoad = false;

      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("dcminer()");

      //creating the genealogy graph
      genealogy::Project& genealogyBase = initGenealogy(errorAtLoad);
      updateMemoryStat();
      set<string> needToSkip;

      theCloneVisitor = NULL;
      COVERAGE_VISITOR* coverageVisitor=NULL;

      bool first=false;
      int exit_code = EXIT_SUCCESS;

      if (!initLim()) {
        return EXIT_FAILURE;
      }
      updateMemoryStat();
      
      do {
        // first we need to reset the state of the objects below (in case that DCF is being executed for the second time)
        first=!first;

        needToSkip.clear();
        coveredNodes.clear();
        coveredLines.clear();
        cloneClassMap.clear();

        genealogyFact->enableReverseEdges();
        int age = currentSystem->getAge();
        genealogyFact->destroyNode(currentSystem->getId());
        currentSystem = createSystem();

        currentSystem->setAge(age);
        updateMemoryStat();
        
        limFact->turnFilterOn();
        
        exit_code = serializeAsg(true);

        config.stat.serializedASGLength = nodeIdSequence.size();
        /**
        * The language-independent clone-detection algorithm
        */
        detectClones(coveredNodes, maxCCSize, needToSkip);
        updateMemoryStat();

        if (maxCCSize) {
          for (set<string>::const_iterator it = needToSkip.begin(); it != needToSkip.end(); ++it){
            if ((*it).empty()) continue;
            common::WriteMsg::write(CMSG_ADDING_PATH_TO_FILTER, (*it).c_str());
            config.bpaths.push_back(*it);
          }
        }
      } while (maxCCSize && needToSkip.size()>0 && first);

      common::timestat time = common::getProcessUsedTime();
     
      updateMemoryStat();
      WriteMsg::write(CMSG_CONVERTING_TO_GRAPH);
      TOGRAPH::convertBaseGraph(*limFact, graph, true, true, /*components=*/ true, /*variants=*/ true);
      updateMemoryStat();
      columbus::graph::Node cloneRootNode = graph.createNode(graphsupport::graphconstants::UID_CLONE_ROOT, columbus::graph::Node::NodeType(graphsupport::graphconstants::NTYPE_ROOT));
      graphsupport::addNodeNameAttribute(graph, cloneRootNode,graphsupport::graphconstants::UID_CLONE_ROOT);
      graphsupport::addNodeLongNameAttribute(graph, cloneRootNode,graphsupport::graphconstants::UID_CLONE_ROOT);

      if (config.metrics) {
        //CE metric
        if (coverageVisitor != NULL){
          delete coverageVisitor;
        }

        coverageVisitor = new COVERAGE_VISITOR();

        computeCoverage(coverageVisitor, coveredNodes);
        perfSectionHandler.addTimeStamp("computeCoverage");

        //compute connected edges
        NODE_EMBEDDEDNESS_VISITOR visitor(conectedEdgesMap,*this);

        for (std::map<std::string, std::set<NodeId> >::iterator itCoverages = coveredNodes.begin();itCoverages != coveredNodes.end();++itCoverages) {
          currentFactory.loadComponentByComponentID(itCoverages->first);
          LANGUAGE_NS::asg::Factory& factory = *currentFactory.getByComponentID(itCoverages->first);
          factory.getReverseEdges();
          factory.turnFilterOff();
          visitor.LimComponenetId(getLimComponenetIdByName(itCoverages->first,*limFact)); //set the current lim component id in the visitor based on current covered node

          for (std::set<NodeId>::iterator itNodes = itCoverages->second.begin(); itNodes != itCoverages->second.end();++itNodes) {
            //visit nodes
            (factory.getRef(*itNodes)).accept(visitor);
          }
          currentFactory.release();
        }

        updateMemoryStat();
        WriteMsg::write(CMSG_BUILD_CE);
        
        for  (std::list<std::string>::iterator fileIter=config.files.begin();fileIter!=config.files.end();++fileIter) {
          std::string componenetID;
          currentFactory.loadComponent(*fileIter,false,NULL,&componenetID);
          LANGUAGE_NS::asg::Factory& factory = *currentFactory(*fileIter);
          visitor.LimComponenetId(getLimComponenetIdByName(componenetID,*limFact));

          for (LANGUAGE_NS::asg::Factory::const_iterator it = factory.begin(); it != factory.end();++it) {
            if (LANGUAGE_NS::asg::Common::getIsPositioned(**it)) {
              NodeId limNode =  getLimNodeIdByNode(visitor.LimComponenetId(),**it);
              if (limNode ) {
                NODE_EMBEDDEDNESS_VISITOR::NodeAliasMap::iterator itLimNode = visitor.aliasMap.find(limNode) ;

                if (( itLimNode != visitor.aliasMap.end() )&&  (*itLimNode).second.componenetId  != visitor.LimComponenetId()) {
                  visitor.setAlias((*itLimNode).second);
                  (*it)->accept( visitor);
                }
              }
            }
          }
          currentFactory.release();
        }
      } //if config.metrics

      updateMemoryStat();

      delete theCloneVisitor;
      theCloneVisitor = NULL;
      nodeKindSequence.clear();
      currentFactory.release();

      config.stat.calculateMetricsTime += common::getProcessUsedTime().user - time.user;

      //generating evolution mapping
      if(!errorAtLoad) {
        evolutionMapping(*currentSystem, genealogyBase);
      }

      setClonesUniqueName();

      //updating paths;
      createBackup(backup);


      /**
      * The ASGs will be loaded again...anyway we need to compute the coverage
      */

      time = common::getProcessUsedTime();

      // turn on graph indexer and build  index
      indexer = &columbus::graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance();
      indexer->turnOn(graph);
      currentFactory.release();

      if (getIsNeeded("CC")) {
        if(coverageVisitor) {
          coverageVisitor->fillCoverage(coverage);
        }
      }
      delete coverageVisitor;

      visitedLimNodes.clear();
      for (CoverageVisitorBase::CCMap::iterator  it = coverage.begin();it !=coverage.end();++it){
        visitedLimNodes.insert(it->first.limNodeId);
      }

      finalize();
      perfSectionHandler.addTimeStamp("finalize");
      build_clones_tree();
      perfSectionHandler.addTimeStamp("build_clones_tree");
      clearNodeIdSequence(nodeIdSequence);
      config.stat.calculateMetricsTime += common::getProcessUsedTime().user - time.user;

      return exit_code;
    }

    columbus::genealogy::System* DuplicatedCodeMiner::createSystem() {
      columbus::genealogy::System* system= genealogyFact->createSystemNode();
      system->setName(config.systemName);
      system->setVersion(config.systemVersion);
      system->setLimFileLocation(config.limFileName);
      system->setAge(1);
      genealogyFact->getRoot()->addSystems(system->getId());
      return system;
    }

    columbus::genealogy::Project& DuplicatedCodeMiner::initGenealogy(bool& errorAtLoad) {
      common::WriteMsg::write(CMSG_INITIALIZING_GENEALOGY);

      errorAtLoad = false;

      strTable = new RefDistributorStrTable();
      genealogyFact = new columbus::genealogy::Factory(*strTable);

      if (!config.genealogyFilename.empty()) {
        boost::filesystem::path genealogyFile(config.genealogyFilename);
        try {
          if (boost::filesystem::exists(genealogyFile)) {
            columbus::CsiHeader header;
            genealogyFact->load(config.genealogyFilename, header);
            // We should replace the string table to reset the internal bucket counters due to the enormous amount of delete operations
            columbus::RefDistributorStrTable* newStrTable = new RefDistributorStrTable();
            genealogyFact->swapStringTable(*newStrTable);
            delete strTable;
            strTable = newStrTable;
          }
        } catch (columbus::genealogy::GenealogyException& e) {
          common::WriteMsg::write(CMSG_GENALOGY_WILL_NOT_BE_SAVED, e.toString().c_str());
          errorAtLoad = true;
        }
      }

      if(errorAtLoad) {
        delete genealogyFact;
        delete strTable;
        strTable = new RefDistributorStrTable();
        genealogyFact = new columbus::genealogy::Factory(*strTable);
      }

      columbus::genealogy::Project& genealogyBase= *genealogyFact->getRoot();

      for ( columbus::genealogy::ListIterator<columbus::genealogy::System> systemsIterator=genealogyBase.getSystemsListIteratorBegin(); systemsIterator !=genealogyBase.getSystemsListIteratorEnd(); ++systemsIterator) {
        lastSystem = &*systemsIterator;
      }

      currentSystem = createSystem();
      if ( lastSystem ) {
        currentSystem->setPrev(lastSystem->getId());
        currentSystem->setAge(lastSystem->getAge()+1);
      } else {
        currentSystem->setAge(1);
      }

      common::WriteMsg::write(CMSG_DONE_D);
      return genealogyBase;
    }

    void DuplicatedCodeMiner::evolutionMapping(columbus::genealogy::System& systemRef, columbus::genealogy::Project& genealogyBase) {
#ifdef GENEALOGY
      // load back asg for evolution mapping
      common::timestat time = common::getProcessUsedTime();

      common::WriteMsg::write(CMSG_START_EVOLUTION_MAPPING);
      common::WriteMsg::write(CMSG_START_EVOLUTION_MAPPING_SYSTEM_SET("2")); 
      updateMemoryStat();


      vector<genealogy::CloneInstance*> instancesOfTheCurrentSystem = getInstancesOfaSystem(systemRef);
      unsigned numberOfInstancesInTheRefSystem = instancesOfTheCurrentSystem.size();

      std::sort(instancesOfTheCurrentSystem.begin(), instancesOfTheCurrentSystem.end(), sortCloneInstancesByComponentId());
      unsigned int prev = 0;

      // calculate the similarity attributes for all instances
      for (vector<genealogy::CloneInstance*>::iterator currentInsatnceIt = instancesOfTheCurrentSystem.begin(); currentInsatnceIt != instancesOfTheCurrentSystem.end();++currentInsatnceIt) {
        genealogy::CloneInstance* instanceOfTheCurentSystem = *currentInsatnceIt;
        if(prev != instanceOfTheCurentSystem->getComponent()->getId()) {
          prev = instanceOfTheCurentSystem->getComponent()->getId();
          currentFactory.release();
          currentFactory.loadComponent(instanceOfTheCurentSystem->getComponent()->getLocation(),true);
          updateMemoryStat();
        }
        computeSimilarityAttributes(*instanceOfTheCurentSystem);
      }
      currentFactory.release();

      updateMemoryStat();
      if (lastSystem) {
        currentSystem->setPrev(lastSystem->getId());
        ((columbus::genealogy::System*)lastSystem)->setNext(currentSystem->getId());

        vector<genealogy::CloneInstance*> instancesOfTheLastSystem = getInstancesOfaSystem(*lastSystem);
        unsigned numberOfInstancesInTheLastSystem = instancesOfTheLastSystem.size();
        config.stat.numberOfInstancesInTheLastSystem = numberOfInstancesInTheLastSystem;

        for (vector<genealogy::CloneInstance*>::iterator currentInsatnceIt = instancesOfTheCurrentSystem.begin(); currentInsatnceIt != instancesOfTheCurrentSystem.end();++currentInsatnceIt) {
          genealogy::CloneInstance* instanceOfTheCurentSystem = *currentInsatnceIt;

          if (!instanceOfTheCurentSystem->getPrevIsEmpty() || instanceOfTheCurentSystem->getIsVirtual())
            continue;

          for (vector<genealogy::CloneInstance*>::iterator prevInsatnceIt = instancesOfTheLastSystem.begin(); prevInsatnceIt != instancesOfTheLastSystem.end();++prevInsatnceIt) {
            genealogy::CloneInstance* instanceOfTheLastSystem = *prevInsatnceIt;

            if (!instanceOfTheLastSystem->getNextIsEmpty() || instanceOfTheLastSystem->getIsVirtual())
              continue;

            double sim=similarity(*instanceOfTheLastSystem, *instanceOfTheCurentSystem);
            common::WriteMsg::write(WriteMsg::mlDDDDebug, "Similarity of %d(last) and %d(current): %f", instanceOfTheLastSystem->getId(), instanceOfTheCurentSystem->getId(), sim);
            if (sim==0.0) {
              instanceOfTheLastSystem->addNext(instanceOfTheCurentSystem);
              instanceOfTheCurentSystem->addPrev(instanceOfTheLastSystem);
              trivial_pairs++;
              break;
            }
          }
        }

        config.stat.numberOfTrivialPairs = trivial_pairs;
        try{
          boost::numeric::ublas::matrix<double> m(numberOfInstancesInTheLastSystem - trivial_pairs, numberOfInstancesInTheRefSystem - trivial_pairs);

          for (unsigned int q1=0; q1<m.size1(); q1++) {
            for (unsigned int q2=0; q2<m.size2(); q2++) {
              m(q1,q2)=std::numeric_limits<double>::infinity();
            }
          }

          updateMemoryStat();

          unsigned int row=0;
          unsigned int col=0;
          typedef boost::bimap<unsigned int, columbus::genealogy::CloneInstance*> IntCloneInstanceBimap;
          typedef std::map<unsigned int, columbus::genealogy::CloneInstance*> IntCloneInstanceMap;

          IntCloneInstanceMap row_map;
          IntCloneInstanceBimap col_map;

          for (vector<genealogy::CloneInstance*>::iterator prevInsatnceIt = instancesOfTheLastSystem.begin(); prevInsatnceIt != instancesOfTheLastSystem.end();++prevInsatnceIt) {
            genealogy::CloneInstance* instanceOfTheLastSystem = *prevInsatnceIt;    

            if (!instanceOfTheLastSystem->getNextIsEmpty() || instanceOfTheLastSystem->getIsVirtual())
              continue;

            row_map.insert(IntCloneInstanceMap::value_type(row, instanceOfTheLastSystem));

            for (vector<genealogy::CloneInstance*>::iterator currentInsatnceIt = instancesOfTheCurrentSystem.begin(); currentInsatnceIt != instancesOfTheCurrentSystem.end();++currentInsatnceIt) {
              genealogy::CloneInstance* instanceOfTheCurentSystem = *currentInsatnceIt;

              if (!instanceOfTheCurentSystem->getPrevIsEmpty() || instanceOfTheCurentSystem->getIsVirtual())
                continue;

              IntCloneInstanceBimap::right_iterator leftIter=col_map.right.find(instanceOfTheCurentSystem);
              unsigned int mycol = 0;
              if (leftIter != col_map.right.end())
                mycol = leftIter->second;
              else {
                col_map.insert(IntCloneInstanceBimap::value_type(col, instanceOfTheCurentSystem));
                mycol = col;
                col++;
              }
              double sim = similarity(*instanceOfTheLastSystem, *instanceOfTheCurentSystem);  // Ez mar egyszer ki lett szamolva! Lehet el kellene tarolni es nem megegyszer kiszamolni.
              m(row, mycol) = sim;
            }
            row++;
          }

          updateMemoryStat();
          boost::numeric::ublas::matrix<double> m_orig(m);
          
          common::math::HungarianMethod<std::string, double> Hm(m_orig);
          std::map<unsigned int, unsigned int> solution=Hm.solve(common::math::HungarianMethod<std::string, double>::INJECTIVE_KIND);
          std::map<unsigned int, unsigned int>::iterator sol_iter=solution.begin();
          unsigned int nontrivial_maps=0;
          double overall_similarity=0.0;
          while (sol_iter!=solution.end()) {
            unsigned int second=(*sol_iter).first;
            unsigned int first=(*sol_iter).second;
            sol_iter++;
            if (first>=m.size1() || second>=m.size2() || m(first,second)==numeric_limits<double>::infinity())
              continue;
            IntCloneInstanceMap::iterator iter1;
            if ((iter1=row_map.find(first))==row_map.end())
              continue;
            IntCloneInstanceBimap::left_iterator iter2;
            if ((iter2=col_map.left.find(second))==col_map.left.end())
              continue;
            (*iter1).second->addNext((*iter2).second->getId());
            (*iter2).second->addPrev((*iter1).second->getId());
            nontrivial_maps++;
            overall_similarity+=m(first, second);
          }
        }catch (std::bad_alloc&) {
          common::WriteMsg::write(CMSG_NOT_ENOUGH_MEMORY_TO_EVOLUTE);
        }
        // connecting clone classes

        // connect by fingerprints
        std::map<columbus::Key, genealogy::CloneClass*> prevFingerprints;
        for (columbus::genealogy::ListIterator<columbus::genealogy::CloneClass> it = lastSystem->getCloneClassesListIteratorBegin(); it != lastSystem->getCloneClassesListIteratorEnd();++it ) {
          columbus::genealogy::CloneClass& classItem = const_cast<columbus::genealogy::CloneClass&>(*it);

          if(classItem.getIsVirtual())
            continue;

          prevFingerprints.insert(make_pair(classItem.getFingerprintKey(), &classItem));
        }

        for (columbus::genealogy::ListIterator<columbus::genealogy::CloneClass> it = currentSystem->getCloneClassesListIteratorBegin();  it != currentSystem->getCloneClassesListIteratorEnd();++it ) {
          columbus::genealogy::CloneClass& classItem = const_cast<columbus::genealogy::CloneClass&>(*it);

          if(classItem.getIsVirtual())
            continue;

          std::map<columbus::Key, genealogy::CloneClass*>::const_iterator fpIt = prevFingerprints.find(classItem.getFingerprintKey());
          if (fpIt != prevFingerprints.end()) {
            columbus::genealogy::CloneClass& candClass = *fpIt->second;
            if (classItem.getPrevIsEmpty() && candClass.getNextIsEmpty()) {
              classItem.addPrev(candClass.getId());
              candClass.addNext(classItem.getId());
            }
          }
        }

        // connect by instances
        columbus::genealogy::System& lastSystemRef=(columbus::genealogy::System&)*currentSystem;

        for (columbus::genealogy::ListIterator<columbus::genealogy::CloneClass> groupIter=lastSystemRef.getCloneClassesListIteratorBegin();groupIter!=lastSystemRef.getCloneClassesListIteratorEnd();++groupIter) {
          columbus::genealogy::CloneClass& classItem= const_cast<columbus::genealogy::CloneClass&>(*groupIter);

          //Virtual Node-ok miatt javitva.
          if (!classItem.getPrevIsEmpty() || classItem.getIsVirtual())
            continue;

          std::map<columbus::NodeId, unsigned int> countMap;
          for(columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> itemsIter=classItem.getItemsListIteratorBegin();itemsIter!=classItem.getItemsListIteratorEnd();++itemsIter) {
            columbus::genealogy::CloneInstance& itm= const_cast<columbus::genealogy::CloneInstance&>(*itemsIter);
            //Virtual Node-ok miatt javitva.
            if(itm.getIsVirtual())
              continue;


            for(columbus::genealogy::ListIterator<columbus::genealogy::Trackable> prevIt = itm.getPrevListIteratorBegin();prevIt != itm.getPrevListIteratorEnd();++prevIt) {
              columbus::NodeId prev=prevIt->getId();
              if (genealogyFact->getExist(prev)) {
                columbus::genealogy::CloneInstance& prevRef=(columbus::genealogy::CloneInstance&)genealogyFact->getRef(prev);
                columbus::NodeId groupId=prevRef.getCloneClass()->getId();
                if(groupId != 0){
                  std::map<columbus::NodeId, unsigned int>::iterator iter=countMap.find(groupId);
                  if (iter==countMap.end()) {
                    countMap.insert(std::map<columbus::NodeId, unsigned int>::value_type(groupId, 1));
                  } else
                    (*iter).second++;
                }
              }
            }
          }


          std::map<columbus::NodeId, unsigned int>::iterator iter=countMap.begin();
          columbus::NodeId maxId=0;
          unsigned int maxValue=0;
          while (iter!=countMap.end()) {
            unsigned int currentValue=(*iter).second;
            if (currentValue>maxValue) {
              maxValue=currentValue;
              maxId=(*iter).first;
            }
            iter++;
          }
          if (maxValue>0) {
            columbus::genealogy::CloneClass& candClass=(columbus::genealogy::CloneClass&)genealogyFact->getRef(maxId);
            if (maxValue>classItem.getItemsSize()/2 && maxValue>candClass.getItemsSize()/2) {
              //connecting the classes
              if (classItem.getPrevIsEmpty() && candClass.getNextIsEmpty()) {
                classItem.addPrev(candClass.getId());
                candClass.addNext(classItem.getId());
              }
            }
          }
        }

        for(std::map<std::string, SerializedAsg>::iterator serializedAsgMapIt = serializedAsgMap.begin(); serializedAsgMapIt != serializedAsgMap.end(); ++serializedAsgMapIt) {
          clearNodeIdSequence(serializedAsgMapIt->second.nodeIdSequence);
        }
        serializedAsgMap.clear();
        common::WriteMsg::write(CMSG_DONE_D);

      }

      updateMemoryStat();

      config.stat.evolutionMappingTime = common::getProcessUsedTime().user - time.user;
#endif
    }

    void DuplicatedCodeMiner::setClonesUniqueName() {
      common::WriteMsg::write(CMSG_START_CLONE_NAMING);

      unsigned uniqueId = 0;
      if (lastSystem != NULL)
        uniqueId = lastSystem->getFirstFreeID();

      columbus::genealogy::System& currentSystemRef=*currentSystem;
      for (columbus::genealogy::ListIterator<genealogy::CloneClass> classItemsIter = currentSystemRef.getCloneClassesListIteratorBegin(); classItemsIter != currentSystemRef.getCloneClassesListIteratorEnd(); ++classItemsIter ) {
        columbus::genealogy::CloneClass& classItem=const_cast<columbus::genealogy::CloneClass&>(*classItemsIter);
        if (classItem.getIsVirtual())
          continue;
        const columbus::genealogy::CloneClass* prevClass= &classItem;

        if (!classItem.getPrevIsEmpty()) {
          columbus::genealogy::ListIterator<columbus::genealogy::Trackable> prevIter = classItem.getPrevListIteratorEnd() ;
          --prevIter;
          prevClass=  dynamic_cast<const columbus::genealogy::CloneClass*>(&(*prevIter));
        }

        //if the clone class is new 
        if (prevClass==&classItem) {
          std::string id=boost::lexical_cast<std::string>(uniqueId++);
          classItem.setUniqueName(id+"~CloneClass");

          if (currentSystemRef.getAge() > 1) {
            classItem.setCloneSmellType(columbus::genealogy::cstAppearing);
          }
        } else {
          classItem.setUniqueName(prevClass->getUniqueName());
          for(columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> itemsIter=prevClass->getItemsListIteratorBegin();itemsIter!=prevClass->getItemsListIteratorEnd();++itemsIter) {
            columbus::genealogy::CloneInstance& itm= const_cast<columbus::genealogy::CloneInstance&>(*itemsIter);
            if (itemsIter->getNextSize() == 0 && !itm.getIsVirtual()) {
              columbus::genealogy::CloneInstance* cloneInstanceNext = itm.getFactory().createCloneInstanceNode();
              classItem.addItems(cloneInstanceNext);
              cloneInstanceNext->setCloneClass(&classItem);
              cloneInstanceNext->setIsVirtual(true);
              cloneInstanceNext->setUniqueNameKey(itm.getUniqueNameKey());
              cloneInstanceNext->setCloneSmellType(columbus::genealogy::cstDisappearing);
              cloneInstanceNext->addPrev(itm.getId());
              cloneInstanceNext->setPath(itm.getPath());
              cloneInstanceNext->setLine(itm.getLine());
              cloneInstanceNext->setEndLine(itm.getEndLine());
              cloneInstanceNext->setCol(itm.getCol());
              cloneInstanceNext->setEndCol(itm.getEndCol());

              itm.addNext(cloneInstanceNext);
            } 
          }
        }

        for (columbus::genealogy::ListIterator<genealogy::CloneInstance> itemsIter = classItemsIter->getItemsListIteratorBegin(); itemsIter!=classItemsIter->getItemsListIteratorEnd();++itemsIter) {
          columbus::genealogy::CloneInstance& instance=const_cast<columbus::genealogy::CloneInstance&>(*itemsIter);
          if (instance.getPrevIsEmpty()) {
            std::string id=boost::lexical_cast<std::string>(uniqueId++);
            instance.setUniqueName(id+"~CloneInstance");
            if (!instance.getCloneClass()->getPrevIsEmpty()) { 
              instance.setCloneSmellType(columbus::genealogy::cstAppearing);
            }
          } else {
            if (!instance.getIsVirtual()) {
              const columbus::genealogy::CloneInstance& prev = dynamic_cast<const columbus::genealogy::CloneInstance&>(*instance.getPrevListIteratorBegin());
              instance.setUniqueNameKey(prev.getUniqueNameKey());
              if (prev.getCloneClass()->getUniqueNameKey() == instance.getCloneClass()->getUniqueNameKey()) {
                instance.setCloneSmellType(columbus::genealogy::cstNone);
              } else {
                if (prev.getCloneClass()->getNextSize() > 0 ) {
                  instance.setCloneSmellType(columbus::genealogy::cstMoving);
                } else {
                  instance.setCloneSmellType(columbus::genealogy::cstNone);
                }
              }
            }
          }
        }
      }


      // build virtual clone class
      if (currentSystem->getPrev()) {
        columbus::genealogy::System& pervSystemRef= (columbus::genealogy::System&)*currentSystem->getPrev();

        for ( columbus::genealogy::ListIterator<genealogy::CloneClass> groupIter=pervSystemRef.getCloneClassesListIteratorBegin(); groupIter!=pervSystemRef.getCloneClassesListIteratorEnd();++groupIter) {
          columbus::genealogy::CloneClass& classItem=const_cast<columbus::genealogy::CloneClass&>(*groupIter);
          if (classItem.getIsVirtual())
            continue;

          if (groupIter->getNextIsEmpty()) {
            columbus::genealogy::CloneClass* cloneClassVirtual = classItem.getFactory().createCloneClassNode();
            currentSystem->addCloneClasses(cloneClassVirtual);
            cloneClassVirtual->setUniqueNameKey(classItem.getUniqueNameKey());
            cloneClassVirtual->setIsVirtual(true);
            cloneClassVirtual->setCloneSmellType(columbus::genealogy::cstDisappearing);

            for(columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> itemsIter=classItem.getItemsListIteratorBegin();itemsIter!=classItem.getItemsListIteratorEnd();++itemsIter) {
              columbus::genealogy::CloneInstance& itm= const_cast<columbus::genealogy::CloneInstance&>(*itemsIter);

              if (itm.getNextIsEmpty()) {
                columbus::genealogy::CloneInstance* cloneInstanceNext = itm.getFactory().createCloneInstanceNode();
                cloneClassVirtual->addItems(cloneInstanceNext);
                cloneInstanceNext->setCloneClass(&classItem);
                cloneInstanceNext->setIsVirtual(true);
                cloneInstanceNext->setUniqueNameKey(itm.getUniqueNameKey());
                cloneInstanceNext->setCloneSmellType(columbus::genealogy::cstNone);
                cloneInstanceNext->addPrev(itm.getId());
                cloneInstanceNext->setPath(itm.getPath());
                cloneInstanceNext->setLine(itm.getLine());
                cloneInstanceNext->setEndLine(itm.getEndLine());
                cloneInstanceNext->setCol(itm.getCol());
                cloneInstanceNext->setEndCol(itm.getEndCol());

                itm.addNext(cloneInstanceNext);
              }
            }
          }
        }
      }
      currentSystem->setFirstFreeID(uniqueId);
      common::WriteMsg::write(CMSG_DONE_D);
    }

    void DuplicatedCodeMiner::computeCoverage(COVERAGE_VISITOR* coverageVisitor, std::map<std::string, std::set<NodeId> >& coveredNodes) {
      if (!theCloneVisitor)
        return;

      common::WriteMsg::write(CMSG_COMPUTING_COVERAGE_AND_GENERATE_GRAPH_FORM_LIM);
      std::string asg;

      for (unsigned long l=0; l < nodeIdSequence.size(); l++) {
        ClonePositioned* px=nodeIdSequence[l];
        if (px==NULL) {
          continue;
        }

        if (px->getLimComponentId() != 0) {
          std::string newASg=getAsgNameByLimId(px->getLimComponentId(),*limFact);
          if (newASg!=asg) {
            currentFactory.release();
            currentFactory.loadComponentByComponentID(newASg);
            coverageVisitor->setFactory(limFact, newASg, coveredNodes);
            asg = newASg;
            calculateCOOForLangASG (px->getLimComponentId(), newASg);
          }

          Base& node=currentFactory.getByComponentID(newASg)->getRef(px->getId());
          coverageVisitor->setLimNodeId(px->getLimNodeId());
          coverageVisitor->acceptNode(node);
        }
      }
      common::WriteMsg::write(CMSG_COMPUTING_COVERAGE_DONE);
    }

    void DuplicatedCodeMiner::createBackup(const std::string& backup) {
#ifdef GENEALOGY
      if ( !backup.empty() ) {
        common::WriteMsg::write(CMSG_CREATE_BACKUP);
        std::wstring backupW;
        backupW.assign(backup.begin(),backup.end());
        boost::filesystem::path to_dir(backupW);

        if (!to_dir.is_complete()) {
          to_dir = (boost::filesystem::current_path() / to_dir );
        }

        if (!boost::filesystem::exists(to_dir))
          boost::filesystem::create_directories(to_dir);

        for(columbus::genealogy::ListIterator<columbus::genealogy::Component> cIter = currentSystem->getComponentsListIteratorBegin();cIter != currentSystem->getComponentsListIteratorEnd();++cIter) {
          const columbus::genealogy::Base& component=*cIter;
          columbus::genealogy::Component& cmp=(columbus::genealogy::Component&)component;
          boost::filesystem::path p(cmp.getLocation());
          boost::filesystem::path newfile;

          if (p.is_complete())
            newfile=to_dir/p.relative_path();
          else
            newfile=to_dir/(boost::filesystem::current_path()/p).relative_path();


          newfile.normalize();
          newfile.make_preferred();

          newfile = LONGDIRPREFIXSTRING + newfile.wstring();

          boost::filesystem::remove(newfile);
          boost::filesystem::create_directories(boost::filesystem::path(newfile).remove_leaf());
          boost::filesystem::copy_file(p,newfile);
          cmp.setLocation(newfile.string());
          p=boost::filesystem::change_extension(p, FILTER_FILE_EXTENSION_W);
          newfile=boost::filesystem::change_extension(newfile, FILTER_FILE_EXTENSION_W);
          boost::filesystem::remove(newfile);
          if (boost::filesystem::exists(p))
            boost::filesystem::copy_file(p,newfile);
        }
        common::WriteMsg::write(CMSG_DONE_D);
      }
#endif
    }

    void DuplicatedCodeMiner::saveGenealogy() {
#ifdef GENEALOGY

      if (!config.genealogyFilename.empty()){

        if (config.smallGenealogy) {
          // Remove the last system
          if (lastSystem != NULL) {
            genealogyFact->destroyNode(lastSystem->getId());
          }
        }

        if ( dumpGraphml)
        {
          genealogy::AlgorithmPreorder pre;
          pre.setFactory( *genealogyFact);
          pre.setSafeMode();
          io::GraphmlIO ioToDumpGraphml((config.genealogyFilename+ ".graphml").c_str(), "");
          std::set<std::string> tmpSet;
          genealogy::VisitorGraphml visitorToDumpGraphml(ioToDumpGraphml, tmpSet);
          pre.addVisitor(visitorToDumpGraphml);
          pre.run();
        }
        common::WriteMsg::write(CMSG_SAVE_GENEALOGY);
        columbus::CsiHeader header;
        genealogyFact->save(config.genealogyFilename, header);
        common::WriteMsg::write(CMSG_DONE_D);
      }
#endif
    }

    bool DuplicatedCodeMiner::isASGNode(unsigned int sequencePosition) const {
      return (nodeIdSequence.at(sequencePosition)!=NULL);
    }

    const ClonePositioned* DuplicatedCodeMiner::getNode(unsigned int sequencePosition) const {
      return nodeIdSequence.at(sequencePosition);
    }

    bool DuplicatedCodeMiner::containsInstanceAtPositon(unsigned int position, const genealogy::CloneClass& cc) {
      for(genealogy::ListIterator<genealogy::CloneInstance> instances = cc.getItemsListIteratorBegin();instances != cc.getItemsListIteratorEnd();++instances) {
        const genealogy::CloneInstance& ci = *instances;
        if(positions[ci.getId()] == position) {
          return true;
        }
      }
      return false;
    }

    std::string DuplicatedCodeMiner::computeCloneClassCode(unsigned int pos, unsigned int length) {
      std::string s("CLONE");

      for (unsigned int i=0;i<length; i++) {

        int kind=getNodeKindAt(pos+i);
        s.append(boost::lexical_cast<std::string>(kind));
      }
      return s;
    }

    void DuplicatedCodeMiner::alignCloneClass(Aligner::AlignKind alignKind, const SuffixArray<int>::CloneClass& suffixCl, CloneClassPotentialCloneInstanceMap& potentialCloneInstances) {
      config.stat.numOfFoundsuffixInstances += suffixCl.num;
      ++config.stat.numOfFoundsuffixClass;
      unsigned int length = suffixCl.length;
      int oneOccurance = suffixCl.position[0];
      const unsigned* instances = suffixCl.position;

      common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ,oneOccurance,length+oneOccurance,suffixCl.num);

      // if (common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDDebug ) {
      //   for (int i = 1;i<suffixCl.num;i++) {
      //     common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ_2,suffixCl.position[i],length+suffixCl.position[i]);
      //   }
      // }

      if (alignKind==Aligner::SyntaxBoundary) {
        std::stack<unsigned int> offset;
        std::list<Interval> intervals;
        for (unsigned int i=0; i<length; i++) {
          int currentNodeKind=getNodeKindAt(oneOccurance+i);
          if (isDecDepthSign(currentNodeKind)) {
            if (!offset.empty()) {
              unsigned int lastOffset=offset.top();
              if ((i - lastOffset) > config.minAsgNodes || !config.singleAsgRoot) {
                Interval I(lastOffset, i);

                list<Interval>::iterator iter=intervals.begin();
                while (iter!=intervals.end()) {
                  // removing contained intervals
                  Interval current=(*iter);
                  if (current<=I)
                    iter=intervals.erase(iter);
                  else
                    break;
                }
                intervals.push_front(I);
              }
              offset.pop();
            } else {
              //     common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ_6,oneOccurance+i);
              //this node was not part of a whole syntax tree
              //we cannot do anything at this point.
            }
          } 
          else 
            if (isASGNode(oneOccurance+i)) {
              offset.push(i);
            }
        }//end for

        //at this point 'intervals' contains all the syntactic subtrees of the current clone class
        //first we merge the available intervals
        if(!config.singleAsgRoot && !intervals.empty()) {
          for(list<Interval>::iterator it1 = intervals.begin(), it2 = it1++; it1 != intervals.end() && it2 != intervals.end();) {
            if(it1->b == it2->a - 1 ) {
              it1->b = it2->b;
              if(it2->intervals == NULL) {
                delete it1->intervals;
                it1->intervals = new vector<unsigned int>();
                updateMemoryStat();
              } else {
                it1->intervals = it2->intervals;
              }
              it1->intervals->push_back(it2->a);
              it2->intervals = NULL;
              intervals.erase(it2);
            }
            it2 = it1++;
          }
        }

        // create clone classes

        list<Interval>::iterator iter=intervals.begin();
        while (iter!=intervals.end()) {
          Interval& I=(*iter);
          iter++;
          unsigned intervalLength = I.b - I.a + 1;
          if (intervalLength < config.minAsgNodes) {
            common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ_5,intervalLength);
            continue;
          }


          bool isNew = true;
          
          genealogy::CloneClass* cc = createCloneClass(oneOccurance+I.a, intervalLength, isNew);
          common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ_3,cc->getId());
          for (unsigned posIt = 0; posIt <  suffixCl.num; ++posIt) {
            PotentialCloneInstance potI(instances[posIt], I.clone());
          
            updateMemoryStat();
            potentialCloneInstances[cc->getId()].insert(potI);
            // common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ_4,instances[posIt],instances[posIt]+I.a,instances[posIt]+I.b);
           
           // createCloneInstance(potI.startPosition + potI.I.a, potI.I.b - potI.I.a + 1, potI.startPosition, potI.I.intervals, *cc);
           config.stat.numOfpotInstances++;
           updateMemoryStat();
          }
        }
      } //end Syntax Boundary
    }

    genealogy::CloneClass* DuplicatedCodeMiner::createCloneClass(unsigned int position, unsigned int length, bool& isNewClass) {

      genealogy::CloneClass* cloneClass = NULL;

      //first we have to check if this clone class already exists
      std::string code=computeCloneClassCode(position, length);
      std::map<std::string, genealogy::CloneClass*>::iterator iter=cloneClassMap.find(code);

      if (iter!=cloneClassMap.end()) {
        isNewClass = false;
        cloneClass = iter->second;
      } else {
        isNewClass = true;
        cloneClass = genealogyFact->createCloneClassNode();
        cloneClass->setFingerprint(code);
        cloneClass->setHeadNodeKind(getNodeKindAt(position));
        cloneClass->setType(genealogy::ctkType2);
        lengths[cloneClass->getId()] = length;
        currentSystem->addCloneClasses(cloneClass->getId());
        cloneClassMap.insert(make_pair(code, cloneClass));
      }
      return cloneClass;
    }

    const ClonePositioned* DuplicatedCodeMiner::getFirstNode(unsigned int from, unsigned int to) const {
      for(unsigned int pos = from; pos <= to; ++pos) {
        const ClonePositioned* nodePos = getNode(pos);
        if(nodePos)
          return nodePos;
      }
      return NULL;
    }

    genealogy::CloneInstance* DuplicatedCodeMiner::createCloneInstance(unsigned int position, unsigned int length, unsigned int intervalStart, vector<unsigned int>* intervals, genealogy::CloneClass& parent) {

      const ClonePositioned* firstNode = getFirstNode(position, position + length);
      if (!firstNode)
        throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNABLE_TO_DETERMINE_THE_LINE_INFO);

      std::stack<unsigned int> offset;
      unsigned int lastOffset=0;
      bool wasLastOffset=false;

      for(unsigned int i = 0; i < length; ++i) {
        int currentNodeKind = getNodeKindAt(position + i);
        if( isDecDepthSign(currentNodeKind) ) {
          if(!offset.empty()) {
            lastOffset = offset.top();
            wasLastOffset = true;
            offset.pop();
          } else {
            //this node was not part of a whole syntax tree
            //we cannot do anything at this point.
          }
        } else if (isASGNode(position + i)) {
          offset.push(i);
        }
      }
      if (!wasLastOffset) {
        if (!offset.empty()) {
          lastOffset=offset.top();
        } else
          throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNABLE_TO_DETERMINE_THE_LINE_INFO);
      }

      const ClonePositioned* lastNode=getNode(position+lastOffset);
      if (!lastNode)
        throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNABLE_TO_DETERMINE_THE_LINE_INFO);

      genealogy::CloneInstance& ci = *(genealogyFact->createCloneInstanceNode());
      ci.setLine(firstNode->getLine());
      ci.setCol(firstNode->getCol());
      ci.setEndLine(lastNode->getEndLine());
      ci.setEndCol(lastNode->getEndCol());
      ci.setPath(firstNode->getStringPath());
      ci.setRootBegin(firstNode->getId());


      std::stringstream cloneInstanceRootNodes;
      cloneInstanceRootNodes << std::hex;
      cloneInstanceRootNodes << std::setw(8);
      cloneInstanceRootNodes << std::setfill('0');
      cloneInstanceRootNodes << firstNode->getId();

      if(intervals ) {
        ci.setRootLength(static_cast<unsigned>(intervals->size())+1);

        std::sort(intervals->begin(),intervals->end());

        for (std::vector<unsigned int>::iterator it = intervals->begin(); it != intervals->end(); ++it) {
          const ClonePositioned* nodePos = getNode(intervalStart + *it);
          if (nodePos) {
            cloneInstanceRootNodes << std::hex;
            cloneInstanceRootNodes << std::setw(8);
            cloneInstanceRootNodes << std::setfill('0');
            cloneInstanceRootNodes << nodePos->getId();
          }
        }
      } else {
        ci.setRootLength(1);
      }

      ci.setRootNodes(cloneInstanceRootNodes.str());

      positions[ci.getId()] = position;

      // set component


      //ci.setComponent(firstNode->getLimComponentId());
      std::string asg= getAsgNameByLimId ( firstNode->getLimComponentId(),*limFact);
      for (columbus::genealogy::ListIterator<genealogy::Component> componentIt = currentSystem->getComponentsListIteratorBegin();componentIt != currentSystem->getComponentsListIteratorEnd();++componentIt) {
        const columbus::genealogy::Component& cmp = *componentIt;
        if (cmp.getName() == asg) {
          ci.setComponent(cmp.getId());
          break;
        }
      }
      
      parent.setInstances(parent.getInstances()+1);
      parent.addItems(ci.getId());
      ci.setCloneClass(&parent);

      common::WriteMsg::write(CMSG_CLONE_INSTANCE, ci.getId());
      //assign clone instance to the lim nodes 
      NodeId lastLimNodeID = 0;

      for (unsigned int i = 0; i < length;i++){
        const ClonePositioned* nodePos = getNode(position+i);

        if(nodePos) {
          common::WriteMsg::write(CMSG_SD_ON, LANGUAGE_NAMESPACE::Common::toString( ((LANGUAGE_NAMESPACE::NodeKind) nodePos->getNodeKind())).c_str(), nodePos->getId() ,nodePos->getLine(),nodePos->getCol(),nodePos->getStringPath().c_str(),position+i);
          if (nodePos->getLimNodeId() != 0 && lastLimNodeID != nodePos->getLimNodeId()) {
            limNodeClineInstanceMap[ci.getId()].insert(nodePos->getLimNodeId());
            limComponentClineInstanceMap[ci.getId()].insert(nodePos->getLimComponentId());
            lastLimNodeID = nodePos->getLimNodeId();
          } 
        }
      }

      updateMemoryStat();
      return &ci;
    }

    int DuplicatedCodeMiner::getNodeKindAt(unsigned int position) const {
      return nodeKindSequence.at(position);
    }

    bool DuplicatedCodeMiner::getIsNeeded(const string& id) const {
      if (config.metrics)
        return rulHandler->getIsEnabled(id);
      else
        return false;
    }

    bool DuplicatedCodeMiner::isSeparator(int value) const {
      return theCloneVisitor->isSepCharacter(value);
    }

    bool DuplicatedCodeMiner::isDecDepthSign(int value) const {
      return theCloneVisitor->isSepDecDepthSign(value);
    }

    void DuplicatedCodeMiner::addValue(const string& warningType, const std::list<columbus::graph::Edge::EdgeType>& relType, const columbus::graph::Node& node, int value, bool sumUp) {
      columbus::graphsupport::incMetricInt(graph, node.getUID(), warningType, value );
      if (sumUp) {
        std::list<columbus::graph::Node> nodes;
        getParent(node, relType, nodes);
        for(std::list<columbus::graph::Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
          addValue(warningType, relType, *it, value, true);
        }
      }
    }

    columbus::graph::Node DuplicatedCodeMiner::findNodeByRange(columbus::graph::Graph& graph, const string& path, int line, int col, int endLine, int endCol) {
      // remove \\\\ from lines
      std::list<columbus::graph::Node> nodes;
      indexer->findNodesByRange(graph, path, line, col, endLine, endCol, nodes);
      if(nodes.size() > 0) {
        int min_line = INT_MIN, min_col = INT_MIN, min_endline = INT_MAX, min_endcol = INT_MAX;
        std::string min_path = "";
        columbus::graph::Node minimalNode;/* = nodes.front();*/
        /*columbus::graphsupport::getPositionAttribute(minimalNode, min_path, min_line, min_col, min_endline, min_endcol);*/

        for(std::list<columbus::graph::Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
          if(it->getType().getType() == graphsupport::graphconstants::NTYPE_DCF_CLONECLASS || it->getType().getType() == graphsupport::graphconstants::NTYPE_DCF_CLONEINSTANCE)
            continue;
          int act_line = 0, act_col = 0, act_endline = 0, act_endcol = 0;
          std::string act_path = "";
          columbus::graphsupport::getPositionAttribute(*it, act_path, act_line, act_col, act_endline, act_endcol);
          // if the clone not in the actual element we go the next iteration
          if (act_line > line || act_endline < endLine)
            continue;
          if ((act_line > min_line || (act_line == min_line && act_col > min_col)) &&
            (act_endline < min_endline || (act_endline == min_endline && act_endcol < min_endcol))
            ) {
              minimalNode = *it;
              min_path = act_path;
              min_line = act_line;
              min_col = act_col;
              min_endline = act_endline;
              min_endcol = act_endcol;
          }
        }
        return minimalNode;
      }
      return columbus::graph::Graph::invalidNode;
    }

    void DuplicatedCodeMiner::getParent(const columbus::graph::Node& node, const std::list<columbus::graph::Edge::EdgeType>& relType, std::list<columbus::graph::Node>& nodes) {
      for (std::list<columbus::graph::Edge::EdgeType>::const_iterator itRelType = relType.begin();itRelType != relType.end();++itRelType) {
        static map<columbus::graph::Edge::EdgeType, map<graph::Node, graph::Node> > parents;
        map<graph::Node, graph::Node>::iterator node_parent_it = parents[*itRelType].find(node);
        if(node_parent_it != parents[*itRelType].end()) {
          nodes.push_back(node_parent_it->second);
          continue;
        }

        unsigned parentCounter = 0;
        columbus::graph::Node parent = columbus::graph::Graph::invalidNode;
        // find parent node
        columbus::graph::Edge::EdgeIterator edgeIt = node.findOutEdges( *itRelType);
        while(edgeIt.hasNext()) {
          ++parentCounter;
          parent = edgeIt.next().getToNode();
          if( !(parent == columbus::graph::Graph::invalidNode))
            nodes.push_back(parent);
        }

        if(parentCounter == 1) {
          parents[*itRelType].insert(make_pair(node, nodes.back()));
        }

      }
    }

    void DuplicatedCodeMiner::applyFilter(AbstractFilter* filter) {
      set<NodeId> markedCloneClasses;
      for(genealogy::ListIterator<genealogy::CloneClass> groupsIt = currentSystem->getCloneClassesListIteratorBegin(); groupsIt != currentSystem->getCloneClassesListIteratorEnd(); ++groupsIt) {
        const genealogy::CloneClass& cc = *groupsIt;
        if (cc.getIsVirtual())
          continue;
        
        if(filter->checkCloneClass(cc)) {
          cloneClassMap.erase(cc.getFingerprint());
          markedCloneClasses.insert(cc.getId());
        }
      }

      for(set<NodeId>::iterator it = markedCloneClasses.begin(); it != markedCloneClasses.end(); ++it) {
        genealogyFact->destroyNode(*it);
      }
    }

    DuplicatedCodeMiner::~DuplicatedCodeMiner() {
      for (unsigned q=0; q<nodeIdSequence.size(); q++) {
        delete nodeIdSequence[q];
      }

      if (limFact) {
        delete limFact;
        limFact = NULL;
      }

      delete theCloneVisitor;
      delete genealogyFact;
      delete strTable;
    }

    unsigned int DuplicatedCodeMiner::getLength(const genealogy::CloneClass& cc) {
      unsigned int length = INT_MAX;
      for (genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd(); ++cloneInstanceIt) {
        const genealogy::CloneInstance& ci = dynamic_cast<const genealogy::CloneInstance&>(*cloneInstanceIt);
        unsigned int instanceLength = (ci.getEndLine() - ci.getLine() + 1);
        if(length > instanceLength) {
          length = instanceLength;
        }
      }
      if(length == INT_MAX)
        length = 0;
      const_cast<genealogy::CloneClass&>(cc).setLength(length);
      return length;
    }

    void dumpCloneSmellType(const genealogy::Clone& clone, std::ostream& out) {
      switch (clone.getCloneSmellType()) {
      case genealogy::cstAppearing:
        out << " Appeared";
        break;
      case genealogy::cstMoving:
        out << " Moved from " << (dynamic_cast<const genealogy::CloneInstance&>(*clone.getPrevListIteratorBegin())).getCloneClass()->getUniqueName();
        break;
      case genealogy::cstDisappearing:
        out << " Disappeared";
        break;
      case genealogy::cstNone:
      default:
        break;
      }
    }

    void dump(const genealogy::CloneInstance& ci, std::ostream& out) {
      out << ci.getPath() <<"(" << ci.getLine() << "): " << ci.getUniqueName() << " [Ln:" << ci.getLine() << ", Col:" << ci.getCol() << " - Ln:"<< ci.getEndLine() <<", Col:"<< ci.getEndCol() <<"]";
      dumpCloneSmellType(ci, out);
      out << "\n";
    }



    void dump(const genealogy::CloneClass& cc, std::ostream& out) {
      //dump clone instance
      out << cc.getUniqueName() << " [Number of Clone Instances: " << DuplicatedCodeMiner::getRealNumberCi(cc) << ", Lines of Code: " << DuplicatedCodeMiner::getLength(cc) << "]";
      dumpCloneSmellType(cc, out);
      out << "\n";

      // The current instances
      for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin(); cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt) {
        const genealogy::CloneInstance& ci = dynamic_cast<const genealogy::CloneInstance&>(*cloneInstanceIt);
        dump(ci, out);
      }
      out << "\n";
    }

    void DuplicatedCodeMiner::dumpLastSystem(std::ostream& out) {

      out << "Number of Clone Classes: " << getRealNumberCC( *currentSystem) << std::endl << std::endl;

      // The current classes
      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin();cloneClassIt != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIt) {
        const genealogy::CloneClass& cc = dynamic_cast<const genealogy::CloneClass&>(*cloneClassIt);
        dump(cc, out);
      }
    }

    int DuplicatedCodeMiner::getCloneClassNum() const {
      return currentSystem->getCloneClassesSize() ;
    }

    void DuplicatedCodeMiner::exportGraph(const std::string& filename) {
      if(config.exportRul)
        graphsupport::buildRulToGraph(graph, *rulHandler);
      graph.saveBinary(filename);
    }

    unsigned int DuplicatedCodeMiner::getPosition(NodeId id) const{
      std::map<NodeId, unsigned int>::const_iterator pos = positions.find(id);
      if(pos != positions.end()) {
        return pos->second;
      } else {
        return 0;
      }
    }

    unsigned int DuplicatedCodeMiner::getLength(NodeId id) const{
      std::map<NodeId, unsigned int>::const_iterator len = lengths.find(id);
      if(len != lengths.end()) {
        return len->second;
      } else {
        return 0;
      }
    }

    bool DuplicatedCodeMiner::initLim() {
      common::WriteMsg::write(CMSG_INITIALIZING_LIM);
      strTable = new RefDistributorStrTable();

      if (limFact != NULL)
        delete limFact;

      if (!config.limFileName.empty()) {
        boost::filesystem::path limFilePath(config.limFileName);
        if (boost::filesystem::exists(limFilePath)) {
          try {
            limFact = new columbus::lim::asg::Factory(*strTable, "", columbus::lim::asg::limLangOther);
            std::list<HeaderData*> headerList;
            headerList.push_back(&limOrigin);
            limFact->load(config.limFileName, headerList);
            limFact->initializeFilter();

            boost::filesystem::path f(config.limFileName);
            try {
              f=boost::filesystem::change_extension(f, LIM_FILTER_FILE_EXTENSION);
              if (common::fileTimeCmp(f.string(), config.limFileName) == -1) {
                common::WriteMsg::write(CMSG_FILTER_FILE_OLD, f.string().c_str());
              } else {
                if(common::pathFileExists(f.string().c_str(), false))
                {
                  limFact->loadFilter(f.string());
                }
              }
            } catch (columbus::Exception& e) {
              common::WriteMsg::write(CMSG_FILTER_FILE_CANNOT_BE_LOADED , f.string().c_str());
              common::WriteMsg::write(CMSG_CAUSE, e.getMessage().c_str());
            }

          }
          catch (columbus::lim::asg::LimException& e) {
            common::WriteMsg::write(CMSG_FAILED);
            common::WriteMsg::write(CMSG_SIMPLE_STRING_TRANSMIT_ERR, e.getMessage().c_str() );
            return false;
          }
        } else {
          common::WriteMsg::write(CMSG_FAILED);
          return false;
        }
      } else {
        common::WriteMsg::write(CMSG_FAILED);
        return false;
      }

      class FileSystemVisitor :public columbus::lim::asg::Visitor {
      public:
        int maxNDC;

        FileSystemVisitor():maxNDC(0){}
        std::list<std::string> files;/*
                                     void visit(const columbus::lim::asg::physical::File& node , bool callVirtualBase) {
                                     std::string name = lim::asg::Common::getFullPath(node);
                                     for (std::list<std::string>::iterator it = files.begin();it != files.end();++it)  {
                                     unsigned int ndc =  NodeEmbeddednessVisitorBase::calculateNDC(*it,name);
                                     if (ndc > maxNDC) {
                                     maxNDC = ndc;
                                     }
                                     }
                                     files.push_back(name);
                                     }
                                     */
        struct NdcDepthPair {
          NdcDepthPair(int depth, int subMaxNDC) :depth(depth), subMaxNDC(subMaxNDC) {}
          int depth;
          int subMaxNDC;
        };

        NdcDepthPair calculateMaxDistance(columbus::lim::asg::physical::Folder& node) {
          string s = lim::asg::Common::getFullPath(node);

          if (node.getContainsIsEmpty()) {
            return NdcDepthPair(1,0);
          }

          if (node.getContainsSize() == 1) {
            if (lim::asg::Common::getIsFile(* node.getContainsListIteratorBegin())) {
              return NdcDepthPair(2,0);
            } else {
              NdcDepthPair subtreeValues = calculateMaxDistance((columbus::lim::asg::physical::Folder&)*node.getContainsListIteratorBegin());
              subtreeValues.depth++;
              return subtreeValues;
            }
          } else {
            int maxNDC = 0;
            int maxDept = 0;
            int maxDepth2 = 0;

            for (columbus::lim::asg::ListIterator<columbus::lim::asg::physical::FSEntry> it = node.getContainsListIteratorBegin();it != node.getContainsListIteratorEnd();++it ) {
              NdcDepthPair subtreeValues = NdcDepthPair(0,0);

              if (lim::asg::Common::getIsFile(* it)) {
                subtreeValues = NdcDepthPair(1,0);
              } else {
                subtreeValues = calculateMaxDistance((columbus::lim::asg::physical::Folder&)*it);
              }
              if (subtreeValues.subMaxNDC > maxNDC) {
                maxNDC = subtreeValues.subMaxNDC;
              }

              if (subtreeValues.depth > maxDept) {
                maxDepth2 = maxDept;
                maxDept = subtreeValues.depth ;
              } else if (subtreeValues.depth > maxDepth2) {
                maxDepth2 = subtreeValues.depth ;
              }

            }

            int ndc = maxDept+maxDepth2;
            if (ndc < maxNDC) {
              ndc = maxNDC;
            }
            return NdcDepthPair(maxDept+1,ndc);
          }
          return NdcDepthPair(1,0);
        }


        void visit(const columbus::lim::asg::physical::FileSystem& node , bool callVirtualBase) {
          int maxDept = 0;
          int maxDept2 = 0;
          for (columbus::lim::asg::ListIterator<columbus::lim::asg::physical::FSEntry> it = node.getFSEntryListIteratorBegin();it != node.getFSEntryListIteratorEnd();++it ) {
            if (lim::asg::Common::getIsFolder(* it)) {
              NdcDepthPair result = calculateMaxDistance((columbus::lim::asg::physical::Folder&) (*it));

              if (maxNDC < (result.subMaxNDC)){
                maxNDC = (result.subMaxNDC);
              }
              if (maxDept < result.depth) {
                if (maxDept2 < maxDept ) {
                  maxDept2 = maxDept;
                }
                maxDept = result.depth;
              } else {
                if (maxDept2 < result.depth ) {
                  maxDept2 = result.depth;
                }
              }
            }
          }
        }
      };

      FileSystemVisitor fileSystemVisitor;
      columbus::lim::asg::AlgorithmPreorder ap ;

      if (getIsNeeded("NCR")) {
        ap.run(*limFact,fileSystemVisitor);
      }

      currentSystemMaxNDC = (fileSystemVisitor.maxNDC> 0 ? (fileSystemVisitor.maxNDC-1) :0) +1;

      set<std::string> componenetsInLim;
      //check components
      for (lim::asg::Factory::const_iterator it = limFact->begin();it != limFact->end();++it) {
        if (lim::asg::Common::getIsComponent(**it)){
          const std::string& name = dynamic_cast<const lim::asg::base::Component*>(*it)->getName();
          componenetsInLim.insert(name );
          if (name.compare(ROOT_COMPONENT_NAME) == 0) {
            rootComponenetID = (*it)->getId();
          }
        }
      }
      
      currentFactory.fillComponentList(config.files);
      const std::map<std::string, std::string>& componentList = currentFactory.getLimComponentNameFileNameMap();
      bool componetOK = true;
      
      for (std::map<std::string, std::string>::const_iterator it =componentList.begin();it != componentList.end();++it) {
        if (componenetsInLim.erase(it->first) == 0 ){
          common::WriteMsg::write(CMSG_NO_INFO_FOR_FILE,it->first.c_str(),config.limFileName.c_str());
          componetOK = false;
        }
      }

      return componetOK;
    }

    void DuplicatedCodeMiner::setFilterOut(ostream& out) {
      filterOut = &out;
    }

    void clearNodeIdSequence(std::vector<ClonePositioned*>& nodeIdSequence) {
      for (size_t q=0; q<nodeIdSequence.size(); q++)
        delete nodeIdSequence[q];
      nodeIdSequence.clear();
    }


    bool DuplicatedCodeMiner::PutBeginSignToNode( std::stack<const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned*> &nodeStack, const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned* node,LANGUAGE_NAMESPACE::VisitorAbstractNodes*  cloneVisitor ) {
      nodeStack.push(node);
      cloneVisitor ->visit(*node);
      return true;
    }

    void DuplicatedCodeMiner::PutEndSignToNode( std::stack<const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned*> &nodeStack, LANGUAGE_NAMESPACE::VisitorAbstractNodes*  cloneVisitor) {
      cloneVisitor->visitEnd(*nodeStack.top());
      nodeStack.pop();
    }

    struct PosComparator {
    public:

      bool operator() ( const CorrectedPos& leftNode,const CorrectedPos&  rightNode) { 
        if (leftNode.uniformPath != rightNode.uniformPath) {
          return (leftNode.uniformPath < rightNode.uniformPath) ;
        }
#if defined SCHEMA_JAVA
        return  leftNode.node->compareByPosition(*rightNode.node) < 0;
#else
        if(leftNode.node->GET_FILE_KEY_OF_POSITIONS != rightNode.node->GET_FILE_KEY_OF_POSITIONS)
          return leftNode.node->GET_FILE_KEY_OF_POSITIONS < rightNode.node->GET_FILE_KEY_OF_POSITIONS;

        if(leftNode.node->GET_LINE_OF_POSITIONS != rightNode.node->GET_LINE_OF_POSITIONS)
          return leftNode.node->GET_LINE_OF_POSITIONS < rightNode.node->GET_LINE_OF_POSITIONS;

        if(leftNode.node->GET_COLUMN_OF_POSITIONS != rightNode.node->GET_COLUMN_OF_POSITIONS)
          return leftNode.node->GET_COLUMN_OF_POSITIONS < rightNode.node->GET_COLUMN_OF_POSITIONS;

        if(leftNode.node->GET_END_FILE_KEY_OF_POSITIONS != rightNode.node->GET_END_FILE_KEY_OF_POSITIONS)
          return leftNode.node->GET_END_FILE_KEY_OF_POSITIONS > rightNode.node->GET_END_FILE_KEY_OF_POSITIONS;

        if(leftNode.node->GET_END_LINE_OF_POSITIONS != rightNode.node->GET_END_LINE_OF_POSITIONS)
          return leftNode.node->GET_END_LINE_OF_POSITIONS > rightNode.node->GET_END_LINE_OF_POSITIONS;

        if(leftNode.node-> GET_END_COLUMN_OF_POSITIONS != rightNode.node-> GET_END_COLUMN_OF_POSITIONS)
          return leftNode.node-> GET_END_COLUMN_OF_POSITIONS > rightNode.node-> GET_END_COLUMN_OF_POSITIONS; 

        if (leftNode.node->getNodeKind() != rightNode.node->getNodeKind()) {
          return leftNode.node->getNodeKind() < rightNode.node->getNodeKind();
        }

        return false;
#endif
      }
    };

    void DuplicatedCodeMiner::traversalPosiotionedNodes(LANGUAGE_NAMESPACE::Factory& rCurFact, VisitorAbstractNodes* cloneVisitor,const string& componentID,  const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned* inner /*= NULL*/ ) {
      // fill the vector with the nodes 
      std::vector< CorrectedPos > sortedPositionNodes;
      fillPositionnodesVektor(rCurFact, sortedPositionNodes,componentID);

      //sort the nodes 
      PosComparator co;
      std::sort<std::vector<CorrectedPos>::iterator,PosComparator >(sortedPositionNodes.begin(),sortedPositionNodes.end(),co);

      //This stack for find out when left the nodes.
      std::stack<const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned*> nodeStack;

      //IntervalData::iterator it = lineInfo->begin();
      std::vector<CorrectedPos>::iterator it = sortedPositionNodes.begin();

      if (inner) {
        //it = lineInfo->find(inner->getId());
        //TODO: find logarithm
        for (it = sortedPositionNodes.begin(); it!= sortedPositionNodes.end();++it ) {
          if (it->node == inner )
            break;
        }
      }

      bool quit = false;
      for (;it != sortedPositionNodes.end()&& !quit ;++it) {
        const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned& rPos = *(it->node);

        // Test the current node is after then the last node end.
        while ((nodeStack.size() >0) && isNodeAfter(*nodeStack.top(), rPos) ) {
          PutEndSignToNode(nodeStack,cloneVisitor);
          if ((nodeStack.size() == 0) && (inner)){
            quit = true;
          }
        }

        if ( !quit ) {
          PutBeginSignToNode(nodeStack, &rPos,cloneVisitor);
        }
      }

      //flush left
      while ( nodeStack.size() > 0 ) {
        PutEndSignToNode(nodeStack,cloneVisitor);
      }
    }

    void DuplicatedCodeMiner::updateMemoryStat() {
      static long long last = 0;
      using namespace common;
      memstat ms = getProcessUsedMemSize();
      if (config.stat.memory_peak < ms.size)
        config.stat.memory_peak = ms.size;
      if (  ( ms.size -last) != 0) {
        WriteMsg::write(WriteMsg::mlDDebug,"Mem ussage %d Mb diff %I64d\n",ms.size/1024/1024 ,   ms.size -last);
      }
      last = ms.size;
      
      
    }

    DuplicatedCodeMiner::DuplicatedCodeMiner(Config& config, columbus::rul::RulHandler* rulHandler) 

      : statementFilter(true)
      , config(config)
      , strTable(NULL)
      , genealogyFact(NULL)
      , limFact(NULL)
      , currentSystem(NULL)
      , lastSystem(NULL)
      , rulHandler(rulHandler)
      , indexer(NULL)
      , theCloneVisitor(NULL)
      , filterOut(NULL)
#ifdef GENEALOGY
      , trivial_pairs(0)
      , dumpGraphml(false)
#endif
      , coveredLines()
      , coveredNodes()
    {

    }

    void DuplicatedCodeMiner::getParentTransitve( const columbus::graph::Node& node, const std::list<columbus::graph::Edge::EdgeType>& relType, std::set<columbus::graph::Node>& nodesList ) {
      std::list<columbus::graph::Node> nodes;
      getParent(node, relType, nodes);
      for(std::list<columbus::graph::Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        getParentTransitve(*it,relType,nodesList);
        nodesList.insert(*it);
      }
    }

    std::string DuplicatedCodeMiner::getGraphNameOfGenelogyNode( const columbus::genealogy::Base& genealogyBase ) {
      std::string s("C");
      return  s + boost::lexical_cast<std::string>(genealogyBase.getId());
    }

    NodeId DuplicatedCodeMiner::getLimComponenetIdByName( const std::string& name, const columbus::lim::asg::Factory& factory ) {
      vector<const columbus::lim::asg::base::Component*> components;
      for ( columbus::lim::asg::Factory::const_iterator it = factory.begin();it != factory.end();++it) {
        if (lim::asg::Common::getIsComponent(**it) ) {
          const string& compname = static_cast< const columbus::lim::asg::base::Component*>(*it)->getName();
          if (! (compname.compare(name) ) ) {
            return (*it)->getId();
          }
          components.push_back(static_cast< const columbus::lim::asg::base::Component*>(*it));
        }
      }

      for (auto componentNode : components)
      {
        if (componentNode->getName().find(name) != string::npos)
        {
          common::WriteMsg::write(CMSG_FILENAME_COMPONENT_MATCH, name.c_str());
          return componentNode->getId();
        }
      }

      return 0;
    }

    const std::string& DuplicatedCodeMiner::getAsgNameByLimId( columbus::NodeId limId, const columbus::lim::asg::Factory& factory ) const {
      const std::string& refEmptyString = limFact->getStringTable().get(limFact->getStringTable().set(""));

      if (limId == 0)
        return refEmptyString;

      if (!factory.getExist(limId))
        return refEmptyString;

      if (lim::asg::Common::getIsComponent( factory.getRef(limId))) {
        lim::asg::base::Component&  refComp = static_cast<lim::asg::base::Component&> (factory.getRef(limId));
        return refComp.getName();
      }
      return refEmptyString;
    }

    const ClonePositioned* DuplicatedCodeMiner::getEndNode( unsigned int from, unsigned int to ) const
    {
      for(unsigned int pos = to; pos >= from; --pos) {
        const ClonePositioned* nodePos = getNode(pos);
        if(nodePos)
          return nodePos;
      }
      return NULL;
    }

    bool DuplicatedCodeMiner::isItFilteredInLim(NodeId compId, const Base& asgNode) const {
      //find the lim node. 

      NodeId limNodeId = 0;
      const Base* node = &asgNode;
      while (limNodeId == 0 && node ) {
        limNodeId = getLimNodeIdByNode(compId, *node);
        if (!limNodeId) {
          node = node->getParent();
        }
      }
      if (limNodeId) {
        return limFact->getIsFiltered(limNodeId);
      }

      return true;
    }

    NodeId DuplicatedCodeMiner::getLimNodeIdByNode(NodeId compId, const Base& node) const {
      return limOrigin.getLimIdToCompIdAndCppId(compId,node.getId());
    }

    int DuplicatedCodeMiner::getCloneInstanceNum() const {
      int ret = 0;
      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin();cloneClassIt != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIt) {
        const genealogy::CloneClass& cc = dynamic_cast<const genealogy::CloneClass&>(*cloneClassIt);
        ret += cc.getItemsSize();
      }
      return ret;
    }

    bool DuplicatedCodeMiner::isNodeAfter( const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned &referencePos , const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned &pos ) {
      return (    ( referencePos.GET_FILE_KEY_OF_POSITIONS != pos.GET_FILE_KEY_OF_POSITIONS )
        ||  ( referencePos.GET_END_LINE_OF_POSITIONS < pos.GET_LINE_OF_POSITIONS )

        || (    ( referencePos.GET_END_LINE_OF_POSITIONS  == pos.GET_LINE_OF_POSITIONS )
        && ( referencePos.GET_END_COLUMN_OF_POSITIONS < pos.GET_COLUMN_OF_POSITIONS )
        )
        );
    }

    void DuplicatedCodeMiner::fillPositionnodesVektor( LANGUAGE_NAMESPACE::Factory &rCurFact, std::vector<CorrectedPos > &sortedPostitionNodes,const string& componenetId )
    {
      class VisitorOfPosNodes : public VisitorAbstractNodes {
      public:
        /**
        * \brief Constructor for Visitor.
        * \param nodelist [in, out] The list where the id of the visited nodes are inserted.
        */

        VisitorOfPosNodes(LANGUAGE_NAMESPACE::Factory &rCurFact, std::vector<CorrectedPos > &sortedPostitionNodes,const string& componenetId,std::map<std::string, std::set<columbus::NodeId> >& filteredNodes ):
          rCurFact(rCurFact), sortedPostitionNodes(sortedPostitionNodes), componenetId(componenetId), filteredNodes(filteredNodes) {}

            /**
            * \brief Visitor for all nodes.
            * \param node [in] This node is being visited.
            */
            virtual void visit(const LANGUAGE_NAMESPACE::BASE_NAMESPACE::Positioned &node, bool callVirtualBase = true){
              if (node.GET_FILE_KEY_OF_POSITIONS != 0) {
                sortedPostitionNodes.push_back(CorrectedPos (&node,getUniformPathKey(node.GET_FILE_KEY_OF_POSITIONS,rCurFact.getStringTable())));
              } else {
                common::WriteMsg::write(WriteMsg::mlDDebug,"The position node has not a position %s %d\n", LANGUAGE_NAMESPACE::Common::toString(node.getNodeKind()).c_str(),node.getId());
              }
            }

      protected:
        /** \internal \brief Reference to the list where the ids will be collected. */
        LANGUAGE_NAMESPACE::Factory &rCurFact;
        std::vector<CorrectedPos > &sortedPostitionNodes;
        const string& componenetId;
        std::map<std::string, std::set<columbus::NodeId> >& filteredNodes;
      };

      VisitorOfPosNodes visitor(rCurFact,sortedPostitionNodes,componenetId,filteredNodes);
      LANGUAGE_NAMESPACE::AlgorithmPreorder ap;
      ap.setSafeMode();
#ifdef SCHEMA_CSHARP
      ap.run(rCurFact, visitor);
#else 
      ap.run(rCurFact,visitor,rCurFact.getRoot()->getId());
#endif
    }

    unsigned int DuplicatedCodeMiner::getRealNumberCi( const genealogy::CloneClass& cc ) {
      unsigned int ret= 0;
      for (columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> itemsIter=cc.getItemsListIteratorBegin();itemsIter!=cc.getItemsListIteratorEnd();++itemsIter) {
        if (!itemsIter->getIsVirtual()) {
          ret++;
        }
      }
      return ret;
    }

    unsigned int DuplicatedCodeMiner::getRealNumberCC( const genealogy::System& sys )
    {
      unsigned int ret= 0;
      for (columbus::genealogy::ListIterator<columbus::genealogy::CloneClass> itemsIter=sys.getCloneClassesListIteratorBegin();itemsIter!=sys.getCloneClassesListIteratorEnd();++itemsIter) {
        if (!itemsIter->getIsVirtual() ) {
          ret++;
        }
      }
      return ret;
    }

    void DuplicatedCodeMiner::addParentComponents( std::set<NodeId> &componentsOfTheClass, NodeId currentComp )
    {
      componentsOfTheClass.insert(currentComp);
      for ( columbus::lim::asg::ListIterator<columbus::lim::asg::base::Base> 
        it = limFact->getReverseEdges().constIteratorBegin(currentComp,columbus::lim::asg::edkComponent_Contains);
        it != limFact->getReverseEdges().constIteratorEnd(currentComp,columbus::lim::asg::edkComponent_Contains);
      ++it) {
        addParentComponents(componentsOfTheClass,it->getId());
      }
    }

    void DuplicatedCodeMiner::collectContainerFiles( const lim::asg::logical::Package &package, std::set<columbus::Key> &fileNames )
    {

      for ( lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> it = package.getIsContainedInListIteratorAssocBegin();
        it != package.getIsContainedInListIteratorAssocEnd();++it) {
          std::string path = lim::asg::Common::getFullPath(*it);
          LowerStringOnWindows(path);
          fileNames.insert( limFact->getStringTable().set( path ) );
      }

      for (lim::asg::ListIterator<lim::asg::logical::Member> it = package.getMemberListIteratorBegin(); it != package.getMemberListIteratorEnd() ;++it) {
        if (lim::asg::Common::getIsPackage(*it)) {
          const lim::asg::logical::Package& subPackage = (const lim::asg::logical::Package&) *it;
          collectContainerFiles(subPackage,fileNames);
        }
      }
    }

    columbus::Key DuplicatedCodeMiner::getUniformPathKey( Key key, StrTable& strtable )
    {
      std::string origStr = strtable.get(key);
      std::replace(origStr.begin(),origStr.end(),'\\','/');
      return strtable.set(origStr);
    }

    void DuplicatedCodeMiner::setStatementFilter( bool val )
    {
      statementFilter = val;
    }

    //CCO metric - Clone Complexity for other langs
    void DuplicatedCodeMiner::calculateCOOForLangASG( columbus::NodeId componenetId,const std::string& sCompId)
    {
      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin();cloneClassIt != currentSystem->getCloneClassesListIteratorEnd();++cloneClassIt) {
        columbus::genealogy::CloneClass& cc= (columbus::genealogy::CloneClass&) cloneClassIt->getFactory().getRef(  cloneClassIt->getId());
        if (cc.getIsVirtual())
          continue;
        int length = lengths[cc.getId()];
        for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin(); cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt) {
          columbus::genealogy::CloneInstance& ci= (columbus::genealogy::CloneInstance&)cloneInstanceIt->getFactory().getRef(  cloneInstanceIt->getId());
          int sequencePos = positions[ci.getId()] ;
          const ClonePositioned* cp = getNode(sequencePos);
          if (cp->getLimComponentId() == componenetId){
            int cco = 0;
            COVERAGE_VISITOR coverageVisitor;
           
            for (int i = 0; i < length; ++i) {
              const ClonePositioned* position = getNode(sequencePos + i);
              if (position) {
                Base& langNode = currentFactory.getByComponentID(sCompId)->getRef(position->getId());
                if (position && coverageVisitor.isIncTheComplexity( langNode)){
                  cco++;
                }
              }
            }
            ci.setCco(cco+1);
          } 
        }
      }
    }
  }
}


