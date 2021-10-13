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

#ifndef _JAVA_Lambda_H_
#define _JAVA_Lambda_H_

#include "java/inc/java.h"

/**
* \file Lambda.h
* \brief Contains declaration of the expr::Lambda class.
* \brief The it get atributes from 
    * \brief base::Base
    * \brief base::Commentable
*/

namespace columbus { namespace java { namespace asg {
namespace expr {

  /**
  * \brief Lambda class, which represents the expr::Lambda node.
  * (missing)
  * 
  * Attributes:
  *   - lloc (int) : (missing)
  *   - paramKind (LambdaParameterKind) : (missing)
  *   - bodyKind (LambdaBodyKind) : (missing)
  * 
  * Edges:
  *   - hasParameters (struc::Parameter, multiple) : (missing)
  *   - hasBody (base::Positioned, single) : (missing)
  */
  class Lambda : public FunctionalExpression {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Lambda(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Lambda();

    private:
      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Lambda & operator=(const Lambda&);

      /**
      * \brief This function always throws a JavaException due to copying is not allowed!
      */
      Lambda(const Lambda&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Lambda& other, bool tryOnVirtualParent);

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

      /**
      * \brief Gives back the paramKind of the node.
      * \return Returns with the paramKind.
      */
      LambdaParameterKind getParamKind() const;

      /**
      * \brief Gives back the bodyKind of the node.
      * \return Returns with the bodyKind.
      */
      LambdaBodyKind getBodyKind() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the lloc of the node.
      * \param lloc [in] The new value of the lloc.
      */
      void setLloc(int _lloc);

      /**
      * \internal
      * \brief Sets the paramKind of the node.
      * \param paramKind [in] The new value of the paramKind.
      */
      void setParamKind(LambdaParameterKind _paramKind);

      /**
      * \internal
      * \brief Sets the bodyKind of the node.
      * \param bodyKind [in] The new value of the bodyKind.
      */
      void setBodyKind(LambdaBodyKind _bodyKind);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `lloc`. */
      int m_lloc;

      /** \internal \brief The LambdaParameterKind of the node. */
      LambdaParameterKind m_paramKind;

      /** \internal \brief The LambdaBodyKind of the node. */
      LambdaBodyKind m_bodyKind;

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
      * \brief Gives back iterator for the hasParameters edges.
      * \return Returns an iterator for the hasParameters edges.
      */
      ListIterator<struc::Parameter> getParametersListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasParameters edges.
      * \return Returns an iterator for the hasParameters edges.
      */
      ListIterator<struc::Parameter> getParametersListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasParameters edges or not.
      * \return Returns true if the node doesn't have any hasParameters edge.
      */
      bool getParametersIsEmpty() const;

      /**
      * \brief Gives back how many hasParameters edges the node has.
      * \return Returns with the number of hasParameters edges.
      */
      unsigned getParametersSize() const;

      /**
      * \brief Gives back the pointer of the node the hasBody edge points to.
      * \return Returns the end point of the hasBody edge.
      */
      base::Positioned* getBody() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasParameters edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasParameters edge.
      */
      void addParameters(const struc::Parameter *node);

      /**
      * \brief Adds a new hasParameters edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasParameters edge.
      */
      void addParameters(NodeId id);

      /**
      * \brief Remove the hasParameters edge by id from the node.
      * \param id [in] The end point of the hasParameters edge.
      */
      void removeParameters(NodeId id);

      /**
      * \brief Remove the hasParameters edge from the node.
      * \param node [in] The end point of the hasParameters edge.
      */
      void removeParameters(struc::Parameter *node);

      /**
      * \brief Sets the hasBody edge.
      * \param id [in] The new end point of the hasBody edge.
      */
      void setBody(NodeId id);

      /**
      * \brief Sets the hasBody edge.
      * \param node [in] The new end point of the hasBody edge.
      */
      void setBody(base::Positioned *node);

      /**
      * \brief remove the hasBody edge.
      */
      void removeBody();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasParameters edge points to. */
      ListIterator<struc::Parameter>::Container hasParametersContainer;

      /** \internal \brief The id of the node the hasBody edge points to. */
      NodeId m_hasBody;

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

