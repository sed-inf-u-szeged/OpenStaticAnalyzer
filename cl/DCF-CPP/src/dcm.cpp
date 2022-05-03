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


#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>
#include <common/inc/math/linear/hungarian_method.h>
#include <lim2graph/inc/Lim2GraphConverter.h>
#include <lim2graph/inc/VisitorGraphConverter.h>
#include <graphsupport/inc/RulBuilder.h>
#include <graphsupport/inc/GraphConstants.h>

#include <common/inc/Stat.h>
#include <common/inc/StringSup.h>
#include <iomanip> 
#include <lim/inc/visitors/Visitor.h>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <iostream> //sajat

#include <clang/Metrics/invoke.h>
#include <clang/Metrics/Output.h>
#include <clang/Metrics/BasicUID.h>
#include <clang/Frontend/ASTUnit.h>
#include <clangsupport/ASTIDMapGenerator.h>
#include <clangsupport/ASTLoader.h>
#include <clangsupport/ASTSupport.h>
#include <clang/AST/ParentMapContext.h>


#include "../inc/dcm.h"
#include "../inc/StatementFilter.h"
#include "../inc/CloneOccuranceFilter.h"
#include "../inc/CloneLengthFilter.h"
#include "../inc/RepeatingLinesFilter.h"
#include "../inc/messages.h"
#include "../inc/DistanceVisitor.h"
#include "../inc/CPPNamedVisitor.h"


using namespace common;

#define ROOT_COMPONENT_NAME "<System>"

namespace columbus {


    void updateMemoryStat(Config &config, const char* msg)
    {
      static long long last = 0;
      using namespace common;
      memstat ms = getProcessUsedMemSize();
      if (config.stat.memory_peak < ms.size)
        config.stat.memory_peak = ms.size;
      if ((msg != nullptr ) ||  ((ms.size - last) != 0)) {
        if (msg != nullptr)
          WriteMsg::write(WriteMsg::mlDebug,"[%s] Mem ussage %d MByte diff %I64d (peak:%lu MByte)\n", msg, ms.size / 1024 / 1024, (ms.size - last) / 1024 / 1024, config.stat.memory_peak / 1024 / 1024);
        else
          WriteMsg::write(WriteMsg::mlDDebug,"Mem ussage %d MByte diff %I64d (peak:%lu MByte)\n", ms.size/1024/1024, (ms.size - last) / 1024 / 1024, config.stat.memory_peak / 1024 / 1024);

      }
      last = ms.size;
    }


    using namespace suffix_array;
    

    std::map<NodeId, std::string> ciIdToAST;


    //when genealogy is maintained the previous factory is also needed

    void DuplicatedCodeMiner::setDumpgraphml( bool dump )
    {
      dumpGraphml = dump;
    }

#define DEBUGPRINTF(x)
#define DEBUGPRINTF2(x)
#define DEBUGPRINTF3(x)
  
    int DuplicatedCodeMiner::getNodeKindSequenceSize(){
      return serializationData.nodeKindSequence.size();
    }

