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

#ifndef _JAVA_VISITORSTRMAP_H_
#define _JAVA_VISITORSTRMAP_H_

#include <java/inc/java.h>
#include "LinkerHelper.h"


namespace columbus { namespace java { namespace linker {

  class VisitorStrMap : public LinkerHelper, public columbus::java::asg::Visitor {

    public:
      VisitorStrMap(UniqueMap& strMap, StrNodeIdMap& pathMap);

      virtual ~VisitorStrMap();

      virtual void visit(const columbus::java::asg::base::BlockComment& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::base::JavadocComment& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::base::LineComment& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::AnnotationType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::AnnotationTypeElement& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::AnonymousClass& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::Class& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::ClassGeneric& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::CompilationUnit& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::Enum& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::EnumConstant& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::InstanceInitializerBlock& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::Interface& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::InterfaceGeneric& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::Method& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::MethodGeneric& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::Package& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::Parameter& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::StaticInitializerBlock& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::TypeParameter& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::struc::Variable& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::ArrayType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::BooleanType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::ByteType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::CharType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::ClassType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::DoubleType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::ErrorType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::FloatType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::IntType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::LongType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::LowerBoundedWildcardType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::MethodType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::NoType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::NullType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::PackageType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::ParameterizedType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::ShortType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::TypeVariable& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::UnboundedWildcardType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::UnionType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::UpperBoundedWildcardType& node, bool callVirtualBase);
      virtual void visit(const columbus::java::asg::type::VoidType& node, bool callVirtualBase);

  };

}}}

#endif

