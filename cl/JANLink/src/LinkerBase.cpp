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

#include <sstream>

#include <common/inc/WriteMessage.h>
#include <java/inc/java.h>
#include "../inc/LinkerBase.h"
#include "../inc/messages.h"

using namespace std;
using namespace common;
using namespace columbus::java::asg;


namespace columbus { namespace java { namespace linker {

LinkerBase::LinkerBase(UniqueMap& strMap, StrNodeIdMap& pathMap, Factory& fact, Factory& tmpFact)
  : LinkerHelper(strMap, pathMap), fact(fact), tmpFact(tmpFact), tmpMap(), toRemap(), skip(0)
{
  tmpMap.resize(tmpFact.size(), 0);
}

LinkerBase::~LinkerBase() {
}

void LinkerBase::visit(const base::BlockComment& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.BlockComments.find(uname);
  if (it != strMap.BlockComments.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkBlockComment, fact.size()).getId();
  strMap.BlockComments[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  base::BlockComment* newNodePtr = dynamic_cast<base::BlockComment*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "base::BlockComment"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const base::BlockComment& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const base::JavadocComment& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.JavadocComments.find(uname);
  if (it != strMap.JavadocComments.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkJavadocComment, fact.size()).getId();
  strMap.JavadocComments[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  base::JavadocComment* newNodePtr = dynamic_cast<base::JavadocComment*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "base::JavadocComment"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const base::JavadocComment& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const base::LineComment& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.LineComments.find(uname);
  if (it != strMap.LineComments.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkLineComment, fact.size()).getId();
  strMap.LineComments[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  base::LineComment* newNodePtr = dynamic_cast<base::LineComment*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "base::LineComment"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const base::LineComment& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::ArrayAccess& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkArrayAccess, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::ArrayAccess* newNodePtr = dynamic_cast<expr::ArrayAccess*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::ArrayAccess"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::ArrayAccess& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::ArrayTypeExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkArrayTypeExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::ArrayTypeExpression* newNodePtr = dynamic_cast<expr::ArrayTypeExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::ArrayTypeExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::ArrayTypeExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::Assignment& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkAssignment, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::Assignment* newNodePtr = dynamic_cast<expr::Assignment*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::Assignment"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::Assignment& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::BooleanLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkBooleanLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::BooleanLiteral* newNodePtr = dynamic_cast<expr::BooleanLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::BooleanLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::BooleanLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::CharacterLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkCharacterLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::CharacterLiteral* newNodePtr = dynamic_cast<expr::CharacterLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::CharacterLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::CharacterLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::ClassLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkClassLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::ClassLiteral* newNodePtr = dynamic_cast<expr::ClassLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::ClassLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::ClassLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::Conditional& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkConditional, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::Conditional* newNodePtr = dynamic_cast<expr::Conditional*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::Conditional"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::Conditional& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::DoubleLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkDoubleLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::DoubleLiteral* newNodePtr = dynamic_cast<expr::DoubleLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::DoubleLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::DoubleLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::Erroneous& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkErroneous, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::Erroneous* newNodePtr = dynamic_cast<expr::Erroneous*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::Erroneous"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::Erroneous& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::ErroneousTypeExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkErroneousTypeExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::ErroneousTypeExpression* newNodePtr = dynamic_cast<expr::ErroneousTypeExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::ErroneousTypeExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::ErroneousTypeExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::ExternalTypeExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkExternalTypeExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::ExternalTypeExpression* newNodePtr = dynamic_cast<expr::ExternalTypeExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::ExternalTypeExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::ExternalTypeExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::FieldAccess& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkFieldAccess, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::FieldAccess* newNodePtr = dynamic_cast<expr::FieldAccess*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::FieldAccess"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::FieldAccess& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::FloatLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkFloatLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::FloatLiteral* newNodePtr = dynamic_cast<expr::FloatLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::FloatLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::FloatLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::Identifier& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkIdentifier, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::Identifier* newNodePtr = dynamic_cast<expr::Identifier*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::Identifier"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::Identifier& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::InfixExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkInfixExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::InfixExpression* newNodePtr = dynamic_cast<expr::InfixExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::InfixExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::InfixExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::InstanceOf& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkInstanceOf, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::InstanceOf* newNodePtr = dynamic_cast<expr::InstanceOf*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::InstanceOf"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::InstanceOf& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::IntegerLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkIntegerLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::IntegerLiteral* newNodePtr = dynamic_cast<expr::IntegerLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::IntegerLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::IntegerLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::LongLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkLongLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::LongLiteral* newNodePtr = dynamic_cast<expr::LongLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::LongLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::LongLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::MarkerAnnotation& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkMarkerAnnotation, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::MarkerAnnotation* newNodePtr = dynamic_cast<expr::MarkerAnnotation*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::MarkerAnnotation"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::MarkerAnnotation& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::MethodInvocation& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkMethodInvocation, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::MethodInvocation* newNodePtr = dynamic_cast<expr::MethodInvocation*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::MethodInvocation"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::MethodInvocation& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::NewArray& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkNewArray, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::NewArray* newNodePtr = dynamic_cast<expr::NewArray*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::NewArray"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::NewArray& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::NewClass& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkNewClass, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::NewClass* newNodePtr = dynamic_cast<expr::NewClass*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::NewClass"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::NewClass& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::NormalAnnotation& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkNormalAnnotation, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::NormalAnnotation* newNodePtr = dynamic_cast<expr::NormalAnnotation*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::NormalAnnotation"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::NormalAnnotation& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::NullLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkNullLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::NullLiteral* newNodePtr = dynamic_cast<expr::NullLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::NullLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::NullLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::ParenthesizedExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkParenthesizedExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::ParenthesizedExpression* newNodePtr = dynamic_cast<expr::ParenthesizedExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::ParenthesizedExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::ParenthesizedExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::PostfixExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkPostfixExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::PostfixExpression* newNodePtr = dynamic_cast<expr::PostfixExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::PostfixExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::PostfixExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::PrefixExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkPrefixExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::PrefixExpression* newNodePtr = dynamic_cast<expr::PrefixExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::PrefixExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::PrefixExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::PrimitiveTypeExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkPrimitiveTypeExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::PrimitiveTypeExpression* newNodePtr = dynamic_cast<expr::PrimitiveTypeExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::PrimitiveTypeExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::PrimitiveTypeExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::QualifiedTypeExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkQualifiedTypeExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::QualifiedTypeExpression* newNodePtr = dynamic_cast<expr::QualifiedTypeExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::QualifiedTypeExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::QualifiedTypeExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::SimpleTypeExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkSimpleTypeExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::SimpleTypeExpression* newNodePtr = dynamic_cast<expr::SimpleTypeExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::SimpleTypeExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::SimpleTypeExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::SingleElementAnnotation& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkSingleElementAnnotation, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::SingleElementAnnotation* newNodePtr = dynamic_cast<expr::SingleElementAnnotation*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::SingleElementAnnotation"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::SingleElementAnnotation& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::StringLiteral& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkStringLiteral, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::StringLiteral* newNodePtr = dynamic_cast<expr::StringLiteral*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::StringLiteral"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::StringLiteral& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::Super& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkSuper, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::Super* newNodePtr = dynamic_cast<expr::Super*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::Super"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::Super& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::This& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkThis, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::This* newNodePtr = dynamic_cast<expr::This*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::This"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::This& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::TypeApplyExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkTypeApplyExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::TypeApplyExpression* newNodePtr = dynamic_cast<expr::TypeApplyExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::TypeApplyExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::TypeApplyExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::TypeCast& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkTypeCast, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::TypeCast* newNodePtr = dynamic_cast<expr::TypeCast*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::TypeCast"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::TypeCast& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::TypeUnionExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkTypeUnionExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::TypeUnionExpression* newNodePtr = dynamic_cast<expr::TypeUnionExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::TypeUnionExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::TypeUnionExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const expr::WildcardExpression& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkWildcardExpression, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  expr::WildcardExpression* newNodePtr = dynamic_cast<expr::WildcardExpression*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "expr::WildcardExpression"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const expr::WildcardExpression& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Assert& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkAssert, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Assert* newNodePtr = dynamic_cast<statm::Assert*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Assert"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Assert& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::BasicFor& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkBasicFor, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::BasicFor* newNodePtr = dynamic_cast<statm::BasicFor*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::BasicFor"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::BasicFor& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Block& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkBlock, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Block* newNodePtr = dynamic_cast<statm::Block*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Block"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Block& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Break& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkBreak, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Break* newNodePtr = dynamic_cast<statm::Break*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Break"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Break& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Case& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkCase, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Case* newNodePtr = dynamic_cast<statm::Case*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Case"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Case& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Continue& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkContinue, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Continue* newNodePtr = dynamic_cast<statm::Continue*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Continue"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Continue& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Default& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkDefault, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Default* newNodePtr = dynamic_cast<statm::Default*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Default"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Default& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Do& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkDo, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Do* newNodePtr = dynamic_cast<statm::Do*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Do"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Do& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Empty& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkEmpty, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Empty* newNodePtr = dynamic_cast<statm::Empty*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Empty"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Empty& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::EnhancedFor& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkEnhancedFor, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::EnhancedFor* newNodePtr = dynamic_cast<statm::EnhancedFor*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::EnhancedFor"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::EnhancedFor& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::ExpressionStatement& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkExpressionStatement, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::ExpressionStatement* newNodePtr = dynamic_cast<statm::ExpressionStatement*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::ExpressionStatement"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::ExpressionStatement& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Handler& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkHandler, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Handler* newNodePtr = dynamic_cast<statm::Handler*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Handler"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Handler& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::If& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkIf, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::If* newNodePtr = dynamic_cast<statm::If*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::If"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::If& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::LabeledStatement& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkLabeledStatement, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::LabeledStatement* newNodePtr = dynamic_cast<statm::LabeledStatement*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::LabeledStatement"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::LabeledStatement& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Return& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkReturn, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Return* newNodePtr = dynamic_cast<statm::Return*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Return"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Return& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Switch& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkSwitch, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Switch* newNodePtr = dynamic_cast<statm::Switch*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Switch"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Switch& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Synchronized& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkSynchronized, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Synchronized* newNodePtr = dynamic_cast<statm::Synchronized*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Synchronized"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Synchronized& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Throw& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkThrow, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Throw* newNodePtr = dynamic_cast<statm::Throw*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Throw"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Throw& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::Try& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkTry, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::Try* newNodePtr = dynamic_cast<statm::Try*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::Try"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::Try& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const statm::While& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkWhile, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  statm::While* newNodePtr = dynamic_cast<statm::While*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "statm::While"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const statm::While& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::AnnotationType& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkAnnotationType, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::AnnotationType* newNodePtr = dynamic_cast<struc::AnnotationType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::AnnotationType"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::AnnotationType& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::AnnotationTypeElement& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkAnnotationTypeElement, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::AnnotationTypeElement* newNodePtr = dynamic_cast<struc::AnnotationTypeElement*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::AnnotationTypeElement"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::AnnotationTypeElement& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::AnonymousClass& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkAnonymousClass, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::AnonymousClass* newNodePtr = dynamic_cast<struc::AnonymousClass*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::AnonymousClass"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::AnonymousClass& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::Class& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkClass, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::ClassDeclaration* newNodePtr;
  if (node.getNodeKind() == ndkClassGeneric && baseNewNode->getNodeKind() == ndkClass)
    newNodePtr = dynamic_cast<struc::ClassDeclaration*>(fact.replaceNode(*baseNewNode));
  else
    newNodePtr = dynamic_cast<struc::ClassDeclaration*>(baseNewNode);

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::Class& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::ClassGeneric& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkClassGeneric, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::ClassDeclaration* newNodePtr;
  if (node.getNodeKind() == ndkClassGeneric && baseNewNode->getNodeKind() == ndkClass)
    newNodePtr = dynamic_cast<struc::ClassDeclaration*>(fact.replaceNode(*baseNewNode));
  else
    newNodePtr = dynamic_cast<struc::ClassDeclaration*>(baseNewNode);

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::ClassGeneric& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::CompilationUnit& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkCompilationUnit, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::CompilationUnit* newNodePtr = dynamic_cast<struc::CompilationUnit*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::CompilationUnit"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::CompilationUnit& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::Enum& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkEnum, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::Enum* newNodePtr = dynamic_cast<struc::Enum*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::Enum"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::Enum& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::EnumConstant& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkEnumConstant, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::EnumConstant* newNodePtr = dynamic_cast<struc::EnumConstant*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::EnumConstant"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::EnumConstant& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::Import& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkImport, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::Import* newNodePtr = dynamic_cast<struc::Import*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::Import"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::Import& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::InstanceInitializerBlock& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkInstanceInitializerBlock, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::InstanceInitializerBlock* newNodePtr = dynamic_cast<struc::InstanceInitializerBlock*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::InstanceInitializerBlock"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::InstanceInitializerBlock& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::Interface& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkInterface, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::InterfaceDeclaration* newNodePtr;
  if (node.getNodeKind() == ndkInterfaceGeneric && baseNewNode->getNodeKind() == ndkInterface)
    newNodePtr = dynamic_cast<struc::InterfaceDeclaration*>(fact.replaceNode(*baseNewNode));
  else
    newNodePtr = dynamic_cast<struc::InterfaceDeclaration*>(baseNewNode);

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::Interface& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::InterfaceGeneric& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkInterfaceGeneric, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::InterfaceDeclaration* newNodePtr;
  if (node.getNodeKind() == ndkInterfaceGeneric && baseNewNode->getNodeKind() == ndkInterface)
    newNodePtr = dynamic_cast<struc::InterfaceDeclaration*>(fact.replaceNode(*baseNewNode));
  else
    newNodePtr = dynamic_cast<struc::InterfaceDeclaration*>(baseNewNode);

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::InterfaceGeneric& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::Method& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkMethod, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::NormalMethod* newNodePtr;
  if (node.getNodeKind() == ndkMethodGeneric && baseNewNode->getNodeKind() == ndkMethod)
    newNodePtr = dynamic_cast<struc::NormalMethod*>(fact.replaceNode(*baseNewNode));
  else
    newNodePtr = dynamic_cast<struc::NormalMethod*>(baseNewNode);

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::Method& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::MethodGeneric& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkMethodGeneric, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::NormalMethod* newNodePtr;
  if (node.getNodeKind() == ndkMethodGeneric && baseNewNode->getNodeKind() == ndkMethod)
    newNodePtr = dynamic_cast<struc::NormalMethod*>(fact.replaceNode(*baseNewNode));
  else
    newNodePtr = dynamic_cast<struc::NormalMethod*>(baseNewNode);

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::MethodGeneric& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::Package& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkPackage, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::Package* newNodePtr = dynamic_cast<struc::Package*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::Package"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::Package& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::PackageDeclaration& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  n = fact.createNode(ndkPackageDeclaration, fact.size()).getId();
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::PackageDeclaration* newNodePtr = dynamic_cast<struc::PackageDeclaration*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::PackageDeclaration"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::PackageDeclaration& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::Parameter& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkParameter, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::Parameter* newNodePtr = dynamic_cast<struc::Parameter*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::Parameter"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::Parameter& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::StaticInitializerBlock& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkStaticInitializerBlock, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::StaticInitializerBlock* newNodePtr = dynamic_cast<struc::StaticInitializerBlock*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::StaticInitializerBlock"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::StaticInitializerBlock& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::TypeParameter& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkTypeParameter, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::TypeParameter* newNodePtr = dynamic_cast<struc::TypeParameter*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::TypeParameter"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::TypeParameter& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const struc::Variable& node, bool callVirtualBase) {
  if (skip) return;

  NodeId n;
  bool update = true;
  n = getNewNode(node, update);
  if (!n) {
    n = fact.createNode(ndkVariable, fact.size()).getId();
    if (!create)
      create = node.getId();
  }
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  struc::Variable* newNodePtr = dynamic_cast<struc::Variable*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "struc::Variable"));
  }

  if (update) {
    setAttributes(*newNodePtr, node, true);
    storeUniqueString(node);
  }

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const struc::Variable& node, bool callVirtualBase) {
  if (create == node.getId())
    create = 0;
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::ArrayType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.ArrayTypes.find(uname);
  if (it != strMap.ArrayTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkArrayType, fact.size()).getId();
  strMap.ArrayTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::ArrayType* newNodePtr = dynamic_cast<type::ArrayType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::ArrayType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::ArrayType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::BooleanType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.BooleanTypes.find(uname);
  if (it != strMap.BooleanTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkBooleanType, fact.size()).getId();
  strMap.BooleanTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::BooleanType* newNodePtr = dynamic_cast<type::BooleanType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::BooleanType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::BooleanType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::ByteType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.ByteTypes.find(uname);
  if (it != strMap.ByteTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkByteType, fact.size()).getId();
  strMap.ByteTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::ByteType* newNodePtr = dynamic_cast<type::ByteType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::ByteType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::ByteType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::CharType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.CharTypes.find(uname);
  if (it != strMap.CharTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkCharType, fact.size()).getId();
  strMap.CharTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::CharType* newNodePtr = dynamic_cast<type::CharType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::CharType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::CharType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::ClassType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.ClassTypes.find(uname);
  if (it != strMap.ClassTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkClassType, fact.size()).getId();
  strMap.ClassTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::ClassType* newNodePtr = dynamic_cast<type::ClassType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::ClassType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::ClassType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::DoubleType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.DoubleTypes.find(uname);
  if (it != strMap.DoubleTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkDoubleType, fact.size()).getId();
  strMap.DoubleTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::DoubleType* newNodePtr = dynamic_cast<type::DoubleType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::DoubleType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::DoubleType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::ErrorType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.ErrorTypes.find(uname);
  if (it != strMap.ErrorTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkErrorType, fact.size()).getId();
  strMap.ErrorTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::ErrorType* newNodePtr = dynamic_cast<type::ErrorType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::ErrorType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::ErrorType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::FloatType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.FloatTypes.find(uname);
  if (it != strMap.FloatTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkFloatType, fact.size()).getId();
  strMap.FloatTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::FloatType* newNodePtr = dynamic_cast<type::FloatType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::FloatType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::FloatType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::IntType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.IntTypes.find(uname);
  if (it != strMap.IntTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkIntType, fact.size()).getId();
  strMap.IntTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::IntType* newNodePtr = dynamic_cast<type::IntType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::IntType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::IntType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::LongType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.LongTypes.find(uname);
  if (it != strMap.LongTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkLongType, fact.size()).getId();
  strMap.LongTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::LongType* newNodePtr = dynamic_cast<type::LongType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::LongType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::LongType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::LowerBoundedWildcardType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.LowerBoundedWildcardTypes.find(uname);
  if (it != strMap.LowerBoundedWildcardTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkLowerBoundedWildcardType, fact.size()).getId();
  strMap.LowerBoundedWildcardTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::LowerBoundedWildcardType* newNodePtr = dynamic_cast<type::LowerBoundedWildcardType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::LowerBoundedWildcardType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::LowerBoundedWildcardType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::MethodType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.MethodTypes.find(uname);
  if (it != strMap.MethodTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkMethodType, fact.size()).getId();
  strMap.MethodTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::MethodType* newNodePtr = dynamic_cast<type::MethodType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::MethodType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::MethodType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::NoType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.NoTypes.find(uname);
  if (it != strMap.NoTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkNoType, fact.size()).getId();
  strMap.NoTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::NoType* newNodePtr = dynamic_cast<type::NoType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::NoType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::NoType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::NullType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.NullTypes.find(uname);
  if (it != strMap.NullTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkNullType, fact.size()).getId();
  strMap.NullTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::NullType* newNodePtr = dynamic_cast<type::NullType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::NullType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::NullType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::PackageType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.PackageTypes.find(uname);
  if (it != strMap.PackageTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkPackageType, fact.size()).getId();
  strMap.PackageTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::PackageType* newNodePtr = dynamic_cast<type::PackageType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::PackageType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::PackageType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::ParameterizedType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.ParameterizedTypes.find(uname);
  if (it != strMap.ParameterizedTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkParameterizedType, fact.size()).getId();
  strMap.ParameterizedTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::ParameterizedType* newNodePtr = dynamic_cast<type::ParameterizedType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::ParameterizedType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::ParameterizedType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::ShortType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.ShortTypes.find(uname);
  if (it != strMap.ShortTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkShortType, fact.size()).getId();
  strMap.ShortTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::ShortType* newNodePtr = dynamic_cast<type::ShortType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::ShortType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::ShortType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::TypeVariable& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.TypeVariables.find(uname);
  if (it != strMap.TypeVariables.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkTypeVariable, fact.size()).getId();
  strMap.TypeVariables[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::TypeVariable* newNodePtr = dynamic_cast<type::TypeVariable*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::TypeVariable"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::TypeVariable& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::UnboundedWildcardType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.UnboundedWildcardTypes.find(uname);
  if (it != strMap.UnboundedWildcardTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkUnboundedWildcardType, fact.size()).getId();
  strMap.UnboundedWildcardTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::UnboundedWildcardType* newNodePtr = dynamic_cast<type::UnboundedWildcardType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::UnboundedWildcardType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::UnboundedWildcardType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::UnionType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.UnionTypes.find(uname);
  if (it != strMap.UnionTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkUnionType, fact.size()).getId();
  strMap.UnionTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::UnionType* newNodePtr = dynamic_cast<type::UnionType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::UnionType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::UnionType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::UpperBoundedWildcardType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.UpperBoundedWildcardTypes.find(uname);
  if (it != strMap.UpperBoundedWildcardTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkUpperBoundedWildcardType, fact.size()).getId();
  strMap.UpperBoundedWildcardTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::UpperBoundedWildcardType* newNodePtr = dynamic_cast<type::UpperBoundedWildcardType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::UpperBoundedWildcardType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::UpperBoundedWildcardType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visit(const type::VoidType& node, bool callVirtualBase) {
  if (skip) return;

  string uname = getUniqueString(node);
  StrNodeIdMap::iterator it = strMap.VoidTypes.find(uname);
  if (it != strMap.VoidTypes.end()) {
    remapNode(node.getId(), it->second);
    skip = node.getId();
    return;
  }

  NodeId n;
  n = fact.createNode(ndkVoidType, fact.size()).getId();
  strMap.VoidTypes[uname] = n;
  remapNode(node.getId(), n);

  base::Base* baseNewNode = fact.getPointer(n);
  type::VoidType* newNodePtr = dynamic_cast<type::VoidType*>(baseNewNode);
  if (!newNodePtr) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CANNOT_CAST_NODE_TO(baseNewNode->getId(), baseNewNode->getNodeKind(), "type::VoidType"));
  }

  setAttributes(*newNodePtr, node, true);

  vector<NodeId> v;
  v.push_back(n);
  collectEdges(*newNodePtr, node, v, true);
  if (v.size() > 1) {
    toRemap.push_back(v);
  }
}

void LinkerBase::visitEnd(const type::VoidType& node, bool callVirtualBase) {
  if (skip == node.getId()) { skip = 0; return; }
  if (skip) return;
}

void LinkerBase::visitEndAnnotation_HasAnnotationName(const expr::Annotation& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::Annotation* beginNodePtr = dynamic_cast<expr::Annotation*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkAnnotation", "LinkerBase::visitEndAnnotation_HasAnnotationName");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndAnnotation_HasAnnotationName");
    return;
  }
  beginNodePtr->setAnnotationName(endNodePtr);
}

void LinkerBase::visitEndArrayTypeExpression_HasComponentType(const expr::ArrayTypeExpression& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::ArrayTypeExpression* beginNodePtr = dynamic_cast<expr::ArrayTypeExpression*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkArrayTypeExpression", "LinkerBase::visitEndArrayTypeExpression_HasComponentType");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndArrayTypeExpression_HasComponentType");
    return;
  }
  beginNodePtr->setComponentType(endNodePtr);
}

