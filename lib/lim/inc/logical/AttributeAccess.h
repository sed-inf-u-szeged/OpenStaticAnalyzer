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

#ifndef _LIM_AttributeAccess_H_
#define _LIM_AttributeAccess_H_

#include "lim/inc/lim.h"

/**
* \file AttributeAccess.h
* \brief Contains declaration of the logical::AttributeAccess class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace logical {

  /**
  * \brief AttributeAccess class, which represents the logical::AttributeAccess node.
  * (missing)
  * 
  * Attributes:
  *   - accesses (String) : (missing)
  * 
  * Edges:
  *   - attribute (logical::Attribute, single) : (missing)
  */
  class AttributeAccess : public base::Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      AttributeAccess(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~AttributeAccess();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      AttributeAccess & operator=(const AttributeAccess&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      AttributeAccess(const AttributeAccess&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const AttributeAccess& other, bool tryOnVirtualParent);

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
      * \brief Gives back the accesses of the node.
      * \return Returns with the accesses.
      */
      const std::string& getAccesses() const;

      /**
      * \brief Gives back the Key of accesses of the node.
      * \return Returns with the Key of the accesses.
      */
      Key getAccessesKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the accesses of the node.
      * \param accesses [in] The new value of the accesses.
      */
      void setAccesses(const std::string& _accesses);

      /**
      * \internal
      * \brief Sets the accesses of the node.
      * \param accesses [in] The new Key of the accesses.
      */
      void setAccessesKey(Key _accesses);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `accesses`. */
      Key m_accesses;

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
      * \brief Gives back the pointer of the node the attribute edge points to.
      * \return Returns the end point of the attribute edge.
      */
      logical::Attribute* getAttribute() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the attribute edge.
      * \param id [in] The new end point of the attribute edge.
      */
      void setAttribute(NodeId id);

      /**
      * \brief Sets the attribute edge.
      * \param node [in] The new end point of the attribute edge.
      */
      void setAttribute(Attribute *node);

      /**
      * \brief remove the attribute edge.
      */
      void removeAttribute();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the attribute edge points to. */
      NodeId m_attribute;

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

