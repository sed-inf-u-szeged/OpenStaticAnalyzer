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

#ifndef _GENEALOGY_System_H_
#define _GENEALOGY_System_H_

#include "genealogy/inc/genealogy.h"

/**
* \file System.h
* \brief Contains declaration of the System class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief System class, which represents the System node.
  * (missing)
  * 
  * Attributes:
  *   - age (int) : (missing)
  *   - version (String) : (missing)
  *   - name (String) : (missing)
  *   - limFileLocation (String) : (missing)
  *   - firstFreeID (int) : (missing)
  * 
  * Edges:
  *   - components (Component, multiple) : (missing)
  *   - cloneClasses (CloneClass, multiple) : (missing)
  *   - smells (StructuralClone, multiple) : (missing)
  *   - next (System, single) : (missing)
  *   - prev (System, single) : (missing)
  */
  class System : public Trackable {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      System(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~System();

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      System & operator=(const System&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      System(const System&);

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
      * \brief Gives back the age of the node.
      * \return Returns with the age.
      */
      unsigned getAge() const;

      /**
      * \brief Gives back the version of the node.
      * \return Returns with the version.
      */
      const std::string& getVersion() const;

      /**
      * \brief Gives back the Key of version of the node.
      * \return Returns with the Key of the version.
      */
      Key getVersionKey() const;

      /**
      * \brief Gives back the name of the node.
      * \return Returns with the name.
      */
      const std::string& getName() const;

      /**
      * \brief Gives back the Key of name of the node.
      * \return Returns with the Key of the name.
      */
      Key getNameKey() const;

      /**
      * \brief Gives back the limFileLocation of the node.
      * \return Returns with the limFileLocation.
      */
      const std::string& getLimFileLocation() const;

      /**
      * \brief Gives back the Key of limFileLocation of the node.
      * \return Returns with the Key of the limFileLocation.
      */
      Key getLimFileLocationKey() const;

      /**
      * \brief Gives back the firstFreeID of the node.
      * \return Returns with the firstFreeID.
      */
      unsigned getFirstFreeID() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the age of the node.
      * \param age [in] The new value of the age.
      */
      void setAge(unsigned _age);

      /**
      * \internal
      * \brief Sets the version of the node.
      * \param version [in] The new value of the version.
      */
      void setVersion(const std::string& _version);

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new value of the name.
      */
      void setName(const std::string& _name);

      /**
      * \internal
      * \brief Sets the limFileLocation of the node.
      * \param limFileLocation [in] The new value of the limFileLocation.
      */
      void setLimFileLocation(const std::string& _limFileLocation);

      /**
      * \internal
      * \brief Sets the firstFreeID of the node.
      * \param firstFreeID [in] The new value of the firstFreeID.
      */
      void setFirstFreeID(unsigned _firstFreeID);

      /**
      * \internal
      * \brief Sets the version of the node.
      * \param version [in] The new Key of the version.
      */
      void setVersionKey(Key _version);

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new Key of the name.
      */
      void setNameKey(Key _name);

      /**
      * \internal
      * \brief Sets the limFileLocation of the node.
      * \param limFileLocation [in] The new Key of the limFileLocation.
      */
      void setLimFileLocationKey(Key _limFileLocation);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `age`. */
      unsigned m_age;

      /** \internal \brief The value of the `firstFreeID`. */
      unsigned m_firstFreeID;

      /** \internal \brief The Key of the `version`. */
      Key m_version;

      /** \internal \brief The Key of the `name`. */
      Key m_name;

      /** \internal \brief The Key of the `limFileLocation`. */
      Key m_limFileLocation;

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
      * \brief Gives back iterator for the components edges.
      * \return Returns an iterator for the components edges.
      */
      ListIterator<Component> getComponentsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the components edges.
      * \return Returns an iterator for the components edges.
      */
      ListIterator<Component> getComponentsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has components edges or not.
      * \return Returns true if the node doesn't have any components edge.
      */
      bool getComponentsIsEmpty() const;

      /**
      * \brief Gives back how many components edges the node has.
      * \return Returns with the number of components edges.
      */
      unsigned getComponentsSize() const;

      /**
      * \brief Gives back iterator for the cloneClasses edges.
      * \return Returns an iterator for the cloneClasses edges.
      */
      ListIterator<CloneClass> getCloneClassesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the cloneClasses edges.
      * \return Returns an iterator for the cloneClasses edges.
      */
      ListIterator<CloneClass> getCloneClassesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has cloneClasses edges or not.
      * \return Returns true if the node doesn't have any cloneClasses edge.
      */
      bool getCloneClassesIsEmpty() const;

      /**
      * \brief Gives back how many cloneClasses edges the node has.
      * \return Returns with the number of cloneClasses edges.
      */
      unsigned getCloneClassesSize() const;

      /**
      * \brief Gives back iterator for the smells edges.
      * \return Returns an iterator for the smells edges.
      */
      ListIterator<StructuralClone> getSmellsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the smells edges.
      * \return Returns an iterator for the smells edges.
      */
      ListIterator<StructuralClone> getSmellsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has smells edges or not.
      * \return Returns true if the node doesn't have any smells edge.
      */
      bool getSmellsIsEmpty() const;

      /**
      * \brief Gives back how many smells edges the node has.
      * \return Returns with the number of smells edges.
      */
      unsigned getSmellsSize() const;

      /**
      * \brief Gives back the pointer of the node the next edge points to.
      * \return Returns the end point of the next edge.
      */
      System* getNext() const;

      /**
      * \brief Gives back the pointer of the node the prev edge points to.
      * \return Returns the end point of the prev edge.
      */
      System* getPrev() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new components edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new components edge.
      */
      void addComponents(const Component *node);

      /**
      * \brief Adds a new components edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new components edge.
      */
      void addComponents(NodeId id);

      /**
      * \brief Remove the components edge by id from the node.
      * \param id [in] The end point of the components edge.
      */
      void removeComponents(NodeId id);

      /**
      * \brief Remove the components edge from the node.
      * \param node [in] The end point of the components edge.
      */
      void removeComponents(Component *node);

      /**
      * \brief Adds a new cloneClasses edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new cloneClasses edge.
      */
      void addCloneClasses(const CloneClass *node);

      /**
      * \brief Adds a new cloneClasses edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new cloneClasses edge.
      */
      void addCloneClasses(NodeId id);

      /**
      * \brief Remove the cloneClasses edge by id from the node.
      * \param id [in] The end point of the cloneClasses edge.
      */
      void removeCloneClasses(NodeId id);

      /**
      * \brief Remove the cloneClasses edge from the node.
      * \param node [in] The end point of the cloneClasses edge.
      */
      void removeCloneClasses(CloneClass *node);

      /**
      * \brief Adds a new smells edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new smells edge.
      */
      void addSmells(const StructuralClone *node);

      /**
      * \brief Adds a new smells edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new smells edge.
      */
      void addSmells(NodeId id);

      /**
      * \brief Remove the smells edge by id from the node.
      * \param id [in] The end point of the smells edge.
      */
      void removeSmells(NodeId id);

      /**
      * \brief Remove the smells edge from the node.
      * \param node [in] The end point of the smells edge.
      */
      void removeSmells(StructuralClone *node);

      /**
      * \brief Sets the next edge.
      * \param id [in] The new end point of the next edge.
      */
      void setNext(NodeId id);

      /**
      * \brief Sets the next edge.
      * \param node [in] The new end point of the next edge.
      */
      void setNext(System *node);

      /**
      * \brief remove the next edge.
      */
      void removeNext();

      /**
      * \brief Sets the prev edge.
      * \param id [in] The new end point of the prev edge.
      */
      void setPrev(NodeId id);

      /**
      * \brief Sets the prev edge.
      * \param node [in] The new end point of the prev edge.
      */
      void setPrev(System *node);

      /**
      * \brief remove the prev edge.
      */
      void removePrev();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the components edge points to. */
      ListIterator<Component>::Container componentsContainer;

      /** \internal \brief Container stores the id of the nodes the cloneClasses edge points to. */
      ListIterator<CloneClass>::Container cloneClassesContainer;

      /** \internal \brief Container stores the id of the nodes the smells edge points to. */
      ListIterator<StructuralClone>::Container smellsContainer;

      /** \internal \brief The id of the node the next edge points to. */
      NodeId m_next;

      /** \internal \brief The id of the node the prev edge points to. */
      NodeId m_prev;

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

