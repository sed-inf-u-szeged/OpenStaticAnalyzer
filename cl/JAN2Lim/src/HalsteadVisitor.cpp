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

#include "../inc/HalsteadVisitor.h"
#include "../inc/messages.h"
#include <numeric>

#define VISIT_BEGIN(node,callVirtualBase,visitName) \
  VisitorAbstractNodes::visit( node, callVirtualBase ); \
  if ( common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDDebug ) \
  { \
    common::WriteMsg::write( CMSG_VISIT_BEGIN, visitName, node.getId(), 0 ); \
  }

#define VISIT_END(node,callVirtualBase,visitName) \
  VisitorAbstractNodes::visitEnd( node, callVirtualBase );

#define VISIT_END_FIRST(node,visitName) \
  if ( common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDDebug ) \
  { \
    common::WriteMsg::write( CMSG_VISIT_END, visitName, node.getId(), 0 ); \
  }

namespace columbus {
  namespace JAN2Lim
  {

    HalsteadVisitor::HalsteadVisitor(columbus::java::asg::Factory& javaFact, bool countSeparators, HalsteadCalculationMode hcm) :
      javaFactory(javaFact), countSeparators(countSeparators), halsteadMode(hcm) {
    }

    // enum -> string converters

    std::string HalsteadVisitor::getEnumText(java::asg::AccessibilityKind kind)
    {
      return java::asg::Common::toString(kind);
    }

    std::string HalsteadVisitor::getEnumText(java::asg::AssignmentOperatorKind kind)
    {
      return java::asg::Common::toString(kind);
    }

    std::string HalsteadVisitor::getEnumText(java::asg::InfixOperatorKind kind)
    {
      return java::asg::Common::toString(kind);
    }

    std::string HalsteadVisitor::getEnumText(java::asg::PostfixOperatorKind kind)
    {
      return java::asg::Common::toString(kind);
    }

    std::string HalsteadVisitor::getEnumText(java::asg::PrefixOperatorKind kind)
    {
      return java::asg::Common::toString(kind);
    }

    std::string HalsteadVisitor::getEnumText(java::asg::PrimitiveTypeKind kind)
    {
      return java::asg::Common::toString(kind);
    }

    std::string HalsteadVisitor::getEnumText(java::asg::NodeKind kind)
    {
      return java::asg::Common::toString(kind);
    }

    std::string HalsteadVisitor::getEnumText(java::asg::TypeBoundKind kind)
    {
      return java::asg::Common::toString(kind);
    }

    std::string HalsteadVisitor::getEnumText(OperatorTypes kind)
    {
      switch (kind) {
        case opkAbstract: return "opkAbstract";
        case opkContinue: return "opkContinue";
        case opkFor: return "opkFor";
        case opkNew: return "opkNew";
        case opkSwitch: return "opkSwitch";
        case opkAssert: return "opkAssert";
        case opkDefault: return "opkDefault";
        case opkGoto: return "opkGoto";
        case opkPackage: return "opkPackage";
        case opkSynchronized: return "opkSynchronized";
        case opkBoolean: return "opkBoolean";
        case opkDo: return "opkDo";
        case opkIf: return "opkIf";
        case opkPrivate: return "opkPrivate";
        case opkThis: return "opkThis";
        case opkBreak: return "opkBreak";
        case opkDouble: return "opkDouble";
        case opkImplements: return "opkImplements";
        case opkProtected: return "opkProtected";
        case opkThrow: return "opkThrow";
        case opkByte: return "opkByte";
        case opkElse: return "opkElse";
        case opkImport: return "opkImport";
        case opkPublic: return "opkPublic";
        case opkThrows: return "opkThrows";
        case opkCase: return "opkCase";
        case opkEnum: return "opkEnum";
        case opkInstanceof: return "opkInstanceof";
        case opkReturn: return "opkReturn";
        case opkTransient: return "opkTransient";
        case opkCatch: return "opkCatch";
        case opkExtends: return "opkExtends";
        case opkInt: return "opkInt";
        case opkShort: return "opkShort";
        case opkTry: return "opkTry";
        case opkChar: return "opkChar";
        case opkFinal: return "opkFinal";
        case opkInterface: return "opkInterface";
        case opkStatic: return "opkStatic";
        case opkVoid: return "opkVoid";
        case opkClass: return "opkClass";
        case opkFinally: return "opkFinally";
        case opkLong: return "opkLong";
        case opkStrictfp: return "opkStrictfp";
        case opkVolatile: return "opkVolatile";
        case opkConst: return "opkConst";
        case opkFloat: return "opkFloat";
        case opkNative: return "opkNative";
        case opkSuper: return "opkSuper";
        case opkWhile: return "opkWhile";
        case opkSemicolon: return "opkSemicolon";
        case opkLabel: return "opkLabel";
        case opkSeparator: return "opkSeparator";
        case opkArray: return "opkArray";
        case opkDiamond: return "opkDiamond";
        case opkPipe: return "opkPipe";
        case opkTypeQualifier: return "opkTypeQualifier";
        case opkMethodInvocation: return "opkMethodInvocation";
        case opkGenericAnd: return "opkGenericAnd";
        case opkGenericExtends: return "opkGenericExtends";
        default: throw columbus::Exception(COLUMBUS_LOCATION, "Invalid OperatorTypes kind");
      }
    }

