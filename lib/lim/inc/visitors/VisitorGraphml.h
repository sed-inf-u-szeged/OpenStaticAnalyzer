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

#ifndef _LIM_VISITORGRAPHML_H_
#define _LIM_VISITORGRAPHML_H_

#include "lim/inc/lim.h"
#include "io/inc/GraphmlIO.h"

/**
* \file VisitorGraphml.h
* \brief Contains declaration of VisitorGraphml class.
*/

namespace columbus { namespace lim { namespace asg {

  /**
  * \brief Exports the ASG to Graphml format.
  */
  class VisitorGraphml : public Visitor {
    public:
      typedef bool(*NodeCompareFunc)(const base::Base&);

      /**
      * \brief Constructor for VisitorGraphml.
      */
      VisitorGraphml(columbus::io::GraphmlIO& io, std::set< std::string>& edgeFilter, unsigned int maxDrawingDepth = 0);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorGraphml();

      /**
      * \brief Give back to compare function
      */
      NodeCompareFunc getCompareFunctionToNode( std::string& nodeName);

      /**
      * \brief Create compare map
      */
      static std::map< std::string, NodeCompareFunc> create_map(){
        std::map< std::string, NodeCompareFunc> cmpTable;
        cmpTable.insert( std::make_pair( "Comment", &Common::getIsComment));
        cmpTable.insert( std::make_pair( "Component", &Common::getIsComponent));
        cmpTable.insert( std::make_pair( "ControlFlowBlock", &Common::getIsControlFlowBlock));
        cmpTable.insert( std::make_pair( "Named", &Common::getIsNamed));
        cmpTable.insert( std::make_pair( "Attribute", &Common::getIsAttribute));
        cmpTable.insert( std::make_pair( "AttributeAccess", &Common::getIsAttributeAccess));
        cmpTable.insert( std::make_pair( "Class", &Common::getIsClass));
        cmpTable.insert( std::make_pair( "ClassGeneric", &Common::getIsClassGeneric));
        cmpTable.insert( std::make_pair( "ClassGenericInstance", &Common::getIsClassGenericInstance));
        cmpTable.insert( std::make_pair( "ClassGenericSpec", &Common::getIsClassGenericSpec));
        cmpTable.insert( std::make_pair( "Friendship", &Common::getIsFriendship));
        cmpTable.insert( std::make_pair( "GenericParameter", &Common::getIsGenericParameter));
        cmpTable.insert( std::make_pair( "Member", &Common::getIsMember));
        cmpTable.insert( std::make_pair( "Method", &Common::getIsMethod));
        cmpTable.insert( std::make_pair( "MethodCall", &Common::getIsMethodCall));
        cmpTable.insert( std::make_pair( "MethodGeneric", &Common::getIsMethodGeneric));
        cmpTable.insert( std::make_pair( "MethodGenericInstance", &Common::getIsMethodGenericInstance));
        cmpTable.insert( std::make_pair( "MethodGenericSpec", &Common::getIsMethodGenericSpec));
        cmpTable.insert( std::make_pair( "Package", &Common::getIsPackage));
        cmpTable.insert( std::make_pair( "Parameter", &Common::getIsParameter));
        cmpTable.insert( std::make_pair( "Scope", &Common::getIsScope));
        cmpTable.insert( std::make_pair( "FSEntry", &Common::getIsFSEntry));
        cmpTable.insert( std::make_pair( "File", &Common::getIsFile));
        cmpTable.insert( std::make_pair( "FileSystem", &Common::getIsFileSystem));
        cmpTable.insert( std::make_pair( "Folder", &Common::getIsFolder));
        cmpTable.insert( std::make_pair( "SimpleType", &Common::getIsSimpleType));
        cmpTable.insert( std::make_pair( "Type", &Common::getIsType));
        cmpTable.insert( std::make_pair( "TypeFormer", &Common::getIsTypeFormer));
        cmpTable.insert( std::make_pair( "TypeFormerArray", &Common::getIsTypeFormerArray));
        cmpTable.insert( std::make_pair( "TypeFormerMethod", &Common::getIsTypeFormerMethod));
        cmpTable.insert( std::make_pair( "TypeFormerNonType", &Common::getIsTypeFormerNonType));
        cmpTable.insert( std::make_pair( "TypeFormerPointer", &Common::getIsTypeFormerPointer));
        cmpTable.insert( std::make_pair( "TypeFormerType", &Common::getIsTypeFormerType));
        return cmpTable;
      }

