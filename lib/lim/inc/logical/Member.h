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

#ifndef _LIM_Member_H_
#define _LIM_Member_H_

#include "lim/inc/lim.h"

/**
* \file Member.h
* \brief Contains declaration of the logical::Member class.
* \brief The it get atributes from 
*/

namespace columbus { namespace lim { namespace asg {
namespace logical {

  /**
  * \brief Member class, which represents the logical::Member node.
  * (missing)
  * 
  * Attributes:
  *   - accessibility (AccessibilityKind) : (missing)
  *   - commentLines (int) : (missing)
  *   - demangledName (String) : (missing)
  *   - isCompilerGenerated (boolean) : (missing)
  *   - isStatic (boolean) : (missing)
  *   - language (LanguageKind) : (missing)
  *   - mangledName (String) : (missing)
  * 
  * Edges:
  *   - aggregated (logical::Member, single) : (missing)
  *   - belongsTo (base::Component, multiple) : (missing)
  *   - compilationUnit (physical::File, multiple) : (missing)
  *   - declares (logical::Member, single) : (missing)
  *   - hasComment (base::Comment, multiple) : (missing)
  *   - instance (logical::Member, multiple) : (missing)
  *   - isContainedIn (physical::File, multiple) : (missing)
  *   - languageVariant (logical::Member, single) : (missing)
  *   - uses (type::Type, multiple) : (missing)
  *   - variant (logical::Member, multiple) : (missing)
  */
  class Member : public base::Named {
    protected:
      /**
      * \internal
      * \brief Non-public constructor, only factory can instantiates nodes.
      * \param nodeId  [in] The id of the node.
      * \param factory [in] Poiter to the Factory the node belongs to.
      */
      Member(NodeId nodeId, Factory *factory);

      /**
      * \internal
      * \brief Non-public destructor, only factory can destroy nodes.
      */
      virtual ~Member();

    private:
      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Member & operator=(const Member&);

      /**
      * \brief This function always throws a LimException due to copying is not allowed!
      */
      Member(const Member&);

    protected:
      /**
      * \internal
      * \brief Clone method.
      */
      virtual void clone(const Member& other, bool tryOnVirtualParent);

    public:
      /**
      * \brief Gives back the NodeKind of the node.
      * \return Returns with the NodeKind.
      */
      virtual NodeKind getNodeKind() const = 0;

      /**
      * \brief Delete all edge.
      */
      virtual void prepareDelete(bool tryOnVirtualParent);


      // ---------- Attribute getter function(s) ----------

      /**
      * \brief Gives back the accessibility of the node.
      * \return Returns with the accessibility.
      */
      AccessibilityKind getAccessibility() const;

      /**
      * \brief Gives back the commentLines of the node.
      * \return Returns with the commentLines.
      */
      unsigned getCommentLines() const;

      /**
      * \brief Gives back the demangledName of the node.
      * \return Returns with the demangledName.
      */
      const std::string& getDemangledName() const;

      /**
      * \brief Gives back the Key of demangledName of the node.
      * \return Returns with the Key of the demangledName.
      */
      Key getDemangledNameKey() const;

      /**
      * \brief Gives back the isCompilerGenerated of the node.
      * \return Returns with the isCompilerGenerated.
      */
      bool getIsCompilerGenerated() const;

      /**
      * \brief Gives back the isStatic of the node.
      * \return Returns with the isStatic.
      */
      bool getIsStatic() const;

      /**
      * \brief Gives back the language of the node.
      * \return Returns with the language.
      */
      LanguageKind getLanguage() const;

      /**
      * \brief Gives back the mangledName of the node.
      * \return Returns with the mangledName.
      */
      const std::string& getMangledName() const;

      /**
      * \brief Gives back the Key of mangledName of the node.
      * \return Returns with the Key of the mangledName.
      */
      Key getMangledNameKey() const;


      // ---------- Attribute setter function(s) ----------

      /**
      * \internal
      * \brief Sets the accessibility of the node.
      * \param accessibility [in] The new value of the accessibility.
      */
      void setAccessibility(AccessibilityKind _accessibility);

      /**
      * \internal
      * \brief Sets the commentLines of the node.
      * \param commentLines [in] The new value of the commentLines.
      */
      void setCommentLines(unsigned _commentLines);

      /**
      * \internal
      * \brief Sets the demangledName of the node.
      * \param demangledName [in] The new value of the demangledName.
      */
      void setDemangledName(const std::string& _demangledName);