    // operand/operator counter

    bool HalsteadVisitor::ignore() {
      if (methodStack.empty()) return true;
      MethodInfo& mi = methodStack.top();
      if (mi.method->getIsToolGenerated()) return true;

      if (classStack.empty()) return true;
      java::asg::base::Base* parent = mi.method->getParent();
      if (parent == NULL) return true;
      if (parent->getId() != classStack.top()) return true;

      return false;
    }

    void HalsteadVisitor::incOperands(const java::asg::base::Base& operand)
    {
      if (ignore()) return;

      MethodInfo& mi = methodStack.top();
      if (java::asg::Common::getIsIdentifier(operand)) {
        const java::asg::expr::Identifier& i = dynamic_cast<const java::asg::expr::Identifier&>(operand);
        if (i.getRefersTo() != NULL) {
          std::string compactId = i.getName() + "<" + java::asg::Common::getLongName(*(i.getRefersTo())) + ">";
          mi.identifiers[compactId]++;
        }
      }
      else if (java::asg::Common::getIsLabeledStatement(operand)) {
        mi.labels[dynamic_cast<const java::asg::statm::LabeledStatement&>(operand).getLabel()]++;
      }
      else if (java::asg::Common::getIsJump(operand)) {
        mi.labels[dynamic_cast<const java::asg::statm::Jump&>(operand).getLabel()]++;
      }
      else if (java::asg::Common::getIsLiteral(operand)) {
        const java::asg::expr::Literal* i = dynamic_cast<const java::asg::expr::Literal*>(&operand);
        mi.literals.push_back(i);
      }
      else if (java::asg::Common::getIsMethodDeclaration(operand)) {
        const java::asg::struc::MethodDeclaration& meth = dynamic_cast<const java::asg::struc::MethodDeclaration&>(operand);
        std::string compactId = java::asg::Common::getLongName(meth);
        mi.identifiers[compactId]++;
      }
      else if (java::asg::Common::getIsParameter(operand)) {
        const java::asg::struc::Parameter& par = dynamic_cast<const java::asg::struc::Parameter&>(operand);
        std::string compactId = par.getName() + "<" + java::asg::Common::getLongName(par) + ">";
        mi.identifiers[compactId]++;
      }
      else if (java::asg::Common::getIsVariable(operand)) {
        const java::asg::struc::Variable& var = dynamic_cast<const java::asg::struc::Variable&>(operand);
        std::string compactId = var.getName() + "<" + java::asg::Common::getLongName(var) + ">";
        mi.identifiers[compactId]++;
      }
      else if (java::asg::Common::getIsTypeDeclaration(operand)) {
        mi.identifiers[java::asg::Common::getLongName(operand)]++;
      }
      else if (java::asg::Common::getIsType(operand)) {
        mi.identifiers[java::asg::Common::getLongName(operand)]++;
      }
      else if (java::asg::Common::getIsTypeParameter(operand)) {
        const java::asg::struc::TypeParameter& par = dynamic_cast<const java::asg::struc::TypeParameter&>(operand);
        std::string compactId = par.getName() + "<" + java::asg::Common::getLongName(par) + ">";
        mi.identifiers[compactId]++;
      }
      else {
        throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_UNEXPECTED_TYPE(operand.getId(), operand.getNodeKind()));
      }

      return;
    }

    void HalsteadVisitor::incOperators(std::string enumKind)
    {
      incOperators(enumKind, 1);
      return;
    }

