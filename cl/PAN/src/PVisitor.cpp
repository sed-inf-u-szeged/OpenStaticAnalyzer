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

#include "../inc/PVisitor.h"
#include "../inc/messages.h"
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <algorithm>

using namespace std;
using namespace common;

#ifdef PY3
#define PyString_AS_STRING PyUnicode_AsUTF8
#endif

#ifndef _DEBUG

#define EXCEPTION_LOC_BEGIN \
  try {
#define EXCEPTION_LOC_END(location) \
} catch (Exception e) { \
  WriteMsg::write(CMSG_EXCEPTION_AT, location); \
  WriteMsg::write(CMSG_POS, path.c_str(), parent->lineno, parent->col_offset); \
  WriteMsg::write(CMSG_ERROR, e.getLocation().c_str(), e.getMessage().c_str()); \
  exit(1); \
} catch (...) { \
  WriteMsg::write(CMSG_UNKNOWN_EXCEPTION, location); \
  WriteMsg::write(CMSG_POS, path.c_str(), parent->lineno, parent->col_offset); \
  exit(1); \
} \

#else

#define EXCEPTION_LOC_BEGIN
#define EXCEPTION_LOC_END(location)

#endif


ASTVisitor::ASTVisitor(PBuilder& pBuilder): pBuilder(pBuilder){
  assignment_map[Add] = askAdd;
  assignment_map[Sub] = askSub;
  assignment_map[Mult] = askMult;
  assignment_map[Div] = askDiv;
  assignment_map[Mod] = askMod;
  assignment_map[Pow] = askPow;
  assignment_map[LShift] = askLShift;
  assignment_map[RShift] = askRShift;
  assignment_map[BitOr] = askBitOr;
  assignment_map[BitXor] = askBitXor;
  assignment_map[BitAnd] = askBitAnd;
  assignment_map[FloorDiv] = askFloorDiv;

  arithmetic_map[Add] = bakAddition;
  arithmetic_map[Sub] = bakSubtraction;
  arithmetic_map[Mult] = bakMultiplication;
  arithmetic_map[Div] = bakDivision;
  arithmetic_map[Mod] = bakModulo;
  arithmetic_map[Pow] = bakPow;
  arithmetic_map[LShift] = bakLShift;
  arithmetic_map[RShift] = bakRShift;
  arithmetic_map[BitOr] = bakBitOr;
  arithmetic_map[BitXor] = bakBitXor;
  arithmetic_map[BitAnd] = bakBitAnd;
  arithmetic_map[FloorDiv] = bakFloorDivision;

  comp_map[Eq] = blkEq;
  comp_map[NotEq] = blkNotEq;
  comp_map[Lt] = blkLt;
  comp_map[LtE] = blkLtE;
  comp_map[Gt] = blkGt;
  comp_map[GtE] = blkGtE;
  comp_map[Is] = blkIs;
  comp_map[IsNot] = blkIsNot;
  comp_map[In] = blkIn;
  comp_map[NotIn] = blkNotIn;

  boolop_map[And] = blkAnd;
  boolop_map[Or] = blkOr;

  unary_map[Invert] = unkInvert;
  unary_map[Not] = unkNot;
  unary_map[UAdd] = unkPlus;
  unary_map[USub] = unkMinus;

  build_object = false;
  collect_objects = false;
}

std::map<NodeId, std::string>& ASTVisitor::getObjectMap() {
  return object_map;
}

PBuilder& ASTVisitor::getBuilder() {
  return pBuilder;
}

std::string ASTVisitor::getFunctionName(expr_ty name) {
  std::string ret;

  while(name->kind == Attribute_kind){
    if(ret.length() > 0) ret = std::string(PyString_AS_STRING(name->v.Attribute.attr)) + "." + ret;
    else ret = std::string(PyString_AS_STRING(name->v.Attribute.attr));
    name = name->v.Attribute.value;
  }
  if(name->kind == Name_kind){
    if(ret.length() > 0) ret = "." + ret;
    ret = std::string(PyString_AS_STRING(name->v.Name.id)) + ret;
  }

  return ret;
}

vector<NodeId> ASTVisitor::visitStmtAsdl(asdl_seq* ch_list, NodeId docstring) {
  vector<NodeId> body;
  int i = 0;
  if (docstring) {
    i++;
  }

  if (ch_list != 0) {
    for (; i < (ch_list->size); i++) {
      body.push_back(visitStmt(static_cast<stmt_ty>(ch_list->elements[i])));
    }
  }
  return body;
}

vector<NodeId> ASTVisitor::visitExceptHandlerAsdl(asdl_seq* ch_list) {
  vector<NodeId> body;

  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
      body.push_back(visitExceptHandler(static_cast<excepthandler_ty>(ch_list->elements[i])));
    }
  }
  return body;
}

vector<NodeId> ASTVisitor::visitIdentifierAsdl(asdl_seq* ch_list) {
  vector<NodeId> body;

  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
      std::string str(PyString_AS_STRING(static_cast<identifier>(ch_list->elements[i])));
      global_list.back()->insert(str);
      body.push_back(pBuilder.buildIdentifier(str, 0));   // TODO:setPosition
    }
  }
  return body;
}

vector<NodeId> ASTVisitor::visitBaseSpecifierAsdl(asdl_seq* ch_list) {
  vector<NodeId> bases;

  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
      expr_ty expr = static_cast<expr_ty>(ch_list->elements[i]);

      std::string str("");
      NodeId name = 0;

      if (expr->kind == Name_kind) {
        name = visitExpr(expr);
        str = std::string(PyString_AS_STRING(expr->v.Name.id));
      } else if (expr->kind == Attribute_kind) {
        name = visitExpr(expr);
        str = std::string(PyString_AS_STRING(expr->v.Attribute.attr));  // should build the whole attributeref structure - if needed at all
      } else if (expr->kind == Call_kind) {
        name = visitExpr(expr);
        // finish edge
      } else {
        //FIXME if not name kind
      }

      NodeId bsnodeid = pBuilder.buildBaseSpecifier(name);
      pBuilder.setIncreasedPosition(bsnodeid, expr->lineno, expr->col_offset, expr->endline, expr->endcol);
      object_map[bsnodeid] = str;
      bases.push_back(bsnodeid);
    }
  }
  return bases;
}

vector<NodeId> ASTVisitor::visitExprAsdl(asdl_seq* ch_list) {
  vector<NodeId> body;

  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
      body.push_back(visitExpr(static_cast<expr_ty>(ch_list->elements[i])));
    }
  }
  return body;
}

NodeId ASTVisitor::createParamAndObject(std::string name, python::asg::ParameterKind kind, NodeId lastParam){
  NodeId objNid = pBuilder.buildObject(name);
  NodeId param = pBuilder.buildParameter(name, objNid, kind);

  //FIXME: its wrong if the parameters are not on the same line
  if (lastParam){
    base::Positioned& lastParamNode = static_cast<base::Positioned&>(pBuilder.getFactory()->getRef(lastParam));
    int col = lastParamNode.getPosition().getEndCol() + 2; // +2 for ", " between the parameters
    int endCol = col + name.length();
    pBuilder.setIncreasedPosition(param, lastParamNode.getPosition().getLine(), col, lastParamNode.getPosition().getEndLine(), endCol);
  }

  objects.back().first->insert( pair<std::string,NodeId>(name,objNid) );

  pBuilder.AddObjectRef(objNid, param);
  return param;
}