    void DuplicatedCodeMiner::computeSimilarityAttributes(columbus::genealogy::CloneInstance& ci)
    {
      columbus::genealogy::CloneClass* cc = ci.getCloneClass();
      vector<NodeId> ciRootsList   = getInstanceIds(ci);

      columbus::genealogy::Component* component  = ci.getComponent();
      if (component == NULL)
        throw Exception(COLUMBUS_LOCATION, CMSG_EX_MISSING_COMPONENT_FOR_CI);

      const ASTNodeInfo* cp;
      
      //load ast
      ASTWithNodeIDMaps astWithNodeIdMaps = loadAST(ciIdToAST[ci.getId()], /*cacheLast=*/true);
      unsigned int pos = positions[ci.getId()];
      cp = getNode(pos);

      const int nodeKind = getNodeKindAt(pos);

      // For computing F1, F2, F3, F4, F5 only the first subtree is used!

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


      if((nodeKind & NodeMask::NodeTypeMask) == NodeType::Declaration){
        clang::Decl* d = static_cast<clang::Decl*>(astWithNodeIdMaps.nodeIdMaps->id2node[cp->getId()].first);
        if(auto* namedNode = clang::dyn_cast<clang::NamedDecl>(d)){
          if (ci.getF3_HeadNodeUniqueName().empty())  {
            ci.setF3_HeadNodeUniqueName(namedNode->getQualifiedNameAsString());
            common::WriteMsg::write(WriteMsg::mlDDDDebug,"the F3 is %s for %d\n",ci.getF3_HeadNodeUniqueName().c_str(),ci.getId());
          }
        }
      }
        
      
      // ============================ Computing F4 Attribute =======================================
        const clang::NamedDecl* ptrNamedAncestor = nullptr;
        std::string namedAncestor = "";
        
        if((nodeKind & NodeMask::NodeTypeMask) == NodeType::Declaration)
        { 
          clang::Decl* d = static_cast<clang::Decl*>(astWithNodeIdMaps.nodeIdMaps->id2node[cp->getId()].first);
          //Need to find the first declaration, because a definition also a declaration and it's first named ancestor can be the clang::TranslationUnitDecl.
          while(!d->isFirstDecl()){
            d = d->getPreviousDecl();
          }
          
          clang::DynTypedNodeList parents = getParents(&astWithNodeIdMaps.astUnit->getASTContext(), clang::DynTypedNode::create(*d));
          while((parents.size() > 0) && (parents[0].get<clang::TranslationUnitDecl>() == NULL))
          {
            if (auto namedDecl = parents[0].get<clang::NamedDecl>())
            {
              namedAncestor = namedDecl->getQualifiedNameAsString();
              ptrNamedAncestor = namedDecl;
              break;
            }
            else
              parents = getParents(&astWithNodeIdMaps.astUnit->getASTContext(), parents[0]);
          }
        }
        else if((nodeKind & NodeMask::NodeTypeMask) == NodeType::Statement)
        {
          clang::DynTypedNodeList parents =  astWithNodeIdMaps.astUnit->getASTContext().getParents( *(static_cast<clang::Stmt*>(astWithNodeIdMaps.nodeIdMaps->id2node[cp->getId()].first)) );

          while((parents.size() > 0) && (parents[0].get<clang::TranslationUnitDecl>() == NULL))
          {
            if (auto namedDecl = parents[0].get<clang::NamedDecl>())
            {
              namedAncestor = namedDecl->getQualifiedNameAsString();
              ptrNamedAncestor = namedDecl;
              break;
            }
            else
              parents = getParents(&astWithNodeIdMaps.astUnit->getASTContext(), parents[0]);
          }
        }
        
      if (ci.getF4_AncestorUniqueName().empty()) {
        if (namedAncestor != "") {
          ci.setF4_AncestorUniqueName(namedAncestor);
          common::WriteMsg::write(WriteMsg::mlDDDDebug,"the F4 is %s for %d\n",ci.getF4_AncestorUniqueName().c_str(),ci.getId());
        }
      }


      // ================================= Computing F5 Attribute ==================================
      // The L2 is the node count of the instanse so normally it can not be 0. If it is zero then it means that it is not calculated yet.
      if (ci.getF5_L2() == 0 && ptrNamedAncestor != nullptr) {

        if ((nodeKind & NodeMask::NodeKindMask) != clang::Decl::Kind::Namespace) {
not_namespace:
          DistanceVisitor dv(astWithNodeIdMaps.nodeIdMaps->id2node[cp->getId()].first);
          clang::NamedDecl* parent = const_cast<clang::NamedDecl*>(ptrNamedAncestor);
          clang::ASTPrePostTraverser astTraverser(astWithNodeIdMaps.astUnit->getASTContext(), parent, dv);
          astTraverser.run();
          
          ci.setF5_L1(dv.getL1());
          ci.setF5_L2(dv.getL2());
          ci.setF5_L3(dv.getL3());
          common::WriteMsg::write(WriteMsg::mlDDDDebug,"the F5 is L1 %d L2 %d L3 %d for %d\n",dv.getL1(),dv.getL2(),dv.getL3(),ci.getId());
        }
        else
        {
          if((nodeKind & NodeMask::NodeTypeMask) != NodeType::Declaration){
            //if the nodeKind is clang::Decl::Kind::Namespace but the node type not a declaration but a statement then that is not a namespace
            goto not_namespace;
          }
        }
      }


      // ================================ Computing F6 Attribute ===================================
      if (ci.getF6_LexicalStructure().empty()) {
        std::string source;
        clang::PrintingPolicy pp = astWithNodeIdMaps.astUnit->getASTContext().getPrintingPolicy();
        pp.Indentation = 0;
        pp.IncludeNewlines = false;
        for(vector<NodeId>::const_iterator ciRootsListIt = ciRootsList.begin(); ciRootsListIt != ciRootsList.end(); ++ciRootsListIt)
        {

          const auto &nodeInfo = astWithNodeIdMaps.nodeIdMaps->id2node[*ciRootsListIt];
          if(nodeInfo.second == AstNodeType::DECL)
          {
            clang::Decl* decl = (clang::Decl*)nodeInfo.first;
            llvm::raw_string_ostream s(source);
            decl->print(s, pp, 0);
          }
          else if(nodeInfo.second == AstNodeType::STMT)
          {
            clang::Stmt* stmt = (clang::Stmt*)nodeInfo.first;
            llvm::raw_string_ostream s(source);
            stmt->printPretty(s, nullptr, pp, 0, "");
          }
        }
        // Since the Decl printer does not use the IncludeNewlines policy we have to remove the newlines
        replace(source.begin(), source.end(), '\n', ' ');
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
      // Currently if order1 != order2, then the overall distance is set to inf later on.
      // Solution / TODO: modify weight of F2 in alpha array
      // Temporary solution: don't use F2 distance at all
      /*if (dist < bound) {
        int order1 = from.getF2_OrdinalNumber();
        int order2 = to.getF2_OrdinalNumber();

        if (order1 != order2) {
          double lineDistance=fabs((double)order1-order2);
          dist += alpha[2] * lineDistance;
          partial[2] = alpha[2] * lineDistance;
        }
      }*/
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
      {
        return inf;
      }
      return dist;
    }

    vector<genealogy::CloneInstance*> DuplicatedCodeMiner::getInstancesOfaSystem(const genealogy::System& system) const
    {
      vector<genealogy::CloneInstance*> instances;
      for (genealogy::ListIterator<genealogy::CloneClass> classItemsIter = system.getCloneClassesListIteratorBegin(); classItemsIter != system.getCloneClassesListIteratorEnd(); ++classItemsIter)
        for (genealogy::ListIterator<genealogy::CloneInstance> instanceItemsIter = classItemsIter->getItemsListIteratorBegin();  instanceItemsIter != classItemsIter->getItemsListIteratorEnd(); ++instanceItemsIter) 
          instances.push_back(const_cast<genealogy::CloneInstance*>(&(*instanceItemsIter)));
      return instances;
    }


    inline static void clearNodeIdSequence(std::vector<ASTNodeInfo*>& nodeInfoSequence);

    class ProcessCC : public SuffixArray<int>::CloneVisitor
    {
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
      std::list<std::shared_ptr<AbstractFilter>> filters;

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
          const ASTNodeInfo* cp = dcm->getNode(position+ctl);
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

/*
        printf("SuffixCC length:%u\n", suffixCl.length);
        for (unsigned i = 0; i < suffixCl.num; ++i)
        {
            printf("%u, ", suffixCl.position[i]);
        }
        printf("\n");
 */
        dcm->alignCloneClass(Aligner::SyntaxBoundary, suffixCl, potentialCloneInstances);
      }

      void buildCloneInstances()
      {
        for (DuplicatedCodeMiner::CloneClassPotentialCloneInstanceMap::const_iterator ccIt = potentialCloneInstances.begin(); ccIt != potentialCloneInstances.end(); ++ccIt) {
          unsigned lastend = 0;
          genealogy::CloneClass& cc = (genealogy::CloneClass&)dcm->genealogyFact->getRef(ccIt->first);
          for (set<DuplicatedCodeMiner::PotentialCloneInstance>::const_iterator ciIt = ccIt->second.begin(); ciIt != ccIt->second.end(); ++ciIt) {
            if (lastend > 0 && ciIt->startPosition + ciIt->I->a <= lastend){
              continue;
            }
            if (!dcm->containsInstanceAtPositon(ciIt->startPosition + ciIt->I->a, cc)) {
              lastend = ciIt->startPosition + ciIt->I->b;
              dcm->createCloneInstance(ciIt->startPosition + ciIt->I->a, ciIt->I->b - ciIt->I->a + 1, ciIt->startPosition, ciIt->I->intervals, cc);
            }
          }

          for (auto filter : filters)
          {
            if(filter->checkCloneClass(cc))
            {
              for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin(); cloneInstanceIt != cc.getItemsListIteratorEnd(); ++cloneInstanceIt)
              { //clone instance
                const auto ciId = cloneInstanceIt->getId();
                dcm->limNodeCloneInstanceMap.erase(ciId);
                dcm->limComponentCloneInstanceMap.erase(ciId);
                dcm->cloneInstanceRootNodesMap.erase(ciId);
                ciIdToAST.erase(ciId);
              }

              const auto ccId = cc.getId();
              dcm->cloneClassMap.erase(dcm->cloneClassFingerprintMap[ccId]);
              dcm->genealogyFact->destroyNode(ccId);
              dcm->cloneClassFingerprintMap.erase(ccId);
              break;
            }
          }

          // If the cc is not filtered then we set the fingerprint and rootnodes attributes of the clone classes and instances
          if (dcm->genealogyFact->getExist(ccIt->first))
          {
            cc.setFingerprint(dcm->cloneClassFingerprintMap[cc.getId()]);
            for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin(); cloneInstanceIt != cc.getItemsListIteratorEnd(); ++cloneInstanceIt)
            {
              const_cast<columbus::genealogy::CloneInstance&>(*cloneInstanceIt).setRootNodes(dcm->cloneInstanceRootNodesMap[cloneInstanceIt->getId()]);
            }
          }

        }
      }

      void addFilter(shared_ptr<AbstractFilter> filter)
      {
        filters.push_back(filter);
      }

    };

    class ProcessPatternFilter : public SuffixArray<int>::CloneVisitor {
    public:
      ProcessPatternFilter()
        : sequence(NULL)
        , min_inst_length(0)
        , dcm(NULL)
      {

      }
      virtual ~ProcessPatternFilter(){}
      ProcessPatternFilter(const ProcessPatternFilter&);
      ProcessPatternFilter operator= (const ProcessPatternFilter&);
      Sequence<int>* sequence;
      unsigned min_inst_length;

      std::set<size_t> filteredNodeIndexes;
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
              for(unsigned i = drop_begin; i < drop_end; i++)
                filteredNodeIndexes.insert(i);
            }
            drop_begin = 0;
            drop_end = 0;
          }
          prevPos = it;
        }

        if(drop_end !=0 && ( (drop_end - drop_begin) >= min_inst_length ) ) {
          // drop node at x position
          for(unsigned i = drop_begin; i < drop_end; i++)
            filteredNodeIndexes.insert(i);
        }
      }
    };


    void DuplicatedCodeMiner::patternFilter() {
      if(config.patternMaxSingleLength == 0 || config.patternMinFullLength == 0)
        return;

      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("patternFilter()");

      common::timestat time = common::getProcessUsedTime();
      Sequence<int> sequence(serializationData.nodeKindSequence);
      ProcessPatternFilter ppf;
      ppf.sequence = &sequence;
      ppf.min_inst_length = config.patternMinFullLength;
      ppf.dcm = this;

      LinearSuffixArray<int> suffixArray(sequence);
      LinearSuffixArray<int>::Duplicateiterator lduplicateIterator = suffixArray.iterator(1, config.patternMaxSingleLength, config.patternMinFullLength, false);


      lduplicateIterator.run(ppf);
      size_t count = ppf.filteredNodeIndexes.size();

      auto filterTime = common::getProcessUsedTime().user - time.user;
      common::WriteMsg::write(CMSG_NODE_FILTERED_OUT, count, filterTime);

      config.stat.filterTime += filterTime;


      perfSectionHandler.addTimeStamp("remove filtered nodes");

      updateMemoryStat(config);
      if(count > 0)
      {
        // make unique nodekinds for the filtered nodes
        for (size_t i = 0; i < serializationData.nodeKindSequence.size(); ++i)
        {
          if (ppf.filteredNodeIndexes.find(i) != ppf.filteredNodeIndexes.end())
          {
            serializationData.nodeKindSequence[i] = theCloneVisitor->getSeparator();
            delete serializationData.nodeInfoSequence[i];
            serializationData.nodeInfoSequence[i] = nullptr;
          }
        }
        updateMemoryStat(config);
      }
      common::WriteMsg::write(CMSG_SERIALIZED_AST_SIZE, serializationData.nodeKindSequence.size());

/*
      // DEBUG
      for (auto nk : serializationData.nodeKindSequence)
        printf("%d ", nk);
      printf("\n");
*/
    }
    
    void DuplicatedCodeMiner::dumpNodeIdSequence(const std::string filename)
    {
      ofstream out;
      out.open(filename, ios::out | ios::trunc);
      
      unsigned indent_size = 0;
      if(out.is_open())
      {
        for(auto node : serializationData.nodeInfoSequence)
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

    void DuplicatedCodeMiner::dumpNodeKindSequence(const std::string filename)
    {
      ofstream out;
      out.open(filename);
      int indent_size = 0;
      if(out.is_open())
      {
        for(auto kind : serializationData.nodeKindSequence)
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

    void DuplicatedCodeMiner::dumpCloneInstanceInformation()
    {
      vector<genealogy::CloneInstance*> instancesOfTheCurrentSystem = getInstancesOfaSystem(*currentSystem);
      for (auto currentInsatnce : instancesOfTheCurrentSystem)
      {
        //get position of clone instance in the node id sequence
        int pos = positions[currentInsatnce->getId()];

        printf("CI:%d position:%d\n", currentInsatnce->getId(), pos);
        printf("  Root Nodes:%s\n", currentInsatnce->getRootNodes().c_str());

        //get the appropriate clone positioned object
        auto cp = serializationData.nodeInfoSequence[pos];
        if (cp != nullptr)
        {
          printf("Path:%s TUPath:%s\n", cp->getStringPath().c_str(), cp->getStringTUPath().c_str());

        }
      }
    }

    void DuplicatedCodeMiner::detectClones(std::map<std::string, std::set<NodeId> >& coveredNodes, std::set<std::string>& needToSkip)
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("detectClones()");

      common::timestat time = common::getProcessUsedTime();

      size_t sizeBeforePatternFilter, sizeAfterPatternFilter;

      do
      {
        sizeBeforePatternFilter = serializationData.nodeInfoSequence.size();
        common::WriteMsg::write(CMSG_USE_PATTERNFILTER);
        patternFilter();
        sizeAfterPatternFilter = serializationData.nodeInfoSequence.size();
      }
      while (sizeBeforePatternFilter != sizeAfterPatternFilter);

      config.stat.serializedASGLengthFiltered = serializationData.nodeInfoSequence.size();

      common::WriteMsg::write(CMSG_DETECTING_CLONES);
/*
      // DEBUG
      printf("Serialized AST:\n");
      for (auto nk : serializationData.nodeKindSequence)
        printf("%d ", nk);
      printf("\n");

      {
        ofstream serializedFstream("Serialized.dat", std::ios_base::binary);
        for (auto nk : serializationData.nodeKindSequence)
          serializedFstream.write((char*)&nk, sizeof(nk));
      }
*/


      time = common::getProcessUsedTime();

      std::map<std::string, unsigned int> clone_counter;
      Sequence<int> sequence(serializationData.nodeKindSequence);

      LinearSuffixArray<int> suffixArray(sequence);
      common::WriteMsg::write(CMSG_CLONE_DETECTION_DONE_IN, common::getProcessUsedTime().user - time.user);
      common::WriteMsg::write(CMSG_GENERATING_CLONE_INSTANCES);

      perfSectionHandler.addTimeStamp("clone detection");

      time = common::getProcessUsedTime();
      LinearSuffixArray<int>::Duplicateiterator lduplicateIterator = suffixArray.iterator( config.minAsgNodes, 0, 0, true);

      ProcessCC processCC;

      processCC.clone_counter = &clone_counter;
      processCC.dcm = this;
      processCC.maxCCSize = config.maxCCSize;
      processCC.needToSkip = &needToSkip;


      processCC.addFilter(std::make_shared<CloneOccuranceFilter>(config.minOccur));
      processCC.addFilter(std::make_shared<CloneLengthFilter>(config.minLines));
      processCC.addFilter(std::make_shared<RepeatingLinesFilter>(*this));
      if (statementFilter)
        processCC.addFilter(std::make_shared<StatementFilter>(*this));



      lduplicateIterator.run(processCC);

      updateMemoryStat(config);
      common::WriteMsg::write(CMSG_PROBALBLY_CLONES_FOUND);
      processCC.buildCloneInstances();

      common::WriteMsg::write(CMSG_DONE_IN, common::getProcessUsedTime().user - time.user);

      config.stat.cloneFindTime += common::getProcessUsedTime().user - time.user;


      time = common::getProcessUsedTime();
      perfSectionHandler.addTimeStamp("clone instances");
      updateMemoryStat(config, "Clone instances are built");

      //calculating coverage
      if (config.metrics)
      {
        time = common::getProcessUsedTime();
        updateMemoryStat(config);
        common::WriteMsg::write(CMSG_COMPUTING_COVERED_NODES);
        computeCoveredNodes();
        perfSectionHandler.addTimeStamp("computeCoveredNodes");
        computeCoveredLines();
        perfSectionHandler.addTimeStamp("computeCoveredLines");
        updateMemoryStat(config);
        common::WriteMsg::write(CMSG_DONE_D);
        config.stat.calculateMetricsTime += common::getProcessUsedTime().user - time.user;
        perfSectionHandler.addTimeStamp("clone coverage containers");
      }
    }

    void DuplicatedCodeMiner::computeCoveredNodes()
    {
      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIt != currentSystem->getCloneClassesListIteratorEnd();++cloneClassIt)
      { //clone class
        const genealogy::CloneClass& cc = *cloneClassIt;
        if (cc.getIsVirtual())
          continue;
        unsigned int length =  lengths[cc.getId()];
        for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt)
        { //clone instance
          const genealogy::CloneInstance& ci = *cloneInstanceIt;
          unsigned int pos = positions[ci.getId()];
          for(unsigned int i = 0; i < length; ++i)
          {
            const ASTNodeInfo* position = getNode(pos + i);
            if(position)
            {
              const string componentName = getComponentName(position->getLimComponentId(),*limFact);
              map<std::string, std::set<columbus::NodeId> >::iterator coverageIt = coveredNodes.find(componentName);

              if(coverageIt == coveredNodes.end())
              {
                set<NodeId> nodeSet;
                nodeSet.insert(position->getId());
                coveredNodes.insert(make_pair(componentName, nodeSet));
              }
              else
              {
                (coverageIt->second).insert(position->getId());
              }
            }
          }
        } //clone instances
      } // clone classes
    }

    void DuplicatedCodeMiner::computeCoveredLines()
    {
      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIt != currentSystem->getCloneClassesListIteratorEnd();++cloneClassIt)
      {
        const genealogy::CloneClass& cc = *cloneClassIt;
        if (cc.getIsVirtual())
          continue;

        for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt)
        {
          const genealogy::CloneInstance& ci = *cloneInstanceIt;
          std::string path =  ci.getPath();
            unsigned int pos = positions[ci.getId()];
          if (ci.getRootBegin() && serializationData.nodeInfoSequence[pos] )
          {
            columbus::lim::asg::logical::Member& node = (columbus::lim::asg::logical::Member&)limFact->getRef((serializationData.nodeInfoSequence [pos]->getLimNodeId()));

            if ( columbus::lim::asg::Common::getIsClass(node) 
              || columbus::lim::asg::Common::getIsMethod(node)
              || columbus::lim::asg::Common::getIsPackage(node)
              || columbus::lim::asg::Common::getIsComponent(node))
            {
                if (!node.getIsContainedInIsEmpty()) {
                  path = columbus::lim::asg::Common::getFullPath (*node.getIsContainedInListIteratorAssocBegin());
                }
            }
          }
          LowerStringOnWindows(path);
          Key fileId = limFact->getStringTable().set(path);
          
          for(unsigned int i = ci.getLine(); i <= ci.getEndLine(); ++i)
            coveredLines.insert(LineIdentifier(fileId,i));
        }
      }
    }

    void DuplicatedCodeMiner::buildBaseCloneTree()
    {
      common::timestat time = common::getProcessUsedTime();
      common::WriteMsg::write(CMSG_BUILD_CLONE_TREE);

      columbus::genealogy::System& lastSystemRef = *currentSystem;
      columbus::graph::Node        cloneRootNode = graph.findNode(graphsupport::graphconstants::UID_CLONE_ROOT);

      for (auto groupsIter = lastSystemRef.getCloneClassesListIteratorBegin(); groupsIter != lastSystemRef.getCloneClassesListIteratorEnd(); ++groupsIter)
      { // clone classes
        auto& cc = const_cast<columbus::genealogy::CloneClass&>(*groupsIter);
        std::set<NodeId> componentsOfTheClass;  // Container to store the components of all the corresponding clone instance nodes

        columbus::graph::Node classItem = graph.findNode(getGraphNameOfGenelogyNode(cc));
        if (classItem == columbus::graph::Graph::invalidNode)
        {
          classItem = graph.createNode(getGraphNameOfGenelogyNode(cc), columbus::graph::Node::NodeType(graphsupport::graphconstants::NTYPE_DCF_CLONECLASS));
          graph.createDirectedEdge(cloneRootNode, classItem, graphsupport::graphconstants::ETYPE_DCF_CLONETREE, true);
        }

        // first deal with clone instances
        for (auto itemsIter = cc.getItemsListIteratorBegin(); itemsIter != cc.getItemsListIteratorEnd(); ++itemsIter)
        {
          auto& ci = const_cast<columbus::genealogy::CloneInstance&>(*itemsIter);
          std::list<columbus::graph::Node> nodes;

          columbus::graph::Node instanceItem = graph.findNode(getGraphNameOfGenelogyNode(ci));
          if(instanceItem == columbus::graph::Graph::invalidNode)
          {
            instanceItem = graph.createNode(getGraphNameOfGenelogyNode(ci), columbus::graph::Node::NodeType(graphsupport::graphconstants::NTYPE_DCF_CLONEINSTANCE));
            graph.createDirectedEdge(classItem, instanceItem, graphsupport::graphconstants::ETYPE_DCF_CLONETREE, true);
            columbus::graphsupport::addPositionAttribute(graph, instanceItem, ci.getPath(), ci.getLine(), ci.getCol(), ci.getEndLine(), ci.getEndCol());
          }

          std::map<NodeId,std::set<NodeId> >::iterator itLimNodes          = limNodeCloneInstanceMap.find(ci.getId());
          std::map<NodeId,std::set<NodeId> >::iterator itLimComponent      = limComponentCloneInstanceMap.find(ci.getId());

          if (itLimNodes != limNodeCloneInstanceMap.end())
          {
            std::set<columbus::NodeId>& nodes = itLimNodes->second;
            for (auto LimNodeId  : nodes)
            {
              std::string gaphNodeUUid = columbus::lim2graph::VisitorGraphConverter::determineNodeName(limFact->getRef(LimNodeId));
              columbus::graph::Node theItem = graph.findNode(gaphNodeUUid);
              if (theItem != columbus::graph::Graph::invalidNode)
                graph.createDirectedEdge(theItem, instanceItem, graphsupport::graphconstants::ETYPE_DCF_HASCLONE, true);
              else
              {
                common::WriteMsg::write(WriteMsg::mlWarning, "The source code element (uuid: %s) is not found for clone instance (id: %d)!\n", gaphNodeUUid.c_str(), ci.getId());
              }
            }
          }

          // Create the component edges of the clone instance nodes
          if (itLimComponent != limComponentCloneInstanceMap.end())
          {
            const std::set<NodeId >& componentsOfTheInstance = itLimComponent->second;
            for (auto componentId  : componentsOfTheInstance)
            {
              std::string gaphNodeUUid =  columbus::lim2graph::VisitorGraphConverter::determineNodeName(limFact->getRef(componentId));
              columbus::graph::Node theCommponent = graph.findNode(gaphNodeUUid);
              if (theCommponent != columbus::graph::Graph::invalidNode)
                graph.createDirectedEdge(instanceItem, theCommponent, graphsupport::graphconstants::ETYPE_LIM_COMPONENT, true);
              else
              {
                common::WriteMsg::write(WriteMsg::mlWarning,"The commponent (uuid: %s) is not found for clone instance %d (id: %d)!\n", gaphNodeUUid.c_str(), ci.getId());
              }
            }

            // Adding the components of the instance to the component set of the clone class
            componentsOfTheClass.insert(componentsOfTheInstance.begin(), componentsOfTheInstance.end());
          }
        } //loop clone instance

          // deal with clone classes
        // Create the component edges of the clone class nodes
        for (auto componentId : componentsOfTheClass)
        {
          std::string gaphNodeUUid =  columbus::lim2graph::VisitorGraphConverter::determineNodeName(limFact->getRef(componentId));
          columbus::graph::Node theComponent = graph.findNode(gaphNodeUUid);
          graph.createDirectedEdge(classItem, theComponent, graphsupport::graphconstants::ETYPE_LIM_COMPONENT, true);
        }
      }

      common::WriteMsg::write(CMSG_DONE_D);
      config.stat.buildCloneTreeTime += common::getProcessUsedTime().user - time.user;
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


    int DuplicatedCodeMiner::serializeAsg(bool createComponent)
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("serializeAsg()");

      common::timestat serializeTime = common::getProcessUsedTime();
      int exit_code = EXIT_SUCCESS;

      serializationData.nodeKindSequence.clear();
      clearNodeIdSequence(serializationData.nodeInfoSequence);
      serializationData.referencesMap.clear();
      serializationData.inverseReferencesMap.clear();

            
      delete theCloneVisitor;
      theCloneVisitor = new CppCloneVisitor(limOrigin, limFact);
      
      theCloneVisitor->setFilterLogStream(filterOut);
      
      //TODO :  fileNamesByComponent üres...
      if (createComponent) {
        theCloneVisitor->setFileNamesByComponent(&fileNamesByComponent);
        theCloneVisitor->setTuPathToCompAndTuId(&tuPathToCompAndTuId);
      } else {
        theCloneVisitor->setFileNamesByComponent(NULL);
      }
      
      double numberOfComponents = config.files.size();
      int componentCounter = 0;
      for  (auto& componentFileName : config.files)
      {
        ++componentCounter;
        std::string componenetID = componentFileName.c_str();

        if (createComponent) {
          // create component to genealogy
          columbus::genealogy::Component* componentRef=genealogyFact->createComponentNode();
          componentRef->setLocation(componentFileName);
          componentRef->setName(componenetID);
          currentSystem->addComponents(componentRef);
          //calculate hash
          //std::size_t hash = currentFactory.calculateHash(currentFactory.operator ()(fname), fname);
          //componentRef->setCode(hash);
        }
        NodeId limComponentId = getLimComponenetIdByName(componenetID,*limFact);
        list<string> compilationUnitsList;
        loadStringListFromFile(componentFileName, compilationUnitsList);

        compilationUnitsList.remove_if([](const string& fileName) { return common::pathFindExtension(fileName) != "ast"; });

        common::WriteMsg::write(CMSG_LOADING_CPP_COMPONENT, componentCounter / numberOfComponents, compilationUnitsList.size(), componentFileName.c_str());
        common::WriteMsg::write(CMSG_CURRENT_COMPONENT_ID, limComponentId);

        //filter
        std::map<std::string, std::set<columbus::NodeId> >::iterator it = filteredNodes.find(componenetID);
        if(it != filteredNodes.end()) {
          theCloneVisitor->setFilter(it->second);
        } else {
          theCloneVisitor->clearFilter();
        }
        theCloneVisitor->resetVisitedNodesNumber();
        theCloneVisitor->setCurrentLimComponent(limComponentId);
        theCloneVisitor->serializeComponent(compilationUnitsList, serializationData);

        serializedAsgNodeNumberByComponenet[componenetID] = theCloneVisitor->getVisitedNodesNumber();
        config.stat.totalASTNodeNumber += theCloneVisitor->getVisitedNodesNumber();
        updateMemoryStat(config, "Component Loaded");

/*
        // Debug
        printf("Sizes referencesMap: %lu\n", serializationData.referencesMap.size());
        size_t sum = 0;
        for (const auto& m : serializationData.referencesMap)
          sum += m.second.size();
        printf("    maps sum: %lu\n", sum);

        printf("Sizes nodeReferencePathMap: %lu\n", serializationData.nodeReferencePathMap.size());
        sum = 0;
        for (const auto& m : serializationData.nodeReferencePathMap)
          sum += m.second.size();
        printf("    maps sum: %lu\n", sum);
*/

/*
        // Debug
        printf("Last separator: %d\n", theCloneVisitor->getSeparator());
*/
      }

      config.stat.asgSerializationTime += common::getProcessUsedTime().user - serializeTime.user;
      return exit_code;
    }

    int DuplicatedCodeMiner::dcminer() {
      bool errorAtLoad = false;

      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("dcminer()");

      //creating the genealogy graph
      genealogy::Project& genealogyBase = initGenealogy(errorAtLoad);
      updateMemoryStat(config);
      set<string> needToSkip;

      int exit_code = EXIT_SUCCESS;

      if (!initLim())
        return EXIT_FAILURE;

      updateMemoryStat(config);


      bool first = false;
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
        updateMemoryStat(config);
        
        limFact->turnFilterOn();
        
        exit_code = serializeAsg(true);
        config.stat.serializedASGLength = serializationData.nodeInfoSequence.size();

/*
        // Debug
        printf("Serialized AST:\n");
        for (const auto& n: serializationData.nodeInfoSequence)
        {
          if (n)
          {
            n->dump();
            const auto& refmap = serializationData.referencesMap[n->getTUPath()];
            auto it = refmap.find(n->getId());
            if (it != refmap.end())
              printf("REF: %d\n", it->second);
          }
        }
*/
        // generate inverse references from the referencesMap
        for (const auto& ASTRefInfo : serializationData.referencesMap)
          for (const auto& reference : ASTRefInfo.second)
              serializationData.inverseReferencesMap[ASTRefInfo.first][reference.second].push_back(reference.first);

/*
        // Debug
        printf("Reference map:\n");
        for (const auto& ASTRefInfo : serializationData.referencesMap)
        {
          printf("AST:%s\n", ASTNodeInfo::getStringPath(ASTRefInfo.first).c_str());
          for (const auto& reference : ASTRefInfo.second)
            printf("   %u -> %u\n", reference.first, reference.second);
        }

        // Debug
        printf("Inverse reference map:\n");
        for (const auto& ASTRefInfo : serializationData.inverseReferencesMap)
        {
          printf("AST:%s\n", ASTNodeInfo::getStringPath(ASTRefInfo.first).c_str());
          for (const auto& reference : ASTRefInfo.second)
          {
            printf("   %u -> ", reference.first);
            for (const auto& ref : reference.second)
              printf("%u ", ref);
            printf("\n");
          }
        }
        // Debug
        printf("Reference map:\n");
        for (const auto& ASTRefInfo : serializationData.referencesMap)
        {
          printf("AST:%s\n", ASTNodeInfo::getStringPath(ASTRefInfo.first).c_str());
          for (const auto& reference : ASTRefInfo.second)
            printf("   %s -> %s\n", ASTNodeInfo::getStringPath(serializationData.nodeReferencePathMap[ASTRefInfo.first][reference.first]).c_str()
                                  , ASTNodeInfo::getStringPath(serializationData.nodeReferencePathMap[ASTRefInfo.first][reference.second]).c_str());
        }

*/

/*
        // Debug
        printf("Sizes referencesMap: %lu\n", serializationData.referencesMap.size());
        size_t sum = 0;
        for (const auto& m : serializationData.referencesMap)
          sum += m.second.size();
        printf("    maps sum: %lu\n", sum);

        printf("Sizes inverseReferencesMap: %lu\n", serializationData.inverseReferencesMap.size());

        sum = 0;
        int oneref = 0;
        int multipleref = 0;
        for (const auto& m : serializationData.inverseReferencesMap)
        {
          sum += m.second.size();
          for (const auto& s : m.second)
          {
            if (s.second.size() == 1)
              ++oneref;
            else
              ++multipleref;
          }
        }

        printf("    number of sets: %lu\n  1: %d\n  *: %d\n", sum, oneref, multipleref);

        printf("Sizes nodeReferencePathMap: %lu\n", serializationData.nodeReferencePathMap.size());
        sum = 0;
        for (const auto& m : serializationData.nodeReferencePathMap)
          sum += m.second.size();
        printf("    maps sum: %lu\n", sum);
*/
        detectClones(coveredNodes, needToSkip);
        updateMemoryStat(config);

        if (config.maxCCSize) {
          for (const auto& needToSkipFile :needToSkip)
          {
            if (needToSkipFile.empty())
              continue;

            common::WriteMsg::write(CMSG_ADDING_PATH_TO_FILTER, needToSkipFile.c_str());
            config.bpaths.push_back(needToSkipFile);
          }
        }

      } while (config.maxCCSize && needToSkip.size()>0 && first);

      
      updateMemoryStat(config);
      columbus::lim2graph::convertBaseGraph(*limFact, graph, true, true, /*components=*/ true, /*variants=*/ true);
      //cout << "Graph converting took: " << common::getProcessUsedTime().user - time.user << endl;

      updateMemoryStat(config);
      columbus::graph::Node cloneRootNode = graph.createNode(graphsupport::graphconstants::UID_CLONE_ROOT, columbus::graph::Node::NodeType(graphsupport::graphconstants::NTYPE_ROOT));
      graphsupport::addNodeNameAttribute(graph, cloneRootNode,graphsupport::graphconstants::UID_CLONE_ROOT);
      graphsupport::addNodeLongNameAttribute(graph, cloneRootNode,graphsupport::graphconstants::UID_CLONE_ROOT);

      updateMemoryStat(config);
      buildBaseCloneTree();
      perfSectionHandler.addTimeStamp("buildBaseCloneTree");


      if (config.metrics)
        calculateMetrics();

      updateMemoryStat(config);
      
      //generating evolution mapping
      if(!errorAtLoad && !config.genealogyFilename.empty())
      {
        evolutionMapping(*currentSystem, genealogyBase);
      }

      setClonesUniqueNameAndCloneSmells();

      // turn on graph indexer and build  index
      indexer = &columbus::graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance();
      indexer->turnOn(graph);

      if (config.metrics)
      {
        calculateEvolutionDependentMetrics();
        addDefaultMetricsForTheNodes();
      }
      clearNodeIdSequence(serializationData.nodeInfoSequence);
      serializationData.nodeKindSequence.clear();

      return exit_code;
    }

    void DuplicatedCodeMiner::addDefaultMetricsForTheNodes()
    {
      std::map<string, std::set<string>> nodeTypeMetricMap;
      std::vector<string> metrics;

      rulHandler->getRuleIdList(metrics);

      for (const auto& metric : metrics)
        for (const auto& Item : rulHandler->getCalculatedForSet(metric))
          nodeTypeMetricMap[Item].insert(metric);
/*
      // DEBUG
      for (const auto& item : nodeTypeMetricMap)
      {
        printf("Item:%s\n", item.first.c_str());
        for (const auto& metric: item.second)
        {
          printf(" Metric:%s\n", metric.c_str());
        }
      }
*/
      auto nodeIt = graph.getNodes();
      while (nodeIt.hasNext())
      {
          auto node = nodeIt.next();
          auto nodeMapIt = nodeTypeMetricMap.find(node.getType().getType());
          if (nodeMapIt != nodeTypeMetricMap.end())
          {
/*
            // DEBUG
            printf("Node:%s Type:%s\n", node.getUID().c_str(), node.getType().getType().c_str());
*/


            if (graphsupport::getRealizationLevel(node) == graphsupport::graphconstants::ATTRVALUE_LIM_RELDECLARES)
            {
              for (const auto& metric : nodeMapIt->second)
              {
                auto attributeIterator = node.findAttributeByName(metric);
                if (!attributeIterator.hasNext())
                  graphsupport::setMetricINVALID(graph, node, metric);
              }

            }
            else
            {
              for (const auto& metric : nodeMapIt->second)
              {
                auto attributeIterator = node.findAttributeByName(metric);
                if (!attributeIterator.hasNext())
                {
                  // The metric is missing from the node
                  if ((metric == "CA") && getIsNeeded(metric))
                    graphsupport::setMetricInt(graph, node, "CA", 0);

                  else if ((metric == "CCL") && getIsNeeded(metric))
                    graphsupport::setMetricInt(graph, node, "CCL", 0);

                  else if ((metric == "CCO") && getIsNeeded(metric))
                    graphsupport::setMetricInt(graph, node, "CC", 0);

                  else if ((metric == "CC") && getIsNeeded(metric))
                    graphsupport::setMetricFloat(graph, node, "CC", 0.0);

                  else if ((metric == "CEE") && getIsNeeded(metric))
                    graphsupport::setMetricFloat(graph, node, "CEE", 0.0);

                  else if ((metric == "CEG") && getIsNeeded(metric))
                    graphsupport::setMetricFloat(graph, node, "CEG", 0.0);

                  else if ((metric == "CE") && getIsNeeded(metric))
                    graphsupport::setMetricFloat(graph, node, "CE", 0.0);

                  else if ((metric == "CI") && getIsNeeded(metric))
                    graphsupport::setMetricInt(graph, node, "CI", 0);

                  else if ((metric == "CLC") && getIsNeeded(metric))
                    graphsupport::setMetricFloat(graph, node, "CLC", 0.0);

                  else if ((metric == "CLLOC") && getIsNeeded(metric))
                    graphsupport::setMetricInt(graph, node, "CLLOC", 0);

                  else if ((metric == "CLLC") && getIsNeeded(metric))
                    graphsupport::setMetricInt(graph, node, "CLLC", 0);

                  else if ((metric == "CR") && getIsNeeded(metric))
                    graphsupport::setMetricFloat(graph, node, "CR", 0.0);

                  else if ((metric == "CV") && getIsNeeded(metric))
                    graphsupport::setMetricFloat(graph, node, "CV", 0.0);

                  else if ((metric == "LDC") && getIsNeeded(metric))
                    graphsupport::setMetricInt(graph, node, "LDC", 0);

                  else if ((metric == "LLDC") && getIsNeeded(metric))
                    graphsupport::setMetricInt(graph, node, "LLDC", 0);

                  else if ((metric == "NCR") && getIsNeeded(metric))
                    graphsupport::setMetricFloat(graph, node, "NCR", 0.0);

                }
              }
            }
          }
      }


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
      // load back asg for evolution mapping
      common::timestat time = common::getProcessUsedTime();

      common::WriteMsg::write(CMSG_START_EVOLUTION_MAPPING);
      updateMemoryStat(config);


      vector<genealogy::CloneInstance*> instancesOfTheCurrentSystem = getInstancesOfaSystem(systemRef);
      unsigned numberOfInstancesInTheRefSystem = instancesOfTheCurrentSystem.size();
      //Sort instances by translation unit id
      std::sort(instancesOfTheCurrentSystem.begin(), instancesOfTheCurrentSystem.end(), [this](genealogy::CloneInstance* struct1, genealogy::CloneInstance* struct2){
          return ( tuPathToCompAndTuId[ciIdToAST[struct1->getId()]].second < tuPathToCompAndTuId[ciIdToAST[struct2->getId()]].second );
      });
      
      std::sort(instancesOfTheCurrentSystem.begin(), instancesOfTheCurrentSystem.end(), sortCloneInstancesByComponentId());

      // calculate the similarity attributes for all instances
      for (vector<genealogy::CloneInstance*>::iterator currentInsatnceIt = instancesOfTheCurrentSystem.begin(); currentInsatnceIt != instancesOfTheCurrentSystem.end();++currentInsatnceIt) {
        genealogy::CloneInstance* instanceOfTheCurentSystem = *currentInsatnceIt;
        
        computeSimilarityAttributes(*instanceOfTheCurentSystem);
      }
      

      updateMemoryStat(config);
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
            common::WriteMsg::write(WriteMsg::mlDDDDebug, "Similarity of %d(last) and %d(current): %f\n", instanceOfTheLastSystem->getId(), instanceOfTheCurentSystem->getId(), sim);
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

          updateMemoryStat(config);

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

          updateMemoryStat(config);
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
        }
        catch (std::bad_alloc&)
        {
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
          clearNodeIdSequence(serializedAsgMapIt->second.nodeInfoSequence);
        }
        serializedAsgMap.clear();
        common::WriteMsg::write(CMSG_DONE_D);

      }

      updateMemoryStat(config);

      config.stat.evolutionMappingTime = common::getProcessUsedTime().user - time.user;
      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Evolution mapping took %d (1/100s)\n", config.stat.evolutionMappingTime);
    }


    void DuplicatedCodeMiner::setClonesUniqueNameAndCloneSmells()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("setClonesUniqueNameAndCloneSmells()");
      common::timestat time = common::getProcessUsedTime();

      unsigned uniqueId = 0;
      if (lastSystem != NULL)
        uniqueId = lastSystem->getFirstFreeID();

      columbus::genealogy::System& currentSystemRef=*currentSystem;
      for (auto classItemsIter = currentSystemRef.getCloneClassesListIteratorBegin(); classItemsIter != currentSystemRef.getCloneClassesListIteratorEnd(); ++classItemsIter)
      {
        columbus::genealogy::CloneClass& classItem = const_cast<columbus::genealogy::CloneClass&>(*classItemsIter);
        if (classItem.getIsVirtual())
          continue;

        const columbus::genealogy::CloneClass* prevClass = &classItem;

        if (!classItem.getPrevIsEmpty())
        {
          columbus::genealogy::ListIterator<columbus::genealogy::Trackable> prevIter = classItem.getPrevListIteratorEnd() ;
          --prevIter;
          prevClass =  dynamic_cast<const columbus::genealogy::CloneClass*>(&(*prevIter));
        }

        auto cloneClassGraphNode = graph.findNode(getGraphNameOfGenelogyNode(classItem));

        //if the clone class is new 
        if (prevClass == &classItem)
        {
          std::string id = to_string(uniqueId++);
          classItem.setUniqueName(id + "~CloneClass");

          if (currentSystemRef.getAge() > 1)
          {
            classItem.setCloneSmellType(columbus::genealogy::cstAppearing);
          }

        }
        else
        {
          classItem.setUniqueName(prevClass->getUniqueName());

          for(auto itemsIter = prevClass->getItemsListIteratorBegin(); itemsIter != prevClass->getItemsListIteratorEnd(); ++itemsIter)
          {
            columbus::genealogy::CloneInstance& cloneInstance = const_cast<columbus::genealogy::CloneInstance&>(*itemsIter);
            if (itemsIter->getNextSize() == 0 && !cloneInstance.getIsVirtual())
            {
              columbus::genealogy::CloneInstance* cloneInstanceNext = cloneInstance.getFactory().createCloneInstanceNode();
              cloneInstanceNext->setCloneClass(&classItem);
              cloneInstanceNext->setIsVirtual(true);
              cloneInstanceNext->setUniqueNameKey(cloneInstance.getUniqueNameKey());
              cloneInstanceNext->setCloneSmellType(columbus::genealogy::cstDisappearing);
              cloneInstanceNext->addPrev(cloneInstance.getId());
              cloneInstanceNext->setPath(cloneInstance.getPath());
              cloneInstanceNext->setLine(cloneInstance.getLine());
              cloneInstanceNext->setEndLine(cloneInstance.getEndLine());
              cloneInstanceNext->setCol(cloneInstance.getCol());
              cloneInstanceNext->setEndCol(cloneInstance.getEndCol());

              cloneInstance.addNext(cloneInstanceNext);
              classItem.addItems(cloneInstanceNext);

              auto cloneInstanceGraphNode = graph.createNode(getGraphNameOfGenelogyNode(*cloneInstanceNext), columbus::graph::Node::NodeType(graphsupport::graphconstants::NTYPE_DCF_CLONEINSTANCE));
              graph.createDirectedEdge(cloneClassGraphNode, cloneInstanceGraphNode, graphsupport::graphconstants::ETYPE_DCF_CLONETREE, true);
              columbus::graphsupport::addPositionAttribute(graph, cloneInstanceGraphNode, cloneInstance.getPath(), cloneInstance.getLine(), cloneInstance.getCol(), cloneInstance.getEndLine(), cloneInstance.getEndCol());
            }
          }
        }

        graphsupport::addNodeNameAttribute(graph, cloneClassGraphNode, classItem.getUniqueName());
        graphsupport::setStringAttribute(graph, cloneClassGraphNode, graphsupport::graphconstants::ATTR_DCF_CLONESMELLTYPE, genealogy::Common::toString(classItem.getCloneSmellType()));

        // Set the clone smells of the clone instances
        for (auto itemsIter = classItemsIter->getItemsListIteratorBegin(); itemsIter != classItemsIter->getItemsListIteratorEnd(); ++itemsIter)
        {
          columbus::genealogy::CloneInstance& instance = const_cast<columbus::genealogy::CloneInstance&>(*itemsIter);

          auto cloneInstanceGraphNode = graph.findNode(getGraphNameOfGenelogyNode(instance));
          if (instance.getPrevIsEmpty())
          {
            std::string id = to_string(uniqueId++);
            instance.setUniqueName(id + "~CloneInstance");

            if (classItem.getCloneSmellType() == columbus::genealogy::cstNone)
              if (!instance.getCloneClass()->getPrevIsEmpty())
                instance.setCloneSmellType(columbus::genealogy::cstAppearing);
          }
          else
          {
            if (!instance.getIsVirtual())
            {
              const columbus::genealogy::CloneInstance& prev = dynamic_cast<const columbus::genealogy::CloneInstance&>(*instance.getPrevListIteratorBegin());
              instance.setUniqueNameKey(prev.getUniqueNameKey());

              if (classItem.getCloneSmellType() == columbus::genealogy::cstNone)
              {
                if (prev.getCloneClass()->getUniqueNameKey() == instance.getCloneClass()->getUniqueNameKey())
                {
                  instance.setCloneSmellType(columbus::genealogy::cstNone);
                }
                else
                {
                  if (prev.getCloneClass()->getNextSize() > 0 )
                    instance.setCloneSmellType(columbus::genealogy::cstMoving);
                  else
                    instance.setCloneSmellType(columbus::genealogy::cstNone);
                }
              }
            }
          }

          graphsupport::addNodeNameAttribute(graph, cloneInstanceGraphNode, instance.getUniqueName());
          graphsupport::setStringAttribute(graph, cloneInstanceGraphNode, graphsupport::graphconstants::ATTR_DCF_CLONESMELLTYPE, genealogy::Common::toString(instance.getCloneSmellType()));

        }
      }

      // build virtual clone class
      if (currentSystem->getPrev())
      {
        columbus::genealogy::System& pervSystemRef = *currentSystem->getPrev();

        for (auto groupIter = pervSystemRef.getCloneClassesListIteratorBegin(); groupIter != pervSystemRef.getCloneClassesListIteratorEnd(); ++groupIter)
        {
          columbus::genealogy::CloneClass& classItem = const_cast<columbus::genealogy::CloneClass&>(*groupIter);
          if (classItem.getIsVirtual())
            continue;

          if (groupIter->getNextIsEmpty())
          {
            columbus::genealogy::CloneClass* cloneClassVirtual = classItem.getFactory().createCloneClassNode();
            currentSystem->addCloneClasses(cloneClassVirtual);
            cloneClassVirtual->setUniqueNameKey(classItem.getUniqueNameKey());
            cloneClassVirtual->setIsVirtual(true);
            cloneClassVirtual->setCloneSmellType(columbus::genealogy::cstDisappearing);

            auto cloneClassGraphNode = graph.createNode(getGraphNameOfGenelogyNode(*cloneClassVirtual), columbus::graph::Node::NodeType(graphsupport::graphconstants::NTYPE_DCF_CLONECLASS));
            graph.createDirectedEdge(graph.findNode(graphsupport::graphconstants::UID_CLONE_ROOT), cloneClassGraphNode, graphsupport::graphconstants::ETYPE_DCF_CLONETREE, true);
            graphsupport::addNodeNameAttribute(graph, cloneClassGraphNode, cloneClassVirtual->getUniqueName());
            graphsupport::setStringAttribute(graph, cloneClassGraphNode, graphsupport::graphconstants::ATTR_DCF_CLONESMELLTYPE, genealogy::Common::toString(cloneClassVirtual->getCloneSmellType()));

            for(auto  itemsIter = classItem.getItemsListIteratorBegin(); itemsIter != classItem.getItemsListIteratorEnd(); ++itemsIter)
            {
              columbus::genealogy::CloneInstance& cloneInstance= const_cast<columbus::genealogy::CloneInstance&>(*itemsIter);

              if (cloneInstance.getNextIsEmpty()) {
                columbus::genealogy::CloneInstance* cloneInstanceNext = cloneInstance.getFactory().createCloneInstanceNode();
                cloneClassVirtual->addItems(cloneInstanceNext);
                cloneInstanceNext->setCloneClass(&classItem);
                cloneInstanceNext->setIsVirtual(true);
                cloneInstanceNext->setUniqueNameKey(cloneInstance.getUniqueNameKey());
                cloneInstanceNext->setCloneSmellType(columbus::genealogy::cstNone);
                cloneInstanceNext->addPrev(cloneInstance.getId());
                cloneInstanceNext->setPath(cloneInstance.getPath());
                cloneInstanceNext->setLine(cloneInstance.getLine());
                cloneInstanceNext->setEndLine(cloneInstance.getEndLine());
                cloneInstanceNext->setCol(cloneInstance.getCol());
                cloneInstanceNext->setEndCol(cloneInstance.getEndCol());

                cloneInstance.addNext(cloneInstanceNext);
              }
            }
          }
        }
      }
      currentSystem->setFirstFreeID(uniqueId);

      updateMemoryStat(config);
      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Generating unique names took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }


    void DuplicatedCodeMiner::createBackup(const std::string& backup)
    {

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
    }

    void DuplicatedCodeMiner::saveGenealogy() {

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
    }

    bool DuplicatedCodeMiner::isASGNode(unsigned int sequencePosition) const {
      return (serializationData.nodeInfoSequence.at(sequencePosition)!=NULL);
    }

    const ASTNodeInfo* DuplicatedCodeMiner::getNode(unsigned int sequencePosition) const {
      return serializationData.nodeInfoSequence.at(sequencePosition);
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

    std::string DuplicatedCodeMiner::computeCloneClassCode(unsigned int pos, unsigned int length)
    {
      std::string s("CLONE");

      for (unsigned int i = 0; i < length; i++)
        s.append(to_string(getNodeKindAt(pos + i)));

      auto hashCode = hash<std::string>()(s);
      return to_string(hashCode);
    }

    void DuplicatedCodeMiner::alignCloneClass(Aligner::AlignKind alignKind, const SuffixArray<int>::CloneClass& suffixCl, CloneClassPotentialCloneInstanceMap& potentialCloneInstances)
    {
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
        std::list<std::shared_ptr<Interval>> intervals;
        for (unsigned int i=0; i<length; i++) {
          int currentNodeKind=getNodeKindAt(oneOccurance+i);
          if (isDecDepthSign(currentNodeKind)) {
            if (!offset.empty()) {
              unsigned int lastOffset=offset.top();
              if ((i - lastOffset) > config.minAsgNodes || !config.singleAsgRoot) {
                auto I = std::make_shared<Interval>(lastOffset, i);

                list<std::shared_ptr<Interval>>::iterator iter=intervals.begin();
                while (iter != intervals.end())
                {
                  // removing contained intervals
                  auto current=(*iter);
                  if (*current <= *I)
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
          for(list<std::shared_ptr<Interval>>::iterator it1 = intervals.begin(), it2 = it1++; it1 != intervals.end() && it2 != intervals.end();) {
            if((*it1)->b == (*it2)->a - 1 ) {
              (*it1)->b = (*it2)->b;
              if((*it2)->intervals == NULL) {
                delete (*it1)->intervals;
                (*it1)->intervals = new vector<unsigned int>();
              } else {
                (*it1)->intervals = (*it2)->intervals;
              }
              (*it1)->intervals->push_back((*it2)->a);
              (*it2)->intervals = NULL;
              intervals.erase(it2);
            }
            it2 = it1++;
          }
        }

        // create clone classes

        list<std::shared_ptr<Interval>>::iterator iter = intervals.begin();
        while (iter!=intervals.end()) {
          auto I=*iter;
          iter++;
          unsigned intervalLength = I->b - I->a + 1;
          if (intervalLength < config.minAsgNodes) {
            common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ_5,intervalLength);
            continue;
          }


          bool isNew = true;
          
          genealogy::CloneClass* cc = createCloneClass(oneOccurance + I->a, intervalLength, isNew);
          common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ_3,cc->getId());
          for (unsigned posIt = 0; posIt <  suffixCl.num; ++posIt) {
            PotentialCloneInstance potI(instances[posIt], I);
            //potI.dump();
            potentialCloneInstances[cc->getId()].insert(potI);
            // common::WriteMsg::write(CMSG_FUND_REPEATING_SEQ_4,instances[posIt],instances[posIt]+I.a,instances[posIt]+I.b);
            config.stat.numOfpotInstances++;
          }
        }

      }//end Syntax Boundary
     
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

        // The fingerprint is set only after the filtering stage as strings are not deleted from the stringtable when the nodes are deleted.
        cloneClassFingerprintMap[cloneClass->getId()] = code;
        cloneClass->setHeadNodeKind(getNodeKindAt(position));
        cloneClass->setType(genealogy::ctkType2);
        lengths[cloneClass->getId()] = length;
        currentSystem->addCloneClasses(cloneClass->getId());
        cloneClassMap.insert(make_pair(code, cloneClass));
      }
      return cloneClass;
    }

    const ASTNodeInfo* DuplicatedCodeMiner::getFirstNode(unsigned int from, unsigned int to) const {
      for(unsigned int pos = from; pos <= to; ++pos) {
        const ASTNodeInfo* nodePos = getNode(pos);
        if(nodePos)
          return nodePos;
      }
      return NULL;
    }

    genealogy::CloneInstance* DuplicatedCodeMiner::createCloneInstance(unsigned int position, unsigned int length, unsigned int intervalStart, vector<unsigned int>* intervals, genealogy::CloneClass& parent)
    {
      const ASTNodeInfo* firstNode = getFirstNode(position, position + length);
      if (!firstNode)
        throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNABLE_TO_DETERMINE_THE_LINE_INFO);

      std::stack<unsigned int> offset;
      unsigned int lastOffset=0;
      bool wasLastOffset=false;

      for(unsigned int i = 0; i < length; ++i)
      {
        int currentNodeKind = getNodeKindAt(position + i);
        if( isDecDepthSign(currentNodeKind) )
        {
          if(!offset.empty()) {
            lastOffset = offset.top();
            wasLastOffset = true;
            offset.pop();
          } else {
            //this node was not part of a whole syntax tree
            //we cannot do anything at this point.
          }
        }
        else
        if (isASGNode(position + i))
        {
          offset.push(i);
        }
      }
      if (!wasLastOffset) {
        if (!offset.empty()) {
          lastOffset=offset.top();
        } else
          throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNABLE_TO_DETERMINE_THE_LINE_INFO);
      }

      const ASTNodeInfo* lastNode=getNode(position+lastOffset);
      if (!lastNode)
        throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNABLE_TO_DETERMINE_THE_LINE_INFO);

      genealogy::CloneInstance& ci = *(genealogyFact->createCloneInstanceNode());
      ci.setLine(firstNode->getLine());
      ci.setCol(firstNode->getCol());
      ci.setEndLine(lastNode->getEndLine());
      ci.setEndCol(lastNode->getEndCol());

      ci.setPath(firstNode->getStringPath().c_str());
      ci.setRootBegin(firstNode->getId());


      std::stringstream cloneInstanceRootNodes;
      cloneInstanceRootNodes << std::hex;
      cloneInstanceRootNodes << std::setw(8);
      cloneInstanceRootNodes << std::setfill('0');
      cloneInstanceRootNodes << firstNode->getId();

      //store into the ciIdToAST map
      ciIdToAST[ci.getId()] = firstNode->getStringTUPath();

      if(intervals ) {
        ci.setRootLength(static_cast<unsigned>(intervals->size())+1);

        std::sort(intervals->begin(),intervals->end());

        for (std::vector<unsigned int>::iterator it = intervals->begin(); it != intervals->end(); ++it) {
          const ASTNodeInfo* nodePos = getNode(intervalStart + *it);
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

      // The root nodes is set only after the filtering stage as strings are not deleted from the stringtable when the nodes are deleted.
      cloneInstanceRootNodesMap[ci.getId()] = cloneInstanceRootNodes.str();

      positions[ci.getId()] = position;

      // set component


      std::string componentNameInTheLimAsg = getComponentName( firstNode->getLimComponentId(),*limFact);
      for (columbus::genealogy::ListIterator<genealogy::Component> componentIt = currentSystem->getComponentsListIteratorBegin();componentIt != currentSystem->getComponentsListIteratorEnd();++componentIt)
      {
        const columbus::genealogy::Component& genealogyComponentNode = *componentIt;
        if (genealogyComponentNode.getName() == componentNameInTheLimAsg)
        {
          ci.setComponent(genealogyComponentNode.getId());
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
        const ASTNodeInfo* nodePos = getNode(position+i);

        if(nodePos) {
          if ((nodePos->getLimNodeId() != 0)  &&
              (lastLimNodeID != nodePos->getLimNodeId()) &&
              (!columbus::lim::asg::Common::getIsPackage(limFact->getRef(nodePos->getLimNodeId()))))
          {
            limNodeCloneInstanceMap[ci.getId()].insert(nodePos->getLimNodeId());
            limComponentCloneInstanceMap[ci.getId()].insert(nodePos->getLimComponentId());
            lastLimNodeID = nodePos->getLimNodeId();
          } 
        }
      }

      updateMemoryStat(config);
      return &ci;
    }

    int DuplicatedCodeMiner::getNodeKindAt(unsigned int position) const {
      return serializationData.nodeKindSequence.at(position);
    }

    bool DuplicatedCodeMiner::getIsNeeded(const string& id) const {
      if (config.metrics)
        return rulHandler->getIsEnabled(id);
      else
        return false;
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

    DuplicatedCodeMiner::~DuplicatedCodeMiner() {
      for (unsigned q=0; q<serializationData.nodeInfoSequence.size(); q++) {
        delete serializationData.nodeInfoSequence[q];
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

    bool DuplicatedCodeMiner::initLim()
    {
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

      class FileSystemVisitor :public columbus::lim::asg::Visitor
      {
      public:
        int maxNDC;

        FileSystemVisitor()
          :maxNDC(0)
        {}

        std::list<std::string> files;

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
            int maxNDC =0;
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


          if (maxDept && maxDept2  && (maxNDC < maxDept+maxDept2)) {
            maxNDC = maxDept2+maxDept;
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
        }
      }

      bool componetOK = true;

      limFact->turnFilterOff();
      return componetOK;
    }

    void DuplicatedCodeMiner::setFilterOut(ostream& out) {
      filterOut = &out;
    }

    void clearNodeIdSequence(std::vector<ASTNodeInfo*>& nodeInfoSequence) {
      for (size_t q=0; q<nodeInfoSequence.size(); q++)
        delete nodeInfoSequence[q];
      nodeInfoSequence.clear();
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
      , trivial_pairs(0)
      , dumpGraphml(false)
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

    const std::string& DuplicatedCodeMiner::getComponentName( columbus::NodeId limId, const columbus::lim::asg::Factory& factory ) const
    {
      const std::string& refEmptyString = limFact->getStringTable().get(limFact->getStringTable().set(""));

      if (limId == 0)
        return refEmptyString;

      if (!factory.getExist(limId))
        return refEmptyString;

      if (lim::asg::Common::getIsComponent(factory.getRef(limId)))
      {
        lim::asg::base::Component& refComp = static_cast<lim::asg::base::Component&> (factory.getRef(limId));
        return refComp.getName();
      }
      return refEmptyString;
    }

    const ASTNodeInfo* DuplicatedCodeMiner::getEndNode( unsigned int from, unsigned int to ) const
    {
      for(unsigned int pos = to; pos >= from; --pos) {
        const ASTNodeInfo* nodePos = getNode(pos);
        if(nodePos)
          return nodePos;
      }
      return NULL;
    }

    int DuplicatedCodeMiner::getCloneInstanceNum() const {
      int ret = 0;
      for(genealogy::ListIterator<genealogy::CloneClass> cloneClassIt = currentSystem->getCloneClassesListIteratorBegin();cloneClassIt != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIt) {
        const genealogy::CloneClass& cc = dynamic_cast<const genealogy::CloneClass&>(*cloneClassIt);
        ret += cc.getItemsSize();
      }
      return ret;
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


    int DuplicatedCodeMiner::getLimNodeDepth(NodeId nodeId)
    {
      auto searchResult = nodeDepthCache.getValue(nodeId);
      if (searchResult.found)
        return searchResult.value;

      NodeId parent = getLimNodeParent(nodeId);
      int depth = 0;
      if (parent != 0)
        depth = getLimNodeDepth(parent) + 1;

      nodeDepthCache.setValue(nodeId, depth);
      return depth;
    }

    /**
      Calculates the CCO - McCabe complexity
    */
    void DuplicatedCodeMiner::calculateCCO()
    {

      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCCO()");
      common::timestat time = common::getProcessUsedTime();

      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        int ClassCCO = 0;
        auto length = lengths[cloneClassIter->getId()];
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          int CCO = 1;
          auto startPosition = positions[cloneInstanceIter->getId()];

          for (size_t index = startPosition; index < startPosition + length; ++index)
          {
            const auto nodeInfo = serializationData.nodeInfoSequence[index];
            const int nodeKind = serializationData.nodeKindSequence[index];
            if (nodeInfo != nullptr)
            {
              if ((nodeKind & NodeMask::NodeTypeMask) == NodeType::Statement)
              {
                switch (nodeKind & NodeMask::NodeKindMask)
                {
                  case clang::Stmt::IfStmtClass:
                  case clang::Stmt::ForStmtClass:
                  case clang::Stmt::CXXForRangeStmtClass:
                  case clang::Stmt::WhileStmtClass:
                  case clang::Stmt::DoStmtClass:
                  case clang::Stmt::CaseStmtClass:
                  case clang::Stmt::CXXCatchStmtClass:
                  case clang::Stmt::ObjCAtCatchStmtClass:
                  case clang::Stmt::ConditionalOperatorClass:
                  case clang::Stmt::BinaryConditionalOperatorClass:
                    ++CCO;
                    break;

                  case clang::Stmt::BinaryOperatorClass:
                    if ((nodeKind & NodeMask::LogicalBOMask) == NodeBOType::LogicalBinaryOperator)
                      ++CCO;
                    break;
                }

              }

            }
          }

          graphsupport::setMetricInt(graph,
                                     getGraphNameOfGenelogyNode(*cloneInstanceIter),
                                     "CCO",
                                     CCO);
          // At the moment there is only constant reference operator for the
          // ListIterator class and it is faster to const_cast it than getting
          // a non const referenc from the factory by its ID.
          const_cast<genealogy::CloneInstance&>(*cloneInstanceIter).setCco(CCO);

          ClassCCO += CCO;
        }

        graphsupport::setMetricInt(graph,
                                   getGraphNameOfGenelogyNode(*cloneClassIter),
                                   "CCO",
                                   ClassCCO);


        // At the moment there is only constant reference operator for the
        // ListIterator class and it is faster to const_cast it than getting
        // a non const referenc from the factory by its ID.
        const_cast<genealogy::CloneClass&>(*cloneClassIter).setCco(ClassCCO);

      }

      // This part is almost perfect clone of the CI metric calculation !!!!!!!!
      // It collects the clone instances for each source code elments

      map</* LIM */ NodeId, set</* GENEALOGY */ NodeId>> sourceCodeElementLimId2CloneInstanceGenelogyIdMap;

      // Calculate the number of clone instances for each source code element
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          const auto& correspondingSourceCodeElements = limNodeCloneInstanceMap[cloneInstanceIter->getId()];
          for (auto limNodeId : correspondingSourceCodeElements)
            sourceCodeElementLimId2CloneInstanceGenelogyIdMap[limNodeId].insert(cloneInstanceIter->getId());
        }
      }

      // Copy the nodeids of the related LIM nodes into a separate container with their depth to prepare them for aggregation
      set<pair</* dpeth of the node in the asg*/ int, NodeId>> cloneRelatedLimNodes;

      for (const auto& sourceCodeElementClones : sourceCodeElementLimId2CloneInstanceGenelogyIdMap)
        cloneRelatedLimNodes.insert({ -getLimNodeDepth(sourceCodeElementClones.first), sourceCodeElementClones.first });

      // Add the corresponding component nodes too
      for (const auto& cloneRelatedLimNodeInfo : cloneRelatedLimNodes)
      {
        NodeId currentLimNodeId = cloneRelatedLimNodeInfo.second;
        auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(currentLimNodeId));
        for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
        {
          const NodeId componentId = componentIt->getId();
          // Add the clone instances to the component node
          sourceCodeElementLimId2CloneInstanceGenelogyIdMap[componentId].insert(sourceCodeElementLimId2CloneInstanceGenelogyIdMap[currentLimNodeId].begin(),
                                                                                sourceCodeElementLimId2CloneInstanceGenelogyIdMap[currentLimNodeId].end());
          // Add the component nodes with a positive depth to be sure that they will be processed after all other nodes
          // Since the component tree is flat (all but the system component is on level 1.
          cloneRelatedLimNodes.insert({1 , componentId});
        }
      }

      updateMemoryStat(config);

      // Aggregate counters to the parents
      while (!cloneRelatedLimNodes.empty())
      {
        auto cloneRelatedLimNodesIt = cloneRelatedLimNodes.begin();
        int currentDepth = cloneRelatedLimNodesIt->first;
        NodeId currentLimNodeId = cloneRelatedLimNodesIt->second;
        auto cloneInstancesOfTheCurrentNode = sourceCodeElementLimId2CloneInstanceGenelogyIdMap[currentLimNodeId];
        NodeId parentNodeId = getLimNodeParent(currentLimNodeId);

/*      // Debug
        printf("LimId:%d (%d) : %lu\n", currentLimNodeId, currentDepth, cloneInstancesOfTheCurrentNode.size());
*/

        if (parentNodeId != 0)
        {
          // Add instances to the parent
          sourceCodeElementLimId2CloneInstanceGenelogyIdMap[parentNodeId].insert(cloneInstancesOfTheCurrentNode.begin(),
                                                                                 cloneInstancesOfTheCurrentNode.end());

          // add the parent to the set
          cloneRelatedLimNodes.insert({currentDepth + 1, parentNodeId });
        }

        // Set the CCO metric for LIM element
        int CCOSum = 0;
        for (auto cloneInstanceID : cloneInstancesOfTheCurrentNode)
          CCOSum += ((genealogy::CloneInstance&)genealogyFact->getRef(cloneInstanceID)).getCco();

        graphsupport::setMetricInt(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(currentLimNodeId),
                                   "CCO",
                                   CCOSum);


        // remove the current node from the set
        cloneRelatedLimNodes.erase(cloneRelatedLimNodesIt);
      }


      //--------------------------------------------------------------------------------//
      updateMemoryStat(config);
      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CCO took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    void DuplicatedCodeMiner::calculateCCL()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCCL()");
      common::timestat time = common::getProcessUsedTime();

      // Map to store the the related clone classes for each source code element;
      map</* LIM */ NodeId , set< /* genealogy */ NodeId>> sourceCodeElementLimId2CloneClassGenalogyIdMap;

      // Collect the related clone classes for each related sourcecode elements
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          const auto& correspondingSourceCodeElements = limNodeCloneInstanceMap[cloneInstanceIter->getId()];
          for (auto limNodeId : correspondingSourceCodeElements)
            sourceCodeElementLimId2CloneClassGenalogyIdMap[limNodeId].insert(cloneClassIter->getId());
        }
      }


/*      // Debug
      for (const auto& sourceCodeElementClones : sourceCodeElementLimId2CloneClassGenalogyIdMap)
      {
        const auto& limNode = dynamic_cast<const columbus::lim::asg::base::Named&>(limFact->getRef(sourceCodeElementClones.first));
        printf("%d (%s,\t%s)\n", sourceCodeElementClones.first, columbus::lim::asg::Common::toString(limNode.getNodeKind()).c_str(), limNode.getName().c_str());

        for (auto cloneClassId : sourceCodeElementClones.second)
        {
          printf("%d ", cloneClassId);
        }
        printf("\n");
      }
*/
      // Copy the nodeids of the related LIM nodes into a separate container with their depth to prepare them for aggregation
      set<pair</* dpeth of the node in the asg*/ int, NodeId>> cloneRelatedLimNodes;

      for (const auto& sourceCodeElementClones : sourceCodeElementLimId2CloneClassGenalogyIdMap)
        cloneRelatedLimNodes.insert({ -getLimNodeDepth(sourceCodeElementClones.first), sourceCodeElementClones.first });

      // Add the corresponding component nodes too
      for (const auto& cloneRelatedLimNodeInfo : cloneRelatedLimNodes)
      {
        NodeId currentLimNodeId = cloneRelatedLimNodeInfo.second;
        auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(currentLimNodeId));
        for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
        {
          const NodeId componentId = componentIt->getId();
          // Add the clone classes to the component nodes
          sourceCodeElementLimId2CloneClassGenalogyIdMap[componentId].insert(sourceCodeElementLimId2CloneClassGenalogyIdMap[currentLimNodeId].begin(),
                                                                             sourceCodeElementLimId2CloneClassGenalogyIdMap[currentLimNodeId].end());

          // Add the component nodes with a positive depth to be sure that they will be processed after all other nodes
          // Since the component tree is flat (all but the system component is on level 1.
          cloneRelatedLimNodes.insert({1 , componentId});
        }
      }

