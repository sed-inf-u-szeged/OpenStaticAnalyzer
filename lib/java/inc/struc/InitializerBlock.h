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

#ifndef _JAVA_InitializerBlock_H_
#define _JAVA_InitializerBlock_H_

#include "java/inc/java.h"

/**
* \file InitializerBlock.h
* \brief Contains declaration of the struc::InitializerBlock class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
    * \brief struc::Member
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief InitializerBlock class, which represents the struc::InitializerBlock node.
  * (missing)
  * 
  * Attributes:
  *   - lloc (int) : (missing)
  * 
  * Edges:
  *   - hasBody (statm::Block, single) : (missing)
  */
  class InitializerBlock : public Declaration {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      InitializerBlock(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~InitializerBlock();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      InitializerBlock & operator=(const InitializerBlock&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      InitializerBlock(const InitializerBlock&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const InitializerBlock& other, bool tryOnVirtualParent);

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
      * \brief Gives back the lloc of the node.
      * \return Returns with the lloc.
      */
      int getLloc() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the lloc of the node.
      * \param lloc [in] The new value of the lloc.
      */
      void setLloc(int _lloc);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `lloc`. */
      int m_lloc;

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
      * \brief Gives back the pointer of the node the hasBody edge points to.
      * \return Returns the end point of the hasBody edge.
      */
      statm::Block* getBody() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasBody edge.
      * \param id [in] The new end point of the hasBody edge.
      */
      void setBody(NodeId id);

      /**
      * \brief Sets the hasBody edge.
      * \param node [in] The new end point of the hasBody edge.
      */
      void setBody(statm::Block *node);

      /**
      * \brief remove the hasBody edge.
      */
      void removeBody();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasBody edge points to. */
      NodeId m_hasBody;

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

