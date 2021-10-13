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

#ifndef _JAVA_ModuleDeclaration_H_
#define _JAVA_ModuleDeclaration_H_

#include "java/inc/java.h"

/**
* \file ModuleDeclaration.h
* \brief Contains declaration of the struc::ModuleDeclaration class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace struc {

  /**
  * \brief ModuleDeclaration class, which represents the struc::ModuleDeclaration node.
  * (missing)
  * 
  * Attributes:
  *   - moduleKind (ModuleKind) : (missing)
  * 
  * Edges:
  *   - hasName (expr::Expression, single) : (missing)
  *   - hasDirectives (module::ModuleDirective, multiple) : (missing)
  *   - moduleType (type::ModuleType, single) : (missing)
  *   - refersTo (struc::Module, single) : (missing)
  */
  class ModuleDeclaration : public base::Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ModuleDeclaration(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ModuleDeclaration();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      ModuleDeclaration & operator=(const ModuleDeclaration&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      ModuleDeclaration(const ModuleDeclaration&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const ModuleDeclaration& other, bool tryOnVirtualParent);

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
      * \brief Gives back the moduleKind of the node.
      * \return Returns with the moduleKind.
      */
      ModuleKind getModuleKind() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the moduleKind of the node.
      * \param moduleKind [in] The new value of the moduleKind.
      */
      void setModuleKind(ModuleKind _moduleKind);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The ModuleKind of the node. */
      ModuleKind m_moduleKind;

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
      * \brief Gives back the pointer of the node the hasName edge points to.
      * \return Returns the end point of the hasName edge.
      */
      expr::Expression* getName() const;

      /**
      * \brief Gives back iterator for the hasDirectives edges.
      * \return Returns an iterator for the hasDirectives edges.
      */
      ListIterator<module::ModuleDirective> getDirectivesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasDirectives edges.
      * \return Returns an iterator for the hasDirectives edges.
      */
      ListIterator<module::ModuleDirective> getDirectivesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasDirectives edges or not.
      * \return Returns true if the node doesn't have any hasDirectives edge.
      */
      bool getDirectivesIsEmpty() const;

      /**
      * \brief Gives back how many hasDirectives edges the node has.
      * \return Returns with the number of hasDirectives edges.
      */
      unsigned getDirectivesSize() const;

      /**
      * \brief Gives back the pointer of the node the moduleType edge points to.
      * \return Returns the end point of the moduleType edge.
      */
      type::ModuleType* getModuleType() const;

      /**
      * \brief Gives back the pointer of the node the refersTo edge points to.
      * \return Returns the end point of the refersTo edge.
      */
      struc::Module* getRefersTo() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasName edge.
      * \param id [in] The new end point of the hasName edge.
      */
      void setName(NodeId id);

      /**
      * \brief Sets the hasName edge.
      * \param node [in] The new end point of the hasName edge.
      */
      void setName(expr::Expression *node);

      /**
      * \brief remove the hasName edge.
      */
      void removeName();

      /**
      * \brief Adds a new hasDirectives edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasDirectives edge.
      */
      void addDirectives(const module::ModuleDirective *node);

      /**
      * \brief Adds a new hasDirectives edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasDirectives edge.
      */
      void addDirectives(NodeId id);

      /**
      * \brief Remove the hasDirectives edge by id from the node.
      * \param id [in] The end point of the hasDirectives edge.
      */
      void removeDirectives(NodeId id);

      /**
      * \brief Remove the hasDirectives edge from the node.
      * \param node [in] The end point of the hasDirectives edge.
      */
      void removeDirectives(module::ModuleDirective *node);

      /**
      * \brief Sets the moduleType edge.
      * \param id [in] The new end point of the moduleType edge.
      */
      void setModuleType(NodeId id);

      /**
      * \brief Sets the moduleType edge.
      * \param node [in] The new end point of the moduleType edge.
      */
      void setModuleType(type::ModuleType *node);

      /**
      * \brief remove the moduleType edge.
      */
      void removeModuleType();

      /**
      * \brief Sets the refersTo edge.
      * \param id [in] The new end point of the refersTo edge.
      */
      void setRefersTo(NodeId id);

      /**
      * \brief Sets the refersTo edge.
      * \param node [in] The new end point of the refersTo edge.
      */
      void setRefersTo(Module *node);

      /**
      * \brief remove the refersTo edge.
      */
      void removeRefersTo();

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasName edge points to. */
      NodeId m_hasName;

      /** \internal \brief Container stores the id of the nodes the hasDirectives edge points to. */
      ListIterator<module::ModuleDirective>::Container hasDirectivesContainer;

      /** \internal \brief The id of the node the moduleType edge points to. */
      NodeId m_moduleType;

      /** \internal \brief The id of the node the refersTo edge points to. */
      NodeId m_refersTo;

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

