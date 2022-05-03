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

#include "../inc/CppSerializeAST.h"
#include "../inc/messages.h"
#include "../inc/Config.h"
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CompilationDatabase.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/FileSup.h>
#include <common/inc/Stat.h>
#include <common/inc/StringSup.h>
#include <clangsupport/ASTIDMapGenerator.h>
#include <Exception.h>
#include <stack>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <cerrno>

using namespace std;
using namespace llvm;
using namespace clang;
using namespace common;
using namespace tooling;


using columbus::FilterState;

extern Config config;

namespace columbus
{
  void updateMemoryStat(Config &config, const char* msg = nullptr);
}

ASTSerializerConsumer::ASTSerializerConsumer(columbus::SerializationData& serializationData, CppCloneVisitor* ccVitor)
  : serializationData(serializationData)
  , ccVitor(ccVitor)
  , prevPath()
  , prevLine (0)
  , filter(ccVitor->getFilter())
  , filterLogStream(ccVitor->getFilterLogStream())
{
}

string getCannocializedPath(ASTContext &context, common::Cache<clang::FileID, std::string>& cannonicalizedPathCache, clang::FileID fileID)
{
  string path;
  const auto cacheSearchResult = cannonicalizedPathCache.getValue(fileID);

  if(cacheSearchResult.found)
    path = cacheSearchResult.value;
  else
  {
    if (fileID.isValid())
    {
      const auto fileEntry = context.getSourceManager().getFileEntryForID(fileID);
      if (fileEntry != nullptr)
      {
        path = pathCanonicalize(fileEntry->getName().str());
        path = path.c_str();
      }
    }

    cannonicalizedPathCache.setValue(fileID, path);
  }

  return path;
}

void ASTSerializerConsumer::addSeparator()
{
  serializationData.nodeKindSequence.push_back(ccVitor->getSeparator());
  serializationData.nodeInfoSequence.push_back(NULL);
}


