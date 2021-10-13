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

#ifndef _JAVASCRIPT_Property_H_
#define _JAVASCRIPT_Property_H_

#include "javascript/inc/javascript.h"

/**
* \file Property.h
* \brief Contains declaration of the expression::Property class.
* \brief The it get atributes from 
*/

namespace columbus { namespace javascript { namespace asg {
namespace expression {

  /**
  * \brief Property class, which represents the expression::Property node.
  * (missing)
  * 
  * Attributes:
  *   - kind (PropertyKind) : (missing)
  *   - method (boolean) : (missing)
  *   - shorthand (boolean) : (missing)
  *   - computed (boolean) : (missing)
  * 
  * Edges:
  *   - hasValue (base::Positioned, single) : (missing)
  *   - hasKey (expression::Expression, single) : (missing)
  */
  class Property : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Property(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Property();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      Property & operator=(const Property&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      Property(const Property&);

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
      PropertyKind getKind() const;

      /**
      * \brief Gives back the method of the node.
      * \return Returns with the method.
      */
      bool getMethod() const;

      /**
      * \brief Gives back the shorthand of the node.
      * \return Returns with the shorthand.
      */
      bool getShorthand() const;

      /**
      * \brief Gives back the computed of the node.
      * \return Returns with the computed.
      */
      bool getComputed() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the kind of the node.
      * \param kind [in] The new value of the kind.
      */
      void setKind(PropertyKind _kind);

      /**
      * \internal
      * \brief Sets the method of the node.
      * \param method [in] The new value of the method.
      */
      void setMethod(bool _method);

      /**
      * \internal
      * \brief Sets the shorthand of the node.
      * \param shorthand [in] The new value of the shorthand.
      */
      void setShorthand(bool _shorthand);

      /**
      * \internal
      * \brief Sets the computed of the node.
      * \param computed [in] The new value of the computed.
      */
      void setComputed(bool _computed);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `method`. */
      bool m_method : 1;

      /** \internal \brief The value of the `shorthand`. */
      bool m_shorthand : 1;

      /** \internal \brief The value of the `computed`. */
      bool m_computed : 1;

      /** \internal \brief The PropertyKind of the node. */
      PropertyKind m_kind;

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
      * \brief Gives back the pointer of the node the hasValue edge points to.
      * \return Returns the end point of the hasValue edge.
      */
      base::Positioned* getValue() const;

      /**
      * \brief Gives back the pointer of the node the hasKey edge points to.
      * \return Returns the end point of the hasKey edge.
      */
      expression::Expression* getKey() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasValue edge.
      * \param id [in] The new end point of the hasValue edge.
      */
      void setValue(NodeId id);

      /**
      * \brief Sets the hasValue edge.
      * \param node [in] The new end point of the hasValue edge.
      */
      void setValue(base::Positioned *node);

      /**
      * \brief remove the hasValue edge.
      */
      void removeValue();

      /**
      * \brief Sets the hasKey edge.
      * \param id [in] The new end point of the hasKey edge.
      */
      void setKey(NodeId id);

      /**
      * \brief Sets the hasKey edge.
      * \param node [in] The new end point of the hasKey edge.
      */
      void setKey(Expression *node);

      /**
      * \brief remove the hasKey edge.
      */
      void removeKey();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasValue edge points to. */
      NodeId m_hasValue;

      /** \internal \brief The id of the node the hasKey edge points to. */
      NodeId m_hasKey;

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

