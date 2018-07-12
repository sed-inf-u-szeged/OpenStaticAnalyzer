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

#include "../inc/JSAN2LimVisitor.h"
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include "../inc/messages.h"
#include <iostream>
#include <sstream>

#define NOPOS ",0,0,0,0"

#define VISIT_BEGIN(node, callVirtualBase) \
  VisitorAbstractNodes::visit(node, callVirtualBase);

#define VISIT_END(node, callVirtualBase) \
  VisitorAbstractNodes::visitEnd(node, callVirtualBase);

#define SAFE_EDGE(node, name, type, param)                                        \
  do {                                                                            \
    bool node##_found = false;                                                    \
    lim::asg::ListIterator<type> node##_it = node.get##name##ListIteratorBegin(); \
    for (; node##_it != node.get##name##ListIteratorEnd(); ++node##_it) {         \
      if (node##_it->getId() == param) {                                          \
        node##_found = true;                                                      \
        break;                                                                    \
      }                                                                           \
    }                                                                             \
    if (!node##_found) {                                                          \
      node.add##name(param);                                                      \
    }                                                                             \
  } while (false)

namespace columbus {
namespace JSAN2Lim {
  using namespace std;
  using namespace javascript::asg;

  JSAN2LimVisitor::JSAN2LimVisitor(lim::asg::Factory& limFact ,columbus::javascript::asg::Factory& javascriptFact, LimOrigin& origin, string& componentName)
    : limFactory(limFact)
    , origin(origin)
    , attributeStack()
    , classStack()
    , methodStack()
    , packageStack()
    , fileStack()
    , lastLimMemberNodeId()
    , lastLimScopeNodeId()
    , demangledNameParts()
    , nodeMap()
    , methodMap()
    , attributeMap()
    , javascriptFactory(javascriptFact)
    , component(limFactory.createComponent(componentName))
    , revEdges(limFact.getReverseEdges())
    , skipUntil(0)
    , anonymusArrowCounter(0)
    , anonymusFunctionCounter(0)
    , anonymusMethodCounter(0)
    , anonymusClassCounter(0)

  {
    limFact.getComponentRootRef().addContains(component.getId());
    // shortName for component
    component.setShortName(common::pathRemoveExtension(common::pathFindFileName(componentName)));
    limFactory.getRoot()->addBelongsTo(component.getId());
    origin.addCompIdCppIdLimIdToMap(component.getId(), javascriptFact.getRoot()->getId(), limFact.getRoot()->getId());
  }

  bool JSAN2LimVisitor::PosInfo::matches(const PosInfo& other) const
  {
    if (file == "" || other.file == "")
      return true;
    if (file != other.file)
      return false;
    if (posString == NOPOS || other.posString == NOPOS)
      return true;
    return posString == other.posString;
  }

  bool JSAN2LimVisitor::PosInfo::operator<(const PosInfo& other) const
  {
    return file < other.file || (file == other.file && posString < other.posString);
  }

  lim::asg::NodeKind JSAN2LimVisitor::getLimKind(const javascript::asg::base::Base& node, bool tolerateError)
  {
    lim::asg::NodeKind nodeKind = lim::asg::ndkBase;
    if (javascript::asg::Common::getIsClass(node)) {
      nodeKind = lim::asg::ndkClass;
    }
    else if (javascript::asg::Common::getIsMethodDefinition(node)) {
      nodeKind = lim::asg::ndkMethod;
    }
    else if (javascript::asg::Common::getIsFunction(node)) {
      nodeKind = lim::asg::ndkMethod;
    }
    else if (javascript::asg::Common::getIsPattern(node)) {
      nodeKind = lim::asg::ndkParameter;
    }
    else if (javascript::asg::Common::getIsCallExpression(node)) {
      nodeKind = lim::asg::ndkMethodCall;
    }
    else if (javascript::asg::Common::getIsVariableDeclaration(node)) {
      nodeKind = lim::asg::ndkAttribute;
    }
    else if (javascript::asg::Common::getIsComment(node)) {
      nodeKind = lim::asg::ndkComment;
    }
    else if (javascript::asg::Common::getIsProgram(node)) {
      nodeKind = lim::asg::ndkPackage;
    }
    else if (javascript::asg::Common::getIsIdentifier(node)) {
      nodeKind = lim::asg::ndkAttributeAccess;
    }
    else if (javascript::asg::Common::getIsSystem(node)) {
      nodeKind = lim::asg::ndkComponent;
    }
    else if (javascript::asg::Common::getIsProperty(node)) {
      nodeKind = lim::asg::ndkAttribute;
    }
    return nodeKind;
  }

  JSAN2LimVisitor::PosInfo JSAN2LimVisitor::getPosInfo(const javascript::asg::base::Base& node) const
  {
    PosInfo posInfo;
    if (javascript::asg::Common::getIsPositioned(node)) {
      const javascript::asg::base::Positioned* currentNode = dynamic_cast<const javascript::asg::base::Positioned*>(&node);

      javascript::asg::Range pos = currentNode->getPosition();

      posInfo.posString = pos.getPath() + ","
        + common::toString(pos.getWideLine()) + ","
        + common::toString(pos.getWideCol()) + ","
        + common::toString(pos.getWideEndLine()) + ","
        + common::toString(pos.getWideEndCol());

      const javascript::asg::base::Base* current = &node;
      for (;;) {
        if (current && javascript::asg::Common::getIsPositioned(*current)) {
          string path = dynamic_cast<const javascript::asg::base::Positioned&>(*current).getPosition().getPath();
          if (path != "") {
            posInfo.file = path;
            break;
          }
          else
            current = current->getParent();
        }
        else
          break;
      }
    }
    else {
      posInfo.posString = NOPOS;
    }

    return posInfo;
  }

  lim::asg::base::Base& JSAN2LimVisitor::createLimNode(const javascript::asg::base::Base& node, bool checkExist)
  {

    lim::asg::base::Named* limNode = (lim::asg::base::Named*)limFactory.createNode(getLimKind(node));
    PosInfo posInfo = getPosInfo(node);
    NodeMap::iterator iterator = nodeMap.find(posInfo);
    if (iterator == nodeMap.end()) {
      nodeMap.insert(make_pair(posInfo, limNode->getId()));
    }
    origin.addCompIdCppIdLimIdToMap(component.getId(), node.getId(), limNode->getId());
    return *limNode;
  }

  std::map<Key, NodeId> JSAN2LimVisitor::fileMap;

