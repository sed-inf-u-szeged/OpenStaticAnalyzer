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

#ifndef _JAVA_Handler_H_
#define _JAVA_Handler_H_

#include "java/inc/java.h"

/**
* \file Handler.h
* \brief Contains declaration of the statm::Handler class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace statm {

  /**
  * \brief Handler class, which represents the statm::Handler node.
  * (missing)
  * 
  * Attributes:
  *   - leftParenPosition (Range) : (missing)
  *   - rightParenPosition (Range) : (missing)
  * 
  * Edges:
  *   - hasParameter (struc::Parameter, single) : (missing)
  *   - hasBlock (statm::Block, single) : (missing)
  */
  class Handler : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Handler(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Handler();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Handler & operator=(const Handler&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Handler(const Handler&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Handler& other, bool tryOnVirtualParent);

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
      * \brief Gives back the leftParenPosition of the node.
      * \return Returns with the leftParenPosition.
      */
      virtual const Range getLeftParenPosition() const;

      /**
      * \brief Compare two node by leftParenPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByLeftParenPosition(const Handler& other) const;

      /**
      * \brief Gives back the rightParenPosition of the node.
      * \return Returns with the rightParenPosition.
      */
      virtual const Range getRightParenPosition() const;

      /**
      * \brief Compare two node by rightParenPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByRightParenPosition(const Handler& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the leftParenPosition of the node.
      * \param leftParenPosition [in] The new value of the leftParenPosition.
      */
      virtual void setLeftParenPosition(const Range& _leftParenPosition);

      /**
      * \internal
      * \brief Sets the rightParenPosition of the node.
      * \param rightParenPosition [in] The new value of the rightParenPosition.
      */
      virtual void setRightParenPosition(const Range& _rightParenPosition);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief todo (unknown). */
      MultiRange m_leftParenPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_rightParenPosition;

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
      * \brief Gives back the pointer of the node the hasParameter edge points to.
      * \return Returns the end point of the hasParameter edge.
      */
      struc::Parameter* getParameter() const;

      /**
      * \brief Gives back the pointer of the node the hasBlock edge points to.
      * \return Returns the end point of the hasBlock edge.
      */
      statm::Block* getBlock() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasParameter edge.
      * \param id [in] The new end point of the hasParameter edge.
      */
      void setParameter(NodeId id);

      /**
      * \brief Sets the hasParameter edge.
      * \param node [in] The new end point of the hasParameter edge.
      */
      void setParameter(struc::Parameter *node);

      /**
      * \brief remove the hasParameter edge.
      */
      void removeParameter();

      /**
      * \brief Sets the hasBlock edge.
      * \param id [in] The new end point of the hasBlock edge.
      */
      void setBlock(NodeId id);

      /**
      * \brief Sets the hasBlock edge.
      * \param node [in] The new end point of the hasBlock edge.
      */
      void setBlock(Block *node);

      /**
      * \brief remove the hasBlock edge.
      */
      void removeBlock();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasParameter edge points to. */
      NodeId m_hasParameter;

      /** \internal \brief The id of the node the hasBlock edge points to. */
      NodeId m_hasBlock;

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

