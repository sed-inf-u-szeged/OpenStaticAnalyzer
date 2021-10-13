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

#ifndef _CSHARP_FACTORY_H_
#define _CSHARP_FACTORY_H_

#include "csharp/inc/csharp.h"

/**
* \file Factory.h
* \brief Contains declaration of Factory class.
*/

namespace columbus { namespace csharp { namespace asg {
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
      structure::CompilationUnitSyntax* getRoot() const;

      /**
      * \brief Decides whether it is a valid id or not.
      * \param id [in] The id whose validity is examined.
      * \return Returns true if a node belongs to the id.
      */
      bool getExist(NodeId id) const;

      /**
      * \brief Gives back a reference to the node.
      * \param id              [in] The id of the node.
      * \throw CsharpException Throws CsharpException if there is no node for the id.
      * \return Reference to the node.
      */
      base::Base& getRef(NodeId id) const;

      /**
      * \brief Gives back a pointer to the node.
      * \param id              [in] The id of the node.
      * \throw CsharpException Throws CsharpException if there is no node for the id.
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
      * \throw CsharpException Throws CsharpException if there is no node for the id.
      * \return The NodeKind of the node.
      */
      NodeKind getNodeKind(NodeId id) const;

      /**
      * \brief Deletes the node with the given ID and every node in it's subtree.
      * \param id              [in] The id of the node.
      * \throw CsharpException Throws CsharpException if there is no node for the id.
      */
      void destroyNode(NodeId id);

      /**
      * \brief Deletes the node with the given ID without it's subtree.
      * \param id              [in] The id of the node.
      * \throw CsharpException Throws CsharpException if there is no node for the id.
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
      * \throw CsharpException Throws CsharpException if the id is too large (larger than the size of the ASG).
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
      * \throw CsharpException Throws CsharpException id the id is too large (larger than the size of the Filter).
      */
      void setFiltered(NodeId id);

      /**
      * \brief Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
      * \param id              [in] The id of the node.
      * \throw CsharpException Throws CsharpException id the id is too large (larger than the size of the Filter).
      */
      void setNotFiltered(NodeId id);

      /**
      * \brief Sets the state of the node and all of its ancestors to not filtered.
      * \param id              [in] The id of the node.
      * \throw CsharpException Throws CsharpException id the id is too large (larger than the size of the Filter).
      */
      void setNotFilteredThisNode(NodeId id);

      /**
      * \brief Gives back the filter state (csharp::Filter::FilterStae) of the given node irrespectively of the state of the filter mode.
      * \param id              [in] The id of the node.
      * \throw CsharpException Throws CsharpException if the id is too large (larger than the size of the ASG).
      * \return Returns with the state of the filter.
      */
      Filter::FilterState getFilterState(NodeId id) const;

      /**
      * \brief Loads the filter.
      * \param filename    [in] The name of the filter file.
      * \throw CsharpException Throws CsharpException if the filter contains more (or less) node than the factory does.
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
      * \throw CsharpException Throws CsharpException id the id is too large (larger than the size of the Filter).
      */
      void setFilteredThisNodeOnly(NodeId id);