void LinkerBase::visitEndBinary_HasLeftOperand(const expr::Binary& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::Binary* beginNodePtr = dynamic_cast<expr::Binary*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBinary", "LinkerBase::visitEndBinary_HasLeftOperand");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndBinary_HasLeftOperand");
    return;
  }
  beginNodePtr->setLeftOperand(endNodePtr);
}

void LinkerBase::visitEndBinary_HasRightOperand(const expr::Binary& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::Binary* beginNodePtr = dynamic_cast<expr::Binary*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBinary", "LinkerBase::visitEndBinary_HasRightOperand");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndBinary_HasRightOperand");
    return;
  }
  beginNodePtr->setRightOperand(endNodePtr);
}

void LinkerBase::visitEndClassLiteral_HasComponentType(const expr::ClassLiteral& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::ClassLiteral* beginNodePtr = dynamic_cast<expr::ClassLiteral*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkClassLiteral", "LinkerBase::visitEndClassLiteral_HasComponentType");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndClassLiteral_HasComponentType");
    return;
  }
  beginNodePtr->setComponentType(endNodePtr);
}

void LinkerBase::visitEndConditional_HasCondition(const expr::Conditional& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::Conditional* beginNodePtr = dynamic_cast<expr::Conditional*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkConditional", "LinkerBase::visitEndConditional_HasCondition");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndConditional_HasCondition");
    return;
  }
  beginNodePtr->setCondition(endNodePtr);
}

void LinkerBase::visitEndConditional_HasTrueExpression(const expr::Conditional& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::Conditional* beginNodePtr = dynamic_cast<expr::Conditional*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkConditional", "LinkerBase::visitEndConditional_HasTrueExpression");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndConditional_HasTrueExpression");
    return;
  }
  beginNodePtr->setTrueExpression(endNodePtr);
}

void LinkerBase::visitEndConditional_HasFalseExpression(const expr::Conditional& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::Conditional* beginNodePtr = dynamic_cast<expr::Conditional*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkConditional", "LinkerBase::visitEndConditional_HasFalseExpression");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndConditional_HasFalseExpression");
    return;
  }
  beginNodePtr->setFalseExpression(endNodePtr);
}

void LinkerBase::visitEndErroneous_HasErrors(const expr::Erroneous& begin, const base::Positioned& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::Erroneous* beginNodePtr = dynamic_cast<expr::Erroneous*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkErroneous", "LinkerBase::visitEndErroneous_HasErrors");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  base::Positioned* endNodePtr = dynamic_cast<base::Positioned*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkPositioned", "LinkerBase::visitEndErroneous_HasErrors");
    return;
  }
  beginNodePtr->addErrors(endNodePtr);
}

void LinkerBase::visitEndErroneousTypeExpression_HasErrors(const expr::ErroneousTypeExpression& begin, const base::Positioned& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::ErroneousTypeExpression* beginNodePtr = dynamic_cast<expr::ErroneousTypeExpression*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkErroneousTypeExpression", "LinkerBase::visitEndErroneousTypeExpression_HasErrors");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  base::Positioned* endNodePtr = dynamic_cast<base::Positioned*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkPositioned", "LinkerBase::visitEndErroneousTypeExpression_HasErrors");
    return;
  }
  beginNodePtr->addErrors(endNodePtr);
}

void LinkerBase::visitEndInstanceOf_HasTypeOperand(const expr::InstanceOf& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::InstanceOf* beginNodePtr = dynamic_cast<expr::InstanceOf*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkInstanceOf", "LinkerBase::visitEndInstanceOf_HasTypeOperand");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndInstanceOf_HasTypeOperand");
    return;
  }
  beginNodePtr->setTypeOperand(endNodePtr);
}

void LinkerBase::visitEndMethodInvocation_HasTypeArguments(const expr::MethodInvocation& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::MethodInvocation* beginNodePtr = dynamic_cast<expr::MethodInvocation*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkMethodInvocation", "LinkerBase::visitEndMethodInvocation_HasTypeArguments");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndMethodInvocation_HasTypeArguments");
    return;
  }
  beginNodePtr->addTypeArguments(endNodePtr);
}

void LinkerBase::visitEndMethodInvocation_HasArguments(const expr::MethodInvocation& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::MethodInvocation* beginNodePtr = dynamic_cast<expr::MethodInvocation*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkMethodInvocation", "LinkerBase::visitEndMethodInvocation_HasArguments");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndMethodInvocation_HasArguments");
    return;
  }
  beginNodePtr->addArguments(endNodePtr);
}

void LinkerBase::visitEndNewArray_HasComponentType(const expr::NewArray& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NewArray* beginNodePtr = dynamic_cast<expr::NewArray*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewArray", "LinkerBase::visitEndNewArray_HasComponentType");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndNewArray_HasComponentType");
    return;
  }
  beginNodePtr->setComponentType(endNodePtr);
}

void LinkerBase::visitEndNewArray_HasDimensions(const expr::NewArray& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NewArray* beginNodePtr = dynamic_cast<expr::NewArray*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewArray", "LinkerBase::visitEndNewArray_HasDimensions");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndNewArray_HasDimensions");
    return;
  }
  beginNodePtr->addDimensions(endNodePtr);
}

void LinkerBase::visitEndNewArray_HasInitializers(const expr::NewArray& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NewArray* beginNodePtr = dynamic_cast<expr::NewArray*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewArray", "LinkerBase::visitEndNewArray_HasInitializers");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndNewArray_HasInitializers");
    return;
  }
  beginNodePtr->addInitializers(endNodePtr);
}

void LinkerBase::visitEndNewClass_HasEnclosingExpression(const expr::NewClass& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NewClass* beginNodePtr = dynamic_cast<expr::NewClass*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewClass", "LinkerBase::visitEndNewClass_HasEnclosingExpression");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndNewClass_HasEnclosingExpression");
    return;
  }
  beginNodePtr->setEnclosingExpression(endNodePtr);
}

void LinkerBase::visitEndNewClass_HasTypeArguments(const expr::NewClass& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NewClass* beginNodePtr = dynamic_cast<expr::NewClass*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewClass", "LinkerBase::visitEndNewClass_HasTypeArguments");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndNewClass_HasTypeArguments");
    return;
  }
  beginNodePtr->addTypeArguments(endNodePtr);
}

void LinkerBase::visitEndNewClass_HasTypeName(const expr::NewClass& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NewClass* beginNodePtr = dynamic_cast<expr::NewClass*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewClass", "LinkerBase::visitEndNewClass_HasTypeName");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndNewClass_HasTypeName");
    return;
  }
  beginNodePtr->setTypeName(endNodePtr);
}

void LinkerBase::visitEndNewClass_HasArguments(const expr::NewClass& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NewClass* beginNodePtr = dynamic_cast<expr::NewClass*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewClass", "LinkerBase::visitEndNewClass_HasArguments");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndNewClass_HasArguments");
    return;
  }
  beginNodePtr->addArguments(endNodePtr);
}

void LinkerBase::visitEndNewClass_HasAnonymousClass(const expr::NewClass& begin, const struc::AnonymousClass& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NewClass* beginNodePtr = dynamic_cast<expr::NewClass*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewClass", "LinkerBase::visitEndNewClass_HasAnonymousClass");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::AnonymousClass* endNodePtr = dynamic_cast<struc::AnonymousClass*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkAnonymousClass", "LinkerBase::visitEndNewClass_HasAnonymousClass");
    return;
  }
  beginNodePtr->setAnonymousClass(endNodePtr);
}

void LinkerBase::visitEndNormalAnnotation_HasArguments(const expr::NormalAnnotation& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::NormalAnnotation* beginNodePtr = dynamic_cast<expr::NormalAnnotation*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNormalAnnotation", "LinkerBase::visitEndNormalAnnotation_HasArguments");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndNormalAnnotation_HasArguments");
    return;
  }
  beginNodePtr->addArguments(endNodePtr);
}

void LinkerBase::visitEndQualifiedTypeExpression_HasQualifierType(const expr::QualifiedTypeExpression& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::QualifiedTypeExpression* beginNodePtr = dynamic_cast<expr::QualifiedTypeExpression*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkQualifiedTypeExpression", "LinkerBase::visitEndQualifiedTypeExpression_HasQualifierType");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndQualifiedTypeExpression_HasQualifierType");
    return;
  }
  beginNodePtr->setQualifierType(endNodePtr);
}

