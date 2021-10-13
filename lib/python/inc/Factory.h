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

#ifndef _PYTHON_FACTORY_H_
#define _PYTHON_FACTORY_H_

#include "python/inc/python.h"

/**
* \file Factory.h
* \brief Contains declaration of Factory class.
*/

namespace columbus { namespace python { namespace asg {
  /**
  * \brief Factory, which handles (creates, deletes, sets their properties) nodes.
  */
  class Factory {
    protected:

      /** \internal \brief Type definition to store pointers to nodes. */
      typedef std::vector<base::Base*> Container;

    public:

      class SchemaPointerSorage {
        public:
          virtual ~SchemaPointerSorage(){};
          virtual void onDestroyNode(const base::Base* node) = 0;
      };

      /**
      * \brief Constructor.
      * \param st [in] Reference to the StrTable.
      */
      Factory(RefDistributorStrTable& st);

      /**
      * \brief Copy Constructor. It not implemented so it make a linker error if anybody want copy
      */
      Factory(const Factory&);

      /**
      * \brief Copy. It not implemented so it make a linker error if anybody want copy
      */
      Factory& operator=(const Factory&);

      /**
      * \brief Destructor.
      */
      virtual ~Factory();

      /**
      * \internal
      * \brief It is swap the string table ids to the other string table.
      * \param newStrTable [in] The new table
      */
      void swapStringTable(RefDistributorStrTable& newStrTable);

      /**
      * \brief Saves the graph.
      * \param filename [in] The graph is saved into this file.
      * \param header   [in] The header information (also will be saved).
      */
      void save(const std::string &filename , CsiHeader &header) const;

      /**
      * \brief Checks the graph header.
      * \param header [in] The header information.
      */
      void checkHeader(CsiHeader &header);

      /**
      * \brief Loads the graph header.
      * \param filename [in] The graph header is loaded from this file.
      * \param header   [in] The header information.
      */
      void loadHeader(const std::string &filename, CsiHeader &header);

      /**
      * \brief Loads the graph.
      * \param filename [in] The graph is loaded from this file.
      * \param header   [in] The header information (also will be loaded).
      */
      void load(const std::string &filename, CsiHeader &header);

      void clear();

      /**
      * \brief It can register for the node destroing event.
      * \param storage [in] The graph is loaded from this file.
      */
      void regPointerStorage(SchemaPointerSorage* storage);

      /**
      * \brief It can delete storage from destroling alert list.
      * \param storage [in] The graph is loaded from this file.
      */
      void unregPointerStorage(SchemaPointerSorage* storage);

      /**
      * \brief Gives back a pointer to the root node.
      * \return The pointer to the root node.
      */
      module::Package* getRoot() const;

      /**
      * \brief Decides whether it is a valid id or not.
      * \param id [in] The id whose validity is examined.
      * \return Returns true if a node belongs to the id.
      */
      bool getExist(NodeId id) const;

      /**
      * \brief Gives back a reference to the node.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if there is no node for the id.
      * \return Reference to the node.
      */
      base::Base& getRef(NodeId id) const;

      /**
      * \brief Gives back a pointer to the node.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if there is no node for the id.
      * \return Pointer to the node.
      */
      base::Base* getPointer(NodeId id) const;

      /**
      * \brief Gives back a reference to the StringTable.
      * \return Reference to the StringTable.
      */
      RefDistributorStrTable& getStringTable() const;

      /**
      * \brief Gives back the NodeKind of a node.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if there is no node for the id.
      * \return The NodeKind of the node.
      */
      NodeKind getNodeKind(NodeId id) const;

      /**
      * \brief Deletes the node with the given ID and every node in it's subtree.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if there is no node for the id.
      */
      void destroyNode(NodeId id);

      /**
      * \brief Deletes the node with the given ID without it's subtree.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if there is no node for the id.
      */
      void destroyThisNodeOnly(NodeId id);


      // ******************** ConstIterator ********************

