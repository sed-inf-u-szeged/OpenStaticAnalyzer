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

#ifndef _JAVA_Try_H_
#define _JAVA_Try_H_

#include "java/inc/java.h"

/**
* \file Try.h
* \brief Contains declaration of the statm::Try class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace statm {

  /**
  * \brief Try class, which represents the statm::Try node.
  * (missing)
  * 
  * Attributes:
  *   - resourceLeftParenPosition (Range) : (missing)
  *   - resourceRightParenPosition (Range) : (missing)
  *   - finallyPosition (Range) : (missing)
  * 
  * Edges:
  *   - hasResources (struc::Variable, multiple) : (missing)
  *   - hasBlock (statm::Block, single) : (missing)
  *   - hasHandlers (statm::Handler, multiple) : (missing)
  *   - hasFinallyBlock (statm::Block, single) : (missing)
  */
  class Try : public Statement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Try(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Try();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Try & operator=(const Try&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Try(const Try&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Try& other, bool tryOnVirtualParent);

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
      * \brief Gives back the resourceLeftParenPosition of the node.
      * \return Returns with the resourceLeftParenPosition.
      */
      virtual const Range getResourceLeftParenPosition() const;

      /**
      * \brief Compare two node by resourceLeftParenPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByResourceLeftParenPosition(const Try& other) const;

      /**
      * \brief Gives back the resourceRightParenPosition of the node.
      * \return Returns with the resourceRightParenPosition.
      */
      virtual const Range getResourceRightParenPosition() const;

      /**
      * \brief Compare two node by resourceRightParenPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByResourceRightParenPosition(const Try& other) const;

      /**
      * \brief Gives back the finallyPosition of the node.
      * \return Returns with the finallyPosition.
      */
      virtual const Range getFinallyPosition() const;

      /**
      * \brief Compare two node by finallyPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByFinallyPosition(const Try& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the resourceLeftParenPosition of the node.
      * \param resourceLeftParenPosition [in] The new value of the resourceLeftParenPosition.
      */
      virtual void setResourceLeftParenPosition(const Range& _resourceLeftParenPosition);

      /**
      * \internal
      * \brief Sets the resourceRightParenPosition of the node.
      * \param resourceRightParenPosition [in] The new value of the resourceRightParenPosition.
      */
      virtual void setResourceRightParenPosition(const Range& _resourceRightParenPosition);

      /**
      * \internal
      * \brief Sets the finallyPosition of the node.
      * \param finallyPosition [in] The new value of the finallyPosition.
      */
      virtual void setFinallyPosition(const Range& _finallyPosition);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief todo (unknown). */
      MultiRange m_resourceLeftParenPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_resourceRightParenPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_finallyPosition;

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
      * \brief Gives back iterator for the hasResources edges.
      * \return Returns an iterator for the hasResources edges.
      */
      ListIterator<struc::Variable> getResourcesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasResources edges.
      * \return Returns an iterator for the hasResources edges.
      */
      ListIterator<struc::Variable> getResourcesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasResources edges or not.
      * \return Returns true if the node doesn't have any hasResources edge.
      */
      bool getResourcesIsEmpty() const;

      /**
      * \brief Gives back how many hasResources edges the node has.
      * \return Returns with the number of hasResources edges.
      */
      unsigned getResourcesSize() const;

      /**
      * \brief Gives back the pointer of the node the hasBlock edge points to.
      * \return Returns the end point of the hasBlock edge.
      */
      statm::Block* getBlock() const;

      /**
      * \brief Gives back iterator for the hasHandlers edges.
      * \return Returns an iterator for the hasHandlers edges.
      */
      ListIterator<statm::Handler> getHandlersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasHandlers edges.
      * \return Returns an iterator for the hasHandlers edges.
      */
      ListIterator<statm::Handler> getHandlersListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasHandlers edges or not.
      * \return Returns true if the node doesn't have any hasHandlers edge.
      */
      bool getHandlersIsEmpty() const;

      /**
      * \brief Gives back how many hasHandlers edges the node has.
      * \return Returns with the number of hasHandlers edges.
      */
      unsigned getHandlersSize() const;

      /**
      * \brief Gives back the pointer of the node the hasFinallyBlock edge points to.
      * \return Returns the end point of the hasFinallyBlock edge.
      */
      statm::Block* getFinallyBlock() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasResources edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasResources edge.
      */
      void addResources(const struc::Variable *node);

      /**
      * \brief Adds a new hasResources edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasResources edge.
      */
      void addResources(NodeId id);

      /**
      * \brief Remove the hasResources edge by id from the node.
      * \param id [in] The end point of the hasResources edge.
      */
      void removeResources(NodeId id);

      /**
      * \brief Remove the hasResources edge from the node.
      * \param node [in] The end point of the hasResources edge.
      */
      void removeResources(struc::Variable *node);

      /**
      * \brief Sets the hasBlock edge.
      * \param id [in] The new end point of the hasBlock edge.
      */
      void setBlock(NodeId id);

      /**
      * \brief Sets the hasBlock edge.
      * \param node [in] The new end point of the hasBlock edge.
      */
      void setBlock(Block *node);

      /**
      * \brief remove the hasBlock edge.
      */
      void removeBlock();

      /**
      * \brief Adds a new hasHandlers edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasHandlers edge.
      */
      void addHandlers(const Handler *node);

      /**
      * \brief Adds a new hasHandlers edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasHandlers edge.
      */
      void addHandlers(NodeId id);

      /**
      * \brief Remove the hasHandlers edge by id from the node.
      * \param id [in] The end point of the hasHandlers edge.
      */
      void removeHandlers(NodeId id);

      /**
      * \brief Remove the hasHandlers edge from the node.
      * \param node [in] The end point of the hasHandlers edge.
      */
      void removeHandlers(Handler *node);

      /**
      * \brief Sets the hasFinallyBlock edge.
      * \param id [in] The new end point of the hasFinallyBlock edge.
      */
      void setFinallyBlock(NodeId id);

      /**
      * \brief Sets the hasFinallyBlock edge.
      * \param node [in] The new end point of the hasFinallyBlock edge.
      */
      void setFinallyBlock(Block *node);

      /**
      * \brief remove the hasFinallyBlock edge.
      */
      void removeFinallyBlock();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasResources edge points to. */
      ListIterator<struc::Variable>::Container hasResourcesContainer;

      /** \internal \brief The id of the node the hasBlock edge points to. */
      NodeId m_hasBlock;

      /** \internal \brief Container stores the id of the nodes the hasHandlers edge points to. */
      ListIterator<statm::Handler>::Container hasHandlersContainer;

      /** \internal \brief The id of the node the hasFinallyBlock edge points to. */
      NodeId m_hasFinallyBlock;

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