vector<NodeId> ASTVisitor::visitParameterListAsdl(arguments_ty arguments) {
  vector<NodeId> body;

  asdl_seq* ch_list = arguments->args;
  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
#ifdef PY3
      arg_ty arg = static_cast<arg_ty>(ch_list->elements[i]);
      std::string name = PyString_AS_STRING(arg->arg);

      NodeId param = createParamAndObject(name, pmkNormal);
      //pBuilder.setIncreasedPosition(param, arg->lineno, arg->col_offset, arg->endline, arg->endcol);
      // TODO endline and endcol for "arg" type
      pBuilder.setIncreasedPosition(param, arg->lineno, arg->col_offset, arg->lineno, arg->col_offset + name.size());
      body.push_back(param);
#else
      expr_ty expr = static_cast<expr_ty>(ch_list->elements[i]);
      std::string name = "";
      if (expr->kind == Name_kind){
        name = PyString_AS_STRING(expr->v.Name.id);
      } else {
        // FIXME if not a name
        // check ref 7.6. Function definitions
        // e.g. def comp_args((a, b)=(3, 4)):
      }

      NodeId param = createParamAndObject(name, pmkNormal);
      pBuilder.setIncreasedPosition(param, expr->lineno, expr->col_offset, expr->endline, expr->endcol);
      body.push_back(param);
#endif
    }
  }

  vector<NodeId>::iterator argItEnd = body.end();
  ch_list = arguments->defaults;
  if (ch_list != 0) {
    if (body.size() >= static_cast<size_t>(arguments->defaults->size)) {
      for (int i = static_cast<int>(ch_list->size) - 1; i >= 0; --i) {
        statement::Parameter& param = dynamic_cast<statement::Parameter&>(pBuilder.getFactory()->getRef(*(--argItEnd)));
        param.setDefaultValue(visitExpr(static_cast<expr_ty>(ch_list->elements[i])));
      }
    }
  }

#ifndef PY3
  NodeId lastParam = 0;
  if (!body.empty()){
    lastParam = body.back();
  }

  if (arguments->vararg){
    std::string varargName(PyString_AS_STRING(arguments->vararg));
    body.push_back(createParamAndObject(varargName, pmkVararg, lastParam));
    lastParam = body.back();
  }

  if(arguments->kwarg){
    std::string kwargName(PyString_AS_STRING(arguments->kwarg));
    body.push_back(createParamAndObject(kwargName, pmkKwarg, lastParam));
  }
#endif

  return body;
}

vector<NodeId> ASTVisitor::visitAliasAsdl(asdl_seq* ch_list, stmt_ty parent) {
  vector< NodeId > names;

  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
      alias_ty al = static_cast<alias_ty>(ch_list->elements[i]);
      std::string name(PyString_AS_STRING(al->name));
      std::string asname;
      if(al->asname != 0) asname = std::string(PyString_AS_STRING(al->asname));

      NodeId aliasId = pBuilder.buildAlias(name, asname);
      //FIXME: alias position
      pBuilder.setIncreasedPosition(aliasId, parent->lineno, parent->col_offset, parent->endline, parent->endcol);
      names.push_back(aliasId);
      object_map[aliasId] = name;
    }
  }
  return names;
}

vector< BinaryLogicalKind > ASTVisitor::visitCompAsdl(asdl_int_seq* ch_list){
  vector< BinaryLogicalKind > comp;

  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
      comp.push_back(comp_map[static_cast<cmpop_ty>(ch_list->elements[i])]);
    }
  }
  return comp;
}

vector<NodeId> ASTVisitor::visitKeywordAsdl(asdl_seq* ch_list) {
  vector<NodeId> body;

  if (ch_list != 0) {
    int previousKeyWordEndLine = 0;
    bool first = true;
    for (int i = 0; i < (ch_list->size); i++) {
      keyword_ty elem = static_cast<keyword_ty>(ch_list->elements[i]);
#ifdef PY3
      std::string name(elem->arg ? PyString_AS_STRING(elem->arg) : "");
#else
      std::string name(PyString_AS_STRING(elem->arg));
#endif
      NodeId identifier = pBuilder.buildIdentifier(name, 0);
      NodeId value = visitExpr(elem->value);
      NodeId keyw = pBuilder.buildKeyword(identifier, value);
      body.push_back(keyw);

      //FIXME: the positions are estimated and if the key and the value not on the same line they are totally wrong
      int keyWordStartLine;
      if (first){
        keyWordStartLine = elem->value->lineno;
      } else {
        keyWordStartLine = previousKeyWordEndLine +1;
      }
      int keyWordStartCol = elem->value->col_offset - (name.length() +1 ); // +1 for the "="
      pBuilder.setIncreasedPosition(identifier, keyWordStartLine, keyWordStartCol, elem->value->endline, elem->value->col_offset -1);
      pBuilder.setIncreasedPosition(keyw, keyWordStartLine, keyWordStartCol, elem->value->endline, elem->value->endcol);

      previousKeyWordEndLine = elem->value->endline;
      first = false;
    }
  }
  return body;
}

vector<NodeId> ASTVisitor::visitComprehensionAsdl(asdl_seq* ch_list){
  vector<NodeId> body;

  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
      comprehension_ty elem = static_cast<comprehension_ty>(ch_list->elements[i]);
      NodeId target = visitExpr(elem->target);

      NodeId iter = visitExpr(elem->iter);
      vector<NodeId> ifs;
      if(elem->ifs != 0){
        ifs = visitExprAsdl(elem->ifs);
      }

      int line = elem->target->lineno;
      int col = elem->target->col_offset - 4; // -4 for "for "
      int endLine = elem->iter->endline;
      int endCol = elem->iter->endcol;

      if (!ifs.empty()){
        base::Positioned& lastCond = static_cast<base::Positioned&>(pBuilder.getFactory()->getRef(ifs.back()));
        endLine = lastCond.getPosition().getEndLine();
        endCol = lastCond.getPosition().getEndCol();
      }

      NodeId gen = pBuilder.buildGenerator(target, iter, ifs);
      pBuilder.setIncreasedPosition(gen, line, col, endLine, endCol);

      body.push_back(gen);
    }
  }
  return body;
}

vector<NodeId> ASTVisitor::visitSliceAsdl(asdl_seq* ch_list) {
  vector<NodeId> body;

  if (ch_list != 0) {
    for (int i = 0; i < (ch_list->size); i++) {
      body.push_back(visitSlice(static_cast<slice_ty>(ch_list->elements[i])));
    }
  }
  return body;
}