void LinkerBase::visitEndQualifiedTypeExpression_HasSimpleType(const expr::QualifiedTypeExpression& begin, const expr::SimpleTypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::QualifiedTypeExpression* beginNodePtr = dynamic_cast<expr::QualifiedTypeExpression*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkQualifiedTypeExpression", "LinkerBase::visitEndQualifiedTypeExpression_HasSimpleType");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::SimpleTypeExpression* endNodePtr = dynamic_cast<expr::SimpleTypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkSimpleTypeExpression", "LinkerBase::visitEndQualifiedTypeExpression_HasSimpleType");
    return;
  }
  beginNodePtr->setSimpleType(endNodePtr);
}

void LinkerBase::visitEndSingleElementAnnotation_HasArgument(const expr::SingleElementAnnotation& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::SingleElementAnnotation* beginNodePtr = dynamic_cast<expr::SingleElementAnnotation*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkSingleElementAnnotation", "LinkerBase::visitEndSingleElementAnnotation_HasArgument");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndSingleElementAnnotation_HasArgument");
    return;
  }
  beginNodePtr->setArgument(endNodePtr);
}

void LinkerBase::visitEndTypeApplyExpression_HasRawType(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::TypeApplyExpression* beginNodePtr = dynamic_cast<expr::TypeApplyExpression*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeApplyExpression", "LinkerBase::visitEndTypeApplyExpression_HasRawType");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndTypeApplyExpression_HasRawType");
    return;
  }
  beginNodePtr->setRawType(endNodePtr);
}

void LinkerBase::visitEndTypeApplyExpression_HasTypeArguments(const expr::TypeApplyExpression& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::TypeApplyExpression* beginNodePtr = dynamic_cast<expr::TypeApplyExpression*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeApplyExpression", "LinkerBase::visitEndTypeApplyExpression_HasTypeArguments");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndTypeApplyExpression_HasTypeArguments");
    return;
  }
  beginNodePtr->addTypeArguments(endNodePtr);
}

void LinkerBase::visitEndTypeCast_HasTypeOperand(const expr::TypeCast& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::TypeCast* beginNodePtr = dynamic_cast<expr::TypeCast*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeCast", "LinkerBase::visitEndTypeCast_HasTypeOperand");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndTypeCast_HasTypeOperand");
    return;
  }
  beginNodePtr->setTypeOperand(endNodePtr);
}

void LinkerBase::visitEndTypeUnionExpression_HasAlternatives(const expr::TypeUnionExpression& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::TypeUnionExpression* beginNodePtr = dynamic_cast<expr::TypeUnionExpression*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeUnionExpression", "LinkerBase::visitEndTypeUnionExpression_HasAlternatives");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndTypeUnionExpression_HasAlternatives");
    return;
  }
  beginNodePtr->addAlternatives(endNodePtr);
}

void LinkerBase::visitEndUnary_HasOperand(const expr::Unary& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::Unary* beginNodePtr = dynamic_cast<expr::Unary*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkUnary", "LinkerBase::visitEndUnary_HasOperand");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndUnary_HasOperand");
    return;
  }
  beginNodePtr->setOperand(endNodePtr);
}

void LinkerBase::visitEndWildcardExpression_HasBound(const expr::WildcardExpression& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  expr::WildcardExpression* beginNodePtr = dynamic_cast<expr::WildcardExpression*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkWildcardExpression", "LinkerBase::visitEndWildcardExpression_HasBound");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndWildcardExpression_HasBound");
    return;
  }
  beginNodePtr->setBound(endNodePtr);
}

void LinkerBase::visitEndAssert_HasCondition(const statm::Assert& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Assert* beginNodePtr = dynamic_cast<statm::Assert*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkAssert", "LinkerBase::visitEndAssert_HasCondition");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndAssert_HasCondition");
    return;
  }
  beginNodePtr->setCondition(endNodePtr);
}

void LinkerBase::visitEndAssert_HasDetail(const statm::Assert& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Assert* beginNodePtr = dynamic_cast<statm::Assert*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkAssert", "LinkerBase::visitEndAssert_HasDetail");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndAssert_HasDetail");
    return;
  }
  beginNodePtr->setDetail(endNodePtr);
}

void LinkerBase::visitEndBasicFor_HasInitializers(const statm::BasicFor& begin, const statm::Statement& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::BasicFor* beginNodePtr = dynamic_cast<statm::BasicFor*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBasicFor", "LinkerBase::visitEndBasicFor_HasInitializers");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Statement* endNodePtr = dynamic_cast<statm::Statement*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkStatement", "LinkerBase::visitEndBasicFor_HasInitializers");
    return;
  }
  beginNodePtr->addInitializers(endNodePtr);
}

void LinkerBase::visitEndBasicFor_HasCondition(const statm::BasicFor& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::BasicFor* beginNodePtr = dynamic_cast<statm::BasicFor*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBasicFor", "LinkerBase::visitEndBasicFor_HasCondition");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndBasicFor_HasCondition");
    return;
  }
  beginNodePtr->setCondition(endNodePtr);
}

void LinkerBase::visitEndBasicFor_HasUpdates(const statm::BasicFor& begin, const statm::Statement& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::BasicFor* beginNodePtr = dynamic_cast<statm::BasicFor*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBasicFor", "LinkerBase::visitEndBasicFor_HasUpdates");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Statement* endNodePtr = dynamic_cast<statm::Statement*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkStatement", "LinkerBase::visitEndBasicFor_HasUpdates");
    return;
  }
  beginNodePtr->addUpdates(endNodePtr);
}

void LinkerBase::visitEndBlock_HasStatements(const statm::Block& begin, const statm::Statement& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Block* beginNodePtr = dynamic_cast<statm::Block*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBlock", "LinkerBase::visitEndBlock_HasStatements");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Statement* endNodePtr = dynamic_cast<statm::Statement*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkStatement", "LinkerBase::visitEndBlock_HasStatements");
    return;
  }
  beginNodePtr->addStatements(endNodePtr);
}

void LinkerBase::visitEndCase_HasExpression(const statm::Case& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Case* beginNodePtr = dynamic_cast<statm::Case*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkCase", "LinkerBase::visitEndCase_HasExpression");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndCase_HasExpression");
    return;
  }
  beginNodePtr->setExpression(endNodePtr);
}

void LinkerBase::visitEndDo_HasCondition(const statm::Do& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Do* beginNodePtr = dynamic_cast<statm::Do*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkDo", "LinkerBase::visitEndDo_HasCondition");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndDo_HasCondition");
    return;
  }
  beginNodePtr->setCondition(endNodePtr);
}

void LinkerBase::visitEndEnhancedFor_HasParameter(const statm::EnhancedFor& begin, const struc::Parameter& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::EnhancedFor* beginNodePtr = dynamic_cast<statm::EnhancedFor*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkEnhancedFor", "LinkerBase::visitEndEnhancedFor_HasParameter");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::Parameter* endNodePtr = dynamic_cast<struc::Parameter*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkParameter", "LinkerBase::visitEndEnhancedFor_HasParameter");
    return;
  }
  beginNodePtr->setParameter(endNodePtr);
}

void LinkerBase::visitEndEnhancedFor_HasExpression(const statm::EnhancedFor& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::EnhancedFor* beginNodePtr = dynamic_cast<statm::EnhancedFor*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkEnhancedFor", "LinkerBase::visitEndEnhancedFor_HasExpression");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndEnhancedFor_HasExpression");
    return;
  }
  beginNodePtr->setExpression(endNodePtr);
}

void LinkerBase::visitEndExpressionStatement_HasExpression(const statm::ExpressionStatement& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::ExpressionStatement* beginNodePtr = dynamic_cast<statm::ExpressionStatement*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpressionStatement", "LinkerBase::visitEndExpressionStatement_HasExpression");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndExpressionStatement_HasExpression");
    return;
  }
  beginNodePtr->setExpression(endNodePtr);
}

void LinkerBase::visitEndHandler_HasParameter(const statm::Handler& begin, const struc::Parameter& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Handler* beginNodePtr = dynamic_cast<statm::Handler*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkHandler", "LinkerBase::visitEndHandler_HasParameter");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::Parameter* endNodePtr = dynamic_cast<struc::Parameter*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkParameter", "LinkerBase::visitEndHandler_HasParameter");
    return;
  }
  beginNodePtr->setParameter(endNodePtr);
}

void LinkerBase::visitEndHandler_HasBlock(const statm::Handler& begin, const statm::Block& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Handler* beginNodePtr = dynamic_cast<statm::Handler*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkHandler", "LinkerBase::visitEndHandler_HasBlock");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Block* endNodePtr = dynamic_cast<statm::Block*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBlock", "LinkerBase::visitEndHandler_HasBlock");
    return;
  }
  beginNodePtr->setBlock(endNodePtr);
}

void LinkerBase::visitEndIf_HasSubstatement(const statm::If& begin, const statm::Statement& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::If* beginNodePtr = dynamic_cast<statm::If*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkIf", "LinkerBase::visitEndIf_HasSubstatement");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Statement* endNodePtr = dynamic_cast<statm::Statement*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkStatement", "LinkerBase::visitEndIf_HasSubstatement");
    return;
  }
  beginNodePtr->setSubstatement(endNodePtr);
}

void LinkerBase::visitEndIf_HasFalseSubstatement(const statm::If& begin, const statm::Statement& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::If* beginNodePtr = dynamic_cast<statm::If*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkIf", "LinkerBase::visitEndIf_HasFalseSubstatement");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Statement* endNodePtr = dynamic_cast<statm::Statement*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkStatement", "LinkerBase::visitEndIf_HasFalseSubstatement");
    return;
  }
  beginNodePtr->setFalseSubstatement(endNodePtr);
}

void LinkerBase::visitEndIteration_HasSubstatement(const statm::Iteration& begin, const statm::Statement& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Iteration* beginNodePtr = dynamic_cast<statm::Iteration*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkIteration", "LinkerBase::visitEndIteration_HasSubstatement");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Statement* endNodePtr = dynamic_cast<statm::Statement*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkStatement", "LinkerBase::visitEndIteration_HasSubstatement");
    return;
  }
  beginNodePtr->setSubstatement(endNodePtr);
}

void LinkerBase::visitEndLabeledStatement_HasStatement(const statm::LabeledStatement& begin, const statm::Statement& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::LabeledStatement* beginNodePtr = dynamic_cast<statm::LabeledStatement*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkLabeledStatement", "LinkerBase::visitEndLabeledStatement_HasStatement");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Statement* endNodePtr = dynamic_cast<statm::Statement*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkStatement", "LinkerBase::visitEndLabeledStatement_HasStatement");
    return;
  }
  beginNodePtr->setStatement(endNodePtr);
}

void LinkerBase::visitEndReturn_HasExpression(const statm::Return& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Return* beginNodePtr = dynamic_cast<statm::Return*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkReturn", "LinkerBase::visitEndReturn_HasExpression");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndReturn_HasExpression");
    return;
  }
  beginNodePtr->setExpression(endNodePtr);
}

void LinkerBase::visitEndSelection_HasCondition(const statm::Selection& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Selection* beginNodePtr = dynamic_cast<statm::Selection*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkSelection", "LinkerBase::visitEndSelection_HasCondition");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndSelection_HasCondition");
    return;
  }
  beginNodePtr->setCondition(endNodePtr);
}

void LinkerBase::visitEndSwitch_HasCases(const statm::Switch& begin, const statm::SwitchLabel& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Switch* beginNodePtr = dynamic_cast<statm::Switch*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkSwitch", "LinkerBase::visitEndSwitch_HasCases");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::SwitchLabel* endNodePtr = dynamic_cast<statm::SwitchLabel*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkSwitchLabel", "LinkerBase::visitEndSwitch_HasCases");
    return;
  }
  beginNodePtr->addCases(endNodePtr);
}

void LinkerBase::visitEndSwitchLabel_HasStatements(const statm::SwitchLabel& begin, const statm::Statement& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::SwitchLabel* beginNodePtr = dynamic_cast<statm::SwitchLabel*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkSwitchLabel", "LinkerBase::visitEndSwitchLabel_HasStatements");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Statement* endNodePtr = dynamic_cast<statm::Statement*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkStatement", "LinkerBase::visitEndSwitchLabel_HasStatements");
    return;
  }
  beginNodePtr->addStatements(endNodePtr);
}

void LinkerBase::visitEndSynchronized_HasLock(const statm::Synchronized& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Synchronized* beginNodePtr = dynamic_cast<statm::Synchronized*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkSynchronized", "LinkerBase::visitEndSynchronized_HasLock");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndSynchronized_HasLock");
    return;
  }
  beginNodePtr->setLock(endNodePtr);
}

void LinkerBase::visitEndSynchronized_HasBlock(const statm::Synchronized& begin, const statm::Block& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Synchronized* beginNodePtr = dynamic_cast<statm::Synchronized*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkSynchronized", "LinkerBase::visitEndSynchronized_HasBlock");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Block* endNodePtr = dynamic_cast<statm::Block*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBlock", "LinkerBase::visitEndSynchronized_HasBlock");
    return;
  }
  beginNodePtr->setBlock(endNodePtr);
}

void LinkerBase::visitEndThrow_HasExpression(const statm::Throw& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Throw* beginNodePtr = dynamic_cast<statm::Throw*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkThrow", "LinkerBase::visitEndThrow_HasExpression");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndThrow_HasExpression");
    return;
  }
  beginNodePtr->setExpression(endNodePtr);
}

void LinkerBase::visitEndTry_HasResources(const statm::Try& begin, const struc::Variable& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Try* beginNodePtr = dynamic_cast<statm::Try*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTry", "LinkerBase::visitEndTry_HasResources");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::Variable* endNodePtr = dynamic_cast<struc::Variable*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkVariable", "LinkerBase::visitEndTry_HasResources");
    return;
  }
  beginNodePtr->addResources(endNodePtr);
}

void LinkerBase::visitEndTry_HasBlock(const statm::Try& begin, const statm::Block& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Try* beginNodePtr = dynamic_cast<statm::Try*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTry", "LinkerBase::visitEndTry_HasBlock");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Block* endNodePtr = dynamic_cast<statm::Block*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBlock", "LinkerBase::visitEndTry_HasBlock");
    return;
  }
  beginNodePtr->setBlock(endNodePtr);
}

void LinkerBase::visitEndTry_HasHandlers(const statm::Try& begin, const statm::Handler& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Try* beginNodePtr = dynamic_cast<statm::Try*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTry", "LinkerBase::visitEndTry_HasHandlers");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Handler* endNodePtr = dynamic_cast<statm::Handler*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkHandler", "LinkerBase::visitEndTry_HasHandlers");
    return;
  }
  beginNodePtr->addHandlers(endNodePtr);
}

void LinkerBase::visitEndTry_HasFinallyBlock(const statm::Try& begin, const statm::Block& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::Try* beginNodePtr = dynamic_cast<statm::Try*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTry", "LinkerBase::visitEndTry_HasFinallyBlock");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Block* endNodePtr = dynamic_cast<statm::Block*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBlock", "LinkerBase::visitEndTry_HasFinallyBlock");
    return;
  }
  beginNodePtr->setFinallyBlock(endNodePtr);
}

void LinkerBase::visitEndWhile_HasCondition(const statm::While& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  statm::While* beginNodePtr = dynamic_cast<statm::While*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkWhile", "LinkerBase::visitEndWhile_HasCondition");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndWhile_HasCondition");
    return;
  }
  beginNodePtr->setCondition(endNodePtr);
}

void LinkerBase::visitEndAnnotatedElement_HasAnnotations(const struc::AnnotatedElement& begin, const expr::Annotation& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::AnnotatedElement* beginNodePtr = dynamic_cast<struc::AnnotatedElement*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkAnnotatedElement", "LinkerBase::visitEndAnnotatedElement_HasAnnotations");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Annotation* endNodePtr = dynamic_cast<expr::Annotation*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkAnnotation", "LinkerBase::visitEndAnnotatedElement_HasAnnotations");
    return;
  }
  beginNodePtr->addAnnotations(endNodePtr);
}

