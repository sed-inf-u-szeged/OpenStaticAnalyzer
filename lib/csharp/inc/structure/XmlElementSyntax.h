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

#ifndef _CSHARP_XmlElementSyntax_H_
#define _CSHARP_XmlElementSyntax_H_

#include "csharp/inc/csharp.h"

/**
* \file XmlElementSyntax.h
* \brief Contains declaration of the structure::XmlElementSyntax class.
* \brief The it get atributes from 
*/

namespace columbus { namespace csharp { namespace asg {
namespace structure {

  /**
  * \brief XmlElementSyntax class, which represents the structure::XmlElementSyntax node.
  * (missing)
  * 
  * Edges:
  *   - Content (structure::XmlNodeSyntax, multiple) : (missing)
  *   - EndTag (structure::XmlElementEndTagSyntax, single) : (missing)
  *   - StartTag (structure::XmlElementStartTagSyntax, single) : (missing)
  */
  class XmlElementSyntax : public XmlNodeSyntax {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      XmlElementSyntax(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~XmlElementSyntax();

    private:
      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      XmlElementSyntax & operator=(const XmlElementSyntax&);

      /**
      * \brief This function always throws a CsharpException due to copying is not allowed!
      */
      XmlElementSyntax(const XmlElementSyntax&);

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
      * \brief Gives back iterator for the Content edges.
      * \return Returns an iterator for the Content edges.
      */
      ListIterator<structure::XmlNodeSyntax> getContentListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the Content edges.
      * \return Returns an iterator for the Content edges.
      */
      ListIterator<structure::XmlNodeSyntax> getContentListIteratorEnd() const;

      /**
      * \brief Tells whether the node has Content edges or not.
      * \return Returns true if the node doesn't have any Content edge.
      */
      bool getContentIsEmpty() const;

      /**
      * \brief Gives back how many Content edges the node has.
      * \return Returns with the number of Content edges.
      */
      unsigned getContentSize() const;

      /**
      * \brief Gives back the pointer of the node the EndTag edge points to.
      * \return Returns the end point of the EndTag edge.
      */
      structure::XmlElementEndTagSyntax* getEndTag() const;

      /**
      * \brief Gives back the pointer of the node the StartTag edge points to.
      * \return Returns the end point of the StartTag edge.
      */
      structure::XmlElementStartTagSyntax* getStartTag() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new Content edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new Content edge.
      */
      void addContent(const XmlNodeSyntax *node);

      /**
      * \brief Adds a new Content edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new Content edge.
      */
      void addContent(NodeId id);

      /**
      * \brief Remove the Content edge by id from the node.
      * \param id [in] The end point of the Content edge.
      */
      void removeContent(NodeId id);

      /**
      * \brief Remove the Content edge from the node.
      * \param node [in] The end point of the Content edge.
      */
      void removeContent(XmlNodeSyntax *node);

      /**
      * \brief Sets the EndTag edge.
      * \param id [in] The new end point of the EndTag edge.
      */
      void setEndTag(NodeId id);

      /**
      * \brief Sets the EndTag edge.
      * \param node [in] The new end point of the EndTag edge.
      */
      void setEndTag(XmlElementEndTagSyntax *node);

      /**
      * \brief remove the EndTag edge.
      */
      void removeEndTag();

      /**
      * \brief Sets the StartTag edge.
      * \param id [in] The new end point of the StartTag edge.
      */
      void setStartTag(NodeId id);

      /**
      * \brief Sets the StartTag edge.
      * \param node [in] The new end point of the StartTag edge.
      */
      void setStartTag(XmlElementStartTagSyntax *node);

      /**
      * \brief remove the StartTag edge.
      */
      void removeStartTag();

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the Content edge points to. */
      ListIterator<structure::XmlNodeSyntax>::Container ContentContainer;

      /** \internal \brief The id of the node the EndTag edge points to. */
      NodeId m_EndTag;

      /** \internal \brief The id of the node the StartTag edge points to. */
      NodeId m_StartTag;

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


      friend class csharp::asg::Factory;
      friend class csharp::asg::VisitorSave;
  };

} 


}}}
#endif

