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

#ifdef SCHEMA_JAVA

#include "../inc/common.h"
#include "../inc/Visitors/JNodeEmbeddednessVisitor.h"
#include "../inc/dcm.h"

void JNodeEmbeddednessVisitorBase::putNode( const columbus::java::asg::base::Positioned& n1 ,const columbus::java::asg::base::Positioned& n2, bool unique )
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

void JNodeEmbeddednessVisitorBase::visit( const columbus::java::asg::struc::MethodDeclaration& n, bool b )
{
  NodeEmbeddednessVisitorBase::visit(n,b);

  const columbus::java::asg::ReverseEdges& reverseEdges = n.getFactory().getReverseEdges();
  for (columbus::java::asg::ListIterator<columbus::java::asg::base::Base> itConnectedEdges =  reverseEdges.constIteratorBegin(n.getId(),columbus::java::asg::edkIdentifier_RefersTo); itConnectedEdges != reverseEdges.constIteratorEnd(n.getId(),columbus::java::asg::edkIdentifier_RefersTo) ; ++itConnectedEdges) {
    putNode(n,dynamic_cast<const columbus::java::asg::base::Positioned&>(*itConnectedEdges),false);
  }
}

void JNodeEmbeddednessVisitorBase::visit( const columbus::java::asg::expr::Identifier& n, bool b )
{
  NodeEmbeddednessVisitorBase::visit(n,b);
  if (n.getParentEdgeKind() == columbus::java::asg::edkBinary_HasRightOperand) {
    return;
  }

  if (n.getRefersTo() && columbus::java::asg::Common::getIsPositioned(*n.getRefersTo())) {
    putNode(n,*  dynamic_cast<const columbus::java::asg::base::Positioned*>(n.getRefersTo()),false);
  }
}

void JNodeEmbeddednessVisitorBase::visit( const columbus::java::asg::struc::VariableDeclaration& n, bool b )
{
  NodeEmbeddednessVisitorBase::visit(n,b);

  const columbus::java::asg::ReverseEdges& reverseEdges = n.getFactory().getReverseEdges();
  for (columbus::java::asg::ListIterator<columbus::java::asg::base::Base> itConnectedEdges =  reverseEdges.constIteratorBegin(n.getId(),columbus::java::asg::edkIdentifier_RefersTo); itConnectedEdges != reverseEdges.constIteratorEnd(n.getId(),columbus::java::asg::edkIdentifier_RefersTo) ; ++itConnectedEdges) {
    putNode(n,dynamic_cast<const columbus::java::asg::base::Positioned&>(*itConnectedEdges),false);
  }
}

void JNodeEmbeddednessVisitorBase::visit( const columbus::java::asg::expr::Expression& n, bool b )
{
  NodeEmbeddednessVisitorBase::visit(n,b);
  if (n.getType() && columbus::java::asg::Common::getIsClassType(*n.getType())) {
    const columbus::java::asg::type::ClassType* originType = dynamic_cast<const columbus::java::asg::type::ClassType*>(n.getType());
    if (originType) {
      if (originType->getRefersTo()) {
        putNode(n,*originType->getRefersTo(),true);
      }
    }
  }
}

#endif
