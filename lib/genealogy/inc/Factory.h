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

#ifndef _GENEALOGY_FACTORY_H_
#define _GENEALOGY_FACTORY_H_

#include "genealogy/inc/genealogy.h"

/**
* \file Factory.h
* \brief Contains declaration of Factory class.
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Factory, which handles (creates, deletes, sets their properties) nodes.
  */
  class Factory {
    protected:

      /** \internal \brief Type definition to store pointers to nodes. */
      typedef std::vector<Base*> Container;

    public:

      class SchemaPointerSorage {
        public:
          virtual ~SchemaPointerSorage(){};
          virtual void onDestroyNode(const Base* node) = 0;
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
      Project* getRoot() const;

      /**
      * \brief Decides whether it is a valid id or not.
      * \param id [in] The id whose validity is examined.
      * \return Returns true if a node belongs to the id.
      */
      bool getExist(NodeId id) const;

      /**
      * \brief Gives back a reference to the node.
      * \param id                 [in] The id of the node.
      * \throw GenealogyException Throws GenealogyException if there is no node for the id.
      * \return Reference to the node.
      */
      Base& getRef(NodeId id) const;

      /**
      * \brief Gives back a pointer to the node.
      * \param id                 [in] The id of the node.
      * \throw GenealogyException Throws GenealogyException if there is no node for the id.
      * \return Pointer to the node.
      */
      Base* getPointer(NodeId id) const;

      /**
      * \brief Gives back a reference to the StringTable.
      * \return Reference to the StringTable.
      */
      RefDistributorStrTable& getStringTable() const;

      /**
      * \brief Gives back the NodeKind of a node.
      * \param id                 [in] The id of the node.
      * \throw GenealogyException Throws GenealogyException if there is no node for the id.
      * \return The NodeKind of the node.
      */
      NodeKind getNodeKind(NodeId id) const;

      /**
      * \brief Deletes the node with the given ID and every node in it's subtree.
      * \param id                 [in] The id of the node.
      * \throw GenealogyException Throws GenealogyException if there is no node for the id.
      */
      void destroyNode(NodeId id);

      /**
      * \brief Deletes the node with the given ID without it's subtree.
      * \param id                 [in] The id of the node.
      * \throw GenealogyException Throws GenealogyException if there is no node for the id.
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
          * \brief Returns a constant reference of the next node (Base).
          * \return Reference of the next node.
          */
          const Base& next();

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
          const_iterator(Container::const_iterator it,const Factory* fact):containerIt(it),fact(fact){while (containerIt != fact->container.end()  &&  ((*containerIt == NULL))) containerIt++;}

          Container::const_iterator containerIt;
          const Factory* fact;
        public:

          const_iterator(const const_iterator& otherit) :containerIt (otherit.containerIt),fact(otherit.fact){}
          const_iterator& operator++() {containerIt++;  while (containerIt != fact->container.end()  &&  ((*containerIt == NULL) )) containerIt++; return *this;}
          const_iterator operator++(int) {const_iterator tmp(*this); operator++(); return tmp;}
          bool operator==(const const_iterator& rhs) {return containerIt==rhs.containerIt;}
          bool operator!=(const const_iterator& rhs) {return containerIt!=rhs.containerIt;}
          const Base* operator*() {return *containerIt;}
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
      * \param ndk                [in] The kind of the node.
      * \throw GenealogyException If an invalid (or an abstract) NodeKind is given, GenealogyException is thrown.
      * \return Pointer to the new node.
      */
      Base* createNode(NodeKind ndk);

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      Project* createProjectNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      Trackable* createTrackableNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      Component* createComponentNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      SourceCodeElement* createSourceCodeElementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      System* createSystemNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      Clone* createCloneNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      StructuralClone* createStructuralCloneNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      CloneClass* createCloneClassNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      CloneInstance* createCloneInstanceNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      DataClumpsClass* createDataClumpsClassNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      DataClumps* createDataClumpsNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      DataElement* createDataElementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      SwitchStatementClass* createSwitchStatementClassNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      SwitchStatement* createSwitchStatementNode();

      /**
      * \brief Creates a new node, insert it into the container and return with it.
      * \return Reference to the new node.
      */
      CaseLabel* createCaseLabelNode();

      /**
      * \brief Flush the node Sizes to the default out
      */
      static void printNodeSizes();


      // ******************** Unique node builders ********************

    private:

      /**
      * \internal
      * \brief Creates a new node, insert it into the container and return with it.
      * \param ndk                [in] The kind of the node.
      * \param id                 [in] The id of the new node.
      * \throw GenealogyException If an invalid (or an abstract) NodeKind is given, GenealogyException is thrown.
      * \return Reference to the new node.
      */
      Base& createNode(NodeKind ndk, NodeId id);

      /**
      * \internal
      * \brief This function is call the alert list.
      * \param node [in] The node which is going to destroy.
      */
      void alertNodeDestroy(const Base* node);

    private:


      // ******************** Private attributes ********************

      /** \internal \brief Container where the pointers to nodes are stored. */
      Container container;

      /** \internal \brief Reference to the StringTable. */
      RefDistributorStrTable* strTable;

      /** \internal \brief Pointer to the ReverseEdges. */
      ReverseEdges *reverseEdges;

      typedef struct EdgeIdentifier {
        EdgeIdentifier(Base* edgeBegin, NodeId edgeEnd, EdgeKind edgekind) : edgeBegin(edgeBegin), edgeEnd(edgeEnd), edgekind(edgekind) {}
        Base* edgeBegin;
        NodeId edgeEnd;
        EdgeKind edgekind;
      } EdgeIdentifier;

      /** \internal \brief The subcripted object for the node destroy. */
      std::list<SchemaPointerSorage*> registeredPointerStorage;

      /** \internal \brief Pointer to the root of the ASG. */
      Project *root;

      /** \internal \brief List of the ids of the deleted nodes. */
      std::list<NodeId> deletedNodeIdList;


      friend class Base;
      friend class Project;
      friend class Trackable;
      friend class Component;
      friend class SourceCodeElement;
      friend class System;
      friend class Clone;
      friend class StructuralClone;
      friend class CloneClass;
      friend class CloneInstance;
      friend class DataClumpsClass;
      friend class DataClumps;
      friend class DataElement;
      friend class SwitchStatementClass;
      friend class SwitchStatement;
      friend class CaseLabel;

  }; // Factory


}}
#endif

