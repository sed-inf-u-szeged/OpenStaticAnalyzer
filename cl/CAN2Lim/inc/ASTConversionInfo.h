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

#ifndef _CAN2LIM_AST_CONVERSION_INFO_H
#define _CAN2LIM_AST_CONVERSION_INFO_H

#include "MergeUID.h"
#include "CommentProcessor.h"
#include <clangsupport/CANCommon.h>

#include <clang/Metrics/Output.h>
#include <llvm/Support/FileSystem/UniqueID.h>
#include <clangsupport/ASTIDMapGenerator.h>
#include <clang/AST/Mangle.h>
#include <lim/inc/lim.h>
#include "Linker.h"
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <set>

class GlobalASTConversionInfo
{
private:
  // Helper for UID hashing.
  struct UIDHasher
  {
    typedef std::shared_ptr<const clang::metrics::UID> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& o) const
    {
      if (!o)
        return 0;

      return o->hash();
    }
  };

  // Helper for UID equivalence.
  struct UIDEq
  {
    typedef std::shared_ptr<const clang::metrics::UID> first_argument_type;
    typedef std::shared_ptr<const clang::metrics::UID> second_argument_type;
    typedef bool result_type;

    result_type operator()(const first_argument_type& lhs, const second_argument_type& rhs) const
    {
      if (!lhs || !rhs)
        return lhs.get() == rhs.get();

      return lhs->equals(*rhs);
    }
  };

  // Helper for UID equivalence.
  struct NoPosUIDEq
  {
    typedef std::shared_ptr<const MergeUID> first_argument_type;
    typedef std::shared_ptr<const MergeUID> second_argument_type;
    typedef bool result_type;

    result_type operator()(const first_argument_type& lhs, const second_argument_type& rhs) const
    {
      if (!lhs || !rhs)
        return lhs.get() == rhs.get();

      return lhs->noPositionEquals(*rhs);
    }
  };

public:
  GlobalASTConversionInfo(columbus::lim::asg::Factory& limFactory, const clang::metrics::Output& output, columbus::LimOrigin& origin);

  columbus::lim::asg::Factory& limFactory;
  const clang::metrics::Output& metricsOutput;

  columbus::LimOrigin& limOrigin;

    // Filter the folders based on the filter-file
    void filterFolders();

  // Matches UIDs to LIM nodes.
  std::unordered_map<std::shared_ptr<clang::metrics::UID>, columbus::lim::asg::base::Base*, UIDHasher, UIDEq> limTable;

  // Matches UIDs to LIM Types.
  std::unordered_map<std::shared_ptr<clang::metrics::UID>, columbus::lim::asg::type::Type*, UIDHasher, UIDEq> typeTable;

  std::unordered_set<std::shared_ptr<clang::metrics::UID>, UIDHasher, UIDEq> incompleteNodes;

  CommentProcessor commentProcessor;

  // Called after all ASTs have been converted.
  void finalizeConversion();

  void addMemberToScopeList(columbus::lim::asg::SourcePosition& position, columbus::lim::asg::logical::Member* member, columbus::lim::asg::physical::File* file);

  void addGlobalNamespaceToScopeList(std::vector<ScopeGuard>& scopeList);

  // Stores scope beginning and endings for positioned elements (used for comment processing)
  // TODO: Duplicate
  struct FileComparator
  {
    bool operator()(const columbus::lim::asg::physical::File* lhs, const columbus::lim::asg::physical::File* rhs) const
    {
      return lhs->getId() < rhs->getId();
    }
  };
  std::map<columbus::lim::asg::physical::File*, std::vector<ScopeGuard>, FileComparator> scopeListPerFile;

  //We have to store namespaces and only add their metrics at the end (since for example the LOC of a namespace may grow during the processing of different TUs)
  std::vector<std::pair<columbus::lim::asg::logical::Package*, std::shared_ptr<clang::metrics::UID>>> namespaces;

  // Linker singleton
  Linker& linker;

  // A map for the files that we have created in the LIM.
  // They key is the filename, in the format of clang FileEntry->getName()
  // The value is a pointer to the LIM file node
  //std::unordered_map<std::string, columbus::lim::asg::physical::File*> fileLibrary;

  std::string changePathFrom;
  std::string changePathTo;

  std::map<const std::string, columbus::lim::asg::physical::File*> correctedFileNameToFileNode;
  std::map<const std::string, columbus::lim::asg::physical::File*> canonicalFileNameToFileNode;

  //TODO: refactor this later
  std::map<llvm::sys::fs::UniqueID, columbus::lim::asg::physical::File*> filesAlreadyProcessed;

  std::map<columbus::lim::asg::physical::File*, std::set<columbus::lim::asg::physical::File*, FileComparator>> fileNode_to_TUNodes;

  struct ASTIdentifier
  {
    std::string fileName;
    uintmax_t fileSize;
    ASTIdentifier() {}
    ASTIdentifier(const std::string& fullPath)
      : fileName(common::pathFindFileName(fullPath)),
      fileSize(boost::filesystem::file_size(fullPath))
    {}

    bool operator<(const ASTIdentifier& rhs) const
    {
      return std::tie(this->fileSize, this->fileName) < std::tie(rhs.fileSize, rhs.fileName);
    }
    bool operator==(const ASTIdentifier& rhs) const
    {
      return std::tie(this->fileSize, this->fileName) == std::tie(rhs.fileSize, rhs.fileName);
    }
  };

  std::map<ASTIdentifier, std::set<columbus::lim::asg::base::Component*>> componentsOfTU;
};

class GlobalASTConversionInfo_ThreadSafe
{
  GlobalASTConversionInfo& globalASTConversionInfo;
  boost::recursive_mutex globalASTConversionInfoMutex;

public:
  GlobalASTConversionInfo_ThreadSafe(GlobalASTConversionInfo& globalASTConversionInfo) : globalASTConversionInfo(globalASTConversionInfo) {}
  template <class Operation>
  auto call(Operation o) -> decltype(o(globalASTConversionInfo))
  { 
    boost::lock_guard<boost::recursive_mutex> lock(globalASTConversionInfoMutex);
    return o(globalASTConversionInfo);
  }
};

class ASTConversionInfo
{
public:
  ASTConversionInfo(const std::string ASTFilename, const std::string compilationUnitName, GlobalASTConversionInfo_ThreadSafe& globalInfo, MergeUIDFactory& uidFactory);

  // The name of the AST file.
  const std::string ASTFilename;

  // The full path of the AST file.
  const std::string compilationUnitName;

  // Pointer to the current AST file being processed.
  columbus::lim::asg::physical::File* pCurrentASTFile = nullptr;

  std::unordered_map<const clang::FileEntry*, columbus::lim::asg::physical::File*> filesOfTU;

  // Uniquely identifies an AST file based on it's full path and file size
  const GlobalASTConversionInfo::ASTIdentifier currentASTIdentifier;

  std::shared_ptr<columbus::NodeIDMaps> originMap;

  std::map<const clang::Decl*,const clang::LambdaExpr*> lambdaCallOpExprMap;

  GlobalASTConversionInfo_ThreadSafe& globalInfo;

  // The Mangle context.
  std::shared_ptr<clang::MangleContext> pMyMangleContext;

  MergeUIDFactory& uidFactory;
};

extern class CANFilePathRenamer cANFilePathRenamer;

#endif
