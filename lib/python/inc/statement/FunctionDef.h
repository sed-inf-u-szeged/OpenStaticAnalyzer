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

#ifndef _PYTHON_FunctionDef_H_
#define _PYTHON_FunctionDef_H_

#include "python/inc/python.h"

/**
* \file FunctionDef.h
* \brief Contains declaration of the statement::FunctionDef class.
* \brief The it get atributes from 
*/

namespace columbus { namespace python { namespace asg {
namespace statement {

  /**
  * \brief FunctionDef class, which represents the statement::FunctionDef node.
  * (missing)
  * 
  * Attributes:
  *   - name (String) : (missing)
  *   - lloc (int) : (missing)
  *   - isAsync (boolean) : (missing)
  * 
  * Edges:
  *   - hasDecorator (expression::Expression, multiple) : (missing)
  *   - hasObject (module::Object, multiple) : (missing)
  *   - hasParameter (statement::Parameter, multiple) : (missing)
  *   - hasReturnAnnotation (expression::Expression, single) : (missing)
  *   - refersTo (module::Object, single) : (missing)
  *   - returnType (type::Type, single) : (missing)
  *   - docstring (base::Docstring, single) : (missing)
  */
  class FunctionDef : public CompoundStatement {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      FunctionDef(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~FunctionDef();

    private:
      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      FunctionDef & operator=(const FunctionDef&);

      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      FunctionDef(const FunctionDef&);

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

      /**
      * \brief Gives back the isAsync of the node.
      * \return Returns with the isAsync.
      */
      bool getIsAsync() const;


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
      * \brief Sets the isAsync of the node.
      * \param isAsync [in] The new value of the isAsync.
      */
      void setIsAsync(bool _isAsync);

      /**
      * \internal
      * \brief Sets the name of the node.
      * \param name [in] The new Key of the name.
      */
      void setNameKey(Key _name);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `Async` or not. */
      bool m_isAsync : 1;

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
      * \brief Gives back iterator for the hasParameter edges.
      * \return Returns an iterator for the hasParameter edges.
      */
      ListIterator<statement::Parameter> getParameterListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasParameter edges.
      * \return Returns an iterator for the hasParameter edges.
      */
      ListIterator<statement::Parameter> getParameterListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasParameter edges or not.
      * \return Returns true if the node doesn't have any hasParameter edge.
      */
      bool getParameterIsEmpty() const;

      /**
      * \brief Gives back how many hasParameter edges the node has.
      * \return Returns with the number of hasParameter edges.
      */
      unsigned getParameterSize() const;

      /**
      * \brief Gives back the pointer of the node the hasReturnAnnotation edge points to.
      * \return Returns the end point of the hasReturnAnnotation edge.
      */
      expression::Expression* getReturnAnnotation() const;

      /**
      * \brief Gives back the pointer of the node the refersTo edge points to.
      * \return Returns the end point of the refersTo edge.
      */
      module::Object* getRefersTo() const;

      /**
      * \brief Gives back the pointer of the node the returnType edge points to.
      * \return Returns the end point of the returnType edge.
      */
      type::Type* getReturnType() const;

      /**
      * \brief Gives back the pointer of the node the docstring edge points to.
      * \return Returns the end point of the docstring edge.
      */
      base::Docstring* getDocstring() const;


      // ---------- Edge setter function(s) ----------

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
      * \brief Adds a new hasParameter edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasParameter edge.
      */
      void addParameter(const Parameter *node);

      /**
      * \brief Adds a new hasParameter edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasParameter edge.
      */
      void addParameter(NodeId id);

      /**
      * \brief Remove the hasParameter edge by id from the node.
      * \param id [in] The end point of the hasParameter edge.
      */
      void removeParameter(NodeId id);

      /**
      * \brief Remove the hasParameter edge from the node.
      * \param node [in] The end point of the hasParameter edge.
      */
      void removeParameter(Parameter *node);

      /**
      * \brief Sets the hasReturnAnnotation edge.
      * \param id [in] The new end point of the hasReturnAnnotation edge.
      */
      void setReturnAnnotation(NodeId id);

      /**
      * \brief Sets the hasReturnAnnotation edge.
      * \param node [in] The new end point of the hasReturnAnnotation edge.
      */
      void setReturnAnnotation(expression::Expression *node);

      /**
      * \brief remove the hasReturnAnnotation edge.
      */
      void removeReturnAnnotation();

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
      * \brief Sets the returnType edge.
      * \param id [in] The new end point of the returnType edge.
      */
      void setReturnType(NodeId id);

      /**
      * \brief Sets the returnType edge.
      * \param node [in] The new end point of the returnType edge.
      */
      void setReturnType(type::Type *node);

      /**
      * \brief remove the returnType edge.
      */
      void removeReturnType();

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

      /** \internal \brief Container stores the id of the nodes the hasDecorator edge points to. */
      ListIterator<expression::Expression>::Container hasDecoratorContainer;

      /** \internal \brief Container stores the id of the nodes the hasObject edge points to. */
      ListIterator<module::Object>::Container hasObjectContainer;

      /** \internal \brief Container stores the id of the nodes the hasParameter edge points to. */
      ListIterator<statement::Parameter>::Container hasParameterContainer;

      /** \internal \brief The id of the node the hasReturnAnnotation edge points to. */
      NodeId m_hasReturnAnnotation;

      /** \internal \brief The id of the node the refersTo edge points to. */
      NodeId m_refersTo;

      /** \internal \brief The id of the node the returnType edge points to. */
      NodeId m_returnType;

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