  //FILLDATA
  void JSAN2LimVisitor::fillData(lim::asg::logical::Method& limNode, const javascript::asg::structure::MethodDefinition& jsNode)
  {
    limNode.setAccessibility(lim::asg::ackPublic);
    limNode.setIsStatic(jsNode.getStatic());
    limNode.setLanguage(lim::asg::lnkJavaScript);
    lastLimMemberNodeId.push(limNode.getId());
    lastLimScopeNodeId.push(limNode.getId());

    if (javascript::asg::Common::getIsIdentifier(*jsNode.getKey())) {
      javascript::asg::expression::Identifier& identifier = dynamic_cast<javascript::asg::expression::Identifier&>(*jsNode.getKey());
      limNode.setName(identifier.getName());
      limNode.setIsAnonymous(false);
    }
    else {
      stringstream ss;
      ss << this->anonymusMethodCounter++;
      limNode.setName("anonymusMethod" + ss.str());
      limNode.setIsAnonymous(true);
    }
    methodStack.top().TLOC = jsNode.getPosition().getEndLine() - jsNode.getPosition().getLine() + 1;
    // LOC modified later on, if needed
    methodStack.top().LOC = methodStack.top().TLOC;
    switch (jsNode.getKind()) {
    case javascript::asg::mdkConstructor:
      limNode.setMethodKind(lim::asg::mekConstructor);
      break;
    case javascript::asg::mdkGet:
      limNode.setMethodKind(lim::asg::mekGet);
      break;
    case javascript::asg::mdkSet:
      limNode.setMethodKind(lim::asg::mekSet);
      break;
    case javascript::asg::mdkMethod:
      limNode.setMethodKind(lim::asg::mekNormal);
      break;
    case javascript::asg::mdkLAST:
      limNode.setMethodKind(lim::asg::mekLAST);
      break;
    default:
      common::WriteMsg::write(common::WriteMsg::mlWarning, "Missing methodkind of JSnode %d during lim conversion", jsNode.getId());
    }

    if ((!classStack.empty()) && classStack.top().classNodeId) {
      lim::asg::logical::Class& parent = dynamic_cast<lim::asg::logical::Class&>(limFactory.getRef(classStack.top().classNodeId));
      SAFE_EDGE(parent, Member, lim::asg::logical::Member, limNode.getId());
      addIsContained(limNode, jsNode.getPosition());
    }
    methodMap.insert(make_pair(limNode.getName(), limNode.getId()));
  }

  void JSAN2LimVisitor::addIsContained(lim::asg::logical::Member& member, const javascript::asg::Range& range)
  {

    lim::asg::SourcePosition limPos;
    limPos.setLine(range.getWideLine());
    limPos.setColumn(range.getWideCol());
    limPos.setEndLine(range.getWideEndLine());
    limPos.setEndColumn(range.getWideEndCol());
    limPos.setRealizationLevel(lim::asg::relDefines);

    if (!fileStack.empty()) {
      member.addIsContainedIn(fileStack.top(), limPos);
    }
  }

  void JSAN2LimVisitor::fillData(lim::asg::logical::Method& limNode, const javascript::asg::statement::Function& jsNode)
  {
    limNode.setAccessibility(lim::asg::ackPublic);
    limNode.setMethodKind(lim::asg::mekNormal);
    limNode.setLanguage(lim::asg::lnkJavaScript);
    lastLimMemberNodeId.push(limNode.getId());
    lastLimScopeNodeId.push(limNode.getId());

    /*Determine the name for the function. Anonym functions are handled.*/
    if (jsNode.getIdentifier() != NULL) {
      javascript::asg::expression::Identifier& identifier = *jsNode.getIdentifier();
      limNode.setName(identifier.getName());
    }
    else {
      limNode.setIsAnonymous(true);
      if (!jsNode.getParent()) {
        common::WriteMsg::write(common::WriteMsg::mlDebug, "Missing parent of node %d", jsNode.getId());
      }
      if (jsNode.getParent() && javascript::asg::Common::getIsProperty(*jsNode.getParent())) {
        javascript::asg::expression::Property& propertyNode = dynamic_cast<javascript::asg::expression::Property&>(*jsNode.getParent());
        if (propertyNode.getKey() != NULL && javascript::asg::Common::getIsIdentifier(*propertyNode.getKey())) {
          javascript::asg::expression::Identifier& propertyIdentifier = dynamic_cast<javascript::asg::expression::Identifier&>(*propertyNode.getKey());
          limNode.setName(propertyIdentifier.getName());
        }
      }
      else {
        stringstream ss;
        if (javascript::asg::Common::getIsFunctionExpression(jsNode)) {
          ss << anonymusFunctionCounter++;
          limNode.setName("anonymousFunctionExpression" + ss.str());
        }
        else {
          ss << anonymusArrowCounter++;
          limNode.setName("anonymusArrowFunctionExpression" + ss.str());
        }
      }
    }

    if ((!methodStack.empty()) && methodStack.top().methodNodeId) {
      lim::asg::logical::Method& parent = dynamic_cast<lim::asg::logical::Method&>(limFactory.getRef(methodStack.top().methodNodeId));
      SAFE_EDGE(parent, Member, lim::asg::logical::Member, limNode.getId());
    }
    else if ((!packageStack.empty()) && packageStack.top().packageNodeId) {
      lim::asg::logical::Package& parent = dynamic_cast<lim::asg::logical::Package&>(limFactory.getRef(packageStack.top().packageNodeId));
      SAFE_EDGE(parent, Member, lim::asg::logical::Member, limNode.getId());
    }
    else {
      lim::asg::logical::Package* packageNode = limFactory.getRoot();
      packageNode->addMember(limNode.getId());
    }

    methodMap.insert(make_pair(limNode.getName(), limNode.getId()));
    addIsContainedInEdge(limNode, jsNode);
  }

  void JSAN2LimVisitor::fillData(lim::asg::logical::Parameter& limNode, const javascript::asg::statement::Pattern& jsNode)
  {
    if ((!methodStack.empty()) && methodStack.top().methodNodeId) {
      lim::asg::logical::Method& parent = dynamic_cast<lim::asg::logical::Method&>(limFactory.getRef(methodStack.top().methodNodeId));
      if (javascript::asg::Common::getIsIdentifier(jsNode)) {
        const javascript::asg::expression::Identifier& ident = dynamic_cast<const javascript::asg::expression::Identifier&>(jsNode);
        limNode.setName(ident.getName());
      }
      else if (javascript::asg::Common::getIsArrayPattern(jsNode)) {
        limNode.setName("ArrayPattern");
      }
      else if (javascript::asg::Common::getIsObjectPattern(jsNode)) {
        limNode.setName("ObjectPattern");
      }
      else if (javascript::asg::Common::getIsRestElement(jsNode)) {
        const javascript::asg::statement::RestElement& restElement = dynamic_cast<const javascript::asg::statement::RestElement&>(jsNode);
        if (javascript::asg::Common::getIsIdentifier(*restElement.getArgument())) {
          const javascript::asg::expression::Identifier& ident = dynamic_cast<const javascript::asg::expression::Identifier&>(*restElement.getArgument());
          limNode.setName(ident.getName());
        }
        else {
          limNode.setName("RestElement");
        }
      }
      else if (javascript::asg::Common::getIsAssignmentPattern(jsNode)) {
        limNode.setName("AssignmentPattern");
      }
      SAFE_EDGE(parent, Parameter, lim::asg::logical::Parameter, limNode.getId());
    }
  }