    void HalsteadVisitor::incOperators(std::string enumKind, unsigned int times)
    {
      if (ignore()) return;
      if (times <= 0) return;
      if (!countSeparators && enumKind == getEnumText(opkSeparator)) return;

      MethodInfo& mi = methodStack.top();
      mi.operatorKinds[enumKind] += times;

      return;
    }

    void HalsteadVisitor::incMethodInvocations(std::string methodInvocationName, java::asg::struc::MethodDeclaration* method)
    {
      if (ignore()) return;

      if (halsteadMode == hcmMethodUseIsOperator || halsteadMode == hcmTypeAndMethodUseIsOperator) {
        incOperators(getEnumText(opkMethodInvocation));
      }
      MethodInfo& mi = methodStack.top();
      mi.methodInvocations[java::asg::Common::getLongName(*method)]++;

      return;
    }

    void HalsteadVisitor::incType(const java::asg::base::Base& node)
    {
      if (ignore()) return;

      MethodInfo& mi = methodStack.top();
      if (halsteadMode == hcmTypeIsOperator || halsteadMode == hcmTypeAndMethodUseIsOperator) {
        mi.operatorNodes[node.getId()]++;
      }
      else {
        incOperands(node);
      }

      return;
    }

    // needs semicolon or not

    bool getIsMemberWithTypeDeclarationParent(const java::asg::base::Base& node, java::asg::base::Base& parent) {
      return java::asg::Common::getIsTypeDeclaration(parent) && java::asg::Common::getIsMember(node) && !java::asg::Common::getIsInitializerBlock(node);
    }

    bool getIsIfSubstatementOrFalseSubstatement(const java::asg::base::Base& node, const java::asg::base::Base& parent) {
      return java::asg::Common::getIsIf(parent)
        && (dynamic_cast<const java::asg::statm::If&>(parent).getSubstatement() == &node
          || dynamic_cast<const java::asg::statm::If&>(parent).getFalseSubstatement() == &node);
    }

    bool getIsIfFalseSubstatementWithoutComment(const java::asg::statm::If& node, java::asg::base::Base& parent) {
      return java::asg::Common::getIsIf(parent)
        && (dynamic_cast<const java::asg::statm::If&>(parent).getFalseSubstatement() == &node
          && node.getCommentsIsEmpty());
    }

    bool getIsIterationSubstatement(const java::asg::base::Base& node, java::asg::base::Base& parent) {
      return java::asg::Common::getIsIteration(parent)
        && dynamic_cast<const java::asg::statm::Iteration&>(parent).getSubstatement() == &node;
    }

    bool getHasCaseParentAndNotInExpression(const java::asg::base::Base& node, java::asg::base::Base& parent) {
      return java::asg::Common::getIsCase(parent)
        && dynamic_cast<const java::asg::statm::Case&>(parent).getExpression() != &node;
    }

    bool getIsMethodWithoutBody(const java::asg::base::Base& node) {
      return java::asg::Common::getIsNormalMethod(node)
        && dynamic_cast<const java::asg::struc::NormalMethod&>(node).getBody() == NULL;
    }

    bool HalsteadVisitor::needsSemicolon(const java::asg::base::Base& node)
    {
      java::asg::base::Base* parent = node.getParent();
      if (parent == NULL) return false;

      if (java::asg::Common::getIsImport(node)
        || java::asg::Common::getIsPackageDeclaration(node) || java::asg::Common::getIsDo(node)
        || getIsMethodWithoutBody(node)) {
        return true;
      }

      if (java::asg::Common::getIsBlock(node) || java::asg::Common::getIsIteration(node)
        || java::asg::Common::getIsIf(node) || java::asg::Common::getIsTypeDeclaration(node)
        || java::asg::Common::getIsTry(node) || java::asg::Common::getIsNormalMethod(node)
        || java::asg::Common::getIsSwitch(node) || java::asg::Common::getIsEnumConstant(node)
        || java::asg::Common::getIsLabeledStatement(node)
        || java::asg::Common::getIsSynchronized(node)) {
        return false;
      }

      if (getHasCaseParentAndNotInExpression(node, *parent)
        || getIsIterationSubstatement(node, *parent)
        || getIsIfSubstatementOrFalseSubstatement(node, *parent)
        || java::asg::Common::getIsBlock(*parent)
        || java::asg::Common::getIsDefault(*parent)
        || getIsMemberWithTypeDeclarationParent(node, *parent)) {
        return true;
      }

      return false;
    }

    // debug info

