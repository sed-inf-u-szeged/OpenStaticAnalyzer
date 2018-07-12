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

#include <java/inc/java.h>
#include "../inc/VisitorStrMap.h"

using namespace columbus::java::asg;


namespace columbus { namespace java { namespace linker {

VisitorStrMap::VisitorStrMap(UniqueMap& strMap, StrNodeIdMap& pathMap) : LinkerHelper(strMap, pathMap) {
}

VisitorStrMap::~VisitorStrMap() {
}

void VisitorStrMap::visit(const base::BlockComment& node, bool callVirtualBase) {
  strMap.BlockComments[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const base::JavadocComment& node, bool callVirtualBase) {
  strMap.JavadocComments[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const base::LineComment& node, bool callVirtualBase) {
  strMap.LineComments[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const struc::AnnotationType& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::AnnotationTypeElement& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::AnonymousClass& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::Class& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::ClassGeneric& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::CompilationUnit& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::Enum& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::EnumConstant& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::InstanceInitializerBlock& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::Interface& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::InterfaceGeneric& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::Method& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::MethodGeneric& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::Package& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::Parameter& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::StaticInitializerBlock& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::TypeParameter& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const struc::Variable& node, bool callVirtualBase) {
  storeUniqueString(node);
}

void VisitorStrMap::visit(const type::ArrayType& node, bool callVirtualBase) {
  strMap.ArrayTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::BooleanType& node, bool callVirtualBase) {
  strMap.BooleanTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::ByteType& node, bool callVirtualBase) {
  strMap.ByteTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::CharType& node, bool callVirtualBase) {
  strMap.CharTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::ClassType& node, bool callVirtualBase) {
  strMap.ClassTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::DoubleType& node, bool callVirtualBase) {
  strMap.DoubleTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::ErrorType& node, bool callVirtualBase) {
  strMap.ErrorTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::FloatType& node, bool callVirtualBase) {
  strMap.FloatTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::IntType& node, bool callVirtualBase) {
  strMap.IntTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::LongType& node, bool callVirtualBase) {
  strMap.LongTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::LowerBoundedWildcardType& node, bool callVirtualBase) {
  strMap.LowerBoundedWildcardTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::MethodType& node, bool callVirtualBase) {
  strMap.MethodTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::NoType& node, bool callVirtualBase) {
  strMap.NoTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::NullType& node, bool callVirtualBase) {
  strMap.NullTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::PackageType& node, bool callVirtualBase) {
  strMap.PackageTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::ParameterizedType& node, bool callVirtualBase) {
  strMap.ParameterizedTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::ShortType& node, bool callVirtualBase) {
  strMap.ShortTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::TypeVariable& node, bool callVirtualBase) {
  strMap.TypeVariables[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::UnboundedWildcardType& node, bool callVirtualBase) {
  strMap.UnboundedWildcardTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::UnionType& node, bool callVirtualBase) {
  strMap.UnionTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::UpperBoundedWildcardType& node, bool callVirtualBase) {
  strMap.UpperBoundedWildcardTypes[getUniqueString(node)] = node.getId();
}

void VisitorStrMap::visit(const type::VoidType& node, bool callVirtualBase) {
  strMap.VoidTypes[getUniqueString(node)] = node.getId();
}


}}}