  void JSAN2LimVisitor::fillData(lim::asg::logical::Class& limNode, const javascript::asg::structure::Class& jsNode)
  {
    limNode.setAccessibility(lim::asg::ackPublic);
    limNode.setLanguage(lim::asg::lnkJavaScript);
    lastLimMemberNodeId.push(limNode.getId());
    lastLimScopeNodeId.push(limNode.getId());
    limNode.setClassKind(lim::asg::clkClass);
    if (jsNode.getIdentifier() != NULL) {
      javascript::asg::expression::Identifier& identifier = *jsNode.getIdentifier();
      limNode.setName(identifier.getName());
    }
    else {
      limNode.setIsAnonymous(true);
      stringstream ss;
      ss << anonymusClassCounter++;
      limNode.setName("anonymousClass" + ss.str());
    }
    if ((!methodStack.empty()) && methodStack.top().methodNodeId) {
      lim::asg::logical::Method& parent = dynamic_cast<lim::asg::logical::Method&>(limFactory.getRef(methodStack.top().methodNodeId));
      SAFE_EDGE(parent, Member, lim::asg::logical::Member, limNode.getId());
    }
    else if ((!packageStack.empty()) && packageStack.top().packageNodeId) {
      lim::asg::logical::Package& parent = dynamic_cast<lim::asg::logical::Package&>(limFactory.getRef(packageStack.top().packageNodeId));
      SAFE_EDGE(parent, Member, lim::asg::logical::Member, limNode.getId());
    }
    else {
      lim::asg::logical::Package* packageNode = limFactory.getRoot();
      packageNode->addMember(limNode.getId());
    }
    addIsContainedInEdge(limNode, jsNode);
  }

  void JSAN2LimVisitor::fillData(lim::asg::logical::Attribute& limNode, const javascript::asg::declaration::VariableDeclaration& jsNode)
  {
    limNode.setAccessibility(lim::asg::ackNone);
    limNode.setIsStatic(false);
    limNode.setLanguage(lim::asg::lnkJavaScript);
    lastLimMemberNodeId.push(limNode.getId());

    if (!jsNode.getDeclarationsIsEmpty()) {
      javascript::asg::ListIterator<javascript::asg::declaration::VariableDeclarator> varDeclarator = jsNode.getDeclarationsListIteratorBegin();
      if (varDeclarator->getIdentifier() != NULL && Common::getIsIdentifier(*varDeclarator->getIdentifier())) {
        javascript::asg::expression::Identifier& variableName = dynamic_cast<javascript::asg::expression::Identifier&>(*varDeclarator->getIdentifier());
        limNode.setName(variableName.getName());
      }
      else {
        limNode.setName("anonymousAttribute");
      }
    }
    addIsContainedInEdge(limNode, jsNode);
  }

  lim::asg::base::Base* JSAN2LimVisitor::getLimNode(const javascript::asg::base::Base& node)
  {
    PosInfo posInfo = getPosInfo(node);
    NodeMap::iterator iterator = nodeMap.find(posInfo);
    if (iterator == nodeMap.end()) {
      return NULL;
    }
    lim::asg::base::Base* limNode = limFactory.getPointer(nodeMap.at(posInfo));
    return limNode;
  }

