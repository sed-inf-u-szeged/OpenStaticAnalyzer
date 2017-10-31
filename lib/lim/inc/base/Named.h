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

#ifndef _LIM_Named_H_
#define _LIM_Named_H_

#include "lim/inc/lim.h"

/**
* \file Named.h
* \brief Contains declaration of the base::Named class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace base {

  /**
  * \brief Named class, which represents the base::Named node.
  * (missing)
  * 
  * Attributes:
  *   - name (String) : (missing)
  * 
  * Edges:
  *   - dependsOn (base::Named, multiple) : (missing)
  */
  class Named : public Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Named(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Named();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Named & operator=(const Named&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Named(const Named&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Named& other, bool tryOnVirtualParent);

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
      * \brief Gives back the name of the node.
      * \return Returns with the name.
      */
      const std::string& getName() const;

      /**
      * \brief Gives back the Key of name of the node.
      * \return Returns with the Key of the name.
      */
      Key getNameKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new value of the name.
      */
      void setName(const std::string& _name);

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new Key of the name.
      */
      void setNameKey(Key _name);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `name`. */
      Key m_name;

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
      * \brief Gives back iterator for the dependsOn edges.
      * \return Returns an iterator for the dependsOn edges.
      */
      ListIteratorAssocString<base::Named> getDependsOnListIteratorAssocBegin() const;

      /**
      * \brief Gives back iterator for the dependsOn edges.
      * \return Returns an iterator for the dependsOn edges.
      */
      ListIteratorAssocString<base::Named> getDependsOnListIteratorAssocEnd() const;

      /**
      * \brief Tells whether the node has dependsOn edges or not.
      * \return Returns true if the node doesn't have any dependsOn edge.
      */
      bool getDependsOnIsEmpty() const;

      /**
      * \brief Gives back how many dependsOn edges the node has.
      * \return Returns with the number of dependsOn edges.
      */
      unsigned getDependsOnSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new dependsOn edge to the node.
      * \param node    [in] The end point of the new dependsOn edge.
      * \param acValue [in] The value of the association class.
      */
      void addDependsOn(const Named *node, const std::string& acValue);

      /**
      * \brief Adds a new dependsOn edge to the node.
      * \param id      [in] The end point of the new dependsOn edge.
      * \param acValue [in] The value of the association class.
      */
      void addDependsOn(NodeId id, const std::string& acValue);

      /**
      * \brief Remove the dependsOn edge by id from the node.
      * \param id [in] The end point of the dependsOn edge.
      */
      void removeDependsOn(NodeId id);

      /**
      * \brief Remove the dependsOn edge from the node.
      * \param node [in] The end point of the dependsOn edge.
      */
      void removeDependsOn(Named *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the dependsOn edge points to and the association classes. */
      ListIteratorAssocString<base::Named>::Container dependsOnContainer;

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

