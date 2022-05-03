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

#include "../inc/ASTVisitor.h"
#include "../inc/messages.h"
#include "../inc/clangHelpers.h"

#include <clangsupport/ASTIDMapGenerator.h>
#include <llvm/Demangle/Demangle.h>

#include "clang/Basic/TokenKinds.h"
#include "clang/Lex/Lexer.h"
#include <clang/Tooling/Tooling.h>
#include <clang/AST/Mangle.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Metrics/Metrics.h>
#include <clang/Metrics/MetricsUtility.h>
#include <clang/AST/ParentMapContext.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>
#include <Exception.h>

#include <stack>
#include <regex>



using namespace std;

using namespace clang;
using namespace common;
using namespace tooling;

using namespace columbus::lim::asg;
using namespace logical;

using namespace metrics;

using columbus::FilterState;


extern std::string g_filterfile;


ASTConverterConsumer::ASTConverterConsumer(ASTConversionInfo& conversionInfo)
  : conversionInfo(conversionInfo)
{}

void ASTConverterConsumer::HandleTranslationUnit(ASTContext& context)
{
  conversionInfo.originMap = columbus::generateNodeIDMaps(context);
  auto TUDecl = context.getTranslationUnitDecl();
  if (TUDecl != nullptr)
  {
    auto printingPolicy = TUDecl->getASTContext().getPrintingPolicy();
    printingPolicy.SuppressInlineNamespace = false;
    TUDecl->getASTContext().setPrintingPolicy(printingPolicy);

    ASTConverterVisitor visitor(context, conversionInfo);
    visitor.TraverseDecl(TUDecl);

    map<llvm::sys::fs::UniqueID, const clang::FileEntry*> sortedFiles;
    for (auto it = context.getSourceManager().fileinfo_begin(); it != context.getSourceManager().fileinfo_end(); ++it)
    {
      const clang::FileEntry* fileEntry = it->first;
      sortedFiles.insert(make_pair(fileEntry->getUniqueID(), fileEntry));
    }

    for(auto it : sortedFiles)
      visitor.getOrCreateFileNode(it.second);


    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.commentProcessor.loadCommentStructure(conversionInfo.ASTFilename);
    });
    
  }
}

/////////// VISITORS ////////////////////////////////////////////////////////////

ASTConverterVisitor::ASTConverterVisitor(ASTContext& context, ASTConversionInfo& conversionInfo)
  : myFilter(g_filterfile, context, true, true, true)
  , context (context)
  , conversionInfo (conversionInfo)
  , sm (context.getSourceManager())
{
    if (context.getLangOpts().CPlusPlus)
      languageKind = columbus::lim::asg::lnkCpp;
    else if (context.getLangOpts().ObjC)
      languageKind = columbus::lim::asg::lnkNotSet; // TODO Create a new language kind for the ObjC sources
    else
      languageKind = columbus::lim::asg::lnkC;
}

// This is only a test to see performance. Not correct behaviour
bool ASTConverterVisitor::TraverseDecl(clang::Decl *decl)
{
  if(!decl)
    return true;

  // Check if this is a decl for a file we want to traverse
  const FileEntry *fileEntry = sm.getFileEntryForID(locToFileID(decl->getLocation()));
  if (fileEntry)
  {
    getOrCreateFileNode(fileEntry);
    if (conversionInfo.filesOfTU.count(fileEntry) == 0)
      return true;
  }
    
  RecursiveASTVisitor<ASTConverterVisitor>::TraverseDecl(decl);
  return true;
}

bool ASTConverterVisitor::VisitTranslationUnitDecl(const clang::TranslationUnitDecl* decl)
{  
  // This looks useless, but we must do this, as it has the side effect of sm.fileinfo getting filled with the .h files (a cache table is being built in the background)
  sm.getExpansionLineNumber(sm.getLocForEndOfFile(sm.getMainFileID()));

  // Add translation unit.
  pMyCurrentTU = getOrCreateFileNode(sm.getFileEntryForID(sm.getMainFileID()));
  string fileName = pMyCurrentTU->getName();

  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    globalInfo.fileNode_to_TUNodes[pMyCurrentTU].insert(pMyCurrentTU);
    conversionInfo.pCurrentASTFile = &globalInfo.limFactory.createFile(conversionInfo.ASTFilename);
    globalInfo.limFactory.setFiltered(conversionInfo.pCurrentASTFile->getId());

    //Add compilationunit edges for components
    for (const auto& component : globalInfo.componentsOfTU[conversionInfo.currentASTIdentifier])
    {
      if (!contains(component->getCompilationUnitListIteratorBegin(), component->getCompilationUnitListIteratorEnd(), conversionInfo.pCurrentASTFile))
        component->addCompilationUnit(conversionInfo.pCurrentASTFile);
    }
  });
  
  return true;
}

bool ASTConverterVisitor::VisitVarDecl(const clang::VarDecl* decl)
{
  //common::WriteMsg::write(common::WriteMsg::mlNormal, "DAVID: visiting vardecl\n");
  // We are only interested in global variables and declarations in function bodys here.
  // Note: If this is changed, be sure to also update parameters (ParmVarDecl) in VisitFunctionDecl() as it depends
  // on the fact that parameters are not handled here.
  if (ParmVarDecl::classof(decl))
    return true;
  
  // If the varDecl is in a function, then we add it as instantiates edge
  if (const FunctionDecl* f = dyn_cast_or_null<const FunctionDecl>(decl->getParentFunctionOrMethod()))
  {
    //cout << f->getNameAsString() << endl;
    //decl->getType().getTypePtr()->dump();
    addInstantiatesEdge(f, decl->getType().getTypePtr());
    return true;
  }

  if(isTemplateInstantiation(decl->getTemplateSpecializationKind()))
    return true;

  // Otherwise it is an attribute
  Attribute* limAttribute;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);

  //cout << "AAAAAAAAAAAAAAAAAAttribute UID : " << uid->getName() << endl;

  // Node
  bool nodeCreated = createNode<Attribute>(uid, limAttribute, decl);
  //limAttribute->addCompilationUnit(pMyCurrentTU);

  if (!nodeCreated)
    return true;

  limAttribute->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
  limAttribute->setIsStatic(decl->getStorageClass() == StorageClass::SC_Static || decl->isStaticDataMember());
  limAttribute->setLanguage(languageKind);
  switch (decl->getAccess())
  {
  case AccessSpecifier::AS_public:    limAttribute->setAccessibility(AccessibilityKind::ackPublic);    break;
  case AccessSpecifier::AS_protected: limAttribute->setAccessibility(AccessibilityKind::ackProtected); break;
  case AccessSpecifier::AS_private:   limAttribute->setAccessibility(AccessibilityKind::ackPrivate);   break;
  default:                            limAttribute->setAccessibility(AccessibilityKind::ackNone);      break;
  }

  // Edges
  addPositionEdge(limAttribute, decl);

  if (const Decl *parent = dyn_cast_or_null<Decl>(decl->getDeclContext()))
  {
    addMemberEdge(parent, limAttribute);
  }

   //It should belong to logical parent, not physical, so this code is not needed
  /*if (const Decl* parent = getParentFromContext(decl))
  {
    if (DeclContext::classof(parent))
      addMemberEdge(parent, limAttribute);
  }*/

  if (limAttribute->getTypeIsEmpty())
  {
    const Type* type = decl->getType().getTypePtr();
    //type->dump();
    ConvertType(type);

    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext));
      if (it != globalInfo.typeTable.end())
        limAttribute->addType(it->second);
    });

  }

  if (decl->hasInit())
    addUsesEdgeForStmt(limAttribute, decl->getInit());

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limAttribute->getId());
    });
  }

  return true;
}

bool ASTConverterVisitor::VisitFieldDecl(const clang::FieldDecl* decl)
{
  Attribute* limAttribute;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  
  // Node
  bool nodeCreated = createNode<Attribute>(uid, limAttribute, decl);
  //limAttribute->addCompilationUnit(pMyCurrentTU);

  if (!nodeCreated)
    return true;
 
  limAttribute->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
  limAttribute->setLanguage(languageKind);

  if (const ObjCIvarDecl* ivar = dyn_cast_or_null<ObjCIvarDecl>(decl))
  {
    switch (ivar->getAccessControl())
    {
    case ObjCIvarDecl::AccessControl::Public:    limAttribute->setAccessibility(AccessibilityKind::ackPublic);    break;
    case ObjCIvarDecl::AccessControl::Protected: limAttribute->setAccessibility(AccessibilityKind::ackProtected); break;
    case ObjCIvarDecl::AccessControl::Private:   limAttribute->setAccessibility(AccessibilityKind::ackPrivate);   break;
    case ObjCIvarDecl::AccessControl::None:      limAttribute->setAccessibility(AccessibilityKind::ackNone);      break;
    default:        limAttribute->setAccessibility(AccessibilityKind::ackNone);      break;
    }
  }
  else
  {
    switch (decl->getAccess())
    {
    case AccessSpecifier::AS_public:    limAttribute->setAccessibility(AccessibilityKind::ackPublic);    break;
    case AccessSpecifier::AS_protected: limAttribute->setAccessibility(AccessibilityKind::ackProtected); break;
    case AccessSpecifier::AS_private:   limAttribute->setAccessibility(AccessibilityKind::ackPrivate);   break;
    default:                            limAttribute->setAccessibility(AccessibilityKind::ackNone);      break;
    }
  }

  // Edges
  addPositionEdge(limAttribute, decl);

  const Decl* parentDecl;
  if (const ObjCIvarDecl* iVar = dyn_cast<ObjCIvarDecl>(decl))
    parentDecl = iVar->getContainingInterface();
  else
    parentDecl = decl->getParent();

  addMemberEdge(parentDecl, limAttribute);

  if (limAttribute->getTypeIsEmpty())
  {
    const Type* type = decl->getType().getTypePtr();
    ConvertType(type);

    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext));
      if (it != globalInfo.typeTable.end())
        limAttribute->addType(it->second);
    });
    
  }

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limAttribute->getId());
    });
  }
    
  return true;
}

bool ASTConverterVisitor::VisitEnumConstantDecl(const clang::EnumConstantDecl* decl)
{
  Attribute* limAttribute;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);

  // Node
  bool nodeCreated = createNode<Attribute>(uid, limAttribute, decl);
  //limAttribute->addCompilationUnit(pMyCurrentTU);

  if (!nodeCreated)
    return true;

  limAttribute->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
  limAttribute->setLanguage(languageKind);
  limAttribute->setAccessibility(ackPublic);

  // Edges
  addPositionEdge(limAttribute, decl);

  if (const Decl* parent = getParentFromContext(decl))
    addMemberEdge(parent, limAttribute);

  if (limAttribute->getTypeIsEmpty())
  {
    const Type* type = decl->getType().getTypePtr();
    ConvertType(type);

    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext));
      if (it != globalInfo.typeTable.end())
        limAttribute->addType(it->second);
    });
    
  }

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limAttribute->getId());
    });
  }

  return true;
}

bool ASTConverterVisitor::VisitNamespaceDecl(const clang::NamespaceDecl* decl)
{
  Package* limPackage;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);

  // Node
  if (!createNode<Package>(uid, limPackage, decl))
  {
    // Only add position edge if it does not exist yet for this file.
    clang::SourceLocation loc = decl->getLocation();
    if (loc.isValid())
    {
      // At this point, file MUST exist and not nullptr
      columbus::lim::asg::physical::File *file = getFileNode(sm.getFileEntryForID(locToFileID(loc)));
      if (!file)
      {
        WriteMsg::write(WriteMsg::mlDDebug, "Namespacefile ERROR, file with hash (%s) and name (%s) does not exist, but it should\n", locToFileID(loc).getHashValue(), sm.getFilename(loc).str().c_str());
      }
      else
      {
        columbus::lim::asg::SourcePosition position = getSourcePosition(decl);
        for (auto it = limPackage->getIsContainedInListIteratorAssocBegin(); it != limPackage->getIsContainedInListIteratorAssocEnd(); ++it)
        {
          if (it->getId() == file->getId())
          {
            if (it.getAssocClass() == position)
              return true;
          }
        }

        limPackage->addIsContainedIn(file, position);
        conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
          globalInfo.addMemberToScopeList(position, limPackage, file);
        });
      }
    }

    return true;
  }

  limPackage->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
  limPackage->setLanguage(languageKind);
  limPackage->setAccessibility(AccessibilityKind::ackNone);
  limPackage->setIsAnonymous(decl->isAnonymousNamespace());

  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    globalInfo.namespaces.push_back(std::make_pair(limPackage, uid));
  });
  
  const NamespaceMetrics* metrics = nullptr;
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    metrics = globalInfo.metricsOutput.getNamespaceMetrics(*uid);
  });
  // If this is the first time the namespace is visited then get it's metrics from the metricsOutput.
  if (metrics)
  {
    clang::metrics::NamespaceMetrics::RangeMetrics filteredMetrics;

    // Loop through all namespace ranges and filter ones appearing in filtered files.
    auto metricsByFile = metrics->metricsByFile;
    bool allRangesInFilteredFiles = true;
    for (auto it = metricsByFile.begin(); it != metricsByFile.end(); it++)
    {
      // Get the file name.
      string canonicalFileName = common::pathCanonicalize(it->first);
      // Get the metrics for this namespace range.
      clang::metrics::NamespaceMetrics::RangeMetrics rangeMetrics = it->second;

      // If the file is not filtered, add the metrics to the filtered total.
      if (!myFilter.getDirectoryFilter().isFilteredOut(canonicalFileName))
      {
        filteredMetrics += rangeMetrics;
        allRangesInFilteredFiles = false;
      }
        

    }
    limPackage->setLOC(filteredMetrics.LOC);
    limPackage->setTLOC(filteredMetrics.TLOC);
    limPackage->setLLOC(filteredMetrics.LLOC);
    limPackage->setTLLOC(filteredMetrics.TLLOC);

    if (allRangesInFilteredFiles || myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
    {
      conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
        globalInfo.limFactory.setFiltered(limPackage->getId());
      });
    }
  }
  
  // Edges
  addPositionEdge(limPackage, decl);
  addMemberEdge(dyn_cast<Decl>(decl->getParent()), limPackage);    

  return true;
}