      /**
      * \internal
      * \brief Sets the isCompilerGenerated of the node.
      * \param isCompilerGenerated [in] The new value of the isCompilerGenerated.
      */
      void setIsCompilerGenerated(bool _isCompilerGenerated);

      /**
      * \internal
      * \brief Sets the isStatic of the node.
      * \param isStatic [in] The new value of the isStatic.
      */
      void setIsStatic(bool _isStatic);

      /**
      * \internal
      * \brief Sets the language of the node.
      * \param language [in] The new value of the language.
      */
      void setLanguage(LanguageKind _language);

      /**
      * \internal
      * \brief Sets the mangledName of the node.
      * \param mangledName [in] The new value of the mangledName.
      */
      void setMangledName(const std::string& _mangledName);

      /**
      * \internal
      * \brief Sets the demangledName of the node.
      * \param demangledName [in] The new Key of the demangledName.
      */
      void setDemangledNameKey(Key _demangledName);

      /**
      * \internal
      * \brief Sets the mangledName of the node.
      * \param mangledName [in] The new Key of the mangledName.
      */
      void setMangledNameKey(Key _mangledName);

    protected:

      // ---------- Attribute(s) ----------

      /** \internal \brief Stores whether the node is `CompilerGenerated` or not. */
      bool m_isCompilerGenerated : 1;

      /** \internal \brief Stores whether the node is `Static` or not. */
      bool m_isStatic : 1;

      /** \internal \brief The AccessibilityKind of the node. */
      AccessibilityKind m_accessibility;

      /** \internal \brief The value of the `commentLines`. */
      unsigned m_commentLines;

      /** \internal \brief The LanguageKind of the node. */
      LanguageKind m_language;

      /** \internal \brief The Key of the `demangledName`. */
      Key m_demangledName;

      /** \internal \brief The Key of the `mangledName`. */
      Key m_mangledName;

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
      * \brief Gives back the pointer of the node the aggregated edge points to.
      * \return Returns the end point of the aggregated edge.
      */
      logical::Member* getAggregated() const;

      /**
      * \brief Gives back iterator for the belongsTo edges.
      * \return Returns an iterator for the belongsTo edges.
      */
      ListIterator<base::Component> getBelongsToListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the belongsTo edges.
      * \return Returns an iterator for the belongsTo edges.
      */
      ListIterator<base::Component> getBelongsToListIteratorEnd() const;

      /**
      * \brief Tells whether the node has belongsTo edges or not.
      * \return Returns true if the node doesn't have any belongsTo edge.
      */
      bool getBelongsToIsEmpty() const;

      /**
      * \brief Gives back how many belongsTo edges the node has.
      * \return Returns with the number of belongsTo edges.
      */
      unsigned getBelongsToSize() const;

      /**
      * \brief Gives back iterator for the compilationUnit edges.
      * \return Returns an iterator for the compilationUnit edges.
      */
      ListIterator<physical::File> getCompilationUnitListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the compilationUnit edges.
      * \return Returns an iterator for the compilationUnit edges.
      */
      ListIterator<physical::File> getCompilationUnitListIteratorEnd() const;

      /**
      * \brief Tells whether the node has compilationUnit edges or not.
      * \return Returns true if the node doesn't have any compilationUnit edge.
      */
      bool getCompilationUnitIsEmpty() const;

      /**
      * \brief Gives back how many compilationUnit edges the node has.
      * \return Returns with the number of compilationUnit edges.
      */
      unsigned getCompilationUnitSize() const;

      /**
      * \brief Gives back the pointer of the node the declares edge points to.
      * \return Returns the end point of the declares edge.
      */
      logical::Member* getDeclares() const;

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
      * \brief Gives back iterator for the instance edges.
      * \return Returns an iterator for the instance edges.
      */
      ListIterator<logical::Member> getInstanceListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the instance edges.
      * \return Returns an iterator for the instance edges.
      */
      ListIterator<logical::Member> getInstanceListIteratorEnd() const;

      /**
      * \brief Tells whether the node has instance edges or not.
      * \return Returns true if the node doesn't have any instance edge.
      */
      bool getInstanceIsEmpty() const;

      /**
      * \brief Gives back how many instance edges the node has.
      * \return Returns with the number of instance edges.
      */
      unsigned getInstanceSize() const;

      /**
      * \brief Gives back iterator for the isContainedIn edges.
      * \return Returns an iterator for the isContainedIn edges.
      */
      ListIteratorAssocSourcePosition<physical::File> getIsContainedInListIteratorAssocBegin() const;

