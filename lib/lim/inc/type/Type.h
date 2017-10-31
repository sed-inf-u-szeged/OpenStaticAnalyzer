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

#ifndef _LIM_Type_H_
#define _LIM_Type_H_

#include "lim/inc/lim.h"

/**
* \file Type.h
* \brief Contains declaration of the type::Type class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace type {

  /**
  * \brief Type class, which represents the type::Type node.
  * (missing)
  * 
  * Attributes:
  *   - refers (String) : (missing)
  * 
  * Edges:
  *   - hasTypeFormer (type::TypeFormer, multiple) : (missing)
  */
  class Type : public base::Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Type(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Type();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Type & operator=(const Type&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Type(const Type&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Type& other, bool tryOnVirtualParent);

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
      * \brief Gives back the refers of the node.
      * \return Returns with the refers.
      */
      const std::string& getRefers() const;

      /**
      * \brief Gives back the Key of refers of the node.
      * \return Returns with the Key of the refers.
      */
      Key getRefersKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the refers of the node.
      * \param refers [in] The new value of the refers.
      */
      void setRefers(const std::string& _refers);

      /**
      * \internal
      * \brief Sets the refers of the node.
      * \param refers [in] The new Key of the refers.
      */
      void setRefersKey(Key _refers);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `refers`. */
      Key m_refers;

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
      * \brief Gives back iterator for the hasTypeFormer edges.
      * \return Returns an iterator for the hasTypeFormer edges.
      */
      ListIterator<type::TypeFormer> getTypeFormerListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasTypeFormer edges.
      * \return Returns an iterator for the hasTypeFormer edges.
      */
      ListIterator<type::TypeFormer> getTypeFormerListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasTypeFormer edges or not.
      * \return Returns true if the node doesn't have any hasTypeFormer edge.
      */
      bool getTypeFormerIsEmpty() const;

      /**
      * \brief Gives back how many hasTypeFormer edges the node has.
      * \return Returns with the number of hasTypeFormer edges.
      */
      unsigned getTypeFormerSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasTypeFormer edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasTypeFormer edge.
      */
      void addTypeFormer(const TypeFormer *node);

      /**
      * \brief Adds a new hasTypeFormer edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasTypeFormer edge.
      */
      void addTypeFormer(NodeId id);

      /**
      * \brief Remove the hasTypeFormer edge by id from the node.
      * \param id [in] The end point of the hasTypeFormer edge.
      */
      void removeTypeFormer(NodeId id);

      /**
      * \brief Remove the hasTypeFormer edge from the node.
      * \param node [in] The end point of the hasTypeFormer edge.
      */
      void removeTypeFormer(TypeFormer *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasTypeFormer edge points to. */
      ListIterator<type::TypeFormer>::Container hasTypeFormerContainer;

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