bool ASTConverterVisitor::VisitRecordDecl(const clang::RecordDecl* decl)
{
  //this is a visitor for c style structs and unions only
  if(isa<CXXRecordDecl>(decl))
    return true;

  Class* limClass;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);

  bool nodeCreated = createNode<Class>(uid, limClass, decl);

  if (!nodeCreated)
    return true;

  RecordDeclHelper(decl,limClass,uid);
  return true;
}

bool ASTConverterVisitor::VisitCXXRecordDecl(const clang::CXXRecordDecl* decl)
{
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  buildClass(decl, uid);
  return true;
}

bool ASTConverterVisitor::VisitEnumDecl(const clang::EnumDecl* decl)
{
  Class* limClass;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);

  bool nodeCreated = createNode<Class>(uid, limClass, decl);
  //limClass->addCompilationUnit(pMyCurrentTU);

  if (!nodeCreated)
    return true;

  limClass->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
  limClass->setLanguage(languageKind);
  limClass->setClassKind(ClassKind::clkEnum);
  limClass->setIsAnonymous(decl->getDeclName().isEmpty());

  switch (decl->getAccess())
  {
  case AccessSpecifier::AS_public:    limClass->setAccessibility(AccessibilityKind::ackPublic);    break;
  case AccessSpecifier::AS_protected: limClass->setAccessibility(AccessibilityKind::ackProtected); break;
  case AccessSpecifier::AS_private:   limClass->setAccessibility(AccessibilityKind::ackPrivate);   break;
  default:                            limClass->setAccessibility(AccessibilityKind::ackPublic);    break;
  }

  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    if (const EnumMetrics* metrics = globalInfo.metricsOutput.getEnumMetrics(*uid))
    {
      limClass->setLOC(metrics->LOC);
      limClass->setTLOC(metrics->LOC);
      limClass->setLLOC(metrics->LLOC);
      limClass->setTLLOC(metrics->LLOC);
    }
  });

  // Edges
  addPositionEdge(limClass, decl);
  addMemberEdge(dyn_cast<Decl>(decl->getParent()), limClass);

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limClass->getId());
    });
  }

  return true;
}

bool ASTConverterVisitor::VisitClassScopeFunctionSpecializationDecl(const clang::ClassScopeFunctionSpecializationDecl* decl)
{
  //clang::manuallyExpandClassScopeFunctionSpecializationDecl(decl,context); //hack
  //set<const clang::Type*> usedTypes;
  return true;
}

bool ASTConverterVisitor::VisitFunctionDecl(const clang::FunctionDecl* decl)
{
  if (isa<CXXDeductionGuideDecl>(decl))
    return true;

  buildMethod(decl);
  return true;
}

bool ASTConverterVisitor::VisitFriendDecl(const clang::FriendDecl* decl)
{
  // Only handle type friends here. Friend functions are handled in VisitFunctionDecl().
  if (const CXXRecordDecl* parentClass = dyn_cast_or_null<CXXRecordDecl>(getParentFromContext(decl)))
  {
    // This is only true for non-function friends.
    if (const TypeSourceInfo* tsi = decl->getFriendType())
    {
      if (const Type* type = tsi->getType().getTypePtrOrNull())
      {
        // Load the LIM node of the parent class (in which the friend is declared).
        // Ensure the node is of Class type.
        Class* limParent = getOrCreateIncompleteNode_Class(parentClass);
        if (!limParent)
          return true;

        if (const CXXRecordDecl* classDecl = type->getAsCXXRecordDecl())
        {
          // We create a node for the friend declaration (this is a very special kind of node...)
          shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
          Class* limFriendClass = buildClass(classDecl, uid);

          if (limFriendClass)
          {
            addPositionEdge(limFriendClass, decl);
            conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
              globalInfo.linker.add_declaration(limFriendClass, uid);
              if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
                globalInfo.limFactory.setFiltered(limFriendClass->getId());
              else
                globalInfo.limFactory.setNotFiltered(limFriendClass->getId());
            });
          }

          //we apply the friend edge to the definition if we can, otherwise just to the declaration created above
          if (const CXXRecordDecl *def = classDecl->getDefinition())
          {
            Class* limDefClass = getOrCreateIncompleteNode_Class(def);
            if(limDefClass)
              addFriendshipEdge(limParent, limDefClass->getId(), classDecl->getNameAsString());
          }
          else if (limFriendClass)
          {
            addFriendshipEdge(limParent, limFriendClass->getId(), classDecl->getNameAsString());
          }
        }
        else if (const TemplateTypeParmType* pt = dyn_cast_or_null<TemplateTypeParmType>(type))
        {
          if (const TemplateTypeParmDecl* named = pt->getDecl())
            addFriendshipEdge(limParent, 0, named->getNameAsString());
        }
      }
    }
  }

  return true;
}

bool ASTConverterVisitor::VisitTypedefNameDecl(const clang::TypedefNameDecl *decl)
{
  if(Scope *limParent = getOrCreateIncompleteNode_Scope(getParentFromContext(decl)))
    addUsesEdgeForType(limParent,context.getTypedefType(decl).getTypePtr());
  return true;
}

bool ASTConverterVisitor::VisitExpr(const clang::Expr* expr)
{
  
  /*cout << "Expr Type found: "<< expr->getType()->getTypeClassName() << ", " << conversionInfo.uidFactory.createTypeId(expr->getType())->getName() << ", ";
  if (const BuiltinType* specificType = expr->getType()->getAs<BuiltinType>())
  {
    cout << specificType->getNameAsCString(PrintingPolicy(context.getLangOpts()));
  }
  cout << endl;*/

  if(isa<CXXConstructExpr>(expr))
    return true;

  if (const clang::FunctionDecl* f = dyn_cast_or_null<FunctionDecl>(getFunctionContextFromStmt(*expr)))
    if (Method* limMethod = getOrCreateIncompleteNode_Method(f)) {
      //expr->dump();
      addUsesEdgeForStmt(limMethod, expr, false);
    }
      

  return true;
}

bool ASTConverterVisitor::VisitCallExpr(const clang::CallExpr* stmt)
{
  const FunctionDecl *directCallee = stmt->getDirectCallee();
  const FunctionDecl *caller = dyn_cast_or_null<const FunctionDecl>(getFunctionContextFromStmt(*stmt));

  HandleFunctionCalling(directCallee, caller, stmt);

  if (caller && directCallee)
  {
    Method* limCaller = getOrCreateIncompleteNode_Method(caller);
    if(limCaller)
      addUsesEdgeForType(limCaller, directCallee->getType().getTypePtrOrNull());
  }
  return true;
}

bool ASTConverterVisitor::VisitCXXThrowExpr(const clang::CXXThrowExpr* stmt)
{
  if (!stmt->getSubExpr())
    return true;

  if (const FunctionDecl* fd = dyn_cast_or_null<FunctionDecl>(getFunctionContextFromStmt(*stmt)))
  {
    const Type* type = stmt->getSubExpr()->getType().getTypePtr();
    ConvertType(type);

    Method* limMethod = getOrCreateIncompleteNode_Method(fd);
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto it2 = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext));
      if (limMethod && it2 != globalInfo.typeTable.end())
        limMethod->addThrows(it2->second);
    });
    
  }

  return true;
}

bool ASTConverterVisitor::VisitCXXConstructExpr(const clang::CXXConstructExpr* stmt)
{
  if (const CXXConstructorDecl* constDecl = stmt->getConstructor())
  {
    if (const CXXRecordDecl* record = constDecl->getParent())
    {
      if (const FunctionDecl* func = dyn_cast_or_null<FunctionDecl>(getFunctionContextFromStmt(*stmt)))
      {
        if (!constDecl->isImplicit())
        {
          HandleFunctionCalling(dyn_cast_or_null<FunctionDecl>(constDecl), func, stmt);
        }

        if(stmt->getConstructionKind() == CXXConstructExpr::ConstructionKind::CK_Complete)
          addInstantiatesEdge(func, record->getTypeForDecl());
      }
    }
  }

  return true;
}

bool ASTConverterVisitor::VisitDeclRefExpr(const clang::DeclRefExpr* stmt)
{
  if (const clang::FunctionDecl* f = dyn_cast_or_null<FunctionDecl>(getFunctionContextFromStmt(*stmt)))
  {
    if (auto tmp = stmt->getQualifier())
    {
      if (auto rec = tmp->getAsRecordDecl())
      {
        Method *limMethod = getOrCreateIncompleteNode_Method(f);
        if(limMethod)
          addUsesEdgeForType(limMethod, rec->getTypeForDecl());
      }
    }
    handleAttributeAccess(stmt->getDecl(), f);
  }

  return true;
}

bool ASTConverterVisitor::VisitMemberExpr(const clang::MemberExpr* stmt)
{
  handleAttributeAccess(stmt->getMemberDecl(), dyn_cast_or_null<FunctionDecl>(getFunctionContextFromStmt(*stmt)));
  return true;
}

bool ASTConverterVisitor::TraverseLambdaExpr(clang::LambdaExpr* stmt)
{
  // TODO: Lambdas get filtered! Fix that!
  TraverseCXXMethodDecl(stmt->getCallOperator());
  RecursiveASTVisitor<ASTConverterVisitor>::TraverseLambdaExpr(stmt);
  return true;
}

/////////// OBJ-C VISITORS ////////////////////////////////////////////////////////////

bool ASTConverterVisitor::VisitObjCInterfaceDecl(clang::ObjCInterfaceDecl* decl)
{
  Class* limClass;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);

  bool nodeCreated = createNode<Class>(uid, limClass, decl);

  if (nodeCreated)
  {
    limClass->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
    limClass->setLanguage(columbus::lim::asg::lnkNotSet); // TODO create lnkObjC
    limClass->setIsAnonymous(decl->getDeclName().isEmpty());
    limClass->setClassKind(ClassKind::clkClass);
    limClass->setAccessibility(AccessibilityKind::ackNone);
    limClass->setIsAbstract(false);

    if (const ObjCObjectType * baseType = decl->getSuperClassType())
    {
      ConvertType(baseType);
      conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
        auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(baseType, 0), conversionInfo.pMyMangleContext));
        if (it != globalInfo.typeTable.end())
          limClass->addIsSubclass(it->second);
      });
    }

    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      if (const ClassMetrics* metrics = globalInfo.metricsOutput.getClassMetrics(*uid))
      {
        limClass->setLOC(metrics->LOC);
        limClass->setTLOC(metrics->TLOC);
        limClass->setLLOC(metrics->LLOC);
        limClass->setTLLOC(metrics->TLLOC);
      }
    }); 
  }

  // Get protocols this Interface implements.
  SmallVector<ObjCProtocolDecl *, 4> protocols;
  SmallVector<SourceLocation, 4> ProtocolLocs;
  ObjCCategoryDecl::protocol_loc_iterator FromProtoLoc = decl->protocol_loc_begin();

  for (ObjCProtocolDecl::protocol_iterator FromProto = decl->protocol_begin(),
    FromProtoEnd = decl->protocol_end();
    FromProto != FromProtoEnd;
    ++FromProto,
    ++FromProtoLoc)
  {
    protocols.push_back(*FromProto);
    ProtocolLocs.push_back(*FromProtoLoc);
  }
  if(decl->hasDefinition())
  {
    decl->setProtocolList(protocols.data(), protocols.size(), ProtocolLocs.data(), context);
    for (const ObjCProtocolDecl* p : protocols)
    {
      conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
        auto it = globalInfo.limTable.find(conversionInfo.uidFactory.create(p, conversionInfo.pMyMangleContext));
        if (it != globalInfo.limTable.end())
        {
          Class* protocol = static_cast<Class*>(it->second);
          protocol->addExtends(limClass);
        }
      });
    }
  }

  // Edges
  addPositionEdge(limClass, decl);
  addMemberEdge(dyn_cast<Decl>(decl->getParent()), limClass);
  limClass->addCompilationUnit(pMyCurrentTU);

  // Uses edge for definitions.
  if (decl->getDefinition() == decl)
  {
    iterateDecls(decl, limClass);
  }

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limClass->getId());
    });
  }
  return true;
}

