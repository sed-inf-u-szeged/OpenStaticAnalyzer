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
#ifdef SCHEMA_JAVA

#include "../common.h"
#include "NodeEmbeddednessVisitorBase.h"
#include <java/inc/Common.h>


class JNodeEmbeddednessVisitorBase : public NodeEmbeddednessVisitorBase {
public :
  JNodeEmbeddednessVisitorBase(ConectedEdgesMap& mapTofill,const columbus::dcf::DuplicatedCodeMiner& dcf):NodeEmbeddednessVisitorBase(mapTofill,dcf) {}
  virtual ~JNodeEmbeddednessVisitorBase(){}
protected:
  //Put the node to the database
  void putNode(const columbus::java::asg::base::Positioned& n1 ,const columbus::java::asg::base::Positioned& n2, bool unique);
  //Method def
  void visit(const columbus::java::asg::struc::MethodDeclaration& n, bool b);
  //Variable && method reference
  void visit(const columbus::java::asg::expr::Identifier& n, bool b);
  //Variable def
  void visit(const columbus::java::asg::struc::VariableDeclaration& n, bool b);
  //type reference
  void visit(const columbus::java::asg::expr::Expression& n, bool b);

};

#define NODE_EMBEDDEDNESS_VISITOR JNodeEmbeddednessVisitorBase
#endif // SCHEMA_JAVA
#endif // _DCF_CPPJNODEV_H_