    void HalsteadVisitor::printMethodInfo(const MethodInfo& mi) {
      // describe
      using namespace std;

      std::cout << mi.method->getName() << "() -> N1=" << mi.halsteadInfo.N1 << ", N2=" << mi.halsteadInfo.N2 << ", n1=" << mi.halsteadInfo.n1 << ", n2=" << mi.halsteadInfo.n2 << std::endl;
      cout << "\tOperators: ";

      for (auto const &entry : mi.operatorKinds) {
        cout << entry.first;
        if (entry.second > 1) {
          cout << "(x" << entry.second << ")";
        }
        cout << ", ";
      }

      if (halsteadMode == hcmMethodUseIsOperator || halsteadMode == hcmTypeAndMethodUseIsOperator) {
        for (auto const &entry : mi.methodInvocations) {
          cout << entry.first << "()";
          if (entry.second > 1) {
            cout << "(x" << entry.second << ")";
          }
          cout << ", ";
        }
      }

      for (auto const &entry : mi.operatorNodes) {
        std::string name;
        java::asg::base::Base& node = javaFactory.getRef(entry.first);
        if (java::asg::Common::getIsClassType(node)) {
          java::asg::struc::TypeDeclaration* td = dynamic_cast<const java::asg::type::ClassType*>(&node)->getRefersTo();
          name = java::asg::Common::getLongName(*td);
        }
        else if (java::asg::Common::getIsTypeVariable(node)) {
          java::asg::struc::TypeParameter* t = dynamic_cast<const java::asg::type::TypeVariable*>(&node)->getRefersTo();
          name = "<" + t->getName() + ">" + java::asg::Common::getLongName(*t);
        }
        else {
          name = java::asg::Common::getLongName(javaFactory.getRef(entry.first));
        }
        cout << name;
        if (entry.second > 1) {
          cout << "(x" << entry.second << ")";
        }
        cout << ", ";
      }
      cout << endl;

      cout << "\tOperands: ";
      auto N2List = { mi.identifiers, mi.labels };
      for (auto &map : N2List) {
        for (auto const &entry : map) {
          cout << entry.first;
          if (entry.second > 1) {
            cout << "(x" << entry.second << ")";
          }
          cout << ", ";
        }
      }
      if (halsteadMode != hcmMethodUseIsOperator && halsteadMode != hcmTypeAndMethodUseIsOperator) {
        for (auto const &entry : mi.methodInvocations) {
          cout << entry.first << "()";
          if (entry.second > 1) {
            cout << "(x" << entry.second << ")";
          }
          cout << ", ";
        }
      }
      for (const java::asg::expr::Literal* literal : mi.literals) {
        if (java::asg::Common::getIsBooleanLiteral(*literal)) {
          bool ean = dynamic_cast<const java::asg::expr::BooleanLiteral*>(literal)->getBooleanValue();
          cout << (ean ? "true" : "false");
        }
        else if (java::asg::Common::getIsCharacterLiteral(*literal)) {
          wchar_t str = dynamic_cast<const java::asg::expr::CharacterLiteral*>(literal)->getCharValue();
          cout << str;
        }
        else if (java::asg::Common::getIsNumberLiteral(*literal)) {
          std::string str = dynamic_cast<const java::asg::expr::NumberLiteral*>(literal)->getValue();
          cout << str;
        }
        else if (java::asg::Common::getIsStringLiteral(*literal)) {
          std::string str = dynamic_cast<const java::asg::expr::StringLiteral*>(literal)->getValue();
          cout << str;
        }
        else if (java::asg::Common::getIsNullLiteral(*literal)) {
          cout << "<null>";
        }
        else if (java::asg::Common::getIsClassLiteral(*literal)) {
          cout << ".class";
        }
        else {
          throw columbus::Exception(COLUMBUS_LOCATION, "Unhandled Literal type: " + literal->getNodeKind());
        }
        cout << ", ";
      }
      cout << endl;

      return;
    }

    std::map<NodeId, HalsteadVisitor::HalsteadInfo> HalsteadVisitor::getHalsteadValues() {
      return halsteadInfos;
    }

    //
    // VISITORS
    //

    void HalsteadVisitor::visit(const java::asg::struc::MethodDeclaration& node, bool callVirtualBase)
    {
      if (!node.getIsCompilerGenerated()) {
        methodStack.push(MethodInfo());
        methodStack.top().method = &node;

        incOperands(node);
      }

      if (node.getIsAbstract()) {
        incOperators(getEnumText(opkAbstract));
      }
      if (node.getIsStrictfp()) {
        incOperators(getEnumText(opkStrictfp));
      }
      VISIT_BEGIN(node, callVirtualBase, "MethodDeclaration");
    }

