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

#ifndef _LIM_Method_H_
#define _LIM_Method_H_

#include "lim/inc/lim.h"

/**
* \file Method.h
* \brief Contains declaration of the logical::Method class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace logical {

  /**
  * \brief Method class, which represents the logical::Method node.
  * (missing)
  * 
  * Attributes:
  *   - distinctOperands (int) : (missing)
  *   - distinctOperators (int) : (missing)
  *   - isAbstract (boolean) : (missing)
  *   - isVirtual (boolean) : (missing)
  *   - methodKind (MethodKind) : (missing)
  *   - nestingLevel (short) : (missing)
  *   - nestingLevelElseIf (short) : (missing)
  *   - numberOfBranches (int) : (missing)
  *   - numberOfStatements (int) : (missing)
  *   - totalOperands (int) : (missing)
  *   - totalOperators (int) : (missing)
  * 
  * Edges:
  *   - accessesAttribute (logical::AttributeAccess, multiple) : (missing)
  *   - calls (logical::MethodCall, multiple) : (missing)
  *   - canThrow (type::Type, multiple) : (missing)
  *   - hasControlFlowBlock (base::ControlFlowBlock, multiple) : (missing)
  *   - hasParameter (logical::Parameter, multiple) : (missing)
  *   - instantiates (type::Type, multiple) : (missing)
  *   - returns (type::Type, multiple) : (missing)
  *   - throws (type::Type, multiple) : (missing)
  */
  class Method : public Scope {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Method(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Method();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Method & operator=(const Method&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Method(const Method&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Method& other, bool tryOnVirtualParent);

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
      * \brief Gives back the distinctOperands of the node.
      * \return Returns with the distinctOperands.
      */
      unsigned getDistinctOperands() const;

      /**
      * \brief Gives back the distinctOperators of the node.
      * \return Returns with the distinctOperators.
      */
      unsigned getDistinctOperators() const;

      /**
      * \brief Gives back the isAbstract of the node.
      * \return Returns with the isAbstract.
      */
      bool getIsAbstract() const;

      /**
      * \brief Gives back the isVirtual of the node.
      * \return Returns with the isVirtual.
      */
      bool getIsVirtual() const;

      /**
      * \brief Gives back the methodKind of the node.
      * \return Returns with the methodKind.
      */
      MethodKind getMethodKind() const;

      /**
      * \brief Gives back the nestingLevel of the node.
      * \return Returns with the nestingLevel.
      */
      unsigned short getNestingLevel() const;

      /**
      * \brief Gives back the nestingLevelElseIf of the node.
      * \return Returns with the nestingLevelElseIf.
      */
      unsigned short getNestingLevelElseIf() const;

      /**
      * \brief Gives back the numberOfBranches of the node.
      * \return Returns with the numberOfBranches.
      */
      unsigned getNumberOfBranches() const;

      /**
      * \brief Gives back the numberOfStatements of the node.
      * \return Returns with the numberOfStatements.
      */
      unsigned getNumberOfStatements() const;

      /**
      * \brief Gives back the totalOperands of the node.
      * \return Returns with the totalOperands.
      */
      unsigned getTotalOperands() const;

      /**
      * \brief Gives back the totalOperators of the node.
      * \return Returns with the totalOperators.
      */
      unsigned getTotalOperators() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the distinctOperands of the node.
      * \param distinctOperands [in] The new value of the distinctOperands.
      */
      void setDistinctOperands(unsigned _distinctOperands);

      /**
      * \internal
      * \brief Sets the distinctOperators of the node.
      * \param distinctOperators [in] The new value of the distinctOperators.
      */
      void setDistinctOperators(unsigned _distinctOperators);

      /**
      * \internal
      * \brief Sets the isAbstract of the node.
      * \param isAbstract [in] The new value of the isAbstract.
      */
      void setIsAbstract(bool _isAbstract);

      /**
      * \internal
      * \brief Sets the isVirtual of the node.
      * \param isVirtual [in] The new value of the isVirtual.
      */
      void setIsVirtual(bool _isVirtual);

      /**
      * \internal
      * \brief Sets the methodKind of the node.
      * \param methodKind [in] The new value of the methodKind.
      */
      void setMethodKind(MethodKind _methodKind);

      /**
      * \internal
      * \brief Sets the nestingLevel of the node.
      * \param nestingLevel [in] The new value of the nestingLevel.
      */
      void setNestingLevel(unsigned short _nestingLevel);

      /**
      * \internal
      * \brief Sets the nestingLevelElseIf of the node.
      * \param nestingLevelElseIf [in] The new value of the nestingLevelElseIf.
      */
      void setNestingLevelElseIf(unsigned short _nestingLevelElseIf);

      /**
      * \internal
      * \brief Sets the numberOfBranches of the node.
      * \param numberOfBranches [in] The new value of the numberOfBranches.
      */
      void setNumberOfBranches(unsigned _numberOfBranches);

      /**
      * \internal
      * \brief Sets the numberOfStatements of the node.
      * \param numberOfStatements [in] The new value of the numberOfStatements.
      */
      void setNumberOfStatements(unsigned _numberOfStatements);

      /**
      * \internal
      * \brief Sets the totalOperands of the node.
      * \param totalOperands [in] The new value of the totalOperands.
      */
      void setTotalOperands(unsigned _totalOperands);

      /**
      * \internal
      * \brief Sets the totalOperators of the node.
      * \param totalOperators [in] The new value of the totalOperators.
      */
      void setTotalOperators(unsigned _totalOperators);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Abstract` or not. */
      bool m_isAbstract : 1;

      /** \internal \brief Stores whether the node is `Virtual` or not. */
      bool m_isVirtual : 1;

      /** \internal \brief The value of the `nestingLevel`. */
      unsigned short m_nestingLevel;

      /** \internal \brief The value of the `nestingLevelElseIf`. */
      unsigned short m_nestingLevelElseIf;

      /** \internal \brief The value of the `distinctOperands`. */
      unsigned m_distinctOperands;

      /** \internal \brief The value of the `distinctOperators`. */
      unsigned m_distinctOperators;

      /** \internal \brief The MethodKind of the node. */
      MethodKind m_methodKind;

      /** \internal \brief The value of the `numberOfBranches`. */
      unsigned m_numberOfBranches;

      /** \internal \brief The value of the `numberOfStatements`. */
      unsigned m_numberOfStatements;

      /** \internal \brief The value of the `totalOperands`. */
      unsigned m_totalOperands;

      /** \internal \brief The value of the `totalOperators`. */
      unsigned m_totalOperators;

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
      * \brief Gives back iterator for the accessesAttribute edges.
      * \return Returns an iterator for the accessesAttribute edges.
      */
      ListIterator<logical::AttributeAccess> getAccessesAttributeListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the accessesAttribute edges.
      * \return Returns an iterator for the accessesAttribute edges.
      */
      ListIterator<logical::AttributeAccess> getAccessesAttributeListIteratorEnd() const;

      /**
      * \brief Tells whether the node has accessesAttribute edges or not.
      * \return Returns true if the node doesn't have any accessesAttribute edge.
      */
      bool getAccessesAttributeIsEmpty() const;

      /**
      * \brief Gives back how many accessesAttribute edges the node has.
      * \return Returns with the number of accessesAttribute edges.
      */
      unsigned getAccessesAttributeSize() const;

      /**
      * \brief Gives back iterator for the calls edges.
      * \return Returns an iterator for the calls edges.
      */
      ListIterator<logical::MethodCall> getCallsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the calls edges.
      * \return Returns an iterator for the calls edges.
      */
      ListIterator<logical::MethodCall> getCallsListIteratorEnd() const;

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

      /**
      * \brief Gives back iterator for the canThrow edges.
      * \return Returns an iterator for the canThrow edges.
      */
      ListIterator<type::Type> getCanThrowListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the canThrow edges.
      * \return Returns an iterator for the canThrow edges.
      */
      ListIterator<type::Type> getCanThrowListIteratorEnd() const;

      /**
      * \brief Tells whether the node has canThrow edges or not.
      * \return Returns true if the node doesn't have any canThrow edge.
      */
      bool getCanThrowIsEmpty() const;

      /**
      * \brief Gives back how many canThrow edges the node has.
      * \return Returns with the number of canThrow edges.
      */
      unsigned getCanThrowSize() const;

      /**
      * \brief Gives back iterator for the hasControlFlowBlock edges.
      * \return Returns an iterator for the hasControlFlowBlock edges.
      */
      ListIterator<base::ControlFlowBlock> getControlFlowBlockListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasControlFlowBlock edges.
      * \return Returns an iterator for the hasControlFlowBlock edges.
      */
      ListIterator<base::ControlFlowBlock> getControlFlowBlockListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasControlFlowBlock edges or not.
      * \return Returns true if the node doesn't have any hasControlFlowBlock edge.
      */
      bool getControlFlowBlockIsEmpty() const;

      /**
      * \brief Gives back how many hasControlFlowBlock edges the node has.
      * \return Returns with the number of hasControlFlowBlock edges.
      */
      unsigned getControlFlowBlockSize() const;

      /**
      * \brief Gives back iterator for the hasParameter edges.
      * \return Returns an iterator for the hasParameter edges.
      */
      ListIterator<logical::Parameter> getParameterListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasParameter edges.
      * \return Returns an iterator for the hasParameter edges.
      */
      ListIterator<logical::Parameter> getParameterListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasParameter edges or not.
      * \return Returns true if the node doesn't have any hasParameter edge.
      */
      bool getParameterIsEmpty() const;

      /**
      * \brief Gives back how many hasParameter edges the node has.
      * \return Returns with the number of hasParameter edges.
      */
      unsigned getParameterSize() const;

      /**
      * \brief Gives back iterator for the instantiates edges.
      * \return Returns an iterator for the instantiates edges.
      */
      ListIterator<type::Type> getInstantiatesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the instantiates edges.
      * \return Returns an iterator for the instantiates edges.
      */
      ListIterator<type::Type> getInstantiatesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has instantiates edges or not.
      * \return Returns true if the node doesn't have any instantiates edge.
      */
      bool getInstantiatesIsEmpty() const;

      /**
      * \brief Gives back how many instantiates edges the node has.
      * \return Returns with the number of instantiates edges.
      */
      unsigned getInstantiatesSize() const;

      /**
      * \brief Gives back iterator for the returns edges.
      * \return Returns an iterator for the returns edges.
      */
      ListIterator<type::Type> getReturnsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the returns edges.
      * \return Returns an iterator for the returns edges.
      */
      ListIterator<type::Type> getReturnsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has returns edges or not.
      * \return Returns true if the node doesn't have any returns edge.
      */
      bool getReturnsIsEmpty() const;

      /**
      * \brief Gives back how many returns edges the node has.
      * \return Returns with the number of returns edges.
      */
      unsigned getReturnsSize() const;

      /**
      * \brief Gives back iterator for the throws edges.
      * \return Returns an iterator for the throws edges.
      */
      ListIterator<type::Type> getThrowsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the throws edges.
      * \return Returns an iterator for the throws edges.
      */
      ListIterator<type::Type> getThrowsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has throws edges or not.
      * \return Returns true if the node doesn't have any throws edge.
      */
      bool getThrowsIsEmpty() const;

      /**
      * \brief Gives back how many throws edges the node has.
      * \return Returns with the number of throws edges.
      */
      unsigned getThrowsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new accessesAttribute edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new accessesAttribute edge.
      */
      void addAccessesAttribute(const AttributeAccess *node);

      /**
      * \brief Adds a new accessesAttribute edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new accessesAttribute edge.
      */
      void addAccessesAttribute(NodeId id);

      /**
      * \brief Remove the accessesAttribute edge by id from the node.
      * \param id [in] The end point of the accessesAttribute edge.
      */
      void removeAccessesAttribute(NodeId id);

      /**
      * \brief Remove the accessesAttribute edge from the node.
      * \param node [in] The end point of the accessesAttribute edge.
      */
      void removeAccessesAttribute(AttributeAccess *node);

      /**
      * \brief Adds a new calls edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new calls edge.
      */
      void addCalls(const MethodCall *node);

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
      void removeCalls(MethodCall *node);

      /**
      * \brief Adds a new canThrow edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new canThrow edge.
      */
      void addCanThrow(const type::Type *node);

      /**
      * \brief Adds a new canThrow edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new canThrow edge.
      */
      void addCanThrow(NodeId id);

      /**
      * \brief Remove the canThrow edge by id from the node.
      * \param id [in] The end point of the canThrow edge.
      */
      void removeCanThrow(NodeId id);

      /**
      * \brief Remove the canThrow edge from the node.
      * \param node [in] The end point of the canThrow edge.
      */
      void removeCanThrow(type::Type *node);

      /**
      * \brief Adds a new hasControlFlowBlock edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasControlFlowBlock edge.
      */
      void addControlFlowBlock(const base::ControlFlowBlock *node);

      /**
      * \brief Adds a new hasControlFlowBlock edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasControlFlowBlock edge.
      */
      void addControlFlowBlock(NodeId id);

      /**
      * \brief Remove the hasControlFlowBlock edge by id from the node.
      * \param id [in] The end point of the hasControlFlowBlock edge.
      */
      void removeControlFlowBlock(NodeId id);

      /**
      * \brief Remove the hasControlFlowBlock edge from the node.
      * \param node [in] The end point of the hasControlFlowBlock edge.
      */
      void removeControlFlowBlock(base::ControlFlowBlock *node);

      /**
      * \brief Adds a new hasParameter edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasParameter edge.
      */
      void addParameter(const Parameter *node);

      /**
      * \brief Adds a new hasParameter edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasParameter edge.
      */
      void addParameter(NodeId id);

      /**
      * \brief Remove the hasParameter edge by id from the node.
      * \param id [in] The end point of the hasParameter edge.
      */
      void removeParameter(NodeId id);

      /**
      * \brief Remove the hasParameter edge from the node.
      * \param node [in] The end point of the hasParameter edge.
      */
      void removeParameter(Parameter *node);

      /**
      * \brief Adds a new instantiates edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new instantiates edge.
      */
      void addInstantiates(const type::Type *node);

      /**
      * \brief Adds a new instantiates edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new instantiates edge.
      */
      void addInstantiates(NodeId id);

      /**
      * \brief Remove the instantiates edge by id from the node.
      * \param id [in] The end point of the instantiates edge.
      */
      void removeInstantiates(NodeId id);

      /**
      * \brief Remove the instantiates edge from the node.
      * \param node [in] The end point of the instantiates edge.
      */
      void removeInstantiates(type::Type *node);

      /**
      * \brief Adds a new returns edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new returns edge.
      */
      void addReturns(const type::Type *node);

      /**
      * \brief Adds a new returns edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new returns edge.
      */
      void addReturns(NodeId id);

      /**
      * \brief Remove the returns edge by id from the node.
      * \param id [in] The end point of the returns edge.
      */
      void removeReturns(NodeId id);

      /**
      * \brief Remove the returns edge from the node.
      * \param node [in] The end point of the returns edge.
      */
      void removeReturns(type::Type *node);

      /**
      * \brief Adds a new throws edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new throws edge.
      */
      void addThrows(const type::Type *node);

      /**
      * \brief Adds a new throws edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new throws edge.
      */
      void addThrows(NodeId id);

      /**
      * \brief Remove the throws edge by id from the node.
      * \param id [in] The end point of the throws edge.
      */
      void removeThrows(NodeId id);

      /**
      * \brief Remove the throws edge from the node.
      * \param node [in] The end point of the throws edge.
      */
      void removeThrows(type::Type *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the accessesAttribute edge points to. */
      ListIterator<logical::AttributeAccess>::Container accessesAttributeContainer;

      /** \internal \brief Container stores the id of the nodes the calls edge points to. */
      ListIterator<logical::MethodCall>::Container callsContainer;

      /** \internal \brief Container stores the id of the nodes the canThrow edge points to. */
      ListIterator<type::Type>::Container canThrowContainer;

      /** \internal \brief Container stores the id of the nodes the hasControlFlowBlock edge points to. */
      ListIterator<base::ControlFlowBlock>::Container hasControlFlowBlockContainer;

      /** \internal \brief Container stores the id of the nodes the hasParameter edge points to. */
      ListIterator<logical::Parameter>::Container hasParameterContainer;

      /** \internal \brief Container stores the id of the nodes the instantiates edge points to. */
      ListIterator<type::Type>::Container instantiatesContainer;

      /** \internal \brief Container stores the id of the nodes the returns edge points to. */
      ListIterator<type::Type>::Container returnsContainer;

      /** \internal \brief Container stores the id of the nodes the throws edge points to. */
      ListIterator<type::Type>::Container throwsContainer;

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

