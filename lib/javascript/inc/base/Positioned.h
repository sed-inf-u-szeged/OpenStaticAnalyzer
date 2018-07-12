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

#ifndef _JAVASCRIPT_Positioned_H_
#define _JAVASCRIPT_Positioned_H_

#include "javascript/inc/javascript.h"

/**
* \file Positioned.h
* \brief Contains declaration of the base::Positioned class.
* \brief The it get atributes from 
*/

namespace columbus { namespace javascript { namespace asg {
namespace base {

  /**
  * \brief Positioned class, which represents the base::Positioned node.
  * (missing)
  * 
  * Attributes:
  *   - position (Range) : (missing)
  * 
  * Edges:
  *   - comments (base::Comment, multiple) : (missing)
  */
  class Positioned : public Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Positioned(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Positioned();

    private:
      /**
      * \brief This function always throws a JavaScriptException due to copying is not allowed!
      */
      Positioned & operator=(const Positioned&);

      /**
      * \brief This function always throws a JavaScriptException due to copying is not allowed!
      */
      Positioned(const Positioned&);

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
      * \brief Gives back the position of the node.
      * \return Returns with the position.
      */
      virtual const Range getPosition() const;

      /**
      * \brief Compare two node by position attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByPosition(const Positioned& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the position of the node.
      * \param position [in] The new value of the position.
      */
      virtual void setPosition(const Range& _position);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief todo (unknown). */
      MultiRange m_position;

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
      * \brief Gives back iterator for the comments edges.
      * \return Returns an iterator for the comments edges.
      */
      ListIterator<base::Comment> getCommentsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the comments edges.
      * \return Returns an iterator for the comments edges.
      */
      ListIterator<base::Comment> getCommentsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has comments edges or not.
      * \return Returns true if the node doesn't have any comments edge.
      */
      bool getCommentsIsEmpty() const;

      /**
      * \brief Gives back how many comments edges the node has.
      * \return Returns with the number of comments edges.
      */
      unsigned getCommentsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new comments edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new comments edge.
      */
      void addComments(const Comment *node);

      /**
      * \brief Adds a new comments edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new comments edge.
      */
      void addComments(NodeId id);

      /**
      * \brief Remove the comments edge by id from the node.
      * \param id [in] The end point of the comments edge.
      */
      void removeComments(NodeId id);

      /**
      * \brief Remove the comments edge from the node.
      * \param node [in] The end point of the comments edge.
      */
      void removeComments(Comment *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the comments edge points to. */
      ListIterator<base::Comment>::Container commentsContainer;

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


      friend class javascript::asg::Factory;
      friend class javascript::asg::VisitorSave;
  };

} 


}}}
#endif

