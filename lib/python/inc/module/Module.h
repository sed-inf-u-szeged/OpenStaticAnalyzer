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

#ifndef _PYTHON_Module_H_
#define _PYTHON_Module_H_

#include "python/inc/python.h"

/**
* \file Module.h
* \brief Contains declaration of the module::Module class.
* \brief The it get atributes from 
*/

namespace columbus { namespace python { namespace asg {
namespace module {

  /**
  * \brief Module class, which represents the module::Module node.
  * (missing)
  * 
  * Attributes:
  *   - lloc (int) : (missing)
  * 
  * Edges:
  *   - hasObject (module::Object, multiple) : (missing)
  *   - hasStatement (base::Positioned, multiple) : (missing)
  *   - docstring (base::Docstring, single) : (missing)
  */
  class Module : public base::Named {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Module(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Module();

    private:
      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      Module & operator=(const Module&);

      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      Module(const Module&);

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
      * \brief Gives back the lloc of the node.
      * \return Returns with the lloc.
      */
      int getLloc() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the lloc of the node.
      * \param lloc [in] The new value of the lloc.
      */
      void setLloc(int _lloc);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `lloc`. */
      int m_lloc;

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
      * \brief Gives back iterator for the hasObject edges.
      * \return Returns an iterator for the hasObject edges.
      */
      ListIterator<module::Object> getObjectListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasObject edges.
      * \return Returns an iterator for the hasObject edges.
      */
      ListIterator<module::Object> getObjectListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasObject edges or not.
      * \return Returns true if the node doesn't have any hasObject edge.
      */
      bool getObjectIsEmpty() const;

      /**
      * \brief Gives back how many hasObject edges the node has.
      * \return Returns with the number of hasObject edges.
      */
      unsigned getObjectSize() const;

      /**
      * \brief Gives back iterator for the hasStatement edges.
      * \return Returns an iterator for the hasStatement edges.
      */
      ListIterator<base::Positioned> getStatementListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasStatement edges.
      * \return Returns an iterator for the hasStatement edges.
      */
      ListIterator<base::Positioned> getStatementListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasStatement edges or not.
      * \return Returns true if the node doesn't have any hasStatement edge.
      */
      bool getStatementIsEmpty() const;

      /**
      * \brief Gives back how many hasStatement edges the node has.
      * \return Returns with the number of hasStatement edges.
      */
      unsigned getStatementSize() const;

      /**
      * \brief Gives back the pointer of the node the docstring edge points to.
      * \return Returns the end point of the docstring edge.
      */
      base::Docstring* getDocstring() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasObject edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasObject edge.
      */
      void addObject(const Object *node);

      /**
      * \brief Adds a new hasObject edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasObject edge.
      */
      void addObject(NodeId id);

      /**
      * \brief Remove the hasObject edge by id from the node.
      * \param id [in] The end point of the hasObject edge.
      */
      void removeObject(NodeId id);

      /**
      * \brief Remove the hasObject edge from the node.
      * \param node [in] The end point of the hasObject edge.
      */
      void removeObject(Object *node);

      /**
      * \brief Adds a new hasStatement edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasStatement edge.
      */
      void addStatement(const base::Positioned *node);

      /**
      * \brief Adds a new hasStatement edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasStatement edge.
      */
      void addStatement(NodeId id);

      /**
      * \brief Remove the hasStatement edge by id from the node.
      * \param id [in] The end point of the hasStatement edge.
      */
      void removeStatement(NodeId id);

      /**
      * \brief Remove the hasStatement edge from the node.
      * \param node [in] The end point of the hasStatement edge.
      */
      void removeStatement(base::Positioned *node);

      /**
      * \brief Sets the docstring edge.
      * \param id [in] The new end point of the docstring edge.
      */
      void setDocstring(NodeId id);

      /**
      * \brief Sets the docstring edge.
      * \param node [in] The new end point of the docstring edge.
      */
      void setDocstring(base::Docstring *node);

      /**
      * \brief remove the docstring edge.
      */
      void removeDocstring();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasObject edge points to. */
      ListIterator<module::Object>::Container hasObjectContainer;

      /** \internal \brief Container stores the id of the nodes the hasStatement edge points to. */
      ListIterator<base::Positioned>::Container hasStatementContainer;

      /** \internal \brief The id of the node the docstring edge points to. */
      NodeId m_docstring;

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

