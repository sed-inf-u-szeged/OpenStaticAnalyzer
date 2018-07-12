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

#ifndef _JS_COVERAGE_VISITOR_H
#define _JS_COVERAGE_VISITOR_H
#ifdef SCHEMA_JAVASCRIPT

#include "../common.h"


class JSCoverageVisitor : public CoverageVisitorBase, public columbus::javascript::asg::VisitorAbstractNodes
{

public:
  JSCoverageVisitor();
  virtual ~JSCoverageVisitor();
  void visit(const Base& n, bool b);
  virtual bool isIncTheComplexity(const Base& node);// {return isIncTheComplexity(node.getNodeKind()); }
  virtual bool isIncTheComplexity(int nodeKind);
};

#define COVERAGE_VISITOR JSCoverageVisitor
#endif
#endif
