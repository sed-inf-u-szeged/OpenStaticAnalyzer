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

#ifndef _LIM_FACTORY_H_
#define _LIM_FACTORY_H_

#include "lim/inc/lim.h"

/**
* \file Factory.h
* \brief Contains declaration of Factory class.
*/

namespace columbus { namespace lim { namespace asg {
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
      Factory(RefDistributorStrTable& st, const std::string &rootPackageName, Language lang);

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
      logical::Package* getRoot() const;

      /**
      * \brief Decides whether it is a valid id or not.
      * \param id [in] The id whose validity is examined.
      * \return Returns true if a node belongs to the id.
      */
      bool getExist(NodeId id) const;

      /**
      * \brief Gives back a reference to the node.
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException if there is no node for the id.
      * \return Reference to the node.
      */
      base::Base& getRef(NodeId id) const;

      /**
      * \brief Gives back a pointer to the node.
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException if there is no node for the id.
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
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException if there is no node for the id.
      * \return The NodeKind of the node.
      */
      NodeKind getNodeKind(NodeId id) const;

      /**
      * \brief Deletes the node with the given ID and every node in it's subtree.
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException if there is no node for the id.
      */
      void destroyNode(NodeId id);

      /**
      * \brief Deletes the node with the given ID without it's subtree.
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException if there is no node for the id.
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
          bool operator==(const const_iterator& rhs) const {return containerIt==rhs.containerIt;}
          bool operator!=(const const_iterator& rhs) const {return containerIt!=rhs.containerIt;}
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
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException if the id is too large (larger than the size of the ASG).
      * \return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
      */
      bool getIsFiltered(NodeId id) const;

      /**
      * \brief Tells whether the given node is filtered or not.
      * \param node         [in] The pointer to the node.
      * \return Returns true if the Node is filtered and returns false if it isn't (or the filter mode is turned off).
      */
      bool getIsFiltered(const base::Base* node) const;

      /**
      * \brief Filters out the given node and all of its descendants.
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException id the id is too large (larger than the size of the Filter).
      */
      void setFiltered(NodeId id);

      /**
      * \brief Sets the state of the node, all of its descendants and all of its ancestors to not filtered.
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException id the id is too large (larger than the size of the Filter).
      */
      void setNotFiltered(NodeId id);

      /**
      * \brief Sets the state of the node and all of its ancestors to not filtered.
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException id the id is too large (larger than the size of the Filter).
      */
      void setNotFilteredThisNode(NodeId id);

      /**
      * \brief Gives back the filter state (lim::Filter::FilterStae) of the given node irrespectively of the state of the filter mode.
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException if the id is too large (larger than the size of the ASG).
      * \return Returns with the state of the filter.
      */
      Filter::FilterState getFilterState(NodeId id) const;

      /**
      * \brief Loads the filter.
      * \param filename    [in] The name of the filter file.
      * \throw LimException Throws LimException if the filter contains more (or less) node than the factory does.
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
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException id the id is too large (larger than the size of the Filter).
      */
      void setFilteredThisNodeOnly(NodeId id);

      /**
      * \internal
      * \brief Set only the given node to not filtered (without its children).
      * \param id           [in] The id of the node.
      * \throw LimException Throws LimException id the id is too large (larger than the size of the Filter).
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
      * \param ndk          [in] The kind of the node.
      * \throw LimException If an invalid (or an abstract) NodeKind is given, LimException is thrown.
      * \return Pointer to the new node.
      */
      base::Base* createNode(NodeKind ndk);

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      base::ControlFlowBlock* createControlFlowBlockNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::Attribute* createAttributeNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::Class* createClassNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::ClassGeneric* createClassGenericNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::ClassGenericInstance* createClassGenericInstanceNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::ClassGenericSpec* createClassGenericSpecNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::GenericParameter* createGenericParameterNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::Method* createMethodNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::MethodGeneric* createMethodGenericNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::MethodGenericInstance* createMethodGenericInstanceNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::MethodGenericSpec* createMethodGenericSpecNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::Package* createPackageNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      logical::Parameter* createParameterNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      physical::File* createFileNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      physical::Folder* createFolderNode();

      /**
      * \brief Flush the node Sizes to the default out
      */
      static void printNodeSizes();


      // ******************** Unique node builders ********************

    private:

      /**
      * \internal
      * \brief Creates a new node, insert it into the container and return with it.
      * \param ndk          [in] The kind of the node.
      * \param id           [in] The id of the new node.
      * \throw LimException If an invalid (or an abstract) NodeKind is given, LimException is thrown.
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
        EdgeIdentifier(base::Base* edgeBegin, NodeId edgeEnd, EdgeKind edgekind, AssocClassType assocType, void* assocClass) : edgeBegin(edgeBegin), edgeEnd(edgeEnd), edgekind(edgekind), assocType(assocType), assocClass(assocClass) {}
        base::Base* edgeBegin;
        NodeId edgeEnd;
        EdgeKind edgekind;
        AssocClassType assocType;
        void* assocClass;
      } EdgeIdentifier;

      /** \internal \brief The subcripted object for the node destroy. */
      std::list<SchemaPointerSorage*> registeredPointerStorage;

      /** \internal \brief Pointer to the root of the ASG. */
      logical::Package *root;

      /** \internal \brief List of the ids of the deleted nodes. */
      std::list<NodeId> deletedNodeIdList;

      friend class VisitorFilter;

      friend class base::Base;
      friend class base::Comment;
      friend class base::Component;
      friend class base::ControlFlowBlock;
      friend class base::Named;
      friend class logical::Attribute;
      friend class logical::AttributeAccess;
      friend class logical::Class;
      friend class logical::ClassGeneric;
      friend class logical::ClassGenericInstance;
      friend class logical::ClassGenericSpec;
      friend class logical::Friendship;
      friend class logical::GenericParameter;
      friend class logical::Member;
      friend class logical::Method;
      friend class logical::MethodCall;
      friend class logical::MethodGeneric;
      friend class logical::MethodGenericInstance;
      friend class logical::MethodGenericSpec;
      friend class logical::Package;
      friend class logical::Parameter;
      friend class logical::Scope;
      friend class physical::FSEntry;
      friend class physical::File;
      friend class physical::FileSystem;
      friend class physical::Folder;
      friend class type::SimpleType;
      friend class type::Type;
      friend class type::TypeFormer;
      friend class type::TypeFormerArray;
      friend class type::TypeFormerMethod;
      friend class type::TypeFormerNonType;
      friend class type::TypeFormerPointer;
      friend class type::TypeFormerType;

    public:

      /**
      * \brief Tells the language the lim graph built from.
      * \return Returns the language of the lim graph.
      */
      Language getLanguage() const;

      /**
      * \brief Sets the separator string for languages not being in the built-in language list (\ref Language).
      * \param newSeparator [in] The new separator string.
      * \throw LimException If the \ref Language is not the limLangOther, LimException is thrown.
      */
      void setScopeSeparator(const std::string& newSeparator);

      /**
      * \brief Gives back the scope separator string for the given language.
      * \return Returns with the scope separator string.
      */
      const std::string getScopeSeparator() const;

      /**
      * \brief Sets the package name for languages not being in the built-in language list (\ref Language).
      * \param newPackageName [in] The new package name.
      * \throw LimException   If the \ref Language is not the limLangOther, LimException is thrown.
      */
      void setPackageName(const std::string& newPackageName);

      /**
      * \brief Gives back the package name string for the given language.
      * \return Returns with the package name string.
      */
      const std::string getPackageName() const;

      /**
      * \brief Gives back the id of the FileSystem node (only one can be in the ASG).
      * \return Returns with the id of the FileSystem node.
      * \throw If the FileSystem node does not exist LimException is thrown.
      */
      NodeId getFileSystemRoot() const;

      /**
      * \brief Gives back the id of the root Component.
      * \return Returns with the id of the root Component.
      * \throw If the root Component does not exist LimException is thrown.
      */
      NodeId getComponentRoot() const;

      /**
      * \brief Gives back the root Component.
      * \return Returns the root Component.
      * \throw If the root Component does not exist LimException is thrown.
      */
      base::Component& getComponentRootRef() const;

      /**
      * \brief Creates a new Component node with name if it does not
      *        exist, or gives back the already existing node (two different
      *        Component cannot have the same name).
      * \param name [in] The name of the Component.
      * \return Returns with the Component node.
      */
      base::Component& createComponent(const std::string& name);