bool ASTConverterVisitor::VisitObjCMethodDecl(const clang::ObjCMethodDecl* decl)
{
  Method* limMethod;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  bool nodeCreated;
  nodeCreated = createNode<Method>(uid, limMethod, decl);

  assert(uid && "Sanity check: Variable should be always non-null at this point.");

  if (nodeCreated)
  {
    limMethod->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
    limMethod->setLanguage(columbus::lim::asg::lnkNotSet); // TODO create lnkObjC
    limMethod->setMethodKind(MethodKind::mekNormal);

    // TODO: Might not need this check.
    if (const ObjCMethodDecl* md = dyn_cast<ObjCMethodDecl>(decl))
    {
      limMethod->setAccessibility(AccessibilityKind::ackNone);
      limMethod->setIsStatic(md->isClassMethod());
    }

    const FunctionMetrics* metrics;
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      metrics = globalInfo.metricsOutput.getFunctionMetrics(*uid);
    });
    if (metrics)
    {
      limMethod->setLOC(metrics->LOC);
      limMethod->setTLOC(metrics->TLOC);
      limMethod->setLLOC(metrics->LLOC);
      limMethod->setTLLOC(metrics->TLLOC);
      limMethod->setDistinctOperands(metrics->HD_Operands);
      limMethod->setDistinctOperators(metrics->HD_Operators);
      limMethod->setTotalOperands(metrics->H_Operands);
      limMethod->setTotalOperators(metrics->H_Operators);

      // Note: Despite calling it "number of branches", it really is McCC (number of branches + 1).
      limMethod->setNumberOfBranches(metrics->McCC);
    }
  }

  // Edges
  addPositionEdge(limMethod, decl);
  limMethod->addCompilationUnit(pMyCurrentTU);

  const DeclContext* parent = decl->getParent();

  if(const ObjCCategoryImplDecl* impl = dyn_cast<ObjCCategoryImplDecl>(parent))
  {
    parent = impl->getCategoryDecl();
  }
  else if(const ObjCImplementationDecl* impl = dyn_cast<ObjCImplementationDecl>(parent))
  {
    parent = impl->getClassInterface();
  }

  addMemberEdge(dyn_cast<Decl>(parent), limMethod);

  // Add return type if not yet set up.
  if (limMethod->getReturnsIsEmpty())
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(decl->getReturnType().getTypePtr(), 0), conversionInfo.pMyMangleContext));
      if (it != globalInfo.typeTable.end())
        limMethod->addReturns(it->second);
    });
  }

  // No need to do anything with params if they're already added - possibly from different compilation unit (CU).
  // TODO: This check is probably nolonger required as declarations and definitions nolonger share the same node.
  if (limMethod->getParameterSize() != decl->param_size())
  {
    // Add the parameters here.
    // Important: No node duplication is possible. ParmVarDecl is indeed a VarDecl, so VisitVarDecl() visits it.
    // But in VisitVarDecl() we only handle global variable declarations. No node is created there for parameters.
    for (const ParmVarDecl* param : decl->parameters())
    {
      ConvertType(param->getType().getTypePtr());
      conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
        Parameter* limParam = globalInfo.limFactory.createParameterNode();
        limParam->setName(param->getNameAsString());

        auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(param->getType().getTypePtr(), 0), conversionInfo.pMyMangleContext));
        if (it != globalInfo.typeTable.end())
          limParam->setType(it->second);
        limMethod->addParameter(limParam);
      });
    }
  }

  // Uses edge for definitions.
  if (decl->isThisDeclarationADefinition())
  {
    const Type* t;
    for (const Decl* d : decl->decls())
    {
      // Ignore implicit code.
      if (d->isImplicit())
        continue;

      if (const ValueDecl* td = dyn_cast<ValueDecl>(d))
        t = td->getType().getTypePtrOrNull();
      else if (const TypeDecl* td = dyn_cast<TypeDecl>(d))
        t = td->getTypeForDecl();
      else
        continue;

      if (t)
        addUsesEdgeForType(limMethod, t);
    }
  }

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limMethod->getId());
    });
  }

  return true;
}

bool ASTConverterVisitor::VisitObjCProtocolDecl(clang::ObjCProtocolDecl* decl)
{
  Class* limClass;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  bool nodeCreated = createNode<Class>(uid, limClass, decl);

  if (nodeCreated)
  {
    limClass->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
    limClass->setLanguage(columbus::lim::asg::lnkNotSet); // TODO create lnkObjC
    limClass->setIsAnonymous(decl->getDeclName().isEmpty());
    limClass->setClassKind(ClassKind::clkProtocol);
    limClass->setAccessibility(AccessibilityKind::ackNone);
    limClass->setIsAbstract(true);

    SmallVector<ObjCProtocolDecl *, 4> protocols;
    SmallVector<SourceLocation, 4> ProtocolLocs;
    ObjCCategoryDecl::protocol_loc_iterator FromProtoLoc = decl->protocol_loc_begin();

    for (ObjCProtocolDecl::protocol_iterator FromProto = decl->protocol_begin(),
      FromProtoEnd = decl->protocol_end();
      FromProto != FromProtoEnd;
      ++FromProto,
      ++FromProtoLoc)
    {
      protocols.push_back(*FromProto);
      ProtocolLocs.push_back(*FromProtoLoc);
    }

    if(decl->hasDefinition())
    {
      decl->setProtocolList(protocols.data(), protocols.size(), ProtocolLocs.data(), context);
      for (const ObjCProtocolDecl* p : protocols)
      {
        conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
          auto it = globalInfo.limTable.find(conversionInfo.uidFactory.create(p, conversionInfo.pMyMangleContext));
          if (it != globalInfo.limTable.end())
          {
            Class* ancestorProtocol = static_cast<Class*>(it->second);
            globalInfo.limFactory.beginType();
            globalInfo.limFactory.addTypeFormer(globalInfo.limFactory.createTypeFormerType(ancestorProtocol->getId()).getId());
            type::Type& artificialProtocolType = globalInfo.limFactory.endType();

            limClass->addIsSubclass(artificialProtocolType.getId());
          }
        });
      }
    }

    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      if (const ClassMetrics* metrics = globalInfo.metricsOutput.getClassMetrics(*uid))
      {
        limClass->setLOC(metrics->LOC);
        limClass->setTLOC(metrics->TLOC);
        limClass->setLLOC(metrics->LLOC);
        limClass->setTLLOC(metrics->TLLOC);
      }
    });
  }

  // Edges
  addPositionEdge(limClass, decl);
  addMemberEdge(dyn_cast<Decl>(decl->getParent()), limClass);
  limClass->addCompilationUnit(pMyCurrentTU);

  // Uses edge for definitions.
  if (decl->getDefinition() == decl)
  {
    iterateDecls(decl, limClass);
  }

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limClass->getId());
    });
  }
  return true;
}

bool ASTConverterVisitor::VisitObjCCategoryDecl(const clang::ObjCCategoryDecl* decl)
{
  Class* limClass;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  bool nodeCreated = createNode<Class>(uid, limClass, decl);

  if (nodeCreated)
  {
    limClass->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
    limClass->setLanguage(columbus::lim::asg::lnkNotSet); // TODO create lnkObjC
    limClass->setIsAnonymous(decl->getDeclName().isEmpty());
    limClass->setAccessibility(AccessibilityKind::ackNone);
    limClass->setIsAbstract(false);

    if (decl->IsClassExtension())
      limClass->setClassKind(ClassKind::clkExtension);
    else
      limClass->setClassKind(ClassKind::clkCategory);

    const ClassMetrics* metrics;
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      metrics = globalInfo.metricsOutput.getClassMetrics(*uid);
    });
    if (metrics)
    {
      limClass->setLOC(metrics->LOC);
      limClass->setTLOC(metrics->TLOC);
      limClass->setLLOC(metrics->LLOC);
      limClass->setTLLOC(metrics->TLLOC);
    }
  }

  // Edges
  addPositionEdge(limClass, decl);
  addMemberEdge(dyn_cast<Decl>(decl->getParent()), limClass);
  limClass->addCompilationUnit(pMyCurrentTU);

  if (const ObjCInterfaceDecl * extendedInterface = decl->getClassInterface())
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      Class* extendedClass = static_cast<Class*>(globalInfo.limTable.at(conversionInfo.uidFactory.create(extendedInterface, conversionInfo.pMyMangleContext)));
      limClass->addExtends(extendedClass);
    });
  }

  // Uses edge for definitions.
  iterateDecls(decl, limClass);

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limClass->getId());
    });
  }
  return true;
}

bool ASTConverterVisitor::VisitObjCPropertyDecl(const clang::ObjCPropertyDecl* decl)
{
  if (const ObjCMethodDecl* method = decl->getGetterMethodDecl())
    VisitObjCMethodDecl(method);
  if (const ObjCMethodDecl* method = decl->getSetterMethodDecl())
    VisitObjCMethodDecl(method);
  return true;
}

bool ASTConverterVisitor::VisitObjCMessageExpr(const clang::ObjCMessageExpr* stmt)
{
  const ObjCMethodDecl* caller = dyn_cast_or_null<ObjCMethodDecl>(getFunctionContextFromStmt(*stmt));
  return HandleFunctionCalling(stmt->getMethodDecl(), caller, stmt);
}

bool ASTConverterVisitor::VisitObjCAtThrowStmt(const clang::ObjCAtThrowStmt* stmt)
{
  if (!stmt->getThrowExpr())
    return true;

  if (const ObjCMethodDecl* decl = dyn_cast_or_null<ObjCMethodDecl>(getFunctionContextFromStmt(*stmt)))
  {
    const Type* type = stmt->getThrowExpr()->getType().getTypePtr();
    ConvertType(type);

    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto it1 = globalInfo.limTable.find(conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext));
      auto it2 = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext));
      if (it1 != globalInfo.limTable.end() && it2 != globalInfo.typeTable.end())
      {
        if (Method* limMethod = dynamic_cast<Method*>(it1->second))
        {
          limMethod->addThrows(it2->second);
        }
      }
    });
    
  }

  return true;
}

/////////// HELPERS ////////////////////////////////////////////////////////////

/////////// CLASS-HELPERS //////////////////////////////////////////////////////

void ASTConverterVisitor::RecordDeclHelper(const clang::RecordDecl* decl, Class* limClass, shared_ptr<UID> uid)
{
  limClass->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
  limClass->setIsAnonymous(decl->getDeclName().isEmpty());
  limClass->setLanguage(languageKind);
  limClass->setAccessibility(AccessibilityKind::ackPublic); //c type stuff is public by default

  switch (decl->getTagKind())
  {
  case TagTypeKind::TTK_Class:     limClass->setClassKind(ClassKind::clkClass);     break;
  case TagTypeKind::TTK_Struct:    limClass->setClassKind(ClassKind::clkStruct);    break;
  case TagTypeKind::TTK_Union:     limClass->setClassKind(ClassKind::clkUnion);     break;
  case TagTypeKind::TTK_Interface: limClass->setClassKind(ClassKind::clkInterface); break;
  case TagTypeKind::TTK_Enum:      limClass->setClassKind(ClassKind::clkEnum);      break;
  }

  const ClassMetrics* metrics;
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    metrics = globalInfo.metricsOutput.getClassMetrics(*uid);
  });
  if (metrics)
  {
    limClass->setLOC(metrics->LOC);
    limClass->setTLOC(metrics->TLOC);
    limClass->setLLOC(metrics->LLOC);
    limClass->setTLLOC(metrics->TLLOC);
  }

  // Edges
  shared_ptr<UID> recordUID = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);

  if(recordUID->equals(*uid)) // For friendDecls the UID is created from the friendDecl not the recordDecl and positionEdge is handled elsewhere.
    addPositionEdge(limClass, decl);
  if(isa<CXXRecordDecl>(decl))
    addMemberEdge(dyn_cast<Decl>(decl->getParent()), limClass);
  else
    addMemberEdge(decl->getTranslationUnitDecl(), limClass); // c typed nested structs and unions are always global


  // Uses edge for definitions.
  /*if (decl->getDefinition() == decl)
  {
    iterateDecls(decl, limClass);
  }*/

  //cout << (string)decl->getName() << endl;
  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limClass->getId());
    });
  }
}

void ASTConverterVisitor::CXXRecordDeclHelper(const clang::CXXRecordDecl* decl, Class* limClass, shared_ptr<UID> uid)
{
  RecordDeclHelper(decl,limClass,uid);

  /*
  limClass->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
  limClass->setIsAnonymous(decl->getDeclName().isEmpty());
  limClass->setLanguage(columbus::lim::asg::lnkCpp);
  switch (decl->getTagKind())
  {
  case TagTypeKind::TTK_Class:     limClass->setClassKind(ClassKind::clkClass);     break;
  case TagTypeKind::TTK_Struct:    limClass->setClassKind(ClassKind::clkStruct);    break;
  case TagTypeKind::TTK_Union:     limClass->setClassKind(ClassKind::clkUnion);     break;
  case TagTypeKind::TTK_Interface: limClass->setClassKind(ClassKind::clkInterface); break;
  case TagTypeKind::TTK_Enum:      limClass->setClassKind(ClassKind::clkEnum);      break;
  }
  */
  if (decl->hasDefinition())
  {
    limClass->setIsAbstract(decl->isAbstract());

    if (metrics::isInterface(decl))
    {
      limClass->setClassKind(ClassKind::clkInterface);
      limClass->setIsAbstract(true);
    }

    for (const CXXBaseSpecifier base : decl->bases())
    {
      const Type* baseType = base.getType().getTypePtr();
      ConvertType(baseType);
      conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
        auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(baseType, 0), conversionInfo.pMyMangleContext));
        if (it != globalInfo.typeTable.end())
          limClass->addIsSubclass(it->second);
      });
    }
  }

  switch (decl->getAccess())
  {
  case AccessSpecifier::AS_public:    limClass->setAccessibility(AccessibilityKind::ackPublic);    break;
  case AccessSpecifier::AS_protected: limClass->setAccessibility(AccessibilityKind::ackProtected); break;
  case AccessSpecifier::AS_private:   limClass->setAccessibility(AccessibilityKind::ackPrivate);   break;
    // for some reason this must default to public (for the metrics to treat the function as API)
  default:                            limClass->setAccessibility(AccessibilityKind::ackPublic);      break;
  }
  /*
  if (const ClassMetrics* metrics = conversionInfo.metricsOutput.getClassMetrics(*uid))
  {
    limClass->setLOC(metrics->LOC);
    limClass->setTLOC(metrics->TLOC);
    limClass->setLLOC(metrics->LLOC);
    limClass->setTLLOC(metrics->TLLOC);
  }

  // Edges  
  addPositionEdge(limClass, decl);
  addMemberEdge(dyn_cast<Decl>(decl->getParent()), limClass);
  // Uses edge for definitions.
  if (decl->getDefinition() == decl)
  {
    iterateDecls(decl, limClass);
  }

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
    conversionInfo.limFactory.setFiltered(limClass->getId());
  */
}

