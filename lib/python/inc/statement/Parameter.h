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

#ifndef _PYTHON_Parameter_H_
#define _PYTHON_Parameter_H_

#include "python/inc/python.h"

/**
* \file Parameter.h
* \brief Contains declaration of the statement::Parameter class.
* \brief The it get atributes from 
*/

namespace columbus { namespace python { namespace asg {
namespace statement {

  /**
  * \brief Parameter class, which represents the statement::Parameter node.
  * (missing)
  * 
  * Attributes:
  *   - kind (ParameterKind) : (missing)
  * 
  * Edges:
  *   - hasDefaultValue (expression::Expression, single) : (missing)
  *   - hasAnnotation (expression::Expression, single) : (missing)
  *   - refersTo (module::Object, single) : (missing)
  */
  class Parameter : public base::Named {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Parameter(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Parameter();

    private:
      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      Parameter & operator=(const Parameter&);

      /**
      * \brief This function always throws a PythonException due to copying is not allowed!
      */
      Parameter(const Parameter&);

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
      * \brief Gives back the kind of the node.
      * \return Returns with the kind.
      */
      ParameterKind getKind() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the kind of the node.
      * \param kind [in] The new value of the kind.
      */
      void setKind(ParameterKind _kind);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The ParameterKind of the node. */
      ParameterKind m_kind;

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
      * \brief Gives back the pointer of the node the hasDefaultValue edge points to.
      * \return Returns the end point of the hasDefaultValue edge.
      */
      expression::Expression* getDefaultValue() const;

      /**
      * \brief Gives back the pointer of the node the hasAnnotation edge points to.
      * \return Returns the end point of the hasAnnotation edge.
      */
      expression::Expression* getAnnotation() const;

      /**
      * \brief Gives back the pointer of the node the refersTo edge points to.
      * \return Returns the end point of the refersTo edge.
      */
      module::Object* getRefersTo() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the hasDefaultValue edge.
      * \param id [in] The new end point of the hasDefaultValue edge.
      */
      void setDefaultValue(NodeId id);

      /**
      * \brief Sets the hasDefaultValue edge.
      * \param node [in] The new end point of the hasDefaultValue edge.
      */
      void setDefaultValue(expression::Expression *node);

      /**
      * \brief remove the hasDefaultValue edge.
      */
      void removeDefaultValue();

      /**
      * \brief Sets the hasAnnotation edge.
      * \param id [in] The new end point of the hasAnnotation edge.
      */
      void setAnnotation(NodeId id);

      /**
      * \brief Sets the hasAnnotation edge.
      * \param node [in] The new end point of the hasAnnotation edge.
      */
      void setAnnotation(expression::Expression *node);

      /**
      * \brief remove the hasAnnotation edge.
      */
      void removeAnnotation();

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

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the hasDefaultValue edge points to. */
      NodeId m_hasDefaultValue;

      /** \internal \brief The id of the node the hasAnnotation edge points to. */
      NodeId m_hasAnnotation;

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


      friend class python::asg::Factory;
      friend class python::asg::VisitorSave;
  };

} 


}}}
#endif