void ASTSerializerConsumer::HandleTranslationUnit(ASTContext &context)
{
  auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("HandleTranslationUnit()");

  ASTSerializerVisitor::NodeList pre, post;
  shared_ptr<columbus::NodeIDMaps> nodeIds;
  if (context.getTranslationUnitDecl() != nullptr)
  {
    nodeIds = columbus::generateNodeIDMaps(context);
    pre.reserve(nodeIds->id2node.size());
    post.reserve(nodeIds->id2node.size());
    perfSectionHandler.addTimeStamp("generateNodeIDMaps");
    ASTSerializerVisitor(context, false, pre, ccVitor, localSerializationData).TraverseDecl(context.getTranslationUnitDecl());
    perfSectionHandler.addTimeStamp("ASTSerializerVisitor-pre");
    ASTSerializerVisitor(context, true, post, ccVitor, localSerializationData).TraverseDecl(context.getTranslationUnitDecl());
    perfSectionHandler.addTimeStamp("ASTSerializerVisitor-post");
  }

  ASTSerializerVisitor::NodeList merged;
  merged = ASTSerializerVisitor::merge(pre, post);
  columbus::updateMemoryStat(config);

  perfSectionHandler.addTimeStamp("ASTSerializerVisitor-merge");

  common::Cache<clang::FileID, std::string> cannonicalizedPathCache;
  columbus::ASTFilter myFilter(config.filterfile, context, &cannonicalizedPathCache, true, true); // softfilter
  perfSectionHandler.addTimeStamp("ASTSerializerVisitor-filter");

  //Needed for the line filter. If the given line already had visited then we skip that subtree.
  bool isSerializationTurnedOn = true;
  void* turnOnAt;
  
  columbus::NodeId prevLimNode = 0;
  set <void*> serializedNodes;

  for(auto& nodeInfo : merged)
  {
    nodeInfo.nodeId = nodeIds->node2id[nodeInfo.nodePtr];
    unsigned line = nodeInfo.line_start;

/*
    // DEBUG
    if (nodeInfo.nodeId == 0)
    {
      printf(".");
      fflush(stdout);
    }
*/
    /////////////////////// create cp objects ///////////////////////
    if (!((nodeInfo.nodeKind & NodeMask::NodeEndMask) == NodeEndType::NodeEnd))
    {
      ccVitor->updateLimNodeStack(nodeInfo.nodeId, false);

        
      if(isSerializationTurnedOn)
      {
        std::string lPath = getCannocializedPath(context, cannonicalizedPathCache, nodeInfo.pathID);

        if (lPath.empty())
          continue;

        if (serializationData.visitedLines.count(columbus::LineIdentifier(ccVitor->getLimFactory().getStringTable().get(lPath),line)) != 0)
        {
          common::WriteMsg::write(common::WriteMsg::mlDDebug,"\nThe %s %d has already been visited.\n", lPath.c_str(),line);
          
          //insert the last visited line
          serializationData.visitedLines.insert(columbus::LineIdentifier(ccVitor->getLimFactory().getStringTable().set(prevPath.c_str()),prevLine));
          prevPath = lPath;
          prevLine = line;
          
          //turn off the serialization and save the pointer when we have to turn on again
          isSerializationTurnedOn = false;
          turnOnAt = nodeInfo.nodePtr;
          continue;
        }
        
        if((ccVitor->getPrevPath() != lPath) && ccVitor->getFileNamesByComponent())
        {
          ccVitor->assignSrcFileToComponenet(lPath, ccVitor->getCurrentLimComponent());
          ccVitor->setPrevPath(lPath);
          addSeparator();  // File separator
/*
          // Debug
          printf("LineChange: %s\n", lPath.c_str());
*/
        }
    
        //softfilter && limfilter
        if ((myFilter.getFilterState(nodeInfo.nodePtr) == FilterState::NotFiltered) &&
            (!ccVitor->isFilteredInLim(ccVitor->getCurrentLimNode())))
        {
          
          //line filter
          if ((prevPath!=lPath || line!=prevLine) && lPath != "")
          {
            serializationData.visitedLines.insert(columbus::LineIdentifier(ccVitor->getLimFactory().getStringTable().set(prevPath.c_str()),prevLine));
            prevPath = lPath;
            prevLine = line;
          }

          //check in pattern filter
          if(filter != NULL && filter->find(nodeInfo.nodeId) != filter->end())
          {
            if (filterLogStream)
              *filterLogStream << "Pattern filter remove: " << lPath << " [" << nodeInfo.line_start << ":" << nodeInfo.column_start << " | " << nodeInfo.line_end << ":" << nodeInfo.column_end << "] (" << nodeInfo.nodeKind << ")\n";
          }
          else
          {
            ASTNodeInfo *astNodeInfo = new ASTNodeInfo(lPath,
                                              nodeInfo.line_start,
                                              nodeInfo.column_start,
                                              nodeInfo.line_end,
                                              nodeInfo.column_end,
                                              nodeInfo.nodeId,
                                              ccVitor->getCurrentLimNode(),
                                              ccVitor->getCurrentTranslationUnitId(),
                                              ccVitor->getCurrentTranslationUnitPath(),
                                              ccVitor->getCurrentLimComponent());

            auto extraLineInfoIt = localSerializationData.ASTNodeExtraLineMap.find(nodeInfo.nodePtr);

            if (extraLineInfoIt != localSerializationData.ASTNodeExtraLineMap.end())
            {
              for (auto line : extraLineInfoIt->second)
              {
/*
                // Debug
                printf("Extra Sor: %d\n", line);
*/
                astNodeInfo->addLine(line);
              }
            }

            //cp->dump();
            auto nodeKind = nodeInfo.nodeKind;
            if (config.ofc &&
                ((nodeKind & NodeMask::NodeTypeMask) == NodeType::Declaration) &&
                (((nodeKind & NodeMask::NodeKindMask) == clang::Decl::Kind::Function) || ((nodeKind & NodeMask::NodeKindMask) == clang::Decl::Kind::CXXMethod)))
            {
              addSeparator();
            }

            serializationData.nodeKindSequence.push_back(nodeKind);
            serializationData.nodeInfoSequence.push_back(astNodeInfo);
            serializedNodes.insert(nodeInfo.nodePtr);
            
            if(prevLimNode != ccVitor->getCurrentLimNode())
              prevLimNode = ccVitor->getCurrentLimNode();
          }
        }
        else
        {
          //filtered in ast or in LIM
        }
        
      }
      else
      {
        //serialization turned off
      }
      
    }
    else // end node
    {
      ccVitor->updateLimNodeStack(0, true);
      if(isSerializationTurnedOn)
      {
        //softfilter
        if (myFilter.getFilterState(nodeInfo.nodePtr) == FilterState::NotFiltered)
        {
          const auto cacheSearchResult = cannonicalizedPathCache.getValue(nodeInfo.pathID);

          if (cacheSearchResult.found && cacheSearchResult.value.empty())
            continue;

          //lim filter
          if( !ccVitor->isFilteredInLim(ccVitor->getCurrentLimNode()))
          {
            // pattern filter
            if(filter == NULL || filter->find(nodeInfo.nodeId) == filter->end())
            {
              serializationData.nodeKindSequence.push_back(-2);
              serializationData.nodeInfoSequence.push_back(NULL);
            }
          }
        }
      }
      else
      {
        if(nodeInfo.nodePtr == turnOnAt)
        {
          isSerializationTurnedOn = true;
          turnOnAt = nullptr;
        }
      }
    }
      
  } // end for

  columbus::updateMemoryStat(config);

  //insert into the last visited line
  serializationData.visitedLines.insert(columbus::LineIdentifier(ccVitor->getLimFactory().getStringTable().set(prevPath.c_str()),prevLine));

  /////////////////////// END cp objects ///////////////////////
  perfSectionHandler.addTimeStamp("for");

  //convert local references map's pointers to ASTNodeInfo references
  columbus::Key currentASTPathKey = ASTNodeInfo::getPathKey(ccVitor->getCurrentTranslationUnitPath());
  for(auto reference : localSerializationData.ASTNodeReferenceMap)
  {
    const auto fromNode = nodeIds->node2id[reference.first];
    const auto toNode = nodeIds->node2id[reference.second];
    if ((toNode == 0) || (fromNode == 0))
      continue;

    bool serializedEndNode = false;
    if (serializedNodes.find(reference.first) != serializedNodes.end())
      serializedEndNode = true;
    else if (serializedNodes.find(reference.second) != serializedNodes.end())
      serializedEndNode = true;

    // At least one end of the reference edge is serialized so we store the reference
    if (serializedEndNode)
    {
      serializationData.referencesMap[currentASTPathKey][fromNode] = toNode;
      serializationData.nodeReferencePathMap[currentASTPathKey][fromNode] = ASTNodeInfo::getPathKey(getCannocializedPath(context, cannonicalizedPathCache, localSerializationData.ASTNodeFileIDMap[reference.first]));
      serializationData.nodeReferencePathMap[currentASTPathKey][toNode] = ASTNodeInfo::getPathKey(getCannocializedPath(context, cannonicalizedPathCache, localSerializationData.ASTNodeFileIDMap[reference.second]));
    }
  }

  columbus::updateMemoryStat(config);

  addSeparator(); // Translation unit separator
//  Debug
//  ASTSerializerVisitor::dumpNodeList(merged, &context);
//  for (size_t i = 0; i < serializationData.nodeKindSequence.size(); ++i)
//  {
//      auto nodeKind = serializationData.nodeKindSequence[i];
//      auto nodeInfo = serializationData.nodeInfoSequence[i];
//      if (nodeInfo)
//        WriteMsg::write(WriteMsg::mlDebug, "0x%08X  File:%s Line:%d Col:%d\n", nodeKind, nodeInfo->getStringPath().c_str(), nodeInfo->getLine(), nodeInfo->getCol());
//      else
//        WriteMsg::write(WriteMsg::mlDebug, "0x%08X\n", nodeKind);
//
//  }
//  perfSectionHandler.addTimeStamp("ref map conversion");
}