      /**
      * \internal
      * \brief Set only the given node to not filtered (without its children).
      * \param id              [in] The id of the node.
      * \throw CsharpException Throws CsharpException id the id is too large (larger than the size of the Filter).
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
      * \throw CsharpException If an invalid (or an abstract) NodeKind is given, CsharpException is thrown.
      * \return Pointer to the new node.
      */
      base::Base* createNode(NodeKind ndk);

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AliasQualifiedNameSyntax* createAliasQualifiedNameSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AnonymousMethodExpressionSyntax* createAnonymousMethodExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AnonymousObjectCreationExpressionSyntax* createAnonymousObjectCreationExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ArrayCreationExpressionSyntax* createArrayCreationExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ArrayTypeSyntax* createArrayTypeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AssignmentExpressionSyntax* createAssignmentExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::AwaitExpressionSyntax* createAwaitExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::BaseExpressionSyntax* createBaseExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::BinaryExpressionSyntax* createBinaryExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::CastExpressionSyntax* createCastExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::CheckedExpressionSyntax* createCheckedExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ConditionalAccessExpressionSyntax* createConditionalAccessExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ConditionalExpressionSyntax* createConditionalExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::DeclarationExpressionSyntax* createDeclarationExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::DefaultExpressionSyntax* createDefaultExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ElementAccessExpressionSyntax* createElementAccessExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ElementBindingExpressionSyntax* createElementBindingExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::GenericNameSyntax* createGenericNameSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::IdentifierNameSyntax* createIdentifierNameSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ImplicitArrayCreationExpressionSyntax* createImplicitArrayCreationExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ImplicitElementAccessSyntax* createImplicitElementAccessSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ImplicitStackAllocArrayCreationExpressionSyntax* createImplicitStackAllocArrayCreationExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::InitializerExpressionSyntax* createInitializerExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::InterpolatedStringExpressionSyntax* createInterpolatedStringExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::InvocationExpressionSyntax* createInvocationExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::IsPatternExpressionSyntax* createIsPatternExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::LiteralExpressionSyntax* createLiteralExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::MakeRefExpressionSyntax* createMakeRefExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::MemberAccessExpressionSyntax* createMemberAccessExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::MemberBindingExpressionSyntax* createMemberBindingExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::NullableTypeSyntax* createNullableTypeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ObjectCreationExpressionSyntax* createObjectCreationExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::OmittedArraySizeExpressionSyntax* createOmittedArraySizeExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::OmittedTypeArgumentSyntax* createOmittedTypeArgumentSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ParenthesizedExpressionSyntax* createParenthesizedExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ParenthesizedLambdaExpressionSyntax* createParenthesizedLambdaExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::PointerTypeSyntax* createPointerTypeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::PostfixUnaryExpressionSyntax* createPostfixUnaryExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::PredefinedTypeSyntax* createPredefinedTypeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::PrefixUnaryExpressionSyntax* createPrefixUnaryExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::QualifiedNameSyntax* createQualifiedNameSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::QueryExpressionSyntax* createQueryExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::RangeExpressionSyntax* createRangeExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::RefExpressionSyntax* createRefExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::RefTypeExpressionSyntax* createRefTypeExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::RefTypeSyntax* createRefTypeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::RefValueExpressionSyntax* createRefValueExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::SimpleLambdaExpressionSyntax* createSimpleLambdaExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::SizeOfExpressionSyntax* createSizeOfExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::StackAllocArrayCreationExpressionSyntax* createStackAllocArrayCreationExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::SwitchExpressionSyntax* createSwitchExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ThisExpressionSyntax* createThisExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::ThrowExpressionSyntax* createThrowExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::TupleExpressionSyntax* createTupleExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::TupleTypeSyntax* createTupleTypeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      expression::TypeOfExpressionSyntax* createTypeOfExpressionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::BlockSyntax* createBlockSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::BreakStatementSyntax* createBreakStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::CheckedStatementSyntax* createCheckedStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ContinueStatementSyntax* createContinueStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::DoStatementSyntax* createDoStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::EmptyStatementSyntax* createEmptyStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ExpressionStatementSyntax* createExpressionStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::FixedStatementSyntax* createFixedStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ForEachStatementSyntax* createForEachStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ForEachVariableStatementSyntax* createForEachVariableStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ForStatementSyntax* createForStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::GotoStatementSyntax* createGotoStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::IfStatementSyntax* createIfStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::LabeledStatementSyntax* createLabeledStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::LocalDeclarationStatementSyntax* createLocalDeclarationStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::LocalFunctionStatementSyntax* createLocalFunctionStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::LockStatementSyntax* createLockStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ReturnStatementSyntax* createReturnStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::SwitchStatementSyntax* createSwitchStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::ThrowStatementSyntax* createThrowStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::TryStatementSyntax* createTryStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::UnsafeStatementSyntax* createUnsafeStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::UsingStatementSyntax* createUsingStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::WhileStatementSyntax* createWhileStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      statement::YieldStatementSyntax* createYieldStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::AccessorDeclarationSyntax* createAccessorDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::AccessorListSyntax* createAccessorListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::AnonymousObjectMemberDeclaratorSyntax* createAnonymousObjectMemberDeclaratorSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ArgumentListSyntax* createArgumentListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ArgumentSyntax* createArgumentSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ArrayRankSpecifierSyntax* createArrayRankSpecifierSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ArrowExpressionClauseSyntax* createArrowExpressionClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::AttributeArgumentListSyntax* createAttributeArgumentListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::AttributeArgumentSyntax* createAttributeArgumentSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::AttributeListSyntax* createAttributeListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::AttributeSyntax* createAttributeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::AttributeTargetSpecifierSyntax* createAttributeTargetSpecifierSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::BaseListSyntax* createBaseListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::BracketedArgumentListSyntax* createBracketedArgumentListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::BracketedParameterListSyntax* createBracketedParameterListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CasePatternSwitchLabelSyntax* createCasePatternSwitchLabelSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CaseSwitchLabelSyntax* createCaseSwitchLabelSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CatchClauseSyntax* createCatchClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CatchDeclarationSyntax* createCatchDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CatchFilterClauseSyntax* createCatchFilterClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ClassDeclarationSyntax* createClassDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ClassOrStructConstraintSyntax* createClassOrStructConstraintSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CompilationUnitSyntax* createCompilationUnitSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ConstantPatternSyntax* createConstantPatternSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ConstructorConstraintSyntax* createConstructorConstraintSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ConstructorDeclarationSyntax* createConstructorDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ConstructorInitializerSyntax* createConstructorInitializerSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ConversionOperatorDeclarationSyntax* createConversionOperatorDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ConversionOperatorMemberCrefSyntax* createConversionOperatorMemberCrefSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CrefBracketedParameterListSyntax* createCrefBracketedParameterListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CrefParameterListSyntax* createCrefParameterListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::CrefParameterSyntax* createCrefParameterSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::DeclarationPatternSyntax* createDeclarationPatternSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::DefaultSwitchLabelSyntax* createDefaultSwitchLabelSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::DelegateDeclarationSyntax* createDelegateDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::DestructorDeclarationSyntax* createDestructorDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::DiscardDesignationSyntax* createDiscardDesignationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::DiscardPatternSyntax* createDiscardPatternSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ElseClauseSyntax* createElseClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::EnumDeclarationSyntax* createEnumDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::EnumMemberDeclarationSyntax* createEnumMemberDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::EqualsValueClauseSyntax* createEqualsValueClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::EventDeclarationSyntax* createEventDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::EventFieldDeclarationSyntax* createEventFieldDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ExplicitInterfaceSpecifierSyntax* createExplicitInterfaceSpecifierSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ExternAliasDirectiveSyntax* createExternAliasDirectiveSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::FieldDeclarationSyntax* createFieldDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::FinallyClauseSyntax* createFinallyClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::FromClauseSyntax* createFromClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::GlobalStatementSyntax* createGlobalStatementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::GroupClauseSyntax* createGroupClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::IncompleteMemberSyntax* createIncompleteMemberSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::IndexerDeclarationSyntax* createIndexerDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::IndexerMemberCrefSyntax* createIndexerMemberCrefSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::InterfaceDeclarationSyntax* createInterfaceDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::InterpolatedStringTextSyntax* createInterpolatedStringTextSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::InterpolationAlignmentClauseSyntax* createInterpolationAlignmentClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::InterpolationFormatClauseSyntax* createInterpolationFormatClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::InterpolationSyntax* createInterpolationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::JoinClauseSyntax* createJoinClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::JoinIntoClauseSyntax* createJoinIntoClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::LetClauseSyntax* createLetClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::MethodDeclarationSyntax* createMethodDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::NameColonSyntax* createNameColonSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::NameEqualsSyntax* createNameEqualsSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::NameMemberCrefSyntax* createNameMemberCrefSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::NamespaceDeclarationSyntax* createNamespaceDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::OperatorDeclarationSyntax* createOperatorDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::OperatorMemberCrefSyntax* createOperatorMemberCrefSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::OrderByClauseSyntax* createOrderByClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::OrderingSyntax* createOrderingSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ParameterListSyntax* createParameterListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ParameterSyntax* createParameterSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::ParenthesizedVariableDesignationSyntax* createParenthesizedVariableDesignationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::PositionalPatternClauseSyntax* createPositionalPatternClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::PropertyDeclarationSyntax* createPropertyDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::PropertyPatternClauseSyntax* createPropertyPatternClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::QualifiedCrefSyntax* createQualifiedCrefSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::QueryBodySyntax* createQueryBodySyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::QueryContinuationSyntax* createQueryContinuationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::RecursivePatternSyntax* createRecursivePatternSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::SelectClauseSyntax* createSelectClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::SimpleBaseTypeSyntax* createSimpleBaseTypeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::SingleVariableDesignationSyntax* createSingleVariableDesignationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::StructDeclarationSyntax* createStructDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::SubpatternSyntax* createSubpatternSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::SwitchExpressionArmSyntax* createSwitchExpressionArmSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::SwitchSectionSyntax* createSwitchSectionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::SyntaxToken* createSyntaxTokenNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::TupleElementSyntax* createTupleElementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::TypeArgumentListSyntax* createTypeArgumentListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::TypeConstraintSyntax* createTypeConstraintSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::TypeCrefSyntax* createTypeCrefSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::TypeParameterConstraintClauseSyntax* createTypeParameterConstraintClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::TypeParameterListSyntax* createTypeParameterListSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::TypeParameterSyntax* createTypeParameterSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::UsingDirectiveSyntax* createUsingDirectiveSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::VarPatternSyntax* createVarPatternSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::VariableDeclarationSyntax* createVariableDeclarationSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::VariableDeclaratorSyntax* createVariableDeclaratorSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::WhenClauseSyntax* createWhenClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::WhereClauseSyntax* createWhereClauseSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlCDataSectionSyntax* createXmlCDataSectionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlCommentSyntax* createXmlCommentSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlCrefAttributeSyntax* createXmlCrefAttributeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlElementEndTagSyntax* createXmlElementEndTagSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlElementStartTagSyntax* createXmlElementStartTagSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlElementSyntax* createXmlElementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlEmptyElementSyntax* createXmlEmptyElementSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlNameAttributeSyntax* createXmlNameAttributeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlNameSyntax* createXmlNameSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlPrefixSyntax* createXmlPrefixSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlProcessingInstructionSyntax* createXmlProcessingInstructionSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlTextAttributeSyntax* createXmlTextAttributeSyntaxNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      structure::XmlTextSyntax* createXmlTextSyntaxNode();

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
      * \throw CsharpException If an invalid (or an abstract) NodeKind is given, CsharpException is thrown.
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
      structure::CompilationUnitSyntax *root;

