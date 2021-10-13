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

#ifndef _LIM_Component_H_
#define _LIM_Component_H_

#include "lim/inc/lim.h"

/**
* \file Component.h
* \brief Contains declaration of the base::Component class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace base {

  /**
  * \brief Component class, which represents the base::Component node.
  * (missing)
  * 
  * Attributes:
  *   - TLLOC (int) : (missing)
  *   - TLOC (int) : (missing)
  *   - analysisTime (AnalysisTimeKind) : (missing)
  *   - changesetID (String) : (missing)
  *   - shortName (String) : (missing)
  * 
  * Edges:
  *   - compilationUnit (physical::File, multiple) : (missing)
  *   - contains (base::Component, multiple) : (missing)
  *   - hasFiles (physical::File, multiple) : (missing)
  */
  class Component : public Named {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Component(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Component();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Component & operator=(const Component&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Component(const Component&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Component& other, bool tryOnVirtualParent);

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
      * \brief Gives back the analysisTime of the node.
      * \return Returns with the analysisTime.
      */
      AnalysisTimeKind getAnalysisTime() const;

      /**
      * \brief Gives back the changesetID of the node.
      * \return Returns with the changesetID.
      */
      const std::string& getChangesetID() const;

      /**
      * \brief Gives back the Key of changesetID of the node.
      * \return Returns with the Key of the changesetID.
      */
      Key getChangesetIDKey() const;

      /**
      * \brief Gives back the shortName of the node.
      * \return Returns with the shortName.
      */
      const std::string& getShortName() const;

      /**
      * \brief Gives back the Key of shortName of the node.
      * \return Returns with the Key of the shortName.
      */
      Key getShortNameKey() const;


      // ---------- Attribute setter function(s) ----------

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
      * \brief Sets the analysisTime of the node.
      * \param analysisTime [in] The new value of the analysisTime.
      */
      void setAnalysisTime(AnalysisTimeKind _analysisTime);

      /**
      * \internal
      * \brief Sets the changesetID of the node.
      * \param changesetID [in] The new value of the changesetID.
      */
      void setChangesetID(const std::string& _changesetID);

      /**
      * \internal
      * \brief Sets the shortName of the node.
      * \param shortName [in] The new value of the shortName.
      */
      void setShortName(const std::string& _shortName);

      /**
      * \internal
      * \brief Sets the changesetID of the node.
      * \param changesetID [in] The new Key of the changesetID.
      */
      void setChangesetIDKey(Key _changesetID);

      /**
      * \internal
      * \brief Sets the shortName of the node.
      * \param shortName [in] The new Key of the shortName.
      */
      void setShortNameKey(Key _shortName);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `TLLOC`. */
      unsigned m_TLLOC;

      /** \internal \brief The value of the `TLOC`. */
      unsigned m_TLOC;

      /** \internal \brief The AnalysisTimeKind of the node. */
      AnalysisTimeKind m_analysisTime;

      /** \internal \brief The Key of the `changesetID`. */
      Key m_changesetID;

      /** \internal \brief The Key of the `shortName`. */
      Key m_shortName;

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
      * \brief Gives back iterator for the compilationUnit edges.
      * \return Returns an iterator for the compilationUnit edges.
      */
      ListIterator<physical::File> getCompilationUnitListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the compilationUnit edges.
      * \return Returns an iterator for the compilationUnit edges.
      */
      ListIterator<physical::File> getCompilationUnitListIteratorEnd() const;

      /**
      * \brief Tells whether the node has compilationUnit edges or not.
      * \return Returns true if the node doesn't have any compilationUnit edge.
      */
      bool getCompilationUnitIsEmpty() const;

      /**
      * \brief Gives back how many compilationUnit edges the node has.
      * \return Returns with the number of compilationUnit edges.
      */
      unsigned getCompilationUnitSize() const;

      /**
      * \brief Gives back iterator for the contains edges.
      * \return Returns an iterator for the contains edges.
      */
      ListIterator<base::Component> getContainsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the contains edges.
      * \return Returns an iterator for the contains edges.
      */
      ListIterator<base::Component> getContainsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has contains edges or not.
      * \return Returns true if the node doesn't have any contains edge.
      */
      bool getContainsIsEmpty() const;

      /**
      * \brief Gives back how many contains edges the node has.
      * \return Returns with the number of contains edges.
      */
      unsigned getContainsSize() const;

      /**
      * \brief Gives back iterator for the hasFiles edges.
      * \return Returns an iterator for the hasFiles edges.
      */
      ListIterator<physical::File> getFilesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasFiles edges.
      * \return Returns an iterator for the hasFiles edges.
      */
      ListIterator<physical::File> getFilesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasFiles edges or not.
      * \return Returns true if the node doesn't have any hasFiles edge.
      */
      bool getFilesIsEmpty() const;

      /**
      * \brief Gives back how many hasFiles edges the node has.
      * \return Returns with the number of hasFiles edges.
      */
      unsigned getFilesSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new compilationUnit edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new compilationUnit edge.
      */
      void addCompilationUnit(const physical::File *node);

      /**
      * \brief Adds a new compilationUnit edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new compilationUnit edge.
      */
      void addCompilationUnit(NodeId id);

      /**
      * \brief Remove the compilationUnit edge by id from the node.
      * \param id [in] The end point of the compilationUnit edge.
      */
      void removeCompilationUnit(NodeId id);

      /**
      * \brief Remove the compilationUnit edge from the node.
      * \param node [in] The end point of the compilationUnit edge.
      */
      void removeCompilationUnit(physical::File *node);

      /**
      * \brief Adds a new contains edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new contains edge.
      */
      void addContains(const Component *node);

      /**
      * \brief Adds a new contains edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new contains edge.
      */
      void addContains(NodeId id);

      /**
      * \brief Remove the contains edge by id from the node.
      * \param id [in] The end point of the contains edge.
      */
      void removeContains(NodeId id);

      /**
      * \brief Remove the contains edge from the node.
      * \param node [in] The end point of the contains edge.
      */
      void removeContains(Component *node);

      /**
      * \brief Adds a new hasFiles edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasFiles edge.
      */
      void addFiles(const physical::File *node);

      /**
      * \brief Adds a new hasFiles edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasFiles edge.
      */
      void addFiles(NodeId id);

      /**
      * \brief Remove the hasFiles edge by id from the node.
      * \param id [in] The end point of the hasFiles edge.
      */
      void removeFiles(NodeId id);

      /**
      * \brief Remove the hasFiles edge from the node.
      * \param node [in] The end point of the hasFiles edge.
      */
      void removeFiles(physical::File *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the compilationUnit edge points to. */
      ListIterator<physical::File>::Container compilationUnitContainer;

      /** \internal \brief Container stores the id of the nodes the contains edge points to. */
      ListIterator<base::Component>::Container containsContainer;

      /** \internal \brief Container stores the id of the nodes the hasFiles edge points to. */
      ListIterator<physical::File>::Container hasFilesContainer;

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

