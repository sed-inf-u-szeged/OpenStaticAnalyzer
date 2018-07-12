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

#ifndef _CSHARP_SwitchSectionSyntax_H_
#define _CSHARP_SwitchSectionSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file SwitchSectionSyntax.h
* \brief Contains declaration of the structure::SwitchSectionSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief SwitchSectionSyntax class, which represents the structure::SwitchSectionSyntax node.
  * (missing)
  * 
  * Edges:
  *   - Labels (structure::SwitchLabelSyntax, multiple) : (missing)
  *   - Statements (statement::StatementSyntax, multiple) : (missing)
  */
  class SwitchSectionSyntax : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      SwitchSectionSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~SwitchSectionSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      SwitchSectionSyntax & operator=(const SwitchSectionSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      SwitchSectionSyntax(const SwitchSectionSyntax&);

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
      * \brief Gives back iterator for the Labels edges.
      * \return Returns an iterator for the Labels edges.
      */
      ListIterator<structure::SwitchLabelSyntax> getLabelsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Labels edges.
      * \return Returns an iterator for the Labels edges.
      */
      ListIterator<structure::SwitchLabelSyntax> getLabelsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Labels edges or not.
      * \return Returns true if the node doesn't have any Labels edge.
      */
      bool getLabelsIsEmpty() const;

      /**
      * \brief Gives back how many Labels edges the node has.
      * \return Returns with the number of Labels edges.
      */
      unsigned getLabelsSize() const;

      /**
      * \brief Gives back iterator for the Statements edges.
      * \return Returns an iterator for the Statements edges.
      */
      ListIterator<statement::StatementSyntax> getStatementsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Statements edges.
      * \return Returns an iterator for the Statements edges.
      */
      ListIterator<statement::StatementSyntax> getStatementsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Statements edges or not.
      * \return Returns true if the node doesn't have any Statements edge.
      */
      bool getStatementsIsEmpty() const;

      /**
      * \brief Gives back how many Statements edges the node has.
      * \return Returns with the number of Statements edges.
      */
      unsigned getStatementsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new Labels edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Labels edge.
      */
      void addLabels(const SwitchLabelSyntax *node);

      /**
      * \brief Adds a new Labels edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Labels edge.
      */
      void addLabels(NodeId id);

      /**
      * \brief Remove the Labels edge by id from the node.
      * \param id [in] The end point of the Labels edge.
      */
      void removeLabels(NodeId id);

      /**
      * \brief Remove the Labels edge from the node.
      * \param node [in] The end point of the Labels edge.
      */
      void removeLabels(SwitchLabelSyntax *node);

      /**
      * \brief Adds a new Statements edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Statements edge.
      */
      void addStatements(const statement::StatementSyntax *node);

      /**
      * \brief Adds a new Statements edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Statements edge.
      */
      void addStatements(NodeId id);

      /**
      * \brief Remove the Statements edge by id from the node.
      * \param id [in] The end point of the Statements edge.
      */
      void removeStatements(NodeId id);

      /**
      * \brief Remove the Statements edge from the node.
      * \param node [in] The end point of the Statements edge.
      */
      void removeStatements(statement::StatementSyntax *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the Labels edge points to. */
      ListIterator<structure::SwitchLabelSyntax>::Container LabelsContainer;

      /** \internal \brief Container stores the id of the nodes the Statements edge points to. */
      ListIterator<statement::StatementSyntax>::Container StatementsContainer;

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

