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

#include "../inc/common.h"

#ifdef SCHEMA_JAVASCRIPT
using namespace columbus;
using namespace javascript;
using namespace asg;
using namespace std;

JSCoverageVisitor::JSCoverageVisitor()
  : CoverageVisitorBase()
{
}

JSCoverageVisitor::~JSCoverageVisitor()
{
}

void JSCoverageVisitor::visit(const Base& n, bool b)
{
  visitBase(n);
}

bool JSCoverageVisitor::isIncTheComplexity(int ndk) // currently out of use
{
  return
    ndk == ndkWhileStatement ||
    ndk == ndkDoWhileStatement ||
    ndk == ndkIfStatement ||
    ndk == ndkForStatement ||
    ndk == ndkForInStatement ||
    ndk == ndkForOfStatement ||
    ndk == ndkSwitchCase ||
    ndk == ndkConditionalExpression ||
    ndk == ndkLogicalExpression;
}

bool JSCoverageVisitor::isIncTheComplexity(const Base& node)
{
  if (columbus::javascript::asg::Common::getIsWhileStatement(node) ||
    columbus::javascript::asg::Common::getIsIfStatement(node) ||
    columbus::javascript::asg::Common::getIsForStatement(node) ||
    columbus::javascript::asg::Common::getIsForInStatement(node) ||
    columbus::javascript::asg::Common::getIsSwitchCase(node) ||
    columbus::javascript::asg::Common::getIsConditionalExpression(node) ||
    columbus::javascript::asg::Common::getIsLogicalExpression(node)
    ) {
    return true;
  }
  return false;
}
#endif