      /**
      * \brief Gives back iterator for the isContainedIn edges.
      * \return Returns an iterator for the isContainedIn edges.
      */
      ListIteratorAssocSourcePosition<physical::File> getIsContainedInListIteratorAssocEnd() const;

      /**
      * \brief Tells whether the node has isContainedIn edges or not.
      * \return Returns true if the node doesn't have any isContainedIn edge.
      */
      bool getIsContainedInIsEmpty() const;

      /**
      * \brief Gives back how many isContainedIn edges the node has.
      * \return Returns with the number of isContainedIn edges.
      */
      unsigned getIsContainedInSize() const;

      /**
      * \brief Gives back the pointer of the node the languageVariant edge points to.
      * \return Returns the end point of the languageVariant edge.
      */
      logical::Member* getLanguageVariant() const;

      /**
      * \brief Gives back iterator for the uses edges.
      * \return Returns an iterator for the uses edges.
      */
      ListIterator<type::Type> getUsesListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the uses edges.
      * \return Returns an iterator for the uses edges.
      */
      ListIterator<type::Type> getUsesListIteratorEnd() const;

      /**
      * \brief Tells whether the node has uses edges or not.
      * \return Returns true if the node doesn't have any uses edge.
      */
      bool getUsesIsEmpty() const;

      /**
      * \brief Gives back how many uses edges the node has.
      * \return Returns with the number of uses edges.
      */
      unsigned getUsesSize() const;

      /**
      * \brief Gives back iterator for the variant edges.
      * \return Returns an iterator for the variant edges.
      */
      ListIterator<logical::Member> getVariantListIteratorBegin() const;

      /**
      * \brief Gives back iterator for the variant edges.
      * \return Returns an iterator for the variant edges.
      */
      ListIterator<logical::Member> getVariantListIteratorEnd() const;

      /**
      * \brief Tells whether the node has variant edges or not.
      * \return Returns true if the node doesn't have any variant edge.
      */
      bool getVariantIsEmpty() const;

      /**
      * \brief Gives back how many variant edges the node has.
      * \return Returns with the number of variant edges.
      */
      unsigned getVariantSize() const;


      // ---------- Edge setter function(s) ----------

      /**
      * \brief Sets the aggregated edge.
      * \param id [in] The new end point of the aggregated edge.
      */
      void setAggregated(NodeId id);

      /**
      * \brief Sets the aggregated edge.
      * \param node [in] The new end point of the aggregated edge.
      */
      void setAggregated(Member *node);

      /**
      * \brief remove the aggregated edge.
      */
      void removeAggregated();

      /**
      * \brief Adds a new belongsTo edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new belongsTo edge.
      */
      void addBelongsTo(const base::Component *node);

      /**
      * \brief Adds a new belongsTo edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new belongsTo edge.
      */
      void addBelongsTo(NodeId id);

      /**
      * \brief Remove the belongsTo edge by id from the node.
      * \param id [in] The end point of the belongsTo edge.
      */
      void removeBelongsTo(NodeId id);

      /**
      * \brief Remove the belongsTo edge from the node.
      * \param node [in] The end point of the belongsTo edge.
      */
      void removeBelongsTo(base::Component *node);

      /**
      * \brief Adds a new compilationUnit edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new compilationUnit edge.
      */
      void addCompilationUnit(const physical::File *node);

      /**
      * \brief Adds a new compilationUnit edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new compilationUnit edge.
      */
      void addCompilationUnit(NodeId id);

      /**
      * \brief Remove the compilationUnit edge by id from the node.
      * \param id [in] The end point of the compilationUnit edge.
      */
      void removeCompilationUnit(NodeId id);

      /**
      * \brief Remove the compilationUnit edge from the node.
      * \param node [in] The end point of the compilationUnit edge.
      */
      void removeCompilationUnit(physical::File *node);

      /**
      * \brief Sets the declares edge.
      * \param id [in] The new end point of the declares edge.
      */
      void setDeclares(NodeId id);

      /**
      * \brief Sets the declares edge.
      * \param node [in] The new end point of the declares edge.
      */
      void setDeclares(Member *node);

      /**
      * \brief remove the declares edge.
      */
      void removeDeclares();

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
      * \brief Adds a new instance edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new instance edge.
      */
      void addInstance(const Member *node);

      /**
      * \brief Adds a new instance edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new instance edge.
      */
      void addInstance(NodeId id);

      /**
      * \brief Remove the instance edge by id from the node.
      * \param id [in] The end point of the instance edge.
      */
      void removeInstance(NodeId id);