ASTSerializerVisitor::ASTSerializerVisitor(ASTContext &context, bool post, NodeList& nodes, CppCloneVisitor* ccVitor, LocalSerializationData &localSerializationData)
  : context(context)
  , post (post)
  , nodes (nodes)
  , ccVitor(ccVitor)
  , localSerializationData(localSerializationData)
{}

bool ASTSerializerVisitor::VisitStmt(Stmt *s)
{
  if (post)
    nodes.push_back({s, clang::FileID(), ((std::uint32_t)s->getStmtClass() & NodeMask::NodeKindMask) | NodeType::Statement | NodeEndType::NodeEnd, 0, 0, 0, 0, 0 });
  else
  {
    nodes.push_back({s, clang::FileID(), ((std::uint32_t)s->getStmtClass() & NodeMask::NodeKindMask) | NodeType::Statement, 0, 0, 0, 0, 0 });
    ccVitor->incVisitedNodes();
  }
  fillLocationInfo(s, nodes.back());

  // collect references for CE metirc
  if (!post)
  {
    if(clang::DeclRefExpr::classof(s))
    {
      clang::DeclRefExpr* ref = llvm::dyn_cast<clang::DeclRefExpr>(s);
      addToRefernceMaps(ref->getDecl(), s);
    }
    else if (clang::MemberExpr::classof(s))
    {
      clang::MemberExpr* memberRef = llvm::dyn_cast<clang::MemberExpr>(s);
      clang::ValueDecl *memberDecl = nullptr;
      if ((memberRef != nullptr) && ((memberDecl = memberRef->getMemberDecl()) != nullptr))
        addToRefernceMaps(memberDecl, s);
    }
    else if (clang::ExplicitCastExpr::classof(s))
    {
      const clang::ExplicitCastExpr* explicitCast = llvm::dyn_cast<clang::ExplicitCastExpr>(s);
      if (explicitCast != nullptr)
      {
        addToRefernceMaps(getReferencedRecordDecl(explicitCast->getTypeAsWritten().getTypePtr()), s);
      }
    }
    else if (clang::BinaryOperator::classof(s))
    {
      const clang::BinaryOperator* binaryOperator = llvm::dyn_cast<clang::BinaryOperator>(s);
      if (binaryOperator->isLogicalOp())
        nodes.back().nodeKind |= NodeBOType::LogicalBinaryOperator;
    }
    else if (clang::IfStmt::classof(s))
    {
      const clang::IfStmt* ifStmt = llvm::dyn_cast<clang::IfStmt>(s);

      addExtraLineInfo(s, ifStmt->getIfLoc());
      if (ifStmt->getElse() != nullptr)
        addExtraLineInfo(s, ifStmt->getElseLoc());
    }

  }
  return true;
}


