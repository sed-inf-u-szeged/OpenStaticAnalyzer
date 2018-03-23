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

#ifndef _CSHARP_AccessorDeclarationSyntax_H_
#define _CSHARP_AccessorDeclarationSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file AccessorDeclarationSyntax.h
* \brief Contains declaration of the structure::AccessorDeclarationSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief AccessorDeclarationSyntax class, which represents the structure::AccessorDeclarationSyntax node.
  * (missing)
  * 
  * Attributes:
  *   - identifier (String) : (missing)
  * 
  * Edges:
  *   - AttributeLists (structure::AttributeListSyntax, multiple) : (missing)
  *   - Body (statement::BlockSyntax, single) : (missing)
  */
  class AccessorDeclarationSyntax : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      AccessorDeclarationSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~AccessorDeclarationSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      AccessorDeclarationSyntax & operator=(const AccessorDeclarationSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      AccessorDeclarationSyntax(const AccessorDeclarationSyntax&);

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
      * \brief Gives back the pointer of the node the Body edge points to.
      * \return Returns the end point of the Body edge.
      */
      statement::BlockSyntax* getBody() const;


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
      * \brief Sets the Body edge.
      * \param id [in] The new end point of the Body edge.
      */
      void setBody(NodeId id);

      /**
      * \brief Sets the Body edge.
      * \param node [in] The new end point of the Body edge.
      */
      void setBody(statement::BlockSyntax *node);

      /**
      * \brief remove the Body edge.
      */
      void removeBody();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the AttributeLists edge points to. */
      ListIterator<structure::AttributeListSyntax>::Container AttributeListsContainer;

      /** \internal \brief The id of the node the Body edge points to. */
      NodeId m_Body;

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