  //VISIT
  void JSAN2LimVisitor::visit(const javascript::asg::structure::Class& clNode, bool callVirtualBase)
  {
    VISIT_BEGIN(clNode, callVirtualBase);
    lim::asg::logical::Class& classLimNode = dynamic_cast<lim::asg::logical::Class&>(createLimNode(clNode, callVirtualBase));
    fillData(classLimNode, clNode);//sets the name

    fillMemberData(classLimNode);
    demangledNameParts.push_back(classLimNode.getName());

    classStack.push(ClassInfo());
    classStack.top().classNodeId = classLimNode.getId();
    if (clNode.getSuperClass() != NULL) {
      if (javascript::asg::Common::getIsIdentifier(*clNode.getSuperClass())) {
        javascript::asg::expression::Identifier& superClass = dynamic_cast<javascript::asg::expression::Identifier&>(*clNode.getSuperClass());
        classStack.top().isSubclass = superClass.getId();
      }
    }
    classStack.top().TLOC = clNode.getPosition().getEndLine() - clNode.getPosition().getLine() + 1;
    classStack.top().LOC = clNode.getPosition().getEndLine() - clNode.getPosition().getLine() + 1;
    if (!packageStack.empty()) {
      lim::asg::logical::Package& packageLimNode = dynamic_cast<lim::asg::logical::Package&>(limFactory.getRef(packageStack.top().packageNodeId));
      SAFE_EDGE(packageLimNode, Member, lim::asg::logical::Member, classLimNode.getId());
    }
    else {
      common::WriteMsg::write(common::WriteMsg::mlDebug, "Empty packageStack while visiting node %d.", clNode.getId());
    }
    addIsContainedInEdge(classLimNode, clNode);
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::structure::Class& clNode, bool callVirtualBase)
  {
    VISIT_END(clNode, true);
    lim::asg::logical::Class& classLimNode = dynamic_cast<lim::asg::logical::Class&>(limFactory.getRef(classStack.top().classNodeId));
    fillCollectedClassData(classLimNode, clNode);
    lastLimMemberNodeId.pop();
    lastLimScopeNodeId.pop();

    demangledNameParts.pop_back();
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::declaration::ClassDeclaration& clNode, bool callVirtualBase)
  {
    VISIT_END(clNode, false);
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::expression::ClassExpression& clNode, bool callVirtualBase)
  {
    VISIT_END(clNode, false);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::structure::MethodDefinition& mdNode, bool callVirtualBase)
  {
    //VisitorAbstractNodes::visit(mdNode, callVirtualBase);
    VISIT_BEGIN(mdNode, callVirtualBase);
    lim::asg::logical::Method& methodLimNode = dynamic_cast<lim::asg::logical::Method&>(createLimNode(mdNode, callVirtualBase));
    if (!classStack.empty()) {
      lim::asg::logical::Class& classLimNode = dynamic_cast<lim::asg::logical::Class&>(limFactory.getRef(classStack.top().classNodeId));
      SAFE_EDGE(classLimNode, Member, lim::asg::logical::Member, methodLimNode.getId());
    }
    methodStack.push(MethodInfo());
    methodStack.top().methodNodeId = methodLimNode.getId();
    lastLimMemberNodeId.push(methodLimNode.getId());
    lastLimScopeNodeId.push(methodLimNode.getId());
    fillData(methodLimNode, mdNode);

    //first set demangled and mengled name then add method name to name parts
    fillMemberData(methodLimNode);
    demangledNameParts.push_back(methodLimNode.getName());

  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::structure::MethodDefinition& mdNode, bool callVirtualBase)
  {
    VISIT_END(mdNode, true);
    lim::asg::logical::Method& method = dynamic_cast<lim::asg::logical::Method&>(limFactory.getRef(methodStack.top().methodNodeId));
    fillCollectedMethodData(method, mdNode);
    lastLimMemberNodeId.pop();
    lastLimScopeNodeId.pop();

    demangledNameParts.pop_back();
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::Function& functionNode, bool callVirtualBase)
  {
    if (javascript::asg::Common::getIsFunctionExpression(functionNode) && functionNode.getParent() && javascript::asg::Common::getIsMethodDefinition(*functionNode.getParent())) {
      return;
    }
    VISIT_BEGIN(functionNode, callVirtualBase);
    lim::asg::logical::Method& limNode = dynamic_cast<lim::asg::logical::Method&>(createLimNode(functionNode, callVirtualBase));
    fillData(limNode, functionNode);

    fillMemberData(limNode);
    demangledNameParts.push_back(limNode.getName());

    bool embeddedMethod = !methodStack.empty();
    methodStack.push(MethodInfo());
    methodStack.top().methodNodeId = limNode.getId();
    methodStack.top().isEmbeddedMethod = embeddedMethod;
    methodStack.top().TLOC = functionNode.getPosition().getEndLine() - functionNode.getPosition().getLine() + 1;
    methodStack.top().LOC = functionNode.getPosition().getEndLine() - functionNode.getPosition().getLine() + 1;
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::Function& functionNode, bool callVirtualBase)
  {
    if (!functionNode.getParent()) {
      common::WriteMsg::write(common::WriteMsg::mlDebug, "Missing parent of node %d", functionNode.getId());
      return;
    }
    if (javascript::asg::Common::getIsFunctionExpression(functionNode) && javascript::asg::Common::getIsMethodDefinition(*functionNode.getParent())) {
      return;
    }

    if (!methodStack.empty() && methodStack.top().methodNodeId) {
      MethodInfo& methodInfo = methodStack.top();
      //methodInfo.LOC = functionNode.getPosition().getEndLine() - functionNode.getPosition().getLine() + 1; // why not in visit
      lim::asg::logical::Method& method = dynamic_cast<lim::asg::logical::Method&>(limFactory.getRef(methodInfo.methodNodeId));

      //set program NL
      if (packageStack.top().NL < methodStack.top().NL)
        packageStack.top().NL = methodStack.top().NL;
      if (packageStack.top().NLE < methodStack.top().NLE)
        packageStack.top().NLE = methodStack.top().NLE;
      fillCollectedMethodData(method, functionNode);
      lastLimMemberNodeId.pop();
      lastLimScopeNodeId.pop();
    }

    demangledNameParts.pop_back();
    VISIT_END(functionNode, true);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::expression::Identifier& identifierNode, bool callVirtualBase)
  {
    VISIT_BEGIN(identifierNode, callVirtualBase);
    AttributeMap::iterator it = attributeMap.find(identifierNode.getName());
    NodeId attributeId;
    if (it != attributeMap.end()) {
      attributeId = it->second;
      lim::asg::logical::Attribute& attribute = dynamic_cast<lim::asg::logical::Attribute&>(limFactory.getRef(attributeId));
      /*lim::asg::logical::AttributeAccess& attrAccess = limFactory.createAttributeAccess(attribute.getId());*/
      limFactory.createAttributeAccess(attribute.getId());
    }
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::expression::Identifier& identifierNode, bool callVirtualBase)
  {
    VISIT_END(identifierNode, callVirtualBase);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::Pattern& patternNode, bool callVirtualBase)
  {
    VISIT_BEGIN(patternNode, callVirtualBase);
    if (isMethodParameter(patternNode)) {
      lim::asg::logical::Parameter& limNode = dynamic_cast<lim::asg::logical::Parameter&>(createLimNode(patternNode, callVirtualBase));
      fillData(limNode, patternNode);
    }
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::Pattern& patternNode, bool callVirtualBase)
  {
    VISIT_END(patternNode, callVirtualBase);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::expression::CallExpression& callExpressionNode, bool callVirtualBase)
  {
    VISIT_BEGIN(callExpressionNode, callVirtualBase);
    javascript::asg::expression::Identifier* identifier = NULL;
    if (callExpressionNode.getCallee() && javascript::asg::Common::getIsIdentifier(*callExpressionNode.getCallee())) {
      identifier = dynamic_cast<javascript::asg::expression::Identifier*>(callExpressionNode.getCallee());
    }
    else if (callExpressionNode.getCallee() && javascript::asg::Common::getIsMemberExpression(*callExpressionNode.getCallee())) {
      javascript::asg::expression::MemberExpression& memberExpression = dynamic_cast<javascript::asg::expression::MemberExpression&>(*callExpressionNode.getCallee());
      if (javascript::asg::Common::getIsIdentifier(*memberExpression.getProperty())) {
        identifier = dynamic_cast<javascript::asg::expression::Identifier*>(memberExpression.getProperty());
      }
    }
    if (identifier != NULL) {
      MethodMap::iterator it = methodMap.find(identifier->getName());
      NodeId methodId;
      if (it != methodMap.end()) {
        methodId = it->second;
        lim::asg::logical::MethodCall& methodCall = limFactory.createMethodCall(methodId);
        if (!methodStack.empty()) {
          methodStack.top().calls.insert(methodCall.getId());
        }
        else {
          common::WriteMsg::write(CMSG_METHODE_OR_A_STACK_IS_EMPTY);
        }
      }
      else {
        if (!methodStack.empty()) {
          callExprMap.insert(make_pair(callExpressionNode.getId(), methodStack.top().methodNodeId));
        }
        else if (!packageStack.empty()) {
          callExprMap.insert(make_pair(callExpressionNode.getId(), packageStack.top().packageNodeId));
        }
      }
    }
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::expression::CallExpression& callExpressionNode, bool callVirtualBase)
  {
    VISIT_END(callExpressionNode, callVirtualBase);
  }

  // FILL COLLECTED DATA
  void JSAN2LimVisitor::fillCollectedMethodData(lim::asg::logical::Method& method, const javascript::asg::base::Positioned& functionNode)
  {
    MethodInfo methodInfo = methodStack.top();

    javascript::asg::Range pos = functionNode.getPosition();
    methodInfo.lines.insert(pos.getLine());
    methodInfo.lines.insert(pos.getEndLine());
    methodInfo.LLOC += methodInfo.lines.size();
    methodInfo.TLLOC += methodInfo.lines.size();

    if (method.getMemberSize() != 0) {
      for (lim::asg::ListIterator<lim::asg::Member> it = method.getMemberListIteratorBegin(); it != method.getMemberListIteratorEnd(); ++it) {
        if (lim::asg::Common::getIsScope(*it)) {
          const lim::asg::logical::Scope& scope = dynamic_cast<const lim::asg::logical::Scope&>(*it);
          int unnecesaryLines = 0;
          lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> fileIt = scope.getIsContainedInListIteratorAssocBegin();
          lim::asg::SourcePosition pos = fileIt.getAssocClass();
          for (unsigned int j = pos.getLine(); j <= pos.getEndLine(); j++) {
            if ((methodInfo.lines.find(j)) != methodInfo.lines.end()) {
              unnecesaryLines++;
            }
          }
          methodInfo.TLLOC += scope.getTLLOC() - unnecesaryLines;

          /*if (lim::asg::Common::getIsMethod(scope)) {
              //Z: methodInfo.LOC -= (scope.getTLOC() - unnecesaryLines);
            }
            else {
              //Z: methodInfo.LLOC += (scope.getLLOC() - unnecesaryLines);
            }*/
        }
      }
    }

    handleComments(method, functionNode);

    if (!packageStack.empty()) {
      packageStack.top().lines.insert(methodInfo.lines.begin(), methodInfo.lines.end());
    }

    method.setNestingLevel(methodInfo.NL);
    method.setNestingLevelElseIf(methodInfo.NLE);
    method.setNumberOfBranches(methodInfo.NOB);
    method.setNumberOfStatements(methodInfo.NOS);
    method.setTLOC(methodInfo.TLOC);
    method.setLOC(methodInfo.LOC);
    method.setLLOC(methodInfo.LLOC);
    method.setTLLOC(methodInfo.TLLOC);
    set<NodeId>::iterator i;
    for (i = methodInfo.calls.begin(); i != methodInfo.calls.end(); ++i)
      SAFE_EDGE(method, Calls, lim::asg::logical::MethodCall, *i);
    methodStack.pop();

    if (methodStack.size() != 0) {
      methodStack.top().LOC -= method.getTLOC(); //LOC is decreased by the TLOC of contained member: function

      //however there could be code that is not part of the member. E.g: var asd = function{...}
      for (unsigned int j = pos.getLine(); j <= pos.getEndLine(); j++) {
        if ((methodStack.top().lines.find(j)) != methodStack.top().lines.end()) {
          methodStack.top().LOC++;
        }
      }

    }
  }

