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

#ifndef _JAVA_CompilationUnit_H_
#define _JAVA_CompilationUnit_H_

#include "java/inc/java.h"

/**
* \file CompilationUnit.h
* \brief Contains declaration of the struc::CompilationUnit class.
* \brief The it get atributes from 
    * \brief base::Base
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief CompilationUnit class, which represents the struc::CompilationUnit node.
  * (missing)
  * 
  * Attributes:
  *   - fileEncoding (String) : (missing)
  * 
  * Edges:
  *   - hasPackageDeclaration (struc::PackageDeclaration, single) : (missing)
  *   - hasImports (struc::Import, multiple) : (missing)
  *   - typeDeclarations (struc::TypeDeclaration, multiple) : (missing)
  *   - hasOthers (base::Positioned, multiple) : (missing)
  */
  class CompilationUnit : public base::PositionedWithoutComment, public base::Commentable {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      CompilationUnit(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~CompilationUnit();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      CompilationUnit & operator=(const CompilationUnit&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      CompilationUnit(const CompilationUnit&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const CompilationUnit& other, bool tryOnVirtualParent);

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
      * \brief Gives back the fileEncoding of the node.
      * \return Returns with the fileEncoding.
      */
      const std::string& getFileEncoding() const;

      /**
      * \brief Gives back the Key of fileEncoding of the node.
      * \return Returns with the Key of the fileEncoding.
      */
      Key getFileEncodingKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the fileEncoding of the node.
      * \param fileEncoding [in] The new value of the fileEncoding.
      */
      void setFileEncoding(const std::string& _fileEncoding);

      /**
      * \internal
      * \brief Sets the fileEncoding of the node.
      * \param fileEncoding [in] The new Key of the fileEncoding.
      */
      void setFileEncodingKey(Key _fileEncoding);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `fileEncoding`. */
      Key m_fileEncoding;

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
      * \brief Gives back the pointer of the node the hasPackageDeclaration edge points to.
      * \return Returns the end point of the hasPackageDeclaration edge.
      */
      struc::PackageDeclaration* getPackageDeclaration() const;

      /**
      * \brief Gives back iterator for the hasImports edges.
      * \return Returns an iterator for the hasImports edges.
      */
      ListIterator<struc::Import> getImportsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasImports edges.
      * \return Returns an iterator for the hasImports edges.
      */
      ListIterator<struc::Import> getImportsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasImports edges or not.
      * \return Returns true if the node doesn't have any hasImports edge.
      */
      bool getImportsIsEmpty() const;

      /**
      * \brief Gives back how many hasImports edges the node has.
      * \return Returns with the number of hasImports edges.
      */
      unsigned getImportsSize() const;

      /**
      * \brief Gives back iterator for the typeDeclarations edges.
      * \return Returns an iterator for the typeDeclarations edges.
      */
      ListIterator<struc::TypeDeclaration> getTypeDeclarationsListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the typeDeclarations edges.
      * \return Returns an iterator for the typeDeclarations edges.
      */
      ListIterator<struc::TypeDeclaration> getTypeDeclarationsListIteratorEnd() const;

      /**
      * \brief Tells whether the node has typeDeclarations edges or not.
      * \return Returns true if the node doesn't have any typeDeclarations edge.
      */
      bool getTypeDeclarationsIsEmpty() const;

      /**
      * \brief Gives back how many typeDeclarations edges the node has.
      * \return Returns with the number of typeDeclarations edges.
      */
      unsigned getTypeDeclarationsSize() const;

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
      * \brief Sets the hasPackageDeclaration edge.
      * \param id [in] The new end point of the hasPackageDeclaration edge.
      */
      void setPackageDeclaration(NodeId id);

      /**
      * \brief Sets the hasPackageDeclaration edge.
      * \param node [in] The new end point of the hasPackageDeclaration edge.
      */
      void setPackageDeclaration(PackageDeclaration *node);

      /**
      * \brief remove the hasPackageDeclaration edge.
      */
      void removePackageDeclaration();

      /**
      * \brief Adds a new hasImports edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasImports edge.
      */
      void addImports(const Import *node);

      /**
      * \brief Adds a new hasImports edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasImports edge.
      */
      void addImports(NodeId id);

      /**
      * \brief Remove the hasImports edge by id from the node.
      * \param id [in] The end point of the hasImports edge.
      */
      void removeImports(NodeId id);

      /**
      * \brief Remove the hasImports edge from the node.
      * \param node [in] The end point of the hasImports edge.
      */
      void removeImports(Import *node);

      /**
      * \brief Adds a new typeDeclarations edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new typeDeclarations edge.
      */
      void addTypeDeclarations(const TypeDeclaration *node);

      /**
      * \brief Adds a new typeDeclarations edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new typeDeclarations edge.
      */
      void addTypeDeclarations(NodeId id);

      /**
      * \brief Remove the typeDeclarations edge by id from the node.
      * \param id [in] The end point of the typeDeclarations edge.
      */
      void removeTypeDeclarations(NodeId id);

      /**
      * \brief Remove the typeDeclarations edge from the node.
      * \param node [in] The end point of the typeDeclarations edge.
      */
      void removeTypeDeclarations(TypeDeclaration *node);

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

      /** \internal \brief The id of the node the hasPackageDeclaration edge points to. */
      NodeId m_hasPackageDeclaration;

      /** \internal \brief Container stores the id of the nodes the hasImports edge points to. */
      ListIterator<struc::Import>::Container hasImportsContainer;

      /** \internal \brief Container stores the id of the nodes the typeDeclarations edge points to. */
      ListIterator<struc::TypeDeclaration>::Container typeDeclarationsContainer;

      /** \internal \brief Container stores the id of the nodes the hasOthers edge points to. */
      ListIterator<base::Positioned>::Container hasOthersContainer;

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