void LinkerBase::visitEndAnnotationTypeElement_HasDefaultValue(const struc::AnnotationTypeElement& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::AnnotationTypeElement* beginNodePtr = dynamic_cast<struc::AnnotationTypeElement*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkAnnotationTypeElement", "LinkerBase::visitEndAnnotationTypeElement_HasDefaultValue");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndAnnotationTypeElement_HasDefaultValue");
    return;
  }
  beginNodePtr->setDefaultValue(endNodePtr);
}

void LinkerBase::visitEndCompilationUnit_HasPackageDeclaration(const struc::CompilationUnit& begin, const struc::PackageDeclaration& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::CompilationUnit* beginNodePtr = dynamic_cast<struc::CompilationUnit*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkCompilationUnit", "LinkerBase::visitEndCompilationUnit_HasPackageDeclaration");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::PackageDeclaration* endNodePtr = dynamic_cast<struc::PackageDeclaration*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkPackageDeclaration", "LinkerBase::visitEndCompilationUnit_HasPackageDeclaration");
    return;
  }
  beginNodePtr->setPackageDeclaration(endNodePtr);
}

void LinkerBase::visitEndCompilationUnit_HasImports(const struc::CompilationUnit& begin, const struc::Import& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::CompilationUnit* beginNodePtr = dynamic_cast<struc::CompilationUnit*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkCompilationUnit", "LinkerBase::visitEndCompilationUnit_HasImports");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::Import* endNodePtr = dynamic_cast<struc::Import*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkImport", "LinkerBase::visitEndCompilationUnit_HasImports");
    return;
  }
  beginNodePtr->addImports(endNodePtr);
}

void LinkerBase::visitEndCompilationUnit_HasOthers(const struc::CompilationUnit& begin, const base::Positioned& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::CompilationUnit* beginNodePtr = dynamic_cast<struc::CompilationUnit*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkCompilationUnit", "LinkerBase::visitEndCompilationUnit_HasOthers");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  base::Positioned* endNodePtr = dynamic_cast<base::Positioned*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkPositioned", "LinkerBase::visitEndCompilationUnit_HasOthers");
    return;
  }
  beginNodePtr->addOthers(endNodePtr);
}

void LinkerBase::visitEndEnumConstant_HasNewClass(const struc::EnumConstant& begin, const expr::NewClass& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::EnumConstant* beginNodePtr = dynamic_cast<struc::EnumConstant*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkEnumConstant", "LinkerBase::visitEndEnumConstant_HasNewClass");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::NewClass* endNodePtr = dynamic_cast<expr::NewClass*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNewClass", "LinkerBase::visitEndEnumConstant_HasNewClass");
    return;
  }
  beginNodePtr->setNewClass(endNodePtr);
}

void LinkerBase::visitEndGenericDeclaration_HasTypeParameters(const struc::GenericDeclaration& begin, const struc::TypeParameter& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::GenericDeclaration* beginNodePtr = dynamic_cast<struc::GenericDeclaration*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkGenericDeclaration", "LinkerBase::visitEndGenericDeclaration_HasTypeParameters");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::TypeParameter* endNodePtr = dynamic_cast<struc::TypeParameter*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeParameter", "LinkerBase::visitEndGenericDeclaration_HasTypeParameters");
    return;
  }
  if (!endNodePtr->getParent()) {
    beginNodePtr->addTypeParameters(endNodePtr);
  }
}

void LinkerBase::visitEndImport_HasTarget(const struc::Import& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::Import* beginNodePtr = dynamic_cast<struc::Import*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkImport", "LinkerBase::visitEndImport_HasTarget");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndImport_HasTarget");
    return;
  }
  beginNodePtr->setTarget(endNodePtr);
}

void LinkerBase::visitEndInitializerBlock_HasBody(const struc::InitializerBlock& begin, const statm::Block& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::InitializerBlock* beginNodePtr = dynamic_cast<struc::InitializerBlock*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkInitializerBlock", "LinkerBase::visitEndInitializerBlock_HasBody");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Block* endNodePtr = dynamic_cast<statm::Block*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBlock", "LinkerBase::visitEndInitializerBlock_HasBody");
    return;
  }
  beginNodePtr->setBody(endNodePtr);
}

void LinkerBase::visitEndMethodDeclaration_HasReturnType(const struc::MethodDeclaration& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::MethodDeclaration* beginNodePtr = dynamic_cast<struc::MethodDeclaration*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkMethodDeclaration", "LinkerBase::visitEndMethodDeclaration_HasReturnType");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndMethodDeclaration_HasReturnType");
    return;
  }
  beginNodePtr->setReturnType(endNodePtr);
}

void LinkerBase::visitEndNormalMethod_HasParameters(const struc::NormalMethod& begin, const struc::Parameter& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::NormalMethod* beginNodePtr = dynamic_cast<struc::NormalMethod*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNormalMethod", "LinkerBase::visitEndNormalMethod_HasParameters");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::Parameter* endNodePtr = dynamic_cast<struc::Parameter*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkParameter", "LinkerBase::visitEndNormalMethod_HasParameters");
    return;
  }
  if (!endNodePtr->getParent()) {
    beginNodePtr->addParameters(endNodePtr);
  }
}

void LinkerBase::visitEndNormalMethod_HasBody(const struc::NormalMethod& begin, const statm::Block& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::NormalMethod* beginNodePtr = dynamic_cast<struc::NormalMethod*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNormalMethod", "LinkerBase::visitEndNormalMethod_HasBody");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  statm::Block* endNodePtr = dynamic_cast<statm::Block*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkBlock", "LinkerBase::visitEndNormalMethod_HasBody");
    return;
  }
  beginNodePtr->setBody(endNodePtr);
}

void LinkerBase::visitEndNormalMethod_HasThrownExceptions(const struc::NormalMethod& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::NormalMethod* beginNodePtr = dynamic_cast<struc::NormalMethod*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkNormalMethod", "LinkerBase::visitEndNormalMethod_HasThrownExceptions");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndNormalMethod_HasThrownExceptions");
    return;
  }
  beginNodePtr->addThrownExceptions(endNodePtr);
}

void LinkerBase::visitEndPackage_HasCompilationUnits(const struc::Package& begin, const struc::CompilationUnit& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::Package* beginNodePtr = dynamic_cast<struc::Package*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkPackage", "LinkerBase::visitEndPackage_HasCompilationUnits");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::CompilationUnit* endNodePtr = dynamic_cast<struc::CompilationUnit*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkCompilationUnit", "LinkerBase::visitEndPackage_HasCompilationUnits");
    return;
  }
  if (!endNodePtr->getParent()) {
    beginNodePtr->addCompilationUnits(endNodePtr);
  }
}

void LinkerBase::visitEndPackageDeclaration_HasPackageName(const struc::PackageDeclaration& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::PackageDeclaration* beginNodePtr = dynamic_cast<struc::PackageDeclaration*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkPackageDeclaration", "LinkerBase::visitEndPackageDeclaration_HasPackageName");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndPackageDeclaration_HasPackageName");
    return;
  }
  beginNodePtr->setPackageName(endNodePtr);
}

void LinkerBase::visitEndScope_HasMembers(const struc::Scope& begin, const struc::Member& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::Scope* beginNodePtr = dynamic_cast<struc::Scope*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkScope", "LinkerBase::visitEndScope_HasMembers");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  struc::Member* endNodePtr = dynamic_cast<struc::Member*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkMember", "LinkerBase::visitEndScope_HasMembers");
    return;
  }
  if (!endNodePtr->getParent()) {
    beginNodePtr->addMembers(endNodePtr);
  }
}

void LinkerBase::visitEndTypeDeclaration_HasSuperClass(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::TypeDeclaration* beginNodePtr = dynamic_cast<struc::TypeDeclaration*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeDeclaration", "LinkerBase::visitEndTypeDeclaration_HasSuperClass");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndTypeDeclaration_HasSuperClass");
    return;
  }
  beginNodePtr->setSuperClass(endNodePtr);
}

void LinkerBase::visitEndTypeDeclaration_HasSuperInterfaces(const struc::TypeDeclaration& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::TypeDeclaration* beginNodePtr = dynamic_cast<struc::TypeDeclaration*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeDeclaration", "LinkerBase::visitEndTypeDeclaration_HasSuperInterfaces");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndTypeDeclaration_HasSuperInterfaces");
    return;
  }
  beginNodePtr->addSuperInterfaces(endNodePtr);
}

void LinkerBase::visitEndTypeDeclaration_HasOthers(const struc::TypeDeclaration& begin, const base::Positioned& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::TypeDeclaration* beginNodePtr = dynamic_cast<struc::TypeDeclaration*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeDeclaration", "LinkerBase::visitEndTypeDeclaration_HasOthers");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  base::Positioned* endNodePtr = dynamic_cast<base::Positioned*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkPositioned", "LinkerBase::visitEndTypeDeclaration_HasOthers");
    return;
  }
  beginNodePtr->addOthers(endNodePtr);
}

void LinkerBase::visitEndTypeParameter_HasBounds(const struc::TypeParameter& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::TypeParameter* beginNodePtr = dynamic_cast<struc::TypeParameter*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeParameter", "LinkerBase::visitEndTypeParameter_HasBounds");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndTypeParameter_HasBounds");
    return;
  }
  beginNodePtr->addBounds(endNodePtr);
}

void LinkerBase::visitEndVariable_HasInitialValue(const struc::Variable& begin, const expr::Expression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::Variable* beginNodePtr = dynamic_cast<struc::Variable*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkVariable", "LinkerBase::visitEndVariable_HasInitialValue");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::Expression* endNodePtr = dynamic_cast<expr::Expression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkExpression", "LinkerBase::visitEndVariable_HasInitialValue");
    return;
  }
  beginNodePtr->setInitialValue(endNodePtr);
}

void LinkerBase::visitEndVariableDeclaration_HasType(const struc::VariableDeclaration& begin, const expr::TypeExpression& end) {
  if (skip) return;

  base::Base* tmpPtr;
  tmpPtr = fact.getPointer(remap(begin.getId()));
  struc::VariableDeclaration* beginNodePtr = dynamic_cast<struc::VariableDeclaration*>(tmpPtr);
  if (!beginNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "start", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkVariableDeclaration", "LinkerBase::visitEndVariableDeclaration_HasType");
    return;
  }
  tmpPtr = fact.getPointer(remap(end.getId()));
  expr::TypeExpression* endNodePtr = dynamic_cast<expr::TypeExpression*>(tmpPtr);
  if (!endNodePtr) {
    WriteMsg::write(CMSG_WRONG_NODE_AT_LINKING_EDGES, "end", tmpPtr->getId(), Common::toString(tmpPtr->getNodeKind()).c_str(), "ndkTypeExpression", "LinkerBase::visitEndVariableDeclaration_HasType");
    return;
  }
  beginNodePtr->setType(endNodePtr);
}

void LinkerBase::setAttributes(base::Base& to, const base::Base& from, bool callVirtualBase) {
}

void LinkerBase::setAttributes(base::BlockComment& to, const base::BlockComment& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  setAttributes(static_cast<base::NonJavadocComment&>(to), static_cast<const base::NonJavadocComment&>(from), false);
}

void LinkerBase::setAttributes(base::Comment& to, const base::Comment& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  setAttributes(static_cast<base::PositionedWithoutComment&>(to), static_cast<const base::PositionedWithoutComment&>(from), false);

  to.setText(from.getText());
}

void LinkerBase::setAttributes(base::Commentable& to, const base::Commentable& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
}

void LinkerBase::setAttributes(base::JavadocComment& to, const base::JavadocComment& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  setAttributes(static_cast<base::Comment&>(to), static_cast<const base::Comment&>(from), false);
}

void LinkerBase::setAttributes(base::LineComment& to, const base::LineComment& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  setAttributes(static_cast<base::NonJavadocComment&>(to), static_cast<const base::NonJavadocComment&>(from), false);
}

void LinkerBase::setAttributes(base::Named& to, const base::Named& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);

  to.setName(from.getName());

  to.setNamePosition(from.getNamePosition());
}

void LinkerBase::setAttributes(base::NonJavadocComment& to, const base::NonJavadocComment& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  setAttributes(static_cast<base::Comment&>(to), static_cast<const base::Comment&>(from), false);
}

void LinkerBase::setAttributes(base::Positioned& to, const base::Positioned& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<base::PositionedWithoutComment&>(to), static_cast<const base::PositionedWithoutComment&>(from), false);

  to.setIsCompilerGenerated(from.getIsCompilerGenerated());

  to.setIsToolGenerated(from.getIsToolGenerated());
}

void LinkerBase::setAttributes(base::PositionedWithoutComment& to, const base::PositionedWithoutComment& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);

  to.setPosition(from.getPosition());
}

void LinkerBase::setAttributes(expr::Annotation& to, const expr::Annotation& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::ArrayAccess& to, const expr::ArrayAccess& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Binary&>(to), static_cast<const expr::Binary&>(from), false);
}

void LinkerBase::setAttributes(expr::ArrayTypeExpression& to, const expr::ArrayTypeExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);
}

void LinkerBase::setAttributes(expr::Assignment& to, const expr::Assignment& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Binary&>(to), static_cast<const expr::Binary&>(from), false);

  to.setOperator(from.getOperator());
}

void LinkerBase::setAttributes(expr::Binary& to, const expr::Binary& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::BooleanLiteral& to, const expr::BooleanLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Literal&>(to), static_cast<const expr::Literal&>(from), false);

  to.setBooleanValue(from.getBooleanValue());
}

void LinkerBase::setAttributes(expr::CharacterLiteral& to, const expr::CharacterLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Literal&>(to), static_cast<const expr::Literal&>(from), false);

  to.setCharValue(from.getCharValue());

  to.setFormatString(from.getFormatString());
}

void LinkerBase::setAttributes(expr::ClassLiteral& to, const expr::ClassLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Literal&>(to), static_cast<const expr::Literal&>(from), false);
}

void LinkerBase::setAttributes(expr::Conditional& to, const expr::Conditional& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);

  to.setColonPosition(from.getColonPosition());
}

void LinkerBase::setAttributes(expr::DoubleLiteral& to, const expr::DoubleLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::NumberLiteral&>(to), static_cast<const expr::NumberLiteral&>(from), false);

  to.setDoubleValue(from.getDoubleValue());
}

void LinkerBase::setAttributes(expr::Erroneous& to, const expr::Erroneous& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::ErroneousTypeExpression& to, const expr::ErroneousTypeExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);
}

void LinkerBase::setAttributes(expr::Expression& to, const expr::Expression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<base::Positioned&>(to), static_cast<const base::Positioned&>(from), false);
}

void LinkerBase::setAttributes(expr::ExternalTypeExpression& to, const expr::ExternalTypeExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);
}

void LinkerBase::setAttributes(expr::FieldAccess& to, const expr::FieldAccess& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Binary&>(to), static_cast<const expr::Binary&>(from), false);
}

void LinkerBase::setAttributes(expr::FloatLiteral& to, const expr::FloatLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::NumberLiteral&>(to), static_cast<const expr::NumberLiteral&>(from), false);

  to.setFloatValue(from.getFloatValue());
}

void LinkerBase::setAttributes(expr::Identifier& to, const expr::Identifier& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);

  to.setName(from.getName());
}

void LinkerBase::setAttributes(expr::InfixExpression& to, const expr::InfixExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Binary&>(to), static_cast<const expr::Binary&>(from), false);

  to.setOperator(from.getOperator());
}

void LinkerBase::setAttributes(expr::InstanceOf& to, const expr::InstanceOf& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Unary&>(to), static_cast<const expr::Unary&>(from), false);
}

void LinkerBase::setAttributes(expr::IntegerLiteral& to, const expr::IntegerLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::NumberLiteral&>(to), static_cast<const expr::NumberLiteral&>(from), false);

  to.setIntValue(from.getIntValue());
}

void LinkerBase::setAttributes(expr::Literal& to, const expr::Literal& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::LongLiteral& to, const expr::LongLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::NumberLiteral&>(to), static_cast<const expr::NumberLiteral&>(from), false);

  to.setLongValue(from.getLongValue());
}

void LinkerBase::setAttributes(expr::MarkerAnnotation& to, const expr::MarkerAnnotation& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Annotation&>(to), static_cast<const expr::Annotation&>(from), false);
}

