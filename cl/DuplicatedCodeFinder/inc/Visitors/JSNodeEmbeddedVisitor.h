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

#ifndef _DCF_CPPJNODEV_H_
#define _DCF_CPPJNODEV_H_
#ifdef SCHEMA_JAVASCRIPT

#include "../common.h"
#include "NodeEmbeddednessVisitorBase.h"
#include <javascript/inc/Common.h>


class JSNodeEmbeddedVisitor : public NodeEmbeddednessVisitorBase {
public:
  JSNodeEmbeddedVisitor(ConectedEdgesMap& mapTofill, const columbus::dcf::DuplicatedCodeMiner& dcf) :NodeEmbeddednessVisitorBase(mapTofill, dcf) {}
  virtual ~JSNodeEmbeddedVisitor() {}

protected:
  void putNode(const columbus::javascript::asg::base::Positioned& n1, const columbus::javascript::asg::base::Positioned& n2, bool unique);

  void visit(const columbus::javascript::asg::expression::Identifier& n, bool b);

  void visit(const columbus::javascript::asg::declaration::VariableDeclarator& n, bool b);

  void visit(const columbus::javascript::asg::declaration::ClassDeclaration& n, bool b);

  void visit(const columbus::javascript::asg::declaration::FunctionDeclaration& n, bool b);

  void visit(const columbus::javascript::asg::structure::MethodDefinition& n, bool b);
};

#define NODE_EMBEDDEDNESS_VISITOR JSNodeEmbeddedVisitor
#endif // SCHEMA_JAVASCRIPT
#endif // _DCF_CPPJNODEV_H_

