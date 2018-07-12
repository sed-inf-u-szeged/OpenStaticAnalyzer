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

#ifdef SCHEMA_PYTHON

#include "../inc/common.h"
#include "../inc/Visitors/PNodeEmbeddednessVisitor.h"
#include "../inc/dcm.h"

namespace columbus {


  void PNodeEmbeddednessVisitorBase::visit( const columbus::python::asg::statement::Parameter& n, bool b ) {
    NodeEmbeddednessVisitorBase::visit(n,b);
    columbus::python::asg::module::Object* obejctRefersTo = n.getRefersTo();
    if (obejctRefersTo) {
      addObjectReferenceToNode(n, obejctRefersTo,false);
    }
  }

  void PNodeEmbeddednessVisitorBase::visit( const columbus::python::asg::statement::Alias& n, bool b ) {
    NodeEmbeddednessVisitorBase::visit(n,b);
    LANGUAGE_NAMESPACE::base::Base* obejctRefersTo = n.getRefersTo();
    if (obejctRefersTo) {
      if ( LANGUAGE_NAMESPACE::Common::getIsObject(*obejctRefersTo)) {
        addObjectReferenceToNode(n, dynamic_cast<LANGUAGE_NAMESPACE::module::Object*>( obejctRefersTo),false);
      } else if (LANGUAGE_NAMESPACE::Common::getIsPositioned(*obejctRefersTo)) {
        putNode(n,*dynamic_cast<LANGUAGE_NAMESPACE::base::Positioned*>( obejctRefersTo),true);
      }
    }

  }

  void PNodeEmbeddednessVisitorBase::visit( const columbus::python::asg::expression::Identifier& n, bool b ) {
    NodeEmbeddednessVisitorBase::visit(n,b);
    columbus::python::asg::module::Object* obejctRefersTo = n.getRefersTo();
    if (obejctRefersTo) {
      addObjectReferenceToNode(n, obejctRefersTo,false);
    }
  }

  void PNodeEmbeddednessVisitorBase::visit( const columbus::python::asg::statement::FunctionDef& n, bool b )
  {
    NodeEmbeddednessVisitorBase::visit(n,b);
    columbus::python::asg::module::Object* obejctRefersTo = n.getRefersTo();
    if (obejctRefersTo) {
      addObjectReferenceToNode(n, obejctRefersTo,false);
      addTypeReferenceToNode(n, n.getReturnType(),true);
    }
  }

  void PNodeEmbeddednessVisitorBase::visit( const columbus::python::asg::expression::Call& n, bool b )
  {
      NodeEmbeddednessVisitorBase::visit(n,b);
    if (n.getRefersTo()){
      putNode(n,*n.getRefersTo(),false);
    }
  }

  void PNodeEmbeddednessVisitorBase::visit( const columbus::python::asg::statement::ClassDef& n, bool b )
  {
    NodeEmbeddednessVisitorBase::visit(n,b);
    if (n.getRefersTo()){
      addObjectReferenceToNode(n,n.getRefersTo(),false); 
    }
  }

  void PNodeEmbeddednessVisitorBase::visit( const columbus::python::asg::expression::Expression& n, bool b )
  {
    NodeEmbeddednessVisitorBase::visit(n,b);
    addTypeReferenceToNode(n, n.getType(),true);
  }

  void PNodeEmbeddednessVisitorBase::visit( const columbus::python::asg::statement::BaseSpecifier& n, bool b )
  {
    NodeEmbeddednessVisitorBase::visit(n,b);
    if (n.getDerivesFrom()){
      putNode(n,*n.getDerivesFrom(),false);
    }
  }

  


  void PNodeEmbeddednessVisitorBase::putNode( const columbus::python::asg::base::Positioned& n1 ,const columbus::python::asg::base::Positioned& n2, bool unique )
  {
    // test the lim filter state 
    if (dcf.isItFilteredInLim(limComponenetId,n2))
      return;

    NodeId limNode =  dcf.getLimNodeIdByNode(limComponenetId,n1);
    if (limNode) {
      aliasMap[limNode] = NodeGlobalId( limComponenetId,n1.getId());
    }

    if (!aliasMode) {
      alias = NodeGlobalId( limComponenetId,n1.getId());
    }

    const std::string& baseNodeFile = n1.getPosition().getPath();
    const std::string& endNodeFile  = n2.getPosition().getPath();
    ConectedEdgesMap::iterator itFoundAssociation = conectedEdgesMap.find(NodeGlobalId( limComponenetId,n1.getId()));

    int distance =calculateNDC(baseNodeFile,endNodeFile) ;
    if (itFoundAssociation != conectedEdgesMap.end()) {
      bool found = false;
      if (unique) {
        std::list<NodeWithWeight >& listRef = conectedEdgesMap[NodeGlobalId( limComponenetId,n1.getId())];
        for (std::list< NodeWithWeight >::iterator it = listRef.begin();it != listRef.end();++it ) {
          if (it->nodeUniqueId == NodeGlobalId( limComponenetId,n2.getId())) {
            found = true;
          }
        }
      } 
      if (!found) {
        conectedEdgesMap[alias].push_front(
          NodeWithWeight(NodeGlobalId( limComponenetId,n2.getId()),NdcWeight(distance,!unique))
          );
      }
    } else {
      std::list< NodeWithWeight > newList ;
      newList.push_front(NodeWithWeight(NodeGlobalId( limComponenetId,n2.getId()),NdcWeight(distance,!unique)));
      conectedEdgesMap.insert(std::make_pair(alias,newList));
    }
  }

  void PNodeEmbeddednessVisitorBase::addObjectReferenceToNode( const columbus::python::asg::base::Positioned& n, columbus::python::asg::module::Object* obejctRefersTo,bool asUnique )
  {
    if (obejctRefersTo != NULL) {
      for (LANGUAGE_NAMESPACE::ListIterator<LANGUAGE_NAMESPACE::base::Positioned> it = obejctRefersTo->getRefersToListIteratorBegin();
        it != obejctRefersTo->getRefersToListIteratorEnd();++it) {
          putNode(n,*it,asUnique);
      }
    }
  }

  void PNodeEmbeddednessVisitorBase::addTypeReferenceToNode( const columbus::python::asg::base::Positioned& n, columbus::python::asg::type::Type* obejctRefersTo ,bool asUnique )
  {
    if (obejctRefersTo && LANGUAGE_NAMESPACE::Common::getIsReferenceType(*obejctRefersTo)) {
       columbus::python::asg::type::ReferenceType* refType = dynamic_cast<columbus::python::asg::type::ReferenceType*> (obejctRefersTo);
       if (refType->getRefersTo()) {
        putNode(n,*refType->getRefersTo(),asUnique);
       }
    }
  }

}

#endif
