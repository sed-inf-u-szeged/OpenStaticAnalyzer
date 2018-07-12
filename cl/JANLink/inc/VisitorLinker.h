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

#ifndef _JAVA_VISITORLINKER_H_
#define _JAVA_VISITORLINKER_H_

#include <java/inc/java.h>
#include "LinkerBase.h"

/**
* \file VisitorLinker.h
* \brief Contains declaration of VisitorLinker class.
*/

namespace columbus { namespace java { namespace linker {

  /**
  * \brief TODO.
  */
  class VisitorLinker : public LinkerBase {

    public:

      /**
      * \brief Constructor for VisitorLinker.
      */
      VisitorLinker(UniqueMap& strMap, StrNodeIdMap& pathMap, columbus::java::asg::Factory& fact, columbus::java::asg::Factory& tmpFact);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorLinker();


      virtual void collectEdges(columbus::java::asg::expr::Annotation& newNode, const columbus::java::asg::expr::Annotation& node, std::vector<NodeId>& v, bool callVirtualBase);
      virtual void collectEdges(columbus::java::asg::struc::AnnotatedElement& newNode, const columbus::java::asg::struc::AnnotatedElement& node, std::vector<NodeId>& v, bool callVirtualBase);
      virtual void collectEdges(columbus::java::asg::struc::MethodDeclaration& newNode, const columbus::java::asg::struc::MethodDeclaration& node, std::vector<NodeId>& v, bool callVirtualBase);
      virtual void collectEdges(columbus::java::asg::struc::NormalMethod& newNode, const columbus::java::asg::struc::NormalMethod& node, std::vector<NodeId>& v, bool callVirtualBase);
      virtual void collectEdges(columbus::java::asg::struc::TypeDeclaration& newNode, const columbus::java::asg::struc::TypeDeclaration& node, std::vector<NodeId>& v, bool callVirtualBase);
      virtual void collectEdges(columbus::java::asg::struc::TypeParameter& newNode, const columbus::java::asg::struc::TypeParameter& node, std::vector<NodeId>& v, bool callVirtualBase);
      virtual void collectEdges(columbus::java::asg::struc::VariableDeclaration& newNode, const columbus::java::asg::struc::VariableDeclaration& node, std::vector<NodeId>& v, bool callVirtualBase);

    protected:

      virtual NodeId getNewNode(const columbus::java::asg::base::Base& node, bool& update);

      void checkTypeExpression(columbus::java::asg::expr::TypeExpression* newTypeExpr, columbus::java::asg::expr::TypeExpression* otherTypeExpr);
      void checkTypeExpressionList(columbus::java::asg::ListIterator<columbus::java::asg::expr::TypeExpression> it, columbus::java::asg::ListIterator<columbus::java::asg::expr::TypeExpression> itEnd,
                                   columbus::java::asg::ListIterator<columbus::java::asg::expr::TypeExpression> otherIt, columbus::java::asg::ListIterator<columbus::java::asg::expr::TypeExpression> otherItEnd);

  };

}}}

#endif