/*    // Debug
      printf("----------\n");
      for (const auto& x : cloneRelatedLimNodes)
      {
        printf("x:%d  -> %d\n", x.first, x.second);
      }
      printf("----------\n");
*/

      updateMemoryStat(config);

      // After collecting them we should aggregate the sets up on the parents to be able to set the CCL metric by the number of elements in the sets
      // The ordering of the aggregation is very importat! Whe should start it with the furthest node so we use negative distances to be able to
      // use the default comparison of the std::pair. (All the components starts with depth 1)
      while (!cloneRelatedLimNodes.empty())
      {
        auto cloneRelatedLimNodesIt = cloneRelatedLimNodes.begin();
        int currentDepth = cloneRelatedLimNodesIt->first;
        NodeId currentLimNodeId = cloneRelatedLimNodesIt->second;
        auto cloneClassesOfTheCurrrentNode = sourceCodeElementLimId2CloneClassGenalogyIdMap[currentLimNodeId];
        NodeId parentNodeId = getLimNodeParent(currentLimNodeId);

/*      // Debug
        printf("LimId:%d (%d)\n", currentLimNodeId, currentDepth);
*/
        if (parentNodeId != 0)
        {
          // copy the related clone classes to the parent node
          sourceCodeElementLimId2CloneClassGenalogyIdMap[parentNodeId].insert(cloneClassesOfTheCurrrentNode.begin(),
                                                                              cloneClassesOfTheCurrrentNode.end());
          // add the parent to the set
          cloneRelatedLimNodes.insert({currentDepth + 1, parentNodeId });
        }

        // set the CCL metric of the current source code element
        graphsupport::setMetricInt(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(currentLimNodeId),
                                   "CCL",
                                   cloneClassesOfTheCurrrentNode.size());

        // remove the current node from the set
        cloneRelatedLimNodes.erase(cloneRelatedLimNodesIt);
      }

