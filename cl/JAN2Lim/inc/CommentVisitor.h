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

#ifndef __COMMENT_VISITOR_H__
#define __COMMENT_VISITOR_H__

#include "lim/inc/lim.h"
#include "JAN2LimVisitor.h"

namespace columbus { namespace JAN2Lim
{
  class CommentVisitor : public lim::asg::VisitorAbstractNodes
  {
    public:
      CommentVisitor( lim::asg::Factory& f ) : factory( f ), revEdges( f.getReverseEdges() ), pass( 1 ) {}

      virtual void visit( const lim::asg::logical::Package& node, bool );
      virtual void visit( const lim::asg::logical::Method& node, bool );
      virtual void visit( const lim::asg::logical::Attribute& node, bool );

      void setPass( int pass );

    private:
      lim::asg::Factory& factory;
      const lim::asg::ReverseEdges& revEdges;

      /**
      * In the first pass we aggregate every commentLine metric to its closest Package parent
      * ( in this phase, the commentLines values still apply only to their node, e.g. a class'
      * commentLines doesn't contain the commentLines from its methods or attributes, so there
      * will be no duplication )
      *
      * In the second pass, every method and attribute adds its commentLines value to its
      * closest Class parent's value.
      */
      int pass;

      /**
      * Collects the commentLines of the Member and its every non-Package child
      */
      unsigned long aggregateCommentLines( const lim::asg::logical::Member&, bool ) const;

      /**
      * Adds the node's commentLines to its closest Class parent
      */
      void addToParentClass( lim::asg::logical::Member& );
  };
}}

#endif