void ASTVisitor::buildLocalObjects() {
  for(std::multimap<std::string, NodeId>::iterator it = temp_objects.back()->begin(); it != temp_objects.back()->end(); ++it) {
    std::string name = (*it).first;
    std::map<std::string, NodeId>::iterator result = objects.back().first->find(name);
    if (result == objects.back().first->end() &&
      global_list.back()->find(name) == global_list.back()->end()) {   //id not in local list, nor in global, create local object

        NodeId objNid = pBuilder.buildObject(name);
        objects.back().first->insert(pair<std::string, NodeId>(name, objNid));
        static_cast<expression::Identifier&>(pBuilder.getFactory()->getRef((*it).second)).setRefersTo(objNid);
        pBuilder.AddObjectRef(objNid, (*it).second);
    } else if (global_list.back()->find(name) != global_list.back()->end()) {    // id in global list
      std::map<std::string, NodeId>::iterator global_result = objects.front().first->find(name);
      if (global_result == objects.front().first->end()) {    // no actual global obj found, create global object
        NodeId objNid = pBuilder.buildObject(name);
        objects.front().first->insert(pair<std::string, NodeId>(name, objNid));
        static_cast<expression::Identifier&>(pBuilder.getFactory()->getRef((*it).second)).setRefersTo(objNid);
        pBuilder.AddObjectRef(objNid, (*it).second);
      } else {
        // setRef id to module obj
        static_cast<expression::Identifier&>(pBuilder.getFactory()->getRef((*it).second)).setRefersTo((*global_result).second);
        std::map<NodeId, bool>::iterator reverse_edge = reverse_edge_objects.front()->find((*it).second);
        if (reverse_edge != reverse_edge_objects.front()->end()) {
          if ((*reverse_edge).second) {
            pBuilder.AddObjectRef((*global_result).second, (*it).second);
          }
        }
      }
    } else if (result != objects.back().first->end()) {   // already existing local object, no global keyword
      static_cast<expression::Identifier&>(pBuilder.getFactory()->getRef((*it).second)).setRefersTo((*result).second);
      std::map<NodeId, bool>::iterator reverse_edge = reverse_edge_objects.back()->find((*it).second);
      if (reverse_edge != reverse_edge_objects.back()->end()) {
        if ((*reverse_edge).second) {
          pBuilder.AddObjectRef((*result).second, (*it).second);
        }
      }
    }
  }
}

Factory* ASTVisitor::Visit(std::string path_name, std::string modul_name, mod_ty root, vector<int>& llines,  map<int, NodeId>& commentMap) {

  path = modul_name;
  logical_lines = llines;
  pBuilder.setPath(path_name);
  commentHolderCandidates.clear();

  size_t start = modul_name.find_last_of("/\\");
  size_t end = modul_name.find_last_of(".");
  std::string name = modul_name.substr(start+1, end-start-1);
  NodeId module = visitMod(name, root);
  // if the last lines only has comments, than attach them to the module node
  getOuterNodeInLine(module, static_cast<base::Positioned&>(pBuilder.getFactory()->getRef(module)).getPosition().getEndLine() + 1);
  vector<NodeId> body;
  NodeId package = pBuilder.buildPackage(modul_name, body);

  pBuilder.AddModule(module, package);

  for (std::map<int, NodeId>::iterator commentIt = commentMap.begin(); commentIt != commentMap.end(); ++commentIt){
    int line = commentIt->first;
    while(true){
      std::map<int, NodeId>::iterator candidate;
      if ( ( candidate = commentHolderCandidates.find(line) ) == commentHolderCandidates.end()){
        ++line;
      } else {
        base::Positioned& pos = dynamic_cast<base::Positioned&>(pBuilder.getFactory()->getRef(candidate->second));
        pos.addComments(commentIt->second);
        break;
      }
    }
  }

  return pBuilder.getFactory();
}

NodeId ASTVisitor::visitMod(std::string modul_name, mod_ty parent) {
  asdl_seq * ch_list;

  NodeId parentNid = 0;

  switch (parent->kind) {
  case Module_kind:
    {
      std::map<std::string, NodeId> local_objects;
      std::set<std::string> local_globals;

      objects.push_back( pair<std::map<std::string, NodeId>*, NodeKind>(&local_objects, ndkModule));
      global_list.push_back(&local_globals);

      ch_list = parent->v.Module.body;

      int realEndline = logical_lines.back();
      logical_lines.pop_back();

      NodeId docstring = getDocstring(ch_list);
      vector<NodeId> body = visitStmtAsdl(ch_list, docstring); // if the module has docstring, than don't need to build the first stringliteral

      std::vector<NodeId> object;
      for(std::map<std::string, NodeId>::iterator it = local_objects.begin(); it != local_objects.end(); ++it){
        object.push_back((*it).second);
      }

      int lloc = 0, endline = 1, endcol = 1, docSize = 0;

      if (!body.empty()) {
        base::Positioned& last = static_cast<base::Positioned&>(pBuilder.getFactory()->getRef(body.back()));
        endline = last.getPosition().getEndLine();
        endcol = last.getPosition().getEndCol();
      }

      if (docstring){
        base::Docstring& doc = static_cast<base::Docstring&>(pBuilder.getFactory()->getRef(docstring));
        docSize = doc.getPosition().getEndLine() - doc.getPosition().getLine() + 1;

        if (body.empty()){ // if the module only has a docstring, than the module's end position same as the docstring's end position
          endline = doc.getPosition().getEndLine();
          endcol = doc.getPosition().getEndCol();
        }
      }

      if (realEndline > endline) {
        endline = realEndline;
        endcol = 1;
      }

      lloc = getLLOC(1, endline, logical_lines) - docSize;
      parentNid = pBuilder.buildModule(modul_name, docstring, body, object, lloc );
      pBuilder.setPosition(parentNid, 1, 1, endline, endcol);

      objects.pop_back();
      global_list.pop_back();
    }
    break;
  case Interactive_kind:
  case Expression_kind:
  case Suite_kind:
  default:
    break; 
  }

  return parentNid;
}

NodeId ASTVisitor::visitExceptHandler(excepthandler_ty parent) {
  NodeId parentNid = 0;
  asdl_seq * ch_list;

  switch (parent->kind) {
  case ExceptHandler_kind:
    {
      ch_list = parent->v.ExceptHandler.body;
      vector<NodeId> body = visitStmtAsdl(ch_list);
      NodeId suiteNid = pBuilder.buildSuite(body);
      NodeId name = 0;

      if (parent->v.ExceptHandler.name != 0) {
#ifdef PY3
        std::string str(PyString_AS_STRING(parent->v.ExceptHandler.name));
        name = pBuilder.buildIdentifier(str, 0);
#else
        name = visitExpr(parent->v.ExceptHandler.name);
#endif
      }

      NodeId type = visitExpr(parent->v.ExceptHandler.type);

      parentNid = pBuilder.buildHandler(type, name, suiteNid);

      statement::Statement& last = static_cast<statement::Statement&>(pBuilder.getFactory()->getRef(body.back()));
      unsigned endline = last.getPosition().getEndLine();
      unsigned endcol = last.getPosition().getEndCol();
      pBuilder.setIncreasedPosition(parentNid, parent->lineno, parent->col_offset, endline, endcol);
    }
  }


  return parentNid;
}


