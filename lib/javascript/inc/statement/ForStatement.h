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

#ifndef _JAVASCRIPT_ForStatement_H_
#define _JAVASCRIPT_ForStatement_H_

#include "javascript/inc/javascript.h"

/**
* \file ForStatement.h
* \brief Contains declaration of the statement::ForStatement class.
* \brief The it get atributes from 
    * \brief base::Positioned
*/

namespace columbus { namespace javascript { namespace asg {
namespace statement {

  /**
  * \brief ForStatement class, which represents the statement::ForStatement node.
  * (missing)
  * 
  * Edges:
  *   - hasBody (statement::Statement, single) : (missing)
  *   - hasTest (expression::Expression, single) : (missing)
  *   - hasUpdate (expression::Expression, single) : (missing)
  *   - hasInit (base::Positioned, single) : (missing)
  */
  class ForStatement : public Statement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ForStatement(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ForStatement();

    private:
      /**
      * \brief This function always throws a JavaScriptException due to copying is not allowed!
      */
      ForStatement & operator=(const ForStatement&);

      /**
      * \brief This function always throws a JavaScriptException due to copying is not allowed!
      */
      ForStatement(const ForStatement&);

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
      * \brief Gives back the pointer of the node the hasBody edge points to.
      * \return Returns the end point of the hasBody edge.
      */
      statement::Statement* getBody() const;

      /**
      * \brief Gives back the pointer of the node the hasTest edge points to.
      * \return Returns the end point of the hasTest edge.
      */
      expression::Expression* getTest() const;

      /**
      * \brief Gives back the pointer of the node the hasUpdate edge points to.
      * \return Returns the end point of the hasUpdate edge.
      */
      expression::Expression* getUpdate() const;

      /**
      * \brief Gives back the pointer of the node the hasInit edge points to.
      * \return Returns the end point of the hasInit edge.
      */
      base::Positioned* getInit() const;


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
      void setBody(Statement *node);

      /**
      * \brief remove the hasBody edge.
      */
      void removeBody();

      /**
      * \brief Sets the hasTest edge.
      * \param id [in] The new end point of the hasTest edge.
      */
      void setTest(NodeId id);

      /**
      * \brief Sets the hasTest edge.
      * \param node [in] The new end point of the hasTest edge.
      */
      void setTest(expression::Expression *node);

      /**
      * \brief remove the hasTest edge.
      */
      void removeTest();

      /**
      * \brief Sets the hasUpdate edge.
      * \param id [in] The new end point of the hasUpdate edge.
      */
      void setUpdate(NodeId id);

      /**
      * \brief Sets the hasUpdate edge.
      * \param node [in] The new end point of the hasUpdate edge.
      */
      void setUpdate(expression::Expression *node);

      /**
      * \brief remove the hasUpdate edge.
      */
      void removeUpdate();

      /**
      * \brief Sets the hasInit edge.
      * \param id [in] The new end point of the hasInit edge.
      */
      void setInit(NodeId id);

      /**
      * \brief Sets the hasInit edge.
      * \param node [in] The new end point of the hasInit edge.
      */
      void setInit(base::Positioned *node);

      /**
      * \brief remove the hasInit edge.
      */
      void removeInit();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasBody edge points to. */
      NodeId m_hasBody;

      /** \internal \brief The id of the node the hasTest edge points to. */
      NodeId m_hasTest;

      /** \internal \brief The id of the node the hasUpdate edge points to. */
      NodeId m_hasUpdate;

      /** \internal \brief The id of the node the hasInit edge points to. */
      NodeId m_hasInit;

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