/*    // Debug
      printf("--------------------------------------\n");
      for (const auto& sourceCodeElementClones : sourceCodeElementLimId2CloneClassGenalogyIdMap)
      {
        const auto& limNode = dynamic_cast<const columbus::lim::asg::base::Named&>(limFact->getRef(sourceCodeElementClones.first));
        printf("%d (%s,\t%s)\n", sourceCodeElementClones.first, columbus::lim::asg::Common::toString(limNode.getNodeKind()).c_str(), limNode.getName().c_str());

        for (auto cloneClassId : sourceCodeElementClones.second)
        {
          printf("%d ", cloneClassId);
        }
        printf("\n");
      }
*/
      updateMemoryStat(config);

      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CCL took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    void DuplicatedCodeMiner::calculateCC()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCC()");
      common::timestat time = common::getProcessUsedTime();


      // Calculate the number of nodes by the serialized AST for each LIM node
      map</* LIM */ NodeId, size_t> nodeCountMap;
      for (const auto nodeInfo : serializationData.nodeInfoSequence)
      {
        if (nodeInfo != nullptr)
        {
          NodeId limNodeId = nodeInfo->getLimNodeId();
          if (limNodeId != 0)
          {
            ++nodeCountMap[limNodeId];

            auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(limNodeId));
            for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
              ++nodeCountMap[componentIt->getId()];
          }
        }
      }

      // Calculate the clone covered nodes of serialized AST for each LIM node
      map</* LIM */ NodeId, /* covered indexes of the serialized AST */ set<size_t>> coveredNodeCountMap;
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        auto length = lengths[cloneClassIter->getId()];
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          auto startPosition = positions[cloneInstanceIter->getId()];
          for (size_t index = startPosition; index < startPosition + length; ++index)
          {
            const auto nodeInfo = serializationData.nodeInfoSequence[index];
            if (nodeInfo != nullptr)
            {
              NodeId limNodeId = nodeInfo->getLimNodeId();
              if (limNodeId != 0)
                coveredNodeCountMap[limNodeId].insert(index);

            }
          }
        }
      }

