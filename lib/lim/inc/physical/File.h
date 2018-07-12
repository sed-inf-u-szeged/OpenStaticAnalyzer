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

#ifndef _LIM_File_H_
#define _LIM_File_H_

#include "lim/inc/lim.h"

/**
* \file File.h
* \brief Contains declaration of the physical::File class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace physical {

  /**
  * \brief File class, which represents the physical::File node.
  * (missing)
  * 
  * Attributes:
  *   - CLOC (int) : (missing)
  *   - LLOC (int) : (missing)
  *   - LOC (int) : (missing)
  *   - numberOfBranches (int) : (missing)
  * 
  * Edges:
  *   - hasComment (base::Comment, multiple) : (missing)
  *   - includes (physical::File, multiple) : (missing)
  */
  class File : public FSEntry {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      File(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~File();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      File & operator=(const File&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      File(const File&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const File& other, bool tryOnVirtualParent);

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
      * \brief Gives back the CLOC of the node.
      * \return Returns with the CLOC.
      */
      unsigned getCLOC() const;

      /**
      * \brief Gives back the LLOC of the node.
      * \return Returns with the LLOC.
      */
      unsigned getLLOC() const;

      /**
      * \brief Gives back the LOC of the node.
      * \return Returns with the LOC.
      */
      unsigned getLOC() const;

      /**
      * \brief Gives back the numberOfBranches of the node.
      * \return Returns with the numberOfBranches.
      */
      unsigned getNumberOfBranches() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the CLOC of the node.
      * \param CLOC [in] The new value of the CLOC.
      */
      void setCLOC(unsigned _CLOC);

      /**
      * \internal
      * \brief Sets the LLOC of the node.
      * \param LLOC [in] The new value of the LLOC.
      */
      void setLLOC(unsigned _LLOC);

      /**
      * \internal
      * \brief Sets the LOC of the node.
      * \param LOC [in] The new value of the LOC.
      */
      void setLOC(unsigned _LOC);

      /**
      * \internal
      * \brief Sets the numberOfBranches of the node.
      * \param numberOfBranches [in] The new value of the numberOfBranches.
      */
      void setNumberOfBranches(unsigned _numberOfBranches);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief The value of the `CLOC`. */
      unsigned m_CLOC;

      /** \internal \brief The value of the `LLOC`. */
      unsigned m_LLOC;

      /** \internal \brief The value of the `LOC`. */
      unsigned m_LOC;

      /** \internal \brief The value of the `numberOfBranches`. */
      unsigned m_numberOfBranches;

    protected:
      /**
      * \brief Set or add the edge by edge kind
      * \param edgeKind           [in] The kind of the edge.
      * \param edgeEnd            [in] The id of node which is on the end of the edge.
      * \param acValue            [in] The value of the association class.
      * \param tryOnVirtualParent [in] This is help for the traversal.
      * \return Return true if setting was success.
      */
      virtual bool setEdge(EdgeKind edgeKind, NodeId edgeEnd, void *acValue, bool tryOnVirtualParent);

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
      * \brief Gives back iterator for the hasComment edges.
      * \return Returns an iterator for the hasComment edges.
      */
      ListIterator<base::Comment> getCommentListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the hasComment edges.
      * \return Returns an iterator for the hasComment edges.
      */
      ListIterator<base::Comment> getCommentListIteratorEnd() const;

      /**
      * \brief Tells whether the node has hasComment edges or not.
      * \return Returns true if the node doesn't have any hasComment edge.
      */
      bool getCommentIsEmpty() const;

      /**
      * \brief Gives back how many hasComment edges the node has.
      * \return Returns with the number of hasComment edges.
      */
      unsigned getCommentSize() const;

      /**
      * \brief Gives back iterator for the includes edges.
      * \return Returns an iterator for the includes edges.
      */
      ListIterator<physical::File> getIncludesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the includes edges.
      * \return Returns an iterator for the includes edges.
      */
      ListIterator<physical::File> getIncludesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has includes edges or not.
      * \return Returns true if the node doesn't have any includes edge.
      */
      bool getIncludesIsEmpty() const;

      /**
      * \brief Gives back how many includes edges the node has.
      * \return Returns with the number of includes edges.
      */
      unsigned getIncludesSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Adds a new hasComment edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new hasComment edge.
      */
      void addComment(const base::Comment *node);

      /**
      * \brief Adds a new hasComment edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new hasComment edge.
      */
      void addComment(NodeId id);

      /**
      * \brief Remove the hasComment edge by id from the node.
      * \param id [in] The end point of the hasComment edge.
      */
      void removeComment(NodeId id);

      /**
      * \brief Remove the hasComment edge from the node.
      * \param node [in] The end point of the hasComment edge.
      */
      void removeComment(base::Comment *node);

      /**
      * \brief Adds a new includes edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new includes edge.
      */
      void addIncludes(const File *node);

      /**
      * \brief Adds a new includes edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new includes edge.
      */
      void addIncludes(NodeId id);

      /**
      * \brief Remove the includes edge by id from the node.
      * \param id [in] The end point of the includes edge.
      */
      void removeIncludes(NodeId id);

      /**
      * \brief Remove the includes edge from the node.
      * \param node [in] The end point of the includes edge.
      */
      void removeIncludes(File *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief Container stores the id of the nodes the hasComment edge points to. */
      ListIterator<base::Comment>::Container hasCommentContainer;

      /** \internal \brief Container stores the id of the nodes the includes edge points to. */
      ListIterator<physical::File>::Container includesContainer;

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


      friend class lim::asg::Factory;
      friend class lim::asg::VisitorSave;
  };

} 


}}}
#endif