      /**
      * \brief Filter node types by matching substring in qualified name
      */
      static const std::set< std::string> getNodeTypeSet(){
        std::set< std::string> types;
        types.insert( "base::Base");
        types.insert( "base::Comment");
        types.insert( "base::Component");
        types.insert( "base::ControlFlowBlock");
        types.insert( "base::Named");
        types.insert( "logical::Attribute");
        types.insert( "logical::AttributeAccess");
        types.insert( "logical::Class");
        types.insert( "logical::ClassGeneric");
        types.insert( "logical::ClassGenericInstance");
        types.insert( "logical::ClassGenericSpec");
        types.insert( "logical::Friendship");
        types.insert( "logical::GenericParameter");
        types.insert( "logical::Member");
        types.insert( "logical::Method");
        types.insert( "logical::MethodCall");
        types.insert( "logical::MethodGeneric");
        types.insert( "logical::MethodGenericInstance");
        types.insert( "logical::MethodGenericSpec");
        types.insert( "logical::Package");
        types.insert( "logical::Parameter");
        types.insert( "logical::Scope");
        types.insert( "physical::FSEntry");
        types.insert( "physical::File");
        types.insert( "physical::FileSystem");
        types.insert( "physical::Folder");
        types.insert( "type::SimpleType");
        types.insert( "type::Type");
        types.insert( "type::TypeFormer");
        types.insert( "type::TypeFormerArray");
        types.insert( "type::TypeFormerMethod");
        types.insert( "type::TypeFormerNonType");
        types.insert( "type::TypeFormerPointer");
        types.insert( "type::TypeFormerType");
        return types;
      }

      /** \internal \brief It contains a table to node names and compare functions */
      static const std::map< std::string, NodeCompareFunc> compareTable;

      /**
      * \brief Set startpoint
      */
      void setStartPoint( NodeId startPoint);

      /**
      * \brief Set it is white color node or not
      */
      void setIsWhiteColor( bool isWhite);

      /**
      * \brief Set it is need to grouping tree nodes or not
      */
      void setIsGroupingTreeNodes( bool groupingTreeNodes);

      /**
      * \brief Set it is enabled to draw cross edges or not
      */
      void setIsEnableCrossEdge( bool isVisitCrossEdge);

      /**
      * \brief Set node type names to show attributes only of these types 
      */
      void addToFilterNodeTypeAttributes( std::string type);

      /**
      * \brief Set node type names to filtering
      */
      void addToFilterNodeType( std::string type);

      /**
      * \brief Set node type names to filtering
      */
      void filterNodeTypeMatch( std::string pattern);

