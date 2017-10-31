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

#ifndef _GENEALOGY_Trackable_H_
#define _GENEALOGY_Trackable_H_

#include "genealogy/inc/genealogy.h"

/**
* \file Trackable.h
* \brief Contains declaration of the Trackable class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Trackable class, which represents the Trackable node.
  * (missing)
  * 
  * Edges:
  *   - prev (Trackable, multiple) : (missing)
  *   - next (Trackable, multiple) : (missing)
  */
  class Trackable : public Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Trackable(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Trackable();

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      Trackable & operator=(const Trackable&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      Trackable(const Trackable&);

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
      * \brief Gives back iterator for the prev edges.
      * \return Returns an iterator for the prev edges.
      */
      ListIterator<Trackable> getPrevListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the prev edges.
      * \return Returns an iterator for the prev edges.
      */
      ListIterator<Trackable> getPrevListIteratorEnd() const;

      /**
      * \brief Tells whether the node has prev edges or not.
      * \return Returns true if the node doesn't have any prev edge.
      */
      bool getPrevIsEmpty() const;

      /**
      * \brief Gives back how many prev edges the node has.
      * \return Returns with the number of prev edges.
      */
      unsigned getPrevSize() const;

      /**
      * \brief Gives back iterator for the next edges.
      * \return Returns an iterator for the next edges.
      */
      ListIterator<Trackable> getNextListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the next edges.
      * \return Returns an iterator for the next edges.
      */
      ListIterator<Trackable> getNextListIteratorEnd() const;

      /**
      * \brief Tells whether the node has next edges or not.
      * \return Returns true if the node doesn't have any next edge.
      */
      bool getNextIsEmpty() const;

      /**
      * \brief Gives back how many next edges the node has.
      * \return Returns with the number of next edges.
      */
      unsigned getNextSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new prev edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new prev edge.
      */
      void addPrev(const Trackable *node);

      /**
      * \brief Adds a new prev edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new prev edge.
      */
      void addPrev(NodeId id);

      /**
      * \brief Remove the prev edge by id from the node.
      * \param id [in] The end point of the prev edge.
      */
      void removePrev(NodeId id);

      /**
      * \brief Remove the prev edge from the node.
      * \param node [in] The end point of the prev edge.
      */
      void removePrev(Trackable *node);

      /**
      * \brief Adds a new next edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new next edge.
      */
      void addNext(const Trackable *node);

      /**
      * \brief Adds a new next edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new next edge.
      */
      void addNext(NodeId id);

      /**
      * \brief Remove the next edge by id from the node.
      * \param id [in] The end point of the next edge.
      */
      void removeNext(NodeId id);

      /**
      * \brief Remove the next edge from the node.
      * \param node [in] The end point of the next edge.
      */
      void removeNext(Trackable *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the prev edge points to. */
      ListIterator<Trackable>::Container prevContainer;

      /** \internal \brief Container stores the id of the nodes the next edge points to. */
      ListIterator<Trackable>::Container nextContainer;

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
      virtual double getSimilarity(const Base& node);

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


      friend class genealogy::Factory;
      friend class genealogy::VisitorSave;
  };


}}
#endif

