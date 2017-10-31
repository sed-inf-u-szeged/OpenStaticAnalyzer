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

#ifndef _GENEALOGY_CloneClass_H_
#define _GENEALOGY_CloneClass_H_

#include "genealogy/inc/genealogy.h"

/**
* \file CloneClass.h
* \brief Contains declaration of the CloneClass class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief CloneClass class, which represents the CloneClass node.
  * (missing)
  * 
  * Attributes:
  *   - fingerprint (String) : (missing)
  *   - instances (int) : (missing)
  *   - length (int) : (missing)
  *   - headNodeKind (int) : (missing)
  *   - cvCiSmells (int) : (missing)
  *   - ca (int) : (missing)
  *   - risk (double) : (missing)
  *   - gain (double) : (missing)
  *   - effort (double) : (missing)
  *   - cco (int) : (missing)
  *   - ce (int) : (missing)
  *   - clloc (double) : (missing)
  *   - cv (double) : (missing)
  *   - ncrad (double) : (missing)
  *   - type (CloneType) : (missing)
  * 
  * Edges:
  *   - nextNeighbours (CloneClass, multiple) : (missing)
  *   - prevNeighbours (CloneClass, multiple) : (missing)
  *   - items (CloneInstance, multiple) : (missing)
  */
  class CloneClass : public Clone {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      CloneClass(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~CloneClass();

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      CloneClass & operator=(const CloneClass&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      CloneClass(const CloneClass&);

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
      * \brief Gives back the fingerprint of the node.
      * \return Returns with the fingerprint.
      */
      const std::string& getFingerprint() const;

      /**
      * \brief Gives back the Key of fingerprint of the node.
      * \return Returns with the Key of the fingerprint.
      */
      Key getFingerprintKey() const;

      /**
      * \brief Gives back the instances of the node.
      * \return Returns with the instances.
      */
      unsigned getInstances() const;

      /**
      * \brief Gives back the length of the node.
      * \return Returns with the length.
      */
      unsigned getLength() const;

      /**
      * \brief Gives back the headNodeKind of the node.
      * \return Returns with the headNodeKind.
      */
      unsigned getHeadNodeKind() const;

      /**
      * \brief Gives back the cvCiSmells of the node.
      * \return Returns with the cvCiSmells.
      */
      unsigned getCvCiSmells() const;

      /**
      * \brief Gives back the ca of the node.
      * \return Returns with the ca.
      */
      unsigned getCa() const;

      /**
      * \brief Gives back the risk of the node.
      * \return Returns with the risk.
      */
      double getRisk() const;

      /**
      * \brief Gives back the gain of the node.
      * \return Returns with the gain.
      */
      double getGain() const;

      /**
      * \brief Gives back the effort of the node.
      * \return Returns with the effort.
      */
      double getEffort() const;

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
      * \brief Gives back the clloc of the node.
      * \return Returns with the clloc.
      */
      double getClloc() const;

      /**
      * \brief Gives back the cv of the node.
      * \return Returns with the cv.
      */
      double getCv() const;

      /**
      * \brief Gives back the ncrad of the node.
      * \return Returns with the ncrad.
      */
      double getNcrad() const;

      /**
      * \brief Gives back the type of the node.
      * \return Returns with the type.
      */
      CloneType getType() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the fingerprint of the node.
      * \param fingerprint [in] The new value of the fingerprint.
      */
      void setFingerprint(const std::string& _fingerprint);

      /**
      * \internal
      * \brief Sets the instances of the node.
      * \param instances [in] The new value of the instances.
      */
      void setInstances(unsigned _instances);

      /**
      * \internal
      * \brief Sets the length of the node.
      * \param length [in] The new value of the length.
      */
      void setLength(unsigned _length);

      /**
      * \internal
      * \brief Sets the headNodeKind of the node.
      * \param headNodeKind [in] The new value of the headNodeKind.
      */
      void setHeadNodeKind(unsigned _headNodeKind);

      /**
      * \internal
      * \brief Sets the cvCiSmells of the node.
      * \param cvCiSmells [in] The new value of the cvCiSmells.
      */
      void setCvCiSmells(unsigned _cvCiSmells);

      /**
      * \internal
      * \brief Sets the ca of the node.
      * \param ca [in] The new value of the ca.
      */
      void setCa(unsigned _ca);

      /**
      * \internal
      * \brief Sets the risk of the node.
      * \param risk [in] The new value of the risk.
      */
      void setRisk(double _risk);

      /**
      * \internal
      * \brief Sets the gain of the node.
      * \param gain [in] The new value of the gain.
      */
      void setGain(double _gain);

      /**
      * \internal
      * \brief Sets the effort of the node.
      * \param effort [in] The new value of the effort.
      */
      void setEffort(double _effort);

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
      * \brief Sets the clloc of the node.
      * \param clloc [in] The new value of the clloc.
      */
      void setClloc(double _clloc);

      /**
      * \internal
      * \brief Sets the cv of the node.
      * \param cv [in] The new value of the cv.
      */
      void setCv(double _cv);

      /**
      * \internal
      * \brief Sets the ncrad of the node.
      * \param ncrad [in] The new value of the ncrad.
      */
      void setNcrad(double _ncrad);

      /**
      * \internal
      * \brief Sets the type of the node.
      * \param type [in] The new value of the type.
      */
      void setType(CloneType _type);

      /**
      * \internal
      * \brief Sets the fingerprint of the node.
      * \param fingerprint [in] The new Key of the fingerprint.
      */
      void setFingerprintKey(Key _fingerprint);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `instances`. */
      unsigned m_instances;

      /** \internal \brief The value of the `length`. */
      unsigned m_length;

      /** \internal \brief The value of the `headNodeKind`. */
      unsigned m_headNodeKind;

      /** \internal \brief The value of the `cvCiSmells`. */
      unsigned m_cvCiSmells;

      /** \internal \brief The value of the `ca`. */
      unsigned m_ca;

      /** \internal \brief The value of the `cco`. */
      unsigned m_cco;

      /** \internal \brief The value of the `ce`. */
      unsigned m_ce;

      /** \internal \brief The CloneType of the node. */
      CloneType m_type;

      /** \internal \brief The Key of the `fingerprint`. */
      Key m_fingerprint;

      /** \internal \brief The value of the `risk`. */
      double m_risk;

      /** \internal \brief The value of the `gain`. */
      double m_gain;

      /** \internal \brief The value of the `effort`. */
      double m_effort;

      /** \internal \brief The value of the `clloc`. */
      double m_clloc;

      /** \internal \brief The value of the `cv`. */
      double m_cv;

      /** \internal \brief The value of the `ncrad`. */
      double m_ncrad;

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
      * \brief Gives back iterator for the nextNeighbours edges.
      * \return Returns an iterator for the nextNeighbours edges.
      */
      ListIterator<CloneClass> getNextNeighboursListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the nextNeighbours edges.
      * \return Returns an iterator for the nextNeighbours edges.
      */
      ListIterator<CloneClass> getNextNeighboursListIteratorEnd() const;

      /**
      * \brief Tells whether the node has nextNeighbours edges or not.
      * \return Returns true if the node doesn't have any nextNeighbours edge.
      */
      bool getNextNeighboursIsEmpty() const;

      /**
      * \brief Gives back how many nextNeighbours edges the node has.
      * \return Returns with the number of nextNeighbours edges.
      */
      unsigned getNextNeighboursSize() const;

      /**
      * \brief Gives back iterator for the prevNeighbours edges.
      * \return Returns an iterator for the prevNeighbours edges.
      */
      ListIterator<CloneClass> getPrevNeighboursListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the prevNeighbours edges.
      * \return Returns an iterator for the prevNeighbours edges.
      */
      ListIterator<CloneClass> getPrevNeighboursListIteratorEnd() const;

      /**
      * \brief Tells whether the node has prevNeighbours edges or not.
      * \return Returns true if the node doesn't have any prevNeighbours edge.
      */
      bool getPrevNeighboursIsEmpty() const;

      /**
      * \brief Gives back how many prevNeighbours edges the node has.
      * \return Returns with the number of prevNeighbours edges.
      */
      unsigned getPrevNeighboursSize() const;

      /**
      * \brief Gives back iterator for the items edges.
      * \return Returns an iterator for the items edges.
      */
      ListIterator<CloneInstance> getItemsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the items edges.
      * \return Returns an iterator for the items edges.
      */
      ListIterator<CloneInstance> getItemsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has items edges or not.
      * \return Returns true if the node doesn't have any items edge.
      */
      bool getItemsIsEmpty() const;

      /**
      * \brief Gives back how many items edges the node has.
      * \return Returns with the number of items edges.
      */
      unsigned getItemsSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new nextNeighbours edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new nextNeighbours edge.
      */
      void addNextNeighbours(const CloneClass *node);

      /**
      * \brief Adds a new nextNeighbours edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new nextNeighbours edge.
      */
      void addNextNeighbours(NodeId id);

      /**
      * \brief Remove the nextNeighbours edge by id from the node.
      * \param id [in] The end point of the nextNeighbours edge.
      */
      void removeNextNeighbours(NodeId id);

      /**
      * \brief Remove the nextNeighbours edge from the node.
      * \param node [in] The end point of the nextNeighbours edge.
      */
      void removeNextNeighbours(CloneClass *node);

      /**
      * \brief Adds a new prevNeighbours edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new prevNeighbours edge.
      */
      void addPrevNeighbours(const CloneClass *node);

      /**
      * \brief Adds a new prevNeighbours edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new prevNeighbours edge.
      */
      void addPrevNeighbours(NodeId id);

      /**
      * \brief Remove the prevNeighbours edge by id from the node.
      * \param id [in] The end point of the prevNeighbours edge.
      */
      void removePrevNeighbours(NodeId id);

      /**
      * \brief Remove the prevNeighbours edge from the node.
      * \param node [in] The end point of the prevNeighbours edge.
      */
      void removePrevNeighbours(CloneClass *node);

      /**
      * \brief Adds a new items edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new items edge.
      */
      void addItems(const CloneInstance *node);

      /**
      * \brief Adds a new items edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new items edge.
      */
      void addItems(NodeId id);

      /**
      * \brief Remove the items edge by id from the node.
      * \param id [in] The end point of the items edge.
      */
      void removeItems(NodeId id);

      /**
      * \brief Remove the items edge from the node.
      * \param node [in] The end point of the items edge.
      */
      void removeItems(CloneInstance *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the nextNeighbours edge points to. */
      ListIterator<CloneClass>::Container nextNeighboursContainer;

      /** \internal \brief Container stores the id of the nodes the prevNeighbours edge points to. */
      ListIterator<CloneClass>::Container prevNeighboursContainer;

      /** \internal \brief Container stores the id of the nodes the items edge points to. */
      ListIterator<CloneInstance>::Container itemsContainer;

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

