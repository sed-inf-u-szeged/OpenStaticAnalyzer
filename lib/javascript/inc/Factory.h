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

#ifndef _JAVASCRIPT_FACTORY_H_
#define _JAVASCRIPT_FACTORY_H_

#include "javascript/inc/javascript.h"

/**
* \file Factory.h
* \brief Contains declaration of Factory class.
*/

namespace columbus { namespace javascript { namespace asg {
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
      void save(const std::string &filename , std::list<HeaderData*> &headerDataList, bool zip = false) const;

      /**
      * \brief Saves the graph.
      * \param zipIo [in] The graph is saved into this file.
      * \param header   [in] The header information (also will be saved).
      */
      void save(io::ZippedIO &zipIo, std::list<HeaderData*> &headerDataList, bool zip = false) const;

      /**
      * \brief Saves the graph.
      * \param filename [in] The graph is saved into this file.
      * \param header   [in] The header information (also will be saved).
      */
      void save(const std::string &filename , std::list<HeaderData*> &headerDataList, std::streampos& startPos, bool zip = false) const;

      /**
      * \brief Parse the property data file data.
      * \param propertyData [in] The property data file.
      */
      void checkPropertyData( PropertyData& propertyData) ;
      /**
      * \brief Loads the graph header.
      * \param filename [in] The graph header is loaded from this file.
      * \param header   [in] The header information.
      */
      void loadHeader(const std::string &filename,const std::list<HeaderData*> &headerDataList);

      /**
      * \brief Loads the graph.
      * \param filename [in] The graph is loaded from this file.
      * \param header   [in] The header information (also will be loaded).
      */
      void load(const std::string &filename , std::list<HeaderData*> &headerDataList);

      void load(io::ZippedIO &zipIo, const std::list<HeaderData*> &headerDataList);

      void load( const std::string &filename , std::list<HeaderData*> &headerDataList, std::streampos& startPosition);

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
      base::System* getRoot() const;

      /**
      * \brief Decides whether it is a valid id or not.
      * \param id [in] The id whose validity is examined.
      * \return Returns true if a node belongs to the id.
      */
      bool getExist(NodeId id) const;

      /**
      * \brief Gives back a reference to the node.
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException if there is no node for the id.
      * \return Reference to the node.
      */
      base::Base& getRef(NodeId id) const;

      /**
      * \brief Gives back a pointer to the node.
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException if there is no node for the id.
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
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException if there is no node for the id.
      * \return The NodeKind of the node.
      */
      NodeKind getNodeKind(NodeId id) const;

      /**
      * \brief Deletes the node with the given ID and every node in it's subtree.
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException if there is no node for the id.
      */
      void destroyNode(NodeId id);

      /**
      * \brief Deletes the node with the given ID without it's subtree.
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException if there is no node for the id.
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
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException if the id is too large (larger than the size of the ASG).
      * \return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
      */
      bool getIsFiltered(NodeId id) const;

      /**
      * \brief Tells whether the given node is filtered or not.
      * \param node                [in] The pointer to the node.
      * \return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
      */
      bool getIsFiltered(const base::Base* node) const;

      /**
      * \brief Filters out the given node and all of its descendants.
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException id the id is too large (larger than the size of the Filter).
      */
      void setFiltered(NodeId id);

      /**
      * \brief Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException id the id is too large (larger than the size of the Filter).
      */
      void setNotFiltered(NodeId id);

      /**
      * \brief Sets the state of the node and all of its ancestors to not filtered.
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException id the id is too large (larger than the size of the Filter).
      */
      void setNotFilteredThisNode(NodeId id);

      /**
      * \brief Gives back the filter state (javascript::Filter::FilterStae) of the given node irrespectively of the state of the filter mode.
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException if the id is too large (larger than the size of the ASG).
      * \return Returns with the state of the filter.
      */
      Filter::FilterState getFilterState(NodeId id) const;

      /**
      * \brief Loads the filter.
      * \param filename    [in] The name of the filter file.
      * \throw JavaScriptException Throws JavaScriptException if the filter contains more (or less) node than the factory does.
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
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException id the id is too large (larger than the size of the Filter).
      */
      void setFilteredThisNodeOnly(NodeId id);