void ASTSerializerVisitor::addToRefernceMaps(clang::Decl* decl, void *node)
{
  if (decl == nullptr)
    return;

  NodeInfo referencedPositionInfo;
  fillLocationInfo(decl, referencedPositionInfo);

  localSerializationData.ASTNodeReferenceMap[node] = decl;
  localSerializationData.ASTNodeFileIDMap[node] = nodes.back().pathID;
  localSerializationData.ASTNodeFileIDMap[decl] = referencedPositionInfo.pathID;
}

void ASTSerializerVisitor::addExtraLineInfo(void* node, const SourceLocation& sourceLocation)
{
  localSerializationData.ASTNodeExtraLineMap[node].insert(context.getSourceManager().getPresumedLineNumber(sourceLocation));
}



bool ASTSerializerVisitor::VisitDecl(Decl *d)
{
  if (post)
    nodes.push_back({d, clang::FileID(), ((std::uint32_t)d->getKind() & NodeMask::NodeKindMask) | NodeType::Declaration | NodeEndType::NodeEnd, 0, 0, 0, 0, 0 });
  else
  {
    nodes.push_back({d, clang::FileID(), ((std::uint32_t)d->getKind() & NodeMask::NodeKindMask) | NodeType::Declaration, 0, 0, 0, 0, 0 });
    ccVitor->incVisitedNodes();


    // collect extra line info for CLLC and LLDC
    if (clang::TagDecl::classof(d))
    {
      clang::TagDecl* tagDecl = llvm::dyn_cast<clang::TagDecl>(d);
      if (tagDecl->getBraceRange().isValid())
      {
        auto braceRange = tagDecl->getBraceRange();

        // Since the end of the braceRange is probably the same as the end
        // position of the node we dont have to add it
        addExtraLineInfo(d, braceRange.getBegin());
      }
    }

    // collect references for CE metirc
    if (clang::VarDecl::classof(d))
    {
      clang::VarDecl* varDecl = llvm::dyn_cast<clang::VarDecl>(d);
      addToRefernceMaps(getReferencedRecordDecl(varDecl->getType().getTypePtr()), d);
    }
  }
  
  fillLocationInfo(d, nodes.back()); // TODO: Calculate it only in preorder mode and reuse it in the postorder visit
  return true;
}


