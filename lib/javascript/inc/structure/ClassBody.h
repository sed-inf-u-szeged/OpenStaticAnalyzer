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

#ifndef _JAVASCRIPT_ClassBody_H_
#define _JAVASCRIPT_ClassBody_H_

#include "javascript/inc/javascript.h"

/**
* \file ClassBody.h
* \brief Contains declaration of the structure::ClassBody class.
* \brief The it get atributes from 
*/

namespace columbus { namespace javascript { namespace asg {
namespace structure {

  /**
  * \brief ClassBody class, which represents the structure::ClassBody node.
  * (missing)
  * 
  * Edges:
  *   - hasBody (structure::MethodDefinition, multiple) : (missing)
  */
  class ClassBody : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ClassBody(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ClassBody();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      ClassBody & operator=(const ClassBody&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      ClassBody(const ClassBody&);

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
      * \brief Gives back iterator for the hasBody edges.
      * \return Returns an iterator for the hasBody edges.
      */
      ListIterator<structure::MethodDefinition> getBodyListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasBody edges.
      * \return Returns an iterator for the hasBody edges.
      */
      ListIterator<structure::MethodDefinition> getBodyListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasBody edges or not.
      * \return Returns true if the node doesn't have any hasBody edge.
      */
      bool getBodyIsEmpty() const;

      /**
      * \brief Gives back how many hasBody edges the node has.
      * \return Returns with the number of hasBody edges.
      */
      unsigned getBodySize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasBody edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasBody edge.
      */
      void addBody(const MethodDefinition *node);

      /**
      * \brief Adds a new hasBody edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasBody edge.
      */
      void addBody(NodeId id);

      /**
      * \brief Remove the hasBody edge by id from the node.
      * \param id [in] The end point of the hasBody edge.
      */
      void removeBody(NodeId id);

      /**
      * \brief Remove the hasBody edge from the node.
      * \param node [in] The end point of the hasBody edge.
      */
      void removeBody(MethodDefinition *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasBody edge points to. */
      ListIterator<structure::MethodDefinition>::Container hasBodyContainer;

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


      friend class javascript::asg::Factory;
      friend class javascript::asg::VisitorSave;
  };

} 


}}}
#endif

