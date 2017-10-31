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

#ifndef _LIM_TypeFormerMethod_H_
#define _LIM_TypeFormerMethod_H_

#include "lim/inc/lim.h"

/**
* \file TypeFormerMethod.h
* \brief Contains declaration of the type::TypeFormerMethod class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace type {

  /**
  * \brief TypeFormerMethod class, which represents the type::TypeFormerMethod node.
  * (missing)
  * 
  * Edges:
  *   - hasParameterType (type::Type, multiple) : (missing)
  *   - hasReturnType (type::Type, single) : (missing)
  */
  class TypeFormerMethod : public TypeFormer {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      TypeFormerMethod(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~TypeFormerMethod();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      TypeFormerMethod & operator=(const TypeFormerMethod&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      TypeFormerMethod(const TypeFormerMethod&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const TypeFormerMethod& other, bool tryOnVirtualParent);

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
      * \brief Gives back iterator for the hasParameterType edges.
      * \return Returns an iterator for the hasParameterType edges.
      */
      ListIteratorAssocParameterKind<type::Type> getParameterTypeListIteratorAssocBegin() const;

      /**
      * \brief Gives back iterator for the hasParameterType edges.
      * \return Returns an iterator for the hasParameterType edges.
      */
      ListIteratorAssocParameterKind<type::Type> getParameterTypeListIteratorAssocEnd() const;

      /**
      * \brief Tells whether the node has hasParameterType edges or not.
      * \return Returns true if the node doesn't have any hasParameterType edge.
      */
      bool getParameterTypeIsEmpty() const;

      /**
      * \brief Gives back how many hasParameterType edges the node has.
      * \return Returns with the number of hasParameterType edges.
      */
      unsigned getParameterTypeSize() const;

      /**
      * \brief Gives back the pointer of the node the hasReturnType edge points to.
      * \return Returns the end point of the hasReturnType edge.
      */
      type::Type* getReturnType() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasParameterType edge to the node.
      * \param node    [in] The end point of the new hasParameterType edge.
      * \param acValue [in] The value of the association class.
      */
      void addParameterType(const Type *node, ParameterKind acValue);

      /**
      * \brief Adds a new hasParameterType edge to the node.
      * \param id      [in] The end point of the new hasParameterType edge.
      * \param acValue [in] The value of the association class.
      */
      void addParameterType(NodeId id, ParameterKind acValue);

      /**
      * \brief Remove the hasParameterType edge by id from the node.
      * \param id [in] The end point of the hasParameterType edge.
      */
      void removeParameterType(NodeId id);

      /**
      * \brief Remove the hasParameterType edge from the node.
      * \param node [in] The end point of the hasParameterType edge.
      */
      void removeParameterType(Type *node);

      /**
      * \brief Sets the hasReturnType edge.
      * \param id [in] The new end point of the hasReturnType edge.
      */
      void setReturnType(NodeId id);

      /**
      * \brief Sets the hasReturnType edge.
      * \param node [in] The new end point of the hasReturnType edge.
      */
      void setReturnType(Type *node);

      /**
      * \brief remove the hasReturnType edge.
      */
      void removeReturnType();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasParameterType edge points to and the association classes. */
      ListIteratorAssocParameterKind<type::Type>::Container hasParameterTypeContainer;

      /** \internal \brief The id of the node the hasReturnType edge points to. */
      NodeId m_hasReturnType;

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