      /**
      * \brief Writes the Graphml representation of the base::Comment node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Comment& node, bool callVirtualBase = true);

      /**
      * \brief Converts the base::Comment node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Comment& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the base::Component node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::Component& node, bool callVirtualBase = true);

      /**
      * \brief Converts the base::Component node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::Component& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the base::ControlFlowBlock node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const base::ControlFlowBlock& node, bool callVirtualBase = true);

      /**
      * \brief Converts the base::ControlFlowBlock node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const base::ControlFlowBlock& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::Attribute node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Attribute& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::Attribute node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Attribute& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::AttributeAccess node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::AttributeAccess& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::AttributeAccess node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::AttributeAccess& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::Class node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Class& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::Class node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Class& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::ClassGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::ClassGeneric node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::ClassGenericInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGenericInstance& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::ClassGenericInstance node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGenericInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::ClassGenericSpec node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::ClassGenericSpec& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::ClassGenericSpec node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::ClassGenericSpec& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::Friendship node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Friendship& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::Friendship node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Friendship& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::GenericParameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::GenericParameter& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::GenericParameter node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::GenericParameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::Method node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Method& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::Method node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Method& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::MethodCall node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodCall& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::MethodCall node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodCall& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::MethodGeneric node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::MethodGeneric node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGeneric& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::MethodGenericInstance node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGenericInstance& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::MethodGenericInstance node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGenericInstance& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::MethodGenericSpec node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::MethodGenericSpec& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::MethodGenericSpec node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::MethodGenericSpec& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::Package node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Package& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::Package node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Package& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the logical::Parameter node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const logical::Parameter& node, bool callVirtualBase = true);

      /**
      * \brief Converts the logical::Parameter node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const logical::Parameter& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the physical::File node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::File& node, bool callVirtualBase = true);

      /**
      * \brief Converts the physical::File node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::File& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the physical::FileSystem node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::FileSystem& node, bool callVirtualBase = true);

      /**
      * \brief Converts the physical::FileSystem node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::FileSystem& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the physical::Folder node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const physical::Folder& node, bool callVirtualBase = true);

      /**
      * \brief Converts the physical::Folder node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const physical::Folder& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the type::SimpleType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::SimpleType& node, bool callVirtualBase = true);

      /**
      * \brief Converts the type::SimpleType node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::SimpleType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the type::Type node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::Type& node, bool callVirtualBase = true);

      /**
      * \brief Converts the type::Type node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::Type& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the type::TypeFormerArray node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerArray& node, bool callVirtualBase = true);

      /**
      * \brief Converts the type::TypeFormerArray node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerArray& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the type::TypeFormerMethod node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerMethod& node, bool callVirtualBase = true);

      /**
      * \brief Converts the type::TypeFormerMethod node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerMethod& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the type::TypeFormerNonType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerNonType& node, bool callVirtualBase = true);

      /**
      * \brief Converts the type::TypeFormerNonType node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerNonType& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the type::TypeFormerPointer node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerPointer& node, bool callVirtualBase = true);

      /**
      * \brief Converts the type::TypeFormerPointer node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerPointer& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the type::TypeFormerType node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const type::TypeFormerType& node, bool callVirtualBase = true);

      /**
      * \brief Converts the type::TypeFormerType node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const type::TypeFormerType& node, bool callVirtualBase = true);

      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_CompilationUnit(const base::Component& begin, const physical::File& end);

      /**
      * \brief Edge visitor for contains edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_Contains(const base::Component& begin, const base::Component& end);

      /**
      * \brief Edge visitor for hasFiles edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitComponent_HasFiles(const base::Component& begin, const physical::File& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end);

      /**
      * \brief Edge visitor for pred edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end);

      /**
      * \brief Edge visitor for dependsOn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttribute_HasType(const logical::Attribute& begin, const type::Type& end);

      /**
      * \brief Edge visitor for attribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end);

      /**
      * \brief Edge visitor for extends edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_Extends(const logical::Class& begin, const logical::Class& end);

      /**
      * \brief Edge visitor for grantsFriendship edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end);

      /**
      * \brief Edge visitor for isSubclass edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClass_IsSubclass(const logical::Class& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end);

      /**
      * \brief Edge visitor for friend edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end);

      /**
      * \brief Edge visitor for hasParameterConstraint edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end);

      /**
      * \brief Edge visitor for aggregated edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Aggregated(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for belongsTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_BelongsTo(const logical::Member& begin, const base::Component& end);

      /**
      * \brief Edge visitor for compilationUnit edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_CompilationUnit(const logical::Member& begin, const physical::File& end);

      /**
      * \brief Edge visitor for declares edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Declares(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_HasComment(const logical::Member& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for instance edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Instance(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for isContainedIn edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac);

      /**
      * \brief Edge visitor for languageVariant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_LanguageVariant(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for uses edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Uses(const logical::Member& begin, const type::Type& end);

      /**
      * \brief Edge visitor for variant edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMember_Variant(const logical::Member& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for accessesAttribute edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end);

      /**
      * \brief Edge visitor for calls edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Calls(const logical::Method& begin, const logical::MethodCall& end);

      /**
      * \brief Edge visitor for canThrow edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_CanThrow(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge  visitor for hasControlFlowBlock edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end);

      /**
      * \brief Edge  visitor for hasParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end);

      /**
      * \brief Edge visitor for instantiates edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Instantiates(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for returns edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Returns(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for throws edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethod_Throws(const logical::Method& begin, const type::Type& end);

      /**
      * \brief Edge visitor for method edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end);

      /**
      * \brief Edge  visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for hasArguments edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac);

      /**
      * \brief Edge visitor for specialize edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end);

      /**
      * \brief Edge visitor for hasType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameter_HasType(const logical::Parameter& begin, const type::Type& end);

      /**
      * \brief Edge visitor for hasMember edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitScope_HasMember(const logical::Scope& begin, const logical::Member& end);

      /**
      * \brief Edge visitor for hasComment edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFile_HasComment(const physical::File& begin, const base::Comment& end);

      /**
      * \brief Edge visitor for includes edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFile_Includes(const physical::File& begin, const physical::File& end);

      /**
      * \brief Edge  visitor for hasFSEntry edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end);

      /**
      * \brief Edge  visitor for contains edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end);

      /**
      * \brief Edge visitor for hasTypeFormer edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end);

      /**
      * \brief Edge visitor for hasParameterType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      * \param ac    [in] The value of the association class.
      */
      virtual void visitTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac);