    template<typename T> unsigned int sumValues(T map) {
      return std::accumulate(map.begin(), map.end(), 0, [](const unsigned int previous, typename T::value_type p) { return previous + p.second; });
    }

    void HalsteadVisitor::visitEnd(const java::asg::struc::MethodDeclaration& node, bool callVirtualBase)
    {
      VISIT_END_FIRST(node, "MethodDeclaration");

      if (!node.getIsCompilerGenerated()) {
        MethodInfo& mi = methodStack.top();

        // calculating n
        mi.halsteadInfo.n1 = mi.operatorKinds.size() + mi.operatorNodes.size();
        mi.halsteadInfo.n2 = mi.identifiers.size() + mi.labels.size() + mi.literals.size();
        if (halsteadMode == hcmMethodUseIsOperator || halsteadMode == hcmTypeAndMethodUseIsOperator) {
          mi.halsteadInfo.n1 += mi.methodInvocations.size();
        }
        else {
          mi.halsteadInfo.n2 += mi.methodInvocations.size();
        }

        // calculating N
        mi.halsteadInfo.N1 += sumValues(mi.operatorKinds);
        mi.halsteadInfo.N1 += sumValues(mi.operatorNodes);

        auto N2List = { mi.identifiers, mi.labels };
        for (auto &map : N2List) {
          for (auto const &entry : map) {
            mi.halsteadInfo.N2 += entry.second;
          }
        }
        mi.halsteadInfo.N2 += mi.literals.size();
        if (halsteadMode == hcmMethodUseIsOperator || halsteadMode == hcmTypeAndMethodUseIsOperator) {
          for (auto const &entry : mi.methodInvocations) {
            mi.halsteadInfo.N1 += entry.second;
          }
        }
        else {
          for (auto const &entry : mi.methodInvocations) {
            mi.halsteadInfo.N2 += entry.second;
          }
        }

        if (common::WriteMsg::getMessageLevel() >= common::WriteMsg::mlDDebug) {
          printMethodInfo(mi);
        }

        halsteadInfos[node.getId()] = mi.halsteadInfo;
        methodStack.pop();
      }

      VISIT_END(node, callVirtualBase, "MethodDeclaration");
    }


    void HalsteadVisitor::visit(const java::asg::struc::TypeDeclaration& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "TypeDeclaration");