  void JSAN2LimVisitor::fillCollectedClassData(lim::asg::logical::Class& classLimNode, const javascript::asg::structure::Class& classJSNode)
  {
    ClassInfo classInfo = classStack.top();

    javascript::asg::Range pos = classJSNode.getPosition();
    classInfo.lines.insert(pos.getLine());
    classInfo.lines.insert(pos.getEndLine());
    classInfo.LLOC += classInfo.lines.size();
    classInfo.TLLOC += classInfo.lines.size();

    //classInfo.TLLOC = (int)classInfo.lines.size();
    //classInfo.LLOC = classInfo.TLLOC + classInfo.LOC;
    //classInfo.LOC = classInfo.TLOC + classInfo.LOC;

    if (classLimNode.getMemberSize() != 0) {
      for (lim::asg::ListIterator<lim::asg::Member> it = classLimNode.getMemberListIteratorBegin(); it != classLimNode.getMemberListIteratorEnd(); ++it) {
        if (lim::asg::Common::getIsScope(*it)) {
          const lim::asg::logical::Scope& scope = dynamic_cast<const lim::asg::logical::Scope&>(*it);
          int unnecesaryLines = 0;
          lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> fileIt = scope.getIsContainedInListIteratorAssocBegin();
          lim::asg::SourcePosition pos = fileIt.getAssocClass();
          for (unsigned int j = pos.getLine(); j <= pos.getEndLine(); j++) {
            if ((classInfo.lines.find(j)) != classInfo.lines.end()) {
              unnecesaryLines++;
            }
          }
          classInfo.TLLOC += (scope.getTLLOC() - unnecesaryLines);
          classInfo.LOC -= scope.getTLOC();
          classInfo.LLOC -= unnecesaryLines;
          /*if (scope.getIsAnonymous()) {
            classInfo.LOC -= (scope.getTLOC() - unnecesaryLines);
          }
          else {
            classInfo.LLOC += (scope.getTLLOC() - unnecesaryLines);
          }*/
        }
      }
    }

    handleComments(classLimNode, classJSNode);

    limFactory.beginType();
    lim::asg::type::TypeFormerType& typeFormerType = limFactory.createTypeFormerType(classLimNode.getId());
    limFactory.addTypeFormer(typeFormerType.getId());
    lim::asg::type::Type& limType = limFactory.endType();
    classMap.insert(make_pair(classLimNode.getName(), limType.getId()));

    if (classStack.top().isSubclass != 0) {
      javascript::asg::expression::Identifier& parentClass = dynamic_cast<javascript::asg::expression::Identifier&>(javascriptFactory.getRef(classStack.top().isSubclass));
      ClassMap::iterator classIterator = classMap.find(parentClass.getName());
      if (classIterator != classMap.end()) {
        SAFE_EDGE(classLimNode, IsSubclass, lim::asg::type::Type, classIterator->second);
      }
    }

    classLimNode.setTLOC(classInfo.TLOC);
    classLimNode.setLOC(classInfo.LOC);
    classLimNode.setLLOC(classInfo.LLOC);
    classLimNode.setTLLOC(classInfo.TLLOC);
    classStack.pop();
    if (classStack.size() != 0) {
      classStack.top().LOC -= classLimNode.getTLOC();
    }
  }
  void JSAN2LimVisitor::fillCollectedPackageData(lim::asg::logical::Package& packageLimNode)
  {
    PackageInfo packageInfo = packageStack.top();
    //int unnecesaryLines = 0;

    packageLimNode.setTLOC(packageInfo.TLOC);
    packageLimNode.setLOC(packageInfo.LOC);
    packageLimNode.setLLOC((int)packageInfo.lines.size());
    packageLimNode.setTLLOC((int)packageInfo.lines.size()); // calculated properly
  }

  void JSAN2LimVisitor::visit(const javascript::asg::declaration::VariableDeclaration& variableDeclarationNode, bool callVirtualBase)
  {
    VISIT_BEGIN(variableDeclarationNode, callVirtualBase);
    if (classStack.empty() && methodStack.empty()) {
      lim::asg::logical::Attribute& attributeNode = dynamic_cast<lim::asg::logical::Attribute&>(createLimNode(variableDeclarationNode, callVirtualBase));
      fillData(attributeNode, variableDeclarationNode);
      fillMemberData(attributeNode);
      attributeMap.insert(make_pair(attributeNode.getName(), attributeNode.getId()));
      attributeStack.push(AttributeInfo());
      attributeStack.top().attributeNodeId = attributeNode.getId();

      if (!packageStack.empty()) {
        lim::asg::logical::Package& package = dynamic_cast<lim::asg::logical::Package&>(limFactory.getRef(packageStack.top().packageNodeId));
        SAFE_EDGE(package, Member, lim::asg::logical::Member, attributeNode.getId());
      }
    }
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::declaration::VariableDeclaration& variableDeclarationNode, bool callVirtualBase)
  {
    VISIT_END(variableDeclarationNode, callVirtualBase);
    if (classStack.empty() && methodStack.empty()) {
      lastLimMemberNodeId.pop();
      //demangledNameParts.pop_back();
    }
  }