void LinkerBase::setAttributes(expr::MethodInvocation& to, const expr::MethodInvocation& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Unary&>(to), static_cast<const expr::Unary&>(from), false);
}

void LinkerBase::setAttributes(expr::NewArray& to, const expr::NewArray& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);

  to.setLeftBracePosition(from.getLeftBracePosition());
}

void LinkerBase::setAttributes(expr::NewClass& to, const expr::NewClass& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::NormalAnnotation& to, const expr::NormalAnnotation& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Annotation&>(to), static_cast<const expr::Annotation&>(from), false);
}

void LinkerBase::setAttributes(expr::NullLiteral& to, const expr::NullLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Literal&>(to), static_cast<const expr::Literal&>(from), false);
}

void LinkerBase::setAttributes(expr::NumberLiteral& to, const expr::NumberLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Literal&>(to), static_cast<const expr::Literal&>(from), false);

  to.setValue(from.getValue());
}

void LinkerBase::setAttributes(expr::ParenthesizedExpression& to, const expr::ParenthesizedExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Unary&>(to), static_cast<const expr::Unary&>(from), false);
}

void LinkerBase::setAttributes(expr::PostfixExpression& to, const expr::PostfixExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Unary&>(to), static_cast<const expr::Unary&>(from), false);

  to.setOperator(from.getOperator());
}

void LinkerBase::setAttributes(expr::PrefixExpression& to, const expr::PrefixExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Unary&>(to), static_cast<const expr::Unary&>(from), false);

  to.setOperator(from.getOperator());
}

void LinkerBase::setAttributes(expr::PrimitiveTypeExpression& to, const expr::PrimitiveTypeExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);

  to.setKind(from.getKind());
}

void LinkerBase::setAttributes(expr::QualifiedTypeExpression& to, const expr::QualifiedTypeExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);
}

void LinkerBase::setAttributes(expr::SimpleTypeExpression& to, const expr::SimpleTypeExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);

  to.setName(from.getName());
}

void LinkerBase::setAttributes(expr::SingleElementAnnotation& to, const expr::SingleElementAnnotation& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Annotation&>(to), static_cast<const expr::Annotation&>(from), false);
}

void LinkerBase::setAttributes(expr::StringLiteral& to, const expr::StringLiteral& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Literal&>(to), static_cast<const expr::Literal&>(from), false);

  to.setValue(from.getValue());

  to.setFormatString(from.getFormatString());
}

void LinkerBase::setAttributes(expr::Super& to, const expr::Super& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::This& to, const expr::This& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::TypeApplyExpression& to, const expr::TypeApplyExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);
}

void LinkerBase::setAttributes(expr::TypeCast& to, const expr::TypeCast& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Unary&>(to), static_cast<const expr::Unary&>(from), false);
}

void LinkerBase::setAttributes(expr::TypeExpression& to, const expr::TypeExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::TypeUnionExpression& to, const expr::TypeUnionExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);
}

void LinkerBase::setAttributes(expr::Unary& to, const expr::Unary& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::Expression&>(to), static_cast<const expr::Expression&>(from), false);
}

void LinkerBase::setAttributes(expr::WildcardExpression& to, const expr::WildcardExpression& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<expr::TypeExpression&>(to), static_cast<const expr::TypeExpression&>(from), false);

  to.setKind(from.getKind());
}

void LinkerBase::setAttributes(statm::Assert& to, const statm::Assert& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);

  to.setColonPosition(from.getColonPosition());
}

void LinkerBase::setAttributes(statm::BasicFor& to, const statm::BasicFor& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::For&>(to), static_cast<const statm::For&>(from), false);

  to.setFirstSemiPosition(from.getFirstSemiPosition());

  to.setSecondSemiPosition(from.getSecondSemiPosition());
}

void LinkerBase::setAttributes(statm::Block& to, const statm::Block& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(statm::Break& to, const statm::Break& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Jump&>(to), static_cast<const statm::Jump&>(from), false);
}

void LinkerBase::setAttributes(statm::Case& to, const statm::Case& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::SwitchLabel&>(to), static_cast<const statm::SwitchLabel&>(from), false);
}

void LinkerBase::setAttributes(statm::Continue& to, const statm::Continue& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Jump&>(to), static_cast<const statm::Jump&>(from), false);
}

void LinkerBase::setAttributes(statm::Default& to, const statm::Default& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::SwitchLabel&>(to), static_cast<const statm::SwitchLabel&>(from), false);
}

void LinkerBase::setAttributes(statm::Do& to, const statm::Do& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Iteration&>(to), static_cast<const statm::Iteration&>(from), false);

  to.setWhilePosition(from.getWhilePosition());
}

void LinkerBase::setAttributes(statm::Empty& to, const statm::Empty& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(statm::EnhancedFor& to, const statm::EnhancedFor& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::For&>(to), static_cast<const statm::For&>(from), false);

  to.setColonPosition(from.getColonPosition());
}

void LinkerBase::setAttributes(statm::ExpressionStatement& to, const statm::ExpressionStatement& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(statm::For& to, const statm::For& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Iteration&>(to), static_cast<const statm::Iteration&>(from), false);

  to.setLeftParenPosition(from.getLeftParenPosition());

  to.setRightParenPosition(from.getRightParenPosition());
}

void LinkerBase::setAttributes(statm::Handler& to, const statm::Handler& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<base::Positioned&>(to), static_cast<const base::Positioned&>(from), false);

  to.setLeftParenPosition(from.getLeftParenPosition());

  to.setRightParenPosition(from.getRightParenPosition());
}

void LinkerBase::setAttributes(statm::If& to, const statm::If& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Selection&>(to), static_cast<const statm::Selection&>(from), false);

  to.setElsePosition(from.getElsePosition());
}

void LinkerBase::setAttributes(statm::Iteration& to, const statm::Iteration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(statm::Jump& to, const statm::Jump& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);

  to.setLabel(from.getLabel());

  to.setLabelPosition(from.getLabelPosition());
}

void LinkerBase::setAttributes(statm::LabeledStatement& to, const statm::LabeledStatement& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);

  to.setLabel(from.getLabel());

  to.setColonPosition(from.getColonPosition());
}

void LinkerBase::setAttributes(statm::Return& to, const statm::Return& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(statm::Selection& to, const statm::Selection& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(statm::Statement& to, const statm::Statement& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<base::Positioned&>(to), static_cast<const base::Positioned&>(from), false);
}

void LinkerBase::setAttributes(statm::Switch& to, const statm::Switch& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Selection&>(to), static_cast<const statm::Selection&>(from), false);

  to.setBlockStartPosition(from.getBlockStartPosition());
}

void LinkerBase::setAttributes(statm::SwitchLabel& to, const statm::SwitchLabel& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<base::Positioned&>(to), static_cast<const base::Positioned&>(from), false);

  to.setColonPosition(from.getColonPosition());
}

void LinkerBase::setAttributes(statm::Synchronized& to, const statm::Synchronized& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(statm::Throw& to, const statm::Throw& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(statm::Try& to, const statm::Try& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);

  to.setResourceLeftParenPosition(from.getResourceLeftParenPosition());

  to.setResourceRightParenPosition(from.getResourceRightParenPosition());

  to.setFinallyPosition(from.getFinallyPosition());
}

void LinkerBase::setAttributes(statm::While& to, const statm::While& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<statm::Iteration&>(to), static_cast<const statm::Iteration&>(from), false);
}

void LinkerBase::setAttributes(struc::AnnotatedElement& to, const struc::AnnotatedElement& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
}

void LinkerBase::setAttributes(struc::AnnotationType& to, const struc::AnnotationType& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::TypeDeclaration&>(to), static_cast<const struc::TypeDeclaration&>(from), false);

  to.setAtSignPosition(from.getAtSignPosition());
}

void LinkerBase::setAttributes(struc::AnnotationTypeElement& to, const struc::AnnotationTypeElement& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::MethodDeclaration&>(to), static_cast<const struc::MethodDeclaration&>(from), false);

  to.setDefaultPosition(from.getDefaultPosition());
}

void LinkerBase::setAttributes(struc::AnonymousClass& to, const struc::AnonymousClass& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::ClassDeclaration&>(to), static_cast<const struc::ClassDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::Class& to, const struc::Class& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::ClassDeclaration&>(to), static_cast<const struc::ClassDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::ClassDeclaration& to, const struc::ClassDeclaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::TypeDeclaration&>(to), static_cast<const struc::TypeDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::ClassGeneric& to, const struc::ClassGeneric& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::ClassDeclaration&>(to), static_cast<const struc::ClassDeclaration&>(from), false);
  setAttributes(static_cast<struc::GenericDeclaration&>(to), static_cast<const struc::GenericDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::CompilationUnit& to, const struc::CompilationUnit& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  setAttributes(static_cast<base::PositionedWithoutComment&>(to), static_cast<const base::PositionedWithoutComment&>(from), false);
  setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);

  to.setFileEncoding(from.getFileEncoding());
}

void LinkerBase::setAttributes(struc::Declaration& to, const struc::Declaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<statm::Statement&>(to), static_cast<const statm::Statement&>(from), false);
}

void LinkerBase::setAttributes(struc::Enum& to, const struc::Enum& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::TypeDeclaration&>(to), static_cast<const struc::TypeDeclaration&>(from), false);

  to.setSemiPosition(from.getSemiPosition());
}

void LinkerBase::setAttributes(struc::EnumConstant& to, const struc::EnumConstant& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::VariableDeclaration&>(to), static_cast<const struc::VariableDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::GenericDeclaration& to, const struc::GenericDeclaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
}

void LinkerBase::setAttributes(struc::Import& to, const struc::Import& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<base::Positioned&>(to), static_cast<const base::Positioned&>(from), false);

  to.setIsStatic(from.getIsStatic());

  to.setStaticPosition(from.getStaticPosition());
}

void LinkerBase::setAttributes(struc::InitializerBlock& to, const struc::InitializerBlock& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::Declaration&>(to), static_cast<const struc::Declaration&>(from), false);
}

void LinkerBase::setAttributes(struc::InstanceInitializerBlock& to, const struc::InstanceInitializerBlock& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::InitializerBlock&>(to), static_cast<const struc::InitializerBlock&>(from), false);
}

void LinkerBase::setAttributes(struc::Interface& to, const struc::Interface& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::InterfaceDeclaration&>(to), static_cast<const struc::InterfaceDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::InterfaceDeclaration& to, const struc::InterfaceDeclaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::TypeDeclaration&>(to), static_cast<const struc::TypeDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::InterfaceGeneric& to, const struc::InterfaceGeneric& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::InterfaceDeclaration&>(to), static_cast<const struc::InterfaceDeclaration&>(from), false);
  setAttributes(static_cast<struc::GenericDeclaration&>(to), static_cast<const struc::GenericDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::Member& to, const struc::Member& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<struc::AnnotatedElement&>(to), static_cast<const struc::AnnotatedElement&>(from), false);
}

void LinkerBase::setAttributes(struc::Method& to, const struc::Method& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::NormalMethod&>(to), static_cast<const struc::NormalMethod&>(from), false);
}

void LinkerBase::setAttributes(struc::MethodDeclaration& to, const struc::MethodDeclaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::NamedDeclaration&>(to), static_cast<const struc::NamedDeclaration&>(from), false);

  to.setIsAbstract(from.getIsAbstract());

  to.setAbstractPosition(from.getAbstractPosition());

  to.setIsStrictfp(from.getIsStrictfp());

  to.setStrictfpPosition(from.getStrictfpPosition());

  to.setParametersStartPosition(from.getParametersStartPosition());

  to.setParametersEndPosition(from.getParametersEndPosition());
}

void LinkerBase::setAttributes(struc::MethodGeneric& to, const struc::MethodGeneric& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::NormalMethod&>(to), static_cast<const struc::NormalMethod&>(from), false);
  setAttributes(static_cast<struc::GenericDeclaration&>(to), static_cast<const struc::GenericDeclaration&>(from), false);
}

void LinkerBase::setAttributes(struc::NamedDeclaration& to, const struc::NamedDeclaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::Declaration&>(to), static_cast<const struc::Declaration&>(from), false);
  setAttributes(static_cast<base::Named&>(to), static_cast<const base::Named&>(from), false);

  to.setAccessibility(from.getAccessibility());

  to.setAccessibilityPosition(from.getAccessibilityPosition());

  to.setIsStatic(from.getIsStatic());

  to.setStaticPosition(from.getStaticPosition());

  to.setIsFinal(from.getIsFinal());

  to.setFinalPosition(from.getFinalPosition());
}

void LinkerBase::setAttributes(struc::NormalMethod& to, const struc::NormalMethod& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::MethodDeclaration&>(to), static_cast<const struc::MethodDeclaration&>(from), false);

  to.setMethodKind(from.getMethodKind());

  to.setIsSynchronized(from.getIsSynchronized());

  to.setSynchronizedPosition(from.getSynchronizedPosition());

  to.setIsNative(from.getIsNative());

  to.setNativePosition(from.getNativePosition());

  to.setThrowsPosition(from.getThrowsPosition());
}

void LinkerBase::setAttributes(struc::Package& to, const struc::Package& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<base::Named&>(to), static_cast<const base::Named&>(from), false);
  setAttributes(static_cast<struc::Scope&>(to), static_cast<const struc::Scope&>(from), false);

  to.setQualifiedName(from.getQualifiedName());
}

void LinkerBase::setAttributes(struc::PackageDeclaration& to, const struc::PackageDeclaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<base::Positioned&>(to), static_cast<const base::Positioned&>(from), false);
}

void LinkerBase::setAttributes(struc::Parameter& to, const struc::Parameter& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::VariableDeclaration&>(to), static_cast<const struc::VariableDeclaration&>(from), false);

  to.setIsVarargs(from.getIsVarargs());

  to.setVarargsPosition(from.getVarargsPosition());
}

void LinkerBase::setAttributes(struc::Scope& to, const struc::Scope& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
}

void LinkerBase::setAttributes(struc::StaticInitializerBlock& to, const struc::StaticInitializerBlock& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::InitializerBlock&>(to), static_cast<const struc::InitializerBlock&>(from), false);

  to.setBlockStartPosition(from.getBlockStartPosition());
}

void LinkerBase::setAttributes(struc::TypeDeclaration& to, const struc::TypeDeclaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::NamedDeclaration&>(to), static_cast<const struc::NamedDeclaration&>(from), false);
  setAttributes(static_cast<struc::Scope&>(to), static_cast<const struc::Scope&>(from), false);

  to.setTypeNamePosition(from.getTypeNamePosition());

  to.setIsAbstract(from.getIsAbstract());

  to.setAbstractPosition(from.getAbstractPosition());

  to.setIsStrictfp(from.getIsStrictfp());

  to.setStrictfpPosition(from.getStrictfpPosition());

  to.setBinaryName(from.getBinaryName());

  to.setExtendsPosition(from.getExtendsPosition());

  to.setImplementsPosition(from.getImplementsPosition());

  to.setBodyStartPosition(from.getBodyStartPosition());
}

void LinkerBase::setAttributes(struc::TypeParameter& to, const struc::TypeParameter& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  setAttributes(static_cast<base::Positioned&>(to), static_cast<const base::Positioned&>(from), false);
  setAttributes(static_cast<base::Named&>(to), static_cast<const base::Named&>(from), false);
}

void LinkerBase::setAttributes(struc::Variable& to, const struc::Variable& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::VariableDeclaration&>(to), static_cast<const struc::VariableDeclaration&>(from), false);

  to.setIsTransient(from.getIsTransient());

  to.setTransientPosition(from.getTransientPosition());

  to.setIsVolatile(from.getIsVolatile());

  to.setVolatilePosition(from.getVolatilePosition());

  to.setEqualSignPosition(from.getEqualSignPosition());
}

void LinkerBase::setAttributes(struc::VariableDeclaration& to, const struc::VariableDeclaration& from, bool callVirtualBase) {
  if (callVirtualBase)
    setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<base::Commentable&>(to), static_cast<const base::Commentable&>(from), false);
  if (callVirtualBase)
    setAttributes(static_cast<struc::Member&>(to), static_cast<const struc::Member&>(from), false);
  setAttributes(static_cast<struc::NamedDeclaration&>(to), static_cast<const struc::NamedDeclaration&>(from), false);
}

