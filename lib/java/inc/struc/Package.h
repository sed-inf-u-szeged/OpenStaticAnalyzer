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

#ifndef _JAVA_Package_H_
#define _JAVA_Package_H_

#include "java/inc/java.h"

/**
* \file Package.h
* \brief Contains declaration of the struc::Package class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
    * \brief struc::Member
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief Package class, which represents the struc::Package node.
  * (missing)
  * 
  * Attributes:
  *   - qualifiedName (String) : (missing)
  * 
  * Edges:
  *   - hasCompilationUnits (struc::CompilationUnit, multiple) : (missing)
  */
  class Package : public base::Named, public Scope {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Package(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Package();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Package & operator=(const Package&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Package(const Package&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Package& other, bool tryOnVirtualParent);

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
      * \brief Gives back the qualifiedName of the node.
      * \return Returns with the qualifiedName.
      */
      const std::string& getQualifiedName() const;

      /**
      * \brief Gives back the Key of qualifiedName of the node.
      * \return Returns with the Key of the qualifiedName.
      */
      Key getQualifiedNameKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the qualifiedName of the node.
      * \param qualifiedName [in] The new value of the qualifiedName.
      */
      void setQualifiedName(const std::string& _qualifiedName);

      /**
      * \internal
      * \brief Sets the qualifiedName of the node.
      * \param qualifiedName [in] The new Key of the qualifiedName.
      */
      void setQualifiedNameKey(Key _qualifiedName);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `qualifiedName`. */
      Key m_qualifiedName;

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
      * \brief Gives back iterator for the hasCompilationUnits edges.
      * \return Returns an iterator for the hasCompilationUnits edges.
      */
      ListIterator<struc::CompilationUnit> getCompilationUnitsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasCompilationUnits edges.
      * \return Returns an iterator for the hasCompilationUnits edges.
      */
      ListIterator<struc::CompilationUnit> getCompilationUnitsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasCompilationUnits edges or not.
      * \return Returns true if the node doesn't have any hasCompilationUnits edge.
      */
      bool getCompilationUnitsIsEmpty() const;

      /**
      * \brief Gives back how many hasCompilationUnits edges the node has.
      * \return Returns with the number of hasCompilationUnits edges.
      */
      unsigned getCompilationUnitsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasCompilationUnits edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasCompilationUnits edge.
      */
      void addCompilationUnits(const CompilationUnit *node);

      /**
      * \brief Adds a new hasCompilationUnits edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasCompilationUnits edge.
      */
      void addCompilationUnits(NodeId id);

      /**
      * \brief Remove the hasCompilationUnits edge by id from the node.
      * \param id [in] The end point of the hasCompilationUnits edge.
      */
      void removeCompilationUnits(NodeId id);

      /**
      * \brief Remove the hasCompilationUnits edge from the node.
      * \param node [in] The end point of the hasCompilationUnits edge.
      */
      void removeCompilationUnits(CompilationUnit *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasCompilationUnits edge points to. */
      ListIterator<struc::CompilationUnit>::Container hasCompilationUnitsContainer;

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

