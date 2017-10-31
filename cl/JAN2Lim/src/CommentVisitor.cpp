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

#include "../inc/CommentVisitor.h"

namespace columbus { namespace JAN2Lim
{
  using namespace std;

  void CommentVisitor::setPass( int pass )
  {
    this->pass = pass;
  }

  unsigned long CommentVisitor::aggregateCommentLines( const lim::asg::logical::Member& member, bool first = true ) const
  {
    // commentLines are aggregated to the closest parent Package only
    // TCLOC will contain the total aggregate
    if ( !first && lim::asg::Common::getIsPackage( member ) ) return 0;

    unsigned long CLOC = member.getCommentLines();

    if ( ! lim::asg::Common::getIsScope( member ) ) return CLOC;
    const lim::asg::Scope& scope = dynamic_cast<const lim::asg::Scope&>( member );

    if ( scope.getMemberIsEmpty() ) return CLOC;

    lim::asg::ListIterator<lim::asg::logical::Member> i = scope.getMemberListIteratorBegin();
    for ( ; i != scope.getMemberListIteratorEnd(); ++i )
    {
      CLOC += aggregateCommentLines( *i, false );
    }

    return CLOC;
  }

  void CommentVisitor::visit( const lim::asg::logical::Package& node, bool callVirtualBase )
  {
    VisitorAbstractNodes::visit( node, callVirtualBase );

    if ( pass != 1 ) return;

    lim::asg::Package& package = const_cast<lim::asg::Package&>( node );
    package.setCommentLines( aggregateCommentLines( node ) );
  }

  void CommentVisitor::visit( const lim::asg::logical::Method& node, bool callVirtualBase )
  {
    VisitorAbstractNodes::visit( node, callVirtualBase );
    addToParentClass( const_cast<lim::asg::logical::Method&>( node ) );
  }

  void CommentVisitor::visit( const lim::asg::logical::Attribute& node, bool callVirtualBase )
  {
    VisitorAbstractNodes::visit( node, callVirtualBase );
    addToParentClass( const_cast<lim::asg::logical::Attribute&>( node ) );
  }
  
  void CommentVisitor::addToParentClass( lim::asg::logical::Member& member )
  {
    if ( pass != 2 ) return;

    lim::asg::logical::Member* step = &member;

    while( true )
    {
      lim::asg::ListIterator<lim::asg::base::Base> i = revEdges.constIteratorBegin( step->getId(), lim::asg::edkScope_HasMember );
      if ( i == revEdges.constIteratorEnd( step->getId(), lim::asg::edkScope_HasMember ) ) break;

      step = & dynamic_cast<lim::asg::logical::Member&>( const_cast<lim::asg::base::Base&>( *i ) );

      if ( lim::asg::Common::getIsClass( *step ) )
      {
        step->setCommentLines( step->getCommentLines() + member.getCommentLines() );
        break;
      }
    }
  }
}}
