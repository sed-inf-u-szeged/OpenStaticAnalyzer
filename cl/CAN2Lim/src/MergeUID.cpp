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


#include  "../inc/MergeUID.h"
#include <clang/AST/AST.h>
#include <clang/AST/Mangle.h>
#include <clang/Frontend/CompilerInstance.h>
#include <llvm/Support/raw_ostream.h>
#include <common/inc/FileSup.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clangsupport/CANCommon.h>
#include <clang/AST/ParentMapContext.h>

#include <iostream>

using namespace std;
using namespace clang;

boost::mutex MergeUID::m;
extern CANFilePathRenamer cANFilePathRenamer;

MergeUID::MergeUID(const string& mangledName, std::string fileName, unsigned lineNumber, unsigned columnNumber, bool isNamespace)
  : mangledName (mangledName)
  , fileName(common::pathCanonicalize(fileName))
  , lineNumber(lineNumber)
  , columnNumber(columnNumber)
  , hashValue (std::hash<string>()(mangledName /*+ (isNamespace ? "" : "|" + common::pathCanonicalize(fileName))*/))
  , isNamespace(isNamespace)
{
  // TODO: More sophisticated solution to combine hash values.
}

bool MergeUID::equals(const metrics::UID& rhs) const
{
  assert(typeid(rhs) == typeid(MergeUID) && "Invalid UID type!");
  const MergeUID& other = static_cast<const MergeUID&>(rhs);

  // For namespaces, only the mangled name counts.
  if (isNamespace)
    return mangledName == other.mangledName;

  // Allow 0 line numbers to always compare equal so we can safely compare Decl IDs with Type IDs.
  return mangledName  == other.mangledName &&
         (!lineNumber || !other.lineNumber || lineNumber == other.lineNumber)  &&
         (!columnNumber || !other.columnNumber || columnNumber == other.columnNumber) &&
         fileName  == other.fileName;
}

size_t MergeUID::hash() const
{
  return hashValue;
}

void MergeUIDFactory::declContextName(SourceManager& sm, llvm::raw_string_ostream& ss, const DeclContext* parent)
{
  // For non-functions the qualified name identifies the object - only need to take care of cases where decl
  // is within an anonymous namespace or class.
  // Iterate through the AST hierarchy to check if there's an anonymous parent.
  while (parent)
  {
    if (NamespaceDecl::classofKind(parent->getDeclKind()))
    {
      const NamespaceDecl* ns = static_cast<const NamespaceDecl*>(parent);
      if (ns->isAnonymousNamespace())
      {
        // Put the filepath into the stream, prefixed by a "//" and break.
        ss << "//" << cANFilePathRenamer.changeToLIMCompatible(common::pathCanonicalize(sm.getFilename(ns->getLocation()).str()));
        break;
      }
    }
    else if (CXXRecordDecl::classofKind(parent->getDeclKind()))
    {
      const CXXRecordDecl* cs = static_cast<const CXXRecordDecl*>(parent);
      if (cs->isAnonymousStructOrUnion() || cs->getName().empty())
      {
        // Put the filepath into the stream, prefixed by a "//".
        ss << "//" << cANFilePathRenamer.changeToLIMCompatible(common::pathCanonicalize(sm.getFilename(cs->getLocation()).str()));

        // Also put the line info into the stream, as there can be multiple anonymous classes within the same file.
        ss << "//" << sm.getSpellingLineNumber(cs->getBeginLoc()) << '_' << sm.getSpellingLineNumber(cs->getEndLoc());
        ss << '_' << sm.getSpellingColumnNumber(cs->getBeginLoc()) << '_' << sm.getSpellingColumnNumber(cs->getEndLoc());

        break;
      }
    }
    else if (EnumDecl::classofKind(parent->getDeclKind()))
    {
      const EnumDecl* ed = static_cast<const EnumDecl*>(parent);
      if (!ed->hasNameForLinkage())
      {
        // Put the filepath into the stream, prefixed by a "//".
        ss << "//" << cANFilePathRenamer.changeToLIMCompatible(common::pathCanonicalize(sm.getFilename(ed->getLocation()).str()));

        // Also put the line info into the stream, as there can be multiple anonymous classes within the same file.
        ss << "//" << sm.getSpellingLineNumber(ed->getBeginLoc()) << '_' << sm.getSpellingLineNumber(ed->getEndLoc());
        ss << '_' << sm.getSpellingColumnNumber(ed->getBeginLoc()) << '_' << sm.getSpellingColumnNumber(ed->getEndLoc());

        break;
      }
    }

    // Continue the loop with the parent of the parent
    parent = parent->getParent();
  }
}

