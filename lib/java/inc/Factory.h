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

#ifndef _JAVA_FACTORY_H_
#define _JAVA_FACTORY_H_

#include "java/inc/java.h"

/**
* \file Factory.h
* \brief Contains declaration of Factory class.
*/

namespace columbus { namespace java { namespace asg {
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
      struc::Package* getRoot() const;

      /**
      * \brief Decides whether it is a valid id or not.
      * \param id [in] The id whose validity is examined.
      * \return Returns true if a node belongs to the id.
      */
      bool getExist(NodeId id) const;

      /**
      * \brief Gives back a reference to the node.
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException if there is no node for the id.
      * \return Reference to the node.
      */
      base::Base& getRef(NodeId id) const;

      /**
      * \brief Gives back a pointer to the node.
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException if there is no node for the id.
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
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException if there is no node for the id.
      * \return The NodeKind of the node.
      */
      NodeKind getNodeKind(NodeId id) const;

      /**
      * \brief Deletes the node with the given ID and every node in it's subtree.
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException if there is no node for the id.
      */
      void destroyNode(NodeId id);

      /**
      * \brief Deletes the node with the given ID without it's subtree.
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException if there is no node for the id.
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
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException if the id is too large (larger than the size of the ASG).
      * \return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
      */
      bool getIsFiltered(NodeId id) const;

      /**
      * \brief Tells whether the given node is filtered or not.
      * \param node          [in] The pointer to the node.
      * \return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
      */
      bool getIsFiltered(const base::Base* node) const;

      /**
      * \brief Filters out the given node and all of its descendants.
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
      */
      void setFiltered(NodeId id);

      /**
      * \brief Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
      */
      void setNotFiltered(NodeId id);

      /**
      * \brief Sets the state of the node and all of its ancestors to not filtered.
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
      */
      void setNotFilteredThisNode(NodeId id);

      /**
      * \brief Gives back the filter state (java::Filter::FilterStae) of the given node irrespectively of the state of the filter mode.
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException if the id is too large (larger than the size of the ASG).
      * \return Returns with the state of the filter.
      */
      Filter::FilterState getFilterState(NodeId id) const;

      /**
      * \brief Loads the filter.
      * \param filename    [in] The name of the filter file.
      * \throw JavaException Throws JavaException if the filter contains more (or less) node than the factory does.
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
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
      */
      void setFilteredThisNodeOnly(NodeId id);

      /**
      * \internal
      * \brief Set only the given node to not filtered (without its children).
      * \param id            [in] The id of the node.
      * \throw JavaException Throws JavaException id the id is too large (larger than the size of the Filter).
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
      * \param ndk           [in] The kind of the node.
      * \throw JavaException If an invalid (or an abstract) NodeKind is given, JavaException is thrown.
      * \return Pointer to the new node.
      */
      base::Base* createNode(NodeKind ndk);

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::ArrayAccess* createArrayAccessNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::ArrayTypeExpression* createArrayTypeExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::Assignment* createAssignmentNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::BooleanLiteral* createBooleanLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::CharacterLiteral* createCharacterLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::ClassLiteral* createClassLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::Conditional* createConditionalNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::DoubleLiteral* createDoubleLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::Erroneous* createErroneousNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::ErroneousTypeExpression* createErroneousTypeExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::ExternalTypeExpression* createExternalTypeExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::FieldAccess* createFieldAccessNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::FloatLiteral* createFloatLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::Identifier* createIdentifierNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::InfixExpression* createInfixExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::InstanceOf* createInstanceOfNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::IntegerLiteral* createIntegerLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::LongLiteral* createLongLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::MarkerAnnotation* createMarkerAnnotationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::MethodInvocation* createMethodInvocationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::NewArray* createNewArrayNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::NewClass* createNewClassNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::NormalAnnotation* createNormalAnnotationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::NullLiteral* createNullLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::ParenthesizedExpression* createParenthesizedExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::PostfixExpression* createPostfixExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::PrefixExpression* createPrefixExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::PrimitiveTypeExpression* createPrimitiveTypeExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::QualifiedTypeExpression* createQualifiedTypeExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::SimpleTypeExpression* createSimpleTypeExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::SingleElementAnnotation* createSingleElementAnnotationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::StringLiteral* createStringLiteralNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::Super* createSuperNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::This* createThisNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::TypeApplyExpression* createTypeApplyExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::TypeCast* createTypeCastNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::TypeUnionExpression* createTypeUnionExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expr::WildcardExpression* createWildcardExpressionNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Assert* createAssertNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::BasicFor* createBasicForNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Block* createBlockNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Break* createBreakNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Case* createCaseNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Continue* createContinueNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Default* createDefaultNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Do* createDoNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Empty* createEmptyNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::EnhancedFor* createEnhancedForNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::ExpressionStatement* createExpressionStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Handler* createHandlerNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::If* createIfNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::LabeledStatement* createLabeledStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Return* createReturnNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Switch* createSwitchNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Synchronized* createSynchronizedNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Throw* createThrowNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::Try* createTryNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statm::While* createWhileNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::AnnotationType* createAnnotationTypeNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::AnnotationTypeElement* createAnnotationTypeElementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::AnonymousClass* createAnonymousClassNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::Class* createClassNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::ClassGeneric* createClassGenericNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::CompilationUnit* createCompilationUnitNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::Enum* createEnumNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::EnumConstant* createEnumConstantNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::Import* createImportNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::InstanceInitializerBlock* createInstanceInitializerBlockNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::Interface* createInterfaceNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::InterfaceGeneric* createInterfaceGenericNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::Method* createMethodNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::MethodGeneric* createMethodGenericNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::Package* createPackageNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::PackageDeclaration* createPackageDeclarationNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::Parameter* createParameterNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::StaticInitializerBlock* createStaticInitializerBlockNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::TypeParameter* createTypeParameterNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      struc::Variable* createVariableNode();

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

