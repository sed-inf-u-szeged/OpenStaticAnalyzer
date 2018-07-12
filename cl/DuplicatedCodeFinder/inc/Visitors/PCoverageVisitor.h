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

#ifndef _P_COVERAGE_VISITOR_H
#define _P_COVERAGE_VISITOR_H

#ifdef SCHEMA_PYTHON

#include "../common.h"


class PCoverageVisitor : public CoverageVisitorBase, public columbus::python::asg::VisitorAbstractNodes {



public:
  PCoverageVisitor(){}
  virtual ~PCoverageVisitor(){}
  void visit(const columbus::python::asg::base::Base& n, bool b){ visitBase(n);}

  virtual bool isIncTheComplexity( int nodeKind  ) {
    return   columbus::python::asg::Common::getIsBaseClassKind((columbus::python::asg::NodeKind)nodeKind,columbus::python::asg::ndkIfExpression) 
    || columbus::python::asg::Common::getIsBaseClassKind((columbus::python::asg::NodeKind)nodeKind,columbus::python::asg::ndkFor) 
    || columbus::python::asg::Common::getIsBaseClassKind((columbus::python::asg::NodeKind)nodeKind,columbus::python::asg::ndkIf) 
    || columbus::python::asg::Common::getIsBaseClassKind((columbus::python::asg::NodeKind)nodeKind,columbus::python::asg::ndkTry) 
    || columbus::python::asg::Common::getIsBaseClassKind((columbus::python::asg::NodeKind)nodeKind,columbus::python::asg::ndkWhile)  ;
  }

  virtual bool isIncTheComplexity( const columbus::python::asg::base::Base& n ) {

    int nodeKind = n.getNodeKind();
    if (columbus::python::asg::Common::getIsBaseClassKind((columbus::python::asg::NodeKind)nodeKind,columbus::python::asg::ndkBinaryLogical) ) {
     const columbus::python::asg::expression::BinaryLogical& bilogic  = dynamic_cast<const columbus::python::asg::expression::BinaryLogical&>(n);
     if (bilogic.getKind() ==  columbus::python::asg::blkOr || bilogic.getKind() ==  columbus::python::asg::blkAnd) {
       return true;
     }
    }
    return isIncTheComplexity(n.getNodeKind());
  }
};

#define COVERAGE_VISITOR  PCoverageVisitor

#endif
#endif