      /** \internal \brief List of the ids of the deleted nodes. */
      std::list<NodeId> deletedNodeIdList;

      friend class VisitorFilter;

      friend class base::Base;
      friend class base::Positioned;
      friend class expression::AliasQualifiedNameSyntax;
      friend class expression::AnonymousFunctionExpressionSyntax;
      friend class expression::AnonymousMethodExpressionSyntax;
      friend class expression::AnonymousObjectCreationExpressionSyntax;
      friend class expression::ArrayCreationExpressionSyntax;
      friend class expression::ArrayTypeSyntax;
      friend class expression::AssignmentExpressionSyntax;
      friend class expression::AwaitExpressionSyntax;
      friend class expression::BaseExpressionSyntax;
      friend class expression::BinaryExpressionSyntax;
      friend class expression::CastExpressionSyntax;
      friend class expression::CheckedExpressionSyntax;
      friend class expression::ConditionalAccessExpressionSyntax;
      friend class expression::ConditionalExpressionSyntax;
      friend class expression::DeclarationExpressionSyntax;
      friend class expression::DefaultExpressionSyntax;
      friend class expression::ElementAccessExpressionSyntax;
      friend class expression::ElementBindingExpressionSyntax;
      friend class expression::ExpressionSyntax;
      friend class expression::GenericNameSyntax;
      friend class expression::IdentifierNameSyntax;
      friend class expression::ImplicitArrayCreationExpressionSyntax;
      friend class expression::ImplicitElementAccessSyntax;
      friend class expression::ImplicitStackAllocArrayCreationExpressionSyntax;
      friend class expression::InitializerExpressionSyntax;
      friend class expression::InstanceExpressionSyntax;
      friend class expression::InterpolatedStringExpressionSyntax;
      friend class expression::InvocationExpressionSyntax;
      friend class expression::IsPatternExpressionSyntax;
      friend class expression::LambdaExpressionSyntax;
      friend class expression::LiteralExpressionSyntax;
      friend class expression::MakeRefExpressionSyntax;
      friend class expression::MemberAccessExpressionSyntax;
      friend class expression::MemberBindingExpressionSyntax;
      friend class expression::NameSyntax;
      friend class expression::NullableTypeSyntax;
      friend class expression::ObjectCreationExpressionSyntax;
      friend class expression::OmittedArraySizeExpressionSyntax;
      friend class expression::OmittedTypeArgumentSyntax;
      friend class expression::ParenthesizedExpressionSyntax;
      friend class expression::ParenthesizedLambdaExpressionSyntax;
      friend class expression::PointerTypeSyntax;
      friend class expression::PostfixUnaryExpressionSyntax;
      friend class expression::PredefinedTypeSyntax;
      friend class expression::PrefixUnaryExpressionSyntax;
      friend class expression::QualifiedNameSyntax;
      friend class expression::QueryExpressionSyntax;
      friend class expression::RangeExpressionSyntax;
      friend class expression::RefExpressionSyntax;
      friend class expression::RefTypeExpressionSyntax;
      friend class expression::RefTypeSyntax;
      friend class expression::RefValueExpressionSyntax;
      friend class expression::SimpleLambdaExpressionSyntax;
      friend class expression::SimpleNameSyntax;
      friend class expression::SizeOfExpressionSyntax;
      friend class expression::StackAllocArrayCreationExpressionSyntax;
      friend class expression::SwitchExpressionSyntax;
      friend class expression::ThisExpressionSyntax;
      friend class expression::ThrowExpressionSyntax;
      friend class expression::TupleExpressionSyntax;
      friend class expression::TupleTypeSyntax;
      friend class expression::TypeOfExpressionSyntax;
      friend class expression::TypeSyntax;
      friend class statement::BlockSyntax;
      friend class statement::BreakStatementSyntax;
      friend class statement::CheckedStatementSyntax;
      friend class statement::CommonForEachStatementSyntax;
      friend class statement::ContinueStatementSyntax;
      friend class statement::DoStatementSyntax;
      friend class statement::EmptyStatementSyntax;
      friend class statement::ExpressionStatementSyntax;
      friend class statement::FixedStatementSyntax;
      friend class statement::ForEachStatementSyntax;
      friend class statement::ForEachVariableStatementSyntax;
      friend class statement::ForStatementSyntax;
      friend class statement::GotoStatementSyntax;
      friend class statement::IfStatementSyntax;
      friend class statement::LabeledStatementSyntax;
      friend class statement::LocalDeclarationStatementSyntax;
      friend class statement::LocalFunctionStatementSyntax;
      friend class statement::LockStatementSyntax;
      friend class statement::ReturnStatementSyntax;
      friend class statement::StatementSyntax;
      friend class statement::SwitchStatementSyntax;
      friend class statement::ThrowStatementSyntax;
      friend class statement::TryStatementSyntax;
      friend class statement::UnsafeStatementSyntax;
      friend class statement::UsingStatementSyntax;
      friend class statement::WhileStatementSyntax;
      friend class statement::YieldStatementSyntax;
      friend class structure::AccessorDeclarationSyntax;
      friend class structure::AccessorListSyntax;
      friend class structure::AnonymousObjectMemberDeclaratorSyntax;
      friend class structure::ArgumentListSyntax;
      friend class structure::ArgumentSyntax;
      friend class structure::ArrayRankSpecifierSyntax;
      friend class structure::ArrowExpressionClauseSyntax;
      friend class structure::AttributeArgumentListSyntax;
      friend class structure::AttributeArgumentSyntax;
      friend class structure::AttributeListSyntax;
      friend class structure::AttributeSyntax;
      friend class structure::AttributeTargetSpecifierSyntax;
      friend class structure::BaseArgumentListSyntax;
      friend class structure::BaseCrefParameterListSyntax;
      friend class structure::BaseFieldDeclarationSyntax;
      friend class structure::BaseListSyntax;
      friend class structure::BaseMethodDeclarationSyntax;
      friend class structure::BaseParameterListSyntax;
      friend class structure::BasePropertyDeclarationSyntax;
      friend class structure::BaseTypeDeclarationSyntax;
      friend class structure::BaseTypeSyntax;
      friend class structure::BracketedArgumentListSyntax;
      friend class structure::BracketedParameterListSyntax;
      friend class structure::CasePatternSwitchLabelSyntax;
      friend class structure::CaseSwitchLabelSyntax;
      friend class structure::CatchClauseSyntax;
      friend class structure::CatchDeclarationSyntax;
      friend class structure::CatchFilterClauseSyntax;
      friend class structure::ClassDeclarationSyntax;
      friend class structure::ClassOrStructConstraintSyntax;
      friend class structure::CompilationUnitSyntax;
      friend class structure::ConstantPatternSyntax;
      friend class structure::ConstructorConstraintSyntax;
      friend class structure::ConstructorDeclarationSyntax;
      friend class structure::ConstructorInitializerSyntax;
      friend class structure::ConversionOperatorDeclarationSyntax;
      friend class structure::ConversionOperatorMemberCrefSyntax;
      friend class structure::CrefBracketedParameterListSyntax;
      friend class structure::CrefParameterListSyntax;
      friend class structure::CrefParameterSyntax;
      friend class structure::CrefSyntax;
      friend class structure::DeclarationPatternSyntax;
      friend class structure::DefaultSwitchLabelSyntax;
      friend class structure::DelegateDeclarationSyntax;
      friend class structure::DestructorDeclarationSyntax;
      friend class structure::DiscardDesignationSyntax;
      friend class structure::DiscardPatternSyntax;
      friend class structure::ElseClauseSyntax;
      friend class structure::EnumDeclarationSyntax;
      friend class structure::EnumMemberDeclarationSyntax;
      friend class structure::EqualsValueClauseSyntax;
      friend class structure::EventDeclarationSyntax;
      friend class structure::EventFieldDeclarationSyntax;
      friend class structure::ExplicitInterfaceSpecifierSyntax;
      friend class structure::ExternAliasDirectiveSyntax;
      friend class structure::FieldDeclarationSyntax;
      friend class structure::FinallyClauseSyntax;
      friend class structure::FromClauseSyntax;
      friend class structure::GlobalStatementSyntax;
      friend class structure::GroupClauseSyntax;
      friend class structure::IncompleteMemberSyntax;
      friend class structure::IndexerDeclarationSyntax;
      friend class structure::IndexerMemberCrefSyntax;
      friend class structure::InterfaceDeclarationSyntax;
      friend class structure::InterpolatedStringContentSyntax;
      friend class structure::InterpolatedStringTextSyntax;
      friend class structure::InterpolationAlignmentClauseSyntax;
      friend class structure::InterpolationFormatClauseSyntax;
      friend class structure::InterpolationSyntax;
      friend class structure::JoinClauseSyntax;
      friend class structure::JoinIntoClauseSyntax;
      friend class structure::LetClauseSyntax;
      friend class structure::MemberCrefSyntax;
      friend class structure::MemberDeclarationSyntax;
      friend class structure::MethodDeclarationSyntax;
      friend class structure::NameColonSyntax;
      friend class structure::NameEqualsSyntax;
      friend class structure::NameMemberCrefSyntax;
      friend class structure::NamespaceDeclarationSyntax;
      friend class structure::OperatorDeclarationSyntax;
      friend class structure::OperatorMemberCrefSyntax;
      friend class structure::OrderByClauseSyntax;
      friend class structure::OrderingSyntax;
      friend class structure::ParameterListSyntax;
      friend class structure::ParameterSyntax;
      friend class structure::ParenthesizedVariableDesignationSyntax;
      friend class structure::PatternSyntax;
      friend class structure::PositionalPatternClauseSyntax;
      friend class structure::PropertyDeclarationSyntax;
      friend class structure::PropertyPatternClauseSyntax;
      friend class structure::QualifiedCrefSyntax;
      friend class structure::QueryBodySyntax;
      friend class structure::QueryClauseSyntax;
      friend class structure::QueryContinuationSyntax;
      friend class structure::RecursivePatternSyntax;
      friend class structure::SelectClauseSyntax;
      friend class structure::SelectOrGroupClauseSyntax;
      friend class structure::SimpleBaseTypeSyntax;
      friend class structure::SingleVariableDesignationSyntax;
      friend class structure::StructDeclarationSyntax;
      friend class structure::SubpatternSyntax;
      friend class structure::SwitchExpressionArmSyntax;
      friend class structure::SwitchLabelSyntax;
      friend class structure::SwitchSectionSyntax;
      friend class structure::SyntaxToken;
      friend class structure::TupleElementSyntax;
      friend class structure::TypeArgumentListSyntax;
      friend class structure::TypeConstraintSyntax;
      friend class structure::TypeCrefSyntax;
      friend class structure::TypeDeclarationSyntax;
      friend class structure::TypeParameterConstraintClauseSyntax;
      friend class structure::TypeParameterConstraintSyntax;
      friend class structure::TypeParameterListSyntax;
      friend class structure::TypeParameterSyntax;
      friend class structure::UsingDirectiveSyntax;
      friend class structure::VarPatternSyntax;
      friend class structure::VariableDeclarationSyntax;
      friend class structure::VariableDeclaratorSyntax;
      friend class structure::VariableDesignationSyntax;
      friend class structure::WhenClauseSyntax;
      friend class structure::WhereClauseSyntax;
      friend class structure::XmlAttributeSyntax;
      friend class structure::XmlCDataSectionSyntax;
      friend class structure::XmlCommentSyntax;
      friend class structure::XmlCrefAttributeSyntax;
      friend class structure::XmlElementEndTagSyntax;
      friend class structure::XmlElementStartTagSyntax;
      friend class structure::XmlElementSyntax;
      friend class structure::XmlEmptyElementSyntax;
      friend class structure::XmlNameAttributeSyntax;
      friend class structure::XmlNameSyntax;
      friend class structure::XmlNodeSyntax;
      friend class structure::XmlPrefixSyntax;
      friend class structure::XmlProcessingInstructionSyntax;
      friend class structure::XmlTextAttributeSyntax;
      friend class structure::XmlTextSyntax;

  }; // Factory


}}}
#endif

