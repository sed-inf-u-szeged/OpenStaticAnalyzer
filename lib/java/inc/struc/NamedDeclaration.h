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

#ifndef _JAVA_NamedDeclaration_H_
#define _JAVA_NamedDeclaration_H_

#include "java/inc/java.h"

/**
* \file NamedDeclaration.h
* \brief Contains declaration of the struc::NamedDeclaration class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
    * \brief struc::Member
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief NamedDeclaration class, which represents the struc::NamedDeclaration node.
  * (missing)
  * 
  * Attributes:
  *   - accessibility (AccessibilityKind) : (missing)
  *   - accessibilityPosition (Range) : (missing)
  *   - isStatic (boolean) : (missing)
  *   - staticPosition (Range) : (missing)
  *   - isFinal (boolean) : (missing)
  *   - finalPosition (Range) : (missing)
  */
  class NamedDeclaration : public Declaration, public base::Named {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      NamedDeclaration(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~NamedDeclaration();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      NamedDeclaration & operator=(const NamedDeclaration&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      NamedDeclaration(const NamedDeclaration&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const NamedDeclaration& other, bool tryOnVirtualParent);

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


      // ---------- Attribute getter function(s) ----------

      /**
      * \brief Gives back the accessibility of the node.
      * \return Returns with the accessibility.
      */
      AccessibilityKind getAccessibility() const;

      /**
      * \brief Gives back the accessibilityPosition of the node.
      * \return Returns with the accessibilityPosition.
      */
      virtual const Range getAccessibilityPosition() const;

      /**
      * \brief Compare two node by accessibilityPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByAccessibilityPosition(const NamedDeclaration& other) const;

      /**
      * \brief Gives back the isStatic of the node.
      * \return Returns with the isStatic.
      */
      bool getIsStatic() const;

      /**
      * \brief Gives back the staticPosition of the node.
      * \return Returns with the staticPosition.
      */
      virtual const Range getStaticPosition() const;

      /**
      * \brief Compare two node by staticPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByStaticPosition(const NamedDeclaration& other) const;

      /**
      * \brief Gives back the isFinal of the node.
      * \return Returns with the isFinal.
      */
      bool getIsFinal() const;

      /**
      * \brief Gives back the finalPosition of the node.
      * \return Returns with the finalPosition.
      */
      virtual const Range getFinalPosition() const;

      /**
      * \brief Compare two node by finalPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByFinalPosition(const NamedDeclaration& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the accessibility of the node.
      * \param accessibility [in] The new value of the accessibility.
      */
      void setAccessibility(AccessibilityKind _accessibility);

      /**
      * \internal
      * \brief Sets the accessibilityPosition of the node.
      * \param accessibilityPosition [in] The new value of the accessibilityPosition.
      */
      virtual void setAccessibilityPosition(const Range& _accessibilityPosition);

      /**
      * \internal
      * \brief Sets the isStatic of the node.
      * \param isStatic [in] The new value of the isStatic.
      */
      void setIsStatic(bool _isStatic);

      /**
      * \internal
      * \brief Sets the staticPosition of the node.
      * \param staticPosition [in] The new value of the staticPosition.
      */
      virtual void setStaticPosition(const Range& _staticPosition);

      /**
      * \internal
      * \brief Sets the isFinal of the node.
      * \param isFinal [in] The new value of the isFinal.
      */
      void setIsFinal(bool _isFinal);

      /**
      * \internal
      * \brief Sets the finalPosition of the node.
      * \param finalPosition [in] The new value of the finalPosition.
      */
      virtual void setFinalPosition(const Range& _finalPosition);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Static` or not. */
      bool m_isStatic : 1;

      /** \internal \brief Stores whether the node is `Final` or not. */
      bool m_isFinal : 1;

      /** \internal \brief The AccessibilityKind of the node. */
      AccessibilityKind m_accessibility;

      /** \internal \brief todo (unknown). */
      MultiRange m_accessibilityPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_staticPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_finalPosition;

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

