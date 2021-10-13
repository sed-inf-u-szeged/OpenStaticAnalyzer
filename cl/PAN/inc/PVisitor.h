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

#ifndef __ASTVISITOR_H_
#define __ASTVISITOR_H_

#ifdef PY3
#include <python3.8/Python.h>
#else
#include <python2.7/Python.h>
#endif
#include "PBuilder.h"
#ifdef PY3
#include <python3.8/Python-ast.h>
#else
#include <python2.7/Python-ast.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#ifdef PY3
#include <python3.8/node.h>
#include <python3.8/token.h>
#include <python3.8/grammar.h>
#include <python3.8/parsetok.h>
#include <python3.8/errcode.h>
#include <python3.8/code.h>
#include <python3.8/pyarena.h>
#include <python3.8/asdl.h>
#else
#include <python2.7/node.h>
#include <python2.7/token.h>
#include <python2.7/grammar.h>
#include <python2.7/parsetok.h>
#include <python2.7/errcode.h>
#include <python2.7/code.h>
#include <python2.7/pyarena.h>
#include <python2.7/asdl.h>
#endif
#include "PlLOC.h"
#include <string>
#include <vector>
#include <map>

using namespace columbus;
using namespace columbus::python::asg;

namespace columbus {

class ASTVisitor {

private:
  PBuilder& pBuilder;
  std::vector<int> logical_lines;
  std::map<operator_ty, AssignmentKind> assignment_map;
  std::map<operator_ty, BinaryArithmeticKind> arithmetic_map;
  std::map<cmpop_ty, BinaryLogicalKind> comp_map;
  std::map<unaryop_ty, UnaryKind> unary_map;
  std::map<_boolop, BinaryLogicalKind> boolop_map;

  std::string path;
  std::map<NodeId, std::string> object_map;
  std::list< std::pair< std::map<std::string, NodeId>* , NodeKind > > objects;
  std::list< std::multimap<std::string, NodeId>* > temp_objects;
  std::list< std::map<NodeId, bool>* > reverse_edge_objects;    // decides if we should set a reverse edge from object to id
  std::list< std::set<std::string>* > global_list;
  bool build_object;
  bool collect_objects;

  std::map<int, NodeId> commentHolderCandidates;

public:
  ASTVisitor(PBuilder& pBuilder);

  Factory* Visit(std::string path_name, std::string modul_name, mod_ty root, std::vector<int>& logical_lines,
    std::map<int, NodeId>& commentMap );

  std::map<NodeId, std::string>& getObjectMap();

  PBuilder& getBuilder();

private:

  inline std::string getFunctionName(expr_ty name);

  inline std::vector<NodeId> visitStmtAsdl(asdl_seq* ch_list, NodeId docstring = 0);

  inline std::vector<NodeId> visitExceptHandlerAsdl(asdl_seq* ch_list);

  inline std::vector<NodeId> visitExprAsdl(asdl_seq* ch_list);

  inline std::vector<NodeId> visitIdentifierAsdl(asdl_seq* ch_list);

  inline std::vector<NodeId> visitBaseSpecifierAsdl(asdl_seq* ch_list);

  inline std::vector<NodeId> visitParameterListAsdl(arguments_ty arguments);

  inline std::vector<NodeId> visitAliasAsdl(asdl_seq* ch_list, stmt_ty parent);

  inline std::vector<NodeId> visitKeywordAsdl(asdl_seq* ch_list);

  inline std::vector<NodeId> visitComprehensionAsdl(asdl_seq* ch_list);

  inline std::vector< BinaryLogicalKind > visitCompAsdl(asdl_int_seq* ch_list);

  inline std::vector<NodeId> visitSliceAsdl(asdl_seq* ch_list);

  void buildLocalObjects();

  NodeId visitMod(std::string modul_name, mod_ty parent); 

  NodeId visitStmt(stmt_ty parent);

  NodeId visitExceptHandler(excepthandler_ty parent);

  NodeId visitExpr(expr_ty parent);

  NodeId visitSlice(slice_ty parent);

#ifdef PY3
  void visitArg(std::vector<NodeId>& params, arg_ty parent, python::asg::ParameterKind kind);
  void visitArg(std::vector<NodeId>& params, asdl_seq* parent, python::asg::ParameterKind kind);
#endif

  NodeId createParamAndObject(std::string name, python::asg::ParameterKind kind, NodeId annotation, NodeId lastParam = 0);

  int getLLOC(int first_line, int last_line, std::vector<int> logical_lines);

  NodeId getDocstring(asdl_seq* ch_list);

  void getOuterNodeInLine(NodeId id, int forcedLine = 0);

  template<typename T>
  NodeId visitFunctionDef(const T& stmt, bool isAsync);

  template<typename T>
  NodeId visitFor(const T& stmt, bool isAsync);

  template<typename T>
  NodeId visitWith(const T& stmt, bool isAsync);

};
}

#endif
