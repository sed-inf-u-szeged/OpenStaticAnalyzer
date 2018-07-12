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

#ifndef _CSHARP_TypeDeclarationSyntax_H_
#define _CSHARP_TypeDeclarationSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file TypeDeclarationSyntax.h
* \brief Contains declaration of the structure::TypeDeclarationSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief TypeDeclarationSyntax class, which represents the structure::TypeDeclarationSyntax node.
  * (missing)
  * 
  * Edges:
  *   - ConstraintClauses (structure::TypeParameterConstraintClauseSyntax, multiple) : (missing)
  *   - Members (structure::MemberDeclarationSyntax, multiple) : (missing)
  *   - TypeParameterList (structure::TypeParameterListSyntax, single) : (missing)
  */
  class TypeDeclarationSyntax : public BaseTypeDeclarationSyntax {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      TypeDeclarationSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~TypeDeclarationSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      TypeDeclarationSyntax & operator=(const TypeDeclarationSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      TypeDeclarationSyntax(const TypeDeclarationSyntax&);

    public:
      /**
      * \brief Gives back the NodeKind of the node.
      * \return Returns with the NodeKind.
      */
      virtual NodeKind getNodeKind() const = 0;

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
      * \brief Gives back iterator for the Members edges.
      * \return Returns an iterator for the Members edges.
      */
      ListIterator<structure::MemberDeclarationSyntax> getMembersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Members edges.
      * \return Returns an iterator for the Members edges.
      */
      ListIterator<structure::MemberDeclarationSyntax> getMembersListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Members edges or not.
      * \return Returns true if the node doesn't have any Members edge.
      */
      bool getMembersIsEmpty() const;

      /**
      * \brief Gives back how many Members edges the node has.
      * \return Returns with the number of Members edges.
      */
      unsigned getMembersSize() const;

      /**
      * \brief Gives back the pointer of the node the TypeParameterList edge points to.
      * \return Returns the end point of the TypeParameterList edge.
      */
      structure::TypeParameterListSyntax* getTypeParameterList() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new ConstraintClauses edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new ConstraintClauses edge.
      */
      void addConstraintClauses(const TypeParameterConstraintClauseSyntax *node);

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
      void removeConstraintClauses(TypeParameterConstraintClauseSyntax *node);

      /**
      * \brief Adds a new Members edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Members edge.
      */
      void addMembers(const MemberDeclarationSyntax *node);

      /**
      * \brief Adds a new Members edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Members edge.
      */
      void addMembers(NodeId id);

      /**
      * \brief Remove the Members edge by id from the node.
      * \param id [in] The end point of the Members edge.
      */
      void removeMembers(NodeId id);

      /**
      * \brief Remove the Members edge from the node.
      * \param node [in] The end point of the Members edge.
      */
      void removeMembers(MemberDeclarationSyntax *node);

      /**
      * \brief Sets the TypeParameterList edge.
      * \param id [in] The new end point of the TypeParameterList edge.
      */
      void setTypeParameterList(NodeId id);

      /**
      * \brief Sets the TypeParameterList edge.
      * \param node [in] The new end point of the TypeParameterList edge.
      */
      void setTypeParameterList(TypeParameterListSyntax *node);

      /**
      * \brief remove the TypeParameterList edge.
      */
      void removeTypeParameterList();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the ConstraintClauses edge points to. */
      ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container ConstraintClausesContainer;

      /** \internal \brief Container stores the id of the nodes the Members edge points to. */
      ListIterator<structure::MemberDeclarationSyntax>::Container MembersContainer;

      /** \internal \brief The id of the node the TypeParameterList edge points to. */
      NodeId m_TypeParameterList;

    public:

      // ---------- Accept functions for Visitor it now pure virtual ----------

      /**
      * \brief It calls the appropriate visit method of the given visitor in the child nodes.
      * \param visitor [in] The used visitor.
      */
      virtual void accept(Visitor& visitor) const = 0;

      /**
      * \brief It calls the appropriate visitEnd method of the given visitor in the child nodes.
      * \param visitor [in] The used visitor.
      */
      virtual void acceptEnd(Visitor& visitor) const = 0;

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

