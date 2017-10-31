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

#ifndef _JAVA_NormalMethod_H_
#define _JAVA_NormalMethod_H_

#include "java/inc/java.h"

/**
* \file NormalMethod.h
* \brief Contains declaration of the struc::NormalMethod class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
    * \brief struc::Member
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief NormalMethod class, which represents the struc::NormalMethod node.
  * (missing)
  * 
  * Attributes:
  *   - methodKind (MethodKind) : (missing)
  *   - isSynchronized (boolean) : (missing)
  *   - synchronizedPosition (Range) : (missing)
  *   - isNative (boolean) : (missing)
  *   - nativePosition (Range) : (missing)
  *   - throwsPosition (Range) : (missing)
  * 
  * Edges:
  *   - hasParameters (struc::Parameter, multiple) : (missing)
  *   - hasBody (statm::Block, single) : (missing)
  *   - hasThrownExceptions (expr::TypeExpression, multiple) : (missing)
  */
  class NormalMethod : public MethodDeclaration {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      NormalMethod(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~NormalMethod();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      NormalMethod & operator=(const NormalMethod&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      NormalMethod(const NormalMethod&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const NormalMethod& other, bool tryOnVirtualParent);

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


      // ---------- Attribute getter function(s) ----------

      /**
      * \brief Gives back the methodKind of the node.
      * \return Returns with the methodKind.
      */
      MethodKind getMethodKind() const;

      /**
      * \brief Gives back the isSynchronized of the node.
      * \return Returns with the isSynchronized.
      */
      bool getIsSynchronized() const;

      /**
      * \brief Gives back the synchronizedPosition of the node.
      * \return Returns with the synchronizedPosition.
      */
      virtual const Range getSynchronizedPosition() const;

      /**
      * \brief Compare two node by synchronizedPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareBySynchronizedPosition(const NormalMethod& other) const;

      /**
      * \brief Gives back the isNative of the node.
      * \return Returns with the isNative.
      */
      bool getIsNative() const;

      /**
      * \brief Gives back the nativePosition of the node.
      * \return Returns with the nativePosition.
      */
      virtual const Range getNativePosition() const;

      /**
      * \brief Compare two node by nativePosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByNativePosition(const NormalMethod& other) const;

      /**
      * \brief Gives back the throwsPosition of the node.
      * \return Returns with the throwsPosition.
      */
      virtual const Range getThrowsPosition() const;

      /**
      * \brief Compare two node by throwsPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByThrowsPosition(const NormalMethod& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the methodKind of the node.
      * \param methodKind [in] The new value of the methodKind.
      */
      void setMethodKind(MethodKind _methodKind);

      /**
      * \internal
      * \brief Sets the isSynchronized of the node.
      * \param isSynchronized [in] The new value of the isSynchronized.
      */
      void setIsSynchronized(bool _isSynchronized);

      /**
      * \internal
      * \brief Sets the synchronizedPosition of the node.
      * \param synchronizedPosition [in] The new value of the synchronizedPosition.
      */
      virtual void setSynchronizedPosition(const Range& _synchronizedPosition);

      /**
      * \internal
      * \brief Sets the isNative of the node.
      * \param isNative [in] The new value of the isNative.
      */
      void setIsNative(bool _isNative);

      /**
      * \internal
      * \brief Sets the nativePosition of the node.
      * \param nativePosition [in] The new value of the nativePosition.
      */
      virtual void setNativePosition(const Range& _nativePosition);

      /**
      * \internal
      * \brief Sets the throwsPosition of the node.
      * \param throwsPosition [in] The new value of the throwsPosition.
      */
      virtual void setThrowsPosition(const Range& _throwsPosition);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Synchronized` or not. */
      bool m_isSynchronized : 1;

      /** \internal \brief Stores whether the node is `Native` or not. */
      bool m_isNative : 1;

      /** \internal \brief The MethodKind of the node. */
      MethodKind m_methodKind;

      /** \internal \brief todo (unknown). */
      MultiRange m_synchronizedPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_nativePosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_throwsPosition;

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
      * \brief Gives back iterator for the hasParameters edges.
      * \return Returns an iterator for the hasParameters edges.
      */
      ListIterator<struc::Parameter> getParametersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasParameters edges.
      * \return Returns an iterator for the hasParameters edges.
      */
      ListIterator<struc::Parameter> getParametersListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasParameters edges or not.
      * \return Returns true if the node doesn't have any hasParameters edge.
      */
      bool getParametersIsEmpty() const;

      /**
      * \brief Gives back how many hasParameters edges the node has.
      * \return Returns with the number of hasParameters edges.
      */
      unsigned getParametersSize() const;

      /**
      * \brief Gives back the pointer of the node the hasBody edge points to.
      * \return Returns the end point of the hasBody edge.
      */
      statm::Block* getBody() const;

      /**
      * \brief Gives back iterator for the hasThrownExceptions edges.
      * \return Returns an iterator for the hasThrownExceptions edges.
      */
      ListIterator<expr::TypeExpression> getThrownExceptionsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasThrownExceptions edges.
      * \return Returns an iterator for the hasThrownExceptions edges.
      */
      ListIterator<expr::TypeExpression> getThrownExceptionsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasThrownExceptions edges or not.
      * \return Returns true if the node doesn't have any hasThrownExceptions edge.
      */
      bool getThrownExceptionsIsEmpty() const;

      /**
      * \brief Gives back how many hasThrownExceptions edges the node has.
      * \return Returns with the number of hasThrownExceptions edges.
      */
      unsigned getThrownExceptionsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasParameters edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasParameters edge.
      */
      void addParameters(const Parameter *node);

      /**
      * \brief Adds a new hasParameters edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasParameters edge.
      */
      void addParameters(NodeId id);

      /**
      * \brief Remove the hasParameters edge by id from the node.
      * \param id [in] The end point of the hasParameters edge.
      */
      void removeParameters(NodeId id);

      /**
      * \brief Remove the hasParameters edge from the node.
      * \param node [in] The end point of the hasParameters edge.
      */
      void removeParameters(Parameter *node);

      /**
      * \brief Sets the hasBody edge.
      * \param id [in] The new end point of the hasBody edge.
      */
      void setBody(NodeId id);

      /**
      * \brief Sets the hasBody edge.
      * \param node [in] The new end point of the hasBody edge.
      */
      void setBody(statm::Block *node);

      /**
      * \brief remove the hasBody edge.
      */
      void removeBody();

      /**
      * \brief Adds a new hasThrownExceptions edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasThrownExceptions edge.
      */
      void addThrownExceptions(const expr::TypeExpression *node);

      /**
      * \brief Adds a new hasThrownExceptions edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasThrownExceptions edge.
      */
      void addThrownExceptions(NodeId id);

      /**
      * \brief Remove the hasThrownExceptions edge by id from the node.
      * \param id [in] The end point of the hasThrownExceptions edge.
      */
      void removeThrownExceptions(NodeId id);

      /**
      * \brief Remove the hasThrownExceptions edge from the node.
      * \param node [in] The end point of the hasThrownExceptions edge.
      */
      void removeThrownExceptions(expr::TypeExpression *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasParameters edge points to. */
      ListIterator<struc::Parameter>::Container hasParametersContainer;

      /** \internal \brief The id of the node the hasBody edge points to. */
      NodeId m_hasBody;

      /** \internal \brief Container stores the id of the nodes the hasThrownExceptions edge points to. */
      ListIterator<expr::TypeExpression>::Container hasThrownExceptionsContainer;

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

