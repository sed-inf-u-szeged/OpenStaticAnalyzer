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

#ifndef _JAVA_Binary_H_
#define _JAVA_Binary_H_

#include "java/inc/java.h"

/**
* \file Binary.h
* \brief Contains declaration of the expr::Binary class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace expr {

  /**
  * \brief Binary class, which represents the expr::Binary node.
  * (missing)
  * 
  * Edges:
  *   - hasLeftOperand (expr::Expression, single) : (missing)
  *   - hasRightOperand (expr::Expression, single) : (missing)
  */
  class Binary : public Expression {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Binary(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Binary();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Binary & operator=(const Binary&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Binary(const Binary&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Binary& other, bool tryOnVirtualParent);

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
      * \brief Gives back the pointer of the node the hasLeftOperand edge points to.
      * \return Returns the end point of the hasLeftOperand edge.
      */
      expr::Expression* getLeftOperand() const;

      /**
      * \brief Gives back the pointer of the node the hasRightOperand edge points to.
      * \return Returns the end point of the hasRightOperand edge.
      */
      expr::Expression* getRightOperand() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasLeftOperand edge.
      * \param id [in] The new end point of the hasLeftOperand edge.
      */
      void setLeftOperand(NodeId id);

      /**
      * \brief Sets the hasLeftOperand edge.
      * \param node [in] The new end point of the hasLeftOperand edge.
      */
      void setLeftOperand(Expression *node);

      /**
      * \brief remove the hasLeftOperand edge.
      */
      void removeLeftOperand();

      /**
      * \brief Sets the hasRightOperand edge.
      * \param id [in] The new end point of the hasRightOperand edge.
      */
      void setRightOperand(NodeId id);

      /**
      * \brief Sets the hasRightOperand edge.
      * \param node [in] The new end point of the hasRightOperand edge.
      */
      void setRightOperand(Expression *node);

      /**
      * \brief remove the hasRightOperand edge.
      */
      void removeRightOperand();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasLeftOperand edge points to. */
      NodeId m_hasLeftOperand;

      /** \internal \brief The id of the node the hasRightOperand edge points to. */
      NodeId m_hasRightOperand;

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

