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

#ifndef _JAVASCRIPT_Function_H_
#define _JAVASCRIPT_Function_H_

#include "javascript/inc/javascript.h"

/**
* \file Function.h
* \brief Contains declaration of the statement::Function class.
* \brief The it get atributes from 
*/

namespace columbus { namespace javascript { namespace asg {
namespace statement {

  /**
  * \brief Function class, which represents the statement::Function node.
  * (missing)
  * 
  * Attributes:
  *   - generator (boolean) : (missing)
  *   - async (boolean) : (missing)
  * 
  * Edges:
  *   - hasParams (statement::Pattern, multiple) : (missing)
  *   - hasBody (base::Positioned, single) : (missing)
  *   - hasIdentifier (expression::Identifier, single) : (missing)
  */
  class Function : public virtual base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Function(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Function();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      Function & operator=(const Function&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      Function(const Function&);

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
      * \brief Gives back the generator of the node.
      * \return Returns with the generator.
      */
      bool getGenerator() const;

      /**
      * \brief Gives back the async of the node.
      * \return Returns with the async.
      */
      bool getAsync() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the generator of the node.
      * \param generator [in] The new value of the generator.
      */
      void setGenerator(bool _generator);

      /**
      * \internal
      * \brief Sets the async of the node.
      * \param async [in] The new value of the async.
      */
      void setAsync(bool _async);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `generator`. */
      bool m_generator : 1;

      /** \internal \brief The value of the `async`. */
      bool m_async : 1;

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
      * \brief Gives back iterator for the hasParams edges.
      * \return Returns an iterator for the hasParams edges.
      */
      ListIterator<statement::Pattern> getParamsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasParams edges.
      * \return Returns an iterator for the hasParams edges.
      */
      ListIterator<statement::Pattern> getParamsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasParams edges or not.
      * \return Returns true if the node doesn't have any hasParams edge.
      */
      bool getParamsIsEmpty() const;

      /**
      * \brief Gives back how many hasParams edges the node has.
      * \return Returns with the number of hasParams edges.
      */
      unsigned getParamsSize() const;

      /**
      * \brief Gives back the pointer of the node the hasBody edge points to.
      * \return Returns the end point of the hasBody edge.
      */
      base::Positioned* getBody() const;

      /**
      * \brief Gives back the pointer of the node the hasIdentifier edge points to.
      * \return Returns the end point of the hasIdentifier edge.
      */
      expression::Identifier* getIdentifier() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasParams edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasParams edge.
      */
      void addParams(const Pattern *node);

      /**
      * \brief Adds a new hasParams edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasParams edge.
      */
      void addParams(NodeId id);

      /**
      * \brief Remove the hasParams edge by id from the node.
      * \param id [in] The end point of the hasParams edge.
      */
      void removeParams(NodeId id);

      /**
      * \brief Remove the hasParams edge from the node.
      * \param node [in] The end point of the hasParams edge.
      */
      void removeParams(Pattern *node);

      /**
      * \brief Sets the hasBody edge.
      * \param id [in] The new end point of the hasBody edge.
      */
      void setBody(NodeId id);

      /**
      * \brief Sets the hasBody edge.
      * \param node [in] The new end point of the hasBody edge.
      */
      void setBody(base::Positioned *node);

      /**
      * \brief remove the hasBody edge.
      */
      void removeBody();

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

      /** \internal \brief Container stores the id of the nodes the hasParams edge points to. */
      ListIterator<statement::Pattern>::Container hasParamsContainer;

      /** \internal \brief The id of the node the hasBody edge points to. */
      NodeId m_hasBody;

      /** \internal \brief The id of the node the hasIdentifier edge points to. */
      NodeId m_hasIdentifier;

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

