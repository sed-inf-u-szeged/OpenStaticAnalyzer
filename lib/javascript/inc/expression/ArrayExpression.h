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

#ifndef _JAVASCRIPT_ArrayExpression_H_
#define _JAVASCRIPT_ArrayExpression_H_

#include "javascript/inc/javascript.h"

/**
* \file ArrayExpression.h
* \brief Contains declaration of the expression::ArrayExpression class.
* \brief The it get atributes from 
    * \brief base::Positioned
*/

namespace columbus { namespace javascript { namespace asg {
namespace expression {

  /**
  * \brief ArrayExpression class, which represents the expression::ArrayExpression node.
  * &#60;p&#62;An array expression like [a,b,c] or [1,2,3]&#60;&#47;p&#62;
  * 
  * Edges:
  *   - hasElements (base::Positioned, multiple) : (missing)
  */
  class ArrayExpression : public Expression {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ArrayExpression(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ArrayExpression();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      ArrayExpression & operator=(const ArrayExpression&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      ArrayExpression(const ArrayExpression&);

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
      * \brief Gives back iterator for the hasElements edges.
      * \return Returns an iterator for the hasElements edges.
      */
      ListIterator<base::Positioned> getElementsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasElements edges.
      * \return Returns an iterator for the hasElements edges.
      */
      ListIterator<base::Positioned> getElementsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasElements edges or not.
      * \return Returns true if the node doesn't have any hasElements edge.
      */
      bool getElementsIsEmpty() const;

      /**
      * \brief Gives back how many hasElements edges the node has.
      * \return Returns with the number of hasElements edges.
      */
      unsigned getElementsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasElements edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasElements edge.
      */
      void addElements(const base::Positioned *node);

      /**
      * \brief Adds a new hasElements edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasElements edge.
      */
      void addElements(NodeId id);

      /**
      * \brief Remove the hasElements edge by id from the node.
      * \param id [in] The end point of the hasElements edge.
      */
      void removeElements(NodeId id);

      /**
      * \brief Remove the hasElements edge from the node.
      * \param node [in] The end point of the hasElements edge.
      */
      void removeElements(base::Positioned *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasElements edge points to. */
      ListIterator<base::Positioned>::Container hasElementsContainer;

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

