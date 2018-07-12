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

#ifndef _LIM_Class_H_
#define _LIM_Class_H_

#include "lim/inc/lim.h"

/**
* \file Class.h
* \brief Contains declaration of the logical::Class class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace logical {

  /**
  * \brief Class class, which represents the logical::Class node.
  * (missing)
  * 
  * Attributes:
  *   - classKind (ClassKind) : (missing)
  *   - isAbstract (boolean) : (missing)
  *   - objectSize (int) : (missing)
  * 
  * Edges:
  *   - grantsFriendship (logical::Friendship, multiple) : (missing)
  *   - isSubclass (type::Type, multiple) : (missing)
  */
  class Class : public Scope {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Class(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Class();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Class & operator=(const Class&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Class(const Class&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Class& other, bool tryOnVirtualParent);

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
      * \brief Gives back the classKind of the node.
      * \return Returns with the classKind.
      */
      ClassKind getClassKind() const;

      /**
      * \brief Gives back the isAbstract of the node.
      * \return Returns with the isAbstract.
      */
      bool getIsAbstract() const;

      /**
      * \brief Gives back the objectSize of the node.
      * \return Returns with the objectSize.
      */
      unsigned getObjectSize() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the classKind of the node.
      * \param classKind [in] The new value of the classKind.
      */
      void setClassKind(ClassKind _classKind);

      /**
      * \internal
      * \brief Sets the isAbstract of the node.
      * \param isAbstract [in] The new value of the isAbstract.
      */
      void setIsAbstract(bool _isAbstract);

      /**
      * \internal
      * \brief Sets the objectSize of the node.
      * \param objectSize [in] The new value of the objectSize.
      */
      void setObjectSize(unsigned _objectSize);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Abstract` or not. */
      bool m_isAbstract : 1;

      /** \internal \brief The ClassKind of the node. */
      ClassKind m_classKind;

      /** \internal \brief The value of the `objectSize`. */
      unsigned m_objectSize;

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
      * \brief Gives back iterator for the grantsFriendship edges.
      * \return Returns an iterator for the grantsFriendship edges.
      */
      ListIterator<logical::Friendship> getGrantsFriendshipListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the grantsFriendship edges.
      * \return Returns an iterator for the grantsFriendship edges.
      */
      ListIterator<logical::Friendship> getGrantsFriendshipListIteratorEnd() const;

      /**
      * \brief Tells whether the node has grantsFriendship edges or not.
      * \return Returns true if the node doesn't have any grantsFriendship edge.
      */
      bool getGrantsFriendshipIsEmpty() const;

      /**
      * \brief Gives back how many grantsFriendship edges the node has.
      * \return Returns with the number of grantsFriendship edges.
      */
      unsigned getGrantsFriendshipSize() const;

      /**
      * \brief Gives back iterator for the isSubclass edges.
      * \return Returns an iterator for the isSubclass edges.
      */
      ListIterator<type::Type> getIsSubclassListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the isSubclass edges.
      * \return Returns an iterator for the isSubclass edges.
      */
      ListIterator<type::Type> getIsSubclassListIteratorEnd() const;

      /**
      * \brief Tells whether the node has isSubclass edges or not.
      * \return Returns true if the node doesn't have any isSubclass edge.
      */
      bool getIsSubclassIsEmpty() const;

      /**
      * \brief Gives back how many isSubclass edges the node has.
      * \return Returns with the number of isSubclass edges.
      */
      unsigned getIsSubclassSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new grantsFriendship edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new grantsFriendship edge.
      */
      void addGrantsFriendship(const Friendship *node);

      /**
      * \brief Adds a new grantsFriendship edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new grantsFriendship edge.
      */
      void addGrantsFriendship(NodeId id);

      /**
      * \brief Remove the grantsFriendship edge by id from the node.
      * \param id [in] The end point of the grantsFriendship edge.
      */
      void removeGrantsFriendship(NodeId id);

      /**
      * \brief Remove the grantsFriendship edge from the node.
      * \param node [in] The end point of the grantsFriendship edge.
      */
      void removeGrantsFriendship(Friendship *node);

      /**
      * \brief Adds a new isSubclass edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new isSubclass edge.
      */
      void addIsSubclass(const type::Type *node);

      /**
      * \brief Adds a new isSubclass edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new isSubclass edge.
      */
      void addIsSubclass(NodeId id);

      /**
      * \brief Remove the isSubclass edge by id from the node.
      * \param id [in] The end point of the isSubclass edge.
      */
      void removeIsSubclass(NodeId id);

      /**
      * \brief Remove the isSubclass edge from the node.
      * \param node [in] The end point of the isSubclass edge.
      */
      void removeIsSubclass(type::Type *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the grantsFriendship edge points to. */
      ListIterator<logical::Friendship>::Container grantsFriendshipContainer;

      /** \internal \brief Container stores the id of the nodes the isSubclass edge points to. */
      ListIterator<type::Type>::Container isSubclassContainer;

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

