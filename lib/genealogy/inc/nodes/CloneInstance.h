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

#ifndef _GENEALOGY_CloneInstance_H_
#define _GENEALOGY_CloneInstance_H_

#include "genealogy/inc/genealogy.h"

/**
* \file CloneInstance.h
* \brief Contains declaration of the CloneInstance class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief CloneInstance class, which represents the CloneInstance node.
  * (missing)
  * 
  * Attributes:
  *   - path (String) : (missing)
  *   - line (int) : (missing)
  *   - col (int) : (missing)
  *   - endLine (int) : (missing)
  *   - endCol (int) : (missing)
  *   - cvMetricVariability (int) : (missing)
  *   - ca (int) : (missing)
  *   - cco (int) : (missing)
  *   - ce (int) : (missing)
  *   - cv (double) : (missing)
  *   - risk (double) : (missing)
  *   - rootNodes (String) : (missing)
  *   - rootBegin (int) : (missing)
  *   - rootLength (int) : (missing)
  *   - F2_OrdinalNumber (int) : (missing)
  *   - F3_HeadNodeUniqueName (String) : (missing)
  *   - F4_AncestorUniqueName (String) : (missing)
  *   - F5_L1 (int) : (missing)
  *   - F5_L2 (int) : (missing)
  *   - F5_L3 (int) : (missing)
  *   - F6_LexicalStructure (String) : (missing)
  * 
  * Edges:
  *   - intersects (CloneInstance, multiple) : (missing)
  *   - component (Component, single) : (missing)
  *   - cloneClass (CloneClass, single) : (missing)
  */
  class CloneInstance : public Clone {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      CloneInstance(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~CloneInstance();

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      CloneInstance & operator=(const CloneInstance&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      CloneInstance(const CloneInstance&);

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
      * \brief Gives back the path of the node.
      * \return Returns with the path.
      */
      const std::string& getPath() const;

      /**
      * \brief Gives back the Key of path of the node.
      * \return Returns with the Key of the path.
      */
      Key getPathKey() const;

      /**
      * \brief Gives back the line of the node.
      * \return Returns with the line.
      */
      unsigned getLine() const;

      /**
      * \brief Gives back the col of the node.
      * \return Returns with the col.
      */
      unsigned getCol() const;

      /**
      * \brief Gives back the endLine of the node.
      * \return Returns with the endLine.
      */
      unsigned getEndLine() const;

      /**
      * \brief Gives back the endCol of the node.
      * \return Returns with the endCol.
      */
      unsigned getEndCol() const;

      /**
      * \brief Gives back the cvMetricVariability of the node.
      * \return Returns with the cvMetricVariability.
      */
      unsigned getCvMetricVariability() const;

      /**
      * \brief Gives back the ca of the node.
      * \return Returns with the ca.
      */
      unsigned getCa() const;

      /**
      * \brief Gives back the cco of the node.
      * \return Returns with the cco.
      */
      unsigned getCco() const;

      /**
      * \brief Gives back the ce of the node.
      * \return Returns with the ce.
      */
      unsigned getCe() const;

      /**
      * \brief Gives back the cv of the node.
      * \return Returns with the cv.
      */
      double getCv() const;

      /**
      * \brief Gives back the risk of the node.
      * \return Returns with the risk.
      */
      double getRisk() const;

      /**
      * \brief Gives back the rootNodes of the node.
      * \return Returns with the rootNodes.
      */
      const std::string& getRootNodes() const;

      /**
      * \brief Gives back the Key of rootNodes of the node.
      * \return Returns with the Key of the rootNodes.
      */
      Key getRootNodesKey() const;

      /**
      * \brief Gives back the rootBegin of the node.
      * \return Returns with the rootBegin.
      */
      unsigned getRootBegin() const;

      /**
      * \brief Gives back the rootLength of the node.
      * \return Returns with the rootLength.
      */
      unsigned getRootLength() const;

      /**
      * \brief Gives back the F2_OrdinalNumber of the node.
      * \return Returns with the F2_OrdinalNumber.
      */
      unsigned getF2_OrdinalNumber() const;

      /**
      * \brief Gives back the F3_HeadNodeUniqueName of the node.
      * \return Returns with the F3_HeadNodeUniqueName.
      */
      const std::string& getF3_HeadNodeUniqueName() const;

      /**
      * \brief Gives back the Key of F3_HeadNodeUniqueName of the node.
      * \return Returns with the Key of the F3_HeadNodeUniqueName.
      */
      Key getF3_HeadNodeUniqueNameKey() const;

      /**
      * \brief Gives back the F4_AncestorUniqueName of the node.
      * \return Returns with the F4_AncestorUniqueName.
      */
      const std::string& getF4_AncestorUniqueName() const;

      /**
      * \brief Gives back the Key of F4_AncestorUniqueName of the node.
      * \return Returns with the Key of the F4_AncestorUniqueName.
      */
      Key getF4_AncestorUniqueNameKey() const;

      /**
      * \brief Gives back the F5_L1 of the node.
      * \return Returns with the F5_L1.
      */
      unsigned getF5_L1() const;

      /**
      * \brief Gives back the F5_L2 of the node.
      * \return Returns with the F5_L2.
      */
      unsigned getF5_L2() const;

      /**
      * \brief Gives back the F5_L3 of the node.
      * \return Returns with the F5_L3.
      */
      unsigned getF5_L3() const;

      /**
      * \brief Gives back the F6_LexicalStructure of the node.
      * \return Returns with the F6_LexicalStructure.
      */
      const std::string& getF6_LexicalStructure() const;

      /**
      * \brief Gives back the Key of F6_LexicalStructure of the node.
      * \return Returns with the Key of the F6_LexicalStructure.
      */
      Key getF6_LexicalStructureKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the path of the node.
      * \param path [in] The new value of the path.
      */
      void setPath(const std::string& _path);

      /**
      * \internal
      * \brief Sets the line of the node.
      * \param line [in] The new value of the line.
      */
      void setLine(unsigned _line);

      /**
      * \internal
      * \brief Sets the col of the node.
      * \param col [in] The new value of the col.
      */
      void setCol(unsigned _col);

      /**
      * \internal
      * \brief Sets the endLine of the node.
      * \param endLine [in] The new value of the endLine.
      */
      void setEndLine(unsigned _endLine);

      /**
      * \internal
      * \brief Sets the endCol of the node.
      * \param endCol [in] The new value of the endCol.
      */
      void setEndCol(unsigned _endCol);

      /**
      * \internal
      * \brief Sets the cvMetricVariability of the node.
      * \param cvMetricVariability [in] The new value of the cvMetricVariability.
      */
      void setCvMetricVariability(unsigned _cvMetricVariability);

      /**
      * \internal
      * \brief Sets the ca of the node.
      * \param ca [in] The new value of the ca.
      */
      void setCa(unsigned _ca);

      /**
      * \internal
      * \brief Sets the cco of the node.
      * \param cco [in] The new value of the cco.
      */
      void setCco(unsigned _cco);

      /**
      * \internal
      * \brief Sets the ce of the node.
      * \param ce [in] The new value of the ce.
      */
      void setCe(unsigned _ce);

      /**
      * \internal
      * \brief Sets the cv of the node.
      * \param cv [in] The new value of the cv.
      */
      void setCv(double _cv);

      /**
      * \internal
      * \brief Sets the risk of the node.
      * \param risk [in] The new value of the risk.
      */
      void setRisk(double _risk);

      /**
      * \internal
      * \brief Sets the rootNodes of the node.
      * \param rootNodes [in] The new value of the rootNodes.
      */
      void setRootNodes(const std::string& _rootNodes);

      /**
      * \internal
      * \brief Sets the rootBegin of the node.
      * \param rootBegin [in] The new value of the rootBegin.
      */
      void setRootBegin(unsigned _rootBegin);

      /**
      * \internal
      * \brief Sets the rootLength of the node.
      * \param rootLength [in] The new value of the rootLength.
      */
      void setRootLength(unsigned _rootLength);

      /**
      * \internal
      * \brief Sets the F2_OrdinalNumber of the node.
      * \param F2_OrdinalNumber [in] The new value of the F2_OrdinalNumber.
      */
      void setF2_OrdinalNumber(unsigned _F2_OrdinalNumber);

      /**
      * \internal
      * \brief Sets the F3_HeadNodeUniqueName of the node.
      * \param F3_HeadNodeUniqueName [in] The new value of the F3_HeadNodeUniqueName.
      */
      void setF3_HeadNodeUniqueName(const std::string& _F3_HeadNodeUniqueName);

      /**
      * \internal
      * \brief Sets the F4_AncestorUniqueName of the node.
      * \param F4_AncestorUniqueName [in] The new value of the F4_AncestorUniqueName.
      */
      void setF4_AncestorUniqueName(const std::string& _F4_AncestorUniqueName);

      /**
      * \internal
      * \brief Sets the F5_L1 of the node.
      * \param F5_L1 [in] The new value of the F5_L1.
      */
      void setF5_L1(unsigned _F5_L1);

      /**
      * \internal
      * \brief Sets the F5_L2 of the node.
      * \param F5_L2 [in] The new value of the F5_L2.
      */
      void setF5_L2(unsigned _F5_L2);

      /**
      * \internal
      * \brief Sets the F5_L3 of the node.
      * \param F5_L3 [in] The new value of the F5_L3.
      */
      void setF5_L3(unsigned _F5_L3);

      /**
      * \internal
      * \brief Sets the F6_LexicalStructure of the node.
      * \param F6_LexicalStructure [in] The new value of the F6_LexicalStructure.
      */
      void setF6_LexicalStructure(const std::string& _F6_LexicalStructure);

      /**
      * \internal
      * \brief Sets the path of the node.
      * \param path [in] The new Key of the path.
      */
      void setPathKey(Key _path);

      /**
      * \internal
      * \brief Sets the rootNodes of the node.
      * \param rootNodes [in] The new Key of the rootNodes.
      */
      void setRootNodesKey(Key _rootNodes);

      /**
      * \internal
      * \brief Sets the F3_HeadNodeUniqueName of the node.
      * \param F3_HeadNodeUniqueName [in] The new Key of the F3_HeadNodeUniqueName.
      */
      void setF3_HeadNodeUniqueNameKey(Key _F3_HeadNodeUniqueName);

      /**
      * \internal
      * \brief Sets the F4_AncestorUniqueName of the node.
      * \param F4_AncestorUniqueName [in] The new Key of the F4_AncestorUniqueName.
      */
      void setF4_AncestorUniqueNameKey(Key _F4_AncestorUniqueName);

      /**
      * \internal
      * \brief Sets the F6_LexicalStructure of the node.
      * \param F6_LexicalStructure [in] The new Key of the F6_LexicalStructure.
      */
      void setF6_LexicalStructureKey(Key _F6_LexicalStructure);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `line`. */
      unsigned m_line;

      /** \internal \brief The value of the `col`. */
      unsigned m_col;

      /** \internal \brief The value of the `endLine`. */
      unsigned m_endLine;

      /** \internal \brief The value of the `endCol`. */
      unsigned m_endCol;

      /** \internal \brief The value of the `cvMetricVariability`. */
      unsigned m_cvMetricVariability;

      /** \internal \brief The value of the `ca`. */
      unsigned m_ca;

      /** \internal \brief The value of the `cco`. */
      unsigned m_cco;

      /** \internal \brief The value of the `ce`. */
      unsigned m_ce;

      /** \internal \brief The value of the `rootBegin`. */
      unsigned m_rootBegin;

      /** \internal \brief The value of the `rootLength`. */
      unsigned m_rootLength;

      /** \internal \brief The value of the `F2_OrdinalNumber`. */
      unsigned m_F2_OrdinalNumber;

      /** \internal \brief The value of the `F5_L1`. */
      unsigned m_F5_L1;

      /** \internal \brief The value of the `F5_L2`. */
      unsigned m_F5_L2;

      /** \internal \brief The value of the `F5_L3`. */
      unsigned m_F5_L3;

      /** \internal \brief The Key of the `path`. */
      Key m_path;

      /** \internal \brief The value of the `cv`. */
      double m_cv;

      /** \internal \brief The value of the `risk`. */
      double m_risk;

      /** \internal \brief The Key of the `rootNodes`. */
      Key m_rootNodes;

      /** \internal \brief The Key of the `F3_HeadNodeUniqueName`. */
      Key m_F3_HeadNodeUniqueName;

      /** \internal \brief The Key of the `F4_AncestorUniqueName`. */
      Key m_F4_AncestorUniqueName;

      /** \internal \brief The Key of the `F6_LexicalStructure`. */
      Key m_F6_LexicalStructure;

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
      * \brief Gives back iterator for the intersects edges.
      * \return Returns an iterator for the intersects edges.
      */
      ListIterator<CloneInstance> getIntersectsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the intersects edges.
      * \return Returns an iterator for the intersects edges.
      */
      ListIterator<CloneInstance> getIntersectsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has intersects edges or not.
      * \return Returns true if the node doesn't have any intersects edge.
      */
      bool getIntersectsIsEmpty() const;

      /**
      * \brief Gives back how many intersects edges the node has.
      * \return Returns with the number of intersects edges.
      */
      unsigned getIntersectsSize() const;

      /**
      * \brief Gives back the pointer of the node the component edge points to.
      * \return Returns the end point of the component edge.
      */
      Component* getComponent() const;

      /**
      * \brief Gives back the pointer of the node the cloneClass edge points to.
      * \return Returns the end point of the cloneClass edge.
      */
      CloneClass* getCloneClass() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new intersects edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new intersects edge.
      */
      void addIntersects(const CloneInstance *node);

      /**
      * \brief Adds a new intersects edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new intersects edge.
      */
      void addIntersects(NodeId id);

      /**
      * \brief Remove the intersects edge by id from the node.
      * \param id [in] The end point of the intersects edge.
      */
      void removeIntersects(NodeId id);

      /**
      * \brief Remove the intersects edge from the node.
      * \param node [in] The end point of the intersects edge.
      */
      void removeIntersects(CloneInstance *node);

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

      /**
      * \brief Sets the cloneClass edge.
      * \param id [in] The new end point of the cloneClass edge.
      */
      void setCloneClass(NodeId id);

      /**
      * \brief Sets the cloneClass edge.
      * \param node [in] The new end point of the cloneClass edge.
      */
      void setCloneClass(CloneClass *node);

      /**
      * \brief remove the cloneClass edge.
      */
      void removeCloneClass();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the intersects edge points to. */
      ListIterator<CloneInstance>::Container intersectsContainer;

      /** \internal \brief The id of the node the component edge points to. */
      NodeId m_component;

      /** \internal \brief The id of the node the cloneClass edge points to. */
      NodeId m_cloneClass;

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

