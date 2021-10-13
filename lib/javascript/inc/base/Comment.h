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

#ifndef _JAVASCRIPT_Comment_H_
#define _JAVASCRIPT_Comment_H_

#include "javascript/inc/javascript.h"

/**
* \file Comment.h
* \brief Contains declaration of the base::Comment class.
* \brief The it get atributes from 
*/

namespace columbus { namespace javascript { namespace asg {
namespace base {

  /**
  * \brief Comment class, which represents the base::Comment node.
  * (missing)
  * 
  * Attributes:
  *   - text (String) : (missing)
  *   - type (CommentType) : (missing)
  *   - location (CommentLocation) : (missing)
  */
  class Comment : public Positioned {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Comment(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Comment();

    private:
      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      Comment & operator=(const Comment&);

      /**
      * \brief This function always throws a JavascriptException due to copying is not allowed!
      */
      Comment(const Comment&);

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
      * \brief Gives back the text of the node.
      * \return Returns with the text.
      */
      const std::string& getText() const;

      /**
      * \brief Gives back the Key of text of the node.
      * \return Returns with the Key of the text.
      */
      Key getTextKey() const;

      /**
      * \brief Gives back the type of the node.
      * \return Returns with the type.
      */
      CommentType getType() const;

      /**
      * \brief Gives back the location of the node.
      * \return Returns with the location.
      */
      CommentLocation getLocation() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the text of the node.
      * \param text [in] The new value of the text.
      */
      void setText(const std::string& _text);

      /**
      * \internal
      * \brief Sets the type of the node.
      * \param type [in] The new value of the type.
      */
      void setType(CommentType _type);

      /**
      * \internal
      * \brief Sets the location of the node.
      * \param location [in] The new value of the location.
      */
      void setLocation(CommentLocation _location);

      /**
      * \internal
      * \brief Sets the text of the node.
      * \param text [in] The new Key of the text.
      */
      void setTextKey(Key _text);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The CommentType of the node. */
      CommentType m_type;

      /** \internal \brief The CommentLocation of the node. */
      CommentLocation m_location;

      /** \internal \brief The Key of the `text`. */
      Key m_text;

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


      friend class javascript::asg::Factory;
      friend class javascript::asg::VisitorSave;
  };

} 


}}}
#endif

