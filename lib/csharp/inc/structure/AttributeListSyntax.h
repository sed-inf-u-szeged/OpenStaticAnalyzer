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

#ifndef _CSHARP_AttributeListSyntax_H_
#define _CSHARP_AttributeListSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file AttributeListSyntax.h
* \brief Contains declaration of the structure::AttributeListSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief AttributeListSyntax class, which represents the structure::AttributeListSyntax node.
  * (missing)
  * 
  * Edges:
  *   - Attributes (structure::AttributeSyntax, multiple) : (missing)
  *   - Target (structure::AttributeTargetSpecifierSyntax, single) : (missing)
  */
  class AttributeListSyntax : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      AttributeListSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~AttributeListSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      AttributeListSyntax & operator=(const AttributeListSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      AttributeListSyntax(const AttributeListSyntax&);

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
      * \brief Gives back iterator for the Attributes edges.
      * \return Returns an iterator for the Attributes edges.
      */
      ListIterator<structure::AttributeSyntax> getAttributesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Attributes edges.
      * \return Returns an iterator for the Attributes edges.
      */
      ListIterator<structure::AttributeSyntax> getAttributesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Attributes edges or not.
      * \return Returns true if the node doesn't have any Attributes edge.
      */
      bool getAttributesIsEmpty() const;

      /**
      * \brief Gives back how many Attributes edges the node has.
      * \return Returns with the number of Attributes edges.
      */
      unsigned getAttributesSize() const;

      /**
      * \brief Gives back the pointer of the node the Target edge points to.
      * \return Returns the end point of the Target edge.
      */
      structure::AttributeTargetSpecifierSyntax* getTarget() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new Attributes edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Attributes edge.
      */
      void addAttributes(const AttributeSyntax *node);

      /**
      * \brief Adds a new Attributes edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Attributes edge.
      */
      void addAttributes(NodeId id);

      /**
      * \brief Remove the Attributes edge by id from the node.
      * \param id [in] The end point of the Attributes edge.
      */
      void removeAttributes(NodeId id);

      /**
      * \brief Remove the Attributes edge from the node.
      * \param node [in] The end point of the Attributes edge.
      */
      void removeAttributes(AttributeSyntax *node);

      /**
      * \brief Sets the Target edge.
      * \param id [in] The new end point of the Target edge.
      */
      void setTarget(NodeId id);

      /**
      * \brief Sets the Target edge.
      * \param node [in] The new end point of the Target edge.
      */
      void setTarget(AttributeTargetSpecifierSyntax *node);

      /**
      * \brief remove the Target edge.
      */
      void removeTarget();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the Attributes edge points to. */
      ListIterator<structure::AttributeSyntax>::Container AttributesContainer;

      /** \internal \brief The id of the node the Target edge points to. */
      NodeId m_Target;

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