      /**
      * \internal
      * \brief Set only the given node to not filtered (without its children).
      * \param id                  [in] The id of the node.
      * \throw JavaScriptException Throws JavaScriptException id the id is too large (larger than the size of the Filter).
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
      * \param ndk                 [in] The kind of the node.
      * \throw JavaScriptException If an invalid (or an abstract) NodeKind is given, JavaScriptException is thrown.
      * \return Pointer to the new node.
      */
      base::Base* createNode(NodeKind ndk);

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      base::Comment* createCommentNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      base::Program* createProgramNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      base::System* createSystemNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::ClassDeclaration* createClassDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::ExportAllDeclaration* createExportAllDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::ExportDefaultDeclaration* createExportDefaultDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::ExportNamedDeclaration* createExportNamedDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::FunctionDeclaration* createFunctionDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::ImportDeclaration* createImportDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::ModuleDeclaration* createModuleDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::VariableDeclaration* createVariableDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      declaration::VariableDeclarator* createVariableDeclaratorNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ArrayExpression* createArrayExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ArrowFunctionExpression* createArrowFunctionExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AssignmentExpression* createAssignmentExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AssignmentProperty* createAssignmentPropertyNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AwaitExpression* createAwaitExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::BinaryExpression* createBinaryExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::BooleanLiteral* createBooleanLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::CallExpression* createCallExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ClassExpression* createClassExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ConditionalExpression* createConditionalExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::FunctionExpression* createFunctionExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Identifier* createIdentifierNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::LogicalExpression* createLogicalExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::MemberExpression* createMemberExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::MetaProperty* createMetaPropertyNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::NewExpression* createNewExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::NullLiteral* createNullLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::NumberLiteral* createNumberLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ObjectExpression* createObjectExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Property* createPropertyNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::RegExpLiteral* createRegExpLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::SequenceExpression* createSequenceExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::SpreadElement* createSpreadElementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::StringLiteral* createStringLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::Super* createSuperNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::TaggedTemplateExpression* createTaggedTemplateExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::TemplateElement* createTemplateElementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::TemplateLiteral* createTemplateLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ThisExpression* createThisExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::UnaryExpression* createUnaryExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::UpdateExpression* createUpdateExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::YieldExpression* createYieldExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ArrayPattern* createArrayPatternNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::AssignmentPattern* createAssignmentPatternNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::BlockStatement* createBlockStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::BreakStatement* createBreakStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::CatchClause* createCatchClauseNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ContinueStatement* createContinueStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::DebuggerStatement* createDebuggerStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::DoWhileStatement* createDoWhileStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::EmptyStatement* createEmptyStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ExpressionStatement* createExpressionStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ForInStatement* createForInStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ForOfStatement* createForOfStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ForStatement* createForStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::Function* createFunctionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::IfStatement* createIfStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::LabeledStatement* createLabeledStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ObjectPattern* createObjectPatternNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::RestElement* createRestElementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ReturnStatement* createReturnStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::SwitchCase* createSwitchCaseNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::SwitchStatement* createSwitchStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ThrowStatement* createThrowStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::TryStatement* createTryStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::WhileStatement* createWhileStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::WithStatement* createWithStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ClassBody* createClassBodyNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ExportSpecifier* createExportSpecifierNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ImportDefaultSpecifier* createImportDefaultSpecifierNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ImportNamespaceSpecifier* createImportNamespaceSpecifierNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ImportSpecifier* createImportSpecifierNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::MethodDefinition* createMethodDefinitionNode();

      /**
      * \brief Flush the node Sizes to the default out
      */
      static void printNodeSizes();

      /**
      * \brief Creates statistics about the ASG (and writes it to the standard output if message level is to Debug).
      */
      void createAsgStat() const;

      /**
      * \brief Creates statistics about the ASG  (and writes it to the standard output if message level is to Debug).
      * \param allNodesStat      [in] Statistic is created about all nodes in the graph.
      * \param usedNodesStatOnly [in] Statistic is created about the used nodes only.
      * \param edgeStat          [in] Statistic is created about the edges as well.
      */
      void createAsgStat(bool allNodesStat, bool usedNodesStatOnly, bool edgeStat) const;


      // ******************** Unique node builders ********************

    private:

      /**
      * \internal
      * \brief Creates a new node, insert it into the container and return with it.
      * \param ndk                 [in] The kind of the node.
      * \param id                  [in] The id of the new node.
      * \throw JavaScriptException If an invalid (or an abstract) NodeKind is given, JavaScriptException is thrown.
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

      /**
      * \internal
      * \brief Loads the graph header.
      * \param binIo [in] The file from which the header will be loaded.
      * \param header   [in] The header information.
      */
      void loadHeader(io::BinaryIO &binIo, const std::list<HeaderData*> &headerDataList);


      // ******************** Private attributes ********************

      /** \internal \brief Container which contains the unrequested header data. */
      std::vector<std::pair<unsigned short, std::vector< unsigned char > > > unknownHeaderData;

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
      base::System *root;

      /** \internal \brief List of the ids of the deleted nodes. */
      std::list<NodeId> deletedNodeIdList;

      friend class VisitorFilter;

      friend class base::Base;
      friend class base::Comment;
      friend class base::Named;
      friend class base::Positioned;
      friend class base::Program;
      friend class base::System;
      friend class declaration::ClassDeclaration;
      friend class declaration::Declaration;
      friend class declaration::ExportAllDeclaration;
      friend class declaration::ExportDefaultDeclaration;
      friend class declaration::ExportNamedDeclaration;
      friend class declaration::FunctionDeclaration;
      friend class declaration::ImportDeclaration;
      friend class declaration::ModuleDeclaration;
      friend class declaration::VariableDeclaration;
      friend class declaration::VariableDeclarator;
      friend class expression::ArrayExpression;
      friend class expression::ArrowFunctionExpression;
      friend class expression::AssignmentExpression;
      friend class expression::AssignmentProperty;
      friend class expression::AwaitExpression;
      friend class expression::BinaryExpression;
      friend class expression::BooleanLiteral;
      friend class expression::CallExpression;
      friend class expression::ClassExpression;
      friend class expression::ConditionalExpression;
      friend class expression::Expression;
      friend class expression::FunctionExpression;
      friend class expression::Identifier;
      friend class expression::Literal;
      friend class expression::LogicalExpression;
      friend class expression::MemberExpression;
      friend class expression::MetaProperty;
      friend class expression::NewExpression;
      friend class expression::NullLiteral;
      friend class expression::NumberLiteral;
      friend class expression::ObjectExpression;
      friend class expression::Property;
      friend class expression::RegExpLiteral;
      friend class expression::SequenceExpression;
      friend class expression::SpreadElement;
      friend class expression::StringLiteral;
      friend class expression::Super;
      friend class expression::TaggedTemplateExpression;
      friend class expression::TemplateElement;
      friend class expression::TemplateLiteral;
      friend class expression::ThisExpression;
      friend class expression::UnaryExpression;
      friend class expression::UpdateExpression;
      friend class expression::YieldExpression;
      friend class statement::ArrayPattern;
      friend class statement::AssignmentPattern;
      friend class statement::BlockStatement;
      friend class statement::BreakStatement;
      friend class statement::CatchClause;
      friend class statement::ContinueStatement;
      friend class statement::DebuggerStatement;
      friend class statement::DoWhileStatement;
      friend class statement::EmptyStatement;
      friend class statement::ExpressionStatement;
      friend class statement::ForInStatement;
      friend class statement::ForOfStatement;
      friend class statement::ForStatement;
      friend class statement::Function;
      friend class statement::IfStatement;
      friend class statement::LabeledStatement;
      friend class statement::ObjectPattern;
      friend class statement::Pattern;
      friend class statement::RestElement;
      friend class statement::ReturnStatement;
      friend class statement::Statement;
      friend class statement::SwitchCase;
      friend class statement::SwitchStatement;
      friend class statement::ThrowStatement;
      friend class statement::TryStatement;
      friend class statement::WhileStatement;
      friend class statement::WithStatement;
      friend class structure::Class;
      friend class structure::ClassBody;
      friend class structure::ExportSpecifier;
      friend class structure::ImpSpecifier;
      friend class structure::ImportDefaultSpecifier;
      friend class structure::ImportNamespaceSpecifier;
      friend class structure::ImportSpecifier;
      friend class structure::MethodDefinition;
      friend class structure::ModuleSpecifier;

  }; // Factory


}}}
#endif