void LinkerBase::setAttributes(type::ArrayType& to, const type::ArrayType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);

  to.setSize(from.getSize());
}

void LinkerBase::setAttributes(type::BooleanType& to, const type::BooleanType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::BoundedWildcardType& to, const type::BoundedWildcardType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::WildcardType&>(to), static_cast<const type::WildcardType&>(from), false);
}

void LinkerBase::setAttributes(type::ByteType& to, const type::ByteType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::CharType& to, const type::CharType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::ClassType& to, const type::ClassType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::ScopedType&>(to), static_cast<const type::ScopedType&>(from), false);
}

void LinkerBase::setAttributes(type::DoubleType& to, const type::DoubleType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::ErrorType& to, const type::ErrorType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::FloatType& to, const type::FloatType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::IntType& to, const type::IntType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::LongType& to, const type::LongType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::LowerBoundedWildcardType& to, const type::LowerBoundedWildcardType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::BoundedWildcardType&>(to), static_cast<const type::BoundedWildcardType&>(from), false);
}

void LinkerBase::setAttributes(type::MethodType& to, const type::MethodType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::NoType& to, const type::NoType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::NullType& to, const type::NullType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::PackageType& to, const type::PackageType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::ParameterizedType& to, const type::ParameterizedType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::ScopedType&>(to), static_cast<const type::ScopedType&>(from), false);
}

void LinkerBase::setAttributes(type::PrimitiveType& to, const type::PrimitiveType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::ScopedType& to, const type::ScopedType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::ShortType& to, const type::ShortType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::Type& to, const type::Type& from, bool callVirtualBase) {
  setAttributes(static_cast<base::Base&>(to), static_cast<const base::Base&>(from), false);
}

void LinkerBase::setAttributes(type::TypeVariable& to, const type::TypeVariable& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::UnboundedWildcardType& to, const type::UnboundedWildcardType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::WildcardType&>(to), static_cast<const type::WildcardType&>(from), false);
}

void LinkerBase::setAttributes(type::UnionType& to, const type::UnionType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::setAttributes(type::UpperBoundedWildcardType& to, const type::UpperBoundedWildcardType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::BoundedWildcardType&>(to), static_cast<const type::BoundedWildcardType&>(from), false);
}

void LinkerBase::setAttributes(type::VoidType& to, const type::VoidType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::PrimitiveType&>(to), static_cast<const type::PrimitiveType&>(from), false);
}

void LinkerBase::setAttributes(type::WildcardType& to, const type::WildcardType& from, bool callVirtualBase) {
  setAttributes(static_cast<type::Type&>(to), static_cast<const type::Type&>(from), false);
}

void LinkerBase::collectEdges(base::Base& newNode, const base::Base& node, vector<NodeId>& v, bool callVirtualBase) {
}

void LinkerBase::collectEdges(base::BlockComment& newNode, const base::BlockComment& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  collectEdges(static_cast<base::NonJavadocComment&>(newNode), static_cast<const base::NonJavadocComment&>(node), v, false);
}

void LinkerBase::collectEdges(base::Comment& newNode, const base::Comment& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  collectEdges(static_cast<base::PositionedWithoutComment&>(newNode), static_cast<const base::PositionedWithoutComment&>(node), v, false);
}

void LinkerBase::collectEdges(base::Commentable& newNode, const base::Commentable& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);

  for (ListIterator<base::Comment> it = node.getCommentsListIteratorBegin(); it != node.getCommentsListIteratorEnd(); ++it)
    v.push_back(it->getId());
  v.push_back(0);
}

void LinkerBase::collectEdges(base::JavadocComment& newNode, const base::JavadocComment& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  collectEdges(static_cast<base::Comment&>(newNode), static_cast<const base::Comment&>(node), v, false);
}

void LinkerBase::collectEdges(base::LineComment& newNode, const base::LineComment& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  collectEdges(static_cast<base::NonJavadocComment&>(newNode), static_cast<const base::NonJavadocComment&>(node), v, false);
}

void LinkerBase::collectEdges(base::Named& newNode, const base::Named& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
}

void LinkerBase::collectEdges(base::NonJavadocComment& newNode, const base::NonJavadocComment& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  collectEdges(static_cast<base::Comment&>(newNode), static_cast<const base::Comment&>(node), v, false);
}

void LinkerBase::collectEdges(base::Positioned& newNode, const base::Positioned& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<base::PositionedWithoutComment&>(newNode), static_cast<const base::PositionedWithoutComment&>(node), v, false);
}

void LinkerBase::collectEdges(base::PositionedWithoutComment& newNode, const base::PositionedWithoutComment& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Annotation& newNode, const expr::Annotation& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::ArrayAccess& newNode, const expr::ArrayAccess& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Binary&>(newNode), static_cast<const expr::Binary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::ArrayTypeExpression& newNode, const expr::ArrayTypeExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Assignment& newNode, const expr::Assignment& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Binary&>(newNode), static_cast<const expr::Binary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Binary& newNode, const expr::Binary& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::BooleanLiteral& newNode, const expr::BooleanLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Literal&>(newNode), static_cast<const expr::Literal&>(node), v, false);
}

void LinkerBase::collectEdges(expr::CharacterLiteral& newNode, const expr::CharacterLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Literal&>(newNode), static_cast<const expr::Literal&>(node), v, false);
}

void LinkerBase::collectEdges(expr::ClassLiteral& newNode, const expr::ClassLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Literal&>(newNode), static_cast<const expr::Literal&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Conditional& newNode, const expr::Conditional& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::DoubleLiteral& newNode, const expr::DoubleLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::NumberLiteral&>(newNode), static_cast<const expr::NumberLiteral&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Erroneous& newNode, const expr::Erroneous& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::ErroneousTypeExpression& newNode, const expr::ErroneousTypeExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Expression& newNode, const expr::Expression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<base::Positioned&>(newNode), static_cast<const base::Positioned&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getType();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(expr::ExternalTypeExpression& newNode, const expr::ExternalTypeExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::FieldAccess& newNode, const expr::FieldAccess& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Binary&>(newNode), static_cast<const expr::Binary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::FloatLiteral& newNode, const expr::FloatLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::NumberLiteral&>(newNode), static_cast<const expr::NumberLiteral&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Identifier& newNode, const expr::Identifier& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getRefersTo();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(expr::InfixExpression& newNode, const expr::InfixExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Binary&>(newNode), static_cast<const expr::Binary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::InstanceOf& newNode, const expr::InstanceOf& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Unary&>(newNode), static_cast<const expr::Unary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::IntegerLiteral& newNode, const expr::IntegerLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::NumberLiteral&>(newNode), static_cast<const expr::NumberLiteral&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Literal& newNode, const expr::Literal& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::LongLiteral& newNode, const expr::LongLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::NumberLiteral&>(newNode), static_cast<const expr::NumberLiteral&>(node), v, false);
}

void LinkerBase::collectEdges(expr::MarkerAnnotation& newNode, const expr::MarkerAnnotation& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Annotation&>(newNode), static_cast<const expr::Annotation&>(node), v, false);
}

void LinkerBase::collectEdges(expr::MethodInvocation& newNode, const expr::MethodInvocation& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Unary&>(newNode), static_cast<const expr::Unary&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getInvokes();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(expr::NewArray& newNode, const expr::NewArray& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::NewClass& newNode, const expr::NewClass& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getConstructor();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(expr::NormalAnnotation& newNode, const expr::NormalAnnotation& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Annotation&>(newNode), static_cast<const expr::Annotation&>(node), v, false);
}

void LinkerBase::collectEdges(expr::NullLiteral& newNode, const expr::NullLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Literal&>(newNode), static_cast<const expr::Literal&>(node), v, false);
}

void LinkerBase::collectEdges(expr::NumberLiteral& newNode, const expr::NumberLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Literal&>(newNode), static_cast<const expr::Literal&>(node), v, false);
}

void LinkerBase::collectEdges(expr::ParenthesizedExpression& newNode, const expr::ParenthesizedExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Unary&>(newNode), static_cast<const expr::Unary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::PostfixExpression& newNode, const expr::PostfixExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Unary&>(newNode), static_cast<const expr::Unary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::PrefixExpression& newNode, const expr::PrefixExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Unary&>(newNode), static_cast<const expr::Unary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::PrimitiveTypeExpression& newNode, const expr::PrimitiveTypeExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::QualifiedTypeExpression& newNode, const expr::QualifiedTypeExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::SimpleTypeExpression& newNode, const expr::SimpleTypeExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::SingleElementAnnotation& newNode, const expr::SingleElementAnnotation& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Annotation&>(newNode), static_cast<const expr::Annotation&>(node), v, false);
}

void LinkerBase::collectEdges(expr::StringLiteral& newNode, const expr::StringLiteral& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Literal&>(newNode), static_cast<const expr::Literal&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Super& newNode, const expr::Super& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::This& newNode, const expr::This& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::TypeApplyExpression& newNode, const expr::TypeApplyExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::TypeCast& newNode, const expr::TypeCast& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Unary&>(newNode), static_cast<const expr::Unary&>(node), v, false);
}

void LinkerBase::collectEdges(expr::TypeExpression& newNode, const expr::TypeExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::TypeUnionExpression& newNode, const expr::TypeUnionExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::Unary& newNode, const expr::Unary& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::Expression&>(newNode), static_cast<const expr::Expression&>(node), v, false);
}

void LinkerBase::collectEdges(expr::WildcardExpression& newNode, const expr::WildcardExpression& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<expr::TypeExpression&>(newNode), static_cast<const expr::TypeExpression&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Assert& newNode, const statm::Assert& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::BasicFor& newNode, const statm::BasicFor& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::For&>(newNode), static_cast<const statm::For&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Block& newNode, const statm::Block& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Break& newNode, const statm::Break& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Jump&>(newNode), static_cast<const statm::Jump&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Case& newNode, const statm::Case& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::SwitchLabel&>(newNode), static_cast<const statm::SwitchLabel&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Continue& newNode, const statm::Continue& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Jump&>(newNode), static_cast<const statm::Jump&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Default& newNode, const statm::Default& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::SwitchLabel&>(newNode), static_cast<const statm::SwitchLabel&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Do& newNode, const statm::Do& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Iteration&>(newNode), static_cast<const statm::Iteration&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Empty& newNode, const statm::Empty& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::EnhancedFor& newNode, const statm::EnhancedFor& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::For&>(newNode), static_cast<const statm::For&>(node), v, false);
}

void LinkerBase::collectEdges(statm::ExpressionStatement& newNode, const statm::ExpressionStatement& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::For& newNode, const statm::For& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Iteration&>(newNode), static_cast<const statm::Iteration&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Handler& newNode, const statm::Handler& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<base::Positioned&>(newNode), static_cast<const base::Positioned&>(node), v, false);
}

void LinkerBase::collectEdges(statm::If& newNode, const statm::If& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Selection&>(newNode), static_cast<const statm::Selection&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Iteration& newNode, const statm::Iteration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Jump& newNode, const statm::Jump& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getTarget();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(statm::LabeledStatement& newNode, const statm::LabeledStatement& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Return& newNode, const statm::Return& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Selection& newNode, const statm::Selection& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Statement& newNode, const statm::Statement& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<base::Positioned&>(newNode), static_cast<const base::Positioned&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Switch& newNode, const statm::Switch& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Selection&>(newNode), static_cast<const statm::Selection&>(node), v, false);
}

