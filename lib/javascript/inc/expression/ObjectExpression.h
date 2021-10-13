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

#ifndef _JAVASCRIPT_ObjectExpression_H_
#define _JAVASCRIPT_ObjectExpression_H_

#include "javascript/inc/javascript.h"

/**
* \file ObjectExpression.h
* \brief Contains declaration of the expression::ObjectExpression class.
* \brief The it get atributes from 
    * \brief base::Positioned
*/

namespace columbus { namespace javascript { namespace asg {
namespace expression {

  /**
  * \brief ObjectExpression class, which represents the expression::ObjectExpression node.
  * (missing)
  * 
  * Edges:
  *   - hasProperties (base::Positioned, multiple) : (missing)
  */
  class ObjectExpression : public Expression {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ObjectExpression(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ObjectExpression();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      ObjectExpression & operator=(const ObjectExpression&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      ObjectExpression(const ObjectExpression&);

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
      * \brief Gives back iterator for the hasProperties edges.
      * \return Returns an iterator for the hasProperties edges.
      */
      ListIterator<base::Positioned> getPropertiesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasProperties edges.
      * \return Returns an iterator for the hasProperties edges.
      */
      ListIterator<base::Positioned> getPropertiesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasProperties edges or not.
      * \return Returns true if the node doesn't have any hasProperties edge.
      */
      bool getPropertiesIsEmpty() const;

      /**
      * \brief Gives back how many hasProperties edges the node has.
      * \return Returns with the number of hasProperties edges.
      */
      unsigned getPropertiesSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasProperties edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasProperties edge.
      */
      void addProperties(const base::Positioned *node);

      /**
      * \brief Adds a new hasProperties edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasProperties edge.
      */
      void addProperties(NodeId id);

      /**
      * \brief Remove the hasProperties edge by id from the node.
      * \param id [in] The end point of the hasProperties edge.
      */
      void removeProperties(NodeId id);

      /**
      * \brief Remove the hasProperties edge from the node.
      * \param node [in] The end point of the hasProperties edge.
      */
      void removeProperties(base::Positioned *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasProperties edge points to. */
      ListIterator<base::Positioned>::Container hasPropertiesContainer;

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