logical::Class* ASTConverterVisitor::buildClassGenericSpec(const ClassTemplateSpecializationDecl* decl, std::shared_ptr<UID> uid)
{
  Class *limClass;
  // Specialization.
  bool nodeCreated = createNode<ClassGenericSpec>(uid, limClass, decl);
  //limClass->addCompilationUnit(pMyCurrentTU);

  if (!nodeCreated)
    return nullptr;

  const Decl* templatedDecl = decl->getSpecializedTemplate()->getTemplatedDecl(); 
  shared_ptr<UID> primUID = conversionInfo.uidFactory.create(templatedDecl, conversionInfo.pMyMangleContext);
  ClassGeneric* mg;
  createNode<ClassGeneric>(primUID, mg, templatedDecl);
  static_cast<ClassGenericSpec*>(limClass)->setSpecialize(mg);

  // Filter if required.
  if (myFilter.getFilterState(toVoid(templatedDecl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limClass->getId());
    });
  }

  const TemplateArgumentList& args = decl->getTemplateInstantiationArgs();
  for (unsigned i = 0; i < args.size(); ++i)
    addTemplateArgumentEdge(args[i], static_cast<ClassGenericSpec*>(limClass));

  CXXRecordDeclHelper(decl, limClass, uid);
  return limClass;
}

logical::Class* ASTConverterVisitor::buildClassGeneric(const ClassTemplateDecl* templateDecl, std::shared_ptr<UID> uid) {
  const CXXRecordDecl *decl = templateDecl->getTemplatedDecl();

  Class *limClass;
  bool nodeCreated = createNode<ClassGeneric>(uid, limClass, decl);
  //limClass->addCompilationUnit(pMyCurrentTU);

  if (!nodeCreated)
    return nullptr;

  // Add template parameters.
  for (const NamedDecl* param : templateDecl->getTemplateParameters()->asArray())
    static_cast<ClassGeneric*>(limClass)->addGenericParameter(createGenericParameter(param));

  CXXRecordDeclHelper(decl, limClass, uid);
  return limClass;
}

logical::Class* ASTConverterVisitor::buildClass(const CXXRecordDecl* decl, std::shared_ptr<UID> uid)
{
  //cout << "Built class " << decl->getNameAsString() << endl;
  if (const ClassTemplateDecl* templateDecl = decl->getDescribedClassTemplate())
  {
    return buildClassGeneric(templateDecl, uid);
  }
  else if (const ClassTemplateSpecializationDecl* spec = dyn_cast<ClassTemplateSpecializationDecl>(decl))
  {
    if (spec->getSpecializationKind() == TSK_ExplicitSpecialization)
      return buildClassGenericSpec(spec, uid);
  }
  else if (!decl->getTemplateInstantiationPattern())
  {
    // Default case: this is a "normal" class that has nothing to do with templates.
    Class* limClass;
    bool nodeCreated = createNode<Class>(uid, limClass, decl);

    //limClass->addCompilationUnit(pMyCurrentTU);

    if (!nodeCreated)
      return nullptr;

    CXXRecordDeclHelper(decl, limClass, uid);
    return limClass;
  }
  return nullptr;
}

/////////// METHOD-HELPERS /////////////////////////////////////////////////////

// Automatically deduces the proper method type to build
bool ASTConverterVisitor::buildMethod(const FunctionDecl* decl) {
  const CXXRecordDecl *recordParent = dyn_cast_or_null<CXXRecordDecl>(decl->getParent());

  if (const FunctionTemplateDecl* templateDecl = decl->getDescribedFunctionTemplate())
    buildMethodGeneric(decl,templateDecl);
  else if (const FunctionTemplateDecl *primary = decl->getPrimaryTemplate())
  {
    if(decl->getTemplateSpecializationKind() == TemplateSpecializationKind::TSK_ExplicitSpecialization)
      buildMethodGenericSpec(decl,primary);
  }
  else if (const FunctionTemplateSpecializationInfo *ftsi = decl->getTemplateSpecializationInfo())
  {
    if(const FunctionTemplateDecl *ftd = ftsi->getTemplate())
      buildMethodGenericSpec(decl,ftd);
  }
  else if(!decl->isTemplateInstantiation() && recordParent && recordParent->isLambda())
    buildLambda(recordParent);
  else if(!decl->isTemplateInstantiation())
    buildSimpleMethod(decl);
  return true;
}

bool ASTConverterVisitor::buildSimpleMethod(const FunctionDecl* decl) {
  Method* limMethod;
  bool nodeCreated;
  set<const clang::Type*> usedTypes;

  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  nodeCreated = createNode<Method>(uid, limMethod, decl);
  
  if(!nodeCreated)
    return false;

  methodBuildCommon(decl, limMethod, uid, nodeCreated, usedTypes);
  return true;
}

bool ASTConverterVisitor::buildMethodGeneric(const FunctionDecl* decl, const FunctionTemplateDecl* templateDecl)
{
  Method* limMethod;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  bool nodeCreated;
  set<const clang::Type*> usedTypes;

  nodeCreated = createNode<MethodGeneric>(uid, limMethod, decl);

  if(!nodeCreated)
    return false;

  // Add template parameters.
  for (const NamedDecl* param : templateDecl->getTemplateParameters()->asArray())
    static_cast<MethodGeneric*>(limMethod)->addGenericParameter(createGenericParameter(param));

  methodBuildCommon(decl, limMethod, uid, nodeCreated, usedTypes);
  return true;
}

bool ASTConverterVisitor::buildMethodGenericSpec(const FunctionDecl* specFunc, const FunctionTemplateDecl* templateDecl) {
  if(const FunctionTemplateDecl *original = templateDecl->getInstantiatedFromMemberTemplate())
    templateDecl = original;

  Method* limMethod;
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(specFunc, conversionInfo.pMyMangleContext);
  set<const clang::Type*> usedTypes;

  //cout << uid->getName() << endl;
  bool nodeCreated = createNode<MethodGenericSpec>(uid, limMethod, specFunc);
  if (nodeCreated)
  {
    MethodGenericSpec* limSpec = static_cast<MethodGenericSpec*>(limMethod);
    shared_ptr<UID> primUID = conversionInfo.uidFactory.create(templateDecl->getAsFunction(), conversionInfo.pMyMangleContext);

    MethodGeneric* mg;
    createNode<MethodGeneric>(primUID, mg, specFunc);
    limSpec->setSpecialize(mg);

    const TemplateArgumentList *tArgList = specFunc->getTemplateSpecializationArgs();

    for (unsigned i = 0; i < tArgList->size(); ++i){
      addTemplateArgumentEdge(tArgList->operator[](i), limSpec);
    }
    methodBuildCommon(specFunc, limMethod, uid, nodeCreated, usedTypes);
  }

  return true;
}

bool ASTConverterVisitor::buildLambda(const clang::CXXRecordDecl* lambdaClass)
{
  bool nodeCreated = true;
  set<const clang::Type*> usedTypes;

  const CXXMethodDecl* decl = lambdaClass->getLambdaCallOperator();
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);

  Method* limMethod;
  nodeCreated = createNode<Method>(uid, limMethod, decl);
  
  if (!nodeCreated)
    return false;

  methodBuildCommon(decl, limMethod, uid, nodeCreated, usedTypes);
  limMethod->setIsAnonymous(true);
  limMethod->setMethodKind(MethodKind::mekNormal);
  limMethod->setName("lambda");
  addMemberEdge(dyn_cast_or_null<Decl>(lambdaClass->getParent()), limMethod);
  return true;
}

void ASTConverterVisitor::methodBuildCommon(const clang::FunctionDecl* decl, Method* limMethod, shared_ptr<UID> uid, bool nodeCreated, set<const clang::Type*> usedTypes, bool isLambda)
{
  assert(uid && "Sanity check: Variable should be always non-null at this point.");

  if (!nodeCreated)
    return;

  limMethod->setMangledName(static_cast<MergeUID&>(*uid).getMangledName());
  limMethod->setLanguage(languageKind);

  if (decl->isOverloadedOperator())
    limMethod->setMethodKind(MethodKind::mekOperator);

  if (decl->getStorageClass() == StorageClass::SC_Static)
    limMethod->setIsStatic(true);

  if (decl->isOverloadedOperator())
    limMethod->setMethodKind(MethodKind::mekOperator);
  else
    limMethod->setMethodKind(MethodKind::mekNormal);

  if (const CXXMethodDecl* md = dyn_cast<CXXMethodDecl>(decl))
  {
    switch (md->getAccess())
    {
    case AccessSpecifier::AS_public:    limMethod->setAccessibility(AccessibilityKind::ackPublic);    break;
    case AccessSpecifier::AS_protected: limMethod->setAccessibility(AccessibilityKind::ackProtected); break;
    case AccessSpecifier::AS_private:   limMethod->setAccessibility(AccessibilityKind::ackPrivate);   break;
    default:                            limMethod->setAccessibility(AccessibilityKind::ackNone);      break;
    }

    limMethod->setIsStatic(md->isStatic());
    limMethod->setIsVirtual(md->isVirtual());
    limMethod->setIsAbstract(md->isPure());

    if (CXXConstructorDecl::classof(md))
      limMethod->setMethodKind(MethodKind::mekConstructor);
    else if (CXXDestructorDecl::classof(md))
      limMethod->setMethodKind(MethodKind::mekDestructor);
    else if (isGetter(limMethod->getName()))
      limMethod->setMethodKind(MethodKind::mekGet);
    else if (isSetter(limMethod->getName()))
      limMethod->setMethodKind(MethodKind::mekSet);
  }
  else
  {
    limMethod->setAccessibility(AccessibilityKind::ackNone);
  }

  const FunctionMetrics* metrics;
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    metrics = globalInfo.metricsOutput.getFunctionMetrics(*uid);
  });
  if (metrics)
  {
    limMethod->setLOC(metrics->LOC);
    limMethod->setTLOC(metrics->TLOC);
    limMethod->setLLOC(metrics->LLOC);
    limMethod->setTLLOC(metrics->TLLOC);
    limMethod->setDistinctOperands(metrics->HD_Operands);
    limMethod->setDistinctOperators(metrics->HD_Operators);
    limMethod->setTotalOperands(metrics->H_Operands);
    limMethod->setTotalOperators(metrics->H_Operators);
    limMethod->setNumberOfStatements(metrics->NOS);
    limMethod->setNestingLevel(metrics->NL);
    limMethod->setNestingLevelElseIf(metrics->NLE);

    // Note: Despite calling it "number of branches", it really is McCC (number of branches + 1).
    limMethod->setNumberOfBranches(metrics->McCC);
  }

  // Edges
  addPositionEdge(limMethod, decl);
  if(!isLambda)
      addMemberEdge(dyn_cast<Decl>(decl->getParent()), limMethod);

  // Add return type if not yet set up.
  if (limMethod->getReturnsIsEmpty())
  {
    //cout << decl->getNameAsString() << endl;
    //decl->getReturnType()->dump();

    /*if (const AutoType *at = dyn_cast_or_null<AutoType>(decl->getReturnType().getTypePtr())) {
      at->getDeducedType()->dump();
    }*/
    ConvertType(decl->getReturnType().getTypePtr());
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(decl->getReturnType().getTypePtr(), 0), conversionInfo.pMyMangleContext));
      if (it != globalInfo.typeTable.end())
        limMethod->addReturns(it->second);
    });

    /*
    ConvertType(decl->getReturnType().getTypePtr());
    auto it = conversionInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(decl->getReturnType().getTypePtr(), 0)));
    if (it != conversionInfo.typeTable.end())
    limMethod->addReturns(it->second);*/
  }

  usedTypes.insert(decl->getReturnType().getTypePtr());

  // No need to do anything with params if they're already added - possibly from different compilation unit (CU).
  // TODO: This check is probably nolonger required as declarations and definitions nolonger share the same node.
  if (limMethod->getParameterSize() != decl->param_size())
  {
    // Add the parameters here.
    // Important: No node duplication is possible. ParmVarDecl is indeed a VarDecl, so VisitVarDecl() visits it.
    // But in VisitVarDecl() we only handle global variable declarations. No node is created there for parameters.
    for (const ParmVarDecl* param : decl->parameters())
    {
      Parameter* limParam;
      conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
        limParam = globalInfo.limFactory.createParameterNode();
      });
      limParam->setName(param->getNameAsString());

      if (param->getType()->isPointerType() || param->getType()->isReferenceType())
        limParam->setParamKind(ParameterKind::pmkInOut);
      else
        limParam->setParamKind(ParameterKind::pmkIn);

      ConvertType(param->getType().getTypePtr());
      usedTypes.insert(param->getType().getTypePtr());
      conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
        auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(param->getType().getTypePtr(), 0), conversionInfo.pMyMangleContext));
        if (it != globalInfo.typeTable.end())
          limParam->setType(it->second);
      });

      limMethod->addParameter(limParam);
    }
  }

  // Add friend edge to parent class if this is a friend function.
  if (const FriendDecl* fd = dyn_cast_or_null<FriendDecl>(getParentFromContext(decl)))
    if (const CXXRecordDecl* parent = dyn_cast_or_null<CXXRecordDecl>(getParentFromContext(fd)))
      if (Class *limParentClass = getOrCreateIncompleteNode_Class(parent))
      {
        const FunctionDecl* def = decl->getDefinition();
        Method *limDef = nullptr;
        if (def)
          limDef = getOrCreateIncompleteNode_Method(def);

        if(limDef)
          addFriendshipEdge(limParentClass, limDef->getId(), decl->getNameAsString());
        else
          addFriendshipEdge(limParentClass, limMethod->getId(), decl->getNameAsString());
      }

  // Uses edge for definitions.
  if (decl->getDefinition() == decl)
  {
    const Type* t;
    for (const Decl* d : decl->decls())
    {
      // Ignore implicit code.
      //if (d->isImplicit())
      //  continue;
      if (const ValueDecl* td = dyn_cast<ValueDecl>(d))
        t = td->getType().getTypePtrOrNull();
      else if (const TypeDecl* td = dyn_cast<TypeDecl>(d))
        t = td->getTypeForDecl();
      else
        continue;

      if (t && (usedTypes.find(t) == usedTypes.end()))
        addUsesEdgeForType(limMethod, t);
    }
  }

  // Filter if required.
  if (myFilter.getFilterState(toVoid(decl)) == FilterState::Filtered)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      globalInfo.limFactory.setFiltered(limMethod->getId());
    });
  }

  //nem tudom, hogy van-e értelme itt fájlon belül ezt intézni, mert a linkernek ugyis dolgoznia kell a fájlon kivüli deklaráció-definíció feloldásokkal
  /*
  if (!decl->isThisDeclarationADefinition())
  {
    cout << decl->getNameAsString() << endl;
    int a;
    buildMethod(decl->getDefinition());
    shared_ptr<UID> defUID = conversionInfo.uidFactory.create(decl);
    auto defIt = conversionInfo.limTable.find(defUID);
    if (defIt != conversionInfo.limTable.end()) {
      limMethod->setDeclares(dynamic_cast<Method*>(defIt->second));
    }
  }*/
}