/*      // Debug
      for (auto coveredNodeCountMapElement : coveredNodeCountMap)
        printf("Lim:%d   Count:%lu Covered:%lu\n", coveredNodeCountMapElement.first, nodeCountMap[coveredNodeCountMapElement.first], coveredNodeCountMapElement.second.size());
*/
      // Aggregate the counters to the parents

      // set to store all the source code elements which has a clone instance
      set< /* LIM */ NodeId> relatedSourceCodeElementLimId;

      // Collect the LIM nodeids of the affected source code elements
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          const auto& correspondingSourceCodeElements = limNodeCloneInstanceMap[cloneInstanceIter->getId()];
          relatedSourceCodeElementLimId.insert(correspondingSourceCodeElements.begin(), correspondingSourceCodeElements.end());
        }
      }


      // Copy the nodeids of the related LIM nodes into a separate container with their depth to prepare them for aggregation
      set<pair</* dpeth of the node in the asg*/ int, /* LIM */NodeId>> cloneRelatedLimNodes;

      for (auto limNodeId : relatedSourceCodeElementLimId)
        cloneRelatedLimNodes.insert({ -getLimNodeDepth(limNodeId), limNodeId });


      // Add the corresponding component nodes too
      // Since the component tree is flat (all but the system component is on level 1.

      for (const auto& cloneRelatedLimNodeInfo : cloneRelatedLimNodes)
      {
        NodeId currentLimNodeId = cloneRelatedLimNodeInfo.second;
        auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(currentLimNodeId));
        for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
        {
          const NodeId componentId = componentIt->getId();

          coveredNodeCountMap[componentId].insert(coveredNodeCountMap[currentLimNodeId].begin(), coveredNodeCountMap[currentLimNodeId].end());

          cloneRelatedLimNodes.insert({1 , componentId});
        }
      }

      updateMemoryStat(config);

      // Aggregate counters to the parents
      while (!cloneRelatedLimNodes.empty())
      {
        auto cloneRelatedLimNodesIt = cloneRelatedLimNodes.begin();
        int currentDepth = cloneRelatedLimNodesIt->first;
        NodeId currentLimNodeId = cloneRelatedLimNodesIt->second;
        NodeId parentNodeId = getLimNodeParent(currentLimNodeId);



        auto currentNodeCountValue = nodeCountMap[currentLimNodeId];
        const auto& currentCoveredNodes = coveredNodeCountMap[currentLimNodeId];

/*      // Debug
        printf("LimId:%d (%d) : %lu %lu\n", currentLimNodeId, currentDepth, currentNodeCountValue, currentCoveredNodes.size());
*/

        if (parentNodeId != 0)
        {
          // Add the counters to the parent node
          nodeCountMap[parentNodeId] += currentNodeCountValue;
          coveredNodeCountMap[parentNodeId].insert(currentCoveredNodes.begin(), currentCoveredNodes.end());

          // add the parent to the set
          cloneRelatedLimNodes.insert({currentDepth + 1, parentNodeId });
        }

        // set the CC metric of the current source code element
        graphsupport::setMetricFloat(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(currentLimNodeId),
                                   "CC",
                                   (double)currentCoveredNodes.size() / currentNodeCountValue);

        // remove the current node from the set
        cloneRelatedLimNodes.erase(cloneRelatedLimNodesIt);
      }

      updateMemoryStat(config);
      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CC took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }


    void DuplicatedCodeMiner::calculateCI()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCI()");
      common::timestat time = common::getProcessUsedTime();

      map</* LIM */ NodeId, set</* GENEALOGY */ NodeId>> sourceCodeElementLimId2CloneInstanceGenelogyIdMap;

      // Calculate the number of clone instances for each source code element
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          const auto& correspondingSourceCodeElements = limNodeCloneInstanceMap[cloneInstanceIter->getId()];
          for (auto limNodeId : correspondingSourceCodeElements)
            sourceCodeElementLimId2CloneInstanceGenelogyIdMap[limNodeId].insert(cloneInstanceIter->getId());
        }

        // Set the CI metric for the clone classes
        graphsupport::setMetricInt(graph,
                                   getGraphNameOfGenelogyNode(*cloneClassIter),
                                   "CI",
                                   cloneClassIter->getInstances());
      }

      // Copy the nodeids of the related LIM nodes into a separate container with their depth to prepare them for aggregation
      set<pair</* dpeth of the node in the asg*/ int, NodeId>> cloneRelatedLimNodes;

      for (const auto& sourceCodeElementClones : sourceCodeElementLimId2CloneInstanceGenelogyIdMap)
        cloneRelatedLimNodes.insert({ -getLimNodeDepth(sourceCodeElementClones.first), sourceCodeElementClones.first });

      // Add the corresponding component nodes too
      for (const auto& cloneRelatedLimNodeInfo : cloneRelatedLimNodes)
      {
        NodeId currentLimNodeId = cloneRelatedLimNodeInfo.second;
        auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(currentLimNodeId));
        for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
        {
          const NodeId componentId = componentIt->getId();
          // Add the clone instances to the component node
          sourceCodeElementLimId2CloneInstanceGenelogyIdMap[componentId].insert(sourceCodeElementLimId2CloneInstanceGenelogyIdMap[currentLimNodeId].begin(),
                                                                                sourceCodeElementLimId2CloneInstanceGenelogyIdMap[currentLimNodeId].end());
          // Add the component nodes with a positive depth to be sure that they will be processed after all other nodes
          // Since the component tree is flat (all but the system component is on level 1.
          cloneRelatedLimNodes.insert({1 , componentId});
        }
      }

      updateMemoryStat(config);

      // Aggregate counters to the parents
      while (!cloneRelatedLimNodes.empty())
      {
        auto cloneRelatedLimNodesIt = cloneRelatedLimNodes.begin();
        int currentDepth = cloneRelatedLimNodesIt->first;
        NodeId currentLimNodeId = cloneRelatedLimNodesIt->second;
        auto cloneInstancesOfTheCurrentNode = sourceCodeElementLimId2CloneInstanceGenelogyIdMap[currentLimNodeId];
        NodeId parentNodeId = getLimNodeParent(currentLimNodeId);

/*      // Debug
        printf("LimId:%d (%d) : %lu\n", currentLimNodeId, currentDepth, cloneInstancesOfTheCurrentNode.size());
*/

        if (parentNodeId != 0)
        {
          // Add instances to the parent
          sourceCodeElementLimId2CloneInstanceGenelogyIdMap[parentNodeId].insert(cloneInstancesOfTheCurrentNode.begin(),
                                                                                 cloneInstancesOfTheCurrentNode.end());

          // add the parent to the set
          cloneRelatedLimNodes.insert({currentDepth + 1, parentNodeId });
        }

        // Set the CI metric for LIM element
        graphsupport::setMetricInt(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(currentLimNodeId),
                                   "CI",
                                   cloneInstancesOfTheCurrentNode.size());


        // remove the current node from the set
        cloneRelatedLimNodes.erase(cloneRelatedLimNodesIt);
      }


      updateMemoryStat(config);
      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CI took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }


    void DuplicatedCodeMiner::calculateCLC_LDC()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCLC_LDC()");
      common::timestat time = common::getProcessUsedTime();

      // Calculate the clone covered line intervals for each LIM node

      map</* LIM */                    NodeId,
          /* covered lines by files */ map< /* path */                   columbus::Key,
                                            /* covered line intervals */ boost::icl::interval_set<unsigned>>> coveredLinesMap;


      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        auto length = lengths[cloneClassIter->getId()];
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          auto startPosition = positions[cloneInstanceIter->getId()];

          // Collect the lines for one instance into a separate container as we have to merge
          // the ranges not to get logical line coverage before we add it to the coveredLinesMap

          map</* LIM */                    NodeId,
              /* covered lines by files */ map< /* path */                   columbus::Key,
                                                /* covered line intervals */ boost::icl::interval_set<unsigned>>> oneInstanceCoveredLinesMap;

          for (size_t index = startPosition; index < startPosition + length; ++index)
          {
            const auto nodeInfo = serializationData.nodeInfoSequence[index];
            if (nodeInfo != nullptr)
            {
              NodeId limNodeId = nodeInfo->getLimNodeId();
              if (limNodeId != 0)
                oneInstanceCoveredLinesMap[limNodeId][nodeInfo->getPath()].insert(boost::icl::discrete_interval<unsigned>::closed(nodeInfo->getLine(), nodeInfo->getEndLine()));

            }
          }

          // Merge the ranges for each LIM node to convert the logical line coverage to simple line coverage
          for (const auto& covereageInfo : oneInstanceCoveredLinesMap)
          {
            for (const auto& fileCoverageInfo : covereageInfo.second)
            {
              unsigned firstStart = fileCoverageInfo.second.begin()->lower();
              unsigned lastEnd = fileCoverageInfo.second.rbegin()->upper();
/*            // Debug
              if (fileCoverageInfo.second.size() > 1)
              {
                printf("Merge:\n");
                printf("LimId:%d\n", covereageInfo.first);
                printf("  - %s\n", ASTNodeInfo::getStringPath(fileCoverageInfo.first).c_str());
                printf("    Begin: %d End: %d\n", firstStart, lastEnd);
              }
*/
              coveredLinesMap[covereageInfo.first][fileCoverageInfo.first].insert(boost::icl::discrete_interval<unsigned>::closed(firstStart, lastEnd));

            }
          }
        }
      }

      updateMemoryStat(config);