NodeId ASTVisitor::visitStmt(stmt_ty parent) {
  asdl_seq * ch_list;
  NodeId parentNid = 0;

  if (parent == 0) {
    return parentNid;
  }

  EXCEPTION_LOC_BEGIN

    switch (parent->kind) {
    case FunctionDef_kind: 
      {
        std::map<std::string, NodeId> local_objects;
        std::set<std::string> local_globals;
        std::map<NodeId, bool> local_build_objects;
        std::multimap<std::string, NodeId> temp_local_objects;
        vector<NodeId> decorator_list;

        objects.push_back(pair<std::map<std::string, NodeId>*, NodeKind>(&local_objects, ndkFunctionDef));
        temp_objects.push_back(&temp_local_objects);
        global_list.push_back(&local_globals);
        reverse_edge_objects.push_back(&local_build_objects);

        NodeId suiteNid = 0;
        std::string str;

        arguments_ty temp = parent->v.FunctionDef.args;
        vector<NodeId> args;
        if (temp != 0) {
          args = visitParameterListAsdl(temp);
        }

        ch_list = parent->v.FunctionDef.body;
        bool prev_state = collect_objects;
        collect_objects = true;

        NodeId docstring = getDocstring(ch_list);
        vector<NodeId> body = visitStmtAsdl(ch_list, docstring);
        collect_objects = prev_state;
        suiteNid = pBuilder.buildSuite(body);

        identifier tempx = parent->v.FunctionDef.name;
        if (tempx != 0) {
          str.assign(PyString_AS_STRING(tempx));
        }

        ch_list = parent->v.FunctionDef.decorator_list;
        if (ch_list != 0) {
          decorator_list = visitExprAsdl(parent->v.FunctionDef.decorator_list);
        }

        buildLocalObjects();

        std::vector<NodeId> object;
        for(std::map<std::string, NodeId>::iterator it = local_objects.begin(); it != local_objects.end(); ++it){
          object.push_back((*it).second);
        }

        objects.pop_back();
        temp_objects.pop_back();
        global_list.pop_back();
        reverse_edge_objects.pop_back();

        NodeId objNid = 0;
        if( objects.back().first->find(str) == objects.back().first->end() ){
          objNid = pBuilder.buildObject(str);
          objects.back().first->insert( pair<std::string,NodeId>(str,objNid) );
        }else{
          std::map<std::string, NodeId>::iterator it = objects.back().first->find(str);
          objNid = (*it).second;
        }

        parentNid = pBuilder.buildFunctionDef(str, docstring, suiteNid, args, decorator_list, object, objNid, 0);
        pBuilder.AddObjectRef(objNid, parentNid);
      }
      break;
    case ClassDef_kind:
      {
        vector<NodeId> decorator_list;
        std::map<std::string, NodeId> local_objects;
        std::set<std::string> local_globals;
        std::map<NodeId, bool> local_build_objects;
        std::multimap<std::string, NodeId> temp_local_objects;

        objects.push_back(pair<std::map<std::string, NodeId>*, NodeKind>(&local_objects, ndkClassDef));
        temp_objects.push_back(&temp_local_objects);
        global_list.push_back(&local_globals);
        reverse_edge_objects.push_back(&local_build_objects);

        ch_list = parent->v.ClassDef.body;
        bool prev_state = collect_objects;
        collect_objects = true;

        NodeId docstring = getDocstring(ch_list);
        vector<NodeId> body = visitStmtAsdl(ch_list, docstring);
        collect_objects = prev_state;
        NodeId suiteNid = pBuilder.buildSuite(body);

        vector<NodeId> bases;
        if(parent->v.ClassDef.bases != 0) {
          bases = visitBaseSpecifierAsdl(parent->v.ClassDef.bases);
        }

        std::string name(PyString_AS_STRING(parent->v.ClassDef.name));

        ch_list = parent->v.ClassDef.decorator_list;
        if (ch_list != 0) {
          decorator_list = visitExprAsdl(parent->v.ClassDef.decorator_list);
        }

        buildLocalObjects();

        std::vector<NodeId> object;
        for(std::map<std::string, NodeId>::iterator it = local_objects.begin(); it != local_objects.end(); ++it){
          object.push_back((*it).second);
        }

        objects.pop_back();
        temp_objects.pop_back();
        global_list.pop_back();
        reverse_edge_objects.pop_back();

        NodeId objNid = 0;
        if( objects.back().first->find(name) == objects.back().first->end() ){
          objNid = pBuilder.buildObject(name);
          objects.back().first->insert( pair<std::string,NodeId>(name,objNid) );
        }else{
          std::map<std::string, NodeId>::iterator it = objects.back().first->find(name);
          objNid = (*it).second;
        }

        parentNid = pBuilder.buildClassDef(name, docstring, suiteNid, bases, decorator_list, object, objNid, 0 );
        pBuilder.AddObjectRef(objNid, parentNid);
      }
      break;
    case Return_kind:
      {
        NodeId exp = 0;
        if (parent->v.Return.value) {
          exp = visitExpr(parent->v.Return.value);
        }
        parentNid = pBuilder.buildReturn(exp);
      }
      break;
    case Delete_kind:
      {
        vector<NodeId> list = visitExprAsdl(parent->v.Delete.targets);
        NodeId tglist = pBuilder.buildTargetList(list);

        parentNid = pBuilder.buildDelete(tglist);
      }
      break;
    case Assign_kind:
      {
        bool prev_state = build_object;
        build_object = true;
        vector<NodeId> list = visitExprAsdl(parent->v.Assign.targets);
        NodeId tglist = pBuilder.buildTargetList(list);

        build_object = false;

        bool prev_collect_state = collect_objects;
        collect_objects = false;
        NodeId value = visitExpr(parent->v.Assign.value);
        parentNid = pBuilder.buildAssign(tglist, value);

        collect_objects = prev_collect_state;
        build_object = prev_state;
      }
      break;
    case AugAssign_kind:
      {
        NodeId target = visitExpr(parent->v.AugAssign.target);
        vector<NodeId> list;
        list.push_back(target);
        NodeId tglist = pBuilder.buildTargetList(list);
        NodeId value = visitExpr(parent->v.AugAssign.value);

        parentNid = pBuilder.buildAugAssign(tglist, value, assignment_map[parent->v.AugAssign.op]);
      }
      break;
#ifndef PY3
    case Print_kind:
      {
        ch_list = parent->v.Print.values;
        NodeId dest = visitExpr(parent->v.Print.dest);
        vector<NodeId> args = visitExprAsdl(ch_list);
        NodeId expl = pBuilder.buildExpressionList(args, false);

        parentNid = pBuilder.buildPrint(parent->v.Print.nl, dest, expl);
      }
      break;
#endif
    case For_kind:
      {
        bool prev_state = build_object;
        build_object = false;

        ch_list = parent->v.For.body;
        vector<NodeId> bodyl = visitStmtAsdl(ch_list);
        NodeId body = pBuilder.buildSuite(bodyl);

        ch_list = parent->v.For.orelse;
        NodeId elsebody = 0;
        if(ch_list != 0){
          vector<NodeId> elsebodyl = visitStmtAsdl(ch_list);
          elsebody = pBuilder.buildSuite(elsebodyl);
        }

        build_object = true;
        NodeId target = visitExpr(parent->v.For.target);
        build_object = false;
        vector<NodeId> target_list;
        target_list.push_back(target);
        NodeId targetl = pBuilder.buildTargetList(target_list);

        NodeId expression = visitExpr(parent->v.For.iter);
        vector<NodeId> expression_list;
        expression_list.push_back(expression);
        NodeId expressionl = pBuilder.buildExpressionList(expression_list, false);

        parentNid = pBuilder.buildFor(targetl, body, elsebody, expressionl);

        build_object = prev_state;
      }
      break;
    case While_kind:
      {
        ch_list = parent->v.While.body;
        vector<NodeId> bodyl = visitStmtAsdl(ch_list);
        NodeId body = pBuilder.buildSuite(bodyl);

        ch_list = parent->v.While.orelse;
        NodeId elsebody = 0;
        if(ch_list != 0){
          vector<NodeId> elsebodyl = visitStmtAsdl(ch_list);
          elsebody = pBuilder.buildSuite(elsebodyl);
        }

        NodeId expression = visitExpr(parent->v.While.test);

        parentNid = pBuilder.buildWhile(expression, body, elsebody);
      }
      break;
    case If_kind:
      {
        ch_list = parent->v.If.body;
        vector<NodeId> bodyl = visitStmtAsdl(ch_list);
        NodeId body = pBuilder.buildSuite(bodyl);

        ch_list = parent->v.If.orelse;
        NodeId elsebody = 0;
        if(ch_list != 0){
          vector<NodeId> elsebodyl = visitStmtAsdl(ch_list);
          elsebody = pBuilder.buildSuite(elsebodyl);
        }

        NodeId expression = visitExpr(parent->v.If.test);

        parentNid = pBuilder.buildIf(expression, body, elsebody);
      }
      break;
    case With_kind:
      {
        NodeId body = 0;
        ch_list = parent->v.With.body;
        if(ch_list != 0) {
          vector<NodeId> bodyl = visitStmtAsdl(ch_list);
          body = pBuilder.buildSuite(bodyl);
        }

#ifdef PY3
        NodeId context_expr = 0;
        NodeId optional_vars = 0;
#else
        NodeId context_expr = visitExpr(parent->v.With.context_expr);
        NodeId optional_vars = visitExpr(parent->v.With.optional_vars);
#endif

        parentNid = pBuilder.buildWith(body, optional_vars, context_expr);

      }
      break;
    case Raise_kind:
      {
#ifdef PY3
        NodeId type = 0;
        NodeId traceback = 0;
        NodeId value = 0;
#else
        NodeId type = visitExpr(parent->v.Raise.type);
        NodeId traceback = visitExpr(parent->v.Raise.tback);
        NodeId value = visitExpr(parent->v.Raise.inst);
#endif
        parentNid = pBuilder.buildRaise(type, value, traceback);
      }
      break;
#ifdef PY3
    case Try_kind:
      {
        NodeId body = 0, orelse = 0;
        vector<NodeId> handlerl;

        ch_list = parent->v.Try.body;
        if (ch_list != 0) {
          vector<NodeId> bodyl = visitStmtAsdl(ch_list);
          body = pBuilder.buildSuite(bodyl);
        }

        ch_list = parent->v.Try.handlers;
        if (ch_list != 0) {
          handlerl = visitExceptHandlerAsdl(ch_list);
        }

        ch_list = parent->v.Try.orelse;
        if (ch_list != 0) {
          vector<NodeId> orelsel = visitStmtAsdl(ch_list);
          orelse = pBuilder.buildSuite(orelsel);
        }

        parentNid = pBuilder.buildTryExcept(handlerl, body, orelse);
      }
      break;
#else
    case TryExcept_kind:
      {
        NodeId body = 0, orelse = 0;
        vector<NodeId> handlerl;

        ch_list = parent->v.TryExcept.body;
        if(ch_list != 0) {
          vector<NodeId> bodyl = visitStmtAsdl(ch_list);
          body = pBuilder.buildSuite(bodyl);
        } 

        ch_list = parent->v.TryExcept.handlers;
        if(ch_list != 0) {
          handlerl = visitExceptHandlerAsdl(ch_list);
        }

        ch_list = parent->v.TryExcept.orelse;

        if(ch_list != 0) {
          vector<NodeId> orelsel = visitStmtAsdl(ch_list);
          orelse = pBuilder.buildSuite(orelsel);
        }


        parentNid = pBuilder.buildTryExcept(handlerl, body, orelse);
      }
      break;
    case TryFinally_kind:
      {
        NodeId body = 0, finally_body = 0;
        ch_list = parent->v.TryFinally.body;
        if(ch_list != 0) {
          vector<NodeId> bodyl = visitStmtAsdl(ch_list);
          body = pBuilder.buildSuite(bodyl);
        } 

        ch_list = parent->v.TryFinally.finalbody;
        if(ch_list != 0) {
          vector<NodeId> finally_bodyl = visitStmtAsdl(ch_list);
          finally_body = pBuilder.buildSuite(finally_bodyl);
        }

        parentNid = pBuilder.buildTryFinal(body, finally_body);

      }
      break;
#endif
    case Assert_kind:
      {
        NodeId message = visitExpr(parent->v.Assert.msg);
        NodeId test = visitExpr(parent->v.Assert.test);

        parentNid = pBuilder.buildAssert(test, message);
      }
      break;
    case Import_kind:
      {
        vector< NodeId > names = visitAliasAsdl(parent->v.Import.names, parent);
        parentNid = pBuilder.buildImportStatement(names);
      }
      break;
    case ImportFrom_kind:
      {
        vector< NodeId > names = visitAliasAsdl(parent->v.ImportFrom.names, parent);

        int level = parent->v.ImportFrom.level;
        std::string modulename = "";
        if (parent->v.ImportFrom.module)
          modulename = PyString_AS_STRING(parent->v.ImportFrom.module);
        parentNid = pBuilder.buildImportFrom(names, modulename, level);
      }
      break;
#ifndef PY3
    case Exec_kind:
      {
        NodeId body = visitExpr(parent->v.Exec.body);
        NodeId globals = visitExpr(parent->v.Exec.globals);
        NodeId locals = visitExpr(parent->v.Exec.locals);
        parentNid = pBuilder.buildExec(body, globals, locals);
      }
      break;
#endif
    case Global_kind:
      {
        ch_list = parent->v.Global.names;
        vector<NodeId> args = visitIdentifierAsdl(ch_list);

        //fixme: better solution?
        int offset = parent->col_offset + 7; // +7 for: "global "
        for (vector<NodeId>::iterator beginIt = args.begin(); beginIt != args.end(); ++beginIt){
          expression::Identifier& id = dynamic_cast<expression::Identifier&>(pBuilder.getFactory()->getRef(*beginIt));
          int nameSize = id.getName().size();
          pBuilder.setIncreasedPosition(id.getId(), parent->lineno, offset, parent->lineno, offset + nameSize);
          offset += nameSize + 2; // +2 for: ", "
        }

        parentNid = pBuilder.buildGlobal(args);
      }
      break;
    case Expr_kind:
      {
        parentNid = visitExpr(parent->v.Expr.value);
      }
      break;
    case Pass_kind:
      {
        parentNid = pBuilder.buildPass();
      }
      break;
    case Break_kind:
      {
        parentNid = pBuilder.buildBreak();
      }
      break;
    case Continue_kind:
      {
        parentNid = pBuilder.buildContinue();
      }
      break;
#ifdef PY3
    default:
      parentNid = pBuilder.buildPass();
      break;
#endif
  }

  int endLine = parent->endline;
  int endCol = parent->endcol;

  statement::Suite* body = 0;
  base::Base& node = pBuilder.getFactory()->getRef(parentNid);

  if (Common::getIsClassDef(node)){
    statement::ClassDef& stm = static_cast<statement::ClassDef&>(node);
    body = stm.getBody();
    int defEndLine = 0, defEndCol = 0;
    if (body->getStatementIsEmpty()){
      if (stm.getDocstring()){ // if the body is empty bot the definition has a docstring
        defEndLine = stm.getDocstring()->getPosition().getEndLine();
        defEndCol = stm.getDocstring()->getPosition().getEndCol();
      }
    } else {
        defEndLine = body->getPosition().getEndLine();
        defEndCol = body->getPosition().getEndCol();
    }
    pBuilder.setIncreasedPosition(parentNid, parent->lineno, parent->col_offset, defEndLine, defEndCol);
  } else if (Common::getIsFunctionDef(node) ){
    statement::FunctionDef& stm = static_cast<statement::FunctionDef&>(node);
    body = stm.getBody();
    int defEndLine = 0, defEndCol = 0;
    if (body->getStatementIsEmpty()){
      if (stm.getDocstring()){ // if the body is empty bot the definition has a docstring
        defEndLine = stm.getDocstring()->getPosition().getEndLine();
        defEndCol = stm.getDocstring()->getPosition().getEndCol();
      }
    } else {
        defEndLine = body->getPosition().getEndLine();
        defEndCol = body->getPosition().getEndCol();
    }
    pBuilder.setIncreasedPosition(parentNid, parent->lineno, parent->col_offset, defEndLine, defEndCol);
  } else {
    if ( Common::getIsWith(node)){
      statement::CompoundStatement& stm = static_cast<statement::CompoundStatement&>(node);
      body = stm.getBody();
    }

    if (Common::getIsIf(node)){
      statement::If& ifStm = static_cast<statement::If&>(node);
      if (ifStm.getElseBody()){
        body = ifStm.getElseBody();
      } else {
        body = ifStm.getBody();
      }
    }

    if (Common::getIsIteration(node)){
      statement::Iteration& iterStm = static_cast<statement::Iteration&>(node);
      if (iterStm.getElseBody()){
        body = iterStm.getElseBody();
      } else {
        body = iterStm.getBody();
      }
    }

    if (Common::getIsTryFinal(node)){
      statement::TryFinal& tryFinal = static_cast<statement::TryFinal&>(node);
      body = tryFinal.getFinallyBody();
    }

    if (Common::getIsTryExcept(node)){
      statement::TryExcept& tryExcept = static_cast<statement::TryExcept&>(node);
      if (tryExcept.getFinallyBody()) {
        body = tryExcept.getFinallyBody();
      } else if (tryExcept.getElseBody()) {
        body = tryExcept.getElseBody();
      } else if (!tryExcept.getHandlerIsEmpty()) {
        python::asg::ListIterator<python::asg::statement::Handler> handlerItEnd = tryExcept.getHandlerListIteratorEnd();
        --handlerItEnd;
        body = handlerItEnd->getExceptBody();
      }
    }

    if (body){
      endLine = body->getPosition().getEndLine();
      endCol = body->getPosition().getEndCol();
    }

    pBuilder.setIncreasedPosition(parentNid, parent->lineno, parent->col_offset, endLine, endCol);
  }

  if (Common::getIsFunctionDef(node)){
    statement::FunctionDef& func = static_cast<statement::FunctionDef&>(node);
    int docLength = 0;
    if (func.getDocstring()){
      base::Docstring& doc = *func.getDocstring();
      docLength = doc.getPosition().getEndLine()-doc.getPosition().getLine()+1;
    }
    func.setLloc(getLLOC(func.getPosition().getLine(), func.getPosition().getEndLine(), logical_lines) - docLength);
  }

  if (Common::getIsClassDef(node)){
    statement::ClassDef& cls = static_cast<statement::ClassDef&>(node);
    int docLength = 0;
    if (cls.getDocstring()){
      base::Docstring& doc = *cls.getDocstring();
      docLength = doc.getPosition().getEndLine()-doc.getPosition().getLine()+1;
    }
    cls.setLloc(getLLOC(cls.getPosition().getLine(), cls.getPosition().getEndLine(), logical_lines) - docLength);
  }

  getOuterNodeInLine(parentNid);

  EXCEPTION_LOC_END("ASTVisitor::visitStmt()")

    return parentNid;
}