      /**
      * \brief Nested constant iterator class which enumerates the nodes in the ASG.
      */
      class ConstIterator {
        private:

          /**
          * \internal
          * \brief Constructor for ConstIterator.
          * \param cont [in] Pointer to the Container
          * \param fact [in] Pointer to the Factory.
          */
          ConstIterator(const Container* cont, const Factory* fact);

        public:

          /**
          * \brief Examines the existence of the next node.
          * \return Returns true if a next node exists.
          */
          bool hasNext() const;

          /**
          * \brief Returns a constant reference of the next node (base::Base).
          * \return Reference of the next node.
          */
          const base::Base& next();

        private:

          /** \internal \brief Pointer to the Container. */
          const Container* container;

          /** \internal \brief Pointer to the Factory. */
          const Factory* factory;

          /** \internal \brief Iterator which stores the actual positon. */
          Container::const_iterator i;

          friend class Factory;
      };


      // ******************** iterator ********************

      /**
      * \brief Nested constant iterator class which enumerates the nodes in the ASG.
      */
      class const_iterator {
        private:

          /**
          * \internal
          * \brief Constructor for ConstIterator.
          * \param cont [in] Pointer to the Container
          * \param fact [in] Pointer to the Factory.
          */
          const_iterator(Container::const_iterator it,const Factory* fact):containerIt(it),fact(fact){while (containerIt != fact->container.end()  &&  ((*containerIt == NULL)  ||  fact->getIsFiltered(*containerIt))) containerIt++;}

          Container::const_iterator containerIt;
          const Factory* fact;
        public:

          const_iterator(const const_iterator& otherit) :containerIt (otherit.containerIt),fact(otherit.fact){}
          const_iterator& operator++() {containerIt++;  while (containerIt != fact->container.end()  &&  ((*containerIt == NULL)   ||  fact->getIsFiltered(*containerIt))) containerIt++; return *this;}
          const_iterator operator++(int) {const_iterator tmp(*this); operator++(); return tmp;}
          bool operator==(const const_iterator& rhs) {return containerIt==rhs.containerIt;}
          bool operator!=(const const_iterator& rhs) {return containerIt!=rhs.containerIt;}
          const base::Base* operator*() {return *containerIt;}
          friend class Factory;
      };

      /**
      * \brief Get the iterator for the nodes
      * \return An iterator to the nodes.
      */
      const const_iterator begin() const{return const_iterator(container.begin(),this);}

      /**
      * \brief Get the iterator for the nodes.
      * \return An iterator to the nodes.
      */
      const const_iterator end() const {return const_iterator(container.end(),this);}

      /**
      * \brief Creates and returns a constant iterator, which enumerates the nodes in the ASG.
      * \return An iterator to the nodes.
      */
      const ConstIterator constIterator() const;

      /**
      * \brief Tells whether the ASG has nodes (O(n)).
      * \return Returns true if there is not any node.
      */
      bool isEmpty() const;

      /**
      * \brief Returns the number of nodes in the ASG.
      * \return The number of nodes in the ASG.
      */
      unsigned size() const;

      /**
      * \brief get the node individualiy state.
      */
      bool isIndividual(NodeId id) const {return container[id] && (container[id]->getParent()==0);}


      // ******************** Filter ********************

      /**
      * \brief Turns the Filter on.
      */
      void turnFilterOn();

      /**
      * \brief Turns the Filter off.
      */
      void turnFilterOff();

      /**
      * \brief A solution to turn Filter off safely.
      */
      class TurnFilterOffSafely {
        public:

          /**
          * \brief Constructor to turn Filter off safely.
          * \param fact [in] Reference to the Factory.
          */
          TurnFilterOffSafely(Factory &fact);

          /**
          * \brief Constructor to turn Filter off safely.
          * \param fact [in] Reference to the Factory.
          */
          TurnFilterOffSafely(const Factory &fact);