/*
      // Debug
      for (const auto& covereageInfo : coveredLinesMap)
      {
        printf("LimId:%d\n", covereageInfo.first);
        for (const auto& fileCoverageInfo : covereageInfo.second)
        {
          printf("  - %s\n", ASTNodeInfo::getStringPath(fileCoverageInfo.first).c_str());
          for (const auto& interval : fileCoverageInfo.second)
          {
            //cout << interval << endl;
            stringstream tempsstream;
            tempsstream << interval;

            printf("    %s\n", tempsstream.str().c_str());
          }
        }
      }
*/
      set<pair</* dpeth of the node in the asg*/ int, NodeId>> cloneRelatedLimNodes;

      for (const auto& sourceCodeElementCoverage : coveredLinesMap)
        cloneRelatedLimNodes.insert({ -getLimNodeDepth(sourceCodeElementCoverage.first), sourceCodeElementCoverage.first });

      // Add the corresponding component nodes too
      for (const auto& cloneRelatedLimNodeInfo : cloneRelatedLimNodes)
      {
        NodeId currentLimNodeId = cloneRelatedLimNodeInfo.second;
        auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(currentLimNodeId));
        for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
        {
          const NodeId componentId = componentIt->getId();
          // Copy the covered lines to the components
          for (const auto& coveredLinesByPath : coveredLinesMap[currentLimNodeId])
            coveredLinesMap[componentId][coveredLinesByPath.first] += coveredLinesByPath.second;

          // Add the component nodes with a positive depth to be sure that they will be processed after all other nodes
          // Since the component tree is flat (all but the system component is on level 1.
          cloneRelatedLimNodes.insert({1 , componentId});
        }
      }

      updateMemoryStat(config);

      // Calculate CLC for the LIM elements and aggregate the coverage infos to the parents
      while (!cloneRelatedLimNodes.empty())
      {
        auto cloneRelatedLimNodesIt = cloneRelatedLimNodes.begin();
        int currentDepth = cloneRelatedLimNodesIt->first;
        NodeId currentLimNodeId = cloneRelatedLimNodesIt->second;
        NodeId parentNodeId = getLimNodeParent(currentLimNodeId);

        const auto& coveredLinesOfTheCurentLIMNode = coveredLinesMap[currentLimNodeId];

        if (parentNodeId != 0)
        {
          // Add covered lines to the parent
          for (const auto& coveredLinesByPath : coveredLinesOfTheCurentLIMNode)
            coveredLinesMap[parentNodeId][coveredLinesByPath.first] += coveredLinesByPath.second;

          // add the parent to the set
          cloneRelatedLimNodes.insert({currentDepth + 1, parentNodeId });
        }

        // Add the covered ranges to get the full coverage
        int coveredSize = 0;
        for (const auto& coverdLinesByPath : coveredLinesOfTheCurentLIMNode)
          coveredSize += length(coverdLinesByPath.second);


        int TLOC = 0;
        const auto& limNode = limFact->getRef(currentLimNodeId);
        if (columbus::lim::asg::Common::getIsScope(limNode))
          TLOC = static_cast<const columbus::lim::asg::logical::Scope&>(limNode).getTLOC();
        else if (columbus::lim::asg::Common::getIsComponent(limNode))
          TLOC = static_cast<const columbus::lim::asg::base::Component&>(limNode).getTLOC();

/*      // Debug
        printf("LimId:%d (%d) : TLOC:%d Covered:%d  (%f)\n", currentLimNodeId, currentDepth, TLOC, coveredSize, TLOC == 0 ? 0.0 : (double)coveredSize /  TLOC);
*/

        // Set the CI metric for LIM element
        if (getIsNeeded("CLC"))
          if (TLOC != 0)
            graphsupport::setMetricFloat(graph,
                                         lim2graph::VisitorGraphConverter::determineNodeName(currentLimNodeId),
                                         "CLC",
                                         (double)coveredSize / TLOC);

        if (getIsNeeded("LDC"))
          graphsupport::setMetricInt(graph,
                                    lim2graph::VisitorGraphConverter::determineNodeName(currentLimNodeId),
                                    "LDC",
                                    coveredSize);

        // remove the current node from the set
        cloneRelatedLimNodes.erase(cloneRelatedLimNodesIt);
      }


      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CLC and LDC took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    void DuplicatedCodeMiner::calculateCLLC_LLDC()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCLLC()");
      common::timestat time = common::getProcessUsedTime();

      // Calculate the clone covered line intervals for each LIM node

      map</* LIM */                    NodeId,
          /* covered lines by files */ map< /* path */                   columbus::Key,
                                            /* covered line intervals */ boost::icl::interval_set<unsigned>>> coveredLinesMap;


      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        auto length = lengths[cloneClassIter->getId()];
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          auto startPosition = positions[cloneInstanceIter->getId()];
          for (size_t index = startPosition; index < startPosition + length; ++index)
          {
            const auto nodeInfo = serializationData.nodeInfoSequence[index];
            if (nodeInfo != nullptr)
            {
              NodeId limNodeId = nodeInfo->getLimNodeId();
              if (limNodeId != 0)
              {
                auto& lineSet = coveredLinesMap[limNodeId][nodeInfo->getPath()];
                lineSet.insert(boost::icl::discrete_interval<unsigned>::closed(nodeInfo->getLine(), nodeInfo->getLine()));
                lineSet.insert(boost::icl::discrete_interval<unsigned>::closed(nodeInfo->getEndLine(), nodeInfo->getEndLine()));

                if (nodeInfo->getExtraLines() != nullptr)
                  for (auto extraLine : *nodeInfo->getExtraLines())
                    lineSet.insert(boost::icl::discrete_interval<unsigned>::closed(extraLine, extraLine));

              }
            }
          }
        }
      }

      updateMemoryStat(config);


