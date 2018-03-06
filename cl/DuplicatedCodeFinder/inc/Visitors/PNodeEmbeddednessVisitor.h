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

#ifndef _DCF_PNODEEV_H_
#define _DCF_PNODEEV_H_

#ifdef SCHEMA_PYTHON

#include "../common.h"
#include "NodeEmbeddednessVisitorBase.h"
#include <python/inc/Common.h>

namespace columbus {
  
  class PNodeEmbeddednessVisitorBase : public NodeEmbeddednessVisitorBase {
  public :
    PNodeEmbeddednessVisitorBase(ConectedEdgesMap& mapTofill,const columbus::dcf::DuplicatedCodeMiner& dcf):NodeEmbeddednessVisitorBase(mapTofill,dcf) {}
    virtual ~PNodeEmbeddednessVisitorBase(){}
  protected:
    void visit(const columbus::python::asg::statement::Parameter& n, bool b);

    void visit( const columbus::python::asg::statement::Alias& n, bool b );

    void visit( const columbus::python::asg::expression::Identifier& n, bool b );
    void visit( const columbus::python::asg::statement::FunctionDef& n, bool b );

    void visit( const columbus::python::asg::expression::Call& n, bool b );

    void visit( const columbus::python::asg::statement::ClassDef& n, bool b );

    void visit( const columbus::python::asg::expression::Expression& n, bool b );

    void visit( const columbus::python::asg::statement::BaseSpecifier& n, bool b );

    //Put the node to the database
    void putNode(const columbus::python::asg::base::Positioned& n1 ,const columbus::python::asg::base::Positioned& n2, bool unique);

    void addObjectReferenceToNode(const columbus::python::asg::base::Positioned& n, columbus::python::asg::module::Object* obejctRefersTo ,bool asUnique );
    void addTypeReferenceToNode(const columbus::python::asg::base::Positioned& n, columbus::python::asg::type::Type* obejctRefersTo ,bool asUnique );
  };
}
#define NODE_EMBEDDEDNESS_VISITOR PNodeEmbeddednessVisitorBase
#endif // SCHEMA_PYTHON

#endif // _DCF_PNODEEV_H_