NodeId ASTVisitor::visitExpr(expr_ty parent) {
  NodeId parentNid = 0;

  if (parent == 0) {
    return parentNid;
  }

  EXCEPTION_LOC_BEGIN

    switch (parent->kind) {
    case BoolOp_kind:
      {
        vector<NodeId> values = visitExprAsdl(parent->v.BoolOp.values);

        parentNid = pBuilder.buildBinaryLogical(values, boolop_map[parent->v.BoolOp.op]);
      }
      break;
    case BinOp_kind:
      {
        NodeId left = visitExpr(parent->v.BinOp.left);
        NodeId right = visitExpr(parent->v.BinOp.right);

        parentNid = pBuilder.buildBinaryArithmetic(left, right, arithmetic_map[parent->v.BinOp.op]);
      }
      break;
    case UnaryOp_kind:
      {
        NodeId operand = visitExpr(parent->v.UnaryOp.operand);

        parentNid = pBuilder.buildUnaryOperation(operand, unary_map[parent->v.UnaryOp.op]);
      }
      break;
    case Lambda_kind:
      {
        std::map<std::string, NodeId> local_objects;
        objects.push_back( pair<std::map<std::string, NodeId>*, NodeKind>(&local_objects, ndkLambda));

        vector<NodeId> args = visitParameterListAsdl(parent->v.Lambda.args);

        NodeId body = visitExpr(parent->v.Lambda.body);

        std::map<std::string, NodeId>* lastMap = objects.back().first;

        vector<NodeId> lambda_object_list;
        for (vector<NodeId>::iterator argsBegin = args.begin() ; argsBegin != args.end(); ++argsBegin){
          std::string paramName = dynamic_cast<statement::Parameter&>(pBuilder.getFactory()->getRef(*argsBegin)).getName();
          lambda_object_list.push_back(lastMap->find(paramName)->second);
        }
        objects.pop_back();
        parentNid = pBuilder.buildLambda(args, lambda_object_list, body);
      }
      break;
    case IfExp_kind:
      {
        NodeId test = visitExpr(parent->v.IfExp.test);
        NodeId body = visitExpr(parent->v.IfExp.body);
        NodeId elsebody = visitExpr(parent->v.IfExp.orelse);

        parentNid = pBuilder.buildIfExpression(test, body, elsebody);
      }
      break;
    case Dict_kind:
      {
        vector<NodeId> keys = visitExprAsdl(parent->v.Dict.keys);
        vector<NodeId> values = visitExprAsdl(parent->v.Dict.values);
        vector<NodeId> key_list;
        if(keys.size() == values.size()){
          vector<NodeId>::iterator keysit = keys.begin();
          vector<NodeId>::iterator valuesit = values.begin();
          while(keysit != keys.end() && valuesit != values.end()){
            key_list.push_back(pBuilder.buildKeyValue(*keysit, *valuesit));
            keysit++;
            valuesit++;
          }
        }
        parentNid = pBuilder.buildDictionary(key_list);
      }
      break;
    case Set_kind: // python 2.7 feature
      {
        vector<NodeId> args = visitExprAsdl(parent->v.Set.elts);
        parentNid = pBuilder.buildSet(args);
      }
      break;
    case ListComp_kind:
      {
        NodeId elt = visitExpr(parent->v.ListComp.elt);
        vector<NodeId> generators = visitComprehensionAsdl(parent->v.ListComp.generators);

        parentNid = pBuilder.buildListComp(elt, generators);
      }
      break;
    case SetComp_kind: // python 2.7 feature
      {
        NodeId elt = visitExpr(parent->v.SetComp.elt);
        vector<NodeId> generators = visitComprehensionAsdl(parent->v.SetComp.generators);

        parentNid = pBuilder.buildSetComp(elt, generators);
      }
      break;
    case DictComp_kind: // python 2.7 feature
      {
        NodeId key = visitExpr(parent->v.DictComp.key);
        NodeId value = visitExpr(parent->v.DictComp.value);
        vector<NodeId> key_list;
        NodeId keyValue = pBuilder.buildKeyValue(key, value);
        vector<NodeId> generators = visitComprehensionAsdl(parent->v.DictComp.generators);

        parentNid = pBuilder.buildDictComp(keyValue, generators);
      }
      break;
    case GeneratorExp_kind:
      {
        NodeId elt = visitExpr(parent->v.GeneratorExp.elt);
        vector<NodeId> generators = visitComprehensionAsdl(parent->v.GeneratorExp.generators);

        parentNid = pBuilder.buildGeneratorExpression(elt, generators);
      }
      break;
    case Yield_kind:
      {
        vector<NodeId> list;
        if (parent->v.Yield.value) {
          NodeId value = visitExpr(parent->v.Yield.value);
          list.push_back(value);
        }
        NodeId exprl = pBuilder.buildExpressionList(list, true);
        parentNid = pBuilder.buildYield(exprl);
      }
      break;
    case Compare_kind:
      {
        NodeId left = visitExpr(parent->v.Compare.left);
        vector<BinaryLogicalKind> ops = visitCompAsdl(parent->v.Compare.ops);
        vector<NodeId> operands = visitExprAsdl(parent->v.Compare.comparators);

        parentNid = pBuilder.buildCompare(left, operands, ops);
      }
      break;
    case Call_kind:
      {
        bool prev_state = collect_objects;
        collect_objects = false;
        NodeId func = visitExpr(parent->v.Call.func);
        collect_objects = prev_state;

        vector<NodeId> args = visitExprAsdl(parent->v.Call.args);

        NodeId arguments = 0;
        if(!args.empty()) arguments = pBuilder.buildExpressionList(args, false);

        vector<NodeId> keys = visitKeywordAsdl(parent->v.Call.keywords);

        NodeId starargs = 0;
        NodeId kwargs = 0;

        unsigned line = 0, endline = 0, col = 0, endcol = 0;

        line = parent->lineno; col = parent->col_offset;
        endline = parent->endline; endcol = parent->endcol;

#ifndef PY3
        if(parent->v.Call.starargs != 0) {
          starargs = visitExpr(parent->v.Call.starargs);
          line = parent->v.Call.starargs->lineno; col = parent->v.Call.starargs->col_offset;
          endline = parent->v.Call.starargs->endline; endcol = parent->v.Call.starargs->endcol;
        }
        if(parent->v.Call.kwargs != 0) {
          kwargs = visitExpr(parent->v.Call.kwargs);
          line = parent->v.Call.kwargs->lineno; col = parent->v.Call.kwargs->col_offset;
          endline = parent->v.Call.kwargs->endline; endcol = parent->v.Call.kwargs->endcol;
        }

        if (parent->v.Call.kwargs != 0 && parent->v.Call.starargs != 0) {
          line = parent->v.Call.starargs->lineno; col = parent->v.Call.starargs->col_offset;
          endline = parent->v.Call.kwargs->endline; endcol = parent->v.Call.kwargs->endcol;
        }
#endif

        unsigned arglist_line = line, arglist_endline = endline, arglist_col = col, arglist_endcol = endcol;

        if (!keys.empty()){
          expression::Keyword& firstKey = dynamic_cast<expression::Keyword&>(pBuilder.getFactory()->getRef(*(keys.begin())));
          expression::Keyword& lastKey = dynamic_cast<expression::Keyword&>(pBuilder.getFactory()->getRef(keys.back()));
          arglist_line = firstKey.getPosition().getLine();
          arglist_col = firstKey.getPosition().getCol();
          arglist_endline = lastKey.getPosition().getEndLine();
          arglist_endcol = lastKey.getPosition().getEndCol();
        }

        if (arguments){
          expression::Expression& argList = dynamic_cast<expression::Expression&>(pBuilder.getFactory()->getRef(arguments));
          arglist_line = argList.getPosition().getLine();
          arglist_col = argList.getPosition().getCol();
          arglist_endline = argList.getPosition().getEndLine();
          arglist_endcol = argList.getPosition().getEndCol();
        }

        NodeId argument_list = pBuilder.buildArgumentList(arguments, keys, kwargs, starargs);
        pBuilder.setPosition(argument_list, arglist_line, arglist_col, arglist_endline, arglist_endcol);

        parentNid = pBuilder.buildCall(argument_list, func);
      }
      break;
#ifndef PY3
    case Repr_kind:
      {
        // built-in function for string representation of an object
        NodeId value = visitExpr(parent->v.Repr.value);
        vector<NodeId> list;
        list.push_back(value);
        NodeId exprl = pBuilder.buildExpressionList(list, true);  //TODO:why exprlist? yield?

        parentNid = pBuilder.buildStringConversion(exprl);
      }
      break;
#endif
    case Num_kind:
      {
        if(PyFloat_Check(parent->v.Num.n)){
          float x = static_cast<float>(PyFloat_AS_DOUBLE(parent->v.Num.n));
          parentNid = pBuilder.buildFloatNumber(x);
        }else if(PyComplex_Check(parent->v.Num.n)){
          Py_complex z;
          z = PyComplex_AsCComplex(parent->v.Num.n);
          parentNid = pBuilder.buildImagNumber(z.imag, z.real);
        }else{
          int x = static_cast<int>(PyLong_AsLongLong(parent->v.Num.n)); // TODO signed/unsigned int/long/long long
          parentNid = pBuilder.buildIntegerLiteral(x);
        }
      }
      break;
    case Str_kind:
      {
        std::string str;
#ifdef PY3
        // TODO unicodes
        // it fails for e.g. "\uDC80", "\N{EMPTY SET}"
        const char *s = PyString_AS_STRING(parent->v.Str.s);
        if (s)
          str = std::string(s);
#else
        std::string type(parent->v.Str.s->ob_type->tp_name);
        if(type.compare("unicode") == 0)
          str = std::string(PyString_AS_STRING(PyUnicode_AsUTF8String(parent->v.Str.s)));
        else if(type.compare("str") == 0)
          str = std::string(PyString_AS_STRING(parent->v.Str.s));
#endif

        parentNid = pBuilder.buildStringLiteral(str);
      }
      break;
    case Attribute_kind:
      {
        NodeId primary = visitExpr(parent->v.Attribute.value);
        std::string str(PyString_AS_STRING(parent->v.Attribute.attr));
        NodeId identifier = pBuilder.buildIdentifier(str, 0);
        //FIXME: hacked
        int primaryStartCol = parent->v.Attribute.value->col_offset;
        pBuilder.setIncreasedPosition(identifier, parent->lineno, primaryStartCol + 1, parent->endline, parent->endcol); // +1 for the "."

        parentNid = pBuilder.buildAttributeRef(identifier, primary);
      }
      break;
    case Subscript_kind:
      {
        NodeId sliceNid = visitSlice(parent->v.Subscript.slice);
        NodeId value = visitExpr(parent->v.Subscript.value);
        parentNid = pBuilder.buildSubscription(sliceNid, value);
      }
      break;   
    case Name_kind:
      {
        std::string str(PyString_AS_STRING(parent->v.Name.id));

        NodeId objNid = 0;

        if (collect_objects) {
          parentNid = pBuilder.buildIdentifier(str, objNid);
          temp_objects.back()->insert(pair<std::string, NodeId>(str, parentNid));
          reverse_edge_objects.back()->insert(pair<NodeId, bool>(parentNid, build_object));
        } else {
          bool foundObject = false;
          std::list< std::pair< std::map<std::string, NodeId>* , NodeKind > >::reverse_iterator rvIter;
          std::map<std::string, NodeId>::iterator it;
          for ( rvIter = objects.rbegin(); rvIter != objects.rend(); rvIter++) {
            if((*rvIter).second != ndkClassDef){
              it = (*rvIter).first->find(str);
              if( it != (*rvIter).first->end()) {
                foundObject = true;
                break;
              }
            }
          }

          if( foundObject ) {
            objNid = (*it).second;
          }else if(build_object){
            objNid = pBuilder.buildObject(str);
            objects.back().first->insert(pair<std::string, NodeId>(str, objNid));
          }

          parentNid = pBuilder.buildIdentifier(str, objNid);

          if(!foundObject && build_object){
            pBuilder.AddObjectRef(objNid, parentNid);
          }
        }
      }
      break;
    case List_kind:
      {
        vector<NodeId> args = visitExprAsdl(parent->v.List.elts);
        parentNid = pBuilder.buildList(args, false);
      }
      break;
    case Tuple_kind:
      {
        vector<NodeId> args = visitExprAsdl(parent->v.Tuple.elts);
        parentNid = pBuilder.buildList(args, true);
      }
      break;
#ifdef PY3
    case NameConstant_kind:
      {
        std::string name = "";
        PyObject *o = parent->v.NameConstant.value;
        if (o == Py_None)
          name = "None";
        else if (o == Py_True)
          name = "True";
        else if (o == Py_False)
          name = "False";

        if (!name.empty())
          parentNid = pBuilder.buildIdentifier(name, 0);
        else
          parentNid = pBuilder.buildStringLiteral("");
      }
      break;
    default:
      parentNid = pBuilder.buildStringLiteral("");
      break;
#endif
  }

  pBuilder.setIncreasedPosition(parentNid, parent->lineno, parent->col_offset, parent->endline, parent->endcol);

  getOuterNodeInLine(parentNid);

  EXCEPTION_LOC_END("ASTVisitor::visitExpr()")

    return parentNid;
}