      /**
      * \brief Edge visitor for hasReturnType edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end);

      /**
      * \brief Edge visitor for refersTo edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end);

    protected:

      /**
      * \internal
      * \brief Converts the attributes of the base::Base node.
      */
      void addAttributeToContent(const base::Base& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::Comment node.
      */
      void addAttributeToContent(const base::Comment& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::Component node.
      */
      void addAttributeToContent(const base::Component& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::ControlFlowBlock node.
      */
      void addAttributeToContent(const base::ControlFlowBlock& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::Named node.
      */
      void addAttributeToContent(const base::Named& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::Attribute node.
      */
      void addAttributeToContent(const logical::Attribute& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::AttributeAccess node.
      */
      void addAttributeToContent(const logical::AttributeAccess& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::Class node.
      */
      void addAttributeToContent(const logical::Class& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::ClassGeneric node.
      */
      void addAttributeToContent(const logical::ClassGeneric& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::ClassGenericInstance node.
      */
      void addAttributeToContent(const logical::ClassGenericInstance& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::ClassGenericSpec node.
      */
      void addAttributeToContent(const logical::ClassGenericSpec& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::Friendship node.
      */
      void addAttributeToContent(const logical::Friendship& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::GenericParameter node.
      */
      void addAttributeToContent(const logical::GenericParameter& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::Member node.
      */
      void addAttributeToContent(const logical::Member& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::Method node.
      */
      void addAttributeToContent(const logical::Method& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::MethodCall node.
      */
      void addAttributeToContent(const logical::MethodCall& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::MethodGeneric node.
      */
      void addAttributeToContent(const logical::MethodGeneric& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::MethodGenericInstance node.
      */
      void addAttributeToContent(const logical::MethodGenericInstance& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::MethodGenericSpec node.
      */
      void addAttributeToContent(const logical::MethodGenericSpec& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::Package node.
      */
      void addAttributeToContent(const logical::Package& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::Parameter node.
      */
      void addAttributeToContent(const logical::Parameter& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the logical::Scope node.
      */
      void addAttributeToContent(const logical::Scope& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the physical::FSEntry node.
      */
      void addAttributeToContent(const physical::FSEntry& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the physical::File node.
      */
      void addAttributeToContent(const physical::File& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the physical::FileSystem node.
      */
      void addAttributeToContent(const physical::FileSystem& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the physical::Folder node.
      */
      void addAttributeToContent(const physical::Folder& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the type::SimpleType node.
      */
      void addAttributeToContent(const type::SimpleType& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the type::Type node.
      */
      void addAttributeToContent(const type::Type& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the type::TypeFormer node.
      */
      void addAttributeToContent(const type::TypeFormer& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the type::TypeFormerArray node.
      */
      void addAttributeToContent(const type::TypeFormerArray& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the type::TypeFormerMethod node.
      */
      void addAttributeToContent(const type::TypeFormerMethod& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the type::TypeFormerNonType node.
      */
      void addAttributeToContent(const type::TypeFormerNonType& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the type::TypeFormerPointer node.
      */
      void addAttributeToContent(const type::TypeFormerPointer& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the type::TypeFormerType node.
      */
      void addAttributeToContent(const type::TypeFormerType& node, std::string& content, bool callVirtualBase);

      /** \internal \brief The ofstream into the DOT graph will be written. */
      columbus::io::GraphmlIO &io;

      /** \internal \brief Internal counter for generating edges. */
      long long edgeCounter;

    private:

      /** \internal \brief It contains ids of the drawed nodes */
      std::map< NodeId, bool> idsToDrawedNodes;

      /** \internal \brief How many edges are should be draw */
      unsigned int maxDrawingDepth;

      /** \internal \brief Edges names to filtering */
      std::set< std::string> edgeFilter;

      /** \internal \brief The contains is not enable to draw */
      std::set< NodeId> nodeFilter;

      /** \internal \brief The contains is not enable to draw */
      bool visitCrossEdge;

      /** \internal \brief It is need to draw into white */
      bool isColorWhite;

      /** \internal \brief Show attributes only of these node types. If it is empty then show all attributes. */
      std::set< std::string> nodeTypeAttributeFilter;

      /** \internal \brief Helper variable for determine is the actual node groupNode it visitEnd */
      NodeId lastVisitedNodeId;

      /** \internal \brief Helper variable for edgeKind grouping */
      std::list<EdgeKind> edgeKindStack;

      /** \internal \brief Helper variable for edgeKind grouping */
      std::list<NodeId> parentNodeStack;

      /** \internal \brief It is need to grouping tree nodes */
      bool isGroupingTreeNodes;

      /** \internal \brief Node type names to filtering out */
      std::set< std::string> nodeTypeFilter;

  }; // VisitorGraphml


}}}
#endif