/////////// OTHER /////////////////////////////////////////////////////////////

void ASTConverterVisitor::iterateDecls(const clang::Decl* decl, Class* limClass)
{
  const Type* t;
  for (const Decl* d : dyn_cast<DeclContext>(decl)->decls())
  {
    // Ignore implicit code.
    if (d->isImplicit())
      continue;

    if (const ValueDecl* td = dyn_cast<ValueDecl>(d))
      t = td->getType().getTypePtrOrNull();
    else if (const TypedefDecl* td = dyn_cast<TypedefDecl>(d))
      t = context.getTypedefType(td).getTypePtr();
    else if (const TypeDecl* td = dyn_cast<TypeDecl>(d))
      t = td->getTypeForDecl();
    else
      continue;

    if (dyn_cast<VarDecl>(d))
      continue;

    if (dyn_cast<FieldDecl>(d))
      continue;

    if (dyn_cast<FunctionDecl>(d))
      continue;

    if (t)
    {
      if (const CXXRecordDecl* recordDecl = dyn_cast_or_null<CXXRecordDecl>(decl))
      {
        if (t == recordDecl->getTypeForDecl())
          continue;
      }
      addUsesEdgeForType(limClass, t);
    }
  }
}

template <typename CallType>
bool ASTConverterVisitor::HandleFunctionCalling(const CallType* callee, const CallType* caller, const clang::Stmt* stmt)
{
  // Helper lambda.  
  auto hasCallsAlready = [](auto node, columbus::NodeId callId)
  {
    for (auto it = node->getCallsListIteratorBegin(); it != node->getCallsListIteratorEnd(); ++it)
    {
      if (it->getId() == callId)
        return true;
    }

    return false;
  };

  // Forward declare pointer to node.
  MethodCall* limCall = nullptr;

  if (callee)
  {
    if(callee->isImplicit())
      return false;

    if (isDefinition(callee))
    {
      // Try to create 'MethodCall' node by direct callee.
      Method *limCallee = nullptr;
      if(const FunctionDecl *fd = dyn_cast_or_null<FunctionDecl>(callee))
        limCallee = getOrCreateIncompleteNode_Method(fd);
      else
        limCallee = getOrCreateIncompleteNode<Method>(callee);

      conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
        if (limCallee)
          limCall = &globalInfo.limFactory.createMethodCall(limCallee->getId());
        else
          limCall = &globalInfo.limFactory.createMethodCall(getImprint(stmt));
      });
    }
  }
  else
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      limCall = &globalInfo.limFactory.createMethodCall(getImprint(stmt)); // Imprint if no callee is available
    });
  }

  // Ensure we have a caller to which the function call can be connected.
  // Note that a 'MethodCall' is created regardless of whether the caller is known or not.
  if (caller)
  {
    Method *limCaller = nullptr;
    if(const FunctionDecl *fd = dyn_cast_or_null<FunctionDecl>(caller))
      limCaller = getOrCreateIncompleteNode_Method(fd);
    else
      limCaller = getOrCreateIncompleteNode<Method>(caller);

    if (limCaller)
    {
      if (callee && !isDefinition(callee))
      {
        shared_ptr<UID> uid = conversionInfo.uidFactory.create(callee, conversionInfo.pMyMangleContext);
        conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
          globalInfo.linker.unresolved_calls.push_back(std::pair<std::shared_ptr<MergeUID>, columbus::lim::asg::base::Base*>(std::static_pointer_cast<MergeUID>(uid), limCaller));
        }); 
      }
      else if (limCall && !hasCallsAlready(limCaller, limCall->getId()))
      {
        limCaller->addCalls(limCall);
      }
    }
  }

  // Check whether this function is used to initialize a variable.
  const Decl* decl = getDeclFromStmt(*stmt);
  while (decl && !(VarDecl::classof(decl) || FieldDecl::classof(decl)))
  {
    decl = getParentFromContext(decl);
  }

  // Found a (member) variable declaration. Add calls edge.
  // Skip if Decl is a ParmVarDecl, as we don't mangle them anyway.
  // Example: void bar(int = foo());
  if (decl && !isa<ParmVarDecl>(decl) && !decl->getParentFunctionOrMethod())
  {
    Attribute *limAttribute = getOrCreateIncompleteNode<Attribute>(decl);
    if (limAttribute)
    {
      if (callee && !isDefinition(callee))
      {
        shared_ptr<UID> calleeUID = conversionInfo.uidFactory.create(callee, conversionInfo.pMyMangleContext);
        conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
          globalInfo.linker.unresolved_calls.push_back(std::pair<std::shared_ptr<MergeUID>, columbus::lim::asg::base::Base*>(std::static_pointer_cast<MergeUID>(calleeUID), limAttribute));
        });
      }
      else
      {
        if (limCall && !hasCallsAlready(limAttribute, limCall->getId()))
        {
          limAttribute->addCalls(limCall);
        }
      }
    }
  }

  return true;
}

std::string ASTConverterVisitor::getImprint(const Stmt* stmt)
{
  SourceManager& sm = context.getSourceManager();

  // Get the source code (aka the function call) at this position.
  SourceRange r = stmt->getSourceRange();
  llvm::StringRef ref = Lexer::getSourceText(CharSourceRange(r, true), sm, LangOptions());
  return ref.str();
}

bool ASTConverterVisitor::ConvertType(const clang::Type* type)
{
  //type->dump();
  // debug
  /*cout << "?????????????Converting type: " << type->getTypeClassName() << ", ";
  if (const BuiltinType* specificType = type->getAs<BuiltinType>())
  {
    cout << specificType->getNameAsCString(PrintingPolicy(context.getLangOpts()));
  }
  cout << "lol" << endl;*/
  
  // We want Types to be visited only once!
  auto insertionResult = myVisitedTypes.insert(type);

  if (!insertionResult.second)
    return true;

  shared_ptr<UID> uid = conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext);
  // The ID can be null if the mangler is unable to generate a mangled name for it.
  if (!uid)
    return true;

  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    auto it = globalInfo.typeTable.find(uid);
    if (it != globalInfo.typeTable.end())
      return;

    globalInfo.limFactory.beginType();
    createLIMType(type);
    type::Type& limType = globalInfo.limFactory.endType();
    globalInfo.typeTable.emplace(uid, &limType);
  });

  return true;
}

template<class T>
T* ASTConverterVisitor::getOrCreateIncompleteNode(const clang::Decl* decl)
{
  shared_ptr<UID> uid = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  T* limNode = nullptr;
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
  bool nodeCreated = createNode<T>(uid, limNode, decl);

  if(nodeCreated)
    globalInfo.incompleteNodes.insert(uid);
  });

  return limNode;
}

Method * ASTConverterVisitor::getOrCreateIncompleteNode_Method(const clang::FunctionDecl * decl)
{
  if (isa<CXXDeductionGuideDecl>(decl))
    return nullptr;

  if (decl->getDescribedFunctionTemplate())
    return getOrCreateIncompleteNode<MethodGeneric>(decl);
  else if (decl->getPrimaryTemplate())
  {
    if(decl->getTemplateSpecializationKind() == TemplateSpecializationKind::TSK_ExplicitSpecialization)
      return getOrCreateIncompleteNode<MethodGenericSpec>(decl);
  }
  else if (const FunctionTemplateSpecializationInfo *ftsi = decl->getTemplateSpecializationInfo())
  {
    if(ftsi->getTemplate())
      return getOrCreateIncompleteNode<MethodGenericSpec>(decl);
  }
  else if(!decl->isTemplateInstantiation())
    return getOrCreateIncompleteNode<Method>(decl);
  
  return nullptr;
}

columbus::lim::asg::logical::Class * ASTConverterVisitor::getOrCreateIncompleteNode_Class(const clang::CXXRecordDecl * decl)
{
  if (decl->getDescribedClassTemplate())
  {
    return getOrCreateIncompleteNode<ClassGeneric>(decl);
  }
  else if (const ClassTemplateSpecializationDecl* spec = dyn_cast<ClassTemplateSpecializationDecl>(decl))
  {
    if (spec->getSpecializationKind() == TSK_ExplicitSpecialization)
      return getOrCreateIncompleteNode<ClassGenericSpec>(decl);
  }
  else if (!decl->getTemplateInstantiationPattern())
  {
    return getOrCreateIncompleteNode<Class>(decl);
  }
  return nullptr;
}

columbus::lim::asg::logical::Scope * ASTConverterVisitor::getOrCreateIncompleteNode_Scope(const clang::Decl * decl)
{
  if     (const FunctionDecl *fd = dyn_cast_or_null<FunctionDecl>(decl))
    return getOrCreateIncompleteNode_Method(fd);
  else if(const CXXRecordDecl *cxxrd = dyn_cast_or_null<CXXRecordDecl>(decl))
    return getOrCreateIncompleteNode_Class(cxxrd);
  else if(const RecordDecl *rd = dyn_cast_or_null<RecordDecl>(decl))
    return getOrCreateIncompleteNode<Class>(rd);
  else if(const NamespaceDecl *nd = dyn_cast_or_null<NamespaceDecl>(decl))
    return getOrCreateIncompleteNode<Package>(nd);
  else if(const EnumDecl *ed = dyn_cast_or_null<EnumDecl>(decl))
    return getOrCreateIncompleteNode<Class>(ed);
  else
    return nullptr;
}

