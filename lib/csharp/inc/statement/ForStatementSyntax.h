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

#ifndef _CSHARP_ForStatementSyntax_H_
#define _CSHARP_ForStatementSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file ForStatementSyntax.h
* \brief Contains declaration of the statement::ForStatementSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace statement {

  /**
  * \brief ForStatementSyntax class, which represents the statement::ForStatementSyntax node.
  * (missing)
  * 
  * Edges:
  *   - Condition (expression::ExpressionSyntax, single) : (missing)
  *   - Declaration (structure::VariableDeclarationSyntax, single) : (missing)
  *   - Incrementors (expression::ExpressionSyntax, multiple) : (missing)
  *   - Initializers (expression::ExpressionSyntax, multiple) : (missing)
  *   - Statement (statement::StatementSyntax, single) : (missing)
  */
  class ForStatementSyntax : public StatementSyntax {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ForStatementSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ForStatementSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      ForStatementSyntax & operator=(const ForStatementSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      ForStatementSyntax(const ForStatementSyntax&);

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
      * \brief Gives back the pointer of the node the Condition edge points to.
      * \return Returns the end point of the Condition edge.
      */
      expression::ExpressionSyntax* getCondition() const;

      /**
      * \brief Gives back the pointer of the node the Declaration edge points to.
      * \return Returns the end point of the Declaration edge.
      */
      structure::VariableDeclarationSyntax* getDeclaration() const;

      /**
      * \brief Gives back iterator for the Incrementors edges.
      * \return Returns an iterator for the Incrementors edges.
      */
      ListIterator<expression::ExpressionSyntax> getIncrementorsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Incrementors edges.
      * \return Returns an iterator for the Incrementors edges.
      */
      ListIterator<expression::ExpressionSyntax> getIncrementorsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Incrementors edges or not.
      * \return Returns true if the node doesn't have any Incrementors edge.
      */
      bool getIncrementorsIsEmpty() const;

      /**
      * \brief Gives back how many Incrementors edges the node has.
      * \return Returns with the number of Incrementors edges.
      */
      unsigned getIncrementorsSize() const;

      /**
      * \brief Gives back iterator for the Initializers edges.
      * \return Returns an iterator for the Initializers edges.
      */
      ListIterator<expression::ExpressionSyntax> getInitializersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Initializers edges.
      * \return Returns an iterator for the Initializers edges.
      */
      ListIterator<expression::ExpressionSyntax> getInitializersListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Initializers edges or not.
      * \return Returns true if the node doesn't have any Initializers edge.
      */
      bool getInitializersIsEmpty() const;

      /**
      * \brief Gives back how many Initializers edges the node has.
      * \return Returns with the number of Initializers edges.
      */
      unsigned getInitializersSize() const;

      /**
      * \brief Gives back the pointer of the node the Statement edge points to.
      * \return Returns the end point of the Statement edge.
      */
      statement::StatementSyntax* getStatement() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the Condition edge.
      * \param id [in] The new end point of the Condition edge.
      */
      void setCondition(NodeId id);

      /**
      * \brief Sets the Condition edge.
      * \param node [in] The new end point of the Condition edge.
      */
      void setCondition(expression::ExpressionSyntax *node);

      /**
      * \brief remove the Condition edge.
      */
      void removeCondition();

      /**
      * \brief Sets the Declaration edge.
      * \param id [in] The new end point of the Declaration edge.
      */
      void setDeclaration(NodeId id);

      /**
      * \brief Sets the Declaration edge.
      * \param node [in] The new end point of the Declaration edge.
      */
      void setDeclaration(structure::VariableDeclarationSyntax *node);

      /**
      * \brief remove the Declaration edge.
      */
      void removeDeclaration();

      /**
      * \brief Adds a new Incrementors edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Incrementors edge.
      */
      void addIncrementors(const expression::ExpressionSyntax *node);

      /**
      * \brief Adds a new Incrementors edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Incrementors edge.
      */
      void addIncrementors(NodeId id);

      /**
      * \brief Remove the Incrementors edge by id from the node.
      * \param id [in] The end point of the Incrementors edge.
      */
      void removeIncrementors(NodeId id);

      /**
      * \brief Remove the Incrementors edge from the node.
      * \param node [in] The end point of the Incrementors edge.
      */
      void removeIncrementors(expression::ExpressionSyntax *node);

      /**
      * \brief Adds a new Initializers edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Initializers edge.
      */
      void addInitializers(const expression::ExpressionSyntax *node);

      /**
      * \brief Adds a new Initializers edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Initializers edge.
      */
      void addInitializers(NodeId id);

      /**
      * \brief Remove the Initializers edge by id from the node.
      * \param id [in] The end point of the Initializers edge.
      */
      void removeInitializers(NodeId id);

      /**
      * \brief Remove the Initializers edge from the node.
      * \param node [in] The end point of the Initializers edge.
      */
      void removeInitializers(expression::ExpressionSyntax *node);

      /**
      * \brief Sets the Statement edge.
      * \param id [in] The new end point of the Statement edge.
      */
      void setStatement(NodeId id);

      /**
      * \brief Sets the Statement edge.
      * \param node [in] The new end point of the Statement edge.
      */
      void setStatement(StatementSyntax *node);

      /**
      * \brief remove the Statement edge.
      */
      void removeStatement();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the Condition edge points to. */
      NodeId m_Condition;

      /** \internal \brief The id of the node the Declaration edge points to. */
      NodeId m_Declaration;

      /** \internal \brief Container stores the id of the nodes the Incrementors edge points to. */
      ListIterator<expression::ExpressionSyntax>::Container IncrementorsContainer;

      /** \internal \brief Container stores the id of the nodes the Initializers edge points to. */
      ListIterator<expression::ExpressionSyntax>::Container InitializersContainer;

      /** \internal \brief The id of the node the Statement edge points to. */
      NodeId m_Statement;

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

