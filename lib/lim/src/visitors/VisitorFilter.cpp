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

#include "lim/inc/lim.h"


namespace columbus { namespace lim { namespace asg {
VisitorFilter::VisitorFilter(bool filter) : Visitor() ,selector( filter?&Factory::setFilteredThisNodeOnly : &Factory::setNotFilteredThisNodeOnly) {
}

VisitorFilter::~VisitorFilter() {
}

void VisitorFilter::visitEnd(const base::Comment& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const base::Component& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const base::ControlFlowBlock& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::Attribute& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::AttributeAccess& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::Class& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::ClassGeneric& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::ClassGenericInstance& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::ClassGenericSpec& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::Friendship& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::GenericParameter& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::Method& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::MethodCall& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::MethodGeneric& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::MethodGenericInstance& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::MethodGenericSpec& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::Package& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const logical::Parameter& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const physical::File& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const physical::FileSystem& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const physical::Folder& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::SimpleType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::Type& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::TypeFormerArray& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::TypeFormerMethod& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::TypeFormerNonType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::TypeFormerPointer& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const type::TypeFormerType& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}


}}}