NodeId ASTVisitor::visitSlice(slice_ty parent) {
  NodeId parentNid = 0;

  switch (parent->kind) {
#ifndef PY3
  case Ellipsis_kind:
    {
      parentNid = pBuilder.buildEllipsis();
    }
    break;
#endif
  case Slice_kind:
    {
      NodeId lower = 0;
      NodeId upper = 0;
      NodeId step = 0;
      unsigned line = 0, col = 0, endline = 0, endcol = 0;

      if(parent->v.Slice.lower != 0) {
        lower = visitExpr(parent->v.Slice.lower);
        line = parent->v.Slice.lower->lineno;
        col = parent->v.Slice.lower->col_offset;
        endline = parent->v.Slice.lower->endline;
        endcol = parent->v.Slice.lower->endcol;
      }

      if(parent->v.Slice.upper != 0) {
        upper = visitExpr(parent->v.Slice.upper);
        if (line == 0) {
          line = parent->v.Slice.upper->lineno;
          col = parent->v.Slice.upper->col_offset;
        }
        endline = parent->v.Slice.upper->endline;
        endcol = parent->v.Slice.upper->endcol;
      }

      if(parent->v.Slice.step != 0) {
        step = visitExpr(parent->v.Slice.step);
        if (line == 0) {
          line = parent->v.Slice.step->lineno;
          col = parent->v.Slice.step->col_offset;
        }
        endline = parent->v.Slice.step->endline;
        endcol = parent->v.Slice.step->endcol;
        parentNid = pBuilder.buildSlice(upper, lower, step);
      }else{
        parentNid = pBuilder.buildSlice(upper, lower, step);
      }

      pBuilder.setIncreasedPosition(parentNid, line, col, endline, endcol);
    }
    break;
  case ExtSlice_kind:
    {
      vector<NodeId> args = visitSliceAsdl(parent->v.ExtSlice.dims);

      parentNid = pBuilder.buildExtSlice(args, 0);
    }
    break;
  case Index_kind:
    {
      expr_ty indexValue = parent->v.Index.value;
      NodeId value = visitExpr(indexValue);
      parentNid = pBuilder.buildIndex(value);
      pBuilder.setIncreasedPosition(parentNid, indexValue->lineno, indexValue->col_offset, indexValue->endline, indexValue->endcol);
    }
    break;
  }


  return parentNid;
}

