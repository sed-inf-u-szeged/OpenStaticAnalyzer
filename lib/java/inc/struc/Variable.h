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

#ifndef _JAVA_Variable_H_
#define _JAVA_Variable_H_

#include "java/inc/java.h"

/**
* \file Variable.h
* \brief Contains declaration of the struc::Variable class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
    * \brief struc::Member
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief Variable class, which represents the struc::Variable node.
  * (missing)
  * 
  * Attributes:
  *   - isTransient (boolean) : (missing)
  *   - transientPosition (Range) : (missing)
  *   - isVolatile (boolean) : (missing)
  *   - volatilePosition (Range) : (missing)
  *   - equalSignPosition (Range) : (missing)
  * 
  * Edges:
  *   - hasInitialValue (expr::Expression, single) : (missing)
  */
  class Variable : public VariableDeclaration {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Variable(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Variable();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Variable & operator=(const Variable&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Variable(const Variable&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Variable& other, bool tryOnVirtualParent);

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
      * \brief Gives back the isTransient of the node.
      * \return Returns with the isTransient.
      */
      bool getIsTransient() const;

      /**
      * \brief Gives back the transientPosition of the node.
      * \return Returns with the transientPosition.
      */
      virtual const Range getTransientPosition() const;

      /**
      * \brief Compare two node by transientPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByTransientPosition(const Variable& other) const;

      /**
      * \brief Gives back the isVolatile of the node.
      * \return Returns with the isVolatile.
      */
      bool getIsVolatile() const;

      /**
      * \brief Gives back the volatilePosition of the node.
      * \return Returns with the volatilePosition.
      */
      virtual const Range getVolatilePosition() const;

      /**
      * \brief Compare two node by volatilePosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByVolatilePosition(const Variable& other) const;

      /**
      * \brief Gives back the equalSignPosition of the node.
      * \return Returns with the equalSignPosition.
      */
      virtual const Range getEqualSignPosition() const;

      /**
      * \brief Compare two node by equalSignPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByEqualSignPosition(const Variable& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the isTransient of the node.
      * \param isTransient [in] The new value of the isTransient.
      */
      void setIsTransient(bool _isTransient);

      /**
      * \internal
      * \brief Sets the transientPosition of the node.
      * \param transientPosition [in] The new value of the transientPosition.
      */
      virtual void setTransientPosition(const Range& _transientPosition);

      /**
      * \internal
      * \brief Sets the isVolatile of the node.
      * \param isVolatile [in] The new value of the isVolatile.
      */
      void setIsVolatile(bool _isVolatile);

      /**
      * \internal
      * \brief Sets the volatilePosition of the node.
      * \param volatilePosition [in] The new value of the volatilePosition.
      */
      virtual void setVolatilePosition(const Range& _volatilePosition);

      /**
      * \internal
      * \brief Sets the equalSignPosition of the node.
      * \param equalSignPosition [in] The new value of the equalSignPosition.
      */
      virtual void setEqualSignPosition(const Range& _equalSignPosition);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Transient` or not. */
      bool m_isTransient : 1;

      /** \internal \brief Stores whether the node is `Volatile` or not. */
      bool m_isVolatile : 1;

      /** \internal \brief todo (unknown). */
      MultiRange m_transientPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_volatilePosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_equalSignPosition;

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
      * \brief Gives back the pointer of the node the hasInitialValue edge points to.
      * \return Returns the end point of the hasInitialValue edge.
      */
      expr::Expression* getInitialValue() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasInitialValue edge.
      * \param id [in] The new end point of the hasInitialValue edge.
      */
      void setInitialValue(NodeId id);

      /**
      * \brief Sets the hasInitialValue edge.
      * \param node [in] The new end point of the hasInitialValue edge.
      */
      void setInitialValue(expr::Expression *node);

      /**
      * \brief remove the hasInitialValue edge.
      */
      void removeInitialValue();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasInitialValue edge points to. */
      NodeId m_hasInitialValue;

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

