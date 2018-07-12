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

#ifndef _LIM_GenericParameter_H_
#define _LIM_GenericParameter_H_

#include "lim/inc/lim.h"

/**
* \file GenericParameter.h
* \brief Contains declaration of the logical::GenericParameter class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace logical {

  /**
  * \brief GenericParameter class, which represents the logical::GenericParameter node.
  * (missing)
  * 
  * Attributes:
  *   - genericParameterKind (GenericParameterKind) : (missing)
  * 
  * Edges:
  *   - hasParameterConstraint (type::Type, multiple) : (missing)
  */
  class GenericParameter : public base::Named {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      GenericParameter(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~GenericParameter();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      GenericParameter & operator=(const GenericParameter&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      GenericParameter(const GenericParameter&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const GenericParameter& other, bool tryOnVirtualParent);

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
      * \brief Gives back the genericParameterKind of the node.
      * \return Returns with the genericParameterKind.
      */
      GenericParameterKind getGenericParameterKind() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the genericParameterKind of the node.
      * \param genericParameterKind [in] The new value of the genericParameterKind.
      */
      void setGenericParameterKind(GenericParameterKind _genericParameterKind);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The GenericParameterKind of the node. */
      GenericParameterKind m_genericParameterKind;

    protected:
      /**
      * \brief Set or add the edge by edge kind
      * \param edgeKind           [in] The kind of the edge.
      * \param edgeEnd            [in] The id of node which is on the end of the edge.
      * \param acValue            [in] The value of the association class.
      * \param tryOnVirtualParent [in] This is help for the traversal.
      * \return Return true if setting was success.
      */
      virtual bool setEdge(EdgeKind edgeKind, NodeId edgeEnd, void *acValue, bool tryOnVirtualParent);

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
      * \brief Gives back iterator for the hasParameterConstraint edges.
      * \return Returns an iterator for the hasParameterConstraint edges.
      */
      ListIterator<type::Type> getParameterConstraintListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasParameterConstraint edges.
      * \return Returns an iterator for the hasParameterConstraint edges.
      */
      ListIterator<type::Type> getParameterConstraintListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasParameterConstraint edges or not.
      * \return Returns true if the node doesn't have any hasParameterConstraint edge.
      */
      bool getParameterConstraintIsEmpty() const;

      /**
      * \brief Gives back how many hasParameterConstraint edges the node has.
      * \return Returns with the number of hasParameterConstraint edges.
      */
      unsigned getParameterConstraintSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasParameterConstraint edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasParameterConstraint edge.
      */
      void addParameterConstraint(const type::Type *node);

      /**
      * \brief Adds a new hasParameterConstraint edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasParameterConstraint edge.
      */
      void addParameterConstraint(NodeId id);

      /**
      * \brief Remove the hasParameterConstraint edge by id from the node.
      * \param id [in] The end point of the hasParameterConstraint edge.
      */
      void removeParameterConstraint(NodeId id);

      /**
      * \brief Remove the hasParameterConstraint edge from the node.
      * \param node [in] The end point of the hasParameterConstraint edge.
      */
      void removeParameterConstraint(type::Type *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasParameterConstraint edge points to. */
      ListIterator<type::Type>::Container hasParameterConstraintContainer;

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


      friend class lim::asg::Factory;
      friend class lim::asg::VisitorSave;
  };

} 


}}}
#endif

