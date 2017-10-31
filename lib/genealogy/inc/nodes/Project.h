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

#ifndef _GENEALOGY_Project_H_
#define _GENEALOGY_Project_H_

#include "genealogy/inc/genealogy.h"

/**
* \file Project.h
* \brief Contains declaration of the Project class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Project class, which represents the Project node.
  * (missing)
  * 
  * Attributes:
  *   - project (String) : (missing)
  * 
  * Edges:
  *   - systems (System, multiple) : (missing)
  */
  class Project : public Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Project(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Project();

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      Project & operator=(const Project&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      Project(const Project&);

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
      * \brief Gives back the project of the node.
      * \return Returns with the project.
      */
      const std::string& getProject() const;

      /**
      * \brief Gives back the Key of project of the node.
      * \return Returns with the Key of the project.
      */
      Key getProjectKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the project of the node.
      * \param project [in] The new value of the project.
      */
      void setProject(const std::string& _project);

      /**
      * \internal
      * \brief Sets the project of the node.
      * \param project [in] The new Key of the project.
      */
      void setProjectKey(Key _project);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `project`. */
      Key m_project;

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
      * \brief Gives back iterator for the systems edges.
      * \return Returns an iterator for the systems edges.
      */
      ListIterator<System> getSystemsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the systems edges.
      * \return Returns an iterator for the systems edges.
      */
      ListIterator<System> getSystemsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has systems edges or not.
      * \return Returns true if the node doesn't have any systems edge.
      */
      bool getSystemsIsEmpty() const;

      /**
      * \brief Gives back how many systems edges the node has.
      * \return Returns with the number of systems edges.
      */
      unsigned getSystemsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new systems edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new systems edge.
      */
      void addSystems(const System *node);

      /**
      * \brief Adds a new systems edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new systems edge.
      */
      void addSystems(NodeId id);

      /**
      * \brief Remove the systems edge by id from the node.
      * \param id [in] The end point of the systems edge.
      */
      void removeSystems(NodeId id);

      /**
      * \brief Remove the systems edge from the node.
      * \param node [in] The end point of the systems edge.
      */
      void removeSystems(System *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the systems edge points to. */
      ListIterator<System>::Container systemsContainer;

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