          /**
          * \brief Destructor which restores the Filter to its original state .
          */
          ~TurnFilterOffSafely();

        private:
          /** \internal \brief Prevents dynamic instantiation (but does nothing). */
          void* operator new (size_t) throw();

          /** \internal \brief Prevents dynamic instantiation (but does nothing). */
          void* operator new[] (size_t) throw();

          /** \internal \brief Reference to the Factory. */
          Factory& factory;

          /** \internal \brief The original state of the Filter. */
          bool oldState;

      };

      /**
      * \brief Gives back the state of the Filter.
      * \return Returns true if the Filter is turned on, otherwise returns false.
      */
      bool getIsFilterTurnedOn() const;

      /**
      * \brief Initializes the filter (see Filter::initializeFilter() for more details).
      */
      void initializeFilter();

      /**
      * \brief Tells whether the given node is filtered or not.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the ASG).
      * \return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
      */
      bool getIsFiltered(NodeId id) const;

      /**
      * \brief Tells whether the given node is filtered or not.
      * \param node            [in] The pointer to the node.
      * \return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
      */
      bool getIsFiltered(const base::Base* node) const;

      /**
      * \brief Filters out the given node and all of its descendants.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException id the id is too large (larger than the size of the Filter).
      */
      void setFiltered(NodeId id);

      /**
      * \brief Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException id the id is too large (larger than the size of the Filter).
      */
      void setNotFiltered(NodeId id);

      /**
      * \brief Sets the state of the node and all of its ancestors to not filtered.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException id the id is too large (larger than the size of the Filter).
      */
      void setNotFilteredThisNode(NodeId id);

      /**
      * \brief Gives back the filter state (python::Filter::FilterStae) of the given node irrespectively of the state of the filter mode.
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException if the id is too large (larger than the size of the ASG).
      * \return Returns with the state of the filter.
      */
      Filter::FilterState getFilterState(NodeId id) const;

      /**
      * \brief Loads the filter.
      * \param filename    [in] The name of the filter file.
      * \throw PythonException Throws PythonException if the filter contains more (or less) node than the factory does.
      * \throw IOException Throws IOException if any error happens during the loading.
      */
      void loadFilter(const std::string &filename);

      /**
      * \brief Saves the filter.
      * \param filename    [in] The name of the filter file.
      * \throw IOException Throws IOException if any error happens during the saving.
      */
      void saveFilter(const std::string &filename) const;

      /**
      * \internal
      * \brief Filter out only the given node (without its children).
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException id the id is too large (larger than the size of the Filter).
      */
      void setFilteredThisNodeOnly(NodeId id);

      /**
      * \internal
      * \brief Set only the given node to not filtered (without its children).
      * \param id              [in] The id of the node.
      * \throw PythonException Throws PythonException id the id is too large (larger than the size of the Filter).
      */
      void setNotFilteredThisNodeOnly(NodeId id);

    public:


      // ******************** ReverseEdges ********************

      /**
      * \brief Creates reverse edges (if it does not exist) and it can be used until disabling it.
      */
      void enableReverseEdges(ReverseEdges::FuncPtrWithBaseParameterType newSelector = NULL);

      /**
      * \brief Destroyed reverse edges (to use it again it must be rebuilt which takes some time).
      */
      void disableReverseEdges();

      /**
      * \brief Gives back the reverse edge container which is assigned to this Factory (creates it if it does not exist).
      * \return Returns with the const reference to the ReverseEdges.
      */
      const ReverseEdges& getReverseEdges(ReverseEdges::FuncPtrWithBaseParameterType newSelector = NULL);

      /**
      * \brief Checks whether the reverse edges has already been created or not.
      * \return Returns true if ReverseEdges exists.
      */
      bool getExistsReverseEdges() const;


