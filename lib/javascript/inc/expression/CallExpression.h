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

#ifndef _JAVASCRIPT_CallExpression_H_
#define _JAVASCRIPT_CallExpression_H_

#include "javascript/inc/javascript.h"

/**
* \file CallExpression.h
* \brief Contains declaration of the expression::CallExpression class.
* \brief The it get atributes from 
    * \brief base::Positioned
*/

namespace columbus { namespace javascript { namespace asg {
namespace expression {

  /**
  * \brief CallExpression class, which represents the expression::CallExpression node.
  * (missing)
  * 
  * Edges:
  *   - hasCallee (base::Positioned, single) : (missing)
  *   - hasArguments (base::Positioned, multiple) : (missing)
  *   - calls (statement::Function, multiple) : (missing)
  */
  class CallExpression : public Expression, public ChainElement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      CallExpression(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~CallExpression();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      CallExpression & operator=(const CallExpression&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      CallExpression(const CallExpression&);

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
      * \brief Gives back the pointer of the node the hasCallee edge points to.
      * \return Returns the end point of the hasCallee edge.
      */
      base::Positioned* getCallee() const;

      /**
      * \brief Gives back iterator for the hasArguments edges.
      * \return Returns an iterator for the hasArguments edges.
      */
      ListIterator<base::Positioned> getArgumentsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasArguments edges.
      * \return Returns an iterator for the hasArguments edges.
      */
      ListIterator<base::Positioned> getArgumentsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasArguments edges or not.
      * \return Returns true if the node doesn't have any hasArguments edge.
      */
      bool getArgumentsIsEmpty() const;

      /**
      * \brief Gives back how many hasArguments edges the node has.
      * \return Returns with the number of hasArguments edges.
      */
      unsigned getArgumentsSize() const;

      /**
      * \brief Gives back iterator for the calls edges.
      * \return Returns an iterator for the calls edges.
      */
      ListIterator<statement::Function> getCallsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the calls edges.
      * \return Returns an iterator for the calls edges.
      */
      ListIterator<statement::Function> getCallsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has calls edges or not.
      * \return Returns true if the node doesn't have any calls edge.
      */
      bool getCallsIsEmpty() const;

      /**
      * \brief Gives back how many calls edges the node has.
      * \return Returns with the number of calls edges.
      */
      unsigned getCallsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasCallee edge.
      * \param id [in] The new end point of the hasCallee edge.
      */
      void setCallee(NodeId id);

      /**
      * \brief Sets the hasCallee edge.
      * \param node [in] The new end point of the hasCallee edge.
      */
      void setCallee(base::Positioned *node);

      /**
      * \brief remove the hasCallee edge.
      */
      void removeCallee();

      /**
      * \brief Adds a new hasArguments edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasArguments edge.
      */
      void addArguments(const base::Positioned *node);

      /**
      * \brief Adds a new hasArguments edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasArguments edge.
      */
      void addArguments(NodeId id);

      /**
      * \brief Remove the hasArguments edge by id from the node.
      * \param id [in] The end point of the hasArguments edge.
      */
      void removeArguments(NodeId id);

      /**
      * \brief Remove the hasArguments edge from the node.
      * \param node [in] The end point of the hasArguments edge.
      */
      void removeArguments(base::Positioned *node);

      /**
      * \brief Adds a new calls edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new calls edge.
      */
      void addCalls(const statement::Function *node);

      /**
      * \brief Adds a new calls edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new calls edge.
      */
      void addCalls(NodeId id);

      /**
      * \brief Remove the calls edge by id from the node.
      * \param id [in] The end point of the calls edge.
      */
      void removeCalls(NodeId id);

      /**
      * \brief Remove the calls edge from the node.
      * \param node [in] The end point of the calls edge.
      */
      void removeCalls(statement::Function *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasCallee edge points to. */
      NodeId m_hasCallee;

      /** \internal \brief Container stores the id of the nodes the hasArguments edge points to. */
      ListIterator<base::Positioned>::Container hasArgumentsContainer;

      /** \internal \brief Container stores the id of the nodes the calls edge points to. */
      ListIterator<statement::Function>::Container callsContainer;

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