      /**
      * \brief Traverses the nodes and sorts some of their specific edges. The iterators that were created before sorting will be invalid.
      */
      void sort();


      // ******************** Unique node builders ********************

    private:

      /**
      * \internal
      * \brief Creates a new node, insert it into the container and return with it.
      * \param ndk           [in] The kind of the node.
      * \param id            [in] The id of the new node.
      * \throw JavaException If an invalid (or an abstract) NodeKind is given, JavaException is thrown.
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
      struc::Package *root;

      /** \internal \brief List of the ids of the deleted nodes. */
      std::list<NodeId> deletedNodeIdList;

      friend class VisitorFilter;

      friend class base::Base;
      friend class base::BlockComment;
      friend class base::Comment;
      friend class base::Commentable;
      friend class base::JavadocComment;
      friend class base::LineComment;
      friend class base::Named;
      friend class base::NonJavadocComment;
      friend class base::Positioned;
      friend class base::PositionedWithoutComment;
      friend class expr::Annotation;
      friend class expr::ArrayAccess;
      friend class expr::ArrayTypeExpression;
      friend class expr::Assignment;
      friend class expr::Binary;
      friend class expr::BooleanLiteral;
      friend class expr::CharacterLiteral;
      friend class expr::ClassLiteral;
      friend class expr::Conditional;
      friend class expr::DoubleLiteral;
      friend class expr::Erroneous;
      friend class expr::ErroneousTypeExpression;
      friend class expr::Expression;
      friend class expr::ExternalTypeExpression;
      friend class expr::FieldAccess;
      friend class expr::FloatLiteral;
      friend class expr::Identifier;
      friend class expr::InfixExpression;
      friend class expr::InstanceOf;
      friend class expr::IntegerLiteral;
      friend class expr::Literal;
      friend class expr::LongLiteral;
      friend class expr::MarkerAnnotation;
      friend class expr::MethodInvocation;
      friend class expr::NewArray;
      friend class expr::NewClass;
      friend class expr::NormalAnnotation;
      friend class expr::NullLiteral;
      friend class expr::NumberLiteral;
      friend class expr::ParenthesizedExpression;
      friend class expr::PostfixExpression;
      friend class expr::PrefixExpression;
      friend class expr::PrimitiveTypeExpression;
      friend class expr::QualifiedTypeExpression;
      friend class expr::SimpleTypeExpression;
      friend class expr::SingleElementAnnotation;
      friend class expr::StringLiteral;
      friend class expr::Super;
      friend class expr::This;
      friend class expr::TypeApplyExpression;
      friend class expr::TypeCast;
      friend class expr::TypeExpression;
      friend class expr::TypeUnionExpression;
      friend class expr::Unary;
      friend class expr::WildcardExpression;
      friend class statm::Assert;
      friend class statm::BasicFor;
      friend class statm::Block;
      friend class statm::Break;
      friend class statm::Case;
      friend class statm::Continue;
      friend class statm::Default;
      friend class statm::Do;
      friend class statm::Empty;
      friend class statm::EnhancedFor;
      friend class statm::ExpressionStatement;
      friend class statm::For;
      friend class statm::Handler;
      friend class statm::If;
      friend class statm::Iteration;
      friend class statm::Jump;
      friend class statm::LabeledStatement;
      friend class statm::Return;
      friend class statm::Selection;
      friend class statm::Statement;
      friend class statm::Switch;
      friend class statm::SwitchLabel;
      friend class statm::Synchronized;
      friend class statm::Throw;
      friend class statm::Try;
      friend class statm::While;
      friend class struc::AnnotatedElement;
      friend class struc::AnnotationType;
      friend class struc::AnnotationTypeElement;
      friend class struc::AnonymousClass;
      friend class struc::Class;
      friend class struc::ClassDeclaration;
      friend class struc::ClassGeneric;
      friend class struc::CompilationUnit;
      friend class struc::Declaration;
      friend class struc::Enum;
      friend class struc::EnumConstant;
      friend class struc::GenericDeclaration;
      friend class struc::Import;
      friend class struc::InitializerBlock;
      friend class struc::InstanceInitializerBlock;
      friend class struc::Interface;
      friend class struc::InterfaceDeclaration;
      friend class struc::InterfaceGeneric;
      friend class struc::Member;
      friend class struc::Method;
      friend class struc::MethodDeclaration;
      friend class struc::MethodGeneric;
      friend class struc::NamedDeclaration;
      friend class struc::NormalMethod;
      friend class struc::Package;
      friend class struc::PackageDeclaration;
      friend class struc::Parameter;
      friend class struc::Scope;
      friend class struc::StaticInitializerBlock;
      friend class struc::TypeDeclaration;
      friend class struc::TypeParameter;
      friend class struc::Variable;
      friend class struc::VariableDeclaration;
      friend class type::ArrayType;
      friend class type::BooleanType;
      friend class type::BoundedWildcardType;
      friend class type::ByteType;
      friend class type::CharType;
      friend class type::ClassType;
      friend class type::DoubleType;
      friend class type::ErrorType;
      friend class type::FloatType;
      friend class type::IntType;
      friend class type::LongType;
      friend class type::LowerBoundedWildcardType;
      friend class type::MethodType;
      friend class type::NoType;
      friend class type::NullType;
      friend class type::PackageType;
      friend class type::ParameterizedType;
      friend class type::PrimitiveType;
      friend class type::ScopedType;
      friend class type::ShortType;
      friend class type::Type;
      friend class type::TypeVariable;
      friend class type::UnboundedWildcardType;
      friend class type::UnionType;
      friend class type::UpperBoundedWildcardType;
      friend class type::VoidType;
      friend class type::WildcardType;


    private:

      typedef std::map<NodeId, std::string> UniqueNameMapType;

      /** \internal \brief Map for already generated unique names. */
      UniqueNameMapType uniqueNameMap;

      friend std::string Common::getUniqueNameForBase(const base::Base &node);
      friend std::string Common::getUniqueNameForType(const type::Type &node);

      friend class linker::LinkerBase;
      friend class linker::VisitorLinker;

      Container apspecNodes;

      base::Base* createSimpleAPSpecNodeSafely(NodeKind ndk, NodeId id);

      void init();

    public:

      /**
      * \brief Replaces the given Class, Interface or Method node with its generic version.
      * \throw JavaException Throws JavaException if non of the above node types are specified.
      * \return Pointer to the new node.
      */
      base::Base* replaceNode(base::Base &node);

      /**
      * \brief Returns the single AP_SPEC node for the given NodeKind (only primitives, null, no and error types).
      * \throw JavaException Throws JavaException if non of the above node types are specified.
      * \return Pointer to the node.
      */
      base::Base* getAPSpecNode(NodeKind ndk);

  }; // Factory


}}}
#endif