clang::RecordDecl* ASTSerializerVisitor::getReferencedRecordDecl(const clang::Type* typePtr) const
{
  if (clang::RecordType::classof(typePtr))
  {
    const clang::RecordType* recordType = llvm::dyn_cast<clang::RecordType>(typePtr);
//    recordType->getDecl()->dump();
    return recordType->getDecl();
  }
  else if (clang::PointerType::classof(typePtr))
  {
    const clang::PointerType* pointerType = llvm::dyn_cast<clang::PointerType>(typePtr);
    return getReferencedRecordDecl(pointerType->getPointeeType().getDesugaredType(context).getTypePtr());
  }
  else if (clang::ReferenceType::classof(typePtr))
  {
    const clang::ReferenceType* referenceType = llvm::dyn_cast<clang::ReferenceType>(typePtr);
    return getReferencedRecordDecl(referenceType->getPointeeType().getDesugaredType(context).getTypePtr());
  }
  else if (clang::MemberPointerType::classof(typePtr))
  {
    const clang::MemberPointerType* memberPointerType = llvm::dyn_cast<clang::MemberPointerType>(typePtr);
    return getReferencedRecordDecl(memberPointerType->getClass());
  }
  else if (clang::ArrayType::classof(typePtr))
  {
    const clang::ArrayType* arrayType = llvm::dyn_cast<clang::ArrayType>(typePtr);
    return getReferencedRecordDecl(arrayType->getElementType().getDesugaredType(context).getTypePtr());
  }

  return nullptr;
}

template<typename T>
void ASTSerializerVisitor::fillLocationInfo(T* node, NodeInfo& nodeInfo)
{
  PresumedLoc PLoc_start, PLoc_end;
  const SourceManager& sm = context.getSourceManager();

  PLoc_start = sm.getPresumedLoc(node->getBeginLoc());
  PLoc_end = sm.getPresumedLoc(node->getEndLoc());

  if (PLoc_start.isValid() && PLoc_end.isValid())
  {
    nodeInfo.pathID = PLoc_start.getFileID();
    nodeInfo.line_start = PLoc_start.getLine();
    nodeInfo.column_start = PLoc_start.getColumn();
    nodeInfo.line_end = PLoc_end.getLine();
    nodeInfo.column_end = PLoc_end.getColumn();
  }
}

bool ASTSerializerVisitor::shouldTraversePostOrder() const
{
  return post;
}

ASTSerializerVisitor::NodeList ASTSerializerVisitor::merge(const NodeList& pre, const NodeList& post)
{
  NodeList result;
  stack<void*> nodeStack;
  auto preItemIterator = pre.begin();
  auto postItemIterator = post.begin();

  if (pre.size() != post.size())
  {
    WriteMsg::write(CMSG_DIFFERENT_NUMBER_OF_VISITED_NODES, pre.size(), post.size());
    for (auto& preNode : pre)
    {
      auto found = find_if(post, [&preNode](auto& postNode){return preNode.nodePtr == postNode.nodePtr; });
      if (found == post.end())
      {
        WriteMsg::write(CMSG_MISSING_NODE_FORM_POSTORDER, preNode.nodePtr, preNode.nodeKind);
        dumpNodeInfo(preNode, nullptr);
      }
    }
    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_MERGE_FAILED);
  }
  
  result.reserve(pre.size() * 2);
  // Insert the first element into the stack
  nodeStack.push(preItemIterator->nodePtr);
  result.push_back(*preItemIterator);
  ++preItemIterator;
  
  while (postItemIterator != post.end())
  {
    if (!nodeStack.empty() && (nodeStack.top() == postItemIterator->nodePtr))
    {
      result.push_back(*postItemIterator);
      ++postItemIterator;
      nodeStack.pop();
    }
    else
    {
      if(preItemIterator == pre.end()){
        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_MERGE_FAILED);
      }
      result.push_back(*preItemIterator);
      nodeStack.push(preItemIterator->nodePtr);
      ++preItemIterator;
    }
  }
  
  return result;
}