      /**
      * \brief Remove the instance edge from the node.
      * \param node [in] The end point of the instance edge.
      */
      void removeInstance(Member *node);

      /**
      * \brief Adds a new isContainedIn edge to the node.
      * \param node    [in] The end point of the new isContainedIn edge.
      * \param acValue [in] The value of the association class.
      */
      void addIsContainedIn(const physical::File *node, const SourcePosition& acValue);

      /**
      * \brief Adds a new isContainedIn edge to the node.
      * \param id      [in] The end point of the new isContainedIn edge.
      * \param acValue [in] The value of the association class.
      */
      void addIsContainedIn(NodeId id, const SourcePosition& acValue);

      /**
      * \brief Remove the isContainedIn edge by id from the node.
      * \param id [in] The end point of the isContainedIn edge.
      */
      void removeIsContainedIn(NodeId id);

      /**
      * \brief Remove the isContainedIn edge from the node.
      * \param node [in] The end point of the isContainedIn edge.
      */
      void removeIsContainedIn(physical::File *node);

      /**
      * \brief Sets the languageVariant edge.
      * \param id [in] The new end point of the languageVariant edge.
      */
      void setLanguageVariant(NodeId id);

      /**
      * \brief Sets the languageVariant edge.
      * \param node [in] The new end point of the languageVariant edge.
      */
      void setLanguageVariant(Member *node);

      /**
      * \brief remove the languageVariant edge.
      */
      void removeLanguageVariant();

      /**
      * \brief Adds a new uses edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new uses edge.
      */
      void addUses(const type::Type *node);

      /**
      * \brief Adds a new uses edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new uses edge.
      */
      void addUses(NodeId id);

      /**
      * \brief Remove the uses edge by id from the node.
      * \param id [in] The end point of the uses edge.
      */
      void removeUses(NodeId id);

      /**
      * \brief Remove the uses edge from the node.
      * \param node [in] The end point of the uses edge.
      */
      void removeUses(type::Type *node);

      /**
      * \brief Adds a new variant edge to the node and inserts it after the other ones.
      * \param node [in] The end point of the new variant edge.
      */
      void addVariant(const Member *node);

      /**
      * \brief Adds a new variant edge to the node and inserts it after the other ones.
      * \param id [in] The end point of the new variant edge.
      */
      void addVariant(NodeId id);

      /**
      * \brief Remove the variant edge by id from the node.
      * \param id [in] The end point of the variant edge.
      */
      void removeVariant(NodeId id);

      /**
      * \brief Remove the variant edge from the node.
      * \param node [in] The end point of the variant edge.
      */
      void removeVariant(Member *node);

    protected:

      // ---------- Edges ----------

      /** \internal \brief The id of the node the aggregated edge points to. */
      NodeId m_aggregated;

      /** \internal \brief Container stores the id of the nodes the belongsTo edge points to. */
      ListIterator<base::Component>::Container belongsToContainer;

      /** \internal \brief Container stores the id of the nodes the compilationUnit edge points to. */
      ListIterator<physical::File>::Container compilationUnitContainer;

      /** \internal \brief The id of the node the declares edge points to. */
      NodeId m_declares;

      /** \internal \brief Container stores the id of the nodes the hasComment edge points to. */
      ListIterator<base::Comment>::Container hasCommentContainer;

      /** \internal \brief Container stores the id of the nodes the instance edge points to. */
      ListIterator<logical::Member>::Container instanceContainer;

      /** \internal \brief Container stores the id of the nodes the isContainedIn edge points to and the association classes. */
      ListIteratorAssocSourcePosition<physical::File>::Container isContainedInContainer;

      /** \internal \brief The id of the node the languageVariant edge points to. */
      NodeId m_languageVariant;

      /** \internal \brief Container stores the id of the nodes the uses edge points to. */
      ListIterator<type::Type>::Container usesContainer;

      /** \internal \brief Container stores the id of the nodes the variant edge points to. */
      ListIterator<logical::Member>::Container variantContainer;

    public:

      // ---------- Accept functions for Visitor it now pure virtual ----------

      /**
      * \brief It calls the appropriate visit method of the given visitor in the child nodes.
      * \param visitor [in] The used visitor.
      */
      virtual void accept(Visitor& visitor) const = 0;

      /**
      * \brief It calls the appropriate visitEnd method of the given visitor in the child nodes.
      * \param visitor [in] The used visitor.
      */
      virtual void acceptEnd(Visitor& visitor) const = 0;

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

