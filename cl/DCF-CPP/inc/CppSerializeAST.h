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

#ifndef _DCF_CPP_SERIALIZE_AST_H
#define _DCF_CPP_SERIALIZE_AST_H

#include <clang/StaticAnalyzer/Frontend/FrontendActions.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/Tooling/Tooling.h>
#include <vector>
#include <map>
#include <list>

namespace columbus { class DuplicatedCodeMiner; }

#include "ClonePositioned.h"
#include "Types.h"
#include <lim/inc/lim.h>
#include <lim/inc/LimOrigin.h>
#include <clangsupport/ASTFilter.h>
#include <AsgCommon.h>


enum NodeType
{
  Statement     = 0x00010000,
  Declaration   = 0x00020000
};

enum NodeEndType
{
  NodeStart     = 0x00000000,
  NodeEnd       = 0x01000000
};

enum NodeBOType
{
  LogicalBinaryOperator = 0x02000000
};

enum NodeMask
{
  NodeKindMask  = 0x0000FFFF,
  NodeTypeMask  = 0x00FF0000,
  NodeEndMask   = 0x01000000,
  LogicalBOMask = 0x02000000,
  SeparatorMask = 0x80000000
};

class CppCloneVisitor;


struct LocalSerializationData
{
  std::map<void*, void*> ASTNodeReferenceMap;
  std::map<void*, clang::FileID> ASTNodeFileIDMap; // This is collected for the references only!
  std::map<void*, std::set<int>> ASTNodeExtraLineMap; // Extra info for calculatig logical lines
};

class ASTSerializerConsumer : public clang::ASTConsumer
{
  public:
    ASTSerializerConsumer(columbus::SerializationData& serializationData, CppCloneVisitor* ccVitor);
    virtual void HandleTranslationUnit(clang::ASTContext &context) override;

  private:
    void addSeparator();

  private:
    columbus::SerializationData& serializationData;
    CppCloneVisitor* ccVitor;

    LocalSerializationData localSerializationData;
    std::string  prevPath;
    unsigned int prevLine;
    std::set<columbus::NodeId>* filter;
    std::ostream *filterLogStream;
};

class ASTSerializerVisitor : public clang::RecursiveASTVisitor<ASTSerializerVisitor>
{
  public:

    struct NodeInfo
    {
      void* nodePtr;
      clang::FileID pathID;
      std::uint32_t nodeKind;
      std::uint32_t nodeId;
      std::uint32_t line_start;
      std::uint32_t line_end;
      std::uint16_t column_start;
      std::uint16_t column_end;
    };

    using NodeList = std::vector<NodeInfo>;
   
    ASTSerializerVisitor(clang::ASTContext &context, bool post, NodeList& nodes, CppCloneVisitor* ccVitor, LocalSerializationData& localSerializationData);

    bool VisitStmt(clang::Stmt *s);
    bool VisitDecl(clang::Decl *d);
    bool shouldTraversePostOrder() const;

    clang::RecordDecl* getReferencedRecordDecl(const clang::Type* typePtr) const;
    void addToRefernceMaps(clang::Decl* decl, void *node);

    template<typename T>
    void fillLocationInfo(T* node, NodeInfo& nodeInfo);

    void addExtraLineInfo(void* node, const clang::SourceLocation& sourceLocation);

    static NodeList merge(const NodeList& pre, const NodeList& post);
    static void dumpNodeInfo(const NodeInfo& nodeInfo, clang::ASTContext *context);
    static void dumpNodeList(const NodeList& nodes, clang::ASTContext *context);
    template<typename T>
    static void dumpLineInfo(clang::ASTContext *context, T* node, int nodeKind);
    

  private:
    clang::ASTContext &context;
    bool post;
    NodeList& nodes;
    CppCloneVisitor* ccVitor;
    LocalSerializationData &localSerializationData;
};

class SerializeAction : public clang::ASTFrontendAction
{
  public:
    SerializeAction(columbus::SerializationData& serializationData, CppCloneVisitor* ccVitor);
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile);

  private:
     columbus::SerializationData& serializationData;
     CppCloneVisitor* ccVitor;
};



class CppCloneVisitor
{
private:
  columbus::LimOrigin&          limOrigin;
  columbus::lim::asg::Factory*  limFactory;
  
  std::set<columbus::NodeId>* filter;
  int visitedNodes;
  
  const int uniqueValue;
  const int decDepthSign;
  int separatorCounter;
  
  std::string  prevPath;
  std::map<columbus::NodeId,std::set<columbus::Key> >* fileNamesByComponent;
  std::map<std::string, std::pair<columbus::NodeId, columbus::NodeId>>* tuPathToCompAndTuId;
  
  std::stack<columbus::NodeId> currentLimNode;
  columbus::NodeId currentLimComponent;
  columbus::NodeId currentTUId;
  std::string currentTUPath;
  std::ostream *filterLogStream;
  
  bool parseLimNodeId( const ASTNodeInfo* n, columbus::NodeId& limNodeID );
  columbus::NodeId getLimCompilationIdByName( const std::string& name );
  
public:
  CppCloneVisitor(columbus::LimOrigin& limOrigin, columbus::lim::asg::Factory* limFactory);
  
  void serializeComponent(const std::list<std::string>& compilationUnits, columbus::SerializationData& serializationData);
  std::unique_ptr<clang::tooling::FrontendActionFactory> newSerializeActionFactory(columbus::SerializationData& serializationData);
  
  void setFilter(std::set<columbus::NodeId>& filter);
  std::set<columbus::NodeId>* getFilter();
  void clearFilter();
  
  bool evoluteLimNode( const ASTNodeInfo* n, bool end );
  void updateLimNodeStack(columbus::NodeId astNodeId, bool end);
  columbus::NodeId getCurrentLimNode();
  void setCurrentLimComponent(columbus::NodeId id);
  void setCurrentTranslationUnitId(columbus::NodeId id);
  columbus::NodeId getCurrentLimComponent();
  columbus::NodeId getCurrentTranslationUnitId();
  const std::string& getCurrentTranslationUnitPath() const;
  int getVisitedNodesNumber();
  void incVisitedNodes();
  void decVisitedNodes();
  void resetVisitedNodesNumber();
  bool isSepDecDepthSign(int s);
  int getUniqueValue();
  int getDecDepthSign();
  int getSeparator();

  void setFileNamesByComponent(std::map<columbus::NodeId,std::set<columbus::Key> >* val) { fileNamesByComponent = val; }
  void setTuPathToCompAndTuId( std::map<std::string, std::pair<columbus::NodeId, columbus::NodeId>>* val) { tuPathToCompAndTuId = val; }
  bool isFilteredInLim(columbus::NodeId limId);
  
  const columbus::lim::asg::Factory& getLimFactory();
  void assignSrcFileToComponenet( const std::string &lPath, columbus::NodeId currentLimComponent );
  std::string& getPrevPath(){ return prevPath; }
  void setPrevPath(const std::string& val){ prevPath = val; }
  const std::map<columbus::NodeId,std::set<columbus::Key> >* getFileNamesByComponent(){ return fileNamesByComponent; }
  const std::map<std::string, std::pair<columbus::NodeId, columbus::NodeId>>* getTuPathToCompAndTuId(){ return tuPathToCompAndTuId; }
  void setFilterLogStream(std::ostream *out);
  std::ostream *getFilterLogStream() const;
};

#endif