template<class T, class U> bool ASTConverterVisitor::createNode(std::shared_ptr<metrics::UID> uid, U*& out, const Decl* decl)
{
  if(decl && decl->isImplicit())
    return false;

  bool isCreated;

  columbus::lim::asg::base::Base* limNode = nullptr;
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    auto it = globalInfo.limTable.find(uid);
    if (it != globalInfo.limTable.end())
      limNode = it->second;

  if (!limNode)
  {
    out = createNodeHelper<T>();
    globalInfo.limTable.emplace(uid, out);
    
    if (decl)
    {
      auto it = conversionInfo.originMap->node2id.find((void*)decl);
      if (it != conversionInfo.originMap->node2id.end())
      {
        assert(pMyCurrentTU && "TU should already be set at this point.");
        globalInfo.limOrigin.addCompIdCppIdLimIdToMap(conversionInfo.pCurrentASTFile->getId(), it->second, out->getId());
      }
      
      if (const NamedDecl* nd = dyn_cast<NamedDecl>(decl))
      {
        out->setName(nd->getNameAsString());
        //if (out->getName() == "")
        //  out->setName("<Anonymous>");

        std::string s;
        llvm::raw_string_ostream ss(s);

        // For functions, demangled the mangled name.
        if (const FunctionDecl *fd = dyn_cast_or_null<FunctionDecl>(nd))
        {
          if (const CXXConstructorDecl *ccd = dyn_cast<CXXConstructorDecl>(decl))
          {
            out->setName(ccd->getParent()->getNameAsString());
            conversionInfo.pMyMangleContext->mangleName(GlobalDecl(cast<CXXConstructorDecl>(ccd), CXXCtorType::Ctor_Complete), ss);
          }
          else if (const CXXDestructorDecl *dcd = dyn_cast<CXXDestructorDecl>(decl))
          {
            out->setName("~" + dcd->getParent()->getNameAsString());
            conversionInfo.pMyMangleContext->mangleName(GlobalDecl(cast<CXXDestructorDecl>(dcd), CXXDtorType::Dtor_Complete), ss);
          }
          else
            conversionInfo.pMyMangleContext->mangleName(fd, ss);

          size_t bufferSize = 200;
          char* buffer = (char*)malloc(bufferSize);
          int status;
          buffer = llvm::itaniumDemangle(ss.str().c_str(), buffer, &bufferSize, &status);

          if (status == 0 && buffer)
          {
            string demangledName(buffer);
            if (const CXXRecordDecl *rd = dyn_cast_or_null<CXXRecordDecl>(fd->getParent()))
            {
              // Make some alterations to the demangled lambda names
              if (rd->isLambda())
              {
                std::regex pattern("('lambda[0-9]*'(\\(.*?\\))*)|(\\$_[0-9]*)");
                demangledName = std::regex_replace(demangledName, pattern, "lambda");
              }
            }
            out->setDemangledName(demangledName);
          }
          else
          {
            out->setDemangledName("problem");

            std::string s_t;
            llvm::raw_string_ostream ss_t(s_t);
            fd->getNameForDiagnostic(ss_t, context.getPrintingPolicy(), true);

            ss_t << "(";
            if (const FunctionType *ft = fd->getFunctionType())
            {
              if (const FunctionProtoType *fpt = dyn_cast_or_null<FunctionProtoType>(ft))
              {
                bool first = true;
                for (auto pt : fpt->param_types())
                {
                  if (first)
                    first = false;
                  else
                    ss_t << ",";

                  ss_t << pt.getAsString(context.getPrintingPolicy());
                }
              }
            }
            ss_t << ")";
            out->setDemangledName(ss_t.str());
          }
        }
        else
        {
          // Use the same name as we'd use for diagnostics.
          nd->getNameForDiagnostic(ss, context.getPrintingPolicy(), true);
          out->setDemangledName(ss.str());
        }
        if (out->getDemangledName() == "")
        {
          out->setDemangledName("(anonymous)");
        }
      }

      // these are the types of decls that have Declares edges in the LIM
      if(TagDecl::classof(decl) || FunctionDecl::classof(decl) || VarDecl::classof(decl))
      {
        if (isDefinition(decl))
          globalInfo.linker.add_definition(out, uid);
        else
          globalInfo.linker.add_declaration(out, uid);
      }
    }
    isCreated = true;
  }
  else
  {
    //this part is reached if the node is already created
    out = static_cast<T*>(limNode);

    if (globalInfo.incompleteNodes.erase(uid) > 0)
    {
      // The node is already in the LIM table, but it's incomplete. In such case we return true, so that the rest of the build finishes.
      // We also delete it, as it will be soon completed
      isCreated = true;
    }
    else
    {
      isCreated = false;
    }
  }
  });
  return isCreated;
}

columbus::lim::asg::physical::File* ASTConverterVisitor::getOrCreateFileNode(const clang::FileEntry* fileEntry)
{
  if (!fileEntry)
    return nullptr;

  // If this file have already been seen in the CURRENT AST, we simply return it, there is nothing else to do
  auto itFile = conversionInfo.filesOfTU.find(fileEntry);
  if (itFile != conversionInfo.filesOfTU.end())
    return itFile->second;

  // If it isn't, there are 2 cases:
  columbus::lim::asg::physical::File* file;

  // If we've never seen this file before (not even in previous AST conversions), we must create the file node and set it's properties
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    auto itFile2 = globalInfo.filesAlreadyProcessed.find(fileEntry->getUniqueID());
    if (itFile2 == globalInfo.filesAlreadyProcessed.end())
      file = createFileNode(fileEntry);
    else
      file = itFile2->second;

    // If the file has already been added during the conversion of a previous AST, we don't need to create the file node, but
    // in both cases, we need to register the file for the current AST, and components.

    //Do the registerings
    for (const auto& component : globalInfo.componentsOfTU[conversionInfo.currentASTIdentifier])
    {
      globalInfo.linker.component_to_files[component].insert(file);
      globalInfo.linker.file_to_components[file].insert(component);
    }

    if(pMyCurrentTU) 
      globalInfo.fileNode_to_TUNodes[file].insert(pMyCurrentTU);
  });

  return file;
}

columbus::lim::asg::physical::File* ASTConverterVisitor::getFileNode(const clang::FileEntry *fileEntry)
{
  if(!fileEntry)
    return nullptr;

  auto itFile = conversionInfo.filesOfTU.find(fileEntry);
  if (itFile == conversionInfo.filesOfTU.end())
  {
    columbus::lim::asg::physical::File* file = nullptr;
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto itFile2 = globalInfo.filesAlreadyProcessed.find(fileEntry->getUniqueID());
      if (!(itFile2 == globalInfo.filesAlreadyProcessed.end()))
        file = itFile2->second;
    });
    return file;
  }
  else
  {
    return itFile->second;
  }
}

columbus::lim::asg::physical::File* ASTConverterVisitor::createFileNode(const clang::FileEntry* fileEntry)
{
  if (!fileEntry)
    return nullptr;

  string filename = fileEntry->getName().str();
  //cout << "file created with name : " << filename << endl;

  // We have special needs for what the filename should look like in the LIM
  // (also, the filter uses absolute path(canonical), while in the LIM, we might want to use relative)
  string canonicalFileName = common::pathCanonicalize(filename);
  string LIMLongname;
  if (filename.empty())
    LIMLongname = "<UNKNOWN>"; // all stuff that is in an unknown file will be under this name
  else
    LIMLongname = cANFilePathRenamer.changeToLIMCompatible(canonicalFileName);

  columbus::lim::asg::physical::File* fileNode;

  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
  fileNode = &globalInfo.limFactory.createFile(LIMLongname);

  unsigned endLine = 0, endColumn = 0;
  if (auto fileMetrics = globalInfo.metricsOutput.getFileMetrics(filename))
  {
    fileNode->setLOC(fileMetrics->LOC);
    fileNode->setLLOC(fileMetrics->LLOC);
    fileNode->setNumberOfBranches(fileMetrics->McCC);
    endLine = fileMetrics->endLine;
    endColumn = fileMetrics->endColumn;
    //CLOC will be set in finalizeTU (for that, the commentProcessor have to read the comments from the .comment files)
  }

  columbus::lim::asg::Package* root = globalInfo.limFactory.getRoot();
  if (!contains(root->getIsContainedInListIteratorAssocBegin(), root->getIsContainedInListIteratorAssocEnd(), fileNode))
  {
    // Add new 'IsContainedIn' edge in root for this file
    root->addIsContainedIn(fileNode, SourcePosition(relDefines, 1, 1, endLine, endColumn));
  }

  conversionInfo.filesOfTU[fileEntry] = fileNode;
  globalInfo.filesAlreadyProcessed.insert(make_pair(fileEntry->getUniqueID(), fileNode));

  // For the comments lookup
  string correctedFilename = canonicalFileName;
  if (globalInfo.changePathFrom.c_str() && globalInfo.changePathTo.c_str())
    correctedFilename = common::replace(correctedFilename.c_str(), globalInfo.changePathFrom.c_str(), globalInfo.changePathTo.c_str());

  globalInfo.correctedFileNameToFileNode[correctedFilename] = fileNode;
  globalInfo.canonicalFileNameToFileNode[canonicalFileName] = fileNode;
  });
  //cout << "File added to comment map: " << common::replace(filename.c_str(), conversionInfo.changePathFrom.c_str(), conversionInfo.changePathTo.c_str()) << endl;

  // Filtering is in the post-process (ASTConversionInfo.cpp/FilterFolders())

  //cout << "CREATED FILENAME = "<< filename << " FILEUniqueID = " << fileEntry->getUniqueID().getDevice() << ":" << fileEntry->getUniqueID().getFile() <<" FILEUID = " << fileEntry->getUID() << endl;

  return fileNode;
}

clang::FileID ASTConverterVisitor::locToFileID(const clang::SourceLocation &loc)
{
  if(loc.isMacroID())
    return sm.getFileID(sm.getExpansionLoc(loc)); // we need this, as for code in macros, the spellingloc has no file attached to it
  else
    return sm.getFileID(loc);
}


columbus::lim::asg::GenericParameter* ASTConverterVisitor::createGenericParameter(const clang::NamedDecl* param)
{
  // Create parameter node in LIM.
  GenericParameter* limParam;
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    limParam = globalInfo.limFactory.createGenericParameterNode();
  }); 
  limParam->setName(param->getNameAsString());

  // Choose parameter type.
  if (const TemplateTypeParmDecl* d = dyn_cast<TemplateTypeParmDecl>(param))
  {
    limParam->setGenericParameterKind(d->isParameterPack() ? gpkTypePack : gpkType);

    // Register in LIM table.
    shared_ptr<UID> uid = conversionInfo.uidFactory.create(param, conversionInfo.pMyMangleContext);
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      if (globalInfo.limTable.find(uid) == globalInfo.limTable.end())
        globalInfo.limTable.emplace(uid, limParam);
    });
    
  }
  else if (const NonTypeTemplateParmDecl* d = dyn_cast<NonTypeTemplateParmDecl>(param))
    limParam->setGenericParameterKind(d->isParameterPack() ? gpkNonTypePack : gpkNonType);
  else if (const TemplateTemplateParmDecl* d = dyn_cast<TemplateTemplateParmDecl>(param))
    limParam->setGenericParameterKind(d->isParameterPack() ? gpkTemplatePack : gpkTemplate);
  else
    limParam->setGenericParameterKind(GenericParameterKind::gpkType);

  return limParam;
}

void ASTConverterVisitor::addFriendshipEdge(columbus::lim::asg::Class* limParent, columbus::NodeId friendId, const std::string& friendName)
{
  // Only add it once!
  bool found = false;
  if (friendId != 0)
  {
    for (auto it = limParent->getGrantsFriendshipListIteratorBegin(); it != limParent->getGrantsFriendshipListIteratorEnd(); ++it)
    {
      if (it->getFriend() && it->getFriend()->getId() == friendId)
      {
        found = true;
        break;
      }
    }
  }

  if (!found)
  {
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      Friendship& fs = globalInfo.limFactory.createFriendship(friendId);
      if (friendId == 0)
        fs.setGrants(friendName);

      limParent->addGrantsFriendship(&fs);
    });
  }
}

