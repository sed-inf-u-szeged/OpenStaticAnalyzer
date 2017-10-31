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

#ifndef _GENEALOGY_Component_H_
#define _GENEALOGY_Component_H_

#include "genealogy/inc/genealogy.h"

/**
* \file Component.h
* \brief Contains declaration of the Component class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief Component class, which represents the Component node.
  * (missing)
  * 
  * Attributes:
  *   - location (String) : (missing)
  *   - name (String) : (missing)
  *   - code (long) : (missing)
  */
  class Component : public Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Component(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Component();

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      Component & operator=(const Component&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      Component(const Component&);

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
      * \brief Gives back the location of the node.
      * \return Returns with the location.
      */
      const std::string& getLocation() const;

      /**
      * \brief Gives back the Key of location of the node.
      * \return Returns with the Key of the location.
      */
      Key getLocationKey() const;

      /**
      * \brief Gives back the name of the node.
      * \return Returns with the name.
      */
      const std::string& getName() const;

      /**
      * \brief Gives back the Key of name of the node.
      * \return Returns with the Key of the name.
      */
      Key getNameKey() const;

      /**
      * \brief Gives back the code of the node.
      * \return Returns with the code.
      */
      unsigned long long getCode() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the location of the node.
      * \param location [in] The new value of the location.
      */
      void setLocation(const std::string& _location);

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new value of the name.
      */
      void setName(const std::string& _name);

      /**
      * \internal
      * \brief Sets the code of the node.
      * \param code [in] The new value of the code.
      */
      void setCode(unsigned long long _code);

      /**
      * \internal
      * \brief Sets the location of the node.
      * \param location [in] The new Key of the location.
      */
      void setLocationKey(Key _location);

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new Key of the name.
      */
      void setNameKey(Key _name);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `location`. */
      Key m_location;

      /** \internal \brief The Key of the `name`. */
      Key m_name;

      /** \internal \brief The value of the `code`. */
      unsigned long long m_code;

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

