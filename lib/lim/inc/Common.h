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

#ifndef _LIM_Common_H_
#define _LIM_Common_H_

#include "lim/inc/lim.h"

#include <common/inc/PlatformDependentDefines.h>/**
* \file Common.h
* \brief Contains declaration of Common namespace.
*/

namespace columbus { namespace lim { namespace asg {
  typedef unsigned int NodeHashType;
  /**
  * \brief Common contains general graph algorithms and common functions
  */
  namespace Common {
      /**
      * \brief Decides whether the node is base::Comment or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Comment.
      */
      bool getIsComment(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Component or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Component.
      */
      bool getIsComponent(const base::Base& node);

      /**
      * \brief Decides whether the node is base::ControlFlowBlock or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::ControlFlowBlock.
      */
      bool getIsControlFlowBlock(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Named or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Named.
      */
      bool getIsNamed(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::Attribute or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::Attribute.
      */
      bool getIsAttribute(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::AttributeAccess or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::AttributeAccess.
      */
      bool getIsAttributeAccess(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::Class or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::Class.
      */
      bool getIsClass(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::ClassGeneric or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::ClassGeneric.
      */
      bool getIsClassGeneric(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::ClassGenericInstance or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::ClassGenericInstance.
      */
      bool getIsClassGenericInstance(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::ClassGenericSpec or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::ClassGenericSpec.
      */
      bool getIsClassGenericSpec(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::Friendship or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::Friendship.
      */
      bool getIsFriendship(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::GenericParameter or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::GenericParameter.
      */
      bool getIsGenericParameter(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::Member or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::Member.
      */
      bool getIsMember(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::Method or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::Method.
      */
      bool getIsMethod(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::MethodCall or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::MethodCall.
      */
      bool getIsMethodCall(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::MethodGeneric or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::MethodGeneric.
      */
      bool getIsMethodGeneric(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::MethodGenericInstance or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::MethodGenericInstance.
      */
      bool getIsMethodGenericInstance(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::MethodGenericSpec or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::MethodGenericSpec.
      */
      bool getIsMethodGenericSpec(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::Package or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::Package.
      */
      bool getIsPackage(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::Parameter or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::Parameter.
      */
      bool getIsParameter(const base::Base& node);

      /**
      * \brief Decides whether the node is logical::Scope or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is logical::Scope.
      */
      bool getIsScope(const base::Base& node);

      /**
      * \brief Decides whether the node is physical::FSEntry or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is physical::FSEntry.
      */
      bool getIsFSEntry(const base::Base& node);

      /**
      * \brief Decides whether the node is physical::File or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is physical::File.
      */
      bool getIsFile(const base::Base& node);

      /**
      * \brief Decides whether the node is physical::FileSystem or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is physical::FileSystem.
      */
      bool getIsFileSystem(const base::Base& node);

      /**
      * \brief Decides whether the node is physical::Folder or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is physical::Folder.
      */
      bool getIsFolder(const base::Base& node);

      /**
      * \brief Decides whether the node is type::SimpleType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::SimpleType.
      */
      bool getIsSimpleType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::Type or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::Type.
      */
      bool getIsType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::TypeFormer or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::TypeFormer.
      */
      bool getIsTypeFormer(const base::Base& node);

      /**
      * \brief Decides whether the node is type::TypeFormerArray or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::TypeFormerArray.
      */
      bool getIsTypeFormerArray(const base::Base& node);

      /**
      * \brief Decides whether the node is type::TypeFormerMethod or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::TypeFormerMethod.
      */
      bool getIsTypeFormerMethod(const base::Base& node);

      /**
      * \brief Decides whether the node is type::TypeFormerNonType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::TypeFormerNonType.
      */
      bool getIsTypeFormerNonType(const base::Base& node);

      /**
      * \brief Decides whether the node is type::TypeFormerPointer or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::TypeFormerPointer.
      */
      bool getIsTypeFormerPointer(const base::Base& node);

      /**
      * \brief Decides whether the node is type::TypeFormerType or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is type::TypeFormerType.
      */
      bool getIsTypeFormerType(const base::Base& node);

      /**
      * \brief Decides whether the node is AP spec node or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is AP spec node.
      */
      bool getIsAPSpecNode(const base::Base& node);

      /**
      * \brief Decides whether the 'base' is one of the base kinds (transitive) of 'what'.
      * \param what [in] The examined node kind.
      * \param base [in] The base node kind.
      * \return Returns true if 'base' is a base kind of 'what'.
      */
      bool getIsBaseClassKind(NodeKind what, NodeKind base);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is composite.
      */
      bool getIsComposite(const base::Base& node);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is not composite.
      */
      bool getIsNotComposite(const base::Base& node);

      /**
      * \brief Gives back the string representation of the NodeId.
      * \param nodeId [in] The NodeId.
      * \return The string representation of the nodeId given in the parameter.
      */
      const std::string toString(NodeId nodeId);

      /**
      * \brief Gives back the string representation of the AccessibilityKind kind.
      * \param kind         [in] The AccessibilityKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(AccessibilityKind kind);

      /**
      * \brief Gives back the string representation of the AnalysisTimeKind kind.
      * \param kind         [in] The AnalysisTimeKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(AnalysisTimeKind kind);

      /**
      * \brief Gives back the string representation of the ClassKind kind.
      * \param kind         [in] The ClassKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(ClassKind kind);

      /**
      * \brief Gives back the string representation of the GenericParameterKind kind.
      * \param kind         [in] The GenericParameterKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(GenericParameterKind kind);

      /**
      * \brief Gives back the string representation of the LanguageKind kind.
      * \param kind         [in] The LanguageKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(LanguageKind kind);

      /**
      * \brief Gives back the string representation of the MethodKind kind.
      * \param kind         [in] The MethodKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(MethodKind kind);

      /**
      * \brief Gives back the string representation of the PackageKind kind.
      * \param kind         [in] The PackageKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(PackageKind kind);

      /**
      * \brief Gives back the string representation of the ParameterKind kind.
      * \param kind         [in] The ParameterKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(ParameterKind kind);

      /**
      * \brief Gives back the string representation of the PointerKind kind.
      * \param kind         [in] The PointerKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(PointerKind kind);

      /**
      * \brief Gives back the string representation of the RealizationLevel kind.
      * \param kind         [in] The RealizationLevel.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(RealizationLevel kind);

      /**
      * \brief Gives back the string representation of the SimpleTypeKind kind.
      * \param kind         [in] The SimpleTypeKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(SimpleTypeKind kind);

      /**
      * \brief Gives back the string representation of the TypeArgumentConstraintKind kind.
      * \param kind         [in] The TypeArgumentConstraintKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(TypeArgumentConstraintKind kind);

      /**
      * \brief Gives back the string representation of the NodeKind kind.
      * \param kind         [in] The NodeKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(NodeKind kind);

      /**
      * \brief Gives back the string representation of the EdgeKind kind.
      * \param kind         [in] The EdgeKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(EdgeKind kind);

      /**
      * \brief Returns true if the node exists and is not filtered out.
      * \param id [in] The examined node ID.
      * \return True if the node exists and is not filtered out.
      */
      bool getIsValid(NodeId id);

      /**
      * \brief Minimum of same type node similarity.
      */
      extern double SimilarityMinimum;

      /**
      * \brief Returns the minimum similarity value of same type nodes.
      * \return Minimum of same type node similarity.
      */
      double getSimilarityMinimum();

      /**
      * \brief Sets the minimum similarity value of same type nodes.
      * \param value [in] Minimum of same type node similarity.
      */
      void setSimilarityMinimum(double value);

      /**
      * \brief Minimum similarity for string type attributes.
      */
      extern double SimilarityMinForStrings;

      /**
      * \brief Returns the minimum similarity value for string type attributes.
      * \return Minimum similarity for string type attributes.
      */
      double getSimilarityMinForStrings();

      /**
      * \brief Sets the minimum similarity value for string type attributes.
      * \param value [in] Minimum similarity for string type attributes.
      */
      void setSimilarityMinForStrings(double value);

      /**
      * \brief Minimum similarity for AP spec edges.
      */
      extern double SimilarityMinForEdges;

      /**
      * \brief Returns the minimum similarity value for AP spec edges.
      * \return Minimum similarity for AP spec edges.
      */
      double getSimilarityMinForEdges();

      /**
      * \brief Sets the minimum similarity value for AP spec edges.
      * \param value [in] Minimum similarity for AP spec edges.
      */
      void setSimilarityMinForEdges(double value);


      /**
      * \brief Gives back the string representation of the \ref Language.
      * \param language     [in] The Language.
      * \throw LimException If the language is not "valid" LimException is thrown.
      * \return The string representation of the language given in the parameter.
      */
      const std::string toString(Language language);

      /**
      * \brief Gives back the string representation of the \ref ClassDiagramLinkKind.
      * \param linkKind     [in] The ClassDiagramLinkKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The string representation of the link kind given in the parameter.
      */
      const std::string toString(ClassDiagramLinkKind linkKind);

      /**
      * \brief Gives back the string representation of the \ref ClassDiagramLinkMultiplicity.
      * \param linkmult     [in] The ClassDiagramLinkMultiplicity.
      * \throw LimException If the multyplicity is not "valid" LimException is thrown.
      * \return The string representation of the link multiplicity given in the parameter.
      */
      const std::string toString(ClassDiagramLinkMultiplicity linkMult);

      /**
      * \brief Gives back the name of the ClassKind kind (starting with capital letter).
      * \param kind         [in] The ClassKind.
      * \throw LimException If the kind is not "valid" LimException is thrown.
      * \return The name of the kind given in the parameter.
      */
      const std::string toSrcString(ClassKind kind);

      /**
      * \brief Searches for the Scope parent of the node.
      * \param node [in] The node whose Scope parent is searched.
      * \return The id of its Scope parent (or 0 if it does not exist).
      */
      NodeId getScopeParent(const base::Base& node);

      /**
      * \brief Searches for the Package parent of the node.
      * \param node [in] The node whose Package parent is searched.
      * \return The id of its Package parent (or 0 if it does not exist).
      */
      NodeId getPackageParent(const base::Base& node);

      /**
      * \brief Creates the scoped name of the node.
      * \param node [in] The node.
      * \return Returns the scoped name of the node.
      */
      const std::string getScopedName(const base::Named& node);
	  
	  /**
      * \brief Creates unique name of the method in the parameter.
      * \param node [in] The node.
      * \return Returns the unique name of the node.
      */
      const std::string getUniqueName(const lim::asg::logical::Method& node);

      /**
      * \brief Returns the full path of the FSEntry node.
      * \param node      [in] The FSEntry node.
      * \param separator [in] The separator character.
      * \return The full path of the FSEntry node.
      */
      std::string getFullPath(const lim::asg::physical::FSEntry& node, const char separator = DIRDIVCHAR);
      
      /**
      * \brief Returns the prototype pointer of the method instance.
      * \param revEdges       [in] ReverseEdges, which requires to collect prototype.
      * \param methodInstance [in] The method instance, whitch prototype is needed.
      * \return The MethodGeneric prototype or NULL if no prototype exists.
      */
      const lim::asg::logical::MethodGeneric* getMethodPrototype(const ReverseEdges& revEdges, const lim::asg::logical::MethodGenericInstance& methodInstance);

      /**
      * \brief Returns the prototype pointer of the class instance.
      * \param revEdges       [in] ReverseEdges, which requires to collect prototype.
      * \param classInstance  [in] The class instance, whitch prototype is needed.
      * \return The ClassGeneric prototype or NULL if no prototyte exists.
      */
      const lim::asg::logical::ClassGeneric* getClassPrototype(const ReverseEdges& revEdges, const lim::asg::logical::ClassGenericInstance& classInstance);

      /**
      * \brief Performance helper data-structures for inheritance related metrics
      */
      struct InheritanceData
      {
        std::set<const logical::Class*> nodes;
        int depth;
      };
      typedef std::map<const lim::asg::logical::Class*, InheritanceData> InheritanceCache;

      /**
      * \brief Collects the parents of the given class node.
      * \param revEdges [in] ReverseEdges, which are required for collecting parents.
      * \param node    [in] The node.
      * \param parents [out] The ids of the parents (but it is not cleared before collecting them).
      */
      void collectParents(const ReverseEdges& revEdges, const logical::Class& node, std::set<const logical::Class*>& parents, InheritanceCache* cache = NULL);

      /**
      * \brief Collects the ancestors of the given class node.
      * \param revEdges  [in] ReverseEdges, which are required for collecting ancestors.
      * \param node      [in] The node.
      * \param ancestors [out] The ids of the ancestors (but it is not cleared before collecting them).
      * \return The depth of the node in the inheritance tree (DIT)
      */
      int collectAncestors(const ReverseEdges& revEdges, const logical::Class& node, std::set<const logical::Class*>& ancestors, InheritanceCache* cache = NULL);

      /**
      * \brief Collects the children of the given class node.
      * \param revEdges [in] ReverseEdges, which are required for collecting children.
      * \param node     [in] The node.
      * \param children [out] The ids of the children (but it is not cleared before collecting them).
      */
      void collectChildren(const ReverseEdges& revEdges, const logical::Class& node, std::set<const logical::Class*>& children, InheritanceCache* cache = NULL);

      /**
      * \brief Collects the descendants of the given class node.
      * \param revEdges [in] ReverseEdges, which are required for collecting descendants.
      * \param node        [in] The node.
      * \param descendants [out] The ids of the descendants (but it is not cleared before collecting them).
      * \return The depth difference between the node and its deepest child (CLD)
      */
      int collectDescendants(const ReverseEdges& revEdges, const logical::Class& node, std::set<const logical::Class*>& descendants, InheritanceCache* cache = NULL);

#if 0
      /**
      * \brief Tells whether the node can have more position info or not.
      * \param node [in] The node.
      * \return Returns true if the node can have more position info.
      */
      bool getHasMorePositions(const base::Base& node);

      /**
      * \brief Collects the methods that are called by the given method node.
      * \param node    [in] The node.
      * \param callees [out] The ids of the callees (but it is not cleared before collecting them).
      */
      void collectCallees(const logical::Method& node, std::set<NodeId>& callees);

      /**
      * \brief Collects the methods that call the given method node.
      * \param revEdges [in] ReverseEdges, which requires to collect callers.
      * \param node     [in] The node.
      * \param callers  [out] The ids of the callers (but it is not cleared before collecting them).
      */
      void collectCallers(const ReverseEdges& revEdges, const logical::Method& node, std::set<NodeId>& callers);
#endif


  } // Common


}}}
#endif

