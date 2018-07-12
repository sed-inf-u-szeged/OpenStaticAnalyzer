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

#ifndef _LIM_Scope_H_
#define _LIM_Scope_H_

#include "lim/inc/lim.h"

/**
* \file Scope.h
* \brief Contains declaration of the logical::Scope class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace logical {

  /**
  * \brief Scope class, which represents the logical::Scope node.
  * (missing)
  * 
  * Attributes:
  *   - LLOC (int) : (missing)
  *   - LOC (int) : (missing)
  *   - TLLOC (int) : (missing)
  *   - TLOC (int) : (missing)
  *   - isAnonymous (boolean) : (missing)
  * 
  * Edges:
  *   - hasMember (logical::Member, multiple) : (missing)
  */
  class Scope : public Member {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Scope(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Scope();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Scope & operator=(const Scope&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Scope(const Scope&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Scope& other, bool tryOnVirtualParent);

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
      * \brief Gives back the LLOC of the node.
      * \return Returns with the LLOC.
      */
      unsigned getLLOC() const;

      /**
      * \brief Gives back the LOC of the node.
      * \return Returns with the LOC.
      */
      unsigned getLOC() const;

      /**
      * \brief Gives back the TLLOC of the node.
      * \return Returns with the TLLOC.
      */
      unsigned getTLLOC() const;

      /**
      * \brief Gives back the TLOC of the node.
      * \return Returns with the TLOC.
      */
      unsigned getTLOC() const;

      /**
      * \brief Gives back the isAnonymous of the node.
      * \return Returns with the isAnonymous.
      */
      bool getIsAnonymous() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the LLOC of the node.
      * \param LLOC [in] The new value of the LLOC.
      */
      void setLLOC(unsigned _LLOC);

      /**
      * \internal
      * \brief Sets the LOC of the node.
      * \param LOC [in] The new value of the LOC.
      */
      void setLOC(unsigned _LOC);

      /**
      * \internal
      * \brief Sets the TLLOC of the node.
      * \param TLLOC [in] The new value of the TLLOC.
      */
      void setTLLOC(unsigned _TLLOC);

      /**
      * \internal
      * \brief Sets the TLOC of the node.
      * \param TLOC [in] The new value of the TLOC.
      */
      void setTLOC(unsigned _TLOC);

      /**
      * \internal
      * \brief Sets the isAnonymous of the node.
      * \param isAnonymous [in] The new value of the isAnonymous.
      */
      void setIsAnonymous(bool _isAnonymous);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Anonymous` or not. */
      bool m_isAnonymous : 1;

      /** \internal \brief The value of the `LLOC`. */
      unsigned m_LLOC;

      /** \internal \brief The value of the `LOC`. */
      unsigned m_LOC;

      /** \internal \brief The value of the `TLLOC`. */
      unsigned m_TLLOC;

      /** \internal \brief The value of the `TLOC`. */
      unsigned m_TLOC;

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
      * \brief Gives back iterator for the hasMember edges.
      * \return Returns an iterator for the hasMember edges.
      */
      ListIterator<logical::Member> getMemberListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasMember edges.
      * \return Returns an iterator for the hasMember edges.
      */
      ListIterator<logical::Member> getMemberListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasMember edges or not.
      * \return Returns true if the node doesn't have any hasMember edge.
      */
      bool getMemberIsEmpty() const;

      /**
      * \brief Gives back how many hasMember edges the node has.
      * \return Returns with the number of hasMember edges.
      */
      unsigned getMemberSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasMember edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasMember edge.
      */
      void addMember(const Member *node);

      /**
      * \brief Adds a new hasMember edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasMember edge.
      */
      void addMember(NodeId id);

      /**
      * \brief Remove the hasMember edge by id from the node.
      * \param id [in] The end point of the hasMember edge.
      */
      void removeMember(NodeId id);

      /**
      * \brief Remove the hasMember edge from the node.
      * \param node [in] The end point of the hasMember edge.
      */
      void removeMember(Member *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasMember edge points to. */
      ListIterator<logical::Member>::Container hasMemberContainer;

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


      friend class lim::asg::Factory;
      friend class lim::asg::VisitorSave;
  };

} 


}}}
#endif

