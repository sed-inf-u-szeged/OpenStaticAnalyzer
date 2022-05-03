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


#include "../inc/ASTConversionInfo.h"

#include <common/inc/WriteMessage.h>
#include <common/inc/messages.h>
#include <common/inc/DirectoryFilter.h>
#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>

extern std::string g_filterfile;

using namespace clang;
using namespace std;

ASTConversionInfo::ASTConversionInfo(const string ASTFilename, const string compilationUnitName, GlobalASTConversionInfo_ThreadSafe& globalInfo, MergeUIDFactory& uidFactory)
  : ASTFilename(ASTFilename)
  , compilationUnitName(compilationUnitName)
  , currentASTIdentifier(compilationUnitName)
  , globalInfo(globalInfo)
  , uidFactory(uidFactory)
{}

GlobalASTConversionInfo::GlobalASTConversionInfo(columbus::lim::asg::Factory& limFactory, const clang::metrics::Output& output, columbus::LimOrigin& origin)
  : limFactory(limFactory)
  , metricsOutput(output)
  , limOrigin(origin)
  , commentProcessor(*this)
  , linker(Linker::getInstance(*this))
{
}

struct ComponentComparator
{
  bool operator()(const columbus::lim::asg::base::Component *lhs, const columbus::lim::asg::base::Component* rhs) const
  {
    return lhs->getId() < rhs->getId();
  }
};

// Filter some folders from LIM if needed
// As folders are added dynamically along the files, so this is the most practical place to do this.
// This traverses all the folders with a stack.
void GlobalASTConversionInfo::filterFolders()
{
  DirectoryFilter directoryFilter;
  directoryFilter.openFilterFile(g_filterfile);

  columbus::lim::asg::physical::FileSystem *fs = (columbus::lim::asg::physical::FileSystem*)limFactory.getPointer(limFactory.getFileSystemRoot());

  if (!fs) return;

  limFactory.setFiltered(fs->getId());

  for (const auto &kv : canonicalFileNameToFileNode)
  {
    if (!kv.second) continue;

    if (!directoryFilter.isFilteredOut(kv.first))
    {
      limFactory.setNotFilteredThisNode(kv.second->getId());
    }
  }
}

void GlobalASTConversionInfo::finalizeConversion()
{
  filterFolders();

  for (const auto &kv: linker.component_to_files)
  {
    auto component = kv.first;
    auto files = kv.second;

    unsigned compTLOC = 0, compTLLOC = 0;
    for (const auto fileNode : files)
    {
      component->addFiles(fileNode); //should we filter this too?

      if (limFactory.getIsFiltered(fileNode))
        continue;

      compTLOC += fileNode->getLOC();
      compTLLOC += fileNode->getLLOC();
    }
    component->setTLOC(compTLOC);
    component->setTLLOC(compTLLOC);
  }
  
  unsigned rootTLOC = 0, rootTLLOC = 0;
  for (auto kv : filesAlreadyProcessed)
  {
    auto fileNode = kv.second;

    if (limFactory.getIsFiltered(fileNode))
      continue;

    rootTLOC += fileNode->getLOC();
    rootTLLOC += fileNode->getLLOC();
  }

  auto root = limFactory.getRoot();
  root->setLOC(rootTLOC); // namespaces will be subtracted below
  root->setLLOC(rootTLLOC);
  root->setTLOC(rootTLOC);
  root->setTLLOC(rootTLLOC);

  auto& rootComponent = limFactory.getComponentRootRef();
  rootComponent.setTLOC(rootTLOC);
  rootComponent.setTLLOC(rootTLLOC);

  // As namespace metrics are system level (aggragated above all components), we must deal with them here
  for (auto& ns : namespaces)
  {
      columbus::lim::asg::logical::Package* limPackage = ns.first;
      root->setLOC(root->getLOC() - limPackage->getLOC());
      root->setLLOC(root->getLLOC() - limPackage->getLLOC());
  }
  
  for (auto p : scopeListPerFile)
  {
    if (!limFactory.getIsFiltered(p.first))
      commentProcessor.bindCommentsToLimTree(p.first);
  }

  /*std::cout << "COMMENT TABLE" << std::endl;
  for (auto e : commentProcessor.commentTablePerFile)
  {
    std::cout << "PointerValue:" << e.first << ", File: " << e.first->getName() << ",id = " << e.first->getId() <<", CLOC = " << e.first->getCLOC() << ", cTableEntries = " << e.second.size() << std::endl;
  }*/
  
  
  


  for (auto kv : limTable)
  {
    columbus::lim::asg::base::Base* basePtr = kv.second;
    if (columbus::lim::asg::logical::Member *memberPtr = dynamic_cast<columbus::lim::asg::logical::Member *>(basePtr))
    {
      // Collect all TUs
      std::set<columbus::lim::asg::physical::File*, FileComparator> TUsOfNode;
      for (auto it = memberPtr->getIsContainedInListIteratorAssocBegin(); it != memberPtr->getIsContainedInListIteratorAssocEnd(); ++it)
      {
        columbus::lim::asg::physical::File* filenode = const_cast<columbus::lim::asg::physical::File*>(&(*it));
        for (auto tuNode : fileNode_to_TUNodes[filenode])
          TUsOfNode.insert(tuNode);
      }

      std::set<columbus::lim::asg::base::Component*,ComponentComparator> componentsOfNode;
      for(auto tuNode : TUsOfNode)
      {
        // Add the TUs to the node
        //memberPtr->addCompilationUnit(tuNode->getId());

        // In the meantime, collect all components for the TU
        for (const auto &component : linker.file_to_components[tuNode])
          componentsOfNode.insert(component);
      }

      // Add the components to the node
      for(auto component : componentsOfNode)
        memberPtr->addBelongsTo(component);

    }
  }
  linker.link_unresolved_declarations();
  linker.link_unresolved_calls();
  linker.link_unresolved_attribute_accesses();

}

void GlobalASTConversionInfo::addMemberToScopeList(columbus::lim::asg::SourcePosition &position, columbus::lim::asg::logical::Member * member, columbus::lim::asg::physical::File *file)
{
  MyScope scope{ SourcePoint{position.getLine(),position.getColumn()},
               SourcePoint{position.getEndLine(),position.getEndColumn()},
               member};
  scopeListPerFile[file].push_back(ScopeGuard{ scope, ScopeGuard::GuardType::BEGIN });
  scopeListPerFile[file].push_back(ScopeGuard{ scope, ScopeGuard::GuardType::END });
}

void GlobalASTConversionInfo::addGlobalNamespaceToScopeList(std::vector<ScopeGuard> &scopeList)
{
  columbus::lim::asg::logical::Member* globalNS = limFactory.getRoot();
  MyScope scope{ SourcePoint{0,0},
               SourcePoint{UINT_MAX, UINT_MAX},
               globalNS};
  scopeList.push_back(ScopeGuard{ scope, ScopeGuard::GuardType::BEGIN });
  scopeList.push_back(ScopeGuard{ scope, ScopeGuard::GuardType::END });
}

