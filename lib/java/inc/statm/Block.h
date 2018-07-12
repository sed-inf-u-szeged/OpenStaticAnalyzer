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

#ifndef _JAVA_Block_H_
#define _JAVA_Block_H_

#include "java/inc/java.h"

/**
* \file Block.h
* \brief Contains declaration of the statm::Block class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace statm {

  /**
  * \brief Block class, which represents the statm::Block node.
  * (missing)
  * 
  * Edges:
  *   - hasStatements (statm::Statement, multiple) : (missing)
  */
  class Block : public Statement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Block(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Block();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Block & operator=(const Block&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Block(const Block&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Block& other, bool tryOnVirtualParent);

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
      * \brief Gives back iterator for the hasStatements edges.
      * \return Returns an iterator for the hasStatements edges.
      */
      ListIterator<statm::Statement> getStatementsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasStatements edges.
      * \return Returns an iterator for the hasStatements edges.
      */
      ListIterator<statm::Statement> getStatementsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasStatements edges or not.
      * \return Returns true if the node doesn't have any hasStatements edge.
      */
      bool getStatementsIsEmpty() const;

      /**
      * \brief Gives back how many hasStatements edges the node has.
      * \return Returns with the number of hasStatements edges.
      */
      unsigned getStatementsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasStatements edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasStatements edge.
      */
      void addStatements(const Statement *node);

      /**
      * \brief Adds a new hasStatements edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasStatements edge.
      */
      void addStatements(NodeId id);

      /**
      * \brief Remove the hasStatements edge by id from the node.
      * \param id [in] The end point of the hasStatements edge.
      */
      void removeStatements(NodeId id);

      /**
      * \brief Remove the hasStatements edge from the node.
      * \param node [in] The end point of the hasStatements edge.
      */
      void removeStatements(Statement *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasStatements edge points to. */
      ListIterator<statm::Statement>::Container hasStatementsContainer;

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

