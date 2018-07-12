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

#ifndef _CSHARP_BasePropertyDeclarationSyntax_H_
#define _CSHARP_BasePropertyDeclarationSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file BasePropertyDeclarationSyntax.h
* \brief Contains declaration of the structure::BasePropertyDeclarationSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief BasePropertyDeclarationSyntax class, which represents the structure::BasePropertyDeclarationSyntax node.
  * (missing)
  * 
  * Edges:
  *   - AccessorList (structure::AccessorListSyntax, single) : (missing)
  *   - AttributeLists (structure::AttributeListSyntax, multiple) : (missing)
  *   - ExplicitInterfaceSpecifier (structure::ExplicitInterfaceSpecifierSyntax, single) : (missing)
  *   - Type (expression::TypeSyntax, single) : (missing)
  */
  class BasePropertyDeclarationSyntax : public MemberDeclarationSyntax {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      BasePropertyDeclarationSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~BasePropertyDeclarationSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      BasePropertyDeclarationSyntax & operator=(const BasePropertyDeclarationSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      BasePropertyDeclarationSyntax(const BasePropertyDeclarationSyntax&);

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
      * \brief Gives back the pointer of the node the AccessorList edge points to.
      * \return Returns the end point of the AccessorList edge.
      */
      structure::AccessorListSyntax* getAccessorList() const;

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
      * \brief Gives back the pointer of the node the ExplicitInterfaceSpecifier edge points to.
      * \return Returns the end point of the ExplicitInterfaceSpecifier edge.
      */
      structure::ExplicitInterfaceSpecifierSyntax* getExplicitInterfaceSpecifier() const;

      /**
      * \brief Gives back the pointer of the node the Type edge points to.
      * \return Returns the end point of the Type edge.
      */
      expression::TypeSyntax* getType() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the AccessorList edge.
      * \param id [in] The new end point of the AccessorList edge.
      */
      void setAccessorList(NodeId id);

      /**
      * \brief Sets the AccessorList edge.
      * \param node [in] The new end point of the AccessorList edge.
      */
      void setAccessorList(AccessorListSyntax *node);

      /**
      * \brief remove the AccessorList edge.
      */
      void removeAccessorList();

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
      * \brief Sets the ExplicitInterfaceSpecifier edge.
      * \param id [in] The new end point of the ExplicitInterfaceSpecifier edge.
      */
      void setExplicitInterfaceSpecifier(NodeId id);

      /**
      * \brief Sets the ExplicitInterfaceSpecifier edge.
      * \param node [in] The new end point of the ExplicitInterfaceSpecifier edge.
      */
      void setExplicitInterfaceSpecifier(ExplicitInterfaceSpecifierSyntax *node);

      /**
      * \brief remove the ExplicitInterfaceSpecifier edge.
      */
      void removeExplicitInterfaceSpecifier();

      /**
      * \brief Sets the Type edge.
      * \param id [in] The new end point of the Type edge.
      */
      void setType(NodeId id);

      /**
      * \brief Sets the Type edge.
      * \param node [in] The new end point of the Type edge.
      */
      void setType(expression::TypeSyntax *node);

      /**
      * \brief remove the Type edge.
      */
      void removeType();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the AccessorList edge points to. */
      NodeId m_AccessorList;

      /** \internal \brief Container stores the id of the nodes the AttributeLists edge points to. */
      ListIterator<structure::AttributeListSyntax>::Container AttributeListsContainer;

      /** \internal \brief The id of the node the ExplicitInterfaceSpecifier edge points to. */
      NodeId m_ExplicitInterfaceSpecifier;

      /** \internal \brief The id of the node the Type edge points to. */
      NodeId m_Type;

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

