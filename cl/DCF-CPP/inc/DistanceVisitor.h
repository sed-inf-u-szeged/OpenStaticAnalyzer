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

#ifndef DISTANCEVISITOR_H_
#define DISTANCEVISITOR_H_


#include <clang/Metrics/ASTPrePostVisitor.h>

class DistanceVisitor : public clang::ASTPrePostVisitor{
  private:

      void* child;
      
      // the number of AST nodes from the beginning of the first named ancestor node to the beginning of the instance
      unsigned int l1; 
      // the length of the instance (measured by the number of AST nodes)
      unsigned int l2;
      //the number of nodes from the end of the instance to the end of the first named ancestor node
      unsigned int l3;

      short state;
      
    public:
      DistanceVisitor(void* _child) : child(_child) ,l1(0), l2(0), l3(0), state(0) { };
      unsigned int getL1() const {
        return l1;
      }
      unsigned int getL2() const {
        return l2;
      }
      unsigned int getL3() const {
        return l3;
      }
      
      bool visitDecl(clang::Decl* decl) { 
        if(decl == child && state == 0){
          state = 1;
          l2++;
        } else if (state==0) {
        l1++;
        } else if (state==1) {
          l2++;
        } else if (state==2) {
          l3++;
        }
        
        return true; 
      }
      
      void visitEndDecl(clang::Decl* decl) {
        if (decl == child && state == 1) {
          state=2;
        }
      }

      bool visitStmt(clang::Stmt* stmt) { 
        if(stmt == child && state == 0){
          state = 1;
          l2++;
        } else if (state==0) {
        l1++;
        } else if (state==1) {
          l2++;
        } else if (state==2) {
          l3++;
        }
        
        return true; 
      }
      void visitEndStmt(clang::Stmt* stmt) {
        if (stmt == child && state == 1) {
          state=2;
        }
      }

      bool visitType(clang::Type* type) {
        if(type == child && state == 0){
          state = 1;
          l2++;
        } else if (state==0) {
        l1++;
        } else if (state==1) {
          l2++;
        } else if (state==2) {
          l3++;
        }
        
        return true; 
      }
      void visitEndType(clang::Type* type) {
        if (type == child && state == 1) {
          state=2;
        }
      }
      
};


#endif /* DISTANCEVISITOR_H_ */
