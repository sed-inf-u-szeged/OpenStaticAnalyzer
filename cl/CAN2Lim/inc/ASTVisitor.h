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

#ifndef _CAN2LIM_AST_VISITOR_H
#define _CAN2LIM_AST_VISITOR_H

#include <clang/StaticAnalyzer/Frontend/FrontendActions.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/Tooling/Tooling.h>

#include <clangsupport/ASTFilter.h>

#include <vector>
#include <list>
#include <unordered_set>


#include "ASTConversionInfo.h"

class ASTConverterConsumer : public clang::ASTConsumer
{
  public:
    ASTConverterConsumer(ASTConversionInfo& conversionInfo);

    virtual void HandleTranslationUnit(clang::ASTContext &context) override;

  private:
    ASTConversionInfo& conversionInfo;
};

class ASTConverterVisitor : public clang::RecursiveASTVisitor<ASTConverterVisitor>
{
  public:
    ASTConverterVisitor(clang::ASTContext &context, ASTConversionInfo& conversionInfo);

    bool TraverseDecl(clang::Decl * decl);

    bool VisitTranslationUnitDecl(const clang::TranslationUnitDecl* decl);

    bool VisitVarDecl(const clang::VarDecl* decl);
    bool VisitFieldDecl(const clang::FieldDecl* decl);
    bool VisitEnumConstantDecl(const clang::EnumConstantDecl* decl);
    bool VisitNamespaceDecl(const clang::NamespaceDecl* decl);
    bool VisitRecordDecl(const clang::RecordDecl * decl);
    void RecordDeclHelper(const clang::RecordDecl * decl, columbus::lim::asg::logical::Class * limClass, std::shared_ptr<clang::metrics::UID> uid);
    void CXXRecordDeclHelper(const clang::CXXRecordDecl * decl, columbus::lim::asg::logical::Class* limClass, std::shared_ptr<clang::metrics::UID> uid);
    columbus::lim::asg::logical::Class* buildClassGenericSpec(const clang::ClassTemplateSpecializationDecl * decl, std::shared_ptr<clang::metrics::UID> uid);
    columbus::lim::asg::logical::Class* buildClassGeneric(const clang::ClassTemplateDecl * decl, std::shared_ptr<clang::metrics::UID> uid);
    columbus::lim::asg::logical::Class* buildClass(const clang::CXXRecordDecl * decl, std::shared_ptr<clang::metrics::UID> uid);
    bool VisitCXXRecordDecl(const clang::CXXRecordDecl* decl);
    bool VisitEnumDecl(const clang::EnumDecl* decl);
    bool VisitClassScopeFunctionSpecializationDecl(const clang::ClassScopeFunctionSpecializationDecl * decl);
    void methodBuildCommon(const clang::FunctionDecl * decl, columbus::lim::asg::logical::Method * limMethod, std::shared_ptr<clang::metrics::UID> uid, bool nodeCreated, std::set<const clang::Type*> usedTypes, bool isLambda = false);
    bool buildMethodGenericSpec(const clang::FunctionDecl * specFunc, const clang::FunctionTemplateDecl * templateDecl);
    bool buildLambda(const clang::CXXRecordDecl * lambdaClass);
    bool buildMethodGeneric(const clang::FunctionDecl * decl, const clang::FunctionTemplateDecl * templateDecl);
    bool buildSimpleMethod(const clang::FunctionDecl * decl);
    bool VisitFunctionDecl(const clang::FunctionDecl* decl);
    bool VisitFriendDecl(const clang::FriendDecl* decl);
    bool VisitTypedefNameDecl(const clang::TypedefNameDecl * decl);
    bool VisitObjCInterfaceDecl(clang::ObjCInterfaceDecl* decl);
    bool VisitObjCMethodDecl(const clang::ObjCMethodDecl* decl);
    bool VisitObjCProtocolDecl(clang::ObjCProtocolDecl* decl);
    bool VisitObjCCategoryDecl(const clang::ObjCCategoryDecl* decl);
    bool VisitObjCPropertyDecl(const clang::ObjCPropertyDecl* decl);

