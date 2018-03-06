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

#ifndef _J_COVERAGE_VISITOR_H
#define _J_COVERAGE_VISITOR_H
#ifdef SCHEMA_JAVA
#include "../common.h"


class JCoverageVisitor : public CoverageVisitorBase, public columbus::java::asg::VisitorAbstractNodes {

public:
  JCoverageVisitor();
  virtual ~JCoverageVisitor();
  void visit(const columbus::java::asg::base::Base& n, bool b);
  virtual bool isIncTheComplexity (const Base& node) {return isIncTheComplexity(node.getNodeKind());}
  virtual bool isIncTheComplexity( int nodeKind );
};

#define COVERAGE_VISITOR JCoverageVisitor
#endif
#endif