  void JSAN2LimVisitor::visit(const javascript::asg::base::Program& programNode, bool callVirtualBase)
  {
    VISIT_BEGIN(programNode, callVirtualBase);
    //javascript::asg::Range pos = programNode.getPosition();
    lim::asg::logical::Package& packageLimNode = dynamic_cast<lim::asg::logical::Package&>(createLimNode(programNode, callVirtualBase));
    packageLimNode.setName(programNode.getName());

    //first set the mengled and demangled name then add the program as a name part
    fillMemberData(packageLimNode);
    demangledNameParts.push_back(programNode.getName());

    packageLimNode.setLanguage(lim::asg::lnkJavaScript);
    limFactory.getRoot()->addMember(packageLimNode.getId());
    packageStack.push(PackageInfo());
    packageStack.top().packageNodeId = packageLimNode.getId();

    lastLimMemberNodeId.push(packageLimNode.getId());
    lastLimScopeNodeId.push(packageLimNode.getId());

    // TLOC: including empty and comment lines + nests
    packageStack.top().TLOC = programNode.getPosition().getEndLine() - programNode.getPosition().getLine() + 1;

    // LOC: including comment and empty lines + but not nests
    int LOC = packageStack.top().TLOC;
    /* not LOC
      if (!programNode.getCommentsIsEmpty()) {
      for (javascript::asg::ListIterator<javascript::asg::base::Comment> commentNode = programNode.getCommentsListIteratorBegin(); commentNode != programNode.getCommentsListIteratorEnd(); ++commentNode) {
      LOC += commentNode->getPosition().getEndLine() - commentNode->getPosition().getLine() + 1;
      if (programNode.getPosition().getLine() - commentNode->getPosition().getEndLine() > 1) {
      int emptyLines = programNode.getPosition().getLine() - commentNode->getPosition().getEndLine() - 1;
      LOC += emptyLines;
      }
      }
      }*/
    packageStack.top().LOC = LOC;

    createFile(programNode);
    addIsContainedInEdge(packageLimNode, programNode);

    //handle comments
    handleComments(packageLimNode, programNode);

    methodMap.clear();
    classMap.clear();
    callExprMap.clear();
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::base::Program& programNode, bool callVirtualBase)
  {
    VISIT_END(programNode, callVirtualBase);
    lim::asg::logical::Package& packageLimNode = dynamic_cast<lim::asg::logical::Package&>(limFactory.getRef(packageStack.top().packageNodeId));
    fillCollectedPackageData(packageLimNode);
    lim::asg::physical::File& file = createFile(programNode);

    file.setLOC(packageLimNode.getLOC());
    file.setCLOC(packageLimNode.getCommentLines());
    file.setLLOC(packageLimNode.getLLOC());

    //   int lines = 0;
    set<NodeId> commentNodes;

    if (!programNode.getCommentsIsEmpty()) {
      for (set<NodeId>::const_iterator i = commentNodes.begin(); i != commentNodes.end(); ++i) {
        SAFE_EDGE(file, Comment, lim::asg::base::Comment, *i);
      }
    }

    for (CallExprMap::iterator iterator = callExprMap.begin(); iterator != callExprMap.end(); ++iterator) {
      javascript::asg::expression::CallExpression& callExpressionNode = dynamic_cast<javascript::asg::expression::CallExpression&>(javascriptFactory.getRef(iterator->first));

      javascript::asg::expression::Identifier* identifier = NULL;
      if (javascript::asg::Common::getIsIdentifier(*callExpressionNode.getCallee())) {
        identifier = dynamic_cast<javascript::asg::expression::Identifier*>(callExpressionNode.getCallee());
      }
      else if (javascript::asg::Common::getIsMemberExpression(*callExpressionNode.getCallee())) {
        javascript::asg::expression::MemberExpression& memberExpression = dynamic_cast<javascript::asg::expression::MemberExpression&>(*callExpressionNode.getCallee());
        if (javascript::asg::Common::getIsIdentifier(*memberExpression.getProperty())) {
          identifier = dynamic_cast<javascript::asg::expression::Identifier*>(memberExpression.getProperty());
        }
      }
      if (identifier != NULL) {
        MethodMap::iterator methodIt = methodMap.find(identifier->getName());
        if (methodIt != methodMap.end()) {
          lim::asg::logical::MethodCall& methodCall = limFactory.createMethodCall(methodIt->second);
          if (lim::asg::Common::getIsMethod(limFactory.getRef(iterator->second))) {
            lim::asg::logical::Method& limNode = dynamic_cast<lim::asg::logical::Method&>(limFactory.getRef(iterator->second));
            SAFE_EDGE(limNode, Calls, lim::asg::logical::MethodCall, methodCall.getId());
          }
        }
      }
    }

    if (!fileStack.empty()) {
      fileStack.pop();
    }
    if (!packageStack.empty()) {
      common::WriteMsg::write(common::WriteMsg::mlDebug, typeid(limFactory.getRef(packageStack.top().packageNodeId)).name());
      packageStack.pop();
    }
    lastLimMemberNodeId.pop();
    lastLimScopeNodeId.pop();
    demangledNameParts.pop_back();
  }

  void JSAN2LimVisitor::visit(const javascript::asg::base::Positioned& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, callVirtualBase);

    if (!methodStack.empty()) {
      if (!Common::getIsFunction(node)) {
        methodStack.top().lines.insert(node.getPosition().getLine());
        methodStack.top().lines.insert(node.getPosition().getEndLine());
      }
    }

    if (!lastLimScopeNodeId.empty()) {
      lim::asg::logical::Scope& scopeLimNode = dynamic_cast<lim::asg::logical::Scope&>(limFactory.getRef(lastLimScopeNodeId.top()));
      if (lim::asg::Common::getIsMethod(scopeLimNode) && !methodStack.empty()) {
        //methodStack.top().lines.insert(node.getPosition().getLine());
        //methodStack.top().lines.insert(node.getPosition().getEndLine());
      }
      else if (lim::asg::Common::getIsClass(scopeLimNode) && !classStack.empty()) {
        classStack.top().lines.insert(node.getPosition().getLine());
        classStack.top().lines.insert(node.getPosition().getEndLine());
      }
      else if (lim::asg::Common::getIsPackage(scopeLimNode) && !packageStack.empty()) {
        packageStack.top().lines.insert(node.getPosition().getLine());
        packageStack.top().lines.insert(node.getPosition().getEndLine());
      }
    }
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::base::Positioned& node, bool callVirtualBase)
  {

    if (!(Common::getIsClass(node) || Common::getIsFunction(node) || Common::getIsMethodDefinition(node)) && !node.getCommentsIsEmpty()) {

      for (ListIterator<javascript::asg::base::Comment> i = node.getCommentsListIteratorBegin(); i != node.getCommentsListIteratorEnd(); ++i) {

        if (!methodStack.empty()) {
          methodStack.top().comments.insert(i->getId());
        }
        else if (!classStack.empty()) {
          classStack.top().comments.insert(i->getId());
        }
        else if (!packageStack.empty()) {
          packageStack.top().comments.insert(i->getId());
        }
      }
    }

    VISIT_END(node, callVirtualBase);
  }