void ASTSerializerVisitor::dumpNodeInfo(const NodeInfo& nodeInfo, ASTContext *context)
{
  WriteMsg::write(WriteMsg::mlDebug, "%p (0x%08X):", nodeInfo.nodePtr, nodeInfo.nodeKind);
  switch (nodeInfo.nodeKind & NodeMask::NodeTypeMask)
  {
    case NodeType::Statement:
    {
      Stmt* stmt = static_cast<Stmt*>(nodeInfo.nodePtr);
      WriteMsg::write(WriteMsg::mlDebug, "%s", stmt->getStmtClassName());
      dumpLineInfo(context, stmt, nodeInfo.nodeKind);
      break;

    }
    case NodeType::Declaration:
    {
      Decl* decl = static_cast<Decl*>(nodeInfo.nodePtr);
      WriteMsg::write(WriteMsg::mlDebug, "%s", decl->getDeclKindName());
      dumpLineInfo(context, decl, nodeInfo.nodeKind);
      break;
    }
  }
  WriteMsg::write(WriteMsg::mlDebug, "\n");
}

void ASTSerializerVisitor::dumpNodeList(const ASTSerializerVisitor::NodeList& nodes, ASTContext *context)
{
  for (auto& nodeInfo : nodes)
  {
    dumpNodeInfo(nodeInfo, context);
  }
}

template<typename T>
void ASTSerializerVisitor::dumpLineInfo(ASTContext *context, T* node, int nodeKind)
{
  if (context == nullptr)
    return;

  FullSourceLoc fullLocation;
  if ((nodeKind & NodeMask::NodeEndMask) == NodeEndType::NodeEnd)
    fullLocation = context->getFullLoc(node->getEndLoc());
  else
    fullLocation = context->getFullLoc(node->getBeginLoc());

  if (fullLocation.isValid())
    WriteMsg::write(WriteMsg::mlDebug, " %s", fullLocation.printToString(context->getSourceManager()).c_str());
}

SerializeAction::SerializeAction(columbus::SerializationData& serializationData, CppCloneVisitor* ccVitor)
  : serializationData(serializationData)
  , ccVitor(ccVitor)
  {}
  
unique_ptr<ASTConsumer> SerializeAction::CreateASTConsumer(CompilerInstance &Compiler, StringRef InFile)
{
  return unique_ptr<ASTConsumer>(new ASTSerializerConsumer(serializationData, ccVitor));
}


/////////////////////////////////
//
// CppCloneVisitor definitions
//
/////////////////////////////////


CppCloneVisitor::CppCloneVisitor(columbus::LimOrigin& limOrigin, columbus::lim::asg::Factory* limFactory) 
    : limOrigin(limOrigin)
    , limFactory(limFactory)
    , filter(NULL)
    , visitedNodes(0)
    , uniqueValue(-1)
    , decDepthSign(-2)
    , separatorCounter(-3)
    , prevPath("")
    , fileNamesByComponent(nullptr)
    , tuPathToCompAndTuId(nullptr)
    , filterLogStream(nullptr)
    {}


