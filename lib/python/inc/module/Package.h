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

#ifndef _PYTHON_Package_H_
#define _PYTHON_Package_H_

#include "python/inc/python.h"

/**
* \file Package.h
* \brief Contains declaration of the module::Package class.
* \brief The it get atributes from 
*/

namespace columbus { namespace python { namespace asg {
namespace module {

  /**
  * \brief Package class, which represents the module::Package node.
  * (missing)
  * 
  * Attributes:
  *   - name (String) : (missing)
  *   - path (String) : (missing)
  * 
  * Edges:
  *   - hasModule (module::Module, multiple) : (missing)
  *   - hasPackage (module::Package, multiple) : (missing)
  */
  class Package : public base::Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Package(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Package();

    private:
      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      Package & operator=(const Package&);

      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      Package(const Package&);

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
      * \brief Gives back the name of the node.
      * \return Returns with the name.
      */
      const std::string& getName() const;

      /**
      * \brief Gives back the Key of name of the node.
      * \return Returns with the Key of the name.
      */
      Key getNameKey() const;

      /**
      * \brief Gives back the path of the node.
      * \return Returns with the path.
      */
      const std::string& getPath() const;

      /**
      * \brief Gives back the Key of path of the node.
      * \return Returns with the Key of the path.
      */
      Key getPathKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new value of the name.
      */
      void setName(const std::string& _name);

      /**
      * \internal
      * \brief Sets the path of the node.
      * \param path [in] The new value of the path.
      */
      void setPath(const std::string& _path);

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new Key of the name.
      */
      void setNameKey(Key _name);

      /**
      * \internal
      * \brief Sets the path of the node.
      * \param path [in] The new Key of the path.
      */
      void setPathKey(Key _path);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The Key of the `name`. */
      Key m_name;

      /** \internal \brief The Key of the `path`. */
      Key m_path;

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
      * \brief Gives back iterator for the hasModule edges.
      * \return Returns an iterator for the hasModule edges.
      */
      ListIterator<module::Module> getModuleListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasModule edges.
      * \return Returns an iterator for the hasModule edges.
      */
      ListIterator<module::Module> getModuleListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasModule edges or not.
      * \return Returns true if the node doesn't have any hasModule edge.
      */
      bool getModuleIsEmpty() const;

      /**
      * \brief Gives back how many hasModule edges the node has.
      * \return Returns with the number of hasModule edges.
      */
      unsigned getModuleSize() const;

      /**
      * \brief Gives back iterator for the hasPackage edges.
      * \return Returns an iterator for the hasPackage edges.
      */
      ListIterator<module::Package> getPackageListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasPackage edges.
      * \return Returns an iterator for the hasPackage edges.
      */
      ListIterator<module::Package> getPackageListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasPackage edges or not.
      * \return Returns true if the node doesn't have any hasPackage edge.
      */
      bool getPackageIsEmpty() const;

      /**
      * \brief Gives back how many hasPackage edges the node has.
      * \return Returns with the number of hasPackage edges.
      */
      unsigned getPackageSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasModule edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasModule edge.
      */
      void addModule(const Module *node);

      /**
      * \brief Adds a new hasModule edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasModule edge.
      */
      void addModule(NodeId id);

      /**
      * \brief Remove the hasModule edge by id from the node.
      * \param id [in] The end point of the hasModule edge.
      */
      void removeModule(NodeId id);

      /**
      * \brief Remove the hasModule edge from the node.
      * \param node [in] The end point of the hasModule edge.
      */
      void removeModule(Module *node);

      /**
      * \brief Adds a new hasPackage edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasPackage edge.
      */
      void addPackage(const Package *node);

      /**
      * \brief Adds a new hasPackage edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasPackage edge.
      */
      void addPackage(NodeId id);

      /**
      * \brief Remove the hasPackage edge by id from the node.
      * \param id [in] The end point of the hasPackage edge.
      */
      void removePackage(NodeId id);

      /**
      * \brief Remove the hasPackage edge from the node.
      * \param node [in] The end point of the hasPackage edge.
      */
      void removePackage(Package *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasModule edge points to. */
      ListIterator<module::Module>::Container hasModuleContainer;

      /** \internal \brief Container stores the id of the nodes the hasPackage edge points to. */
      ListIterator<module::Package>::Container hasPackageContainer;

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

