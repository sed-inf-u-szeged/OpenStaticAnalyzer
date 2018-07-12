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

#ifndef _GENEALOGY_CaseLabel_H_
#define _GENEALOGY_CaseLabel_H_

#include "genealogy/inc/genealogy.h"

/**
* \file CaseLabel.h
* \brief Contains declaration of the CaseLabel class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief CaseLabel class, which represents the CaseLabel node.
  * (missing)
  * 
  * Attributes:
  *   - caseValue (String) : (missing)
  *   - nodeId (int) : (missing)
  * 
  * Edges:
  *   - component (Component, single) : (missing)
  */
  class CaseLabel : public SourceCodeElement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      CaseLabel(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~CaseLabel();

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      CaseLabel & operator=(const CaseLabel&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      CaseLabel(const CaseLabel&);

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
      * \brief Gives back the caseValue of the node.
      * \return Returns with the caseValue.
      */
      const std::string& getCaseValue() const;

      /**
      * \brief Gives back the Key of caseValue of the node.
      * \return Returns with the Key of the caseValue.
      */
      Key getCaseValueKey() const;

      /**
      * \brief Gives back the nodeId of the node.
      * \return Returns with the nodeId.
      */
      unsigned getNodeId() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the caseValue of the node.
      * \param caseValue [in] The new value of the caseValue.
      */
      void setCaseValue(const std::string& _caseValue);

      /**
      * \internal
      * \brief Sets the nodeId of the node.
      * \param nodeId [in] The new value of the nodeId.
      */
      void setNodeId(unsigned _nodeId);

      /**
      * \internal
      * \brief Sets the caseValue of the node.
      * \param caseValue [in] The new Key of the caseValue.
      */
      void setCaseValueKey(Key _caseValue);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `nodeId`. */
      unsigned m_nodeId;

      /** \internal \brief The Key of the `caseValue`. */
      Key m_caseValue;

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
      * \brief Gives back the pointer of the node the component edge points to.
      * \return Returns the end point of the component edge.
      */
      Component* getComponent() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the component edge.
      * \param id [in] The new end point of the component edge.
      */
      void setComponent(NodeId id);

      /**
      * \brief Sets the component edge.
      * \param node [in] The new end point of the component edge.
      */
      void setComponent(Component *node);

      /**
      * \brief remove the component edge.
      */
      void removeComponent();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the component edge points to. */
      NodeId m_component;

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
      virtual double getSimilarity(const Base& node);

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


      friend class genealogy::Factory;
      friend class genealogy::VisitorSave;
  };


}}
#endif

