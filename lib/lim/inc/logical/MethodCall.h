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

#ifndef _LIM_MethodCall_H_
#define _LIM_MethodCall_H_

#include "lim/inc/lim.h"

/**
* \file MethodCall.h
* \brief Contains declaration of the logical::MethodCall class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace logical {

  /**
  * \brief MethodCall class, which represents the logical::MethodCall node.
  * (missing)
  * 
  * Attributes:
  *   - calls (String) : (missing)
  * 
  * Edges:
  *   - method (logical::Method, single) : (missing)
  */
  class MethodCall : public base::Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      MethodCall(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~MethodCall();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      MethodCall & operator=(const MethodCall&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      MethodCall(const MethodCall&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const MethodCall& other, bool tryOnVirtualParent);

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
      * \brief Gives back the calls of the node.
      * \return Returns with the calls.
      */
      const std::string& getCalls() const;

      /**
      * \brief Gives back the Key of calls of the node.
      * \return Returns with the Key of the calls.
      */
      Key getCallsKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the calls of the node.
      * \param calls [in] The new value of the calls.
      */
      void setCalls(const std::string& _calls);

      /**
      * \internal
      * \brief Sets the calls of the node.
      * \param calls [in] The new Key of the calls.
      */
      void setCallsKey(Key _calls);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `calls`. */
      Key m_calls;

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
      * \brief Gives back the pointer of the node the method edge points to.
      * \return Returns the end point of the method edge.
      */
      logical::Method* getMethod() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the method edge.
      * \param id [in] The new end point of the method edge.
      */
      void setMethod(NodeId id);

      /**
      * \brief Sets the method edge.
      * \param node [in] The new end point of the method edge.
      */
      void setMethod(Method *node);

      /**
      * \brief remove the method edge.
      */
      void removeMethod();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the method edge points to. */
      NodeId m_method;

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