void LinkerBase::collectEdges(statm::SwitchLabel& newNode, const statm::SwitchLabel& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<base::Positioned&>(newNode), static_cast<const base::Positioned&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Synchronized& newNode, const statm::Synchronized& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Throw& newNode, const statm::Throw& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::Try& newNode, const statm::Try& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(statm::While& newNode, const statm::While& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<statm::Iteration&>(newNode), static_cast<const statm::Iteration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::AnnotatedElement& newNode, const struc::AnnotatedElement& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
}

void LinkerBase::collectEdges(struc::AnnotationType& newNode, const struc::AnnotationType& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::TypeDeclaration&>(newNode), static_cast<const struc::TypeDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::AnnotationTypeElement& newNode, const struc::AnnotationTypeElement& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getDefaultValue() && node.getDefaultValue()) {
    tmpFact.setFilteredThisNodeOnly(node.getDefaultValue()->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::MethodDeclaration&>(newNode), static_cast<const struc::MethodDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::AnonymousClass& newNode, const struc::AnonymousClass& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::ClassDeclaration&>(newNode), static_cast<const struc::ClassDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Class& newNode, const struc::Class& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::ClassDeclaration&>(newNode), static_cast<const struc::ClassDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::ClassDeclaration& newNode, const struc::ClassDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::TypeDeclaration&>(newNode), static_cast<const struc::TypeDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::ClassGeneric& newNode, const struc::ClassGeneric& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::ClassDeclaration&>(newNode), static_cast<const struc::ClassDeclaration&>(node), v, false);
  collectEdges(static_cast<struc::GenericDeclaration&>(newNode), static_cast<const struc::GenericDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::CompilationUnit& newNode, const struc::CompilationUnit& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getPackageDeclaration() && node.getPackageDeclaration()) {
    tmpFact.setFilteredThisNodeOnly(node.getPackageDeclaration()->getId());
  }

  if (!newNode.getImportsIsEmpty()) {
    for (ListIterator<struc::Import> it = node.getImportsListIteratorBegin(); it != node.getImportsListIteratorEnd(); ++it)
      tmpFact.setFilteredThisNodeOnly(it->getId());
  }

  if (!newNode.getOthersIsEmpty()) {
    for (ListIterator<base::Positioned> it = node.getOthersListIteratorBegin(); it != node.getOthersListIteratorEnd(); ++it)
      tmpFact.setFilteredThisNodeOnly(it->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  collectEdges(static_cast<base::PositionedWithoutComment&>(newNode), static_cast<const base::PositionedWithoutComment&>(node), v, false);
  collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);

  for (ListIterator<struc::TypeDeclaration> it = node.getTypeDeclarationsListIteratorBegin(); it != node.getTypeDeclarationsListIteratorEnd(); ++it)
    v.push_back(it->getId());
  v.push_back(0);
}

void LinkerBase::collectEdges(struc::Declaration& newNode, const struc::Declaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<statm::Statement&>(newNode), static_cast<const statm::Statement&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Enum& newNode, const struc::Enum& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::TypeDeclaration&>(newNode), static_cast<const struc::TypeDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::EnumConstant& newNode, const struc::EnumConstant& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getNewClass() && node.getNewClass()) {
    tmpFact.setFilteredThisNodeOnly(node.getNewClass()->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::VariableDeclaration&>(newNode), static_cast<const struc::VariableDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::GenericDeclaration& newNode, const struc::GenericDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Import& newNode, const struc::Import& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<base::Positioned&>(newNode), static_cast<const base::Positioned&>(node), v, false);
}

void LinkerBase::collectEdges(struc::InitializerBlock& newNode, const struc::InitializerBlock& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getBody() && node.getBody()) {
    tmpFact.setFilteredThisNodeOnly(node.getBody()->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::Declaration&>(newNode), static_cast<const struc::Declaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::InstanceInitializerBlock& newNode, const struc::InstanceInitializerBlock& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::InitializerBlock&>(newNode), static_cast<const struc::InitializerBlock&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Interface& newNode, const struc::Interface& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::InterfaceDeclaration&>(newNode), static_cast<const struc::InterfaceDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::InterfaceDeclaration& newNode, const struc::InterfaceDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::TypeDeclaration&>(newNode), static_cast<const struc::TypeDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::InterfaceGeneric& newNode, const struc::InterfaceGeneric& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::InterfaceDeclaration&>(newNode), static_cast<const struc::InterfaceDeclaration&>(node), v, false);
  collectEdges(static_cast<struc::GenericDeclaration&>(newNode), static_cast<const struc::GenericDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Member& newNode, const struc::Member& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<struc::AnnotatedElement&>(newNode), static_cast<const struc::AnnotatedElement&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Method& newNode, const struc::Method& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::NormalMethod&>(newNode), static_cast<const struc::NormalMethod&>(node), v, false);
}

void LinkerBase::collectEdges(struc::MethodDeclaration& newNode, const struc::MethodDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getReturnType() && node.getReturnType()) {
    tmpFact.setFilteredThisNodeOnly(node.getReturnType()->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::NamedDeclaration&>(newNode), static_cast<const struc::NamedDeclaration&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getMethodType();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);

  for (ListIterator<struc::MethodDeclaration> it = node.getOverridesListIteratorBegin(); it != node.getOverridesListIteratorEnd(); ++it)
    v.push_back(it->getId());
  v.push_back(0);
}

void LinkerBase::collectEdges(struc::MethodGeneric& newNode, const struc::MethodGeneric& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::NormalMethod&>(newNode), static_cast<const struc::NormalMethod&>(node), v, false);
  collectEdges(static_cast<struc::GenericDeclaration&>(newNode), static_cast<const struc::GenericDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::NamedDeclaration& newNode, const struc::NamedDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::Declaration&>(newNode), static_cast<const struc::Declaration&>(node), v, false);
  collectEdges(static_cast<base::Named&>(newNode), static_cast<const base::Named&>(node), v, false);
}

void LinkerBase::collectEdges(struc::NormalMethod& newNode, const struc::NormalMethod& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getBody() && node.getBody()) {
    tmpFact.setFilteredThisNodeOnly(node.getBody()->getId());
  }

  if (!newNode.getThrownExceptionsIsEmpty()) {
    for (ListIterator<expr::TypeExpression> it = node.getThrownExceptionsListIteratorBegin(); it != node.getThrownExceptionsListIteratorEnd(); ++it)
      tmpFact.setFilteredThisNodeOnly(it->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::MethodDeclaration&>(newNode), static_cast<const struc::MethodDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Package& newNode, const struc::Package& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<base::Named&>(newNode), static_cast<const base::Named&>(node), v, false);
  collectEdges(static_cast<struc::Scope&>(newNode), static_cast<const struc::Scope&>(node), v, false);
}

void LinkerBase::collectEdges(struc::PackageDeclaration& newNode, const struc::PackageDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<base::Positioned&>(newNode), static_cast<const base::Positioned&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getRefersTo();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(struc::Parameter& newNode, const struc::Parameter& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::VariableDeclaration&>(newNode), static_cast<const struc::VariableDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Scope& newNode, const struc::Scope& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
}

void LinkerBase::collectEdges(struc::StaticInitializerBlock& newNode, const struc::StaticInitializerBlock& node, vector<NodeId>& v, bool callVirtualBase) {
  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::InitializerBlock&>(newNode), static_cast<const struc::InitializerBlock&>(node), v, false);
}

void LinkerBase::collectEdges(struc::TypeDeclaration& newNode, const struc::TypeDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getSuperClass() && node.getSuperClass()) {
    tmpFact.setFilteredThisNodeOnly(node.getSuperClass()->getId());
  }

  if (!newNode.getSuperInterfacesIsEmpty()) {
    for (ListIterator<expr::TypeExpression> it = node.getSuperInterfacesListIteratorBegin(); it != node.getSuperInterfacesListIteratorEnd(); ++it)
      tmpFact.setFilteredThisNodeOnly(it->getId());
  }

  if (!newNode.getOthersIsEmpty()) {
    for (ListIterator<base::Positioned> it = node.getOthersListIteratorBegin(); it != node.getOthersListIteratorEnd(); ++it)
      tmpFact.setFilteredThisNodeOnly(it->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::NamedDeclaration&>(newNode), static_cast<const struc::NamedDeclaration&>(node), v, false);
  collectEdges(static_cast<struc::Scope&>(newNode), static_cast<const struc::Scope&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getIsInCompilationUnit();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(struc::TypeParameter& newNode, const struc::TypeParameter& node, vector<NodeId>& v, bool callVirtualBase) {
  if (!newNode.getBoundsIsEmpty()) {
    for (ListIterator<expr::TypeExpression> it = node.getBoundsListIteratorBegin(); it != node.getBoundsListIteratorEnd(); ++it)
      tmpFact.setFilteredThisNodeOnly(it->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  collectEdges(static_cast<base::Positioned&>(newNode), static_cast<const base::Positioned&>(node), v, false);
  collectEdges(static_cast<base::Named&>(newNode), static_cast<const base::Named&>(node), v, false);
}

void LinkerBase::collectEdges(struc::Variable& newNode, const struc::Variable& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getInitialValue() && node.getInitialValue()) {
    tmpFact.setFilteredThisNodeOnly(node.getInitialValue()->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::VariableDeclaration&>(newNode), static_cast<const struc::VariableDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(struc::VariableDeclaration& newNode, const struc::VariableDeclaration& node, vector<NodeId>& v, bool callVirtualBase) {
  if (newNode.getType() && node.getType()) {
    tmpFact.setFilteredThisNodeOnly(node.getType()->getId());
  }

  if (callVirtualBase)
    collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<base::Commentable&>(newNode), static_cast<const base::Commentable&>(node), v, false);
  if (callVirtualBase)
    collectEdges(static_cast<struc::Member&>(newNode), static_cast<const struc::Member&>(node), v, false);
  collectEdges(static_cast<struc::NamedDeclaration&>(newNode), static_cast<const struc::NamedDeclaration&>(node), v, false);
}

void LinkerBase::collectEdges(type::ArrayType& newNode, const type::ArrayType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getComponentType();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(type::BooleanType& newNode, const type::BooleanType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::BoundedWildcardType& newNode, const type::BoundedWildcardType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::WildcardType&>(newNode), static_cast<const type::WildcardType&>(node), v, false);
}

void LinkerBase::collectEdges(type::ByteType& newNode, const type::ByteType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::CharType& newNode, const type::CharType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::ClassType& newNode, const type::ClassType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::ScopedType&>(newNode), static_cast<const type::ScopedType&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getRefersTo();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(type::DoubleType& newNode, const type::DoubleType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::ErrorType& newNode, const type::ErrorType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);
}

void LinkerBase::collectEdges(type::FloatType& newNode, const type::FloatType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::IntType& newNode, const type::IntType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::LongType& newNode, const type::LongType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::LowerBoundedWildcardType& newNode, const type::LowerBoundedWildcardType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::BoundedWildcardType&>(newNode), static_cast<const type::BoundedWildcardType&>(node), v, false);
}

void LinkerBase::collectEdges(type::MethodType& newNode, const type::MethodType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getReturnType();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);

  for (ListIterator<type::Type> it = node.getParameterTypesListIteratorBegin(); it != node.getParameterTypesListIteratorEnd(); ++it)
    v.push_back(it->getId());
  v.push_back(0);

  for (ListIterator<type::Type> it = node.getThrownTypesListIteratorBegin(); it != node.getThrownTypesListIteratorEnd(); ++it)
    v.push_back(it->getId());
  v.push_back(0);
}

void LinkerBase::collectEdges(type::NoType& newNode, const type::NoType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);
}

void LinkerBase::collectEdges(type::NullType& newNode, const type::NullType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);
}

void LinkerBase::collectEdges(type::PackageType& newNode, const type::PackageType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getRefersTo();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(type::ParameterizedType& newNode, const type::ParameterizedType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::ScopedType&>(newNode), static_cast<const type::ScopedType&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getRawType();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);

  for (ListIterator<type::Type> it = node.getArgumentTypesListIteratorBegin(); it != node.getArgumentTypesListIteratorEnd(); ++it)
    v.push_back(it->getId());
  v.push_back(0);
}

void LinkerBase::collectEdges(type::PrimitiveType& newNode, const type::PrimitiveType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);
}

void LinkerBase::collectEdges(type::ScopedType& newNode, const type::ScopedType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getOwner();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(type::ShortType& newNode, const type::ShortType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::Type& newNode, const type::Type& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<base::Base&>(newNode), static_cast<const base::Base&>(node), v, false);
}

void LinkerBase::collectEdges(type::TypeVariable& newNode, const type::TypeVariable& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getRefersTo();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::collectEdges(type::UnboundedWildcardType& newNode, const type::UnboundedWildcardType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::WildcardType&>(newNode), static_cast<const type::WildcardType&>(node), v, false);
}

void LinkerBase::collectEdges(type::UnionType& newNode, const type::UnionType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);

  for (ListIterator<type::Type> it = node.getAlternativesListIteratorBegin(); it != node.getAlternativesListIteratorEnd(); ++it)
    v.push_back(it->getId());
  v.push_back(0);
}

void LinkerBase::collectEdges(type::UpperBoundedWildcardType& newNode, const type::UpperBoundedWildcardType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::BoundedWildcardType&>(newNode), static_cast<const type::BoundedWildcardType&>(node), v, false);
}

void LinkerBase::collectEdges(type::VoidType& newNode, const type::VoidType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::PrimitiveType&>(newNode), static_cast<const type::PrimitiveType&>(node), v, false);
}

void LinkerBase::collectEdges(type::WildcardType& newNode, const type::WildcardType& node, vector<NodeId>& v, bool callVirtualBase) {
  collectEdges(static_cast<type::Type&>(newNode), static_cast<const type::Type&>(node), v, false);

  base::Base* genNodePtr;
  genNodePtr = node.getBound();
  v.push_back(genNodePtr ? genNodePtr->getId() : 0);
}

void LinkerBase::setEdges(columbus::java::asg::base::Base& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
}