void MergeUIDFactory::mangleTypeName(const Type* type, llvm::raw_string_ostream& ss, shared_ptr<MangleContext> mangleContext)
{
  // Handle null.
  if (!type)
  {
    //std::cout << "BOOOO" << endl;
    ss << "<missing id " << (itsMissingIdCounter++) << ">";
    return;
  }
  /*if (const AutoType* at = dyn_cast_or_null<AutoType>(type))
  {
    if (at->isDeduced())
    {
      QualType dt = at->getDeducedType();;
      mangleTypeName(dt.getTypePtrOrNull(),ss);
      return;
    }
  }*/

  // Special case for template parameters.
  if (const TemplateTypeParmType* t = dyn_cast_or_null<TemplateTypeParmType>(type))
  {
    //std::cout << "TOOOO" << endl;
    ss << static_cast<MergeUID&>(*create(t->getDecl(), mangleContext)).getMangledName();
    return;
  }

  if (const TemplateSpecializationType *specType = dyn_cast_or_null<TemplateSpecializationType>(type))
  {
    if (type->isDependentType())
    {
      ss << "<unknown>";
      //NON_CANONICAL_UNLESS_DEPENDENT_TYPE
      //specType->anyDependentTemplateArguments();
      //specType->
    }
    else
    {
      try //this may throw an exception if it fails
      {
        mangleContext->mangleTypeName(QualType(specType, 0), ss);
      }
      catch (...)
      {
        ss << "<unknown>";
      }
    }
    
    //ss << "<unknown>"; //there is no other way for now, the above solution just crashes sometimes, maybe we should check if its dependent first, and dont magnel it then
    return;
  }

  /*
     TODO: Look into this in more detail as this can either crash the program or cause important types not get registered with proper ID.

     Examples:
      - If we did not allow InjectedClassNameType, 'SomeTemplateClass' would be missed in the following instantiation:

          template<template<class> class T> class TestClass {};
          template class TestClass<SomeTemplateClass>;

      - On the other hand if we allowed all dependent types, a simple lambda would crash the mangler:
      
          int y = 0;
          auto lambda = [&](int x)
          {
            return x + y;
          };

     Yet there might still be cases which could cause either a crash or missed registration.
  */
  if (type->isPlaceholderType() || ( (type->isDependentType() && !InjectedClassNameType::classof(type)) ) || FunctionNoProtoType::classof(type))
  {
    //std::cout << "FOOOO" << endl;
    
    //ss << "<missing id " << (itsMissingIdCounter++) << ">";
    ss << "<unknown>";
    return;
  }

  //cout << "LOOOOOOOOOOO" << endl;
  mangleContext->mangleTypeName(QualType(type, 0), ss);
}


