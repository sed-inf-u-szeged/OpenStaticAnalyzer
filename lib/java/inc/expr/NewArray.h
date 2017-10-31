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

#ifndef _JAVA_NewArray_H_
#define _JAVA_NewArray_H_

#include "java/inc/java.h"

/**
* \file NewArray.h
* \brief Contains declaration of the expr::NewArray class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace expr {

  /**
  * \brief NewArray class, which represents the expr::NewArray node.
  * (missing)
  * 
  * Attributes:
  *   - leftBracePosition (Range) : (missing)
  * 
  * Edges:
  *   - hasComponentType (expr::TypeExpression, single) : (missing)
  *   - hasDimensions (expr::Expression, multiple) : (missing)
  *   - hasInitializers (expr::Expression, multiple) : (missing)
  */
  class NewArray : public Expression {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      NewArray(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~NewArray();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      NewArray & operator=(const NewArray&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      NewArray(const NewArray&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const NewArray& other, bool tryOnVirtualParent);

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


      // ---------- Attribute getter function(s) ----------

      /**
      * \brief Gives back the leftBracePosition of the node.
      * \return Returns with the leftBracePosition.
      */
      virtual const Range getLeftBracePosition() const;

      /**
      * \brief Compare two node by leftBracePosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByLeftBracePosition(const NewArray& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the leftBracePosition of the node.
      * \param leftBracePosition [in] The new value of the leftBracePosition.
      */
      virtual void setLeftBracePosition(const Range& _leftBracePosition);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief todo (unknown). */
      MultiRange m_leftBracePosition;

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
      * \brief Gives back the pointer of the node the hasComponentType edge points to.
      * \return Returns the end point of the hasComponentType edge.
      */
      expr::TypeExpression* getComponentType() const;

      /**
      * \brief Gives back iterator for the hasDimensions edges.
      * \return Returns an iterator for the hasDimensions edges.
      */
      ListIterator<expr::Expression> getDimensionsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasDimensions edges.
      * \return Returns an iterator for the hasDimensions edges.
      */
      ListIterator<expr::Expression> getDimensionsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasDimensions edges or not.
      * \return Returns true if the node doesn't have any hasDimensions edge.
      */
      bool getDimensionsIsEmpty() const;

      /**
      * \brief Gives back how many hasDimensions edges the node has.
      * \return Returns with the number of hasDimensions edges.
      */
      unsigned getDimensionsSize() const;

      /**
      * \brief Gives back iterator for the hasInitializers edges.
      * \return Returns an iterator for the hasInitializers edges.
      */
      ListIterator<expr::Expression> getInitializersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasInitializers edges.
      * \return Returns an iterator for the hasInitializers edges.
      */
      ListIterator<expr::Expression> getInitializersListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasInitializers edges or not.
      * \return Returns true if the node doesn't have any hasInitializers edge.
      */
      bool getInitializersIsEmpty() const;

      /**
      * \brief Gives back how many hasInitializers edges the node has.
      * \return Returns with the number of hasInitializers edges.
      */
      unsigned getInitializersSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasComponentType edge.
      * \param id [in] The new end point of the hasComponentType edge.
      */
      void setComponentType(NodeId id);

      /**
      * \brief Sets the hasComponentType edge.
      * \param node [in] The new end point of the hasComponentType edge.
      */
      void setComponentType(TypeExpression *node);

      /**
      * \brief remove the hasComponentType edge.
      */
      void removeComponentType();

      /**
      * \brief Adds a new hasDimensions edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasDimensions edge.
      */
      void addDimensions(const Expression *node);

      /**
      * \brief Adds a new hasDimensions edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasDimensions edge.
      */
      void addDimensions(NodeId id);

      /**
      * \brief Remove the hasDimensions edge by id from the node.
      * \param id [in] The end point of the hasDimensions edge.
      */
      void removeDimensions(NodeId id);

      /**
      * \brief Remove the hasDimensions edge from the node.
      * \param node [in] The end point of the hasDimensions edge.
      */
      void removeDimensions(Expression *node);

      /**
      * \brief Adds a new hasInitializers edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasInitializers edge.
      */
      void addInitializers(const Expression *node);

      /**
      * \brief Adds a new hasInitializers edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasInitializers edge.
      */
      void addInitializers(NodeId id);

      /**
      * \brief Remove the hasInitializers edge by id from the node.
      * \param id [in] The end point of the hasInitializers edge.
      */
      void removeInitializers(NodeId id);

      /**
      * \brief Remove the hasInitializers edge from the node.
      * \param node [in] The end point of the hasInitializers edge.
      */
      void removeInitializers(Expression *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasComponentType edge points to. */
      NodeId m_hasComponentType;

      /** \internal \brief Container stores the id of the nodes the hasDimensions edge points to. */
      ListIterator<expr::Expression>::Container hasDimensionsContainer;

      /** \internal \brief Container stores the id of the nodes the hasInitializers edge points to. */
      ListIterator<expr::Expression>::Container hasInitializersContainer;

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

      /**
      * \internal
      * \brief Sorts some edges and attributes of the node.
      */
      virtual void sort(bool withVirtualBase = true);


      friend class java::asg::Factory;
      friend class java::asg::VisitorSave;
  };

} 


}}}
#endif

