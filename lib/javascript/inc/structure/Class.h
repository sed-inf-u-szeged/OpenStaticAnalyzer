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

#ifndef _JAVASCRIPT_Class_H_
#define _JAVASCRIPT_Class_H_

#include "javascript/inc/javascript.h"

/**
* \file Class.h
* \brief Contains declaration of the structure::Class class.
* \brief The it get atributes from 
*/

namespace columbus { namespace javascript { namespace asg {
namespace structure {

  /**
  * \brief Class class, which represents the structure::Class node.
  * (missing)
  * 
  * Edges:
  *   - hasBody (structure::ClassBody, single) : (missing)
  *   - hasSuperClass (expression::Expression, single) : (missing)
  *   - hasIdentifier (expression::Identifier, single) : (missing)
  */
  class Class : public virtual base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Class(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Class();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      Class & operator=(const Class&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      Class(const Class&);

    public:
      /**
      * \brief Gives back the NodeKind of the node.
      * \return Returns with the NodeKind.
      */
      virtual NodeKind getNodeKind() const = 0;

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
      * \brief Gives back the pointer of the node the hasBody edge points to.
      * \return Returns the end point of the hasBody edge.
      */
      structure::ClassBody* getBody() const;

      /**
      * \brief Gives back the pointer of the node the hasSuperClass edge points to.
      * \return Returns the end point of the hasSuperClass edge.
      */
      expression::Expression* getSuperClass() const;

      /**
      * \brief Gives back the pointer of the node the hasIdentifier edge points to.
      * \return Returns the end point of the hasIdentifier edge.
      */
      expression::Identifier* getIdentifier() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasBody edge.
      * \param id [in] The new end point of the hasBody edge.
      */
      void setBody(NodeId id);

      /**
      * \brief Sets the hasBody edge.
      * \param node [in] The new end point of the hasBody edge.
      */
      void setBody(ClassBody *node);

      /**
      * \brief remove the hasBody edge.
      */
      void removeBody();

      /**
      * \brief Sets the hasSuperClass edge.
      * \param id [in] The new end point of the hasSuperClass edge.
      */
      void setSuperClass(NodeId id);

      /**
      * \brief Sets the hasSuperClass edge.
      * \param node [in] The new end point of the hasSuperClass edge.
      */
      void setSuperClass(expression::Expression *node);

      /**
      * \brief remove the hasSuperClass edge.
      */
      void removeSuperClass();

      /**
      * \brief Sets the hasIdentifier edge.
      * \param id [in] The new end point of the hasIdentifier edge.
      */
      void setIdentifier(NodeId id);

      /**
      * \brief Sets the hasIdentifier edge.
      * \param node [in] The new end point of the hasIdentifier edge.
      */
      void setIdentifier(expression::Identifier *node);

      /**
      * \brief remove the hasIdentifier edge.
      */
      void removeIdentifier();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasBody edge points to. */
      NodeId m_hasBody;

      /** \internal \brief The id of the node the hasSuperClass edge points to. */
      NodeId m_hasSuperClass;

      /** \internal \brief The id of the node the hasIdentifier edge points to. */
      NodeId m_hasIdentifier;

    public:

      // ---------- Accept functions for Visitor it now pure virtual ----------

      /**
      * \brief It calls the appropriate visit method of the given visitor in the child nodes.
      * \param visitor [in] The used visitor.
      */
      virtual void accept(Visitor& visitor) const = 0;

      /**
      * \brief It calls the appropriate visitEnd method of the given visitor in the child nodes.
      * \param visitor [in] The used visitor.
      */
      virtual void acceptEnd(Visitor& visitor) const = 0;

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

