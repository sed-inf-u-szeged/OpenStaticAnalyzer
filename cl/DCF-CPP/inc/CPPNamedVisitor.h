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

#ifndef DCF_CPP_NAMED_VISITOR_H
#define DCF_CPP_NAMED_VISITOR_H

#include <clang/Metrics/ASTPrePostVisitor.h>
#include <clang/Frontend/ASTUnit.h>
#include <boost/lexical_cast.hpp>

#include <iostream>


using namespace std;

class CPPNamedVisitor : public clang::ASTPrePostVisitor {
  
private:
  std::string repr;
public:
  CPPNamedVisitor() : repr("") {}
  operator std::string() { return repr; }
  
  /* visit DECL base */
  bool visitDecl(clang::Decl* decl) { 
    repr += std::string("#") + std::to_string(decl->getKind());
    
    if(clang::isa<clang::NamedDecl>(decl)){
      visitNamedDecl(static_cast<clang::NamedDecl*>(decl));
    }
    
    return true; 
  }
  
  void visitEndDecl(clang::Decl* decl) {
    if(clang::isa<clang::NamedDecl>(decl)){
      visitEndNamedDecl(static_cast<clang::NamedDecl*>(decl));
    }
    visitEnd();
  }

  /* visit STMT base */
  bool visitStmt(clang::Stmt* stmt) { 
    repr += std::string("#") + std::to_string(stmt->getStmtClass());
    
    if(clang::isa<clang::CallExpr>(stmt)){
      
      visitFunctionCallExpression(static_cast<clang::CallExpr*>(stmt));
      
    }else if(clang::isa<clang::StringLiteral>(stmt)){
      
      visitStringLiteral(static_cast<clang::StringLiteral*>(stmt));
      
    }else if(clang::isa<clang::IntegerLiteral>(stmt)){
      
      visitIntegerLiteral(static_cast<clang::IntegerLiteral*>(stmt));
      
    }
    
    return true; 
  }
  
  
  void visitEndStmt(clang::Stmt* stmt) {
    if(clang::isa<clang::CXXMemberCallExpr>(stmt)){
    
      visitEndFunctionCallExpression(static_cast<clang::CallExpr*>(stmt));
    
    }else if(clang::isa<clang::StringLiteral>(stmt)){
      
      visitEndStringLiteral(static_cast<clang::StringLiteral*>(stmt));
      
    }else if(clang::isa<clang::IntegerLiteral>(stmt)){
      
      visitEndIntegerLiteral(static_cast<clang::IntegerLiteral*>(stmt));
      
    }
    
    visitEnd();
  }

  //additional visit functions
  
  
  void visitEnd(){
    repr += std::string("$");
  }
  
  void visitNamedDecl(clang::NamedDecl* named){
    if(named->getSourceRange().isInvalid())
      return;
    
    repr += std::string("#") + std::to_string(named->getKind()) + std::string("(") + named->getNameAsString();
  }
  void visitEndNamedDecl(clang::NamedDecl* named){
    if(named->getSourceRange().isInvalid())
      return;
    
    repr += std::string(")");
    visitEnd();
  }
  
  
  void visitFunctionCallExpression(clang::CallExpr* callExpr){
    if(callExpr->getSourceRange().isInvalid())
      return;
    
    repr += std::string("#") + std::to_string(callExpr->getStmtClass());
    const clang::FunctionDecl* refersTo = callExpr->getDirectCallee();
    if (refersTo) {
      repr+=std::string("(")+refersTo->getNameAsString();
    }
  }
  void visitEndFunctionCallExpression(clang::CallExpr* callExpr){
    if(callExpr->getSourceRange().isInvalid())
      return;
    
    repr += std::string("#") + std::to_string(callExpr->getStmtClass());
    const clang::FunctionDecl* refersTo = callExpr->getDirectCallee();
    if (refersTo) {
      repr+=std::string(")");
    }
    visitEnd();
  }
  
  void visitStringLiteral(clang::StringLiteral* stringConst){
    if(stringConst->getSourceRange().isInvalid())
      return;
    
    repr += std::string("#") + std::to_string(stringConst->getStmtClass());
   
   ///** debug **/
   // clang::PresumedLoc PLoc_start, PLoc_end;
   // const clang::SourceManager& sm = AU->getASTContext().getSourceManager();
   // PLoc_start = sm.getPresumedLoc(stringConst->getLocStart());
   // PLoc_end = sm.getPresumedLoc(stringConst->getLocEnd());
   // cout << "\tString const at: " << PLoc_start.getFilename() << "[" << PLoc_start.getLine() << ":" << PLoc_start.getColumn() << " - " << PLoc_end.getLine() << ":" << PLoc_end.getColumn() << "]" << endl;
   ///** debug end **/ 
   
    clang::StringRef literalValue = stringConst->getBytes();
//    cout << "\t\tString const: " << literalValue.str() << endl;
//    cout << "\t\tString data: " << literalValue.data() << endl;
//    cout << "\t\tLength: " << stringConst->getLength() << endl;
//    cout << "\t\tChar byte width: " << stringConst->getCharByteWidth() << endl;
//    cout << "\t\tByte length: " << stringConst->getByteLength() << endl;
    repr+=std::string("(") + literalValue.str();
  }
  void visitEndStringLiteral(clang::StringLiteral* stringConst){
    if(stringConst->getSourceRange().isInvalid())
      return;
    
    repr+=std::string(")");
    visitEnd();
  }
  
  void visitIntegerLiteral(clang::IntegerLiteral* intConst){
    if(intConst->getSourceRange().isInvalid())
      return;
    
    repr += std::string("#") + std::to_string(intConst->getStmtClass());
    repr += std::string("(") + boost::lexical_cast<std::string>(intConst->getValue().getSExtValue()); 
  }
  void visitEndIntegerLiteral(clang::IntegerLiteral* intConst){
    if(intConst->getSourceRange().isInvalid())
      return;
    
    repr+=std::string(")");
    visitEnd();
  }
  
  void visitFloatingLiteral(clang::FloatingLiteral* floatConst){
    if(floatConst->getSourceRange().isInvalid())
      return;
    
    repr += std::string("#") + std::to_string(floatConst->getStmtClass());
    repr += std::string("(") + boost::lexical_cast<std::string>(floatConst->getValue().convertToDouble()); 
  }
  void visitEndFloatingLiteral(clang::FloatingLiteral* floatConst){
    if(floatConst->getSourceRange().isInvalid())
      return;
    
    repr+=std::string(")");
    visitEnd();
  }
  
};

  
#endif