/*      // Debug
      for (const auto& covereageInfo : coveredLinesMap)
      {
        printf("LimId:%d\n", covereageInfo.first);
        for (const auto& fileCoverageInfo : covereageInfo.second)
        {
          printf("  - %s\n", ASTNodeInfo::getStringPath(fileCoverageInfo.first).c_str());
          for (const auto& interval : fileCoverageInfo.second)
          {
            //cout << interval << endl;
            stringstream tempsstream;
            tempsstream << interval;

            printf("    %s\n", tempsstream.str().c_str());
          }
        }
      }
*/
      set<pair</* dpeth of the node in the asg*/ int, NodeId>> cloneRelatedLimNodes;

      for (const auto& sourceCodeElementCoverage : coveredLinesMap)
        cloneRelatedLimNodes.insert({ -getLimNodeDepth(sourceCodeElementCoverage.first), sourceCodeElementCoverage.first });

      // Add the corresponding component nodes too
      for (const auto& cloneRelatedLimNodeInfo : cloneRelatedLimNodes)
      {
        NodeId currentLimNodeId = cloneRelatedLimNodeInfo.second;
        auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(currentLimNodeId));
        for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
        {
          const NodeId componentId = componentIt->getId();
          // Copy the covered lines to the components
          for (const auto& coveredLinesByPath : coveredLinesMap[currentLimNodeId])
            coveredLinesMap[componentId][coveredLinesByPath.first] += coveredLinesByPath.second;

          // Add the component nodes with a positive depth to be sure that they will be processed after all other nodes
          // Since the component tree is flat (all but the system component is on level 1.
          cloneRelatedLimNodes.insert({1 , componentId});
        }
      }

      updateMemoryStat(config);

      // Calculate CLLC for the LIM elements and aggregate the coverage infos to the parents
      while (!cloneRelatedLimNodes.empty())
      {
        auto cloneRelatedLimNodesIt = cloneRelatedLimNodes.begin();
        int currentDepth = cloneRelatedLimNodesIt->first;
        NodeId currentLimNodeId = cloneRelatedLimNodesIt->second;
        NodeId parentNodeId = getLimNodeParent(currentLimNodeId);

        const auto& coveredLinesOfTheCurentLIMNode = coveredLinesMap[currentLimNodeId];

        if (parentNodeId != 0)
        {
          // Add covered lines to the parent
          for (const auto& coveredLinesByPath : coveredLinesOfTheCurentLIMNode)
            coveredLinesMap[parentNodeId][coveredLinesByPath.first] += coveredLinesByPath.second;

          // add the parent to the set
          cloneRelatedLimNodes.insert({currentDepth + 1, parentNodeId });
        }

        // Add the covered ranges to get the full coverage
        int coveredSize = 0;
        for (const auto& coverdLinesByPath : coveredLinesOfTheCurentLIMNode)
          coveredSize += length(coverdLinesByPath.second);


        int TLLOC = 0;
        const auto& limNode = limFact->getRef(currentLimNodeId);
        if (columbus::lim::asg::Common::getIsScope(limNode))
          TLLOC = static_cast<const columbus::lim::asg::logical::Scope&>(limNode).getTLLOC();
        else if (columbus::lim::asg::Common::getIsComponent(limNode))
          TLLOC = static_cast<const columbus::lim::asg::base::Component&>(limNode).getTLLOC();

/*      // Debug
        printf("LimId:%d (%d) : TLLOC:%d Covered:%d  (%f)\n", currentLimNodeId, currentDepth, TLLOC, coveredSize, TLLOC == 0 ? 0.0 : (double)coveredSize /  TLLOC);
*/

        // Set the CI metric for LIM element
        if (getIsNeeded("CLLC"))
          if (TLLOC != 0)
            graphsupport::setMetricFloat(graph,
                                         lim2graph::VisitorGraphConverter::determineNodeName(currentLimNodeId),
                                         "CLLC",
                                         (double)coveredSize / TLLOC);
        if (getIsNeeded("LLDC"))
          graphsupport::setMetricInt(graph,
                                     lim2graph::VisitorGraphConverter::determineNodeName(currentLimNodeId),
                                     "LLDC",
                                     coveredSize);


        // remove the current node from the set
        cloneRelatedLimNodes.erase(cloneRelatedLimNodesIt);
      }


      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CLLC and LLDC took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    void DuplicatedCodeMiner::calculateCLLOC()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCLLOC()");
      common::timestat time = common::getProcessUsedTime();

      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        int lengthSum = 0;
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          int cloneInstanceLength = cloneInstanceIter->getEndLine() - cloneInstanceIter->getLine() + 1;
          graphsupport::setMetricInt(graph,
                                     getGraphNameOfGenelogyNode(*cloneInstanceIter),
                                     "CLLOC",
                                     cloneInstanceLength);

          lengthSum += cloneInstanceLength;
        }

        // TODO: Check the virtual instances
        double clloc = (double)lengthSum / cloneClassIter->getInstances();

        graphsupport::setMetricFloat(graph,
                                   getGraphNameOfGenelogyNode(*cloneClassIter),
                                   "CLLOC",
                                   clloc);

        // At the moment there is only constant reference operator for the
        // ListIterator class and it is faster to const_cast it than getting
        // a non const referenc from the factory by its ID.
        const_cast<genealogy::CloneClass&>(*cloneClassIter).setClloc(clloc);
      }

      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CLLOC took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    int calculateNDC(const std::string& path1,const std::string& path2)
    {
      boost::filesystem::path p1(path1);
      boost::filesystem::path p2(path2);
      boost::filesystem::path::iterator iterator1 = p1.begin();
      boost::filesystem::path::iterator iterator2 = p2.begin();

      unsigned int dist=0;
      while ((iterator1 != p1.end()) && (iterator2 != p2.end())) {
        if ((*iterator1) != (*iterator2))
          break;

        iterator1++;
        iterator2++;
      }

      while (iterator1!=p1.end()) {
        dist++;
        iterator1++;
      }
      while (iterator2!=p2.end()) {
        dist++;
        iterator2++;
      }

      //If the both file is not in the same directory the 2nd file change does not matter
      if (dist > 1)
        dist--;

      dist++;
      return dist;
    }


    void DuplicatedCodeMiner::calculateNCR()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateNCR()");
      common::timestat time = common::getProcessUsedTime();
/*
      // Debug
      printfprintf("MaxNDC:%d\n", currentSystemMaxNDC);
*/

      // Calculate NCR for clone classes
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        vector<const columbus::genealogy::CloneInstance*> instances;
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
          instances.push_back(&*cloneInstanceIter);

        int NDCSum = 0;
        for (size_t CI1 = 0; CI1 < instances.size(); ++CI1)
          for (size_t CI2 = CI1 + 1; CI2 < instances.size(); ++CI2)
          {
            int NDC = calculateNDC(instances[CI1]->getPath(), instances[CI2]->getPath());
            NDCSum += NDC;
/*
            // Debug
            printf("P1:%s\n", instances[CI1]->getPath().c_str());
            printf("P2:%s\n", instances[CI2]->getPath().c_str());
            printf("NDC:%d\n", NDC);
*/
          }

        double NCR = NDCSum;
        NCR /= instances.size() * (instances.size() - 1) / 2;
        NCR /= currentSystemMaxNDC;
/*
        // Debug
        printf("NCR:%f\n", NCR);
*/
        graphsupport::setMetricFloat(graph,
                                     getGraphNameOfGenelogyNode(*cloneClassIter),
                                     "NCR",
                                     NCR);

        // At the moment there is only constant reference operator for the
        // ListIterator class and it is faster to const_cast it than getting
        // a non const referenc from the factory by its ID.
        const_cast<genealogy::CloneClass&>(*cloneClassIter).setNcrad(NCR);
      }

      // Calculate NCR for components
      map< /* LIM component */ NodeId, set<const columbus::genealogy::CloneClass*>> componentCloneClassMap;

      // Collect the clone classes for each direct clone instance related sourecode elements
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          const auto& correspondingSourceCodeElements = limNodeCloneInstanceMap[cloneInstanceIter->getId()];
          for (auto limNodeId : correspondingSourceCodeElements)
          {
            auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(limNodeId));
            for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
              componentCloneClassMap[componentIt->getId()].insert(&*cloneClassIter);
          }
        }
      }

      // Since the component tree is flat we don't have to aggregate it, but just calculate it to the system component too
      for (const auto& componentCloneClasses : componentCloneClassMap)
      {
        NodeId limComponentNodeId = componentCloneClasses.first;
        const auto& cloneClassesOfTheComponent = componentCloneClasses.second;

        double NCR = 0;
        for (auto CC : cloneClassesOfTheComponent)
          NCR += CC->getNcrad();

        NCR /= cloneClassesOfTheComponent.size();

/*
        // Debug
        printf("Component NCR:%f\n", NCR);
*/
        graphsupport::setMetricFloat(graph,
                                     lim2graph::VisitorGraphConverter::determineNodeName(limComponentNodeId),
                                     "NCR",
                                     NCR);

      }

      // Set the NCR to INVALID for components, which do not contain clones
      const auto& systemComponentNode = limFact->getComponentRootRef();
      for (auto componentIt = systemComponentNode.getContainsListIteratorBegin(); componentIt != systemComponentNode.getContainsListIteratorEnd(); ++componentIt)
        if (componentCloneClassMap.find(componentIt->getId()) == componentCloneClassMap.end())
          graphsupport::setMetricFloat(graph,
                                       lim2graph::VisitorGraphConverter::determineNodeName(componentIt->getId()),
                                       "NCR",
                                       nan(""));

      // Calculate NCR to to the system component
      double systemNCR = 0.0;
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
        systemNCR += cloneClassIter->getNcrad();

      systemNCR /= currentSystem->getCloneClassesSize();

