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

#ifndef _JAVA_MethodType_H_
#define _JAVA_MethodType_H_

#include "java/inc/java.h"

/**
* \file MethodType.h
* \brief Contains declaration of the type::MethodType class.
* \brief The it get atributes from 
*/

namespace columbus { namespace java { namespace asg {
namespace type {

  /**
  * \brief MethodType class, which represents the type::MethodType node.
  * (missing)
  * 
  * Edges:
  *   - returnType (type::Type, single) : (missing)
  *   - parameterTypes (type::Type, multiple) : (missing)
  *   - thrownTypes (type::Type, multiple) : (missing)
  */
  class MethodType : public Type {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      MethodType(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~MethodType();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      MethodType & operator=(const MethodType&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      MethodType(const MethodType&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const MethodType& other, bool tryOnVirtualParent);

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
      * \brief Gives back the pointer of the node the returnType edge points to.
      * \return Returns the end point of the returnType edge.
      */
      type::Type* getReturnType() const;

      /**
      * \brief Gives back iterator for the parameterTypes edges.
      * \return Returns an iterator for the parameterTypes edges.
      */
      ListIterator<type::Type> getParameterTypesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the parameterTypes edges.
      * \return Returns an iterator for the parameterTypes edges.
      */
      ListIterator<type::Type> getParameterTypesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has parameterTypes edges or not.
      * \return Returns true if the node doesn't have any parameterTypes edge.
      */
      bool getParameterTypesIsEmpty() const;

      /**
      * \brief Gives back how many parameterTypes edges the node has.
      * \return Returns with the number of parameterTypes edges.
      */
      unsigned getParameterTypesSize() const;

      /**
      * \brief Gives back iterator for the thrownTypes edges.
      * \return Returns an iterator for the thrownTypes edges.
      */
      ListIterator<type::Type> getThrownTypesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the thrownTypes edges.
      * \return Returns an iterator for the thrownTypes edges.
      */
      ListIterator<type::Type> getThrownTypesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has thrownTypes edges or not.
      * \return Returns true if the node doesn't have any thrownTypes edge.
      */
      bool getThrownTypesIsEmpty() const;

      /**
      * \brief Gives back how many thrownTypes edges the node has.
      * \return Returns with the number of thrownTypes edges.
      */
      unsigned getThrownTypesSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the returnType edge.
      * \param id [in] The new end point of the returnType edge.
      */
      void setReturnType(NodeId id);

      /**
      * \brief Sets the returnType edge.
      * \param node [in] The new end point of the returnType edge.
      */
      void setReturnType(Type *node);

      /**
      * \brief remove the returnType edge.
      */
      void removeReturnType();

      /**
      * \brief Adds a new parameterTypes edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new parameterTypes edge.
      */
      void addParameterTypes(const Type *node);

      /**
      * \brief Adds a new parameterTypes edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new parameterTypes edge.
      */
      void addParameterTypes(NodeId id);

      /**
      * \brief Remove the parameterTypes edge by id from the node.
      * \param id [in] The end point of the parameterTypes edge.
      */
      void removeParameterTypes(NodeId id);

      /**
      * \brief Remove the parameterTypes edge from the node.
      * \param node [in] The end point of the parameterTypes edge.
      */
      void removeParameterTypes(Type *node);

      /**
      * \brief Adds a new thrownTypes edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new thrownTypes edge.
      */
      void addThrownTypes(const Type *node);

      /**
      * \brief Adds a new thrownTypes edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new thrownTypes edge.
      */
      void addThrownTypes(NodeId id);

      /**
      * \brief Remove the thrownTypes edge by id from the node.
      * \param id [in] The end point of the thrownTypes edge.
      */
      void removeThrownTypes(NodeId id);

      /**
      * \brief Remove the thrownTypes edge from the node.
      * \param node [in] The end point of the thrownTypes edge.
      */
      void removeThrownTypes(Type *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the returnType edge points to. */
      NodeId m_returnType;

      /** \internal \brief Container stores the id of the nodes the parameterTypes edge points to. */
      ListIterator<type::Type>::Container parameterTypesContainer;

      /** \internal \brief Container stores the id of the nodes the thrownTypes edge points to. */
      ListIterator<type::Type>::Container thrownTypesContainer;

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

      /**
      * \internal
      * \brief Sorts some edges and attributes of the node.
      */
      virtual void sort(bool withVirtualBase = true);


      friend class java::asg::Factory;
      friend class java::asg::VisitorSave;
  };

} 


}}}
#endif

