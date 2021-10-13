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

#ifndef _CSHARP_LocalFunctionStatementSyntax_H_
#define _CSHARP_LocalFunctionStatementSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file LocalFunctionStatementSyntax.h
* \brief Contains declaration of the statement::LocalFunctionStatementSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace statement {

  /**
  * \brief LocalFunctionStatementSyntax class, which represents the statement::LocalFunctionStatementSyntax node.
  * (missing)
  * 
  * Attributes:
  *   - identifier (String) : (missing)
  * 
  * Edges:
  *   - Body (statement::BlockSyntax, single) : (missing)
  *   - ConstraintClauses (structure::TypeParameterConstraintClauseSyntax, multiple) : (missing)
  *   - ExpressionBody (structure::ArrowExpressionClauseSyntax, single) : (missing)
  *   - ParameterList (structure::ParameterListSyntax, single) : (missing)
  *   - ReturnType (expression::TypeSyntax, single) : (missing)
  *   - TypeParameterList (structure::TypeParameterListSyntax, single) : (missing)
  */
  class LocalFunctionStatementSyntax : public StatementSyntax {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      LocalFunctionStatementSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~LocalFunctionStatementSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      LocalFunctionStatementSyntax & operator=(const LocalFunctionStatementSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      LocalFunctionStatementSyntax(const LocalFunctionStatementSyntax&);

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
      * \brief Gives back the identifier of the node.
      * \return Returns with the identifier.
      */
      const std::string& getIdentifier() const;

      /**
      * \brief Gives back the Key of identifier of the node.
      * \return Returns with the Key of the identifier.
      */
      Key getIdentifierKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the identifier of the node.
      * \param identifier [in] The new value of the identifier.
      */
      void setIdentifier(const std::string& _identifier);

      /**
      * \internal
      * \brief Sets the identifier of the node.
      * \param identifier [in] The new Key of the identifier.
      */
      void setIdentifierKey(Key _identifier);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `identifier`. */
      Key m_identifier;

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
      * \brief Gives back the pointer of the node the Body edge points to.
      * \return Returns the end point of the Body edge.
      */
      statement::BlockSyntax* getBody() const;

      /**
      * \brief Gives back iterator for the ConstraintClauses edges.
      * \return Returns an iterator for the ConstraintClauses edges.
      */
      ListIterator<structure::TypeParameterConstraintClauseSyntax> getConstraintClausesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the ConstraintClauses edges.
      * \return Returns an iterator for the ConstraintClauses edges.
      */
      ListIterator<structure::TypeParameterConstraintClauseSyntax> getConstraintClausesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has ConstraintClauses edges or not.
      * \return Returns true if the node doesn't have any ConstraintClauses edge.
      */
      bool getConstraintClausesIsEmpty() const;

      /**
      * \brief Gives back how many ConstraintClauses edges the node has.
      * \return Returns with the number of ConstraintClauses edges.
      */
      unsigned getConstraintClausesSize() const;

      /**
      * \brief Gives back the pointer of the node the ExpressionBody edge points to.
      * \return Returns the end point of the ExpressionBody edge.
      */
      structure::ArrowExpressionClauseSyntax* getExpressionBody() const;

      /**
      * \brief Gives back the pointer of the node the ParameterList edge points to.
      * \return Returns the end point of the ParameterList edge.
      */
      structure::ParameterListSyntax* getParameterList() const;

      /**
      * \brief Gives back the pointer of the node the ReturnType edge points to.
      * \return Returns the end point of the ReturnType edge.
      */
      expression::TypeSyntax* getReturnType() const;

      /**
      * \brief Gives back the pointer of the node the TypeParameterList edge points to.
      * \return Returns the end point of the TypeParameterList edge.
      */
      structure::TypeParameterListSyntax* getTypeParameterList() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the Body edge.
      * \param id [in] The new end point of the Body edge.
      */
      void setBody(NodeId id);

      /**
      * \brief Sets the Body edge.
      * \param node [in] The new end point of the Body edge.
      */
      void setBody(BlockSyntax *node);

      /**
      * \brief remove the Body edge.
      */
      void removeBody();

      /**
      * \brief Adds a new ConstraintClauses edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new ConstraintClauses edge.
      */
      void addConstraintClauses(const structure::TypeParameterConstraintClauseSyntax *node);

      /**
      * \brief Adds a new ConstraintClauses edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new ConstraintClauses edge.
      */
      void addConstraintClauses(NodeId id);

      /**
      * \brief Remove the ConstraintClauses edge by id from the node.
      * \param id [in] The end point of the ConstraintClauses edge.
      */
      void removeConstraintClauses(NodeId id);

      /**
      * \brief Remove the ConstraintClauses edge from the node.
      * \param node [in] The end point of the ConstraintClauses edge.
      */
      void removeConstraintClauses(structure::TypeParameterConstraintClauseSyntax *node);

      /**
      * \brief Sets the ExpressionBody edge.
      * \param id [in] The new end point of the ExpressionBody edge.
      */
      void setExpressionBody(NodeId id);

      /**
      * \brief Sets the ExpressionBody edge.
      * \param node [in] The new end point of the ExpressionBody edge.
      */
      void setExpressionBody(structure::ArrowExpressionClauseSyntax *node);

      /**
      * \brief remove the ExpressionBody edge.
      */
      void removeExpressionBody();

      /**
      * \brief Sets the ParameterList edge.
      * \param id [in] The new end point of the ParameterList edge.
      */
      void setParameterList(NodeId id);

      /**
      * \brief Sets the ParameterList edge.
      * \param node [in] The new end point of the ParameterList edge.
      */
      void setParameterList(structure::ParameterListSyntax *node);

      /**
      * \brief remove the ParameterList edge.
      */
      void removeParameterList();

      /**
      * \brief Sets the ReturnType edge.
      * \param id [in] The new end point of the ReturnType edge.
      */
      void setReturnType(NodeId id);

      /**
      * \brief Sets the ReturnType edge.
      * \param node [in] The new end point of the ReturnType edge.
      */
      void setReturnType(expression::TypeSyntax *node);

      /**
      * \brief remove the ReturnType edge.
      */
      void removeReturnType();

      /**
      * \brief Sets the TypeParameterList edge.
      * \param id [in] The new end point of the TypeParameterList edge.
      */
      void setTypeParameterList(NodeId id);

      /**
      * \brief Sets the TypeParameterList edge.
      * \param node [in] The new end point of the TypeParameterList edge.
      */
      void setTypeParameterList(structure::TypeParameterListSyntax *node);

      /**
      * \brief remove the TypeParameterList edge.
      */
      void removeTypeParameterList();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the Body edge points to. */
      NodeId m_Body;

      /** \internal \brief Container stores the id of the nodes the ConstraintClauses edge points to. */
      ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container ConstraintClausesContainer;

      /** \internal \brief The id of the node the ExpressionBody edge points to. */
      NodeId m_ExpressionBody;

      /** \internal \brief The id of the node the ParameterList edge points to. */
      NodeId m_ParameterList;

      /** \internal \brief The id of the node the ReturnType edge points to. */
      NodeId m_ReturnType;

      /** \internal \brief The id of the node the TypeParameterList edge points to. */
      NodeId m_TypeParameterList;

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

