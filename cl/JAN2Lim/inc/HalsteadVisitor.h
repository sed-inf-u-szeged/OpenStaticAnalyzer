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

#ifndef __CHECK_HALSTEAD_VISITOR_H__
#define __CHECK_HALSTEAD_VISITOR_H__

#include "lim/inc/lim.h"
#include "java/inc/java.h"

namespace columbus {
  namespace JAN2Lim
  {

    // This visitor calculates Halstead Values and stores them on lim nodes
    class HalsteadVisitor : public java::asg::VisitorAbstractNodes
    {
    public:

      // Defines the mode of operator and operand calculation.
      // This setting tells the halstead calculator whether types and methodinvocations are considered as operators or not.
      enum HalsteadCalculationMode { hcmSimple, hcmTypeIsOperator, hcmMethodUseIsOperator, hcmTypeAndMethodUseIsOperator};

      //
      // INITIALIZATION
      //

      HalsteadVisitor(java::asg::Factory&, bool = false, HalsteadCalculationMode = hcmTypeAndMethodUseIsOperator);

      //
      // VISITORS
      //

      // main logical build
      virtual void visit(const java::asg::struc::MethodDeclaration&, bool);
      virtual void visitEnd(const java::asg::struc::MethodDeclaration&, bool);
      virtual void visit(const java::asg::struc::TypeDeclaration&, bool);
      virtual void visitEnd(const java::asg::struc::TypeDeclaration&, bool);
      virtual void visit(const java::asg::statm::Continue&, bool);
      virtual void visit(const java::asg::statm::For&, bool);
      virtual void visit(const java::asg::expr::NewClass&, bool);
      virtual void visit(const java::asg::expr::NewArray&, bool);
      virtual void visit(const java::asg::statm::Switch&, bool);
      virtual void visit(const java::asg::statm::Assert&, bool);
      virtual void visit(const java::asg::statm::Default&, bool);
      virtual void visit(const java::asg::statm::Synchronized&, bool);
      virtual void visit(const java::asg::struc::NormalMethod&, bool);
      virtual void visit(const java::asg::statm::Do&, bool);
      virtual void visit(const java::asg::statm::If&, bool);
      virtual void visit(const java::asg::struc::NamedDeclaration&, bool);
      virtual void visit(const java::asg::expr::This&, bool);
      virtual void visit(const java::asg::statm::Break&, bool);
      virtual void visit(const java::asg::statm::Throw&, bool);
      virtual void visit(const java::asg::statm::Case&, bool);
      virtual void visit(const java::asg::expr::InstanceOf&, bool);
      virtual void visit(const java::asg::statm::Return&, bool);
      virtual void visit(const java::asg::struc::Variable&, bool);
      virtual void visit(const java::asg::statm::Handler&, bool);
      virtual void visit(const java::asg::statm::Try&, bool);
      virtual void visit(const java::asg::struc::ClassDeclaration&, bool);
      virtual void visitEnd(const java::asg::struc::ClassDeclaration&, bool);
      virtual void visit(const java::asg::expr::Super&, bool);
      virtual void visit(const java::asg::statm::While&, bool);
      virtual void visit(const java::asg::struc::Interface&, bool);
      virtual void visit(const java::asg::expr::InfixExpression&, bool);
      virtual void visit(const java::asg::expr::Assignment&, bool);
      virtual void visit(const java::asg::expr::Binary&, bool);
      virtual void visit(const java::asg::expr::ParenthesizedExpression&, bool);
      virtual void visit(const java::asg::statm::Block&, bool);
      virtual void visit(const java::asg::expr::PostfixExpression&, bool);
      virtual void visit(const java::asg::expr::PrefixExpression&, bool);
      virtual void visit(const java::asg::expr::TypeCast&, bool);
      virtual void visit(const java::asg::expr::MethodInvocation&, bool);
      virtual void visit(const java::asg::expr::Conditional&, bool);
      virtual void visit(const java::asg::base::Base&, bool);
      virtual void visit(const java::asg::statm::Jump&, bool);
      virtual void visit(const java::asg::statm::BasicFor&, bool);
      virtual void visit(const java::asg::statm::EnhancedFor&, bool);
      virtual void visit(const java::asg::struc::GenericDeclaration&, bool);
      virtual void visit(const java::asg::expr::Identifier&, bool);
      virtual void visit(const java::asg::expr::Literal&, bool);
      virtual void visit(const java::asg::statm::LabeledStatement&, bool);
      virtual void visit(const java::asg::struc::VariableDeclaration&, bool);
      virtual void visit(const java::asg::expr::TypeExpression&, bool);
      virtual void visit(const java::asg::expr::PrimitiveTypeExpression&, bool);
      virtual void visit(const java::asg::expr::SimpleTypeExpression&, bool);
      virtual void visit(const java::asg::expr::ArrayTypeExpression&, bool);
      virtual void visit(const java::asg::expr::TypeApplyExpression&, bool);
      virtual void visit(const java::asg::expr::TypeUnionExpression&, bool);
      virtual void visit(const java::asg::expr::WildcardExpression&, bool);
      virtual void visit(const java::asg::expr::QualifiedTypeExpression&, bool);

