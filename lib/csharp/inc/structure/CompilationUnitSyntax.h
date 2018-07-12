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

#ifndef _CSHARP_CompilationUnitSyntax_H_
#define _CSHARP_CompilationUnitSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file CompilationUnitSyntax.h
* \brief Contains declaration of the structure::CompilationUnitSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief CompilationUnitSyntax class, which represents the structure::CompilationUnitSyntax node.
  * (missing)
  * 
  * Edges:
  *   - AttributeLists (structure::AttributeListSyntax, multiple) : (missing)
  *   - Externs (structure::ExternAliasDirectiveSyntax, multiple) : (missing)
  *   - Members (structure::MemberDeclarationSyntax, multiple) : (missing)
  *   - Usings (structure::UsingDirectiveSyntax, multiple) : (missing)
  */
  class CompilationUnitSyntax : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      CompilationUnitSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~CompilationUnitSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      CompilationUnitSyntax & operator=(const CompilationUnitSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      CompilationUnitSyntax(const CompilationUnitSyntax&);

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
      * \brief Gives back iterator for the AttributeLists edges.
      * \return Returns an iterator for the AttributeLists edges.
      */
      ListIterator<structure::AttributeListSyntax> getAttributeListsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the AttributeLists edges.
      * \return Returns an iterator for the AttributeLists edges.
      */
      ListIterator<structure::AttributeListSyntax> getAttributeListsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has AttributeLists edges or not.
      * \return Returns true if the node doesn't have any AttributeLists edge.
      */
      bool getAttributeListsIsEmpty() const;

      /**
      * \brief Gives back how many AttributeLists edges the node has.
      * \return Returns with the number of AttributeLists edges.
      */
      unsigned getAttributeListsSize() const;

      /**
      * \brief Gives back iterator for the Externs edges.
      * \return Returns an iterator for the Externs edges.
      */
      ListIterator<structure::ExternAliasDirectiveSyntax> getExternsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Externs edges.
      * \return Returns an iterator for the Externs edges.
      */
      ListIterator<structure::ExternAliasDirectiveSyntax> getExternsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Externs edges or not.
      * \return Returns true if the node doesn't have any Externs edge.
      */
      bool getExternsIsEmpty() const;

      /**
      * \brief Gives back how many Externs edges the node has.
      * \return Returns with the number of Externs edges.
      */
      unsigned getExternsSize() const;

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
      * \brief Gives back iterator for the Usings edges.
      * \return Returns an iterator for the Usings edges.
      */
      ListIterator<structure::UsingDirectiveSyntax> getUsingsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Usings edges.
      * \return Returns an iterator for the Usings edges.
      */
      ListIterator<structure::UsingDirectiveSyntax> getUsingsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Usings edges or not.
      * \return Returns true if the node doesn't have any Usings edge.
      */
      bool getUsingsIsEmpty() const;

      /**
      * \brief Gives back how many Usings edges the node has.
      * \return Returns with the number of Usings edges.
      */
      unsigned getUsingsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new AttributeLists edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new AttributeLists edge.
      */
      void addAttributeLists(const AttributeListSyntax *node);

      /**
      * \brief Adds a new AttributeLists edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new AttributeLists edge.
      */
      void addAttributeLists(NodeId id);

      /**
      * \brief Remove the AttributeLists edge by id from the node.
      * \param id [in] The end point of the AttributeLists edge.
      */
      void removeAttributeLists(NodeId id);

      /**
      * \brief Remove the AttributeLists edge from the node.
      * \param node [in] The end point of the AttributeLists edge.
      */
      void removeAttributeLists(AttributeListSyntax *node);

      /**
      * \brief Adds a new Externs edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Externs edge.
      */
      void addExterns(const ExternAliasDirectiveSyntax *node);

      /**
      * \brief Adds a new Externs edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Externs edge.
      */
      void addExterns(NodeId id);

      /**
      * \brief Remove the Externs edge by id from the node.
      * \param id [in] The end point of the Externs edge.
      */
      void removeExterns(NodeId id);

      /**
      * \brief Remove the Externs edge from the node.
      * \param node [in] The end point of the Externs edge.
      */
      void removeExterns(ExternAliasDirectiveSyntax *node);

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
      * \brief Adds a new Usings edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Usings edge.
      */
      void addUsings(const UsingDirectiveSyntax *node);

      /**
      * \brief Adds a new Usings edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Usings edge.
      */
      void addUsings(NodeId id);

      /**
      * \brief Remove the Usings edge by id from the node.
      * \param id [in] The end point of the Usings edge.
      */
      void removeUsings(NodeId id);

      /**
      * \brief Remove the Usings edge from the node.
      * \param node [in] The end point of the Usings edge.
      */
      void removeUsings(UsingDirectiveSyntax *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the AttributeLists edge points to. */
      ListIterator<structure::AttributeListSyntax>::Container AttributeListsContainer;

      /** \internal \brief Container stores the id of the nodes the Externs edge points to. */
      ListIterator<structure::ExternAliasDirectiveSyntax>::Container ExternsContainer;

      /** \internal \brief Container stores the id of the nodes the Members edge points to. */
      ListIterator<structure::MemberDeclarationSyntax>::Container MembersContainer;

      /** \internal \brief Container stores the id of the nodes the Usings edge points to. */
      ListIterator<structure::UsingDirectiveSyntax>::Container UsingsContainer;

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

