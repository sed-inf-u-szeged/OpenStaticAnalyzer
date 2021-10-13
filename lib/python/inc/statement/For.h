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

#ifndef _PYTHON_For_H_
#define _PYTHON_For_H_

#include "python/inc/python.h"

/**
* \file For.h
* \brief Contains declaration of the statement::For class.
* \brief The it get atributes from 
*/

namespace columbus { namespace python { namespace asg {
namespace statement {

  /**
  * \brief For class, which represents the statement::For node.
  * (missing)
  * 
  * Attributes:
  *   - isAsync (boolean) : (missing)
  * 
  * Edges:
  *   - hasExpressionList (expression::ExpressionList, single) : (missing)
  *   - hasTargetList (statement::TargetList, single) : (missing)
  */
  class For : public Iteration {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      For(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~For();

    private:
      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      For & operator=(const For&);

      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      For(const For&);

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
      * \brief Gives back the isAsync of the node.
      * \return Returns with the isAsync.
      */
      bool getIsAsync() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the isAsync of the node.
      * \param isAsync [in] The new value of the isAsync.
      */
      void setIsAsync(bool _isAsync);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Async` or not. */
      bool m_isAsync : 1;

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
      * \brief Gives back the pointer of the node the hasExpressionList edge points to.
      * \return Returns the end point of the hasExpressionList edge.
      */
      expression::ExpressionList* getExpressionList() const;

      /**
      * \brief Gives back the pointer of the node the hasTargetList edge points to.
      * \return Returns the end point of the hasTargetList edge.
      */
      statement::TargetList* getTargetList() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasExpressionList edge.
      * \param id [in] The new end point of the hasExpressionList edge.
      */
      void setExpressionList(NodeId id);

      /**
      * \brief Sets the hasExpressionList edge.
      * \param node [in] The new end point of the hasExpressionList edge.
      */
      void setExpressionList(expression::ExpressionList *node);

      /**
      * \brief remove the hasExpressionList edge.
      */
      void removeExpressionList();

      /**
      * \brief Sets the hasTargetList edge.
      * \param id [in] The new end point of the hasTargetList edge.
      */
      void setTargetList(NodeId id);

      /**
      * \brief Sets the hasTargetList edge.
      * \param node [in] The new end point of the hasTargetList edge.
      */
      void setTargetList(TargetList *node);

      /**
      * \brief remove the hasTargetList edge.
      */
      void removeTargetList();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasExpressionList edge points to. */
      NodeId m_hasExpressionList;

      /** \internal \brief The id of the node the hasTargetList edge points to. */
      NodeId m_hasTargetList;

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


      friend class python::asg::Factory;
      friend class python::asg::VisitorSave;
  };

} 


}}}
#endif