/*
      // Debug
      printf("System NCR:%f\n", systemNCR);
*/
      graphsupport::setMetricFloat(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(limFact->getComponentRoot()),
                                   "NCR",
                                   systemNCR);

      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing NCR took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }


    void DuplicatedCodeMiner::calculateCE()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCE()");
      common::timestat time = common::getProcessUsedTime();


      // Collect incoming and outgoing references for each clone instance
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        auto length = lengths[cloneClassIter->getId()];
        int CC_CE = 1;
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {

          set<NodeId> internalNodes;
          bool fullFunctionClone = false;
          NodeId startNodeId = 0;
          NodeId startLimNodeId = 0;

          auto startPosition = positions[cloneInstanceIter->getId()];
          const auto& nodeInfo = serializationData.nodeInfoSequence[startPosition];
          if (nodeInfo != nullptr)
          {
            startNodeId = nodeInfo->getId();
            startLimNodeId = nodeInfo->getLimNodeId();
          }

          // check if it is a full function clone
          int nodeKind = serializationData.nodeKindSequence[startPosition];
          if (((nodeKind & NodeMask::NodeTypeMask) == NodeType::Declaration) &&
              (((nodeKind & NodeMask::NodeKindMask) == clang::Decl::Kind::Function) || ((nodeKind & NodeMask::NodeKindMask) == clang::Decl::Kind::CXXMethod)))
          {
            fullFunctionClone = true;
          }

          Key astKey = serializationData.nodeInfoSequence[startPosition]->getTUPath();
          for (size_t index = startPosition; index < startPosition + length; ++index)
          {
            const auto nodeInfo = serializationData.nodeInfoSequence[index];
            if (nodeInfo != nullptr)
              internalNodes.insert(nodeInfo->getId());

          }

          set<NodeId> outgoingRefs;
          // collect to outgoing references
          for (const auto nodeId : internalNodes)
          {
            const auto& refMap = serializationData.referencesMap[astKey];
            auto refIt = refMap.find(nodeId);
            if (refIt != refMap.end())
              if (internalNodes.find(refIt->second) == internalNodes.end())
                outgoingRefs.insert(refIt->second);
          }

/*
          // Debug
          printf("Clone id: %u\n  ", cloneInstanceIter->getId());
          printf("Outgoing refs:\n  ");
          for (const auto nodeId : outgoingRefs)
              printf("%u ", nodeId);
          printf("\n");
*/
          set<NodeId> incomingRefs;
          // collect to incoming references
          for (const auto nodeId : internalNodes)
          {
            // For full function clones we skip the function node itself as the call edges of the
            // the corresponding LIM node will be used to get calls across compilation units
            if (fullFunctionClone && nodeId == startNodeId)
              continue;

            const auto& inverseRefMap = serializationData.inverseReferencesMap[astKey];
            auto refIt = inverseRefMap.find(nodeId);
            if (refIt != inverseRefMap.end())
              for (const auto externalNodeId : refIt->second)
              {

                if (internalNodes.find(externalNodeId) == internalNodes.end())
                  incomingRefs.insert(externalNodeId);
              }
          }
/*
          // Debug
          printf("Clone id: %u\n  ", cloneInstanceIter->getId());
          printf("Incoming refs:\n");
          for (const auto nodeId : incomingRefs)
              printf("%u ", nodeId);
          printf("\n");
*/
          // TODO: types, calls from other compilation units;
          const string& clonePath = cloneInstanceIter->getPath();

          int CE = 0;

          // Use the lim call edges for the incoming references if the clone is a full function
          if (fullFunctionClone)
          {

            if (lim::asg::Common::getIsMethod(limFact->getRef(startLimNodeId)))
            {
              auto methodcallIt = limFact->getReverseEdges().constIteratorBegin(startLimNodeId, columbus::lim::asg::edkMethodCall_Method);
              auto methodcallItEnd = limFact->getReverseEdges().constIteratorEnd(startLimNodeId, columbus::lim::asg::edkMethodCall_Method);
              while(methodcallIt != methodcallItEnd)
              {
                const lim::asg::base::Base& methodCall = *methodcallIt;
                auto methodIt = limFact->getReverseEdges().constIteratorBegin(methodCall.getId(), columbus::lim::asg::edkMethod_Calls);
                auto methodItEnd = limFact->getReverseEdges().constIteratorEnd(methodCall.getId(), columbus::lim::asg::edkMethod_Calls);

                while(methodIt != methodItEnd)
                {
                  const lim::asg::logical::Method& callerMethod = static_cast<const lim::asg::logical::Method&>(*methodIt);

                  auto containedInItEnd = callerMethod.getIsContainedInListIteratorAssocEnd();
                  for(auto containedInIt = callerMethod.getIsContainedInListIteratorAssocBegin(); containedInIt != containedInItEnd; ++containedInIt)
                    CE += calculateNDC(clonePath, columbus::lim::asg::Common::getFullPath((*containedInIt)).c_str());

                  ++methodIt;
                }
                ++methodcallIt;
              }
            }
            else
            {
/*
                // DEBUG
              printf("FunctionClone (%d) with not method LIM node: LIM root nodeid:%d nodekind:%s\n",
                    cloneInstanceIter->getId(),
                    startLimNodeId,
                    lim::asg::Common::toString(limFact->getRef(startLimNodeId).getNodeKind()).c_str());
*/
            }
          }

          // Weight the outgoing references
          for (const auto outgoingRef : outgoingRefs)
          {
            const string& referencePath = ASTNodeInfo::getStringPath(serializationData.nodeReferencePathMap[astKey][outgoingRef]);
            string relativeReferencePath = referencePath.c_str();
            CE += calculateNDC(clonePath, relativeReferencePath);
/*
            // DEBUG
            printf("O: CP: %s RefPath: %s  CE: %d\n", clonePath.c_str(), relativeReferencePath.c_str(), CE);
*/
          }

          // Weight the incoming references
          for (const auto incomingRef : incomingRefs)
          {
            const string& referencePath = ASTNodeInfo::getStringPath(serializationData.nodeReferencePathMap[astKey][incomingRef]);
            string relativeReferencePath = referencePath.c_str();
            CE += calculateNDC(clonePath, relativeReferencePath);
/*
            // DEBUG
            printf("I: CP: %s RefPath: %s  CE: %d\n", clonePath.c_str(), relativeReferencePath.c_str(), CE);
*/
          }


          graphsupport::setMetricInt(graph,
                                     getGraphNameOfGenelogyNode(*cloneInstanceIter),
                                     "CE",
                                     CE);

          CC_CE += CE;

          // At the moment there is only constant reference operator for the
          // ListIterator class and it is faster to const_cast it than getting
          // a non const referenc from the factory by its ID.
          const_cast<genealogy::CloneInstance&>(*cloneInstanceIter).setCe(CE);
        }

        graphsupport::setMetricInt(graph,
                                   getGraphNameOfGenelogyNode(*cloneClassIter),
                                   "CE",
                                   CC_CE);

        // At the moment there is only constant reference operator for the
        // ListIterator class and it is faster to const_cast it than getting
        // a non const referenc from the factory by its ID.
        const_cast<genealogy::CloneClass&>(*cloneClassIter).setCe(CC_CE);


      }

      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CE took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }


    void DuplicatedCodeMiner::calculateCEE()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCEE()");
      common::timestat time = common::getProcessUsedTime();

      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        if (cloneClassIter->getIsVirtual())
          continue;

        genealogy::CloneClass& cloneClass = const_cast<genealogy::CloneClass&>(*cloneClassIter);

        // TODO: Check if the virtual instances are calculated into the instances attribute!
        double eliminationEffort = cloneClass.getCe() * cloneClass.getNcrad() * cloneClass.getInstances();

        graphsupport::setMetricFloat(graph,
                                   getGraphNameOfGenelogyNode(cloneClass),
                                   "CEE",
                                   eliminationEffort);

        cloneClass.setEffort(eliminationEffort);
      }


      // Calculate CEE for components
      map< /* LIM component */ NodeId, set<const columbus::genealogy::CloneClass*>> componentCloneClassMap;

      // Collect the clone classes for each component
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          const auto& correspondingSourceCodeElements = limNodeCloneInstanceMap[cloneInstanceIter->getId()];
          for (auto limNodeId : correspondingSourceCodeElements)
          {
            auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(limNodeId));
            for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
              componentCloneClassMap[componentIt->getId()].insert(&*cloneClassIter);
          }
        }
      }

      // Set the CEE for the components
      for (const auto& cloneClasses : componentCloneClassMap)
      {
        double eliminationEffort = 0;
        for (const auto cloneClassPtr : cloneClasses.second)
          eliminationEffort += cloneClassPtr->getEffort();

        graphsupport::setMetricFloat(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(cloneClasses.first),
                                   "CEE",
                                   eliminationEffort);

        componentMetrics[cloneClasses.first].CEE = eliminationEffort;
      }

      // set CEE for the system component
      double eliminationEffort = 0;
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
        eliminationEffort += cloneClassIter->getEffort();

      graphsupport::setMetricFloat(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(limFact->getComponentRoot()),
                                   "CEE",
                                   eliminationEffort);

      componentMetrics[limFact->getComponentRoot()].CEE = eliminationEffort;

      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CEE took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    void DuplicatedCodeMiner::calculateCEG()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCEG()");
      common::timestat time = common::getProcessUsedTime();

      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        if (cloneClassIter->getIsVirtual())
          continue;

        genealogy::CloneClass& cloneClass = const_cast<genealogy::CloneClass&>(*cloneClassIter);

        double cloneEliminationGain;

        if (cloneClass.getEffort() < std::numeric_limits<double>::epsilon())
          cloneEliminationGain = nan("");
        else
          cloneEliminationGain = cloneClass.getRisk() / cloneClass.getEffort();

        graphsupport::setMetricFloat(graph,
                                     getGraphNameOfGenelogyNode(cloneClass),
                                     "CEG",
                                     cloneEliminationGain);

        cloneClass.setGain(cloneEliminationGain);
      }

      /* (((1 / (1+  e^(-2*CR/ln(CEE)) )*100)-50)*2) */
      for (const auto& cMetrics : componentMetrics)
      {
        double cloneEliminationGain;

        if (cMetrics.second.CEE < std::numeric_limits<double>::epsilon())
          cloneEliminationGain = nan("");
        else
          cloneEliminationGain = ((100.0 / ( 1.0 + exp(-2.0 * cMetrics.second.CR / log(cMetrics.second.CEE)))) - 50.0) * 2.0;

        graphsupport::setMetricFloat(graph,
                                     lim2graph::VisitorGraphConverter::determineNodeName(cMetrics.first),
                                     "CEG",
                                     cloneEliminationGain);
      }

      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CEG took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    void DuplicatedCodeMiner::calculateCR()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCR()");
      common::timestat time = common::getProcessUsedTime();

      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        if (cloneClassIter->getIsVirtual())
          continue;

        genealogy::CloneClass& cloneClass = const_cast<genealogy::CloneClass&>(*cloneClassIter);

        // TODO: Check if the virtual instances are calculated into the instances attribute!
        double cloneRisk = cloneClass.getClloc() * cloneClass.getInstances() * cloneClass.getCco() * cloneClass.getNcrad() * cloneClass.getCv();

        graphsupport::setMetricFloat(graph,
                                     getGraphNameOfGenelogyNode(cloneClass),
                                     "CR",
                                     cloneRisk);

        cloneClass.setRisk(cloneRisk);
      }


      // Calculate CR for components
      map< /* LIM component */ NodeId, set<const columbus::genealogy::CloneClass*>> componentCloneClassMap;

      // Collect the clone classes for each component
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          const auto& correspondingSourceCodeElements = limNodeCloneInstanceMap[cloneInstanceIter->getId()];
          for (auto limNodeId : correspondingSourceCodeElements)
          {
            auto& currentLimNode = static_cast<columbus::lim::asg::logical::Member&>(limFact->getRef(limNodeId));
            for (auto componentIt = currentLimNode.getBelongsToListIteratorBegin(); componentIt != currentLimNode.getBelongsToListIteratorEnd(); ++componentIt)
              componentCloneClassMap[componentIt->getId()].insert(&*cloneClassIter);
          }
        }
      }

      // Set the CR for the components
      for (const auto& cloneClasses : componentCloneClassMap)
      {
        double cloneRisk = 0;
        for (const auto cloneClassPtr : cloneClasses.second)
          cloneRisk += cloneClassPtr->getRisk();

        const auto& limComponentNode = static_cast<const columbus::lim::asg::base::Component&>(limFact->getRef(cloneClasses.first));
        cloneRisk /= limComponentNode.getTLLOC();

        graphsupport::setMetricFloat(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(cloneClasses.first),
                                   "CR",
                                   cloneRisk);

        componentMetrics[cloneClasses.first].CR = cloneRisk;
      }

      // set CR for the system component
      double cloneRisk = 0;
      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
        cloneRisk += cloneClassIter->getRisk();

      const auto& limSystemComponentNode = static_cast<const columbus::lim::asg::base::Component&>(limFact->getRef(limFact->getComponentRoot()));
      cloneRisk /= limSystemComponentNode.getTLLOC();

      graphsupport::setMetricFloat(graph,
                                   lim2graph::VisitorGraphConverter::determineNodeName(limFact->getComponentRoot()),
                                   "CR",
                                   cloneRisk);

      componentMetrics[limFact->getComponentRoot()].CR = cloneRisk;



      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CR took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    void DuplicatedCodeMiner::calculateCA()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCA()");
      common::timestat time = common::getProcessUsedTime();

      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        if (cloneClassIter->getIsVirtual())
          continue;

        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          auto &cloneInstance = const_cast<columbus::genealogy::CloneInstance&>(*cloneInstanceIter);

          if (cloneInstance.getIsVirtual())
            continue;

          if (!cloneInstance.getPrevIsEmpty())
          {
            const auto& prevInstance = static_cast<const columbus::genealogy::CloneInstance&>(*cloneInstance.getPrevListIteratorBegin());
            cloneInstance.setCa(prevInstance.getCa() + 1);
          }
          else
          {
            cloneInstance.setCa(1);
          }

          graphsupport::setMetricInt(graph,
                                     getGraphNameOfGenelogyNode(cloneInstance),
                                     "CA",
                                     cloneInstance.getCa());

        }

        auto &cloneClass = const_cast<columbus::genealogy::CloneClass&>(*cloneClassIter);
        if (!cloneClass.getPrevIsEmpty())
        {
            const auto& prevClass = static_cast<const columbus::genealogy::CloneClass&>(*cloneClass.getPrevListIteratorBegin());
            cloneClass.setCa(prevClass.getCa() + 1);
        }
        else
        {
          cloneClass.setCa(1);
        }


        graphsupport::setMetricInt(graph,
                           getGraphNameOfGenelogyNode(cloneClass),
                           "CA",
                           cloneClass.getCa());
      }


      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CA took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }

    void DuplicatedCodeMiner::calculateCV()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateCV()");
      common::timestat time = common::getProcessUsedTime();

      for (auto cloneClassIter = currentSystem->getCloneClassesListIteratorBegin(); cloneClassIter != currentSystem->getCloneClassesListIteratorEnd(); ++cloneClassIter)
      {
        if (cloneClassIter->getIsVirtual())
          continue;

        bool hasSmell = 0;
        double cvSum = 0.0;

        for (auto cloneInstanceIter = cloneClassIter->getItemsListIteratorBegin(); cloneInstanceIter != cloneClassIter->getItemsListIteratorEnd(); ++cloneInstanceIter)
        {
          auto &cloneInstance = const_cast<columbus::genealogy::CloneInstance&>(*cloneInstanceIter);

          if (cloneInstance.getIsVirtual())
            continue;

          if (!cloneInstance.getPrevIsEmpty())
          {
            const auto& prevInstance = static_cast<const columbus::genealogy::CloneInstance&>(*cloneInstance.getPrevListIteratorBegin());

            // check if there were changes in structure
            if ((cloneInstance.getEndLine() - cloneInstance.getLine()) != (prevInstance.getEndLine() -  prevInstance.getLine()) ||
                (cloneInstance.getCco() != cloneInstance.getCco()))
            {
              cloneInstance.setCvMetricVariability(prevInstance.getCvMetricVariability() + 1);
            }
            else
            {
              cloneInstance.setCvMetricVariability(prevInstance.getCvMetricVariability());
            }
          }
          else
          {
            cloneInstance.setCvMetricVariability(0);
          }

          double cv = (1.0 + cloneInstance.getCvMetricVariability()) / cloneInstance.getCa();
          cloneInstance.setCv(cv);
          cvSum += cv;

          if (cloneInstance.getCloneSmellType() != columbus::genealogy::cstNone)
            hasSmell = 1;

          graphsupport::setMetricFloat(graph,
                                       getGraphNameOfGenelogyNode(cloneInstance),
                                       "CV",
                                       cv);

        }


        auto &cloneClass = const_cast<columbus::genealogy::CloneClass&>(*cloneClassIter);
        if (!cloneClass.getPrevIsEmpty())
        {
          const auto& prevClass = static_cast<const columbus::genealogy::CloneClass&>(*cloneClass.getPrevListIteratorBegin());
          cloneClass.setCvCiSmells(prevClass.getCvCiSmells() + hasSmell);
        }
        else
        {
          cloneClass.setCvCiSmells(hasSmell);
        }

        double ccCV = ((double)cloneClass.getCvCiSmells()) / cloneClass.getCa() + (cvSum / cloneClass.getInstances());
        cloneClass.setCv(ccCV);


        graphsupport::setMetricFloat(graph,
                                     getGraphNameOfGenelogyNode(cloneClass),
                                     "CV",
                                     ccCV);

      }

      common::WriteMsg::write(WriteMsg::mlDebug, "Debug: Computing CV took %d (1/100s)\n", common::getProcessUsedTime().user - time.user);
    }



    void DuplicatedCodeMiner::calculateMetrics()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateMetrics()");
      common::timestat time = common::getProcessUsedTime();
      common::WriteMsg::write(CMSG_COMPUTING_METRICS);

      // Collect the component LIM nodes and initialize the metric values to zero
      const auto& systemComponentNode = limFact->getComponentRootRef();
      for (auto componentIt = systemComponentNode.getContainsListIteratorBegin(); componentIt != systemComponentNode.getContainsListIteratorEnd(); ++componentIt)
      {
        auto& metrics = componentMetrics[componentIt->getId()];
        metrics.CR = metrics.CEE = 0.0;
      }

      if (getIsNeeded("CC"))
        calculateCC();

      if (getIsNeeded("CI"))
        calculateCI();

      if (getIsNeeded("CCL"))
        calculateCCL();

      if (getIsNeeded("CLLOC"))
        calculateCLLOC();

      if (getIsNeeded("CCO"))
        calculateCCO();

      if (getIsNeeded("CLLC") || getIsNeeded("LLDC"))
        calculateCLLC_LLDC();

      if (getIsNeeded("CLC") || getIsNeeded("LDC"))
        calculateCLC_LDC();

      if (getIsNeeded("NCR"))
        calculateNCR();

      if (getIsNeeded("CE"))
        calculateCE();


      config.stat.calculateMetricsTime += common::getProcessUsedTime().user - time.user;
      common::WriteMsg::write(CMSG_DONE_D);

    }


    void DuplicatedCodeMiner::calculateEvolutionDependentMetrics()
    {
      auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("calculateEvolutionDependentMetrics()");
      common::timestat time = common::getProcessUsedTime();
      common::WriteMsg::write(CMSG_COMPUTING_EVOLUTION_METRICS);

      if (getIsNeeded("CA"))
        calculateCA();

      if (getIsNeeded("CV"))
        calculateCV();

      if (getIsNeeded("CEE"))
        calculateCEE();

      if (getIsNeeded("CR"))
        calculateCR();

      if (getIsNeeded("CEG"))
        calculateCEG();

      // The component metrics are no longer needed.
      componentMetrics.clear();

      config.stat.calculateMetricsTime += common::getProcessUsedTime().user - time.user;
      common::WriteMsg::write(CMSG_DONE_D);
    }


    void DuplicatedCodeMiner::getLimNodeParents(NodeId limId, std::set<NodeId>& parents)
    {
      if (limId != 0)
      {
        columbus::lim::asg::EdgeKind edgeKind = columbus::lim::asg::edkScope_HasMember;

        if (columbus::lim::asg::Common::getIsComponent(limFact->getRef(limId)))
          edgeKind = columbus::lim::asg::edkComponent_Contains;

        for (auto itParent = limFact->getReverseEdges().constIteratorBegin(limId, edgeKind);
                  itParent != limFact->getReverseEdges().constIteratorEnd(limId, edgeKind);
                  ++itParent)
        {
          parents.insert(itParent->getId());
          getLimNodeParents(itParent->getId(), parents);
        }
      }
    }

    NodeId DuplicatedCodeMiner::getLimNodeParent(NodeId limId) const
    {
      if (limId != 0)
      {
        columbus::lim::asg::EdgeKind edgeKind = columbus::lim::asg::edkScope_HasMember;

        if (columbus::lim::asg::Common::getIsComponent(limFact->getRef(limId)))
          edgeKind = columbus::lim::asg::edkComponent_Contains;

        auto itParent = limFact->getReverseEdges().constIteratorBegin(limId, edgeKind);

        if (itParent != limFact->getReverseEdges().constIteratorEnd(limId, edgeKind))
          return itParent->getId(); // return the first
      }
      return 0;
    }


    void DuplicatedCodeMiner::sortNodesByType(const NodeIDMaps &idMaps
      , std::vector<NodeId> &nodes
      , std::vector<clang::Decl*> &declarations
      , std::vector<clang::Stmt*> &statements)
    {
      for(auto node : nodes)
      {
        const auto& nodeInfoIt = idMaps.id2node.find(node);
        if (nodeInfoIt != idMaps.id2node.end())
        {
          if (nodeInfoIt->second.second == AstNodeType::STMT)
            statements.push_back(static_cast<clang::Stmt*>(nodeInfoIt->second.first));
          else if(nodeInfoIt->second.second == AstNodeType::DECL)
            declarations.push_back(static_cast<clang::Decl*>(nodeInfoIt->second.first));
        }
      }
    }

}