    public:

      struct HalsteadInfo
      {
        HalsteadInfo() {}

        HalsteadInfo(unsigned int n1, unsigned int n2, unsigned int N1, unsigned int N2) :
          n1(n1)
          , n2(n2)
          , N1(N1)
          , N2(N2)
        {}

        unsigned int n1 = 0; // distinct operators
        unsigned int n2 = 0; // distinct operands
        unsigned int N1 = 0; // total operators
        unsigned int N2 = 0; // total operands
      };

      // JAN2LimVisitor needs this data to assign halstead values to lim nodes
      std::map<NodeId, HalsteadVisitor::HalsteadInfo> getHalsteadValues();

    private:

      //
      // DATA
      //

      struct NodeInfo
      {
        NodeInfo() :
          node(NULL)
          , occurrence()
          , name()
        {}

        NodeInfo(const java::asg::base::Base *node, unsigned int occurrence, std::string name) :
          node(node)
          , occurrence(occurrence)
          , name(name)
        {}

        const java::asg::base::Base *node;

        unsigned int occurrence;
        std::string name;
      };

      struct MethodInfo
      {
        MethodInfo() :
          method(NULL)
          , halsteadInfo()
          , operatorKinds()
          , methodInvocations()
          , identifiers()
          , labels()
          , literals()
        {}

        const java::asg::struc::MethodDeclaration *method;
        HalsteadInfo halsteadInfo;

        std::map<NodeId, unsigned int> operatorNodes;
        std::map<std::string, unsigned int> operatorKinds;
        std::map<std::string, unsigned int> methodInvocations;
        std::map<std::string, unsigned int> identifiers;
        std::map<std::string, unsigned int> labels;
        std::vector<const java::asg::expr::Literal* > literals; // mostly used for debug purposes, could use an int instead

      };

      enum OperatorTypes {
        opkAbstract,
        opkContinue,
        opkFor,
        opkNew,
        opkSwitch,
        opkAssert,
        opkDefault,
        opkGoto,
        opkPackage,
        opkSynchronized,
        opkBoolean,
        opkDo,
        opkIf,
        opkPrivate,
        opkThis,
        opkBreak,
        opkDouble,
        opkImplements,
        opkProtected,
        opkThrow,
        opkByte,
        opkElse,
        opkImport,
        opkPublic,
        opkThrows,
        opkCase,
        opkEnum,
        opkInstanceof,
        opkReturn,
        opkTransient,
        opkCatch,
        opkExtends,
        opkInt,
        opkShort,
        opkTry,
        opkChar,
        opkFinal,
        opkInterface,
        opkStatic,
        opkVoid,
        opkClass,
        opkFinally,
        opkLong,
        opkStrictfp,
        opkVolatile,
        opkConst,
        opkFloat,
        opkNative,
        opkSuper,
        opkWhile,
        opkSemicolon,
        opkLabel,
        opkSeparator,
        opkArray,
        opkDiamond,
        opkPipe,
        opkTypeQualifier, // type.subtype
        opkMethodInvocation,
        opkGenericAnd, // & e.g.: public <V, W extends Enum<W> & Comparable<W>> void foo( V v, W w )
        opkGenericExtends
      };

      java::asg::Factory& javaFactory;                ///< Reference to the (current) JAN factory
      std::stack<MethodInfo> methodStack;             ///< Stack for the current Method info
      std::stack<NodeId> classStack;                  ///< Stack for the current class id
      bool countSeparators;                           ///< Set separator counting enabled/disabled
      HalsteadCalculationMode halsteadMode;           ///< Sets the calculation mode for halstead visitor
      std::map<NodeId, HalsteadInfo> halsteadInfos;   ///< Stores the halstead data for each method


      //
      // UTIL
      //

      std::string getEnumText(java::asg::AccessibilityKind);
      std::string getEnumText(java::asg::AssignmentOperatorKind);
      std::string getEnumText(java::asg::InfixOperatorKind);
      std::string getEnumText(java::asg::PostfixOperatorKind);
      std::string getEnumText(java::asg::PrefixOperatorKind);
      std::string getEnumText(java::asg::PrimitiveTypeKind);
      std::string getEnumText(java::asg::NodeKind);
      std::string getEnumText(java::asg::TypeBoundKind);
      std::string getEnumText(OperatorTypes);

      void incOperands(const java::asg::base::Base&);
      void incOperators(std::string);
      void incOperators(std::string, unsigned int);
      void incMethodInvocations(std::string, java::asg::struc::MethodDeclaration*);
      void incType(const java::asg::base::Base&);
      void printMethodInfo(const MethodInfo&);
      bool needsSemicolon(const java::asg::base::Base&);
      bool ignore();

    };
  }
}

#endif
