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

#ifndef _JAVA_MethodDeclaration_H_
#define _JAVA_MethodDeclaration_H_

#include "java/inc/java.h"

/**
* \file MethodDeclaration.h
* \brief Contains declaration of the struc::MethodDeclaration class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
    * \brief struc::Member
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief MethodDeclaration class, which represents the struc::MethodDeclaration node.
  * (missing)
  * 
  * Attributes:
  *   - lloc (int) : (missing)
  *   - isAbstract (boolean) : (missing)
  *   - abstractPosition (Range) : (missing)
  *   - isStrictfp (boolean) : (missing)
  *   - strictfpPosition (Range) : (missing)
  *   - parametersStartPosition (Range) : (missing)
  *   - parametersEndPosition (Range) : (missing)
  * 
  * Edges:
  *   - hasReturnType (expr::TypeExpression, single) : (missing)
  *   - methodType (type::MethodType, single) : (missing)
  *   - overrides (struc::MethodDeclaration, multiple) : (missing)
  */
  class MethodDeclaration : public NamedDeclaration {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      MethodDeclaration(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~MethodDeclaration();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      MethodDeclaration & operator=(const MethodDeclaration&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      MethodDeclaration(const MethodDeclaration&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const MethodDeclaration& other, bool tryOnVirtualParent);

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
      * \brief Gives back the lloc of the node.
      * \return Returns with the lloc.
      */
      int getLloc() const;

      /**
      * \brief Gives back the isAbstract of the node.
      * \return Returns with the isAbstract.
      */
      bool getIsAbstract() const;

      /**
      * \brief Gives back the abstractPosition of the node.
      * \return Returns with the abstractPosition.
      */
      virtual const Range getAbstractPosition() const;

      /**
      * \brief Compare two node by abstractPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByAbstractPosition(const MethodDeclaration& other) const;

      /**
      * \brief Gives back the isStrictfp of the node.
      * \return Returns with the isStrictfp.
      */
      bool getIsStrictfp() const;

      /**
      * \brief Gives back the strictfpPosition of the node.
      * \return Returns with the strictfpPosition.
      */
      virtual const Range getStrictfpPosition() const;

      /**
      * \brief Compare two node by strictfpPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByStrictfpPosition(const MethodDeclaration& other) const;

      /**
      * \brief Gives back the parametersStartPosition of the node.
      * \return Returns with the parametersStartPosition.
      */
      virtual const Range getParametersStartPosition() const;

      /**
      * \brief Compare two node by parametersStartPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByParametersStartPosition(const MethodDeclaration& other) const;

      /**
      * \brief Gives back the parametersEndPosition of the node.
      * \return Returns with the parametersEndPosition.
      */
      virtual const Range getParametersEndPosition() const;

      /**
      * \brief Compare two node by parametersEndPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByParametersEndPosition(const MethodDeclaration& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the lloc of the node.
      * \param lloc [in] The new value of the lloc.
      */
      void setLloc(int _lloc);

      /**
      * \internal
      * \brief Sets the isAbstract of the node.
      * \param isAbstract [in] The new value of the isAbstract.
      */
      void setIsAbstract(bool _isAbstract);

      /**
      * \internal
      * \brief Sets the abstractPosition of the node.
      * \param abstractPosition [in] The new value of the abstractPosition.
      */
      virtual void setAbstractPosition(const Range& _abstractPosition);

      /**
      * \internal
      * \brief Sets the isStrictfp of the node.
      * \param isStrictfp [in] The new value of the isStrictfp.
      */
      void setIsStrictfp(bool _isStrictfp);

      /**
      * \internal
      * \brief Sets the strictfpPosition of the node.
      * \param strictfpPosition [in] The new value of the strictfpPosition.
      */
      virtual void setStrictfpPosition(const Range& _strictfpPosition);

      /**
      * \internal
      * \brief Sets the parametersStartPosition of the node.
      * \param parametersStartPosition [in] The new value of the parametersStartPosition.
      */
      virtual void setParametersStartPosition(const Range& _parametersStartPosition);

      /**
      * \internal
      * \brief Sets the parametersEndPosition of the node.
      * \param parametersEndPosition [in] The new value of the parametersEndPosition.
      */
      virtual void setParametersEndPosition(const Range& _parametersEndPosition);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Abstract` or not. */
      bool m_isAbstract : 1;

      /** \internal \brief Stores whether the node is `Strictfp` or not. */
      bool m_isStrictfp : 1;

      /** \internal \brief The value of the `lloc`. */
      int m_lloc;

      /** \internal \brief todo (unknown). */
      MultiRange m_abstractPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_strictfpPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_parametersStartPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_parametersEndPosition;

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
      * \brief Gives back the pointer of the node the hasReturnType edge points to.
      * \return Returns the end point of the hasReturnType edge.
      */
      expr::TypeExpression* getReturnType() const;

      /**
      * \brief Gives back the pointer of the node the methodType edge points to.
      * \return Returns the end point of the methodType edge.
      */
      type::MethodType* getMethodType() const;

      /**
      * \brief Gives back iterator for the overrides edges.
      * \return Returns an iterator for the overrides edges.
      */
      ListIterator<struc::MethodDeclaration> getOverridesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the overrides edges.
      * \return Returns an iterator for the overrides edges.
      */
      ListIterator<struc::MethodDeclaration> getOverridesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has overrides edges or not.
      * \return Returns true if the node doesn't have any overrides edge.
      */
      bool getOverridesIsEmpty() const;

      /**
      * \brief Gives back how many overrides edges the node has.
      * \return Returns with the number of overrides edges.
      */
      unsigned getOverridesSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasReturnType edge.
      * \param id [in] The new end point of the hasReturnType edge.
      */
      void setReturnType(NodeId id);

      /**
      * \brief Sets the hasReturnType edge.
      * \param node [in] The new end point of the hasReturnType edge.
      */
      void setReturnType(expr::TypeExpression *node);

      /**
      * \brief remove the hasReturnType edge.
      */
      void removeReturnType();

      /**
      * \brief Sets the methodType edge.
      * \param id [in] The new end point of the methodType edge.
      */
      void setMethodType(NodeId id);

      /**
      * \brief Sets the methodType edge.
      * \param node [in] The new end point of the methodType edge.
      */
      void setMethodType(type::MethodType *node);

      /**
      * \brief remove the methodType edge.
      */
      void removeMethodType();

      /**
      * \brief Adds a new overrides edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new overrides edge.
      */
      void addOverrides(const MethodDeclaration *node);

      /**
      * \brief Adds a new overrides edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new overrides edge.
      */
      void addOverrides(NodeId id);

      /**
      * \brief Remove the overrides edge by id from the node.
      * \param id [in] The end point of the overrides edge.
      */
      void removeOverrides(NodeId id);

      /**
      * \brief Remove the overrides edge from the node.
      * \param node [in] The end point of the overrides edge.
      */
      void removeOverrides(MethodDeclaration *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasReturnType edge points to. */
      NodeId m_hasReturnType;

      /** \internal \brief The id of the node the methodType edge points to. */
      NodeId m_methodType;

      /** \internal \brief Container stores the id of the nodes the overrides edge points to. */
      ListIterator<struc::MethodDeclaration>::Container overridesContainer;

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