    bool VisitExpr(const clang::Expr * expr);
    bool VisitCallExpr(const clang::CallExpr* stmt);
    bool VisitObjCMessageExpr(const clang::ObjCMessageExpr* stmt);
    bool VisitCXXThrowExpr(const clang::CXXThrowExpr* stmt);
    bool VisitObjCAtThrowStmt(const clang::ObjCAtThrowStmt* stmt);
    bool VisitCXXConstructExpr(const clang::CXXConstructExpr* stmt);
    bool VisitDeclRefExpr(const clang::DeclRefExpr* stmt);
    bool VisitMemberExpr(const clang::MemberExpr* stmt);

    bool TraverseLambdaExpr(clang::LambdaExpr* stmt);

    bool ConvertType(const clang::Type* type);

    // Handles common code for both CallExpr and ObjCMessageExpr.
    template <typename CallType>
    bool HandleFunctionCalling(const CallType* callee, const CallType* caller, const clang::Stmt* stmt);
    std::string getImprint(const clang::Stmt * stmt);
  private:
    // Helper.
    template<class T> static auto toVoid(const T* ptr) -> typename std::enable_if<std::is_base_of<clang::Decl, T>::value, void*>::type
    {
      return (void*)(static_cast<const clang::Decl*>(ptr));
    }
    template<class T> static auto toVoid(const T* ptr) -> typename std::enable_if<std::is_base_of<clang::Stmt, T>::value, void*>::type
    {
      return (void*)(static_cast<const clang::Stmt*>(ptr));
    }
    template<class T> static auto toVoid(const T* ptr) -> typename std::enable_if<std::is_base_of<clang::Type, T>::value, void*>::type
    {
      return (void*)(static_cast<const clang::Type*>(ptr));
    }

    bool buildMethod(const clang::FunctionDecl * decl);

    // Iterates class decls.
    void iterateDecls(const clang::Decl* decl, columbus::lim::asg::Class* limClass);

    // Returns the file for the given SourceLocation.
    //columbus::lim::asg::physical::File& getFile(clang::SourceLocation loc);

    template<class T>
    T * getOrCreateIncompleteNode(const clang::Decl * decl);
    columbus::lim::asg::logical::Method * getOrCreateIncompleteNode_Method(const clang::FunctionDecl * decl);
    columbus::lim::asg::logical::Class * getOrCreateIncompleteNode_Class(const clang::CXXRecordDecl * decl);
    columbus::lim::asg::logical::Scope * getOrCreateIncompleteNode_Scope(const clang::Decl * decl);

    // Creates a new LIM node.
    template<class T, class U> bool createNode(std::shared_ptr<clang::metrics::UID> uid, U*& out, const clang::Decl* decl);
    
    /// Creates a file node in the LIM
    /// The input filename MUST be in the format given by clangtool FileEntry->getName()
    columbus::lim::asg::physical::File * createFileNode(const clang::FileEntry *fileEntry);

    /// Gets a pointer to a file node in the LIM if exists, otherwise returns nullptr
    /// The input filename MUST be in the format given by clangtool FileEntry->getName()
    columbus::lim::asg::physical::File * getFileNode(const clang::FileEntry *fileEntry);

public:
    /// Gets a filenode in the LIM or creates it, if it is not yet created
    /// The input filename MUST be in the format given by clangtool FileEntry->getName()
    columbus::lim::asg::physical::File* getOrCreateFileNode(const clang::FileEntry *fileEntry);

private:
    clang::FileID locToFileID(const clang::SourceLocation & loc);

    // Setup new GenericParameter based on the argument Decl.
    columbus::lim::asg::GenericParameter* createGenericParameter(const clang::NamedDecl* param);

    // Adds a new friendship edge to the Class. Takes care of setting this edge up.
    void addFriendshipEdge(columbus::lim::asg::Class* limParent, columbus::NodeId friendId, const std::string& friendName);

    void createLIMType(const clang::Type* type);

    const clang::Decl* getDeclFromStmt(const clang::Stmt& stmt);
    const clang::DeclContext* getFunctionContextFromStmt(const clang::Stmt& stmt);
    const clang::Decl* getParentFromContext(const clang::Decl* decl);