      /**
      * \brief Creates a new Comment node with comment text if it does not
      *        exist, or gives back the already existing node (two different
      *        Comment cannot have the same name).
      * \param text [in] The comment text.
      * \return Returns with the Comment node.
      */
      base::Comment& createComment(const std::string& text);

      /**
      * \brief Creates a new File node and (if it necessary) Folder nodes according to the path string,
      *        or gives back the already existing one. The new hierarchy will be added to the FileSystem.
      * \param path         [in] The path string.
      * \throw LimException If the path string is empty, LimException is thrown.
      * \return Returns with the File node.
      */
      physical::File& createFile(const std::string& path);

      /**
      * \brief Creates a new File node and (if it necessary) Folder nodes according to the path string,
      *        or gives back the already existing one. The new hierarchy will be added to the node
      *        given by parameter nodeId.
      * \param path         [in] The path string.
      * \param nodeId       [in] The id of the FileSystem or a Folder node.
      * \throw LimException If the path string is empty or an invalid NodeId is given, LimException is thrown.
      * \return Returns with the File node.
      */
      physical::File& createFile(const std::string& path, NodeId nodeId);

            
      void beginType();
      void addTypeFormer(NodeId typeFormer);
      type::Type& endType();

      void beginTypeFormerMethod();
      void setTypeFormerMethodHasReturnType(NodeId returnType);
      void addTypeFormerMethodHasParameterType(NodeId parameterType, ParameterKind paramKind);
      type::TypeFormerMethod& endTypeFormerMethod();

      type::TypeFormerPointer& createTypeFormerPointer(PointerKind ptk);
      
      type::TypeFormerArray& createTypeFormerArray();
      
      type::TypeFormerType& createTypeFormerType(NodeId refersTo);
      
      type::TypeFormerNonType& createTypeFormerNonType();
      
      type::SimpleType& createSimpleType(SimpleTypeKind stk);

      logical::MethodCall& createMethodCall(NodeId method);
      logical::MethodCall& createMethodCall(const std::string& imprint);
      
      logical::AttributeAccess& createAttributeAccess(NodeId attribute);
      logical::Friendship& createFriendship(NodeId friendNode);
      
      /**
      * \brief Replaces the given Class or Method node with its generic version.
      * \throw LimException Throws LimException if non of the above node types are specified.
      * \return Pointer to the new node.
      */
      base::Base* replaceNode(base::Base &node);
      
    private:
      /**
      * \brief Sets the setaparot and the package name (depending on the language).
      */
      void setSeparatorAndPackageName();

    private:

      /** \internal \brief RefDistributorStrTable which stores temporary string (necessary for working of Factory but not necessary for ASG). */
      RefDistributorStrTable tmpStringTable;

      /** \internal \brief The start id of the SimpleTypes (the first one is taken to here). */
      const NodeId simpleTypesStartId;

      /** \internal \brief The possible SimpleTypes. */
      const unsigned int numberOfSimpleTypes;

      /** \internal \brief The id of the unique FileSystem. */
      const NodeId fileSystemId;

      /** \internal \brief The id of the Component. */
      const NodeId rootComponentId;

      /** \internal \brief Stores the language the lim graph built from (set in the constructor and cannot be changed). */
      Language language;

      /** \internal \brief Stores the scope separator and it can be changed only for "non-supported" languages. */
      std::string scopeSeparator;

      /** \internal \brief Stores the name of the package and it can be changed only for "non-supported" languages. */
      std::string packageName;

      /** \internal \brief Stores component nodes and they can be searched by their name. */
      std::map<Key, NodeId> componentNodes;


      // ******************** Type Building ********************

      std::map<Key, NodeId> typeMap;
      std::stack<std::string> typeBuildStack;
      
      std::map<Key, NodeId> typeFormerMethodMap;
      std::stack<std::string> typeFormerMethodBuildStack;
      
      std::map<PointerKind, NodeId> typeFormerPointerMap;
      
      NodeId typeFormerArrayMap;
      NodeId typeFormerNonTypeMap;
      
      std::map<Key, NodeId> typeFormerTypeMap;
      
      std::map<SimpleTypeKind, NodeId> simpleTypeMap;

      std::map<Key, NodeId> methodCallNodeIdMap;
      std::map<Key, NodeId> callImprintMethodCallNodeIdMap;
      std::map<Key, NodeId> attributeAccessNodeIdMap;
      std::map<Key, NodeId> friendshipNodeIdMap;
  }; // Factory


}}}
#endif