void ASTConverterVisitor::createLIMType(const clang::Type* type)
{
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
  Factory& limFactory = globalInfo.limFactory;
  MergeUIDFactory& uidFactory = conversionInfo.uidFactory;
  auto& typeTable = globalInfo.typeTable;

  if (const BuiltinType* specificType = type->getAs<BuiltinType>())
  {
    // TODO: Someone needs to review this, as many clang types are not covered in SimpleTypeKind!
    SimpleTypeKind stk;
    switch (specificType->getKind())
    {
    case clang::BuiltinType::Void:       stk = stkVoid;              break;
    case clang::BuiltinType::Bool:       stk = stkBoolean;           break;
    case clang::BuiltinType::Char_U:     stk = stkUnsignedCharacter; break;
    case clang::BuiltinType::UChar:      stk = stkUnsignedCharacter; break;
    case clang::BuiltinType::WChar_U:    stk = stkUnicode;           break; // Sure?
    case clang::BuiltinType::Char16:     stk = stkUnicode;           break;
    case clang::BuiltinType::Char32:     stk = stkUnicode;           break;
    case clang::BuiltinType::UShort:     stk = stkUnsignedShort;     break;
    case clang::BuiltinType::UInt:       stk = stkUnsignedInteger;   break;
    case clang::BuiltinType::ULong:      stk = stkUnsignedLong;      break;
    case clang::BuiltinType::ULongLong:  stk = stkUnsignedLong;      break;
    case clang::BuiltinType::Char_S:     stk = stkCharacter;         break;
    case clang::BuiltinType::SChar:      stk = stkCharacter;         break;
    case clang::BuiltinType::WChar_S:    stk = stkUnicode;           break;
    case clang::BuiltinType::Short:      stk = stkShort;             break;
    case clang::BuiltinType::Int:        stk = stkInteger;           break;
    case clang::BuiltinType::Long:       stk = stkLong;              break;
    case clang::BuiltinType::LongLong:   stk = stkLong;              break;
    case clang::BuiltinType::Float:      stk = stkFloat;             break;
    case clang::BuiltinType::Double:     stk = stkDouble;            break;
    case clang::BuiltinType::LongDouble: stk = stkDouble;            break;
    case clang::BuiltinType::NullPtr:    stk = stkUnknown;           break; // Sure?
    default:                             stk = stkUnknown;           break;
    }

    type::SimpleType& st = limFactory.createSimpleType(stk);
    type::TypeFormerType& tf = limFactory.createTypeFormerType(st.getId());
    limFactory.addTypeFormer(tf.getId());
  }
  else if (const ArrayType* specificType = type->getAsArrayTypeUnsafe())
  {
    type::TypeFormer* tf;
    tf = &limFactory.createTypeFormerArray();
    limFactory.addTypeFormer(tf->getId());

    createLIMType(specificType->getElementType().getTypePtr());
  }
  else if (type->isPointerType() || type->isReferenceType())
  {
    type::TypeFormer& tf = limFactory.createTypeFormerPointer(type->isPointerType() ? PointerKind::ptkPointer : PointerKind::ptkReference);
    limFactory.addTypeFormer(tf.getId());
    createLIMType(type->getPointeeType().getTypePtr());
  }
  else if (const TemplateSpecializationType* specificType = type->getAs<TemplateSpecializationType>())
  {
    // TemplateSpecializationType is not necessary a class template,
    // as it can also be a template template parameter or alias template.
    columbus::NodeId id = 0;
    auto it = globalInfo.limTable.find(conversionInfo.uidFactory.createTypeId(QualType(specificType, 0), conversionInfo.pMyMangleContext));
    if (it != globalInfo.limTable.end())
    {
      id = it->second->getId();
    }
    else if (const CXXRecordDecl* ptr = specificType->getAsCXXRecordDecl())
    {
      if (dyn_cast_or_null<ClassTemplateSpecializationDecl>(ptr))
      {
        //VisitCXXRecordDecl(ptr);
        
        Class *limClass = getOrCreateIncompleteNode_Class(ptr);
        if(limClass)
          id = limClass->getId();
      }
    }

    // ID may not be setup (see the else case above) - in those cases we don't add the node.
    if (id != 0)
    {
      type::TypeFormer& tf = limFactory.createTypeFormerType(id);
      limFactory.addTypeFormer(tf.getId());
    }
  }
  else if (const RecordType* specificType = type->getAs<RecordType>())
  {
    if (const CXXRecordDecl *cr = dyn_cast_or_null<CXXRecordDecl>(specificType->getDecl()))
    {
      //specificType->dump();
      if (const CXXMethodDecl * md = cr->getLambdaCallOperator())
      {
        //md->dump();
        createLIMType(md->getType().getTypePtr());
        return;
      }

      columbus::lim::asg::base::Base *limClass = getOrCreateIncompleteNode_Class(cr);
      if(limClass)
      {
        type::TypeFormer& tf = limFactory.createTypeFormerType(limClass->getId());
        limFactory.addTypeFormer(tf.getId());
      }
    }
    else
    {
      columbus::lim::asg::logical::Class *limClass = getOrCreateIncompleteNode<Class>(specificType->getDecl());
      if (limClass)
      {
        type::TypeFormer& tf = limFactory.createTypeFormerType(limClass->getId());
        limFactory.addTypeFormer(tf.getId());
      }
    }
  }
  else if (const InjectedClassNameType* specificType = type->getAs<InjectedClassNameType>())
  {
    columbus::lim::asg::logical::Class *limClass = getOrCreateIncompleteNode_Class(specificType->getDecl());
    if (limClass)
    {
      type::TypeFormer& tf = limFactory.createTypeFormerType(limClass->getId());
      limFactory.addTypeFormer(tf.getId());
    }
  }
  else if (const TemplateTypeParmType* specificType = dyn_cast<TemplateTypeParmType>(type))
  {
    if (const TemplateTypeParmDecl* decl = specificType->getDecl())
    {
      //This is not eliminated... no reason
      auto it = globalInfo.limTable.find(conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext));
      if (it != globalInfo.limTable.end())
      {
        type::TypeFormer& tf = limFactory.createTypeFormerType(it->second->getId());
        limFactory.addTypeFormer(tf.getId());
      }
    }
  }
  else if (type->isFunctionType())
  {
    type::TypeFormer& tfp = limFactory.createTypeFormerPointer(PointerKind::ptkPointer); // need to store functions as function pointers (according to legacy)
    limFactory.addTypeFormer(tfp.getId());

    const FunctionType* specificType = type->castAs<FunctionType>();
    ConvertType(specificType->getReturnType().getTypePtr());

    limFactory.beginTypeFormerMethod();
    auto it = typeTable.find(uidFactory.createTypeId(QualType(specificType->getReturnType().getTypePtr(), 0), conversionInfo.pMyMangleContext));
    if (it != typeTable.end())
    {
      base::Base* limRetType = it->second;
      limFactory.setTypeFormerMethodHasReturnType(limRetType->getId());
    }

    if (type->isFunctionProtoType())
    {
      const FunctionProtoType* specificType = type->castAs<FunctionProtoType>();
      for (auto pt : specificType->getParamTypes())
      {
        ConvertType(pt.getTypePtr());
        auto it = typeTable.find(uidFactory.createTypeId(QualType(pt.getTypePtr(), 0), conversionInfo.pMyMangleContext));
        if (it != typeTable.end())
        {
          base::Base* limParamType = it->second;
          if (pt.getTypePtr()->isPointerType() || pt.getTypePtr()->isReferenceType())
            limFactory.addTypeFormerMethodHasParameterType(limParamType->getId(), ParameterKind::pmkInOut);
          else
            limFactory.addTypeFormerMethodHasParameterType(limParamType->getId(), ParameterKind::pmkIn);
        }
      }
    }

    type::TypeFormerMethod& limMethodType = limFactory.endTypeFormerMethod();
    limFactory.addTypeFormer(limMethodType.getId());
  }
  else if (const EnumType *et = dyn_cast_or_null<EnumType>(type))
  {
    if (const EnumDecl *ed = et->getDecl()) 
    {
      Class *limClass = getOrCreateIncompleteNode<Class>(ed);
      if (limClass)
      {
        type::TypeFormer& tf = limFactory.createTypeFormerType(limClass->getId());
        limFactory.addTypeFormer(tf.getId());
      }
    }
  }
  else
  {
    type::SimpleType& st = limFactory.createSimpleType(stkUnknown);
    type::TypeFormerType& tf = limFactory.createTypeFormerType(st.getId());
    limFactory.addTypeFormer(tf.getId());
  }
  /*else if (const AutoType *at = dyn_cast_or_null<AutoType>(type))
  {
    if (at->isDeduced())
    {
      at->dump();
      QualType dt = at->getDeducedType();
      if (!dt.isNull()) {
        dt->dump();
        createLIMType(dt.getTypePtr());
      }
      
      return;
    }
  }*/
  });
}

const Decl* ASTConverterVisitor::getDeclFromStmt(const Stmt& stmt)
{
  auto parents = context.getParents(stmt);

  auto it = parents.begin();
  if (it == parents.end())
    return nullptr;

  const Decl* parentDecl = it->get<Decl>();
  if (parentDecl)
    return parentDecl;

  const Stmt* parentStmt = it->get<Stmt>();
  if (parentStmt)
  {
    if (const LambdaExpr *lambdaExpr = dyn_cast_or_null<LambdaExpr>(parentStmt))
      return lambdaExpr->getCallOperator();
    else
      return getDeclFromStmt(*parentStmt);
  }

  return nullptr;
}

const clang::DeclContext* ASTConverterVisitor::getFunctionContextFromStmt(const clang::Stmt& stmt)
{
  if (const Decl* d = getDeclFromStmt(stmt))
  {
    if (FunctionDecl::classof(d))
      return cast<FunctionDecl>(d);

    if (ObjCMethodDecl::classof(d))
      return cast<ObjCMethodDecl>(d);

    const DeclContext* dc = d->getParentFunctionOrMethod();
    if (dyn_cast_or_null<const FunctionDecl>(dc) || dyn_cast_or_null<const ObjCMethodDecl>(dc))
      return dc;
  }

  return nullptr;
}

const clang::Decl* ASTConverterVisitor::getParentFromContext(const clang::Decl* decl)
{
  auto parents = context.getParents(*decl);
  if (parents.empty())
    return nullptr;

  return parents.begin()->get<Decl>();
}

void ASTConverterVisitor::handleAttributeAccess(const clang::ValueDecl* decl, const clang::FunctionDecl* func)
{
  //decl->dump();
  if (!decl || !func || decl->getAsFunction())
    return;

  if (isa<VarDecl>(decl) && decl->getParentFunctionOrMethod())
    return;

  decl = getPrimaryTemplateVersionOfMemberDecl(decl);
  //decl->dump();
  shared_ptr<UID> declUID = conversionInfo.uidFactory.create(decl, conversionInfo.pMyMangleContext);
  Attribute *limAttribute = getOrCreateIncompleteNode<Attribute>(decl);
  Method *limMethod = getOrCreateIncompleteNode_Method(func);

  if(limAttribute && limMethod)
  {
    // We need to check for access of global extern variables. These must be linked as the definition for the extern declaration is in a separate TU.
    // Maybe sometimes this is also needed for fields?
    if (const VarDecl *vd = dyn_cast<VarDecl>(decl))
    {
      if (!isDefinition(vd))
      {
        conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
          globalInfo.linker.unresolved_attribute_accesses.push_back(std::pair<std::shared_ptr<MergeUID>, columbus::lim::asg::logical::Method*>(std::static_pointer_cast<MergeUID>(declUID), limMethod));
        });
        return;
      }
    }

    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      AttributeAccess& access = globalInfo.limFactory.createAttributeAccess(limAttribute->getId());

      if (!contains(limMethod->getAccessesAttributeListIteratorBegin(), limMethod->getAccessesAttributeListIteratorEnd(), &access))
        limMethod->addAccessesAttribute(&access);
    });
    // We never use this imprint way, dunno if we should
    //access.setAccesses(decl->getNameAsString());
  }
}

/// Attempts to look up the original, non instantiated version of this declaration.
/// It only works with class members. They also must ha the base class NamedDecl
/// If the declaration is not templated to begin with, the function return it's parameter unchanged.
template<class T>
T ASTConverterVisitor::getPrimaryTemplateVersionOfMemberDecl(T input) {
  const NamedDecl *decl = dyn_cast_or_null<NamedDecl>(input);
  if(!decl)
    return input;

  T ret = input;
  if (const CXXRecordDecl *rec = dyn_cast_or_null<CXXRecordDecl>(decl->getDeclContext())){
    if(const CXXRecordDecl *rec_pat = rec->getTemplateInstantiationPattern()){
      bool alreadyFoundOne = false;

      for (auto result : rec_pat->lookup(decl->getDeclName())){
        if (T casted = dynamic_cast<T>(result)){
          if(alreadyFoundOne){
            //cout << "Failed manual lookup, ambiguous name " << decl->getNameAsString() << endl;
            return input;
          }else{
            alreadyFoundOne = true;
            ret = casted;
          }
        }
      }
    }
  }
  return ret;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::NamespaceDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl);
  sp.setRealizationLevel(RealizationLevel::relDefines);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::CXXRecordDecl* decl)
{
  SourcePosition sp;

  if (const ClassTemplateDecl* templateDecl = decl->getDescribedClassTemplate())
    sp = getSourcePositionHelper(templateDecl);
  else
    sp = getSourcePositionHelper(decl);
  
  sp.setRealizationLevel(isDefinition(decl)?RealizationLevel::relDefines:RealizationLevel::relDeclares);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::FriendDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl);
  sp.setRealizationLevel(RealizationLevel::relDeclares);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::TagDecl* decl)
{
  if(const CXXRecordDecl *crd = dyn_cast_or_null<CXXRecordDecl>(decl)) //weird cast, because c and c++ style structs common
    return getSourcePosition(crd);

  SourcePosition sp = getSourcePositionHelper(decl);
  sp.setRealizationLevel(isDefinition(decl)?RealizationLevel::relDefines:RealizationLevel::relDeclares);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::FunctionDecl* decl)
{
  // Note: Deleted and defaulted functions are definitions (as they are ODR).
  // Pure virtual functions can be declarations OR declarations and definitions (if there is an out-of-class definition for it).
  SourcePosition sp;
  const CXXRecordDecl *recordParent = dyn_cast_or_null<CXXRecordDecl>(decl->getParent());

  if (const FunctionTemplateDecl* templateDecl = decl->getDescribedFunctionTemplate())
    sp = getSourcePositionHelper(templateDecl);
  else if(recordParent && recordParent->isLambda())
    sp = getSourcePositionHelper(recordParent->getBeginLoc(),decl->getEndLoc());
  else
    sp = getSourcePositionHelper(decl);

  sp.setRealizationLevel(isDefinition(decl)?RealizationLevel::relDefines:RealizationLevel::relDeclares);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::ObjCMethodDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl);
  sp.setRealizationLevel(isDefinition(decl)?RealizationLevel::relDefines:RealizationLevel::relDeclares);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::FieldDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl->getBeginLoc(), decl->getLocation());
  sp.setRealizationLevel(RealizationLevel::relDefines);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::VarDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl->getBeginLoc(), decl->getLocation());
  sp.setRealizationLevel(isDefinition(decl)?RealizationLevel::relDefines:RealizationLevel::relDeclares);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::EnumConstantDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl);
  sp.setRealizationLevel(RealizationLevel::relDefines);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::ObjCInterfaceDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl);
  sp.setRealizationLevel(isDefinition(decl)?RealizationLevel::relDefines:RealizationLevel::relDeclares);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::ObjCCategoryDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl);
  sp.setRealizationLevel(RealizationLevel::relDefines);
  return sp;
}

columbus::lim::asg::SourcePosition ASTConverterVisitor::getSourcePosition(const clang::ObjCProtocolDecl* decl)
{
  SourcePosition sp = getSourcePositionHelper(decl);
  sp.setRealizationLevel(isDefinition(decl)?RealizationLevel::relDefines:RealizationLevel::relDeclares);
  return sp;
}

SourcePosition ASTConverterVisitor::getSourcePositionHelper(const Decl* decl)
{
  return getSourcePositionHelper(decl->getBeginLoc(), decl->getEndLoc());
}

