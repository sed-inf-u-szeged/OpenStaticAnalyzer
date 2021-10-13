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

#ifndef _PYTHON_ClassDef_H_
#define _PYTHON_ClassDef_H_

#include "python/inc/python.h"

/**
* \file ClassDef.h
* \brief Contains declaration of the statement::ClassDef class.
* \brief The it get atributes from 
*/

namespace columbus { namespace python { namespace asg {
namespace statement {

  /**
  * \brief ClassDef class, which represents the statement::ClassDef node.
  * (missing)
  * 
  * Attributes:
  *   - name (String) : (missing)
  *   - lloc (int) : (missing)
  * 
  * Edges:
  *   - hasObject (module::Object, multiple) : (missing)
  *   - hasBaseSpecifier (statement::BaseSpecifier, multiple) : (missing)
  *   - hasKeyword (expression::Keyword, multiple) : (missing)
  *   - hasDecorator (expression::Expression, multiple) : (missing)
  *   - refersTo (module::Object, single) : (missing)
  *   - docstring (base::Docstring, single) : (missing)
  */
  class ClassDef : public CompoundStatement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      ClassDef(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~ClassDef();

    private:
      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      ClassDef & operator=(const ClassDef&);

      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      ClassDef(const ClassDef&);

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
      * \brief Gives back the lloc of the node.
      * \return Returns with the lloc.
      */
      int getLloc() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new value of the name.
      */
      void setName(const std::string& _name);

      /**
      * \internal
      * \brief Sets the lloc of the node.
      * \param lloc [in] The new value of the lloc.
      */
      void setLloc(int _lloc);

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new Key of the name.
      */
      void setNameKey(Key _name);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `lloc`. */
      int m_lloc;

      /** \internal \brief The Key of the `name`. */
      Key m_name;

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
      * \brief Gives back iterator for the hasBaseSpecifier edges.
      * \return Returns an iterator for the hasBaseSpecifier edges.
      */
      ListIterator<statement::BaseSpecifier> getBaseSpecifierListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasBaseSpecifier edges.
      * \return Returns an iterator for the hasBaseSpecifier edges.
      */
      ListIterator<statement::BaseSpecifier> getBaseSpecifierListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasBaseSpecifier edges or not.
      * \return Returns true if the node doesn't have any hasBaseSpecifier edge.
      */
      bool getBaseSpecifierIsEmpty() const;

      /**
      * \brief Gives back how many hasBaseSpecifier edges the node has.
      * \return Returns with the number of hasBaseSpecifier edges.
      */
      unsigned getBaseSpecifierSize() const;

      /**
      * \brief Gives back iterator for the hasKeyword edges.
      * \return Returns an iterator for the hasKeyword edges.
      */
      ListIterator<expression::Keyword> getKeywordListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasKeyword edges.
      * \return Returns an iterator for the hasKeyword edges.
      */
      ListIterator<expression::Keyword> getKeywordListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasKeyword edges or not.
      * \return Returns true if the node doesn't have any hasKeyword edge.
      */
      bool getKeywordIsEmpty() const;

      /**
      * \brief Gives back how many hasKeyword edges the node has.
      * \return Returns with the number of hasKeyword edges.
      */
      unsigned getKeywordSize() const;

      /**
      * \brief Gives back iterator for the hasDecorator edges.
      * \return Returns an iterator for the hasDecorator edges.
      */
      ListIterator<expression::Expression> getDecoratorListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasDecorator edges.
      * \return Returns an iterator for the hasDecorator edges.
      */
      ListIterator<expression::Expression> getDecoratorListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasDecorator edges or not.
      * \return Returns true if the node doesn't have any hasDecorator edge.
      */
      bool getDecoratorIsEmpty() const;

      /**
      * \brief Gives back how many hasDecorator edges the node has.
      * \return Returns with the number of hasDecorator edges.
      */
      unsigned getDecoratorSize() const;

      /**
      * \brief Gives back the pointer of the node the refersTo edge points to.
      * \return Returns the end point of the refersTo edge.
      */
      module::Object* getRefersTo() const;

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
      void addObject(const module::Object *node);

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
      void removeObject(module::Object *node);

      /**
      * \brief Adds a new hasBaseSpecifier edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasBaseSpecifier edge.
      */
      void addBaseSpecifier(const BaseSpecifier *node);

      /**
      * \brief Adds a new hasBaseSpecifier edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasBaseSpecifier edge.
      */
      void addBaseSpecifier(NodeId id);

      /**
      * \brief Remove the hasBaseSpecifier edge by id from the node.
      * \param id [in] The end point of the hasBaseSpecifier edge.
      */
      void removeBaseSpecifier(NodeId id);

      /**
      * \brief Remove the hasBaseSpecifier edge from the node.
      * \param node [in] The end point of the hasBaseSpecifier edge.
      */
      void removeBaseSpecifier(BaseSpecifier *node);

      /**
      * \brief Adds a new hasKeyword edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasKeyword edge.
      */
      void addKeyword(const expression::Keyword *node);

      /**
      * \brief Adds a new hasKeyword edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasKeyword edge.
      */
      void addKeyword(NodeId id);

      /**
      * \brief Remove the hasKeyword edge by id from the node.
      * \param id [in] The end point of the hasKeyword edge.
      */
      void removeKeyword(NodeId id);

      /**
      * \brief Remove the hasKeyword edge from the node.
      * \param node [in] The end point of the hasKeyword edge.
      */
      void removeKeyword(expression::Keyword *node);

      /**
      * \brief Adds a new hasDecorator edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasDecorator edge.
      */
      void addDecorator(const expression::Expression *node);

      /**
      * \brief Adds a new hasDecorator edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasDecorator edge.
      */
      void addDecorator(NodeId id);

      /**
      * \brief Remove the hasDecorator edge by id from the node.
      * \param id [in] The end point of the hasDecorator edge.
      */
      void removeDecorator(NodeId id);

      /**
      * \brief Remove the hasDecorator edge from the node.
      * \param node [in] The end point of the hasDecorator edge.
      */
      void removeDecorator(expression::Expression *node);

      /**
      * \brief Sets the refersTo edge.
      * \param id [in] The new end point of the refersTo edge.
      */
      void setRefersTo(NodeId id);

      /**
      * \brief Sets the refersTo edge.
      * \param node [in] The new end point of the refersTo edge.
      */
      void setRefersTo(module::Object *node);

      /**
      * \brief remove the refersTo edge.
      */
      void removeRefersTo();

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

      /** \internal \brief Container stores the id of the nodes the hasBaseSpecifier edge points to. */
      ListIterator<statement::BaseSpecifier>::Container hasBaseSpecifierContainer;

      /** \internal \brief Container stores the id of the nodes the hasKeyword edge points to. */
      ListIterator<expression::Keyword>::Container hasKeywordContainer;

      /** \internal \brief Container stores the id of the nodes the hasDecorator edge points to. */
      ListIterator<expression::Expression>::Container hasDecoratorContainer;

      /** \internal \brief The id of the node the refersTo edge points to. */
      NodeId m_refersTo;

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

