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

#ifndef _CSHARP_ArrayRankSpecifierSyntax_H_
#define _CSHARP_ArrayRankSpecifierSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file ArrayRankSpecifierSyntax.h
* \brief Contains declaration of the structure::ArrayRankSpecifierSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief ArrayRankSpecifierSyntax class, which represents the structure::ArrayRankSpecifierSyntax node.
  * (missing)
  * 
  * Edges:
  *   - Sizes (expression::ExpressionSyntax, multiple) : (missing)
  */
  class ArrayRankSpecifierSyntax : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ArrayRankSpecifierSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ArrayRankSpecifierSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      ArrayRankSpecifierSyntax & operator=(const ArrayRankSpecifierSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      ArrayRankSpecifierSyntax(const ArrayRankSpecifierSyntax&);

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
      * \brief Gives back iterator for the Sizes edges.
      * \return Returns an iterator for the Sizes edges.
      */
      ListIterator<expression::ExpressionSyntax> getSizesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Sizes edges.
      * \return Returns an iterator for the Sizes edges.
      */
      ListIterator<expression::ExpressionSyntax> getSizesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Sizes edges or not.
      * \return Returns true if the node doesn't have any Sizes edge.
      */
      bool getSizesIsEmpty() const;

      /**
      * \brief Gives back how many Sizes edges the node has.
      * \return Returns with the number of Sizes edges.
      */
      unsigned getSizesSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new Sizes edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Sizes edge.
      */
      void addSizes(const expression::ExpressionSyntax *node);

      /**
      * \brief Adds a new Sizes edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Sizes edge.
      */
      void addSizes(NodeId id);

      /**
      * \brief Remove the Sizes edge by id from the node.
      * \param id [in] The end point of the Sizes edge.
      */
      void removeSizes(NodeId id);

      /**
      * \brief Remove the Sizes edge from the node.
      * \param node [in] The end point of the Sizes edge.
      */
      void removeSizes(expression::ExpressionSyntax *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the Sizes edge points to. */
      ListIterator<expression::ExpressionSyntax>::Container SizesContainer;

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