SourcePosition ASTConverterVisitor::getSourcePositionHelper(SourceLocation start, SourceLocation end)
{
  const SourceManager& sm = context.getSourceManager();
  /*start.dump(sm);
  cout << endl;

  end.dump(sm);
  cout << endl;*/

  SourcePosition ret;

  // for macros, we would like to set these lines and columns to the place where they are expanded (instead of the macro location)
  // (this is the way it was done on the former one (EDG) too)
  if (start.isMacroID() || end.isMacroID())
  {
    ret.setLine(sm.getExpansionLineNumber(start));
    ret.setColumn(sm.getExpansionColumnNumber(start));
    ret.setEndLine(sm.getExpansionLineNumber(end));
    ret.setEndColumn(sm.getExpansionColumnNumber(end));
  }
  else
  {
    end = Lexer::getLocForEndOfToken(end, 1, sm, context.getLangOpts());
    ret.setLine(sm.getSpellingLineNumber(start));
    ret.setColumn(sm.getSpellingColumnNumber(start));
    ret.setEndLine(sm.getSpellingLineNumber(end));
    ret.setEndColumn(sm.getSpellingColumnNumber(end));
  }

  return ret;
}

template<> columbus::lim::asg::Attribute* ASTConverterVisitor::createNodeHelper<columbus::lim::asg::Attribute>()
{
  return conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    return globalInfo.limFactory.createAttributeNode();
  });
}

template<> columbus::lim::asg::Package* ASTConverterVisitor::createNodeHelper<columbus::lim::asg::Package>()
{
  return conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    return globalInfo.limFactory.createPackageNode();
  });
}

template<> columbus::lim::asg::Class* ASTConverterVisitor::createNodeHelper<columbus::lim::asg::Class>()
{
  return conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    return globalInfo.limFactory.createClassNode();
  });
}

template<> columbus::lim::asg::Method* ASTConverterVisitor::createNodeHelper<columbus::lim::asg::Method>()
{
  return conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    return globalInfo.limFactory.createMethodNode();
  });
}

template<> columbus::lim::asg::MethodGeneric* ASTConverterVisitor::createNodeHelper<columbus::lim::asg::MethodGeneric>()
{
  return conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    return globalInfo.limFactory.createMethodGenericNode();
  });
}

template<> columbus::lim::asg::MethodGenericSpec* ASTConverterVisitor::createNodeHelper<columbus::lim::asg::MethodGenericSpec>()
{
  return conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    return globalInfo.limFactory.createMethodGenericSpecNode();
  });
}

template<> columbus::lim::asg::ClassGeneric* ASTConverterVisitor::createNodeHelper<columbus::lim::asg::ClassGeneric>()
{
  return conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    return globalInfo.limFactory.createClassGenericNode();
  });
}

template<> columbus::lim::asg::ClassGenericSpec* ASTConverterVisitor::createNodeHelper<columbus::lim::asg::ClassGenericSpec>()
{
  return conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    return globalInfo.limFactory.createClassGenericSpecNode();
  });
}

void ASTConverterVisitor::addMemberEdge(const clang::Decl* parent, columbus::lim::asg::logical::Member* to)
{
  if (!parent || !to) {
    WriteMsg::write(WriteMsg::mlDebug, "addMemberEdge ERROR: parent is null\n");
    return;
  }

  // This is a rare case where the "extern "C"" linkage declaration surrounds the actual declaration
  // This could be around a function or global var ; this is always in some namespace scope and it might be nested
  // So we just step through it and call recursively
  if (const LinkageSpecDecl *lsd = dyn_cast_or_null<LinkageSpecDecl>(parent))
  {
    addMemberEdge(dyn_cast<Decl>(lsd->getParent()),to);
  }
  else if (parent && (isa<NamespaceDecl>(parent) || isa<FunctionDecl>(parent) || isa<RecordDecl>(parent) || isa<EnumDecl>(parent)
        || isa<ObjCInterfaceDecl>(parent) || isa<ObjCMethodDecl>(parent) || isa<ObjCCategoryDecl>(parent) || isa<ObjCProtocolDecl>(parent)))
  {
    Scope *limParent = getOrCreateIncompleteNode_Scope(parent);
    if(limParent)
    {
      // Add it only once.
      for (auto mit = limParent->getMemberListIteratorBegin(); mit != limParent->getMemberListIteratorEnd(); ++mit)
      {
        if (mit->getId() == to->getId())
          return;
      }

      limParent->addMember(to);
      return;
    }
  } 
  else if (isa<TranslationUnitDecl>(parent))
  {
    // Add it only once.
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      for (auto mit = globalInfo.limFactory.getRoot()->getMemberListIteratorBegin();
        mit != globalInfo.limFactory.getRoot()->getMemberListIteratorEnd();
        ++mit)
      {
        if (mit->getId() == to->getId())
          return;
      }
      globalInfo.limFactory.getRoot()->addMember(to);
    });
  }
  else
  {
    WriteMsg::write(WriteMsg::mlDebug, "addMemberEdge ERROR: parent is not a handled type\n");
  }
}

void ASTConverterVisitor::addUsesEdgeForStmt(columbus::lim::asg::logical::Member* to, const clang::Stmt* stmt, bool recursive)
{
  // Safety.
  if (!to || !stmt)
    return;

  // Add result types.
  // Note: Not all cases are handled in the switch, because most of them only contain sub-expressions
  // on which we can just iterate over with Stmt::children(). Non-standard extensions are also ignored.
  // TODO: Not yet tested and some cases are known to be missing the addition of type info.
  switch (stmt->getStmtClass())
  {
  case clang::Stmt::CXXBoolLiteralExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXNoexceptExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXNullPtrLiteralExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXThisExprClass:
    {
      const CXXThisExpr* e = cast<CXXThisExpr>(stmt);
      //if (!e->isImplicit()) //ez menjen implicitbe is!
      addUsesEdgeForType(to, e->getType().getTypePtr());
    }
    break;
  case clang::Stmt::CXXTypeidExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CallExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXMemberCallExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXOperatorCallExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::UserDefinedLiteralClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CStyleCastExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXFunctionalCastExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXConstCastExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXDynamicCastExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXReinterpretCastExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CXXStaticCastExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CharacterLiteralClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::CompoundLiteralExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::DeclRefExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::FloatingLiteralClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::IntegerLiteralClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::LambdaExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    return; // dont traverse into lambdas ever
    break;
  case clang::Stmt::MemberExprClass:
  {
    const Type* t = cast<Expr>(stmt)->getType().getTypePtr();
    if (t != nullptr && !t->isPlaceholderType())
      addUsesEdgeForType(to, t);
    break;
  }
  case clang::Stmt::SizeOfPackExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::StringLiteralClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  case clang::Stmt::UnaryExprOrTypeTraitExprClass:
    {
      const UnaryExprOrTypeTraitExpr* expr = cast<UnaryExprOrTypeTraitExpr>(stmt);
      if (expr->isArgumentType())
        addUsesEdgeForType(to, expr->getArgumentType().getTypePtr());
      else
        addUsesEdgeForStmt(to, cast<UnaryExprOrTypeTraitExpr>(stmt)->getArgumentExpr());
    }
    break;
  case clang::Stmt::CXXConstructExprClass:
    addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  default:
    //addUsesEdgeForType(to, cast<Expr>(stmt)->getType().getTypePtr());
    break;
  }

  // Recursively visit sub-expressions.
  if(recursive)
    for (const Stmt* c : stmt->children())
      addUsesEdgeForStmt(to, c);
}

void ASTConverterVisitor::addUsesEdgeForType(columbus::lim::asg::logical::Member* to, const clang::Type* type)
{
  //type->dump();
  //cout << conversionInfo.uidFactory.createTypeId(QualType(type, 0)) << endl;
  ConvertType(type);
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
  auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext));
  if (it != globalInfo.typeTable.end())
  {
    //cout << it->second->getId() << endl;
    bool found = false;
    // Ensure that it's not added
    for (auto it2 = to->getUsesListIteratorBegin(); it2 != to->getUsesListIteratorEnd(); ++it2)
    {
      if (it2->getId() == it->second->getId())
      {
        found = true;
        break;
      }
    }

    if (Method* m = dynamic_cast<Method*>(to))
    {
      // Ensure that it's not added already as instantiation
      for (auto mit = m->getInstantiatesListIteratorBegin(); mit != m->getInstantiatesListIteratorEnd(); ++mit)
      {
        if (mit->getId() == it->second->getId())
        {
          found = true;
          break;
        }
      }
      // Ensure that it's not added already as return value
      for (auto mit = m->getReturnsListIteratorBegin(); mit != m->getReturnsListIteratorEnd(); ++mit)
      {
        if (mit->getId() == it->second->getId())
        {
          found = true;
          break;
        }
      }
      // Ensure that it's not added already as parameter
      for (auto mit = m->getParameterListIteratorBegin(); mit != m->getParameterListIteratorEnd(); ++mit)
      {
        if (mit->getType() && mit->getType()->getId() == it->second->getId())
        {
          found = true;
          break;
        }
      }
    }
    else if(Attribute* a = dynamic_cast<Attribute*>(to))
    {
      // Ensure that it's not added already as hasType
      for (auto ait = a->getTypeListIteratorBegin(); ait != a->getTypeListIteratorEnd(); ++ait)
      {
        if (ait->getId() == it->second->getId())
        {
          found = true;
          break;
        }
      }
    }
    if (!found)
    {
      to->addUses(it->second);
    }
  }
  });
}

bool ASTConverterVisitor::addInstantiatesEdge(const clang::FunctionDecl* f, const clang::Type* type)
{
  Method *m = getOrCreateIncompleteNode_Method(f);
  if(!m)
    return false;

  ConvertType(type);
  columbus::lim::asg::type::Type* t = nullptr;
  conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
    auto rit = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext));
    if (!(rit == globalInfo.typeTable.end()))
      t = rit->second;
  });

  if (!t)
    return false;

  // Ensure that it's not added already.
  for (auto it = m->getInstantiatesListIteratorBegin(); it != m->getInstantiatesListIteratorEnd(); ++it)
  {
    if (it->getId() == t->getId())
      return false;
  }

  // If it's added as a 'uses' edge, remove the uses edge.
  for (auto it = m->getUsesListIteratorBegin(); it != m->getUsesListIteratorEnd(); ++it)
  {
    if (it->getId() == t->getId())
    {
      m->removeUses(it->getId());
      break;
    }
  }

  m->addInstantiates(t);
  return true;
}

template<class T>
void ASTConverterVisitor::addTemplateArgumentEdge(const clang::TemplateArgument& arg, T* limTo)
{
  // Type that needs to be added as argument.
  const Type* type;
  switch (arg.getKind())
  {
  case TemplateArgument::Type:
    type = arg.getAsType().getTypePtr();
    break;

  case TemplateArgument::Declaration:
    type = arg.getAsDecl()->getType().getTypePtr();
    break;

  case TemplateArgument::NullPtr:
    type = arg.getNullPtrType().getTypePtr();
    break;

  case TemplateArgument::Integral:
    type = arg.getIntegralType().getTypePtr();
    break;

  case TemplateArgument::Template:
    {
      const TemplateDecl* d = arg.getAsTemplate().getAsTemplateDecl();
      if (d)
      {
        if (const TypeDecl* td = dyn_cast_or_null<TypeDecl>(d->getTemplatedDecl()))
          type = td->getTypeForDecl();
        else
          type = nullptr;
      }
      else
      {
        type = nullptr;
      }
    }
    break;

  case TemplateArgument::TemplateExpansion:
    /* TODO */
    type = nullptr;
    break;

  case TemplateArgument::Expression:
    /* TODO */
    type = nullptr;
    break;

  case TemplateArgument::Pack:
    for (const TemplateArgument& a : arg.pack_elements())
      addTemplateArgumentEdge(a, limTo);
    return;

  default:
    type = nullptr;
    break;
  }

  if (type)
  {
    ConvertType(type);
    conversionInfo.globalInfo.call([&](GlobalASTConversionInfo& globalInfo) {
      auto it = globalInfo.typeTable.find(conversionInfo.uidFactory.createTypeId(QualType(type, 0), conversionInfo.pMyMangleContext));
      if (it != (globalInfo.typeTable.end()))
        limTo->addArguments(it->second, tackNone);
    });
  }
}

Convert2LimAction::Convert2LimAction(ASTConversionInfo& conversionInfo)
  : conversionInfo(conversionInfo)
{}

unique_ptr<ASTConsumer> Convert2LimAction::CreateASTConsumer(CompilerInstance& compiler, StringRef inFile)
{
  conversionInfo.pMyMangleContext.reset(clang::ItaniumMangleContext::create(compiler.getASTContext(), compiler.getDiagnostics()));
  return unique_ptr<ASTConsumer>(new ASTConverterConsumer(conversionInfo));
}

unique_ptr<FrontendActionFactory> newConvert2LimActionFactory(ASTConversionInfo& conversionInfo)
{
  class SimpleFrontendActionFactory : public FrontendActionFactory {
  public:
    SimpleFrontendActionFactory(ASTConversionInfo& conversionInfo) : conversionInfo(conversionInfo) {}
    unique_ptr<clang::FrontendAction> create() override { return unique_ptr<clang::FrontendAction>(new Convert2LimAction(conversionInfo)); }
  private:
    ASTConversionInfo& conversionInfo;
  };

  return unique_ptr<FrontendActionFactory>(new SimpleFrontendActionFactory(conversionInfo));
}