  void JSAN2LimVisitor::handleComments(lim::asg::Member& limNode, const javascript::asg::base::Positioned& jsNode)
  {

    for (ListIterator<javascript::asg::base::Comment> i = jsNode.getCommentsListIteratorBegin(); i != jsNode.getCommentsListIteratorEnd(); ++i) {

      if (jsNode.getPosition().getLine() - i->getPosition().getEndLine() <= 1) { //then its a doc comment
        SAFE_EDGE(limNode, Comment, lim::asg::base::Comment, limFactory.createComment(i->getText()).getId());
      }
    }

    //handle not documentation comments
    if (lim::asg::Common::getIsMethod(limNode) && !methodStack.empty()) {
      for (auto i = methodStack.top().comments.begin(); i != methodStack.top().comments.end(); i++) {
        javascript::asg::base::Comment* c = dynamic_cast<javascript::asg::base::Comment*>(javascriptFactory.getPointer(*i));
        limNode.setCommentLines(limNode.getCommentLines() + (c->getPosition().getEndLine() - c->getPosition().getLine() + 1));
      }
    }
    else if (lim::asg::Common::getIsClass(limNode) && !classStack.empty()) {
      for (auto i = classStack.top().comments.begin(); i != classStack.top().comments.end(); i++) {
        javascript::asg::base::Comment* c = dynamic_cast<javascript::asg::base::Comment*>(javascriptFactory.getPointer(*i));
        limNode.setCommentLines(limNode.getCommentLines() + (c->getPosition().getEndLine() - c->getPosition().getLine() + 1));
      }
    }
    else if (lim::asg::Common::getIsPackage(limNode) && !packageStack.empty()) {
      for (auto i = packageStack.top().comments.begin(); i != packageStack.top().comments.end(); i++) {
        javascript::asg::base::Comment* c = dynamic_cast<javascript::asg::base::Comment*>(javascriptFactory.getPointer(*i));
        limNode.setCommentLines(limNode.getCommentLines() + (c->getPosition().getEndLine() - c->getPosition().getLine() + 1));
      }
    }
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::declaration::FunctionDeclaration& node, bool callVirtualBase)
  {
    VISIT_END(node, false);
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::expression::FunctionExpression& node, bool callVirtualBase)
  {
    VISIT_END(node, false);
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::expression::ArrowFunctionExpression& node, bool callVirtualBase)
  {
    VISIT_END(node, false);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::IfStatement& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, true);
    incNOB();
    incNL(eligibleForNLE(node));
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::IfStatement& node, bool callVirtualBase)
  {
    VISIT_END(node, callVirtualBase);
    decNL(eligibleForNLE(node));
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::ForStatement& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, true);
    incNOB();
    incNL(true);
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::ForStatement& node, bool callVirtualBase)
  {
    VisitorAbstractNodes::visit(node, callVirtualBase);
    VISIT_END(node, callVirtualBase);
    decNL(true);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::WhileStatement& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, true);
    incNOB();
    incNL(true);
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::WhileStatement& node, bool callVirtualBase)
  {
    VISIT_END(node, true);
    decNL(true);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::SwitchCase& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, true);
    incNOB();
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::SwitchCase& node, bool callVirtualBase)
  {
    VISIT_END(node, callVirtualBase);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::SwitchStatement& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, true);
    incNL(true);
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::SwitchStatement& node, bool callVirtualBase)
  {
    VISIT_END(node, callVirtualBase);
    decNL(true);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::ForInStatement& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, true);
    incNOB();
    incNL(true);
  }
  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::ForInStatement& node, bool callVirtualBase)
  {
    VISIT_END(node, callVirtualBase);
    decNL(true);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::expression::ConditionalExpression& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, true);
    incNL(true);
    incNOB();
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::expression::ConditionalExpression& node, bool callVirtualBase)
  {
    VISIT_END(node, callVirtualBase);
    decNL(true);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::Statement& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, callVirtualBase);
    if (!lastLimScopeNodeId.empty()) {
      lim::asg::logical::Scope& scopeLimNode = dynamic_cast<lim::asg::logical::Scope&>(limFactory.getRef(lastLimScopeNodeId.top()));
      if (lim::asg::Common::getIsPackage(scopeLimNode) && !packageStack.empty()) {
        packageStack.top().lines.insert(node.getPosition().getLine());
        packageStack.top().lines.insert(node.getPosition().getEndLine());
      }
    }
    if (!javascript::asg::Common::getIsBlockStatement(node)) {
      incNOS();
    }
  }

  void JSAN2LimVisitor::visit(const javascript::asg::expression::LogicalExpression& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, callVirtualBase);
    // "||" or "&&" in conditions increase the number of possible branches
    incNOB();
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::CatchClause& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, callVirtualBase);
    // catch clauses increase the number of branches
    incNOB();
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::TryStatement& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, callVirtualBase);
    incNL(true);
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::TryStatement& node, bool callVirtualBase)
  {
    decNL(true);
    VISIT_END(node, callVirtualBase);
  }

  void JSAN2LimVisitor::visit(const javascript::asg::statement::BlockStatement& node, bool callVirtualBase)
  {
    VISIT_BEGIN(node, callVirtualBase);

    if (node.getParent() && Common::getIsBlockStatement(*node.getParent())) {
      incNL(true);
    }
  }

  void JSAN2LimVisitor::visitEnd(const javascript::asg::statement::BlockStatement& node, bool callVirtualBase)
  {
    if (node.getParent() && Common::getIsBlockStatement(*node.getParent())) {
      decNL(true);
    }

    VISIT_END(node, callVirtualBase);
  }

  void JSAN2LimVisitor::finalize(const lim::asg::Factory& factory)
  {

    lim::asg::Factory::const_iterator i = factory.begin(), end = factory.end();
    for (; i != end; ++i) {

      lim::asg::base::Base& node = const_cast<lim::asg::base::Base&>(**i);

      setLineMetricsOfComponent(node);

      if (lim::asg::Common::getIsMember(node)) {
        dynamic_cast<lim::asg::logical::Member&>(node).setLanguage(lim::asg::LanguageKind::lnkJavaScript);
      }
    }
  }

  void JSAN2LimVisitor::setLineMetricsOfComponent(lim::asg::base::Base& node)
  {
    // COMPONENT
    if (lim::asg::Common::getIsComponent(node)) {
      lim::asg::base::Component& component = dynamic_cast<lim::asg::base::Component&>(node);
      const lim::asg::ReverseEdges& revEdges = component.getFactory().getReverseEdges();

      // Files in the Component (through reverse belongsTo and forward isContainedIn)
      std::set<const lim::asg::physical::File*> files;
      lim::asg::ListIterator<lim::asg::base::Base> m = revEdges.constIteratorBegin(component.getId(), lim::asg::EdgeKind::edkMember_BelongsTo),
                             mEnd = revEdges.constIteratorEnd(component.getId(), lim::asg::EdgeKind::edkMember_BelongsTo);
      for (; m != mEnd; ++m) {
        const lim::asg::logical::Member& member = dynamic_cast<const lim::asg::logical::Member&>(*m);
        lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> f = member.getIsContainedInListIteratorAssocBegin(),
                                          fEnd = member.getIsContainedInListIteratorAssocEnd();
        for (; f != fEnd; ++f) {
          files.insert(&*f);
        }
      }

      size_t tloc = 0, tlloc = 0;
      std::set<const lim::asg::physical::File *>::const_iterator f = files.begin(),
                                     fEnd = files.end();
      for (; f != fEnd; ++f) {
        tloc += (*f)->getLOC();
        tlloc += (*f)->getLLOC();
      }

      component.setTLOC(tloc);
      component.setTLLOC(tlloc);

      // Increase TLOC and TLLOC of parent component (only root component has child components now)
      lim::asg::ListIterator<lim::asg::base::Base> c = revEdges.constIteratorBegin(component.getId(), lim::asg::EdgeKind::edkComponent_Contains),
                             cEnd = revEdges.constIteratorEnd(component.getId(), lim::asg::EdgeKind::edkComponent_Contains);
      for (; c != cEnd; ++c) {
        lim::asg::base::Component& component = const_cast<lim::asg::base::Component&>(dynamic_cast<const lim::asg::base::Component&>(*c));
        component.setTLOC(component.getTLOC() + tloc);
        component.setTLLOC(component.getTLLOC() + tlloc);
      }
    }
  }

  lim::asg::physical::File& JSAN2LimVisitor::createFile(const javascript::asg::base::Positioned& pos)
  {
    const javascript::asg::Range& range = pos.getPosition();
    lim::asg::physical::File& file = limFactory.createFile(range.getPath());

    if (javascriptFactory.getFilterState(pos.getId()) == javascript::asg::Filter::Filtered) {
      limFactory.setFilteredThisNodeOnly(file.getId());
    }

    fileStack.push(file.getId());

    return file;
  }
  std::string JSAN2LimVisitor::getDemangledName()
  {
    std::string demangledName = "";
    for (std::vector<std::string>::iterator it = demangledNameParts.begin(); it != demangledNameParts.end(); ++it) {
      demangledName += *it + ".";
    }
    return demangledName;
  }

  void JSAN2LimVisitor::fillMemberData(lim::asg::logical::Member& member)
  {
    std::string demangledName = getDemangledName();
    member.setDemangledName(demangledName + member.getName());
    member.setMangledName(demangledName + member.getName());
    SAFE_EDGE(member, BelongsTo, lim::asg::base::Component, component.getId());
  }

  bool JSAN2LimVisitor::isMethodParameter(const javascript::asg::statement::Pattern& patternNode)
  {
    javascript::asg::base::Base* parentNode = patternNode.getParent();
    if (!parentNode) {
      common::WriteMsg::write(common::WriteMsg::mlDebug, "Missing parent of node %d", patternNode.getId());
      return false;
    }

    if (javascript::asg::Common::getIsFunction(*parentNode)) {
      javascript::asg::statement::Function& functionDeclaration = dynamic_cast<javascript::asg::statement::Function&>(*parentNode);
      javascript::asg::ListIterator<javascript::asg::statement::Pattern> begin = functionDeclaration.getParamsListIteratorBegin();
      javascript::asg::ListIterator<javascript::asg::statement::Pattern> end = functionDeclaration.getParamsListIteratorEnd();
      for (; begin != end; ++begin) {
        if (patternNode.getId() == begin->getId()) {
          return true;
        }
      }
    }

    return false;
  }

  void JSAN2LimVisitor::addIsContainedInEdge(lim::asg::logical::Member& limNode, const javascript::asg::base::Positioned& posWC)
  {
    const javascript::asg::Range& pos = posWC.getPosition();

    lim::asg::SourcePosition limPos;
    limPos.setLine(pos.getWideLine());
    limPos.setColumn(pos.getWideCol());
    limPos.setEndLine(pos.getWideEndLine());
    limPos.setEndColumn(pos.getWideEndCol());
    limPos.setRealizationLevel(lim::asg::relDefines);

    string filePath = pos.getPath();

    if (!filePath.empty()) {
      lim::asg::physical::File& file = createFile(posWC);

      bool found = false;
      lim::asg::ListIteratorAssocSourcePosition<lim::asg::physical::File> spIt = limNode.getIsContainedInListIteratorAssocBegin();
      for (; spIt != limNode.getIsContainedInListIteratorAssocEnd(); ++spIt) {
        lim::asg::SourcePosition oldSp = spIt.getAssocClass();
        if (
          spIt->getId() == file.getId()
          && oldSp.getLine() == pos.getWideLine()
          && oldSp.getColumn() == pos.getWideCol()
          && oldSp.getEndLine() == pos.getWideEndLine()
          && oldSp.getEndColumn() == pos.getWideEndCol()) {
          found = true;
          break;
        }
      }

      if (!found)
        limNode.addIsContainedIn(file.getId(), limPos);
    }
  }

  bool JSAN2LimVisitor::isLimCompatible(const javascript::asg::base::Positioned& node)
  {
    bool metPar = false;
    if (javascript::asg::Common::getIsPattern(node)) {
      const javascript::asg::statement::Pattern& patternNode = dynamic_cast<const javascript::asg::statement::Pattern&>(node);
      metPar = isMethodParameter(patternNode);
    }

    return javascript::asg::Common::getIsProgram(node)
      || javascript::asg::Common::getIsMethodDefinition(node)
      || javascript::asg::Common::getIsFunction(node)
      || javascript::asg::Common::getIsClass(node)
      || (javascript::asg::Common::getIsVariableDeclaration(node) && classStack.empty() && methodStack.empty())
      || metPar;
  }

  /*
    Metric counter method definition start here
    */

  // Number of Statements
  void JSAN2LimVisitor::incNOS()
  {
    if (!methodStack.empty())
      methodStack.top().NOS++;
    if (!packageStack.empty())
      packageStack.top().NOS++;
  }

  void JSAN2LimVisitor::incNOB()
  {

    if (!methodStack.empty())
      methodStack.top().NOB++;
    if (!packageStack.empty())
      packageStack.top().NOB++;
  }

  void JSAN2LimVisitor::incNL(bool NLE)
  {

    if (methodStack.empty())
      return;

    // Nesting Level
    methodStack.top().currentNL++;
    if (methodStack.top().currentNL > methodStack.top().NL)
      methodStack.top().NL = methodStack.top().currentNL;

    // Nesting Level Else-If
    if (NLE) {
      methodStack.top().currentNLE++;
      if (methodStack.top().currentNLE > methodStack.top().NLE)
        methodStack.top().NLE = methodStack.top().currentNLE;
    }
  }

  void JSAN2LimVisitor::decNL(bool NLE)
  {

    if (methodStack.empty())
      return;
    methodStack.top().currentNL--;
    if (NLE)
      methodStack.top().currentNLE--;
  }
  bool JSAN2LimVisitor::eligibleForNLE(const javascript::asg::statement::IfStatement& sel)
  {
    if (
      sel.getParent()
      && javascript::asg::Common::getIsIfStatement(*sel.getParent())
      && dynamic_cast<javascript::asg::statement::IfStatement&>(*sel.getParent()).getAlternate()
      && dynamic_cast<javascript::asg::statement::IfStatement&>(*sel.getParent()).getAlternate()->getId() == sel.getId()) {
      return false;
    }
    return true;
  }

  bool operator<=(const lim::asg::logical::Scope& lhs, const lim::asg::logical::Scope& rhs)
  {
    if (lim::asg::Common::getIsMethod(lhs))
      return true;
    else if (lim::asg::Common::getIsClass(lhs))
      return !lim::asg::Common::getIsMethod(rhs);
    else if (lim::asg::Common::getIsPackage(lhs))
      return lim::asg::Common::getIsPackage(rhs);
    return false;
  }
}
}
