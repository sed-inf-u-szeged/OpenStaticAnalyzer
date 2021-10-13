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

#ifndef _JAVASCRIPT_SequenceExpression_H_
#define _JAVASCRIPT_SequenceExpression_H_

#include "javascript/inc/javascript.h"

/**
* \file SequenceExpression.h
* \brief Contains declaration of the expression::SequenceExpression class.
* \brief The it get atributes from 
    * \brief base::Positioned
*/

namespace columbus { namespace javascript { namespace asg {
namespace expression {

  /**
  * \brief SequenceExpression class, which represents the expression::SequenceExpression node.
  * &#60;p&#62;Comma operator.&#60;&#47;p&#62;&#60;p&#62;a = 4, b = 2;&#60;&#47;p&#62;
  * 
  * Edges:
  *   - hasExpressions (expression::Expression, multiple) : (missing)
  */
  class SequenceExpression : public Expression {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      SequenceExpression(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~SequenceExpression();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      SequenceExpression & operator=(const SequenceExpression&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      SequenceExpression(const SequenceExpression&);

    public:
      /**
      * \brief Gives back the NodeKind of the node.
      * \return Returns with the NodeKind.
      */
      virtual NodeKind getNodeKind() const;

      /**
      * \brief Delete all edge.
      */
      virtual void prepareDelete(bool tryOnVirtualParent);

    protected:
      /**
      * \brief Set or add the edge by edge kind
      * \param edgeKind           [in] The kind of the edge.
      * \param edgeEnd            [in] The id of node which is on the end of the edge.
      * \param tryOnVirtualParent [in] This is help for the traversal.
      * \return Return true if setting was success.
      */
      virtual bool setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent);

    protected:
      /**
      * \brief Remove the edge by edge kind
      * \param edgeKind           [in] The kind of the edge.
      * \param edgeEnd            [in] The id of node which is on the end of the edge.
      * \param tryOnVirtualParent [in] This is help for the traversal.
      * \return Return true if removing was success.
      */
      virtual bool removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent);

    public:

      // ---------- Edge getter function(s) ----------

      /**
      * \brief Gives back iterator for the hasExpressions edges.
      * \return Returns an iterator for the hasExpressions edges.
      */
      ListIterator<expression::Expression> getExpressionsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasExpressions edges.
      * \return Returns an iterator for the hasExpressions edges.
      */
      ListIterator<expression::Expression> getExpressionsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasExpressions edges or not.
      * \return Returns true if the node doesn't have any hasExpressions edge.
      */
      bool getExpressionsIsEmpty() const;

      /**
      * \brief Gives back how many hasExpressions edges the node has.
      * \return Returns with the number of hasExpressions edges.
      */
      unsigned getExpressionsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasExpressions edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasExpressions edge.
      */
      void addExpressions(const Expression *node);

      /**
      * \brief Adds a new hasExpressions edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasExpressions edge.
      */
      void addExpressions(NodeId id);

      /**
      * \brief Remove the hasExpressions edge by id from the node.
      * \param id [in] The end point of the hasExpressions edge.
      */
      void removeExpressions(NodeId id);

      /**
      * \brief Remove the hasExpressions edge from the node.
      * \param node [in] The end point of the hasExpressions edge.
      */
      void removeExpressions(Expression *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasExpressions edge points to. */
      ListIterator<expression::Expression>::Container hasExpressionsContainer;

    public:

      // ---------- Accept fundtions for Visitor ----------

      /**
      * \brief It calls the appropriate visit method of the given visitor.
      * \param visitor [in] The used visitor.
      */
      virtual void accept(Visitor& visitor) const;

      /**
      * \brief It calls the appropriate visitEnd method of the given visitor.
      * \param visitor [in] The used visitor.
      */
      virtual void acceptEnd(Visitor& visitor) const;

      /**
      * \internal
      * \brief Calculate node similarity.
      * \param nodeIf [in] The other node.
      */
      virtual double getSimilarity(const base::Base& node);

      /**
      * \internal
      * \brief Calculate node hash.
      */
      virtual NodeHashType getHash(std::set<NodeId>&  node) const ;

    protected:
      /**
      * \internal
      * \brief It is swap the string table ids to the other string table.
      * \param newStrTable [in] The new table
      * \param oldAndNewStrKeyMap [in] The map for fast serch.
      */
      virtual void swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap );

      /**
      * \internal
      * \brief Saves the node.
      * \param io [in] The node is written into io.
      */
      virtual void save(io::BinaryIO &io, bool withVirtualBase = true) const;

      /**
      * \internal
      * \brief Loads the node.
      * \param io [in] The node is read from io.
      */
      virtual void load(io::BinaryIO &io, bool withVirtualBase = true);


      friend class javascript::asg::Factory;
      friend class javascript::asg::VisitorSave;
  };

} 


}}}
#endif

