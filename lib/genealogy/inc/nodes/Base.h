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

#ifndef _GENEALOGY_Base_H_
#define _GENEALOGY_Base_H_

#include "genealogy/inc/genealogy.h"

/**
* \file Base.h
* \brief Contains declaration of the Base class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Base class, which represents the Base node.
  * (missing)
  * 
  * Attributes:
  *   - id (int) : (missing)
  */
  class Base  {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Base(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Base();

    public:

      /**
      * \brief Gives back the Factory the node belongs to.
      * \return Return with a reference to the Factory.
      */
      Factory& getFactory() const;

    protected:

      /**
      * \internal
      * \brief Sets this node the parent of the node given in parameter.
      * \param childNode [in] The node whose parent is set to this node.
      */
      void setParentEdge(const Base *childNode,EdgeKind) const ;

      /**
      * \internal
      * \brief Removes the parent of the node given in parameter.
      * \param childNode [in] The node whose parent is removed.
      */
      void removeParentEdge(NodeId childNode) const;

      /**
      * \internal
      * \brief Removes the parent of the node given in parameter.
      * \param childNode [in] The node whose parent is removed.
      */
      void removeParentEdge(Base *childNode) const ;

      /**
      * \internal
      * \brief Sets the parent of this node.
      * \param parentNode [in] The id of the parent of this node.
      * \param edgeKind   [in] The edge kind of parent.
      */
      void setParent(const Base* parentNode,EdgeKind edgeKind) const;

    public:

      /**
      * \brief Gives back the pointer of the parent of this node.
      * \return Return with the pointer of the parent of this node.
      */
      Base* getParent() const;

      /**
      * \brief Gives back the pointer of the parent of this node.
      * \return Return with the pointer of the parent of this node.
      */
      EdgeKind getParentEdgeKind() const{return parentEdgeKind;}

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      Base & operator=(const Base&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      Base(const Base&);

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
      * \brief Gives back the id of the node.
      * \return Returns with the id.
      */
      unsigned getId() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the id of the node.
      * \param id [in] The new value of the id.
      */
      void setId(unsigned _id);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The hash of node has been calculated. */
      mutable bool hashOk : 1;

      /** \internal \brief The value of the `id`. */
      unsigned m_id;

      /** \internal \brief Edge kind to the parent node. */
      mutable NodeHashType nodeHashCache;

      /** \internal \brief Edge kind to the parent node. */
      mutable EdgeKind parentEdgeKind;

      /** \internal \brief Edge to the parent node. */
      mutable NodeId parent;

      /** \internal \brief The Factory of the node. */
      Factory *factory;

    public:
      /**
      * \brief Set or add the edge by edge kind
      * \param edgeKind [in] The kind of the edge.
      * \param edgeEnd  [in] The id of node which is on the end of the edge.
      * \return Return true if setting was success.
      */
      bool setEdge(EdgeKind edgeKind, Base* edgeEnd);

    protected:
      /**
      * \brief Set or add the edge by edge kind
      * \param edgeKind           [in] The kind of the edge.
      * \param edgeEnd            [in] The id of node which is on the end of the edge.
      * \param tryOnVirtualParent [in] This is help for the traversal.
      * \return Return true if setting was success.
      */
      virtual bool setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent);

    public:
      /**
      * \brief Remove the edge by edge kind
      * \param edgeKind [in] The kind of the edge.
      * \param edgeEnd  [in] The id of node which is on the end of the edge.
      * \return Return true if removing was success.
      */
      bool removeEdge(EdgeKind edgeKind, Base* edgeEnd);

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

      // ---------- Accept functions for Visitor ----------

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
      virtual double getSimilarity(const Base& node);

      /**
      * \internal
      * \brief Calculate node hash.
      */
      virtual NodeHashType getHash(std::set<NodeId>&  node) const ;

      /**
      * \internal
      * \brief Reset node hash.
      */
      void resetHash(std::set<NodeId>&  node) const {hashOk = false;}

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


      friend class genealogy::Factory;
      friend class genealogy::VisitorSave;
  };


}}
#endif

