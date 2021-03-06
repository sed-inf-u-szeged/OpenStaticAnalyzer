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

#ifndef _LIM_MethodGenericSpec_H_
#define _LIM_MethodGenericSpec_H_

#include "lim/inc/lim.h"

/**
* \file MethodGenericSpec.h
* \brief Contains declaration of the logical::MethodGenericSpec class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace logical {

  /**
  * \brief MethodGenericSpec class, which represents the logical::MethodGenericSpec node.
  * (missing)
  * 
  * Edges:
  *   - hasArguments (type::Type, multiple) : (missing)
  *   - specialize (logical::MethodGeneric, single) : (missing)
  */
  class MethodGenericSpec : public MethodGeneric {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      MethodGenericSpec(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~MethodGenericSpec();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      MethodGenericSpec & operator=(const MethodGenericSpec&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      MethodGenericSpec(const MethodGenericSpec&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const MethodGenericSpec& other, bool tryOnVirtualParent);

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
      * \brief Gives back iterator for the hasArguments edges.
      * \return Returns an iterator for the hasArguments edges.
      */
      ListIteratorAssocTypeArgumentConstraintKind<type::Type> getArgumentsListIteratorAssocBegin() const;

      /**
      * \brief Gives back iterator for the hasArguments edges.
      * \return Returns an iterator for the hasArguments edges.
      */
      ListIteratorAssocTypeArgumentConstraintKind<type::Type> getArgumentsListIteratorAssocEnd() const;

      /**
      * \brief Tells whether the node has hasArguments edges or not.
      * \return Returns true if the node doesn't have any hasArguments edge.
      */
      bool getArgumentsIsEmpty() const;

      /**
      * \brief Gives back how many hasArguments edges the node has.
      * \return Returns with the number of hasArguments edges.
      */
      unsigned getArgumentsSize() const;

      /**
      * \brief Gives back the pointer of the node the specialize edge points to.
      * \return Returns the end point of the specialize edge.
      */
      logical::MethodGeneric* getSpecialize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasArguments edge to the node.
      * \param node    [in] The end point of the new hasArguments edge.
      * \param acValue [in] The value of the association class.
      */
      void addArguments(const type::Type *node, TypeArgumentConstraintKind acValue);

      /**
      * \brief Adds a new hasArguments edge to the node.
      * \param id      [in] The end point of the new hasArguments edge.
      * \param acValue [in] The value of the association class.
      */
      void addArguments(NodeId id, TypeArgumentConstraintKind acValue);

      /**
      * \brief Remove the hasArguments edge by id from the node.
      * \param id [in] The end point of the hasArguments edge.
      */
      void removeArguments(NodeId id);

      /**
      * \brief Remove the hasArguments edge from the node.
      * \param node [in] The end point of the hasArguments edge.
      */
      void removeArguments(type::Type *node);

      /**
      * \brief Sets the specialize edge.
      * \param id [in] The new end point of the specialize edge.
      */
      void setSpecialize(NodeId id);

      /**
      * \brief Sets the specialize edge.
      * \param node [in] The new end point of the specialize edge.
      */
      void setSpecialize(MethodGeneric *node);

      /**
      * \brief remove the specialize edge.
      */
      void removeSpecialize();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasArguments edge points to and the association classes. */
      ListIteratorAssocTypeArgumentConstraintKind<type::Type>::Container hasArgumentsContainer;

      /** \internal \brief The id of the node the specialize edge points to. */
      NodeId m_specialize;

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