void CppCloneVisitor::serializeComponent(const list<string>& compilationUnits, columbus::SerializationData& serializationData)
{
  auto perfSectionHandler = common::PerformanceLogger::getPerformanceLogger().startSection("serializeComponent()");

  tooling::FixedCompilationDatabase compilationDatabase(".", { "-fno-delayed-template-parsing" });
  
  for (auto& compilationUnit : compilationUnits)
  {
    if (common::pathFindExtension(compilationUnit) != "ast")
      continue;

    if (!common::pathFileExists(compilationUnit))
    {
      common::WriteMsg::write(CMSG_NO_COMPILATION_UNIT_FOUND, compilationUnit.c_str());
      continue;
    }

    columbus::NodeId compilationUnitId = getLimCompilationIdByName(compilationUnit);
    if (compilationUnitId != 0)
    {
      setCurrentTranslationUnitId(compilationUnitId);
      currentTUPath = compilationUnit;
      if(tuPathToCompAndTuId){
        auto it = (*tuPathToCompAndTuId).find(currentTUPath);
        if(it == tuPathToCompAndTuId->end() ){
          (*tuPathToCompAndTuId)[currentTUPath] = make_pair<columbus::NodeId, columbus::NodeId>(getCurrentLimComponent(), getCurrentTranslationUnitId());
        }
      }

      tooling::ClangTool Tool(compilationDatabase, {compilationUnit});
      Tool.clearArgumentsAdjusters();
      Tool.appendArgumentsAdjuster(tooling::getClangStripOutputAdjuster());
      Tool.appendArgumentsAdjuster(tooling::getInsertArgumentAdjuster("-fsyntax-only", tooling::ArgumentInsertPosition::BEGIN));

      Tool.run(newSerializeActionFactory(serializationData).get());
    }
    else
      throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_NO_COMPILATION_UNIT_FOUND(compilationUnit));
  }
}

unique_ptr<FrontendActionFactory> CppCloneVisitor::newSerializeActionFactory(columbus::SerializationData& serializationData)
{
  class SimpleFrontendActionFactory : public FrontendActionFactory
  {
  public:
    SimpleFrontendActionFactory(columbus::SerializationData& serializationData, CppCloneVisitor* ccVitor)
      : serializationData(serializationData)
      , ccVitor(ccVitor)
    {
    }

    unique_ptr<clang::FrontendAction> create() override { return unique_ptr<clang::FrontendAction>(new SerializeAction(serializationData, ccVitor)); }
  private:
    columbus::SerializationData& serializationData;
    CppCloneVisitor* ccVitor;
  };

  return unique_ptr<FrontendActionFactory>(new SimpleFrontendActionFactory(serializationData, this));
}


void CppCloneVisitor::setFilter(std::set<columbus::NodeId>& filter) {
  this->filter = &filter;
}

void CppCloneVisitor::clearFilter() {
  this->filter = NULL;
}

bool CppCloneVisitor::evoluteLimNode( const ASTNodeInfo* n, bool end ){
  columbus::NodeId parsedLimNodeID = 0;
  
  if (end) {
    if (currentLimNode.size()) {
      currentLimNode.pop();
      return true;
    } else {
      common::WriteMsg::write(CMSG_MORE_END_THEN_BEGIN );
    }
  } else {
    if (parseLimNodeId(n, parsedLimNodeID)) {
      currentLimNode.push(parsedLimNodeID) ;
      return true;
    } else if (currentLimNode.empty()) {
      currentLimNode.push(limFactory->getRoot()->getId()); 
      return true;
    }else{
      currentLimNode.push(currentLimNode.top()); 
    }
  }
  return false;
}

void CppCloneVisitor::updateLimNodeStack(const columbus::NodeId astNodeId, const bool end)
{
  if (end)
  {
    if (currentLimNode.size())
      currentLimNode.pop();
    else
      common::WriteMsg::write(CMSG_MORE_END_THEN_BEGIN);
  }
  else
  {
    columbus::NodeId correspondingLimNodeId = limOrigin.getLimIdToCompIdAndCppId(currentTUId, astNodeId);
    if (correspondingLimNodeId != 0)
      currentLimNode.push(correspondingLimNodeId);
    else if (currentLimNode.empty())
      currentLimNode.push(limFactory->getRoot()->getId());
    else
      currentLimNode.push(currentLimNode.top());
  }
}

