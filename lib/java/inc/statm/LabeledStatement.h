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

#ifndef _JAVA_LabeledStatement_H_
#define _JAVA_LabeledStatement_H_

#include "java/inc/java.h"

/**
* \file LabeledStatement.h
* \brief Contains declaration of the statm::LabeledStatement class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace statm {

  /**
  * \brief LabeledStatement class, which represents the statm::LabeledStatement node.
  * (missing)
  * 
  * Attributes:
  *   - label (String) : (missing)
  *   - colonPosition (Range) : (missing)
  * 
  * Edges:
  *   - hasStatement (statm::Statement, single) : (missing)
  */
  class LabeledStatement : public Statement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      LabeledStatement(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~LabeledStatement();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      LabeledStatement & operator=(const LabeledStatement&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      LabeledStatement(const LabeledStatement&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const LabeledStatement& other, bool tryOnVirtualParent);

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
      * \brief Gives back the label of the node.
      * \return Returns with the label.
      */
      const std::string& getLabel() const;

      /**
      * \brief Gives back the Key of label of the node.
      * \return Returns with the Key of the label.
      */
      Key getLabelKey() const;

      /**
      * \brief Gives back the colonPosition of the node.
      * \return Returns with the colonPosition.
      */
      virtual const Range getColonPosition() const;

      /**
      * \brief Compare two node by colonPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByColonPosition(const LabeledStatement& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the label of the node.
      * \param label [in] The new value of the label.
      */
      void setLabel(const std::string& _label);

      /**
      * \internal
      * \brief Sets the colonPosition of the node.
      * \param colonPosition [in] The new value of the colonPosition.
      */
      virtual void setColonPosition(const Range& _colonPosition);

      /**
      * \internal
      * \brief Sets the label of the node.
      * \param label [in] The new Key of the label.
      */
      void setLabelKey(Key _label);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `label`. */
      Key m_label;

      /** \internal \brief todo (unknown). */
      MultiRange m_colonPosition;

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
      * \brief Gives back the pointer of the node the hasStatement edge points to.
      * \return Returns the end point of the hasStatement edge.
      */
      statm::Statement* getStatement() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasStatement edge.
      * \param id [in] The new end point of the hasStatement edge.
      */
      void setStatement(NodeId id);

      /**
      * \brief Sets the hasStatement edge.
      * \param node [in] The new end point of the hasStatement edge.
      */
      void setStatement(Statement *node);

      /**
      * \brief remove the hasStatement edge.
      */
      void removeStatement();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasStatement edge points to. */
      NodeId m_hasStatement;

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

      /**
      * \internal
      * \brief Sorts some edges and attributes of the node.
      */
      virtual void sort(bool withVirtualBase = true);


      friend class java::asg::Factory;
      friend class java::asg::VisitorSave;
  };

} 


}}}
#endif

