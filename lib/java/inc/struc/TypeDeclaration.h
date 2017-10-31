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

#ifndef _JAVA_TypeDeclaration_H_
#define _JAVA_TypeDeclaration_H_

#include "java/inc/java.h"

/**
* \file TypeDeclaration.h
* \brief Contains declaration of the struc::TypeDeclaration class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
    * \brief struc::Member
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief TypeDeclaration class, which represents the struc::TypeDeclaration node.
  * (missing)
  * 
  * Attributes:
  *   - typeNamePosition (Range) : (missing)
  *   - isAbstract (boolean) : (missing)
  *   - abstractPosition (Range) : (missing)
  *   - isStrictfp (boolean) : (missing)
  *   - strictfpPosition (Range) : (missing)
  *   - binaryName (String) : (missing)
  *   - extendsPosition (Range) : (missing)
  *   - implementsPosition (Range) : (missing)
  *   - bodyStartPosition (Range) : (missing)
  * 
  * Edges:
  *   - isInCompilationUnit (struc::CompilationUnit, single) : (missing)
  *   - hasSuperClass (expr::TypeExpression, single) : (missing)
  *   - hasSuperInterfaces (expr::TypeExpression, multiple) : (missing)
  *   - hasOthers (base::Positioned, multiple) : (missing)
  */
  class TypeDeclaration : public NamedDeclaration, public Scope {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      TypeDeclaration(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~TypeDeclaration();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      TypeDeclaration & operator=(const TypeDeclaration&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      TypeDeclaration(const TypeDeclaration&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const TypeDeclaration& other, bool tryOnVirtualParent);

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
      * \brief Gives back the typeNamePosition of the node.
      * \return Returns with the typeNamePosition.
      */
      virtual const Range getTypeNamePosition() const;

      /**
      * \brief Compare two node by typeNamePosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByTypeNamePosition(const TypeDeclaration& other) const;

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
      virtual int compareByAbstractPosition(const TypeDeclaration& other) const;

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
      virtual int compareByStrictfpPosition(const TypeDeclaration& other) const;

      /**
      * \brief Gives back the binaryName of the node.
      * \return Returns with the binaryName.
      */
      const std::string& getBinaryName() const;

      /**
      * \brief Gives back the Key of binaryName of the node.
      * \return Returns with the Key of the binaryName.
      */
      Key getBinaryNameKey() const;

      /**
      * \brief Gives back the extendsPosition of the node.
      * \return Returns with the extendsPosition.
      */
      virtual const Range getExtendsPosition() const;

      /**
      * \brief Compare two node by extendsPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByExtendsPosition(const TypeDeclaration& other) const;

      /**
      * \brief Gives back the implementsPosition of the node.
      * \return Returns with the implementsPosition.
      */
      virtual const Range getImplementsPosition() const;

      /**
      * \brief Compare two node by implementsPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByImplementsPosition(const TypeDeclaration& other) const;

      /**
      * \brief Gives back the bodyStartPosition of the node.
      * \return Returns with the bodyStartPosition.
      */
      virtual const Range getBodyStartPosition() const;

      /**
      * \brief Compare two node by bodyStartPosition attribute of the node.
      * \return Returns with the result.
      */
      virtual int compareByBodyStartPosition(const TypeDeclaration& other) const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the typeNamePosition of the node.
      * \param typeNamePosition [in] The new value of the typeNamePosition.
      */
      virtual void setTypeNamePosition(const Range& _typeNamePosition);

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
      * \brief Sets the binaryName of the node.
      * \param binaryName [in] The new value of the binaryName.
      */
      void setBinaryName(const std::string& _binaryName);

      /**
      * \internal
      * \brief Sets the extendsPosition of the node.
      * \param extendsPosition [in] The new value of the extendsPosition.
      */
      virtual void setExtendsPosition(const Range& _extendsPosition);

      /**
      * \internal
      * \brief Sets the implementsPosition of the node.
      * \param implementsPosition [in] The new value of the implementsPosition.
      */
      virtual void setImplementsPosition(const Range& _implementsPosition);

      /**
      * \internal
      * \brief Sets the bodyStartPosition of the node.
      * \param bodyStartPosition [in] The new value of the bodyStartPosition.
      */
      virtual void setBodyStartPosition(const Range& _bodyStartPosition);

      /**
      * \internal
      * \brief Sets the binaryName of the node.
      * \param binaryName [in] The new Key of the binaryName.
      */
      void setBinaryNameKey(Key _binaryName);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Abstract` or not. */
      bool m_isAbstract : 1;

      /** \internal \brief Stores whether the node is `Strictfp` or not. */
      bool m_isStrictfp : 1;

      /** \internal \brief todo (unknown). */
      MultiRange m_typeNamePosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_abstractPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_strictfpPosition;

      /** \internal \brief The Key of the `binaryName`. */
      Key m_binaryName;

      /** \internal \brief todo (unknown). */
      MultiRange m_extendsPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_implementsPosition;

      /** \internal \brief todo (unknown). */
      MultiRange m_bodyStartPosition;

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
      * \brief Gives back the pointer of the node the isInCompilationUnit edge points to.
      * \return Returns the end point of the isInCompilationUnit edge.
      */
      struc::CompilationUnit* getIsInCompilationUnit() const;

      /**
      * \brief Gives back the pointer of the node the hasSuperClass edge points to.
      * \return Returns the end point of the hasSuperClass edge.
      */
      expr::TypeExpression* getSuperClass() const;

      /**
      * \brief Gives back iterator for the hasSuperInterfaces edges.
      * \return Returns an iterator for the hasSuperInterfaces edges.
      */
      ListIterator<expr::TypeExpression> getSuperInterfacesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasSuperInterfaces edges.
      * \return Returns an iterator for the hasSuperInterfaces edges.
      */
      ListIterator<expr::TypeExpression> getSuperInterfacesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasSuperInterfaces edges or not.
      * \return Returns true if the node doesn't have any hasSuperInterfaces edge.
      */
      bool getSuperInterfacesIsEmpty() const;

      /**
      * \brief Gives back how many hasSuperInterfaces edges the node has.
      * \return Returns with the number of hasSuperInterfaces edges.
      */
      unsigned getSuperInterfacesSize() const;

      /**
      * \brief Gives back iterator for the hasOthers edges.
      * \return Returns an iterator for the hasOthers edges.
      */
      ListIterator<base::Positioned> getOthersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasOthers edges.
      * \return Returns an iterator for the hasOthers edges.
      */
      ListIterator<base::Positioned> getOthersListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasOthers edges or not.
      * \return Returns true if the node doesn't have any hasOthers edge.
      */
      bool getOthersIsEmpty() const;

      /**
      * \brief Gives back how many hasOthers edges the node has.
      * \return Returns with the number of hasOthers edges.
      */
      unsigned getOthersSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the isInCompilationUnit edge.
      * \param id [in] The new end point of the isInCompilationUnit edge.
      */
      void setIsInCompilationUnit(NodeId id);

      /**
      * \brief Sets the isInCompilationUnit edge.
      * \param node [in] The new end point of the isInCompilationUnit edge.
      */
      void setIsInCompilationUnit(CompilationUnit *node);

      /**
      * \brief remove the isInCompilationUnit edge.
      */
      void removeIsInCompilationUnit();

      /**
      * \brief Sets the hasSuperClass edge.
      * \param id [in] The new end point of the hasSuperClass edge.
      */
      void setSuperClass(NodeId id);

      /**
      * \brief Sets the hasSuperClass edge.
      * \param node [in] The new end point of the hasSuperClass edge.
      */
      void setSuperClass(expr::TypeExpression *node);

      /**
      * \brief remove the hasSuperClass edge.
      */
      void removeSuperClass();

      /**
      * \brief Adds a new hasSuperInterfaces edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasSuperInterfaces edge.
      */
      void addSuperInterfaces(const expr::TypeExpression *node);

      /**
      * \brief Adds a new hasSuperInterfaces edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasSuperInterfaces edge.
      */
      void addSuperInterfaces(NodeId id);

      /**
      * \brief Remove the hasSuperInterfaces edge by id from the node.
      * \param id [in] The end point of the hasSuperInterfaces edge.
      */
      void removeSuperInterfaces(NodeId id);

      /**
      * \brief Remove the hasSuperInterfaces edge from the node.
      * \param node [in] The end point of the hasSuperInterfaces edge.
      */
      void removeSuperInterfaces(expr::TypeExpression *node);

      /**
      * \brief Adds a new hasOthers edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasOthers edge.
      */
      void addOthers(const base::Positioned *node);

      /**
      * \brief Adds a new hasOthers edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasOthers edge.
      */
      void addOthers(NodeId id);

      /**
      * \brief Remove the hasOthers edge by id from the node.
      * \param id [in] The end point of the hasOthers edge.
      */
      void removeOthers(NodeId id);

      /**
      * \brief Remove the hasOthers edge from the node.
      * \param node [in] The end point of the hasOthers edge.
      */
      void removeOthers(base::Positioned *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the isInCompilationUnit edge points to. */
      NodeId m_isInCompilationUnit;

      /** \internal \brief The id of the node the hasSuperClass edge points to. */
      NodeId m_hasSuperClass;

      /** \internal \brief Container stores the id of the nodes the hasSuperInterfaces edge points to. */
      ListIterator<expr::TypeExpression>::Container hasSuperInterfacesContainer;

      /** \internal \brief Container stores the id of the nodes the hasOthers edge points to. */
      ListIterator<base::Positioned>::Container hasOthersContainer;

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