unique_ptr<metrics::UID> MergeUIDFactory::create(const clang::Decl* decl, shared_ptr<clang::MangleContext> mangleContext)
{
  if (!decl)
    return make_unique<MergeUID>("<missing id " + std::to_string(itsMissingIdCounter++) + ">", declToFileName(decl, mangleContext->getASTContext()), 0, 0, false);

  ASTContext& astContext = mangleContext->getASTContext();
  SourceManager& sm = astContext.getSourceManager();
  string mangledName;

  llvm::raw_string_ostream ss(mangledName);
  unsigned ln, cn;
  string fileName = declToFileName(decl, mangleContext->getASTContext());
  bool isNamespaceDecl = NamespaceDecl::classof(decl);

  // Store line and column numbers. This is not stored for namespaces as all namespaces within the same
  // component are considered to be the same if they share their mangled name.
  if (isNamespaceDecl)
  {
    ln = cn = 0;
  }
  else
  {
    ln = sm.getSpellingLineNumber(decl->getLocation());
    cn = sm.getSpellingColumnNumber(decl->getLocation());
  }

  // First get the underlying templates, FriendDecl will use its own position not the templates.
  if (const FriendDecl* fd = dyn_cast<FriendDecl>(decl))
  {
    if (const TypeSourceInfo* tsi = fd->getFriendType())
      if (const Type* type = tsi->getType().getTypePtrOrNull())
        if (const CXXRecordDecl* classDecl = type->getAsCXXRecordDecl())
        {
          // Use the underlying CXXRecordDecl for Friend Class.
          decl = classDecl;

          // Use the template described by the class declaration if it's a template.
          if (auto td = classDecl->getDescribedClassTemplate())
            decl = td;
        }
  }
  else if (const CXXRecordDecl* rd = dyn_cast<CXXRecordDecl>(decl))
  {
    // Use the template described by the class declaration if it's a template.
    if (auto td = rd->getDescribedClassTemplate())
      decl = td;

    // CXXRecordDecl will use the position of the described template.
    ln = sm.getSpellingLineNumber(decl->getLocation());
    cn = sm.getSpellingColumnNumber(decl->getLocation());
  }

  // Try to mangle templates. If it's not possible, we still try to mangle their "untemplated" name.
  if (const TemplateDecl* td = dyn_cast_or_null<TemplateDecl>(decl))
  {
    //cout << "INTO THE TEMLPATE" << endl;
    const Type* type = nullptr;
    if (const ValueDecl* vd = dyn_cast_or_null<ValueDecl>(td->getTemplatedDecl()))
      type = vd->getType().getTypePtrOrNull();
    else if (const RecordDecl* rd = dyn_cast_or_null<RecordDecl>(td->getTemplatedDecl()))
      type = rd->getTypeForDecl();

    if (type)
    {
      mangleTypeName(type, ss, mangleContext);
      return make_unique<MergeUID>(ss.str(), declToFileName(decl, mangleContext->getASTContext()), ln, cn, false);
    }
  }

  if (FunctionDecl::classof(decl) && !isa<CXXDeductionGuideDecl>(decl))
  {
    const CXXRecordDecl *recordParent = dyn_cast_or_null<CXXRecordDecl>(static_cast<const FunctionDecl*>(decl)->getParent());

    // If this function is only visible from the current translation unit (eg.: static functions, functions in anonymous namespace)
    if (static_cast<const FunctionDecl*>(decl)->getLinkageAndVisibility().getLinkage() != Linkage::ExternalLinkage)
    {
      // Put the filepath into the stream, prefixed by a "//".
      ss << "//" << cANFilePathRenamer.changeToLIMCompatible(common::pathCanonicalize(sm.getFilename(static_cast<const FunctionDecl*>(decl)->getLocation()).str()));
    }

    // Use the built-in mangler to get the mangled name for the function.
    if (CXXConstructorDecl::classof(decl))
      mangleContext->mangleName(GlobalDecl(cast<CXXConstructorDecl>(decl), CXXCtorType::Ctor_Complete), ss);
    else if (CXXDestructorDecl::classof(decl))
      mangleContext->mangleName(GlobalDecl(cast<CXXDestructorDecl>(decl), CXXDtorType::Dtor_Complete), ss);
    else if (recordParent && recordParent->isLambda()) {
      ss << "//" << sm.getSpellingLineNumber(decl->getBeginLoc()) << '_' << sm.getSpellingLineNumber(decl->getEndLoc());
      ss << '_' << sm.getSpellingColumnNumber(decl->getBeginLoc()) << '_' << sm.getSpellingColumnNumber(decl->getEndLoc());
      ss << "(lambda)";
    }
    else
      mangleContext->mangleName(cast<FunctionDecl>(decl), ss);
  }
  else if (const VarDecl* vd = dyn_cast_or_null<VarDecl>(decl))
  {
    if (vd->getLinkageAndVisibility().getLinkage() != Linkage::ExternalLinkage)
    {
      // Put the filepath into the stream, prefixed by a "//".
      ss << "//" << cANFilePathRenamer.changeToLIMCompatible(common::pathCanonicalize(sm.getFilename(static_cast<const FunctionDecl*>(decl)->getLocation()).str()));
    }
    
    if (isa<ParmVarDecl>(decl) || isa<DependentSizedArrayType>(vd->getType())) //for some reasion this crashes the mangler...
    {
      ss << "<missing id " << (itsMissingIdCounter++) << ">";
    }
    else
    {
      //very dangerous line, crashes often
      mangleContext->mangleName(vd, ss);
    }
  }
  else if (const EnumConstantDecl* ecd = dyn_cast<EnumConstantDecl>(decl))
  {
    // Get the EnumDecl corresponding to the constant.
    auto parents = astContext.getParents(*decl);
    assert(!parents.empty() && "Container cannot be empty as EnumDecl is always a parent to the enum constant.");
    
    // Create name for parent first.
    const EnumDecl* p = cast<EnumDecl>(parents.begin()->get<Decl>());
    declContextName(sm, ss, p);
    ss << p->getNameAsString();

    // Append the name of the constant to it.
    ss << "::" << ecd->getNameAsString();
  }
  else if (const CXXRecordDecl* rd = dyn_cast<CXXRecordDecl>(decl))
  {
    if (auto td = dyn_cast<ClassTemplateSpecializationDecl>(decl))
    {
      mangleTypeName(td->getTypeForDecl(), ss, mangleContext);
    }
    else
    {
      declContextName(sm, ss, rd);
      rd->printQualifiedName(ss);
    }
  }
  else if (const DeclContext* parent = dyn_cast<DeclContext>(decl))
  {
    // Generate name.
    declContextName(sm, ss, parent);

    // TODO: Look into this!
    // Only one problem remains: class template specializations. Qualified name does not print template
    // parameters, so the specializations would get the same ID.
    // Once again, we assign the source location to it.
    /*if (const CXXRecordDecl* spec = dyn_cast<ClassTemplateSpecializationDecl>(decl))
    {
      spec = spec->getDefinition();
      if (spec)
      {
        SourceLocation loc = spec->getSourceRange().getBegin();
        ss << '<' << sm.getFilename(loc) << "//" << sm.getSpellingLineNumber(loc) << '_' << sm.getSpellingColumnNumber(loc) << '>';
      }
      else
        ss << "<missing-specialization-definition>";
    }*/

    // Append the qualified name to the stream
    if (NamedDecl::classof(decl))
    {
      const NamedDecl* nd = cast<NamedDecl>(decl);
      nd->printQualifiedName(ss);

    }
  }
  else if (const FieldDecl* fd = dyn_cast<FieldDecl>(decl))
  {
    if (const ObjCIvarDecl* iVar = dyn_cast<ObjCIvarDecl>(fd))
      declContextName(sm, ss, iVar->getContainingInterface());
    else
          declContextName(sm, ss, fd->getParent());

    // Append the qualified name to the stream
    const NamedDecl* nd = cast<NamedDecl>(decl);
    nd->printQualifiedName(ss);
  }
  else if (const TemplateTypeParmDecl* nd = dyn_cast_or_null<TemplateTypeParmDecl>(decl))
  {
    // Create name for parent first, which is always a TemplateDecl somewhere on the top.
    const Decl* p = decl;
    while (true)
    {
      if (!p)
        goto MISSING_ID;

      auto parents = astContext.getParents(*p);
      if (parents.empty())
        goto MISSING_ID;

      p = dyn_cast_or_null<NamedDecl>(parents.begin()->get<Decl>());
      if (!p)
        goto MISSING_ID;

      if (const TemplateDecl* tmp = dyn_cast_or_null<TemplateDecl>(p))
      {
        p = tmp->getTemplatedDecl();
        break;
      }
      else if (CXXRecordDecl::classof(p) || FunctionDecl::classof(p))
        break;
    }

    if (!p)
      goto MISSING_ID;

    // To mangle "in" the parent's name, we just create an ID for the parent and append the ID of the template parameter after it.
    auto uid = create(p, mangleContext);
    ss << static_cast<MergeUID&>(*uid).getMangledName();

    // Append the name of the parameter to it.
    ss << "::<" << nd->getNameAsString() << ">";
  }
  else
  {
  MISSING_ID:
    ss << "<missing id " << (itsMissingIdCounter++) << ">";
  }

  return make_unique<MergeUID>(ss.str(), fileName, ln, cn, isNamespaceDecl);
}

std::unique_ptr<clang::metrics::UID> MergeUIDFactory::createTypeId(const clang::QualType type, shared_ptr<MangleContext> mangleContext)
{
  string mangledName;
  llvm::raw_string_ostream ss(mangledName);
  mangleTypeName(type.getTypePtrOrNull(), ss, mangleContext);
  return make_unique<MergeUID>(ss.str(), declToFileName(nullptr, mangleContext->getASTContext()), 0, 0, false);
}

std::string MergeUIDFactory::declToFileName(const clang::Decl* decl, ASTContext& astContext)
{
  if (!decl)
    return "";

  clang::SourceLocation loc = decl->getLocation();
  if (loc.isMacroID())
    loc = astContext.getSourceManager().getExpansionLoc(loc); // we need this, as for code in macros, the spellingloc has no file attached to it

  return cANFilePathRenamer.changeToLIMCompatible(common::pathCanonicalize(astContext.getSourceManager().getFilename(loc).str()));
}