    void handleAttributeAccess(const clang::ValueDecl* decl, const clang::FunctionDecl* func);

    // Returns the source position (with realization level) for decl. 
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::NamespaceDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::CXXRecordDecl * decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::FriendDecl * decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::TagDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::FunctionDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::ObjCMethodDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::FieldDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::VarDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::EnumConstantDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::ObjCInterfaceDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::ObjCCategoryDecl* decl);
    columbus::lim::asg::SourcePosition getSourcePosition(const clang::ObjCProtocolDecl* decl);

    columbus::lim::asg::SourcePosition getSourcePositionHelper(const clang::Decl* decl);
    columbus::lim::asg::SourcePosition getSourcePositionHelper(clang::SourceLocation start, clang::SourceLocation end);

    template<class T>
    T getPrimaryTemplateVersionOfMemberDecl(T input);
    template<class T> T* createNodeHelper();

    void addMemberEdge(const clang::Decl* parent, columbus::lim::asg::logical::Member* to);

    void addUsesEdgeForStmt(columbus::lim::asg::logical::Member * to, const clang::Stmt * stmt, bool recursive = true);
    void addUsesEdgeForType(columbus::lim::asg::logical::Member* to, const clang::Type* type);

    bool addInstantiatesEdge(const clang::FunctionDecl * f, const clang::Type * type);

    template<class T>
    void addTemplateArgumentEdge(const clang::TemplateArgument& arg, T* limTo);

    template<class T>
    void addPositionEdge(columbus::lim::asg::logical::Member* limNode, const T* decl)
    {
      clang::SourceLocation loc = decl->getLocation();
      if (loc.isValid())
      {
        columbus::lim::asg::physical::File *file = getOrCreateFileNode(sm.getFileEntryForID(locToFileID(loc)));
        if (!file)
        {
          common::WriteMsg::write(
            common::WriteMsg::mlDebug,
            "Posedge ERROR: fileIDHash(%d) filename(%s), ptrAddress(%d) does not exist, but it should",
            locToFileID(loc).getHashValue(),
            ((std::string)context.getSourceManager().getFilename(loc)).c_str(),
            context.getSourceManager().getFileEntryForID(locToFileID(loc))->getUniqueID().getFile()
          );
        }
        else
        {
          columbus::lim::asg::SourcePosition position = getSourcePosition(decl);
          limNode->addIsContainedIn(file, position);

          // We add a sourcePosition to a list for comment and documenation detection.
          // If this is a macro expansion, we add the comment to the first declaration in the expansion.
          conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
            if (loc.isMacroID() && !globalInfo.scopeListPerFile[file].empty())
            {
              // All macroexpanded declaration have the same sourcelocation, so we check, if the last one added is the same as this one.
              // If it is, we will not add any comments to it.
              SourcePoint sp = globalInfo.scopeListPerFile[file].back().scope.begin;
              if (position.getLine() != sp.line || position.getColumn() != sp.column)
              {
                globalInfo.addMemberToScopeList(position, limNode, file);
              }
            }
            else
            {
              globalInfo.addMemberToScopeList(position, limNode, file);
            }
          });
        }
      }
    }

    columbus::ASTFilter myFilter;

    clang::ASTContext& context;

    ASTConversionInfo& conversionInfo;

    clang::SourceManager &sm;

    // The clang visitor may visit a single type multiple types, which we do not want. Hence visited types are added here,
    // and only types not yet here are visited.
    std::unordered_set<const clang::Type*> myVisitedTypes;

    // Stores the ID of the current translation unit.
    columbus::lim::asg::physical::File* pMyCurrentTU = nullptr;
    // TODO Handle the LinkageSpecDecl
    columbus::lim::asg::LanguageKind languageKind;
};

class Convert2LimAction : public clang::ASTFrontendAction
{
  public:
    Convert2LimAction(ASTConversionInfo& conversionInfo);
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile);

  private:
    ASTConversionInfo& conversionInfo;
};

std::unique_ptr<clang::tooling::FrontendActionFactory> newConvert2LimActionFactory(ASTConversionInfo& conversionInfo);

#endif
