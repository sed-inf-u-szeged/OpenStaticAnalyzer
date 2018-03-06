/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#ifndef __VISITORIMPORT_H_
#define __VISITORIMPORT_H_

#include <python/inc/python.h>
#include "VisitorType.h"
#include <list>
#include <map>
#include <set>
#include <algorithm>

using namespace columbus;
using namespace columbus::python::asg;

namespace columbus {

class VisitorImport : public VisitorAbstractNodes {
private:
  Factory* factory;
  NodeId import_scope;
  NodeId package_id;
  std::list< NodeId > scope;
  std::list< NodeId > import_tree;
  std::map< NodeId, std::set< std::pair< NodeId, std::string > > > import_graph;
  std::map< NodeId, std::set< NodeId > >& type_set;
  std::set< NodeId >& import_resolved;

public:

  VisitorImport(Factory* factory, std::list< NodeId > import_tree, std::map< NodeId, std::set< NodeId > >& type_set, std::set< NodeId >& import_resolved): factory(factory), import_tree(import_tree), type_set(type_set), import_resolved(import_resolved){};

protected:

  void setType(module::Object& obj, type::Type& type);

  NodeId findModule(module::Package& package, std::string name);
  NodeId getAssignValue(expression::Expression& target_list, expression::Expression& value, NodeId target);
  std::set<std::string> getAll(module::Module& module);
  NodeId getObject(base::Base& current_scope, std::string name, bool create_object = false);
  NodeId findObject(const std::string& name, ListIterator<module::Object> lit, ListIterator<module::Object> litEnd);

  void visit   (const statement::ClassDef& n, bool);
  void visitEnd(const statement::ClassDef& n, bool);
  
  void visit   (const statement::FunctionDef& n, bool);
  void visitEnd(const statement::FunctionDef& n, bool);

  void visit   (const statement::ImportFrom& node, bool);
  void visitEnd(const statement::ImportFrom& node, bool);

  void visit   (const statement::ImportStatement& node, bool);
  void visitEnd(const statement::ImportStatement& node, bool);

  void visit   (const statement::Alias& n, bool);
  void visitEnd(const statement::Alias& n, bool);

  void visit   (const module::Module& n, bool);
  void visitEnd(const module::Module& n, bool);

};
}

#endif