      // ******************** CreateNode ********************

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \param ndk             [in] The kind of the node.
      * \throw PythonException If an invalid (or an abstract) NodeKind is given, PythonException is thrown.
      * \return Pointer to the new node.
      */
      base::Base* createNode(NodeKind ndk);

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ArgumentList* createArgumentListNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AttributeRef* createAttributeRefNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Await* createAwaitNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::BinaryArithmetic* createBinaryArithmeticNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::BinaryLogical* createBinaryLogicalNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::BytesLiteral* createBytesLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Call* createCallNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::DictComp* createDictCompNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Dictionary* createDictionaryNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Ellipsis* createEllipsisNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ExpressionList* createExpressionListNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ExtSlice* createExtSliceNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::FloatNumber* createFloatNumberNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::FormattedValue* createFormattedValueNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Generator* createGeneratorNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::GeneratorExpression* createGeneratorExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Identifier* createIdentifierNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::IfExpression* createIfExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ImagNumber* createImagNumberNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Index* createIndexNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::IntegerLiteral* createIntegerLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::JoinedStr* createJoinedStrNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::KeyValue* createKeyValueNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Keyword* createKeywordNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Lambda* createLambdaNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::List* createListNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ListComp* createListCompNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::LongInteger* createLongIntegerNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::NamedExpr* createNamedExprNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Set* createSetNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::SetComp* createSetCompNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Slice* createSliceNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Starred* createStarredNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::StringConversion* createStringConversionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::StringLiteral* createStringLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Subscription* createSubscriptionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::UnaryOperation* createUnaryOperationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::YieldExpression* createYieldExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      module::Module* createModuleNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      module::Object* createObjectNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      module::Package* createPackageNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Alias* createAliasNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::AnnAssign* createAnnAssignNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Assert* createAssertNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Assign* createAssignNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::AugAssign* createAugAssignNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::BaseSpecifier* createBaseSpecifierNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Break* createBreakNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ClassDef* createClassDefNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Continue* createContinueNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Delete* createDeleteNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Exec* createExecNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::For* createForNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::FunctionDef* createFunctionDefNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Global* createGlobalNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Handler* createHandlerNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::If* createIfNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ImportFrom* createImportFromNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ImportStatement* createImportStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Nonlocal* createNonlocalNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Parameter* createParameterNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Pass* createPassNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Print* createPrintNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Raise* createRaiseNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Return* createReturnNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Suite* createSuiteNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::TargetList* createTargetListNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Try* createTryNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::While* createWhileNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::With* createWithNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::WithItem* createWithItemNode();

      /**
      * \brief Flush the node Sizes to the default out
      */
      static void printNodeSizes();


      // ******************** Unique node builders ********************

    private:

      /**
      * \internal
      * \brief Creates a new node, insert it into the container and return with it.
      * \param ndk             [in] The kind of the node.
      * \param id              [in] The id of the new node.
      * \throw PythonException If an invalid (or an abstract) NodeKind is given, PythonException is thrown.
      * \return Reference to the new node.
      */
      base::Base& createNode(NodeKind ndk, NodeId id);

      /**
      * \internal
      * \brief This function is call the alert list.
      * \param node [in] The node which is going to destroy.
      */
      void alertNodeDestroy(const base::Base* node);

    private:


      // ******************** Private attributes ********************

      /** \internal \brief Container where the pointers to nodes are stored. */
      Container container;

      /** \internal \brief Reference to the StringTable. */
      RefDistributorStrTable* strTable;

      /** \internal \brief The Filter of the ASG. */
      Filter *filter;

      /** \internal \brief Stores whether the filter is turned on or off. */
      bool filterOn;

      /** \internal \brief Pointer to the ReverseEdges. */
      ReverseEdges *reverseEdges;

      typedef struct EdgeIdentifier {
        EdgeIdentifier(base::Base* edgeBegin, NodeId edgeEnd, EdgeKind edgekind) : edgeBegin(edgeBegin), edgeEnd(edgeEnd), edgekind(edgekind) {}
        base::Base* edgeBegin;
        NodeId edgeEnd;
        EdgeKind edgekind;
      } EdgeIdentifier;