NodeId ASTVisitor::getDocstring(asdl_seq* ch_list){
  stmt_ty stmt = 0;
  if (ch_list != 0) {
    stmt = static_cast<stmt_ty>(ch_list->elements[0]);
  }

  if (!stmt){
    return 0;
  }

  NodeId docstring = 0;
  if (stmt->kind == Expr_kind){
    expr_ty expr = stmt->v.Expr.value;
    if (expr->kind == Str_kind){
      std::string str;
#ifdef PY3
      // TODO unicodes
      const char *s = PyString_AS_STRING(expr->v.Str.s);
      if (s)
        str = std::string(s);
#else
      std::string type(expr->v.Str.s->ob_type->tp_name);
      if(type.compare("unicode") == 0)
        str = std::string(PyString_AS_STRING(PyUnicode_AsUTF8String(expr->v.Str.s)));
      else if(type.compare("str") == 0)
        str = std::string(PyString_AS_STRING(expr->v.Str.s));
#endif

      int lineBreaks = static_cast<int>(std::count(str.begin(), str.end(), '\n'));

      docstring = pBuilder.buildDocstring(str);
      pBuilder.setIncreasedPosition(docstring, expr->endline-lineBreaks, 0, expr->endline, expr->endcol);
    }
  }
  return docstring;
}

int ASTVisitor::getLLOC(int first_line, int last_line, std::vector<int> logical_lines) {
  int lloc = 0;
  for(vector<int>::iterator it = logical_lines.begin(); it != logical_lines.end(); it++){
    if (*it >= first_line) {
      if (*it <= last_line)
        lloc++;
      else
        break;  // because lloc lines are sorted we can skip checking the rest
    }
  }
  return lloc;
}

void ASTVisitor::getOuterNodeInLine(NodeId id, int forcedLine){
  base::Positioned& actualNode = static_cast<base::Positioned&>(pBuilder.getFactory()->getRef(id));
  int actualLine = forcedLine == 0 ? actualNode.getPosition().getLine() : forcedLine;
  std::map<int, NodeId>::iterator it = commentHolderCandidates.find(actualLine); 
  if (it != commentHolderCandidates.end()){ // the last visited node has the most outer range in a line
    it->second = id;
  } else {
    commentHolderCandidates.insert(pair<int, NodeId>(actualLine, id));
  }
}
