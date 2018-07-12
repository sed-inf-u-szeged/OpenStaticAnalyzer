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

#include "../inc/python2lim.h"
#include "../inc/messages.h"
#include <iostream>


using namespace std;

using namespace columbus::python::asg;

#define SAFE_EDGE( node, name, type, param ) \
  do \
  { \
    bool node##_found = false; \
    lim::asg::ListIterator<type> node##_it = node.get##name##ListIteratorBegin(); \
    for ( ; node##_it != node.get##name##ListIteratorEnd(); ++node##_it ) \
    { \
      if ( node##_it->getId() == param ) { node##_found = true; break; } \
    } \
    if ( ! node##_found ) \
    { \
      node.add##name( param ); \
    } \
  } \
  while ( false )


namespace columbus { namespace python {

  Python2LimVisitor::Python2LimVisitor(columbus::python::asg::Factory& pyFact,
                                       columbus::lim::asg::Factory& limFact,
                                       LimOrigin& origin,
                                       const std::string& componentName,
                                       columbus::python::Python2LimVisitor::Key2IdMapType& key2Ids
                                       ):
                                        pyFact(pyFact),
                                        limFact(limFact),
                                        origin(origin),
                                        actualCompNodeId(0),
                                        pythonKey2LimId(key2Ids)
  {
    pythonId2limId.insert(make_pair(pyFact.getRoot()->getId(), limFact.getRoot()->getId()));

    limFact.getRoot()->setName((dynamic_cast<python::asg::module::Package&>(*pyFact.getRoot())).getName());
    limFact.getRoot()->setMangledName(python::asg::Common::getUniqueName(*pyFact.getRoot()));
    limFact.getRoot()->setDemangledName(python::asg::Common::getUniqueName(*pyFact.getRoot()));

    lim::asg::base::Component& actualComp = limFact.createComponent(componentName);
    actualCompNodeId = actualComp.getId();
    limFact.getComponentRootRef().addContains(&actualComp);

    origin.addCompIdCppIdLimIdToMap( actualCompNodeId, pyFact.getRoot()->getId(), limFact.getRoot()->getId() );
  }


  Python2LimVisitor::~Python2LimVisitor() {
  }

  void Python2LimVisitor::visit(const columbus::python::asg::base::Positioned& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);
    if ( !(Common::getIsComment(_node) || Common::getIsDocstring(_node)) ){

      unsigned commentLoc = 0;
      for(ListIterator<base::Comment> it =_node.getCommentsListIteratorBegin(); it != _node.getCommentsListIteratorEnd(); ++it){
        commentLoc += static_cast<unsigned>(std::count(it->getText().begin(), it->getText().end(), '\n') + 1);
      }
      infoStack.back()->CLOC += commentLoc;
    } else {
      Range range = _node.getPosition();
      lim::asg::physical::File& file = buildFileNode(range);
      fileNodeIdCommentLinesMap[file.getId()] += boost::icl::discrete_interval<unsigned>::closed(range.getLine(), range.getEndLine());
    }
  }

/**********
 * MODULE *
 **********/

  void Python2LimVisitor::visit(const columbus::python::asg::module::Package& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    lim::asg::logical::Package& limPackageNode = dynamic_cast<lim::asg::logical::Package&>(createCompleteLimNode(_node));
    setComponentData(limPackageNode.getId());
    setLimMemberData(_node, limPackageNode);
  }


  void Python2LimVisitor::visitEnd(const columbus::python::asg::module::Package& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd(_node, callVirtualBase);

  }


  void Python2LimVisitor::visit(const columbus::python::asg::module::Module& _node, bool callVirtualBase ) {

    ScopeInfo* scopeInfo = new ScopeInfo();
    infoStack.push_back(scopeInfo);
    scopeInfo->node = &_node;

    lim::asg::logical::Package& limPackageNode = dynamic_cast<lim::asg::logical::Package&>(createCompleteLimNode(_node));

    processDocstring(limPackageNode, _node.getDocstring());
    scopeInfo->limNode = &limPackageNode;
    createFictiveMethod(limPackageNode);

    limPackageNode.setPackageKind( lim::asg::pkModule );

    // map Module line info to the lim Package
    limPackageNode.setTLOC( _node.getPosition().getEndLine() - _node.getPosition().getLine() + 1 );
    limPackageNode.setTLLOC( _node.getLloc() );

    // map Module line info to the corresponding lim File too
    lim::asg::physical::File& file = buildFileNode( _node.getPosition());
    file.setLOC( _node.getPosition().getEndLine() - _node.getPosition().getLine() + 1 );
    file.setLLOC( _node.getLloc() );

    setComponentData(limPackageNode.getId());
    setLimMemberData(_node, limPackageNode);

    VisitorAbstractNodes::visit(_node, callVirtualBase);
  }


  void Python2LimVisitor::visitEnd(const columbus::python::asg::module::Module& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd(_node, callVirtualBase);

    ScopeInfo* scopeInfo = infoStack.back();
    fillCollectedMethodData(dynamic_cast<lim::asg::logical::Method&>(*scopeInfo->getMethodInfo()->limNode), scopeInfo->getMethodInfo());
    dynamic_cast<lim::asg::logical::Package&>(*scopeInfo->limNode).setCommentLines(scopeInfo->CLOC);

    delete scopeInfo->fictiveMethodInfo;
    delete scopeInfo;
    infoStack.pop_back();
  }

/*************
 * STATEMENT *
 *************/

  void Python2LimVisitor::visit(const columbus::python::asg::statement::ClassDef& _node, bool callVirtualBase ) {
    ScopeInfo* scopeInfo = new ScopeInfo();
    infoStack.push_back(scopeInfo);
    scopeInfo->node = &_node;

    lim::asg::logical::Class& limClassNode = dynamic_cast<lim::asg::logical::Class&>(createCompleteLimNode(_node));
    processDocstring(limClassNode, _node.getDocstring());

    scopeInfo->limNode = &limClassNode;
    createFictiveMethod(limClassNode);

    setComponentData(limClassNode.getId());
    setLimMemberData(_node, limClassNode);
    setLimClassData(_node, limClassNode);

    // (L)LOC from PAN is really T(L)LOC
    limClassNode.setTLOC( _node.getPosition().getEndLine() - _node.getPosition().getLine() + 1 );
    limClassNode.setTLLOC( _node.getLloc() );

    if(!_node.getBaseSpecifierIsEmpty()) {
      set<NodeId> subSet;
      ListIterator<statement::BaseSpecifier> it = _node.getBaseSpecifierListIteratorBegin();
      for(; it != _node.getBaseSpecifierListIteratorEnd(); ++it){
        const statement::BaseSpecifier& bsNode = *it;
        if(bsNode.getDerivesFrom() && python::asg::Common::getIsClassDef(*bsNode.getDerivesFrom())) {
          python::asg::statement::ClassDef& classDef = dynamic_cast<python::asg::statement::ClassDef&>(*bsNode.getDerivesFrom());
          if (classDef.getRefersTo()) {
              subSet.insert(createType(classDef.getRefersTo()->getId()));
          }
        }
      }
      set<NodeId>::const_iterator subIt;
      for(subIt = subSet.begin(); subIt != subSet.end(); subIt++) {
        limClassNode.addIsSubclass(*subIt);
      }
    }
    
    VisitorAbstractNodes::visit(_node, callVirtualBase);
  }


  void Python2LimVisitor::visitEnd(const columbus::python::asg::statement::ClassDef& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd(_node, callVirtualBase);

    ScopeInfo* scopeInfo = infoStack.back();
    fillCollectedMethodData(dynamic_cast<lim::asg::logical::Method&>(*scopeInfo->getMethodInfo()->limNode), scopeInfo->getMethodInfo());
    dynamic_cast<lim::asg::logical::Class&>(*scopeInfo->limNode).setCommentLines(scopeInfo->CLOC);

    delete scopeInfo->fictiveMethodInfo;
    delete scopeInfo;
    infoStack.pop_back();
  }


  void Python2LimVisitor::visit(const columbus::python::asg::statement::FunctionDef& _node, bool callVirtualBase ) {

    MethodInfo* methodInfo = new MethodInfo();
    infoStack.push_back(methodInfo);
    methodInfo->node = &_node;

    lim::asg::logical::Method& limMethodNode = dynamic_cast<lim::asg::logical::Method&>(createCompleteLimNode(_node));
    processDocstring(limMethodNode, _node.getDocstring());

    methodInfo->limNode = &limMethodNode;

    setComponentData(limMethodNode.getId());
    setLimMemberData(_node, limMethodNode);
    setLimMethodData(_node, limMethodNode);

    // (L)LOC from PAN is really T(L)LOC
    limMethodNode.setTLOC( _node.getPosition().getEndLine() - _node.getPosition().getLine() + 1 );
    limMethodNode.setTLLOC( _node.getLloc() );

    VisitorAbstractNodes::visit(_node, callVirtualBase);
  }


  void Python2LimVisitor::visitEnd(const columbus::python::asg::statement::FunctionDef& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd(_node, callVirtualBase);

    MethodInfo* methodInfo = dynamic_cast<MethodInfo*>(infoStack.back());
    fillCollectedMethodData(dynamic_cast<lim::asg::logical::Method&>(*methodInfo->limNode), methodInfo);
    dynamic_cast<lim::asg::logical::Method&>(*methodInfo->limNode).setCommentLines(methodInfo->CLOC);

    delete methodInfo;
    infoStack.pop_back();
  }


  void Python2LimVisitor::visit(const columbus::python::asg::statement::Parameter& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    if (_node.getParent() && python::asg::Common::getIsFunctionDef(*_node.getParent())) { // TODO lambda?
      if (!infoStack.empty()) {
        MethodInfo* methodInfo = dynamic_cast<MethodInfo*>(infoStack.back());

        lim::asg::logical::Parameter& limParam = dynamic_cast<lim::asg::logical::Parameter&>(createCompleteLimNode(_node));
        dynamic_cast<lim::asg::logical::Method&>(*methodInfo->limNode).addParameter(limParam.getId());

        if(_node.getRefersTo()) {
          python::asg::module::Object& objNode = dynamic_cast<python::asg::module::Object&>(*_node.getRefersTo());
          NodeId limType = createType(objNode.getId());
          if(limFact.getExist(limType)) {
            limParam.setType(limType);
          }
          limParam.setParamKind(lim::asg::pmkInOut);
        }
      }
    }
  }


  void Python2LimVisitor::visit(const columbus::python::asg::statement::Try& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
    incNL( true );
  }

  void Python2LimVisitor::visitEnd(const columbus::python::asg::statement::Try& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd(_node, callVirtualBase);

    decNL( true );
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::With& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
    incNL( true );
  }

  void Python2LimVisitor::visitEnd(const columbus::python::asg::statement::With& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd(_node, callVirtualBase);

    decNL( true );
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Iteration& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNL(true);
    incNos(_node);
    incNob(_node);
  }

  void Python2LimVisitor::visitEnd(const columbus::python::asg::statement::Iteration& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd(_node, callVirtualBase);

    decNL(true);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::If& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNL(eligibleForNLE(_node));
    incNos(_node);
    incNob(_node);
  }

  void Python2LimVisitor::visitEnd(const columbus::python::asg::statement::If& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visitEnd(_node, callVirtualBase);

    decNL(eligibleForNLE(_node));
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Handler& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNob(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Global& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Raise& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    expression::Expression* expr = _node.getTypeExpression();
    if(expr) {
      type::Type* type = expr->getType();
      if(type) {
        NodeId limType = createType(type->getId());
        if(limFact.getExist(limType)) {
          if (!infoStack.empty()) {
            infoStack.back()->getMethodInfo()->throws.insert(limType);
          }
        }
      }
    }

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Assert& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Pass& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Assign& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Delete& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::ImportStatement& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Return& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Print& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Break& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Continue& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Exec& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    incNos(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::statement::Alias& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    base::Base* ref = _node.getRefersTo();
    if(ref) {
      if(python::asg::Common::getIsObject(*ref)) {
        NodeId limType = createType(ref->getId());
        if(limFact.getExist(limType)) {
          if (!infoStack.empty()) {
            infoStack.back()->getMethodInfo()->uses.insert(limType);
          }
        }
      }
    }
  }

/**************
 * EXPRESSION *
 **************/

  void Python2LimVisitor::visit(const columbus::python::asg::expression::Identifier& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    bool isLimAttr = false;

    if (_node.getParent() && python::asg::Common::getIsTargetList(*_node.getParent()) &&
        _node.getParent()->getParent() && python::asg::Common::getIsAssign(*_node.getParent()->getParent()))
    {
      NodeId pyParent = getPythonParent(_node);
      if (pyParent) {
        if (!python::asg::Common::getIsFunctionDef(pyFact.getRef(pyParent))) { // TODO global variables
          isLimAttr = true;
        }
      }
    }

    if (isLimAttr) {
      lim::asg::logical::Attribute& limAttrib = dynamic_cast<lim::asg::logical::Attribute&>(createCompleteLimNode(_node));

      if (limAttrib.getIsContainedInIsEmpty()) { // only the first declaration counts now
        setLimMemberData(_node, limAttrib);
        setLimAttributeData(_node, limAttrib);
        setComponentData(limAttrib.getId());
      }
    }

    if(_node.getRefersTo()) {

      if(_node.getParent() && !python::asg::Common::getIsAttributeRef(*_node.getParent())) {

        python::asg::module::Object& objNode = dynamic_cast<python::asg::module::Object&>(*_node.getRefersTo());
        NodeId instId = createType(objNode.getId());
        lim::asg::type::TypeFormerType *tft;
        if(limFact.getExist(instId)) {
          lim::asg::ListIterator<lim::asg::type::TypeFormer> tfIt = dynamic_cast<lim::asg::type::Type&>(limFact.getRef(instId)).getTypeFormerListIteratorBegin();
          if(dynamic_cast<lim::asg::type::Type&>(limFact.getRef(instId)).getTypeFormerSize() == 1) {
            tft = &const_cast<lim::asg::type::TypeFormerType&>(dynamic_cast<const lim::asg::type::TypeFormerType&>(*tfIt));
            if(lim::asg::Common::getIsClass(*tft->getRefersTo())) {
              if (!infoStack.empty()) {
                infoStack.back()->getMethodInfo()->instantiates.insert(instId);
              }
            }
          }
        }

      } else if(_node.getParent() && python::asg::Common::getIsAttributeRef(*_node.getParent()) && python::asg::Common::getIsObject(*_node.getRefersTo())) {

        python::asg::module::Object& objNode = dynamic_cast<python::asg::module::Object&>(*_node.getRefersTo());
        if(objNode.getRefersToSize() == 1) {
          python::asg::ListIterator<base::Positioned> refIt = objNode.getRefersToListIteratorBegin();
          const python::asg::base::Positioned& baseNode = *refIt;
          NodeId baseParId = getPythonParent(baseNode);
          if(python::asg::Common::getIsIdentifier(baseNode) && pyFact.getExist(baseParId) &&
            python::asg::Common::getIsClassDef(pyFact.getRef(baseParId)) && limFact.getExist(getLimNodeId(baseNode.getId())))
          {
            if (!infoStack.empty()) {
              infoStack.back()->getMethodInfo()->accessesAttribute.insert(baseNode.getId());
            }
          }
        }

      }

    }

  }


  void Python2LimVisitor::visit(const columbus::python::asg::expression::IfExpression& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);
    incNob(_node);
  }

  void Python2LimVisitor::visit(const columbus::python::asg::expression::Call& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    statement::CompoundStatement* ref = _node.getRefersTo();
    if (ref && python::asg::Common::getIsFunctionDef(*ref)) {
      if (!infoStack.empty()) {
        infoStack.back()->getMethodInfo()->calls.insert(ref->getId());
      }
    }
  }


  void Python2LimVisitor::visit(const columbus::python::asg::expression::BinaryLogical& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    if (_node.getKind() == python::asg::blkAnd || _node.getKind() == python::asg::blkOr) {
      incNob(_node);
    }
  }

  void Python2LimVisitor::visit(const columbus::python::asg::expression::Expression& _node, bool callVirtualBase ) {
    VisitorAbstractNodes::visit(_node, callVirtualBase);

    python::asg::base::Base* parent = _node.getParent();
    if (parent) {
      if (python::asg::Common::getIsSuite(*parent)) {
        incNos(_node);
      }
    }
  }

/*************
 * LIM GRAPH *
 *************/

  NodeId Python2LimVisitor::getLimNodeId(NodeId pythonId) {
    NodeIdMapType::const_iterator nIt = pythonId2limId.find(pythonId);
    if(nIt != pythonId2limId.end()) {
      return nIt->second;
    } else {
      const python::asg::base::Base& bn = pyFact.getRef(pythonId);
      if (python::asg::Common::getIsIdentifier(bn)) { // only for attributes
        string attrUname = dynamic_cast<const python::asg::expression::Identifier&>(bn).getPosition().getPath() + "#" + python::asg::Common::getUniqueName(bn);
        Key nodeKey = limFact.getStringTable().set(attrUname);
        Key2IdMapType::const_iterator kIt = pythonKey2LimId.find(nodeKey);
        if(kIt != pythonKey2LimId.end()) {
          return kIt->second;
        }
      }
      return 0;
    }
  }


  lim::asg::base::Base& Python2LimVisitor::createIncompleteLimNode(const python::asg::base::Base& _node) {
    return createLimNode(_node, false);
  }


  lim::asg::base::Base& Python2LimVisitor::createCompleteLimNode(const python::asg::base::Base& _node) {
    return createLimNode(_node, true);
  }


  lim::asg::base::Base& Python2LimVisitor::createLimNode(const python::asg::base::Base& _node, bool isComplete) {
    NodeId pyId = _node.getId();
    NodeId limId = getLimNodeId(pyId);

    if(limId != 0) {

      if(isComplete)
        incompleteNodes.erase(limId);
      return limFact.getRef(limId);

    } else {

      lim::asg::base::Named* newLimNode = NULL;

      if(python::asg::Common::getIsClassDef(_node)) {

        newLimNode = dynamic_cast<lim::asg::base::Named*>(limFact.createNode(lim::asg::ndkClass));
        newLimNode->setName(dynamic_cast<const python::asg::statement::ClassDef&>(_node).getName());
        lim::asg::logical::Class* limNode = dynamic_cast<lim::asg::logical::Class*>(newLimNode);
        string uniqueName = python::asg::Common::getUniqueName(_node);
        limNode->setMangledName(uniqueName);
        limNode->setDemangledName(uniqueName);

      } else if(python::asg::Common::getIsFunctionDef(_node)) {

        newLimNode = dynamic_cast<lim::asg::base::Named*>(limFact.createNode(lim::asg::ndkMethod));
        newLimNode->setName(dynamic_cast<const python::asg::statement::FunctionDef&>(_node).getName());
        lim::asg::logical::Method* limNode = dynamic_cast<lim::asg::logical::Method*>(newLimNode);
        string uniqueName = python::asg::Common::getUniqueName(_node);
        limNode->setMangledName(uniqueName);
        limNode->setDemangledName(uniqueName);

      } else if(python::asg::Common::getIsParameter(_node)) {

        newLimNode = dynamic_cast<lim::asg::base::Named*>(limFact.createNode(lim::asg::ndkParameter));
        newLimNode->setName(dynamic_cast<const python::asg::statement::Parameter&>(_node).getName());
        string uniqueName = python::asg::Common::getUniqueName(_node);

      } else if(python::asg::Common::getIsModule(_node)) {

        newLimNode = dynamic_cast<lim::asg::base::Named*>(limFact.createNode(lim::asg::ndkPackage));
        newLimNode->setName(dynamic_cast<const python::asg::module::Module&>(_node).getName());
        lim::asg::logical::Package* limNode = dynamic_cast<lim::asg::logical::Package*>(newLimNode);
        string uniqueName = python::asg::Common::getUniqueName(_node);
        limNode->setMangledName(uniqueName);
        limNode->setDemangledName(uniqueName);

      } else if(python::asg::Common::getIsIdentifier(_node)) {

        newLimNode = dynamic_cast<lim::asg::base::Named*>(limFact.createNode(lim::asg::ndkAttribute));
        newLimNode->setName(dynamic_cast<const python::asg::expression::Identifier&>(_node).getName());
        lim::asg::logical::Attribute* limNode = dynamic_cast<lim::asg::logical::Attribute*>(newLimNode);
        string uniqueName = python::asg::Common::getUniqueName(_node);
        limNode->setMangledName(uniqueName);
        limNode->setDemangledName(uniqueName);
        string attrUname = dynamic_cast<const python::asg::expression::Identifier&>(_node).getPosition().getPath() + "#" + uniqueName;
        pythonKey2LimId.insert(make_pair(limFact.getStringTable().set(attrUname),newLimNode->getId()));

      } else if(python::asg::Common::getIsPackage(_node)) {

        newLimNode = dynamic_cast<lim::asg::base::Named*>(limFact.createNode(lim::asg::ndkPackage));
        newLimNode->setName(dynamic_cast<const python::asg::module::Package&>(_node).getName());
        lim::asg::logical::Package* limNode = dynamic_cast<lim::asg::logical::Package*>(newLimNode);
        string uniqueName = python::asg::Common::getUniqueName(_node);
        limNode->setMangledName(uniqueName);
        limNode->setDemangledName(uniqueName);

      } else {

        throw PythonException(COLUMBUS_LOCATION, CMSG_INVALID_NODEKIND);

      }

      pythonId2limId.insert(make_pair(_node.getId(), newLimNode->getId()));
      origin.addCompIdCppIdLimIdToMap( actualCompNodeId, _node.getId(), newLimNode->getId() );

      if(!isComplete)
        incompleteNodes.insert((*newLimNode).getId());

      if(pyFact.getFilterState(_node.getId()) == python::asg::Filter::Filtered) {
        limFact.setFiltered((*newLimNode).getId());
      }

      return *newLimNode;

    }
  }


  void Python2LimVisitor::setLimMemberData(const columbus::python::asg::base::Base& _node, columbus::lim::asg::logical::Member& limMember) {

    limMember.setIsStatic(false);

    if ( ! lim::asg::Common::getIsPackage( limMember ) || dynamic_cast<const lim::asg::logical::Package&>( limMember ).getPackageKind() == lim::asg::pkModule ) {
      python::asg::Range pyRange = dynamic_cast<const python::asg::base::Positioned&>(_node).getPosition();
      lim::asg::SourcePosition sourcePosition = lim::asg::SourcePosition(lim::asg::relDefines, pyRange.getLine(), pyRange.getCol(), pyRange.getEndLine(), pyRange.getEndCol());
      limMember.addIsContainedIn( &buildFileNode(pyRange), sourcePosition );
    }

    if (_node.getId() == pyFact.getRoot()->getId())
      return;

    NodeId pythonParentId = getPythonParent(_node);

    if (!pyFact.getExist(pythonParentId)) {
      throw PythonException(COLUMBUS_LOCATION, CMSG_WRONG_ASG);
    }

    lim::asg::logical::Scope& limParent = dynamic_cast<lim::asg::logical::Scope&>(createIncompleteLimNode(pyFact.getRef(pythonParentId)));
    SAFE_EDGE( limParent, Member, lim::asg::logical::Member, limMember.getId() );
  }

  void Python2LimVisitor::processDocstring(lim::asg::logical::Member& member, python::asg::base::Docstring* docstring){
    if (docstring){
      lim::asg::base::Comment& comment = limFact.createComment(docstring->getText());
      member.addComment(comment.getId());
    }
  }

  void Python2LimVisitor::setLimClassData(const columbus::python::asg::statement::Statement& _node, columbus::lim::asg::logical::Class& limClass) {

    limClass.setClassKind(lim::asg::clkClass);

  }


  void Python2LimVisitor::setLimMethodData(const columbus::python::asg::statement::Statement& _node, columbus::lim::asg::logical::Method& limMethod) {

    limMethod.setMethodKind(lim::asg::mekNormal);

    type::Type* retType = dynamic_cast<const python::asg::statement::FunctionDef&>(_node).getReturnType();
    if(retType) {
      NodeId limType = createType(retType->getId());
      if(limFact.getExist(limType)) {
        limMethod.addReturns(limType);
      }
    }

  }


  void Python2LimVisitor::setFictiveMethodData(columbus::lim::asg::logical::Method& fictiveLimMethod) {

    fictiveLimMethod.setMethodKind(lim::asg::mekNormal);
    fictiveLimMethod.setIsStatic(false);
    fictiveLimMethod.setIsAbstract(false);

    // filter it out
    limFact.setFiltered(fictiveLimMethod.getId());

  }


  void Python2LimVisitor::setLimAttributeData(const columbus::python::asg::expression::Identifier& _node, columbus::lim::asg::logical::Attribute& limAttribute) {

    if(_node.getRefersTo()) {
      python::asg::module::Object& objNode = dynamic_cast<python::asg::module::Object&>(*_node.getRefersTo());
      NodeId limType = createType(objNode.getId());
      if(limFact.getExist(limType)) {
        SAFE_EDGE( limAttribute, Type, lim::asg::type::Type, limType );
      }
    }

  }


  void Python2LimVisitor::setComponentData(columbus::NodeId limNodeId) const {

    if(limFact.getFilterState(limNodeId) == lim::asg::Filter::Filtered) {
      return;
    }

    lim::asg::logical::Member& member = dynamic_cast<lim::asg::logical::Member&>(limFact.getRef(limNodeId));
    SAFE_EDGE( member, BelongsTo, lim::asg::base::Component, actualCompNodeId );

  }


  void Python2LimVisitor::fillCollectedMethodData(lim::asg::logical::Method& limMethod, MethodInfo* methodInfo) {

    limMethod.setNumberOfStatements(methodInfo->NOS);
    limMethod.setNumberOfBranches(methodInfo->NOB);
    limMethod.setNestingLevel(methodInfo->NL);
    limMethod.setNestingLevelElseIf(methodInfo->NLE);

    set<NodeId>::iterator it, itEnd;

    for (it = methodInfo->calls.begin(), itEnd = methodInfo->calls.end(); it != itEnd; ++it) {
      lim::asg::base::Base& callNode = createIncompleteLimNode(pyFact.getRef(*it));
      lim::asg::logical::MethodCall& call = limFact.createMethodCall(callNode.getId());
      limMethod.addCalls(&call);
    }

    for (it = methodInfo->accessesAttribute.begin(), itEnd = methodInfo->accessesAttribute.end(); it != itEnd; ++it) {
      lim::asg::logical::Attribute& limAttrib = dynamic_cast<lim::asg::logical::Attribute&>(createIncompleteLimNode(pyFact.getRef(*it)));
      lim::asg::logical::AttributeAccess& access = limFact.createAttributeAccess(limAttrib.getId());
      limMethod.addAccessesAttribute(&access);
    }

    for (it = methodInfo->instantiates.begin(), itEnd = methodInfo->instantiates.end(); it != itEnd; ++it) {
      limMethod.addInstantiates(*it);
    }

    for (it = methodInfo->throws.begin(), itEnd = methodInfo->throws.end(); it != itEnd; ++it) {
      limMethod.addThrows(*it);
    }

    for (it = methodInfo->uses.begin(), itEnd = methodInfo->uses.end(); it != itEnd; ++it) {
      limMethod.addUses(*it);
    }

  }


  lim::asg::logical::Method* Python2LimVisitor::createFictiveMethod(lim::asg::logical::Scope& limNode) {

    string fictShortName = "";
    if (lim::asg::Common::getIsPackage(limNode)) {
      fictShortName = "fictivePackageMethod";
    } else {
      fictShortName = "fictiveClassMethod";
    }

    string fictName = limNode.getMangledName() + "~" + fictShortName;

    lim::asg::logical::Method& fictiveLimMethod = dynamic_cast<lim::asg::logical::Method&>(*limFact.createNode(lim::asg::ndkMethod));
    fictiveLimMethod.setName(fictShortName);
    fictiveLimMethod.setMangledName(fictName);
    fictiveLimMethod.setDemangledName(fictName);
    setFictiveMethodData(fictiveLimMethod);
    limNode.addMember(fictiveLimMethod.getId());

    ScopeInfo* scopeInfo = infoStack.back();
    scopeInfo->fictiveMethodInfo = new MethodInfo();
    scopeInfo->fictiveMethodInfo->limNode = &fictiveLimMethod;

    return &fictiveLimMethod;

  }


  NodeId Python2LimVisitor::createType(columbus::NodeId pythonId) {
    NodeId pyTypeId = 0;
    unsigned int types = 0;

    if(python::asg::Common::getIsObject(pyFact.getRef(pythonId))) {
      if(dynamic_cast<python::asg::module::Object&>(pyFact.getRef(pythonId)).getTypeIsEmpty()) {
        return 0;
      }
      python::asg::ListIterator<type::Type> typeIt = dynamic_cast<python::asg::module::Object&>(pyFact.getRef(pythonId)).getTypeListIteratorBegin();
      python::asg::ListIterator<type::Type> typeItEnd = dynamic_cast<python::asg::module::Object&>(pyFact.getRef(pythonId)).getTypeListIteratorEnd();
      for(; typeIt != typeItEnd; ++typeIt){
        pyTypeId = typeIt->getId();
      }
      if(dynamic_cast<python::asg::module::Object&>(pyFact.getRef(pythonId)).getTypeSize() == 1) {
        types = 1;
      }
    } else if(python::asg::Common::getIsExpression(pyFact.getRef(pythonId))) {
      pyTypeId = dynamic_cast<python::asg::expression::Expression&>(pyFact.getRef(pythonId)).getType()->getId();
      if(!pyFact.getExist(pyTypeId)) {
        return 0;
      } else {
        types = 1;
      }
    } else if(python::asg::Common::getIsType(pyFact.getRef(pythonId))) {
      pyTypeId = pythonId;
      types = 1;
    }

    NodeId limTypeId = 0;
    NodeId typeId = 0;
    bool isClass = false;

    if(PythonType2LimTypeMap.find(pyTypeId) != PythonType2LimTypeMap.end()) {
      return PythonType2LimTypeMap[pyTypeId];
    }

    limFact.beginType();

    if(types == 1) {
      python::asg::type::Type& pyType = dynamic_cast<python::asg::type::Type&>(pyFact.getRef(pyTypeId));
      if(python::asg::Common::getIsReferenceType(pyType)) {
        if(!dynamic_cast<python::asg::type::ReferenceType&>(pyType).getRefersTo()) {
          return 0;
        }
        python::asg::base::Base& refNode = *dynamic_cast<python::asg::type::ReferenceType&>(pyType).getRefersTo();
        if(python::asg::Common::getIsClassDef(refNode)) {
          isClass = true;
          createIncompleteLimNode(refNode);
          typeId = getLimNodeId(refNode.getId());
        }
      }
      if(!isClass) {
        typeId = limFact.createSimpleType(lim::asg::stkUnknown).getId();
      }
    } else {
      typeId = limFact.createSimpleType(lim::asg::stkUnknown).getId();
    }
    lim::asg::type::TypeFormerType& tft = limFact.createTypeFormerType(typeId);
    limFact.addTypeFormer(tft.getId());

    limTypeId = limFact.endType().getId();
    PythonType2LimTypeMap.insert(make_pair(pyTypeId, limTypeId));

    return limTypeId;
  }


  NodeId Python2LimVisitor::getPythonParent(const columbus::python::asg::base::Base& _node) {
    base::Base* parent = _node.getParent();

    while(parent) {
      if(python::asg::Common::getIsClassDef(*parent) || python::asg::Common::getIsModule(*parent) ||
        python::asg::Common::getIsPackage(*parent) || python::asg::Common::getIsFunctionDef(*parent))
      {
        break;
      }
      parent = parent->getParent();
    }

    return parent ? parent->getId() : 0;
  }


  void Python2LimVisitor::incNos(const python::asg::base::Positioned& _node) {
    if (!infoStack.empty()) {
      infoStack.back()->getMethodInfo()->NOS++;
    }
  }


  void Python2LimVisitor::incNob(const python::asg::base::Base& _node) {
    if (!infoStack.empty()) {
      infoStack.back()->getMethodInfo()->NOB++;
    }
  }


  bool Python2LimVisitor::eligibleForNLE(const python::asg::statement::If& _node) {
    if (_node.getParent() && python::asg::Common::getIsSuite(*_node.getParent())) {
      python::asg::statement::Suite& suiteNode = dynamic_cast<python::asg::statement::Suite&>(*_node.getParent());
      if (suiteNode.getStatementSize() == 1) {
        if (suiteNode.getParent() && python::asg::Common::getIsIf(*suiteNode.getParent())) {
          python::asg::statement::If& ifNode = dynamic_cast<python::asg::statement::If&>(*suiteNode.getParent());
          if (ifNode.getElseBody() == &suiteNode) {
            return false;
          }
        }
      }
    }

    return true;
  }

  void Python2LimVisitor::incNL( bool NLE ) {
    if ( infoStack.empty() ) return;

    MethodInfo* methodInfo = infoStack.back()->getMethodInfo();

    // NL
    methodInfo->currentNL++;
    if ( methodInfo->currentNL > methodInfo->NL ) {
      methodInfo->NL = methodInfo->currentNL;
    }

    // NLE
    if ( NLE ) {
      methodInfo->currentNLE++;
      if ( methodInfo->currentNLE > methodInfo->NLE ) {
        methodInfo->NLE = methodInfo->currentNLE;
      }
    }
  }

  void Python2LimVisitor::decNL( bool NLE) {
    if ( infoStack.empty() ) return;

    MethodInfo* methodInfo = infoStack.back()->getMethodInfo();

    methodInfo->currentNL--;
    if ( NLE ) {
      methodInfo->currentNLE--;
    }
  }


  void Python2LimVisitor::finalize( const lim::asg::Factory&  factory ) {

    using namespace lim::asg;

    Factory::const_iterator i = factory.begin(), end = factory.end();
    for ( ; i != end; ++i ) {
      
      base::Base& node = const_cast<base::Base&>( **i );

      setLineMetrics( node );
      
      if ( Common::getIsMember( node ) ) {
        dynamic_cast<logical::Member&>( node ).setLanguage( lnkPython );
      }
    }
  }

  void Python2LimVisitor::setLineMetrics( lim::asg::base::Base& node ) {

    using namespace lim::asg;

    // FILE, already handled...
      
    // COMPONENT
    if ( Common::getIsComponent( node ) ) {
      base::Component& component = dynamic_cast<base::Component&>( node );
      const ReverseEdges& revEdges = component.getFactory().getReverseEdges();

      // Files in the Component (through reverse belongsTo and forward isContainedIn)
      std::set<const physical::File*> files;
      ListIterator<base::Base>  m = revEdges.constIteratorBegin( component.getId(), edkMember_BelongsTo ),
                                mEnd = revEdges.constIteratorEnd( component.getId(), edkMember_BelongsTo );
      for ( ; m != mEnd; ++m ) {
        const logical::Member& member = dynamic_cast<const logical::Member&>( *m );
        ListIteratorAssocSourcePosition<physical::File> f = member.getIsContainedInListIteratorAssocBegin(),
                                                        fEnd = member.getIsContainedInListIteratorAssocEnd();
        for ( ; f != fEnd; ++f ) {
          files.insert( &*f );
        }
      }

      size_t tloc = 0, tlloc = 0;
      std::set<const physical::File*>::const_iterator f = files.begin(),
                                                      fEnd = files.end();
      for ( ; f != fEnd; ++f ) {
        tloc += (*f)->getLOC();
        tlloc += (*f)->getLLOC();
      }

      component.setTLOC( tloc );
      component.setTLLOC( tlloc );

      // Increase TLOC and TLLOC of parent component (only root component has child components now)
      ListIterator<base::Base> c = revEdges.constIteratorBegin( component.getId(), edkComponent_Contains ),
                               cEnd = revEdges.constIteratorEnd( component.getId(), edkComponent_Contains );
      for ( ; c != cEnd; ++c ) {
        base::Component& component = const_cast<base::Component&>( dynamic_cast<const base::Component&>( *c ) );
        component.setTLOC(component.getTLOC() + tloc);
        component.setTLLOC(component.getTLLOC() + tlloc);
      }
    }

    // PACKAGE
    else if ( Common::getIsPackage( node ) ) {
      logical::Package& package = dynamic_cast<logical::Package&>( node );
      if ( package.getPackageKind() == pkPackage ) {
        setPackageLines( package );
      }
    }

    // CLASS/METHOD
    else if ( Common::getIsClass( node ) || Common::getIsMethod( node ) ) {
      logical::Scope& scope = dynamic_cast<logical::Scope&>( node );
      bool isClass = Common::getIsClass( node );

      // starting (L)LOC is the T(L)LOC which was set earlier
      // now it gets reduced
      int loc = scope.getTLOC();
      int lloc = scope.getTLLOC();

      ListIterator<logical::Member> memberIt = scope.getMemberListIteratorBegin(),
                                    memberEnd = scope.getMemberListIteratorEnd();
      for ( ; memberIt != memberEnd; ++memberIt ) {
        if ( Common::getIsClass( *memberIt ) || ( ! isClass && Common::getIsMethod( *memberIt ) ) ) {
          const logical::Scope& childScope = dynamic_cast<const logical::Scope&>( *memberIt );
          loc -= childScope.getTLOC();
          lloc -= childScope.getTLLOC();
        }
      }

      // truncate negative numbers
      // (because of missing line sets... FIXME)
      loc = loc < 0 ? 0 : loc;
      lloc = lloc < 0 ? 0 : lloc;

      scope.setLOC( loc );
      scope.setLLOC( lloc );
    }

  }

  void Python2LimVisitor::setPackageLines( lim::asg::logical::Package& package ) {
    using namespace lim::asg;
    int tloc = 0, tlloc = 0;
    ListIterator<logical::Member> memberIt = package.getMemberListIteratorBegin(),
                                  memberEnd = package.getMemberListIteratorEnd();
    for ( ; memberIt != memberEnd; ++memberIt ) {
      
      if ( ! Common::getIsPackage( *memberIt ) ) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_WRONG_ASG);
      }

      logical::Package& subPackage = const_cast<logical::Package&>( dynamic_cast<const logical::Package&>( *memberIt ) );

      if ( subPackage.getPackageKind() == pkPackage ) {
        setPackageLines( subPackage );
      }

      tloc += subPackage.getTLOC();
      tlloc += subPackage.getTLLOC();
    }

    package.setLOC( 0 );
    package.setLLOC( 0 );
    package.setTLOC( tloc );
    package.setTLLOC( tlloc );
  }

  lim::asg::physical::File& Python2LimVisitor::buildFileNode(const python::asg::Range& range) {
    KeyNodeIdMapType::const_iterator fileNodeIt = pathFileNodeIdMap.find(range.getPathKey());
    if (fileNodeIt != pathFileNodeIdMap.end()) {
      return dynamic_cast<lim::asg::physical::File&>(limFact.getRef(fileNodeIt->second));
    } else {
      lim::asg::physical::File& file = limFact.createFile(range.getPath());
      pathFileNodeIdMap[range.getPathKey()] = file.getId();
      return file;
    }

  }

  void Python2LimVisitor::finishVisit() {
    for (NodeId2UnsignedIntervalSetMap::const_iterator fileCommentMapIt = fileNodeIdCommentLinesMap.begin(); fileCommentMapIt != fileNodeIdCommentLinesMap.end(); ++fileCommentMapIt) {
      dynamic_cast<lim::asg::physical::File&>(limFact.getRef(fileCommentMapIt->first)).setCLOC(boost::icl::length(fileCommentMapIt->second));
    }
  }


}}
