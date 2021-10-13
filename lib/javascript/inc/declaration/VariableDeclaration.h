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

#ifndef _JAVASCRIPT_VariableDeclaration_H_
#define _JAVASCRIPT_VariableDeclaration_H_

#include "javascript/inc/javascript.h"

/**
* \file VariableDeclaration.h
* \brief Contains declaration of the declaration::VariableDeclaration class.
* \brief The it get atributes from 
    * \brief base::Positioned
*/

namespace columbus { namespace javascript { namespace asg {
namespace declaration {

  /**
  * \brief VariableDeclaration class, which represents the declaration::VariableDeclaration node.
  * (missing)
  * 
  * Attributes:
  *   - kind (DeclarationKind) : (missing)
  * 
  * Edges:
  *   - hasDeclarations (declaration::VariableDeclarator, multiple) : (missing)
  */
  class VariableDeclaration : public Declaration {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      VariableDeclaration(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~VariableDeclaration();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      VariableDeclaration & operator=(const VariableDeclaration&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      VariableDeclaration(const VariableDeclaration&);

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
      * \brief Gives back the kind of the node.
      * \return Returns with the kind.
      */
      DeclarationKind getKind() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the kind of the node.
      * \param kind [in] The new value of the kind.
      */
      void setKind(DeclarationKind _kind);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The DeclarationKind of the node. */
      DeclarationKind m_kind;

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
      * \brief Gives back iterator for the hasDeclarations edges.
      * \return Returns an iterator for the hasDeclarations edges.
      */
      ListIterator<declaration::VariableDeclarator> getDeclarationsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasDeclarations edges.
      * \return Returns an iterator for the hasDeclarations edges.
      */
      ListIterator<declaration::VariableDeclarator> getDeclarationsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasDeclarations edges or not.
      * \return Returns true if the node doesn't have any hasDeclarations edge.
      */
      bool getDeclarationsIsEmpty() const;

      /**
      * \brief Gives back how many hasDeclarations edges the node has.
      * \return Returns with the number of hasDeclarations edges.
      */
      unsigned getDeclarationsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasDeclarations edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasDeclarations edge.
      */
      void addDeclarations(const VariableDeclarator *node);

      /**
      * \brief Adds a new hasDeclarations edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasDeclarations edge.
      */
      void addDeclarations(NodeId id);

      /**
      * \brief Remove the hasDeclarations edge by id from the node.
      * \param id [in] The end point of the hasDeclarations edge.
      */
      void removeDeclarations(NodeId id);

      /**
      * \brief Remove the hasDeclarations edge from the node.
      * \param node [in] The end point of the hasDeclarations edge.
      */
      void removeDeclarations(VariableDeclarator *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasDeclarations edge points to. */
      ListIterator<declaration::VariableDeclarator>::Container hasDeclarationsContainer;

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

