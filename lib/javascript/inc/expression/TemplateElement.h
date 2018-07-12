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

#ifndef _JAVASCRIPT_TemplateElement_H_
#define _JAVASCRIPT_TemplateElement_H_

#include "javascript/inc/javascript.h"

/**
* \file TemplateElement.h
* \brief Contains declaration of the expression::TemplateElement class.
* \brief The it get atributes from 
*/

namespace columbus { namespace javascript { namespace asg {
namespace expression {

  /**
  * \brief TemplateElement class, which represents the expression::TemplateElement node.
  * (missing)
  * 
  * Attributes:
  *   - tail (boolean) : (missing)
  *   - cooked (String) : (missing)
  *   - value (String) : (missing)
  */
  class TemplateElement : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      TemplateElement(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~TemplateElement();

    private:
      /**
      * \brief This function always throws a JavaScriptException due to copying is not allowed!
      */
      TemplateElement & operator=(const TemplateElement&);

      /**
      * \brief This function always throws a JavaScriptException due to copying is not allowed!
      */
      TemplateElement(const TemplateElement&);

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
      * \brief Gives back the tail of the node.
      * \return Returns with the tail.
      */
      bool getTail() const;

      /**
      * \brief Gives back the cooked of the node.
      * \return Returns with the cooked.
      */
      const std::string& getCooked() const;

      /**
      * \brief Gives back the Key of cooked of the node.
      * \return Returns with the Key of the cooked.
      */
      Key getCookedKey() const;

      /**
      * \brief Gives back the value of the node.
      * \return Returns with the value.
      */
      const std::string& getValue() const;

      /**
      * \brief Gives back the Key of value of the node.
      * \return Returns with the Key of the value.
      */
      Key getValueKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the tail of the node.
      * \param tail [in] The new value of the tail.
      */
      void setTail(bool _tail);

      /**
      * \internal
      * \brief Sets the cooked of the node.
      * \param cooked [in] The new value of the cooked.
      */
      void setCooked(const std::string& _cooked);

      /**
      * \internal
      * \brief Sets the value of the node.
      * \param value [in] The new value of the value.
      */
      void setValue(const std::string& _value);

      /**
      * \internal
      * \brief Sets the cooked of the node.
      * \param cooked [in] The new Key of the cooked.
      */
      void setCookedKey(Key _cooked);

      /**
      * \internal
      * \brief Sets the value of the node.
      * \param value [in] The new Key of the value.
      */
      void setValueKey(Key _value);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `tail`. */
      bool m_tail : 1;

      /** \internal \brief The Key of the `cooked`. */
      Key m_cooked;

      /** \internal \brief The Key of the `value`. */
      Key m_value;

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

