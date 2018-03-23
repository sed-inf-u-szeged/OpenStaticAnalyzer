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

#ifndef _CSHARP_GroupClauseSyntax_H_
#define _CSHARP_GroupClauseSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file GroupClauseSyntax.h
* \brief Contains declaration of the structure::GroupClauseSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief GroupClauseSyntax class, which represents the structure::GroupClauseSyntax node.
  * (missing)
  * 
  * Edges:
  *   - ByExpression (expression::ExpressionSyntax, single) : (missing)
  *   - GroupExpression (expression::ExpressionSyntax, single) : (missing)
  */
  class GroupClauseSyntax : public SelectOrGroupClauseSyntax {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      GroupClauseSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~GroupClauseSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      GroupClauseSyntax & operator=(const GroupClauseSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      GroupClauseSyntax(const GroupClauseSyntax&);

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
      * \brief Gives back the pointer of the node the ByExpression edge points to.
      * \return Returns the end point of the ByExpression edge.
      */
      expression::ExpressionSyntax* getByExpression() const;

      /**
      * \brief Gives back the pointer of the node the GroupExpression edge points to.
      * \return Returns the end point of the GroupExpression edge.
      */
      expression::ExpressionSyntax* getGroupExpression() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the ByExpression edge.
      * \param id [in] The new end point of the ByExpression edge.
      */
      void setByExpression(NodeId id);

      /**
      * \brief Sets the ByExpression edge.
      * \param node [in] The new end point of the ByExpression edge.
      */
      void setByExpression(expression::ExpressionSyntax *node);

      /**
      * \brief remove the ByExpression edge.
      */
      void removeByExpression();

      /**
      * \brief Sets the GroupExpression edge.
      * \param id [in] The new end point of the GroupExpression edge.
      */
      void setGroupExpression(NodeId id);

      /**
      * \brief Sets the GroupExpression edge.
      * \param node [in] The new end point of the GroupExpression edge.
      */
      void setGroupExpression(expression::ExpressionSyntax *node);

      /**
      * \brief remove the GroupExpression edge.
      */
      void removeGroupExpression();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the ByExpression edge points to. */
      NodeId m_ByExpression;

      /** \internal \brief The id of the node the GroupExpression edge points to. */
      NodeId m_GroupExpression;

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


      friend class csharp::asg::Factory;
      friend class csharp::asg::VisitorSave;
  };

} 


}}}
#endif