      /** \internal \brief The subcripted object for the node destroy. */
      std::list<SchemaPointerSorage*> registeredPointerStorage;

      /** \internal \brief Pointer to the root of the ASG. */
      module::Package *root;

      /** \internal \brief List of the ids of the deleted nodes. */
      std::list<NodeId> deletedNodeIdList;

      friend class VisitorFilter;

      friend class base::Base;
      friend class base::Comment;
      friend class base::Docstring;
      friend class base::Named;
      friend class base::Positioned;
      friend class expression::ArgumentList;
      friend class expression::AttributeRef;
      friend class expression::Await;
      friend class expression::Binary;
      friend class expression::BinaryArithmetic;
      friend class expression::BinaryLogical;
      friend class expression::BytesLiteral;
      friend class expression::Call;
      friend class expression::DictComp;
      friend class expression::Dictionary;
      friend class expression::Ellipsis;
      friend class expression::Expression;
      friend class expression::ExpressionList;
      friend class expression::ExtSlice;
      friend class expression::FloatNumber;
      friend class expression::FormattedValue;
      friend class expression::Generator;
      friend class expression::GeneratorExpression;
      friend class expression::Identifier;
      friend class expression::IfExpression;
      friend class expression::ImagNumber;
      friend class expression::Index;
      friend class expression::IntegerLiteral;
      friend class expression::JoinedStr;
      friend class expression::KeyValue;
      friend class expression::Keyword;
      friend class expression::Lambda;
      friend class expression::List;
      friend class expression::ListComp;
      friend class expression::Literal;
      friend class expression::LongInteger;
      friend class expression::NamedExpr;
      friend class expression::Set;
      friend class expression::SetComp;
      friend class expression::Slice;
      friend class expression::Slicing;
      friend class expression::Starred;
      friend class expression::StringConversion;
      friend class expression::StringLiteral;
      friend class expression::Subscription;
      friend class expression::Unary;
      friend class expression::UnaryOperation;
      friend class expression::YieldExpression;
      friend class module::Module;
      friend class module::Object;
      friend class module::Package;
      friend class statement::Alias;
      friend class statement::AnnAssign;
      friend class statement::Assert;
      friend class statement::Assign;
      friend class statement::AugAssign;
      friend class statement::BaseSpecifier;
      friend class statement::Break;
      friend class statement::ClassDef;
      friend class statement::CompoundStatement;
      friend class statement::Continue;
      friend class statement::Delete;
      friend class statement::Exec;
      friend class statement::For;
      friend class statement::FunctionDef;
      friend class statement::Global;
      friend class statement::Handler;
      friend class statement::If;
      friend class statement::ImportFrom;
      friend class statement::ImportStatement;
      friend class statement::Iteration;
      friend class statement::Nonlocal;
      friend class statement::Parameter;
      friend class statement::Pass;
      friend class statement::Print;
      friend class statement::Raise;
      friend class statement::Return;
      friend class statement::SimpleStatement;
      friend class statement::Statement;
      friend class statement::Suite;
      friend class statement::TargetList;
      friend class statement::Try;
      friend class statement::While;
      friend class statement::With;
      friend class statement::WithItem;
      friend class type::DictType;
      friend class type::ReferenceType;
      friend class type::SequenceType;
      friend class type::SimpleType;
      friend class type::Type;

    protected:
      std::map<SimpleTypeKind, NodeId> simpleType;
      std::map<SequenceTypeKind, NodeId> sequenceType;
      std::map<NodeId, NodeId> referenceType;
      NodeId dictType;

    public:

      type::SimpleType& createSimpleType(SimpleTypeKind kind);

      type::SequenceType& createSequenceType(SequenceTypeKind kind);

      type::DictType& createDictType();

      type::ReferenceType& createReferenceType(NodeId refersTo);

      base::Docstring& createDocstring();

      base::Comment& createComment();

  }; // Factory


}}}
#endif

