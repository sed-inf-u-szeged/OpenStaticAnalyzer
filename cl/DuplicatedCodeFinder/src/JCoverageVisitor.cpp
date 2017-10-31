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

#include "../inc/common.h"

using namespace columbus;
using namespace java;
using namespace asg;
using namespace std;

JCoverageVisitor::JCoverageVisitor() : CoverageVisitorBase(){

}

JCoverageVisitor::~JCoverageVisitor() {

}

void JCoverageVisitor::visit(const columbus::java::asg::base::Base& n, bool b) {
  visitBase(n);
}

bool JCoverageVisitor::isIncTheComplexity( int nodeKind ) {

  return   columbus::java::asg::Common::getIsBaseClassKind((columbus::java::asg::NodeKind)nodeKind,ndkIteration) 
        || columbus::java::asg::Common::getIsBaseClassKind((columbus::java::asg::NodeKind)nodeKind,ndkSelection) 
        || columbus::java::asg::Common::getIsBaseClassKind((columbus::java::asg::NodeKind)nodeKind,ndkCase) 
        || columbus::java::asg::Common::getIsBaseClassKind((columbus::java::asg::NodeKind)nodeKind,ndkHandler) 
        || columbus::java::asg::Common::getIsBaseClassKind((columbus::java::asg::NodeKind)nodeKind,ndkConditional) ;
   
  return false;
}
