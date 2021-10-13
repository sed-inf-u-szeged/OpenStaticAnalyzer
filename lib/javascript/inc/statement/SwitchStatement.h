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

#ifndef _JAVASCRIPT_SwitchStatement_H_
#define _JAVASCRIPT_SwitchStatement_H_

#include "javascript/inc/javascript.h"

/**
* \file SwitchStatement.h
* \brief Contains declaration of the statement::SwitchStatement class.
* \brief The it get atributes from 
    * \brief base::Positioned
*/

namespace columbus { namespace javascript { namespace asg {
namespace statement {

  /**
  * \brief SwitchStatement class, which represents the statement::SwitchStatement node.
  * (missing)
  * 
  * Edges:
  *   - hasDiscriminant (expression::Expression, single) : (missing)
  *   - hasCases (statement::SwitchCase, multiple) : (missing)
  */
  class SwitchStatement : public Statement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      SwitchStatement(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~SwitchStatement();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      SwitchStatement & operator=(const SwitchStatement&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      SwitchStatement(const SwitchStatement&);

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
      * \brief Gives back the pointer of the node the hasDiscriminant edge points to.
      * \return Returns the end point of the hasDiscriminant edge.
      */
      expression::Expression* getDiscriminant() const;

      /**
      * \brief Gives back iterator for the hasCases edges.
      * \return Returns an iterator for the hasCases edges.
      */
      ListIterator<statement::SwitchCase> getCasesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasCases edges.
      * \return Returns an iterator for the hasCases edges.
      */
      ListIterator<statement::SwitchCase> getCasesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasCases edges or not.
      * \return Returns true if the node doesn't have any hasCases edge.
      */
      bool getCasesIsEmpty() const;

      /**
      * \brief Gives back how many hasCases edges the node has.
      * \return Returns with the number of hasCases edges.
      */
      unsigned getCasesSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasDiscriminant edge.
      * \param id [in] The new end point of the hasDiscriminant edge.
      */
      void setDiscriminant(NodeId id);

      /**
      * \brief Sets the hasDiscriminant edge.
      * \param node [in] The new end point of the hasDiscriminant edge.
      */
      void setDiscriminant(expression::Expression *node);

      /**
      * \brief remove the hasDiscriminant edge.
      */
      void removeDiscriminant();

      /**
      * \brief Adds a new hasCases edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasCases edge.
      */
      void addCases(const SwitchCase *node);

      /**
      * \brief Adds a new hasCases edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasCases edge.
      */
      void addCases(NodeId id);

      /**
      * \brief Remove the hasCases edge by id from the node.
      * \param id [in] The end point of the hasCases edge.
      */
      void removeCases(NodeId id);

      /**
      * \brief Remove the hasCases edge from the node.
      * \param node [in] The end point of the hasCases edge.
      */
      void removeCases(SwitchCase *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasDiscriminant edge points to. */
      NodeId m_hasDiscriminant;

      /** \internal \brief Container stores the id of the nodes the hasCases edge points to. */
      ListIterator<statement::SwitchCase>::Container hasCasesContainer;

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