void LinkerBase::setEdges(columbus::java::asg::base::BlockComment& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  setEdges((base::NonJavadocComment&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::base::Comment& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  setEdges((base::PositionedWithoutComment&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::base::Commentable& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);

  NodeId id;
  set<NodeId> edges;
  for (ListIterator<base::Comment> it = node.getCommentsListIteratorBegin(); it != node.getCommentsListIteratorEnd(); ++it) {
    edges.insert(it->getId());
  }
  id = v[++index];
  while (id) {
    if (edges.find(remap(id)) == edges.end())
      node.addComments(remap(id));
    id = v[++index];
  }
}

void LinkerBase::setEdges(columbus::java::asg::base::JavadocComment& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  setEdges((base::Comment&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::base::LineComment& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  setEdges((base::NonJavadocComment&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::base::Named& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::base::NonJavadocComment& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  setEdges((base::Comment&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::base::Positioned& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((base::PositionedWithoutComment&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::base::PositionedWithoutComment& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Annotation& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::ArrayAccess& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Binary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::ArrayTypeExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Assignment& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Binary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Binary& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::BooleanLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Literal&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::CharacterLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Literal&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::ClassLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Literal&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Conditional& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::DoubleLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::NumberLiteral&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Erroneous& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::ErroneousTypeExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Expression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((base::Positioned&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setType(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::expr::ExternalTypeExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::FieldAccess& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Binary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::FloatLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::NumberLiteral&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Identifier& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setRefersTo(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::expr::InfixExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Binary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::InstanceOf& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Unary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::IntegerLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::NumberLiteral&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Literal& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::LongLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::NumberLiteral&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::MarkerAnnotation& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Annotation&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::MethodInvocation& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Unary&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setInvokes(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::expr::NewArray& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::NewClass& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setConstructor(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::expr::NormalAnnotation& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Annotation&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::NullLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Literal&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::NumberLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Literal&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::ParenthesizedExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Unary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::PostfixExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Unary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::PrefixExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Unary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::PrimitiveTypeExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::QualifiedTypeExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::SimpleTypeExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::SingleElementAnnotation& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Annotation&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::StringLiteral& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Literal&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Super& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::This& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::TypeApplyExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::TypeCast& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Unary&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::TypeExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::TypeUnionExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::Unary& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::Expression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::expr::WildcardExpression& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((expr::TypeExpression&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Assert& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::BasicFor& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::For&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Block& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Break& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Jump&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Case& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::SwitchLabel&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Continue& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Jump&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Default& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::SwitchLabel&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Do& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Iteration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Empty& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::EnhancedFor& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::For&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::ExpressionStatement& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::For& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Iteration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Handler& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((base::Positioned&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::If& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Selection&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Iteration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Jump& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setTarget(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::statm::LabeledStatement& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Return& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Selection& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Statement& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((base::Positioned&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Switch& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Selection&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::SwitchLabel& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((base::Positioned&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Synchronized& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Throw& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::Try& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::statm::While& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((statm::Iteration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::AnnotatedElement& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::AnnotationType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::TypeDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::AnnotationTypeElement& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::MethodDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::AnonymousClass& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::ClassDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Class& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::ClassDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::ClassDeclaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::TypeDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::ClassGeneric& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::ClassDeclaration&)node, v, index, false);
  setEdges((struc::GenericDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::CompilationUnit& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  setEdges((base::PositionedWithoutComment&)node, v, index, false);
  setEdges((base::Commentable&)node, v, index, false);

  NodeId id;
  set<NodeId> edges;
  for (ListIterator<struc::TypeDeclaration> it = node.getTypeDeclarationsListIteratorBegin(); it != node.getTypeDeclarationsListIteratorEnd(); ++it) {
    edges.insert(it->getId());
  }
  id = v[++index];
  while (id) {
    if (edges.find(remap(id)) == edges.end())
      node.addTypeDeclarations(remap(id));
    id = v[++index];
  }
}

void LinkerBase::setEdges(columbus::java::asg::struc::Declaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((statm::Statement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Enum& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::TypeDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::EnumConstant& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::VariableDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::GenericDeclaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Import& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((base::Positioned&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::InitializerBlock& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::Declaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::InstanceInitializerBlock& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::InitializerBlock&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Interface& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::InterfaceDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::InterfaceDeclaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::TypeDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::InterfaceGeneric& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::InterfaceDeclaration&)node, v, index, false);
  setEdges((struc::GenericDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Member& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((struc::AnnotatedElement&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Method& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::NormalMethod&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::MethodDeclaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::NamedDeclaration&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setMethodType(remap(id));
  set<NodeId> edges;
  for (ListIterator<struc::MethodDeclaration> it = node.getOverridesListIteratorBegin(); it != node.getOverridesListIteratorEnd(); ++it) {
    edges.insert(it->getId());
  }
  id = v[++index];
  while (id) {
    if (edges.find(remap(id)) == edges.end())
      node.addOverrides(remap(id));
    id = v[++index];
  }
}

void LinkerBase::setEdges(columbus::java::asg::struc::MethodGeneric& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::NormalMethod&)node, v, index, false);
  setEdges((struc::GenericDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::NamedDeclaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::Declaration&)node, v, index, false);
  setEdges((base::Named&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::NormalMethod& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::MethodDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Package& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((base::Named&)node, v, index, false);
  setEdges((struc::Scope&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::PackageDeclaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((base::Positioned&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setRefersTo(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::struc::Parameter& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::VariableDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Scope& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::StaticInitializerBlock& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::InitializerBlock&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::TypeDeclaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::NamedDeclaration&)node, v, index, false);
  setEdges((struc::Scope&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setIsInCompilationUnit(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::struc::TypeParameter& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  setEdges((base::Positioned&)node, v, index, false);
  setEdges((base::Named&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::Variable& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::VariableDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::struc::VariableDeclaration& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  if (callVirtualBase)
    setEdges((base::Base&)node, v, index, false);
  if (callVirtualBase)
    setEdges((base::Commentable&)node, v, index, false);
  if (callVirtualBase)
    setEdges((struc::Member&)node, v, index, false);
  setEdges((struc::NamedDeclaration&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::ArrayType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setComponentType(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::type::BooleanType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::BoundedWildcardType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::WildcardType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::ByteType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::CharType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::ClassType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::ScopedType&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setRefersTo(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::type::DoubleType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::ErrorType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::FloatType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::IntType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::LongType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::LowerBoundedWildcardType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::BoundedWildcardType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::MethodType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setReturnType(remap(id));
  id = v[++index];
  while (id) {
    node.addParameterTypes(remap(id));
    id = v[++index];
  }
  id = v[++index];
  while (id) {
    node.addThrownTypes(remap(id));
    id = v[++index];
  }
}

void LinkerBase::setEdges(columbus::java::asg::type::NoType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::NullType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::PackageType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setRefersTo(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::type::ParameterizedType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::ScopedType&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setRawType(remap(id));
  id = v[++index];
  while (id) {
    node.addArgumentTypes(remap(id));
    id = v[++index];
  }
}

void LinkerBase::setEdges(columbus::java::asg::type::PrimitiveType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::ScopedType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setOwner(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::type::ShortType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::Type& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((base::Base&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::TypeVariable& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setRefersTo(remap(id));
}

void LinkerBase::setEdges(columbus::java::asg::type::UnboundedWildcardType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::WildcardType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::UnionType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);

  NodeId id;
  id = v[++index];
  while (id) {
    node.addAlternatives(remap(id));
    id = v[++index];
  }
}

void LinkerBase::setEdges(columbus::java::asg::type::UpperBoundedWildcardType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::BoundedWildcardType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::VoidType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::PrimitiveType&)node, v, index, false);
}

void LinkerBase::setEdges(columbus::java::asg::type::WildcardType& node, std::vector<NodeId>& v, unsigned int& index, bool callVirtualBase) {
  setEdges((type::Type&)node, v, index, false);

  NodeId id;
  id = v[++index];
  if (id)
    node.setBound(remap(id));
}

void LinkerBase::finishVisit() {
  for (unsigned i = 0; i < toRemap.size(); i++) {
    vector<NodeId>& v = toRemap[i];
    unsigned index = 0;
    base::Base& node = fact.getRef(v[index]);

    switch (node.getNodeKind()) {
      case ndkBlockComment:
        setEdges(dynamic_cast<base::BlockComment&>(node), v, index, true);
        break;

      case ndkJavadocComment:
        setEdges(dynamic_cast<base::JavadocComment&>(node), v, index, true);
        break;

      case ndkLineComment:
        setEdges(dynamic_cast<base::LineComment&>(node), v, index, true);
        break;

      case ndkArrayAccess:
        setEdges(dynamic_cast<expr::ArrayAccess&>(node), v, index, true);
        break;

      case ndkArrayTypeExpression:
        setEdges(dynamic_cast<expr::ArrayTypeExpression&>(node), v, index, true);
        break;

      case ndkAssignment:
        setEdges(dynamic_cast<expr::Assignment&>(node), v, index, true);
        break;

      case ndkBooleanLiteral:
        setEdges(dynamic_cast<expr::BooleanLiteral&>(node), v, index, true);
        break;

      case ndkCharacterLiteral:
        setEdges(dynamic_cast<expr::CharacterLiteral&>(node), v, index, true);
        break;

      case ndkClassLiteral:
        setEdges(dynamic_cast<expr::ClassLiteral&>(node), v, index, true);
        break;

      case ndkConditional:
        setEdges(dynamic_cast<expr::Conditional&>(node), v, index, true);
        break;

      case ndkDoubleLiteral:
        setEdges(dynamic_cast<expr::DoubleLiteral&>(node), v, index, true);
        break;

      case ndkErroneous:
        setEdges(dynamic_cast<expr::Erroneous&>(node), v, index, true);
        break;

      case ndkErroneousTypeExpression:
        setEdges(dynamic_cast<expr::ErroneousTypeExpression&>(node), v, index, true);
        break;

      case ndkExternalTypeExpression:
        setEdges(dynamic_cast<expr::ExternalTypeExpression&>(node), v, index, true);
        break;

      case ndkFieldAccess:
        setEdges(dynamic_cast<expr::FieldAccess&>(node), v, index, true);
        break;

      case ndkFloatLiteral:
        setEdges(dynamic_cast<expr::FloatLiteral&>(node), v, index, true);
        break;

      case ndkIdentifier:
        setEdges(dynamic_cast<expr::Identifier&>(node), v, index, true);
        break;

      case ndkInfixExpression:
        setEdges(dynamic_cast<expr::InfixExpression&>(node), v, index, true);
        break;

      case ndkInstanceOf:
        setEdges(dynamic_cast<expr::InstanceOf&>(node), v, index, true);
        break;

      case ndkIntegerLiteral:
        setEdges(dynamic_cast<expr::IntegerLiteral&>(node), v, index, true);
        break;

      case ndkLongLiteral:
        setEdges(dynamic_cast<expr::LongLiteral&>(node), v, index, true);
        break;

      case ndkMarkerAnnotation:
        setEdges(dynamic_cast<expr::MarkerAnnotation&>(node), v, index, true);
        break;

      case ndkMethodInvocation:
        setEdges(dynamic_cast<expr::MethodInvocation&>(node), v, index, true);
        break;

      case ndkNewArray:
        setEdges(dynamic_cast<expr::NewArray&>(node), v, index, true);
        break;

      case ndkNewClass:
        setEdges(dynamic_cast<expr::NewClass&>(node), v, index, true);
        break;

      case ndkNormalAnnotation:
        setEdges(dynamic_cast<expr::NormalAnnotation&>(node), v, index, true);
        break;

      case ndkNullLiteral:
        setEdges(dynamic_cast<expr::NullLiteral&>(node), v, index, true);
        break;

      case ndkParenthesizedExpression:
        setEdges(dynamic_cast<expr::ParenthesizedExpression&>(node), v, index, true);
        break;

      case ndkPostfixExpression:
        setEdges(dynamic_cast<expr::PostfixExpression&>(node), v, index, true);
        break;

      case ndkPrefixExpression:
        setEdges(dynamic_cast<expr::PrefixExpression&>(node), v, index, true);
        break;

      case ndkPrimitiveTypeExpression:
        setEdges(dynamic_cast<expr::PrimitiveTypeExpression&>(node), v, index, true);
        break;

      case ndkQualifiedTypeExpression:
        setEdges(dynamic_cast<expr::QualifiedTypeExpression&>(node), v, index, true);
        break;

      case ndkSimpleTypeExpression:
        setEdges(dynamic_cast<expr::SimpleTypeExpression&>(node), v, index, true);
        break;

      case ndkSingleElementAnnotation:
        setEdges(dynamic_cast<expr::SingleElementAnnotation&>(node), v, index, true);
        break;

      case ndkStringLiteral:
        setEdges(dynamic_cast<expr::StringLiteral&>(node), v, index, true);
        break;

      case ndkSuper:
        setEdges(dynamic_cast<expr::Super&>(node), v, index, true);
        break;

      case ndkThis:
        setEdges(dynamic_cast<expr::This&>(node), v, index, true);
        break;

      case ndkTypeApplyExpression:
        setEdges(dynamic_cast<expr::TypeApplyExpression&>(node), v, index, true);
        break;

      case ndkTypeCast:
        setEdges(dynamic_cast<expr::TypeCast&>(node), v, index, true);
        break;

      case ndkTypeUnionExpression:
        setEdges(dynamic_cast<expr::TypeUnionExpression&>(node), v, index, true);
        break;

      case ndkWildcardExpression:
        setEdges(dynamic_cast<expr::WildcardExpression&>(node), v, index, true);
        break;

      case ndkAssert:
        setEdges(dynamic_cast<statm::Assert&>(node), v, index, true);
        break;

      case ndkBasicFor:
        setEdges(dynamic_cast<statm::BasicFor&>(node), v, index, true);
        break;

      case ndkBlock:
        setEdges(dynamic_cast<statm::Block&>(node), v, index, true);
        break;

      case ndkBreak:
        setEdges(dynamic_cast<statm::Break&>(node), v, index, true);
        break;

      case ndkCase:
        setEdges(dynamic_cast<statm::Case&>(node), v, index, true);
        break;

      case ndkContinue:
        setEdges(dynamic_cast<statm::Continue&>(node), v, index, true);
        break;

      case ndkDefault:
        setEdges(dynamic_cast<statm::Default&>(node), v, index, true);
        break;

      case ndkDo:
        setEdges(dynamic_cast<statm::Do&>(node), v, index, true);
        break;

      case ndkEmpty:
        setEdges(dynamic_cast<statm::Empty&>(node), v, index, true);
        break;

      case ndkEnhancedFor:
        setEdges(dynamic_cast<statm::EnhancedFor&>(node), v, index, true);
        break;

      case ndkExpressionStatement:
        setEdges(dynamic_cast<statm::ExpressionStatement&>(node), v, index, true);
        break;

      case ndkHandler:
        setEdges(dynamic_cast<statm::Handler&>(node), v, index, true);
        break;

      case ndkIf:
        setEdges(dynamic_cast<statm::If&>(node), v, index, true);
        break;

      case ndkLabeledStatement:
        setEdges(dynamic_cast<statm::LabeledStatement&>(node), v, index, true);
        break;

      case ndkReturn:
        setEdges(dynamic_cast<statm::Return&>(node), v, index, true);
        break;

      case ndkSwitch:
        setEdges(dynamic_cast<statm::Switch&>(node), v, index, true);
        break;

      case ndkSynchronized:
        setEdges(dynamic_cast<statm::Synchronized&>(node), v, index, true);
        break;

      case ndkThrow:
        setEdges(dynamic_cast<statm::Throw&>(node), v, index, true);
        break;

      case ndkTry:
        setEdges(dynamic_cast<statm::Try&>(node), v, index, true);
        break;

      case ndkWhile:
        setEdges(dynamic_cast<statm::While&>(node), v, index, true);
        break;

      case ndkAnnotationType:
        setEdges(dynamic_cast<struc::AnnotationType&>(node), v, index, true);
        break;

      case ndkAnnotationTypeElement:
        setEdges(dynamic_cast<struc::AnnotationTypeElement&>(node), v, index, true);
        break;

      case ndkAnonymousClass:
        setEdges(dynamic_cast<struc::AnonymousClass&>(node), v, index, true);
        break;

      case ndkClass:
        setEdges(dynamic_cast<struc::Class&>(node), v, index, true);
        break;

      case ndkClassGeneric:
        setEdges(dynamic_cast<struc::ClassGeneric&>(node), v, index, true);
        break;

      case ndkCompilationUnit:
        setEdges(dynamic_cast<struc::CompilationUnit&>(node), v, index, true);
        break;

      case ndkEnum:
        setEdges(dynamic_cast<struc::Enum&>(node), v, index, true);
        break;

      case ndkEnumConstant:
        setEdges(dynamic_cast<struc::EnumConstant&>(node), v, index, true);
        break;

      case ndkImport:
        setEdges(dynamic_cast<struc::Import&>(node), v, index, true);
        break;

      case ndkInstanceInitializerBlock:
        setEdges(dynamic_cast<struc::InstanceInitializerBlock&>(node), v, index, true);
        break;

      case ndkInterface:
        setEdges(dynamic_cast<struc::Interface&>(node), v, index, true);
        break;

      case ndkInterfaceGeneric:
        setEdges(dynamic_cast<struc::InterfaceGeneric&>(node), v, index, true);
        break;

      case ndkMethod:
        setEdges(dynamic_cast<struc::Method&>(node), v, index, true);
        break;

      case ndkMethodGeneric:
        setEdges(dynamic_cast<struc::MethodGeneric&>(node), v, index, true);
        break;

      case ndkPackage:
        setEdges(dynamic_cast<struc::Package&>(node), v, index, true);
        break;

      case ndkPackageDeclaration:
        setEdges(dynamic_cast<struc::PackageDeclaration&>(node), v, index, true);
        break;

      case ndkParameter:
        setEdges(dynamic_cast<struc::Parameter&>(node), v, index, true);
        break;

      case ndkStaticInitializerBlock:
        setEdges(dynamic_cast<struc::StaticInitializerBlock&>(node), v, index, true);
        break;

      case ndkTypeParameter:
        setEdges(dynamic_cast<struc::TypeParameter&>(node), v, index, true);
        break;

      case ndkVariable:
        setEdges(dynamic_cast<struc::Variable&>(node), v, index, true);
        break;

      case ndkArrayType:
        setEdges(dynamic_cast<type::ArrayType&>(node), v, index, true);
        break;

      case ndkBooleanType:
        setEdges(dynamic_cast<type::BooleanType&>(node), v, index, true);
        break;

      case ndkByteType:
        setEdges(dynamic_cast<type::ByteType&>(node), v, index, true);
        break;

      case ndkCharType:
        setEdges(dynamic_cast<type::CharType&>(node), v, index, true);
        break;

      case ndkClassType:
        setEdges(dynamic_cast<type::ClassType&>(node), v, index, true);
        break;

      case ndkDoubleType:
        setEdges(dynamic_cast<type::DoubleType&>(node), v, index, true);
        break;

      case ndkErrorType:
        setEdges(dynamic_cast<type::ErrorType&>(node), v, index, true);
        break;

      case ndkFloatType:
        setEdges(dynamic_cast<type::FloatType&>(node), v, index, true);
        break;

      case ndkIntType:
        setEdges(dynamic_cast<type::IntType&>(node), v, index, true);
        break;

      case ndkLongType:
        setEdges(dynamic_cast<type::LongType&>(node), v, index, true);
        break;

      case ndkLowerBoundedWildcardType:
        setEdges(dynamic_cast<type::LowerBoundedWildcardType&>(node), v, index, true);
        break;

      case ndkMethodType:
        setEdges(dynamic_cast<type::MethodType&>(node), v, index, true);
        break;

      case ndkNoType:
        setEdges(dynamic_cast<type::NoType&>(node), v, index, true);
        break;

      case ndkNullType:
        setEdges(dynamic_cast<type::NullType&>(node), v, index, true);
        break;

      case ndkPackageType:
        setEdges(dynamic_cast<type::PackageType&>(node), v, index, true);
        break;

      case ndkParameterizedType:
        setEdges(dynamic_cast<type::ParameterizedType&>(node), v, index, true);
        break;

      case ndkShortType:
        setEdges(dynamic_cast<type::ShortType&>(node), v, index, true);
        break;

      case ndkTypeVariable:
        setEdges(dynamic_cast<type::TypeVariable&>(node), v, index, true);
        break;

      case ndkUnboundedWildcardType:
        setEdges(dynamic_cast<type::UnboundedWildcardType&>(node), v, index, true);
        break;

      case ndkUnionType:
        setEdges(dynamic_cast<type::UnionType&>(node), v, index, true);
        break;

      case ndkUpperBoundedWildcardType:
        setEdges(dynamic_cast<type::UpperBoundedWildcardType&>(node), v, index, true);
        break;

      case ndkVoidType:
        setEdges(dynamic_cast<type::VoidType&>(node), v, index, true);
        break;

      default:
        break;
    }
  }
}

NodeId LinkerBase::remap(NodeId oldId) {
  NodeId newId = tmpMap[oldId];
  if (newId)
    return newId;

  newId = resolve(oldId);
  if (newId)
    return newId;

  throw JavaException(COLUMBUS_LOCATION, CMSG_EX_NODE_HAS_NOT_BEEN_BUILT_INTO_THE_NEW_ASG(oldId));
}

NodeId LinkerBase::resolve(NodeId oldId) {
  if (!tmpFact.getExist(oldId))
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_NODE_NOT_EXIST(oldId));

  base::Base& node = tmpFact.getRef(oldId);
  string position = getPositionString(node);

  if (getIsNeeded(node)) {
    string uniquename = getUniqueString(node);

    StrMultiNodeIdMap::iterator it = strMap.nodes.find(uniquename);
    if (it != strMap.nodes.end() && !it->second.empty()) {
      StrNodeIdMap::iterator it2;
      it2 = it->second.find(position);
      if (it2 != it->second.end()) {
        tmpMap[oldId] = it2->second;
        return it2->second;
      }
    }
  }

  if (!position.empty()) {
    StrNodeIdMap::iterator it = pathMap.find(position);
    if (it != pathMap.end()) {
      tmpMap[oldId] = it->second;
      return it->second;
    }
  }

  return 0;
}

NodeId LinkerBase::getNewNode(const base::Base& node, bool& update) {
  if (!getIsNeeded(node))
    return 0;

  string uniquename = getUniqueString(node);
  string position = getPositionString(node);

  StrMultiNodeIdMap::iterator it = strMap.nodes.find(uniquename);
  if (it != strMap.nodes.end() && !it->second.empty()) {
    StrNodeIdMap::iterator it2;
    it2 = it->second.find(position);
    if (it2 != it->second.end()) {
      if (position.empty())
        update = false;
      return it2->second;
    }
    if (!position.empty()) {
      if (!create) {
        it2 = it->second.find("");
        if (it2 != it->second.end())
          return it2->second;
      }
    } else {
      update = false;
      if (!it->second.empty())
        return it->second.begin()->second;
    }
  }

  return 0;
}

void LinkerBase::remapNode(NodeId oldId, NodeId newId) {
  tmpMap[oldId] = newId;
}


}}}