bool CppCloneVisitor::parseLimNodeId( const ASTNodeInfo* n, columbus::NodeId& limNodeID ){
  columbus::NodeId tmpNode = limOrigin.getLimIdToCompIdAndCppId( currentTUId, n->getId() );
  if (tmpNode != 0) {
    limNodeID = tmpNode;
    return true;
  }
  return false;
}



columbus::NodeId CppCloneVisitor::getCurrentLimNode(){
  return currentLimNode.empty() ? currentLimComponent : currentLimNode.top();
  //return currentLimNode.empty() ? 0 : currentLimNode.top();
}
void CppCloneVisitor::setCurrentLimComponent(columbus::NodeId id){
  currentLimComponent = id;
}

void CppCloneVisitor::setCurrentTranslationUnitId(columbus::NodeId id){
  currentTUId = id;
}

columbus::NodeId CppCloneVisitor::getCurrentLimComponent(){
  return currentLimComponent;
}

columbus::NodeId CppCloneVisitor::getCurrentTranslationUnitId(){
  return currentTUId;
}

int CppCloneVisitor::getVisitedNodesNumber(){
  return visitedNodes;
}

void CppCloneVisitor::incVisitedNodes(){
  visitedNodes++;
}

void CppCloneVisitor::decVisitedNodes(){
  visitedNodes--;
}

void CppCloneVisitor::resetVisitedNodesNumber(){
  visitedNodes = 0;
}

bool CppCloneVisitor::isSepDecDepthSign(int s) {
  return (s==decDepthSign);
}

int CppCloneVisitor::getUniqueValue() {
  return uniqueValue;
}

int CppCloneVisitor::getDecDepthSign() {
  return decDepthSign;
}

int CppCloneVisitor::getSeparator()
{
  --separatorCounter;
#ifndef NDEBUG
  if(separatorCounter == INT_MIN)
    throw columbus::Exception(COLUMBUS_LOCATION,"Too many separator character created!");
#endif
  return separatorCounter;
}

columbus::NodeId CppCloneVisitor::getLimCompilationIdByName( const std::string& name)
{
  columbus::lim::asg::Factory::TurnFilterOffSafely filterOff(*limFactory);

  const auto* componentNode = static_cast< const columbus::lim::asg::base::Component*>(limFactory->getPointer(currentLimComponent));
  if (componentNode != nullptr)
  {
    for(auto it = componentNode->getCompilationUnitListIteratorBegin(); it != componentNode->getCompilationUnitListIteratorEnd(); ++it)
    {
      if (columbus::lim::asg::Common::getFullPath((*it)) == name)
        return it->getId();
    }
  }

  return 0;
}

const std::string& CppCloneVisitor::getCurrentTranslationUnitPath() const {
  return currentTUPath;
}

const columbus::lim::asg::Factory& CppCloneVisitor::getLimFactory(){
  return *limFactory;
}

//Ez lehet hogy nem is kell
void CppCloneVisitor::assignSrcFileToComponenet( const std::string &lPath ,columbus::NodeId currentLimComponent)
{
  (*fileNamesByComponent)[currentLimComponent].insert(limFactory->getStringTable().set(lPath.c_str()));
  for ( columbus::lim::asg::ListIterator<columbus::lim::asg::base::Base> 
    it = limFactory->getReverseEdges().constIteratorBegin(currentLimComponent,columbus::lim::asg::edkComponent_Contains);
    it != limFactory->getReverseEdges().constIteratorEnd(currentLimComponent,columbus::lim::asg::edkComponent_Contains);
  ++it) {
    assignSrcFileToComponenet(lPath,it->getId());
  }
}

bool CppCloneVisitor::isFilteredInLim(columbus::NodeId limId){
  return limFactory->getIsFiltered(limId);
}

std::set<columbus::NodeId>* CppCloneVisitor::getFilter(){
  return filter;
}

void CppCloneVisitor::setFilterLogStream(std::ostream *out)
{
  filterLogStream = out;
}

std::ostream *CppCloneVisitor::getFilterLogStream() const
{
  return filterLogStream;
}