      if (node.getIsAbstract()) {
        incOperators(getEnumText(opkAbstract));
      }
      if (node.getIsStrictfp()) {
        incOperators(getEnumText(opkStrictfp));
      }
      if (!node.getSuperInterfacesIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getSuperInterfacesSize() - 1);
      }
      incOperands(node);
    }

    void HalsteadVisitor::visitEnd(const java::asg::struc::TypeDeclaration& node, bool callVirtualBase)
    {
      VISIT_END_FIRST(node, "TypeDeclaration");
      VISIT_END(node, callVirtualBase, "TypeDeclaration");
    }

    void HalsteadVisitor::visit(const java::asg::statm::Continue& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Continue");

      incOperators(getEnumText(opkContinue));
    }

    void HalsteadVisitor::visit(const java::asg::statm::For& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "For");

      incOperators(getEnumText(opkFor));
    }

    void HalsteadVisitor::visit(const java::asg::expr::NewClass& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "NewClass");

      incOperators(getEnumText(opkNew));
      if (!node.getArgumentsIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getArgumentsIsEmpty() - 1);
      }
      if (!node.getTypeArgumentsIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getTypeArgumentsSize() - 1);
      }

      java::asg::struc::NormalMethod* constructor = node.getConstructor();
      if (constructor != NULL) {
        incMethodInvocations(constructor->getName(), constructor);
      }
    }

    void HalsteadVisitor::visit(const java::asg::expr::NewArray& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "NewArray");

      incOperators(getEnumText(opkNew));
      if (!node.getInitializersIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getInitializersSize() - 1);
      }
      incOperators(getEnumText(opkArray));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Switch& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Switch");

      incOperators(getEnumText(opkSwitch));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Assert& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Assert");

      incOperators(getEnumText(opkAssert));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Default& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Default");

      incOperators(getEnumText(opkDefault));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Synchronized& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Synchronized");

      incOperators(getEnumText(opkSynchronized));
    }

    void HalsteadVisitor::visit(const java::asg::struc::NormalMethod& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "NormalMethod");

      if (node.getIsSynchronized()) {
        incOperators(getEnumText(opkSynchronized));
      }
      if (!node.getThrownExceptionsIsEmpty()) {
        incOperators(getEnumText(opkThrows));
      }
      if (node.getIsNative()) {
        incOperators(getEnumText(opkNative));
      }
      if (!node.getParametersIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getParametersSize() - 1);
        for (java::asg::ListIterator<java::asg::struc::Parameter> it = node.getParametersListIteratorBegin(); it != node.getParametersListIteratorEnd(); ++it) {
          incOperands(*it);
        }
      }
      if (!node.getThrownExceptionsIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getThrownExceptionsSize() - 1);
      }
    }

    void HalsteadVisitor::visit(const java::asg::statm::Do& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Do");

      incOperators(getEnumText(opkDo));
    }

    void HalsteadVisitor::visit(const java::asg::statm::If& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "If");

      incOperators(getEnumText(opkIf));
      if (node.getFalseSubstatement() != NULL) {
        incOperators(getEnumText(opkElse));
      }
    }

    void HalsteadVisitor::visit(const java::asg::struc::NamedDeclaration& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "NamedDeclaration");

      if (node.getAccessibility() != java::asg::ackNone) {
        incOperators(getEnumText(node.getAccessibility()));
      }
      if (node.getIsFinal()) {
        incOperators(getEnumText(opkFinal));
      }
      if (node.getIsStatic()) {
        incOperators(getEnumText(opkStatic));
      }
    }

    void HalsteadVisitor::visit(const java::asg::expr::This& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "This");

      incOperators(getEnumText(opkThis));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Break& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Break");

      incOperators(getEnumText(opkBreak));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Throw& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Throw");

      incOperators(getEnumText(opkThrow));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Case& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Case");

      incOperators(getEnumText(opkCase));
    }

    void HalsteadVisitor::visit(const java::asg::expr::InstanceOf& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "InstanceOf");

      incOperators(getEnumText(opkInstanceof));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Return& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Return");

      incOperators(getEnumText(opkReturn));
    }

    void HalsteadVisitor::visit(const java::asg::struc::Variable& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Variable");

      incOperands(node);
      if (node.getInitialValue() != NULL) {
        incOperators(getEnumText(java::asg::askAssign));
      }
      if (node.getIsTransient()) {
        incOperators(getEnumText(opkTransient));
      }
      if (node.getIsVolatile()) {
        incOperators(getEnumText(opkVolatile));
      }
    }

    void HalsteadVisitor::visit(const java::asg::statm::Handler& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Handler");

      if (node.getParameter() != NULL) {
        incOperands(*(node.getParameter()));
      }

      incOperators(getEnumText(opkCatch));
    }

    void HalsteadVisitor::visit(const java::asg::statm::Try& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Try");

      incOperators(getEnumText(opkTry));
      if (node.getFinallyBlock() != NULL) {
        incOperators(getEnumText(opkFinally));
      }
    }

    void HalsteadVisitor::visit(const java::asg::struc::ClassDeclaration& node, bool callVirtualBase)
    {
      if (!java::asg::Common::getIsAnonymousClass(node)) {
        incOperators(getEnumText(opkClass));
      }
      classStack.push(node.getId());
      VISIT_BEGIN(node, callVirtualBase, "ClassDeclaration");
    }

    void HalsteadVisitor::visitEnd(const java::asg::struc::ClassDeclaration& node, bool callVirtualBase)
    {
      VISIT_END_FIRST(node, "ClassDeclaration");
      VISIT_END(node, callVirtualBase, "ClassDeclaration");
      classStack.pop();
    }

    void HalsteadVisitor::visit(const java::asg::expr::Super& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Super");

      incOperators(getEnumText(opkSuper));
    }

    void HalsteadVisitor::visit(const java::asg::statm::While& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "While");

      incOperators(getEnumText(opkWhile));
    }

    void HalsteadVisitor::visit(const java::asg::struc::Interface& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Interface");

      incOperators(getEnumText(opkInterface));
    }

    /* -------------------------------------------------------------------------- ------------------------------------------------------------------------- */

    void HalsteadVisitor::visit(const java::asg::expr::InfixExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "InfixExpression");

      incOperators(getEnumText(node.getOperator()));
    }

    void HalsteadVisitor::visit(const java::asg::expr::Assignment& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Assignment");

      incOperators(getEnumText(node.getOperator()));
    }

    void HalsteadVisitor::visit(const java::asg::expr::Binary& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Binary");

      if (!(java::asg::Common::getIsInfixExpression(node) || java::asg::Common::getIsAssignment(node))) {
        incOperators(getEnumText(node.getNodeKind()));
      }
    }

    /* -------------------------------------------------------------------------- ------------------------------------------------------------------------- */

    void HalsteadVisitor::visit(const java::asg::expr::ParenthesizedExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "ParenthesizedExpression");

      const java::asg::base::Base* parent = node.getParent();

      if (parent != NULL && !(java::asg::Common::getIsFor(*parent)
        || java::asg::Common::getIsIf(*parent)
        || java::asg::Common::getIsSwitch(*parent)
        || java::asg::Common::getIsWhile(*parent)
        || java::asg::Common::getIsDo(*parent)
        || java::asg::Common::getIsTry(*parent))) {
        incOperators(getEnumText(node.getNodeKind()));
      }
    }

    void HalsteadVisitor::visit(const java::asg::statm::Block& node, bool callVirtualBase) {
      VISIT_BEGIN(node, callVirtualBase, "Block");

      const java::asg::base::Base* parent = node.getParent();

      if (parent != NULL && !(java::asg::Common::getIsSwitch(*parent)
        || java::asg::Common::getIsTry(*parent)
        || java::asg::Common::getIsHandler(*parent)
        || java::asg::Common::getIsNormalMethod(*parent))) {
        incOperators(getEnumText(node.getNodeKind()));
      }
    }

    void HalsteadVisitor::visit(const java::asg::expr::PostfixExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "PostfixExpression");

      incOperators(getEnumText(node.getOperator()));
    }

    void HalsteadVisitor::visit(const java::asg::expr::PrefixExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "PrefixExpression");

      incOperators(getEnumText(node.getOperator()));
    }

    void HalsteadVisitor::visit(const java::asg::expr::TypeCast& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "TypeCast");

      incOperators(getEnumText(node.getNodeKind()));
    }

    void HalsteadVisitor::visit(const java::asg::expr::MethodInvocation& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "MethodInvocation");

      java::asg::expr::Expression* operand = node.getOperand();
      java::asg::struc::MethodDeclaration* method = node.getInvokes();
      if (operand != NULL && method != NULL && java::asg::Common::getIsIdentifier(*operand)) {
        const java::asg::expr::Identifier* i = dynamic_cast<const java::asg::expr::Identifier*>(operand);
        incMethodInvocations(i->getName(), method);
      }
      if (operand != NULL && method != NULL && java::asg::Common::getIsFieldAccess(*operand)) {
        const java::asg::expr::FieldAccess* fa = dynamic_cast<const java::asg::expr::FieldAccess*>(operand);
        incMethodInvocations(java::asg::Common::getLongName(*fa), method);
      }
      if (!node.getArgumentsIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getArgumentsSize() - 1);
      }
      if (!node.getTypeArgumentsIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getTypeArgumentsSize() - 1);
      }
    }

    /* -------------------------------------------------------------------------- ------------------------------------------------------------------------- */

    void HalsteadVisitor::visit(const java::asg::expr::Conditional& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Conditional");

      incOperators(getEnumText(node.getNodeKind()));
    }

    void HalsteadVisitor::visit(const java::asg::base::Base& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Base");

      if (needsSemicolon(node)) {
        incOperators(getEnumText(opkSemicolon));
      }
    }

    void HalsteadVisitor::visit(const java::asg::statm::Jump& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Jump");

      if (!node.getLabel().empty()) {
        incOperators(getEnumText(opkLabel));
        incOperands(node);
      }
    }

    void HalsteadVisitor::visit(const java::asg::statm::BasicFor& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "BasicFor");

      if (!node.getInitializersIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getInitializersSize() - 1);
      }
      if (!node.getUpdatesIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getUpdatesSize() - 1);
      }
    }

    void HalsteadVisitor::visit(const java::asg::statm::EnhancedFor& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "EnhancedFor");

      if (node.getParameter() != NULL) {
        incOperands(*(node.getParameter()));
      }
    }

    void HalsteadVisitor::visit(const java::asg::struc::GenericDeclaration& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "GenericDeclaration");

      if (!node.getTypeParametersIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getTypeParametersSize() - 1);
        incOperators(getEnumText(opkDiamond));
        for (java::asg::ListIterator<java::asg::struc::TypeParameter> it = node.getTypeParametersListIteratorBegin(); it != node.getTypeParametersListIteratorEnd(); ++it) {
          incOperands(*it);
          if (it->getBoundsSize() == 1) {
            // if there is only one bound, we have to check that it has a real ,,extends'' keyword, or it is just the generated default (java.lang.Object)
            if (!it->getBoundsListIteratorBegin()->getIsCompilerGenerated()) {
              incOperators(getEnumText(opkGenericExtends));
            }
          }
          else {
            // if there are more than 1 bounds we definetly have ,,extends'' keyword
            incOperators(getEnumText(opkGenericExtends));
            // we also add the & operators
            incOperators(getEnumText(opkGenericAnd), it->getBoundsSize() - 1);
          }
        }
      }
    }

    /* -------------------------------------------------------------------------- ------------------------------------------------------------------------- */

    void HalsteadVisitor::visit(const java::asg::expr::Identifier& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Identifier");

      const java::asg::base::Base* parent = node.getParent();
      if (parent != NULL
          && java::asg::Common::getIsMethodInvocation(*parent)
          && dynamic_cast<const java::asg::expr::MethodInvocation*>(parent)->getOperand() == &node) {
        return;
      }
      if (parent != NULL
        && java::asg::Common::getIsFieldAccess(*parent)
        && dynamic_cast<const java::asg::expr::FieldAccess*>(parent)->getRightOperand() == &node
        && node.getRefersTo() != NULL
        && java::asg::Common::getIsMethod(*(node.getRefersTo()))) {
        return;
      }

      if (node.getRefersTo() != NULL && java::asg::Common::getIsTypeDeclaration(*(node.getRefersTo()))) {
        incType(*(node.getRefersTo()));
      }
      else {
        incOperands(node);
      }
    }

    void HalsteadVisitor::visit(const java::asg::expr::Literal& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "Literal");

      incOperands(node); // every literal has its own
    }

    void HalsteadVisitor::visit(const java::asg::statm::LabeledStatement& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "LabeledStatement");

      incOperands(node);
    }

    void HalsteadVisitor::visit(const java::asg::struc::VariableDeclaration& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "VariableDeclaration");

      // no-op
    }

    void HalsteadVisitor::visit(const java::asg::expr::TypeExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "TypeExpression");

      if (java::asg::Common::getIsPrimitiveTypeExpression(node)) return;

      const java::asg::type::Type* type = node.getType();
      if (type != NULL && java::asg::Common::getIsClassType(*type)) {
        const java::asg::type::ClassType* classType = dynamic_cast<const java::asg::type::ClassType*>(type);
        if (classType->getRefersTo() != NULL) {
          java::asg::struc::TypeDeclaration* td = classType->getRefersTo();
          td->getName();
        }
      }
    }

    void HalsteadVisitor::visit(const java::asg::expr::PrimitiveTypeExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "PrimitiveTypeExpression");

      incOperators(getEnumText(node.getKind()));
    }

    void HalsteadVisitor::visit(const java::asg::expr::SimpleTypeExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "SimpleTypeExpression");

      if (node.getIsCompilerGenerated()) {
        return;
      }

      const java::asg::type::Type* type = node.getType();
      if (type != NULL) {
        incType(*type);
      }
    }

    void HalsteadVisitor::visit(const java::asg::expr::ArrayTypeExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "ArrayTypeExpression");

      incOperators(getEnumText(opkArray));
    }

    void HalsteadVisitor::visit(const java::asg::expr::TypeApplyExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "TypeApplyExpression");

      if (!node.getTypeArgumentsIsEmpty()) {
        incOperators(getEnumText(opkSeparator), node.getTypeArgumentsSize() - 1);
      }

      incOperators(getEnumText(opkDiamond));
    }

    void HalsteadVisitor::visit(const java::asg::expr::TypeUnionExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "TypeUnionExpression");

      if (!node.getAlternativesIsEmpty()) {
        incOperators(getEnumText(opkPipe), node.getAlternativesSize() - 1);
      }
    }

    void HalsteadVisitor::visit(const java::asg::expr::WildcardExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "WildcardExpression");

      incOperators(getEnumText(node.getKind()));
    }

    void HalsteadVisitor::visit(const java::asg::expr::QualifiedTypeExpression& node, bool callVirtualBase)
    {
      VISIT_BEGIN(node, callVirtualBase, "QualifiedTypeExpression");

      incOperators(getEnumText(opkTypeQualifier));
    }

}
}
