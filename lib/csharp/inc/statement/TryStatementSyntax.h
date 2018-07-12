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

#ifndef _CSHARP_TryStatementSyntax_H_
#define _CSHARP_TryStatementSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file TryStatementSyntax.h
* \brief Contains declaration of the statement::TryStatementSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace statement {

  /**
  * \brief TryStatementSyntax class, which represents the statement::TryStatementSyntax node.
  * (missing)
  * 
  * Edges:
  *   - Block (statement::BlockSyntax, single) : (missing)
  *   - Catches (structure::CatchClauseSyntax, multiple) : (missing)
  *   - Finally (structure::FinallyClauseSyntax, single) : (missing)
  */
  class TryStatementSyntax : public StatementSyntax {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      TryStatementSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~TryStatementSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      TryStatementSyntax & operator=(const TryStatementSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      TryStatementSyntax(const TryStatementSyntax&);

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
      * \brief Gives back the pointer of the node the Block edge points to.
      * \return Returns the end point of the Block edge.
      */
      statement::BlockSyntax* getBlock() const;

      /**
      * \brief Gives back iterator for the Catches edges.
      * \return Returns an iterator for the Catches edges.
      */
      ListIterator<structure::CatchClauseSyntax> getCatchesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Catches edges.
      * \return Returns an iterator for the Catches edges.
      */
      ListIterator<structure::CatchClauseSyntax> getCatchesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Catches edges or not.
      * \return Returns true if the node doesn't have any Catches edge.
      */
      bool getCatchesIsEmpty() const;

      /**
      * \brief Gives back how many Catches edges the node has.
      * \return Returns with the number of Catches edges.
      */
      unsigned getCatchesSize() const;

      /**
      * \brief Gives back the pointer of the node the Finally edge points to.
      * \return Returns the end point of the Finally edge.
      */
      structure::FinallyClauseSyntax* getFinally() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the Block edge.
      * \param id [in] The new end point of the Block edge.
      */
      void setBlock(NodeId id);

      /**
      * \brief Sets the Block edge.
      * \param node [in] The new end point of the Block edge.
      */
      void setBlock(BlockSyntax *node);

      /**
      * \brief remove the Block edge.
      */
      void removeBlock();

      /**
      * \brief Adds a new Catches edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Catches edge.
      */
      void addCatches(const structure::CatchClauseSyntax *node);

      /**
      * \brief Adds a new Catches edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Catches edge.
      */
      void addCatches(NodeId id);

      /**
      * \brief Remove the Catches edge by id from the node.
      * \param id [in] The end point of the Catches edge.
      */
      void removeCatches(NodeId id);

      /**
      * \brief Remove the Catches edge from the node.
      * \param node [in] The end point of the Catches edge.
      */
      void removeCatches(structure::CatchClauseSyntax *node);

      /**
      * \brief Sets the Finally edge.
      * \param id [in] The new end point of the Finally edge.
      */
      void setFinally(NodeId id);

      /**
      * \brief Sets the Finally edge.
      * \param node [in] The new end point of the Finally edge.
      */
      void setFinally(structure::FinallyClauseSyntax *node);

      /**
      * \brief remove the Finally edge.
      */
      void removeFinally();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the Block edge points to. */
      NodeId m_Block;

      /** \internal \brief Container stores the id of the nodes the Catches edge points to. */
      ListIterator<structure::CatchClauseSyntax>::Container CatchesContainer;

      /** \internal \brief The id of the node the Finally edge points to. */
      NodeId m_Finally;

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


      friend class csharp::asg::Factory;
      friend class csharp::asg::VisitorSave;
  };

} 


}}}
#endif

