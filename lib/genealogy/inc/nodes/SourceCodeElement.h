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

#ifndef _GENEALOGY_SourceCodeElement_H_
#define _GENEALOGY_SourceCodeElement_H_

#include "genealogy/inc/genealogy.h"

/**
* \file SourceCodeElement.h
* \brief Contains declaration of the SourceCodeElement class.
* \brief The it get atributes from 
*/

namespace columbus { namespace genealogy { 
  /**
  * \brief SourceCodeElement class, which represents the SourceCodeElement node.
  * (missing)
  * 
  * Attributes:
  *   - path (String) : (missing)
  *   - line (int) : (missing)
  *   - col (int) : (missing)
  *   - endLine (int) : (missing)
  *   - endCol (int) : (missing)
  */
  class SourceCodeElement : public Base {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      SourceCodeElement(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~SourceCodeElement();

    private:
      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      SourceCodeElement & operator=(const SourceCodeElement&);

      /**
      * \brief This function always throws a GenealogyException due to copying is not allowed!
      */
      SourceCodeElement(const SourceCodeElement&);

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
      * \brief Gives back the path of the node.
      * \return Returns with the path.
      */
      const std::string& getPath() const;

      /**
      * \brief Gives back the Key of path of the node.
      * \return Returns with the Key of the path.
      */
      Key getPathKey() const;

      /**
      * \brief Gives back the line of the node.
      * \return Returns with the line.
      */
      unsigned getLine() const;

      /**
      * \brief Gives back the col of the node.
      * \return Returns with the col.
      */
      unsigned getCol() const;

      /**
      * \brief Gives back the endLine of the node.
      * \return Returns with the endLine.
      */
      unsigned getEndLine() const;

      /**
      * \brief Gives back the endCol of the node.
      * \return Returns with the endCol.
      */
      unsigned getEndCol() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the path of the node.
      * \param path [in] The new value of the path.
      */
      void setPath(const std::string& _path);

      /**
      * \internal
      * \brief Sets the line of the node.
      * \param line [in] The new value of the line.
      */
      void setLine(unsigned _line);

      /**
      * \internal
      * \brief Sets the col of the node.
      * \param col [in] The new value of the col.
      */
      void setCol(unsigned _col);

      /**
      * \internal
      * \brief Sets the endLine of the node.
      * \param endLine [in] The new value of the endLine.
      */
      void setEndLine(unsigned _endLine);

      /**
      * \internal
      * \brief Sets the endCol of the node.
      * \param endCol [in] The new value of the endCol.
      */
      void setEndCol(unsigned _endCol);

      /**
      * \internal
      * \brief Sets the path of the node.
      * \param path [in] The new Key of the path.
      */
      void setPathKey(Key _path);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `line`. */
      unsigned m_line;

      /** \internal \brief The value of the `col`. */
      unsigned m_col;

      /** \internal \brief The value of the `endLine`. */
      unsigned m_endLine;

      /** \internal \brief The value of the `endCol`. */
      unsigned m_endCol;

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
      virtual double getSimilarity(const Base& node);

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


      friend class genealogy::Factory;
      friend class genealogy::VisitorSave;
  };


}}
#endif

