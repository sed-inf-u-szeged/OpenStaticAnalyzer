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

#ifndef _JAVASCRIPT_ExportNamedDeclaration_H_
#define _JAVASCRIPT_ExportNamedDeclaration_H_

#include "javascript/inc/javascript.h"

/**
* \file ExportNamedDeclaration.h
* \brief Contains declaration of the declaration::ExportNamedDeclaration class.
* \brief The it get atributes from 
*/

namespace columbus { namespace javascript { namespace asg {
namespace declaration {

  /**
  * \brief ExportNamedDeclaration class, which represents the declaration::ExportNamedDeclaration node.
  * (missing)
  * 
  * Edges:
  *   - hasDeclaration (declaration::Declaration, single) : (missing)
  *   - hasSpecifiers (structure::ExportSpecifier, multiple) : (missing)
  *   - hasSource (expression::Literal, single) : (missing)
  */
  class ExportNamedDeclaration : public ModuleDeclaration {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ExportNamedDeclaration(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ExportNamedDeclaration();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      ExportNamedDeclaration & operator=(const ExportNamedDeclaration&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      ExportNamedDeclaration(const ExportNamedDeclaration&);

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
      * \brief Gives back the pointer of the node the hasDeclaration edge points to.
      * \return Returns the end point of the hasDeclaration edge.
      */
      declaration::Declaration* getDeclaration() const;

      /**
      * \brief Gives back iterator for the hasSpecifiers edges.
      * \return Returns an iterator for the hasSpecifiers edges.
      */
      ListIterator<structure::ExportSpecifier> getSpecifiersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasSpecifiers edges.
      * \return Returns an iterator for the hasSpecifiers edges.
      */
      ListIterator<structure::ExportSpecifier> getSpecifiersListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasSpecifiers edges or not.
      * \return Returns true if the node doesn't have any hasSpecifiers edge.
      */
      bool getSpecifiersIsEmpty() const;

      /**
      * \brief Gives back how many hasSpecifiers edges the node has.
      * \return Returns with the number of hasSpecifiers edges.
      */
      unsigned getSpecifiersSize() const;

      /**
      * \brief Gives back the pointer of the node the hasSource edge points to.
      * \return Returns the end point of the hasSource edge.
      */
      expression::Literal* getSource() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasDeclaration edge.
      * \param id [in] The new end point of the hasDeclaration edge.
      */
      void setDeclaration(NodeId id);

      /**
      * \brief Sets the hasDeclaration edge.
      * \param node [in] The new end point of the hasDeclaration edge.
      */
      void setDeclaration(Declaration *node);

      /**
      * \brief remove the hasDeclaration edge.
      */
      void removeDeclaration();

      /**
      * \brief Adds a new hasSpecifiers edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasSpecifiers edge.
      */
      void addSpecifiers(const structure::ExportSpecifier *node);

      /**
      * \brief Adds a new hasSpecifiers edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasSpecifiers edge.
      */
      void addSpecifiers(NodeId id);

      /**
      * \brief Remove the hasSpecifiers edge by id from the node.
      * \param id [in] The end point of the hasSpecifiers edge.
      */
      void removeSpecifiers(NodeId id);

      /**
      * \brief Remove the hasSpecifiers edge from the node.
      * \param node [in] The end point of the hasSpecifiers edge.
      */
      void removeSpecifiers(structure::ExportSpecifier *node);

      /**
      * \brief Sets the hasSource edge.
      * \param id [in] The new end point of the hasSource edge.
      */
      void setSource(NodeId id);

      /**
      * \brief Sets the hasSource edge.
      * \param node [in] The new end point of the hasSource edge.
      */
      void setSource(expression::Literal *node);

      /**
      * \brief remove the hasSource edge.
      */
      void removeSource();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasDeclaration edge points to. */
      NodeId m_hasDeclaration;

      /** \internal \brief Container stores the id of the nodes the hasSpecifiers edge points to. */
      ListIterator<structure::ExportSpecifier>::Container hasSpecifiersContainer;

      /** \internal \brief The id of the node the hasSource edge points to. */
      NodeId m_hasSource;

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

