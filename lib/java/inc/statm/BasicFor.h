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

#ifndef _JAVA_BasicFor_H_
#define _JAVA_BasicFor_H_

#include "java/inc/java.h"

/**
* \file BasicFor.h
* \brief Contains declaration of the statm::BasicFor class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace statm {

  /**
  * \brief BasicFor class, which represents the statm::BasicFor node.
  * (missing)
  * 
  * Attributes:
  *   - firstSemiPosition (Range) : (missing)
  *   - secondSemiPosition (Range) : (missing)
  * 
  * Edges:
  *   - hasInitializers (statm::Statement, multiple) : (missing)
  *   - hasCondition (expr::Expression, single) : (missing)
  *   - hasUpdates (statm::Statement, multiple) : (missing)
  */
  class BasicFor : public For {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      BasicFor(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~BasicFor();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      BasicFor & operator=(const BasicFor&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      BasicFor(const BasicFor&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const BasicFor& other, bool tryOnVirtualParent);

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
      * \brief Gives back the firstSemiPosition of the node.
      * \return Returns with the firstSemiPosition.
      */
      virtual const Range getFirstSemiPosition() const;

      /**
      * \brief Compare two node by firstSemiPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByFirstSemiPosition(const BasicFor& other) const;

      /**
      * \brief Gives back the secondSemiPosition of the node.
      * \return Returns with the secondSemiPosition.
      */
      virtual const Range getSecondSemiPosition() const;

      /**
      * \brief Compare two node by secondSemiPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareBySecondSemiPosition(const BasicFor& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the firstSemiPosition of the node.
      * \param firstSemiPosition [in] The new value of the firstSemiPosition.
      */
      virtual void setFirstSemiPosition(const Range& _firstSemiPosition);

      /**
      * \internal
      * \brief Sets the secondSemiPosition of the node.
      * \param secondSemiPosition [in] The new value of the secondSemiPosition.
      */
      virtual void setSecondSemiPosition(const Range& _secondSemiPosition);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief todo (unknown). */
      MultiRange m_firstSemiPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_secondSemiPosition;

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
      * \brief Gives back iterator for the hasInitializers edges.
      * \return Returns an iterator for the hasInitializers edges.
      */
      ListIterator<statm::Statement> getInitializersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasInitializers edges.
      * \return Returns an iterator for the hasInitializers edges.
      */
      ListIterator<statm::Statement> getInitializersListIteratorEnd() const;

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

      /**
      * \brief Gives back the pointer of the node the hasCondition edge points to.
      * \return Returns the end point of the hasCondition edge.
      */
      expr::Expression* getCondition() const;

      /**
      * \brief Gives back iterator for the hasUpdates edges.
      * \return Returns an iterator for the hasUpdates edges.
      */
      ListIterator<statm::Statement> getUpdatesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasUpdates edges.
      * \return Returns an iterator for the hasUpdates edges.
      */
      ListIterator<statm::Statement> getUpdatesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasUpdates edges or not.
      * \return Returns true if the node doesn't have any hasUpdates edge.
      */
      bool getUpdatesIsEmpty() const;

      /**
      * \brief Gives back how many hasUpdates edges the node has.
      * \return Returns with the number of hasUpdates edges.
      */
      unsigned getUpdatesSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasInitializers edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasInitializers edge.
      */
      void addInitializers(const Statement *node);

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
      void removeInitializers(Statement *node);

      /**
      * \brief Sets the hasCondition edge.
      * \param id [in] The new end point of the hasCondition edge.
      */
      void setCondition(NodeId id);

      /**
      * \brief Sets the hasCondition edge.
      * \param node [in] The new end point of the hasCondition edge.
      */
      void setCondition(expr::Expression *node);

      /**
      * \brief remove the hasCondition edge.
      */
      void removeCondition();

      /**
      * \brief Adds a new hasUpdates edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasUpdates edge.
      */
      void addUpdates(const Statement *node);

      /**
      * \brief Adds a new hasUpdates edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasUpdates edge.
      */
      void addUpdates(NodeId id);

      /**
      * \brief Remove the hasUpdates edge by id from the node.
      * \param id [in] The end point of the hasUpdates edge.
      */
      void removeUpdates(NodeId id);

      /**
      * \brief Remove the hasUpdates edge from the node.
      * \param node [in] The end point of the hasUpdates edge.
      */
      void removeUpdates(Statement *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasInitializers edge points to. */
      ListIterator<statm::Statement>::Container hasInitializersContainer;

      /** \internal \brief The id of the node the hasCondition edge points to. */
      NodeId m_hasCondition;

      /** \internal \brief Container stores the id of the nodes the hasUpdates edge points to. */
      ListIterator<statm::Statement>::Container hasUpdatesContainer;

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

