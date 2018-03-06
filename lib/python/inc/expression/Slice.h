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

#ifndef _PYTHON_Slice_H_
#define _PYTHON_Slice_H_

#include "python/inc/python.h"

/**
* \file Slice.h
* \brief Contains declaration of the expression::Slice class.
* \brief The it get atributes from 
*/

namespace columbus { namespace python { namespace asg {
namespace expression {

  /**
  * \brief Slice class, which represents the expression::Slice node.
  * (missing)
  * 
  * Edges:
  *   - hasLowerBound (expression::Expression, single) : (missing)
  *   - hasStride (expression::Expression, single) : (missing)
  *   - hasUpperBound (expression::Expression, single) : (missing)
  */
  class Slice : public Slicing {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Slice(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Slice();

    private:
      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      Slice & operator=(const Slice&);

      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      Slice(const Slice&);

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
      * \brief Gives back the pointer of the node the hasLowerBound edge points to.
      * \return Returns the end point of the hasLowerBound edge.
      */
      expression::Expression* getLowerBound() const;

      /**
      * \brief Gives back the pointer of the node the hasStride edge points to.
      * \return Returns the end point of the hasStride edge.
      */
      expression::Expression* getStride() const;

      /**
      * \brief Gives back the pointer of the node the hasUpperBound edge points to.
      * \return Returns the end point of the hasUpperBound edge.
      */
      expression::Expression* getUpperBound() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasLowerBound edge.
      * \param id [in] The new end point of the hasLowerBound edge.
      */
      void setLowerBound(NodeId id);

      /**
      * \brief Sets the hasLowerBound edge.
      * \param node [in] The new end point of the hasLowerBound edge.
      */
      void setLowerBound(Expression *node);

      /**
      * \brief remove the hasLowerBound edge.
      */
      void removeLowerBound();

      /**
      * \brief Sets the hasStride edge.
      * \param id [in] The new end point of the hasStride edge.
      */
      void setStride(NodeId id);

      /**
      * \brief Sets the hasStride edge.
      * \param node [in] The new end point of the hasStride edge.
      */
      void setStride(Expression *node);

      /**
      * \brief remove the hasStride edge.
      */
      void removeStride();

      /**
      * \brief Sets the hasUpperBound edge.
      * \param id [in] The new end point of the hasUpperBound edge.
      */
      void setUpperBound(NodeId id);

      /**
      * \brief Sets the hasUpperBound edge.
      * \param node [in] The new end point of the hasUpperBound edge.
      */
      void setUpperBound(Expression *node);

      /**
      * \brief remove the hasUpperBound edge.
      */
      void removeUpperBound();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasLowerBound edge points to. */
      NodeId m_hasLowerBound;

      /** \internal \brief The id of the node the hasStride edge points to. */
      NodeId m_hasStride;

      /** \internal \brief The id of the node the hasUpperBound edge points to. */
      NodeId m_hasUpperBound;

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


      friend class python::asg::Factory;
      friend class python::asg::VisitorSave;
  };

} 


}}}
#endif

