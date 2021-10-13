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

#include "python/inc/python.h"

#include <string.h>
#include <algorithm>
#include <stdexcept>

#include "common/inc/StringSup.h"
#include "common/inc/WriteMessage.h"

#include "io/inc/ZippedIO.h"

#include "python/inc/messages.h"

namespace columbus { namespace python { namespace asg {
Factory::Factory(RefDistributorStrTable& st) :
  container(),
  strTable(&st),
  filter(NULL),
  filterOn(true),
  reverseEdges(NULL),
  registeredPointerStorage(),
  root(NULL)
{
  filter = new Filter(*this);
  root = dynamic_cast<module::Package*>(&createNode(ndkPackage, 100));
  root->setName("Python");
  dictType = 0;
}

Factory::~Factory() {
  if (filter) {
    delete filter;
    filter = NULL;
  }

  if (reverseEdges)
    delete reverseEdges;

  for (Container::iterator it = container.begin(); it != container.end(); ++it)
    if (*it)
      delete *it;

}

void Factory::swapStringTable(RefDistributorStrTable& newStrTable){
  if (container.size() > 0 ) {
    std::map<Key,Key> oldAndNewStrKeyMap;
    for (Container::iterator it = container.begin() ;it!= container.end();++it) {
      if (*it) {
        (*it)->swapStringTable(newStrTable,oldAndNewStrKeyMap);
      }
    }
  }
  strTable = &newStrTable;
}

void Factory::save(const std::string &filename , CsiHeader &header) const {
  TurnFilterOffSafely t(*this);

  io::ZippedIO zipIo(filename.c_str(), io::IOBase::omWrite, false);
  zipIo.setEndianState(io::BinaryIO::etLittle);

  // saving header ...
  header.add(CsiHeader::csih_Type, "PythonLanguage");
  header.add(CsiHeader::csih_APIVersion, APIVersion);
  header.add(CsiHeader::csih_BinaryVersion, BinaryVersion);

  header.write(zipIo);

  // saving the ASG
  AlgorithmPreorder algPre;
  VisitorSave vSave(zipIo);
  algPre.run(*this, vSave);

  // Writing the ENDMARK!
  zipIo.writeUInt4(0); // NodeId
  zipIo.writeUShort2(0); // NodeKind

  // saving string table ...
  strTable->save(zipIo, StrTable::strToSave);

  zipIo.close();

}

void Factory::checkHeader(CsiHeader &header) {
  // Checking the type
  std::string type;
  if (!header.get(CsiHeader::csih_Type, type))
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
  if (type != "PythonLanguage")
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_WRONG_FILE_TYPE_INFORMATION);

  // Checking API version
  std::string apiVersion;
  if (!header.get(CsiHeader::csih_APIVersion, apiVersion))
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_MISSING_API_VERSION_INFORMATION);
  if (apiVersion != APIVersion)
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_WRONG_API_VERSION(APIVersion,apiVersion));

  // Checking binary version
  std::string binVersion;
  if (!header.get(CsiHeader::csih_BinaryVersion, binVersion))
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_MISSING_BINARY_VERSION_INFORMATION);
  if (binVersion != BinaryVersion)
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_WRONG_BINARY_VERSION(BinaryVersion,binVersion));

}

void Factory::loadHeader(const std::string &filename, CsiHeader &header) {
  io::BinaryIO binIo(filename.c_str(), io::IOBase::omRead);
  header.read(binIo);
  checkHeader(header);
  binIo.close();
}

void Factory::load(const std::string &filename, CsiHeader &header) {
  clear();

  io::ZippedIO zipIo(filename.c_str(), io::IOBase::omRead, false);

  // loading header
  header.read(zipIo);
  checkHeader(header);

  // loading the ASG
  NodeId id = zipIo.readUInt4();
  NodeKind kind = (NodeKind)zipIo.readUShort2();

  while (id || kind) {
    createNode(kind, id);
    container[id]->load(zipIo);

    id = zipIo.readUInt4();
    kind = (NodeKind)zipIo.readUShort2();
  }

  // loading the string table
  strTable->loadWithKeepingTheRefMap(zipIo);

  root = dynamic_cast<module::Package*>(container[100]);
  // fill the deletedNodeIdList with the free ids
  for (size_t id = 100; id < container.size(); ++id)
    if (container[id] == NULL)
      deletedNodeIdList.push_back(id);

  zipIo.close();

}

void Factory::clear() {
  disableReverseEdges();
  for (Container::iterator i = container.begin(); i != container.end(); ++i) {
    if (*i) {
      alertNodeDestroy (*i);
      delete *i;
      *i = NULL;
    }
  }
  container.clear();
  deletedNodeIdList.clear();
  if (filter) {
    delete filter;
    filter = new Filter(*this);;
  }
}

void Factory::regPointerStorage(SchemaPointerSorage* storage) {
  registeredPointerStorage.push_back(storage);
}

void Factory::unregPointerStorage(SchemaPointerSorage* storage) {
  registeredPointerStorage.erase(std::find(registeredPointerStorage.begin(),registeredPointerStorage.end(),storage));
}

void Factory::alertNodeDestroy(const base::Base* node) {
  for ( std::list<SchemaPointerSorage*>::iterator it = registeredPointerStorage.begin();it != registeredPointerStorage.end();++it) {
    (*it)->onDestroyNode(node);
  }

}

module::Package* Factory::getRoot() const {
  return root;
}

bool Factory::getExist(NodeId id) const {
  if (container.size() <= id)
    return false;
  return container[id] != NULL;
}

base::Base& Factory::getRef(NodeId id) const {
  base::Base* p = NULL;
  if (id < container.size())
    p = container[id];
  if (!p)
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  return *p;
}

base::Base* Factory::getPointer(NodeId id) const {
  base::Base* p = NULL;
  try {
    p = container.at(id);
  } catch (const std::out_of_range&) {
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  }
  return p;
}

RefDistributorStrTable& Factory::getStringTable() const {
  return *strTable;
}

void Factory::destroyNode(NodeId id) {
  if (!reverseEdges)
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (!getExist(id))
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

  std::list<NodeId> nodesToDelete;
  VisitorSubtreeCollector visitor(nodesToDelete);
  AlgorithmPreorder ap;
  ap.setVisitSpecialNodes(false, false);
  ap.run(*this, visitor, id);

  for (std::list<NodeId>::iterator it = nodesToDelete.begin(); it != nodesToDelete.end(); it++) {
    alertNodeDestroy(container[*it]);
  }
  for (std::list<NodeId>::iterator it = nodesToDelete.begin(); it != nodesToDelete.end(); it++) {
    container[*it]->prepareDelete(true);
    if (reverseEdges)
      reverseEdges->removeNode(*it);

    delete container[*it];
    container[*it] = NULL;
    deletedNodeIdList.push_back(*it);
    common::WriteMsg::write(CMSG_THE_NODE_HAVE_BEEN_DESTROYED, *it);
  }
}

void Factory::destroyThisNodeOnly(NodeId id) {
  if (!reverseEdges)
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (id >= container.size())
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

  if (!container[id])
    return;

  container[id]->prepareDelete(true);
  if (reverseEdges)
    reverseEdges->removeNode(id);

  alertNodeDestroy(container[id]);
  delete container[id];
  container[id] = NULL;
  deletedNodeIdList.push_back(id);
}

NodeKind Factory::getNodeKind(NodeId id) const {
  return getRef(id).getNodeKind();
}

Factory::ConstIterator::ConstIterator(const Container* cont, const Factory* fact) :
  container(cont),
  factory(fact),
  i(cont->begin())
{
}

bool Factory::ConstIterator::hasNext() const {
  Container::const_iterator j = i;
  while (j != container->end()  &&  (!*j  ||  factory->getIsFiltered(*j)))
     ++j;
  return j != container->end();
}

const base::Base& Factory::ConstIterator::next() {
  while (i != container->end()  &&  (!*i  ||  factory->getIsFiltered(*i)))
     ++i;
  if (i == container->end())
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_NEXT_ELEMENT_DOES_NOT_EXIST);
  return **i++;
}

const Factory::ConstIterator Factory::constIterator() const {
  return ConstIterator(&container,this);
}

bool Factory::isEmpty() const {
  for (Container::const_iterator it = container.begin(); it != container.end(); ++it) {
    if (*it) {
      return false;
    }
  }
  return true;
}

unsigned Factory::size() const {
  return (unsigned)container.size();
}

void Factory::turnFilterOn() {
  filterOn = true;
}

void Factory::turnFilterOff() {
  filterOn = false;
}

Factory::TurnFilterOffSafely::TurnFilterOffSafely(Factory& fact) : factory(fact), oldState(fact.getIsFilterTurnedOn()) {
  factory.turnFilterOff();
}

Factory::TurnFilterOffSafely::TurnFilterOffSafely(const Factory& fact) : factory((Factory&)fact), oldState(fact.getIsFilterTurnedOn()) {
  factory.turnFilterOff();
}

Factory::TurnFilterOffSafely::~TurnFilterOffSafely() {
  if (oldState)
    factory.turnFilterOn();
}

void* Factory::TurnFilterOffSafely::operator new(size_t) throw() {
  return NULL;
}

void* Factory::TurnFilterOffSafely::operator new[](size_t) throw() {
  return NULL;
}

bool Factory::getIsFilterTurnedOn() const {
  return filterOn;
}

void Factory::initializeFilter() {
  filter->initializeFilter();
}

bool Factory::getIsFiltered(NodeId id) const {
  return !filterOn ? false : filter->getIsFiltered(id);
}

bool Factory::getIsFiltered(const base::Base* node) const {
  if (node == NULL) {
    return true;
  }
  return !filterOn ? false : filter->getIsFiltered(node->getId());
}

void Factory::setFiltered(NodeId id) {
  filter->setFiltered(id);
}

void Factory::setNotFiltered(NodeId id) {
  filter->setNotFiltered(id);
}

void Factory::setNotFilteredThisNode(NodeId id) {
  filter->setNotFilteredThisNode(id);
}

Filter::FilterState Factory::getFilterState(NodeId id) const {
  return filter->getFilterState(id);
}

void Factory::loadFilter(const std::string &filename){
  io::BinaryIO binIo(filename.c_str(), io::IOBase::omRead);

  if (!filter)
    filter = new Filter(*this);

  filter->load(&binIo);

  if (container.size() > filter->container.size())
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_LOADED_FILTER_DOES_NOT_MATCH_TO_THE_CURRENT);

  binIo.close();
}

void Factory::saveFilter(const std::string &filename) const {
  io::BinaryIO binIo(filename.c_str(), io::IOBase::omWrite);
  if (filter)
    filter->save(&binIo);
  binIo.close();
}

void Factory::setFilteredThisNodeOnly(NodeId id) {
  filter->setFilteredThisNodeOnly(id);
}

void Factory::setNotFilteredThisNodeOnly(NodeId id) {
  filter->setNotFilteredThisNodeOnly(id);
}

void Factory::enableReverseEdges(ReverseEdges::FuncPtrWithBaseParameterType newSelector) {
  if (!reverseEdges || (newSelector != reverseEdges->selectorFunc)){
    if (reverseEdges){
      delete reverseEdges;
      common::WriteMsg::write(CMSG_SELECTOR_FUNCTION_IS_CHANGED);
    }
    reverseEdges = new ReverseEdges(this, newSelector);
  }
}

void Factory::disableReverseEdges() {
  if (reverseEdges) {
    delete reverseEdges;
    reverseEdges = NULL;
  }
}

const ReverseEdges& Factory::getReverseEdges(ReverseEdges::FuncPtrWithBaseParameterType newSelector) {
  if (!reverseEdges|| (newSelector != reverseEdges->selectorFunc)){
    if (reverseEdges){
      delete reverseEdges;
      common::WriteMsg::write(CMSG_SELECTOR_FUNCTION_IS_CHANGED);
    }
    reverseEdges = new ReverseEdges(this, newSelector);
  }
  return *reverseEdges;
}

bool Factory::getExistsReverseEdges() const {
  return reverseEdges != NULL;
}

base::Base* Factory::createNode(NodeKind kind) {
  base::Base *p = 0;
  NodeId id;
  if (deletedNodeIdList.empty())
    id = container.size();
  else {
    id = deletedNodeIdList.front();
    deletedNodeIdList.pop_front();
  }
  switch (kind) {
    case ndkArgumentList: p = new expression::ArgumentList(id, this); break;
    case ndkAttributeRef: p = new expression::AttributeRef(id, this); break;
    case ndkAwait: p = new expression::Await(id, this); break;
    case ndkBinaryArithmetic: p = new expression::BinaryArithmetic(id, this); break;
    case ndkBinaryLogical: p = new expression::BinaryLogical(id, this); break;
    case ndkBytesLiteral: p = new expression::BytesLiteral(id, this); break;
    case ndkCall: p = new expression::Call(id, this); break;
    case ndkDictComp: p = new expression::DictComp(id, this); break;
    case ndkDictionary: p = new expression::Dictionary(id, this); break;
    case ndkEllipsis: p = new expression::Ellipsis(id, this); break;
    case ndkExpressionList: p = new expression::ExpressionList(id, this); break;
    case ndkExtSlice: p = new expression::ExtSlice(id, this); break;
    case ndkFloatNumber: p = new expression::FloatNumber(id, this); break;
    case ndkFormattedValue: p = new expression::FormattedValue(id, this); break;
    case ndkGenerator: p = new expression::Generator(id, this); break;
    case ndkGeneratorExpression: p = new expression::GeneratorExpression(id, this); break;
    case ndkIdentifier: p = new expression::Identifier(id, this); break;
    case ndkIfExpression: p = new expression::IfExpression(id, this); break;
    case ndkImagNumber: p = new expression::ImagNumber(id, this); break;
    case ndkIndex: p = new expression::Index(id, this); break;
    case ndkIntegerLiteral: p = new expression::IntegerLiteral(id, this); break;
    case ndkJoinedStr: p = new expression::JoinedStr(id, this); break;
    case ndkKeyValue: p = new expression::KeyValue(id, this); break;
    case ndkKeyword: p = new expression::Keyword(id, this); break;
    case ndkLambda: p = new expression::Lambda(id, this); break;
    case ndkList: p = new expression::List(id, this); break;
    case ndkListComp: p = new expression::ListComp(id, this); break;
    case ndkLongInteger: p = new expression::LongInteger(id, this); break;
    case ndkNamedExpr: p = new expression::NamedExpr(id, this); break;
    case ndkSet: p = new expression::Set(id, this); break;
    case ndkSetComp: p = new expression::SetComp(id, this); break;
    case ndkSlice: p = new expression::Slice(id, this); break;
    case ndkStarred: p = new expression::Starred(id, this); break;
    case ndkStringConversion: p = new expression::StringConversion(id, this); break;
    case ndkStringLiteral: p = new expression::StringLiteral(id, this); break;
    case ndkSubscription: p = new expression::Subscription(id, this); break;
    case ndkUnaryOperation: p = new expression::UnaryOperation(id, this); break;
    case ndkYieldExpression: p = new expression::YieldExpression(id, this); break;
    case ndkModule: p = new module::Module(id, this); break;
    case ndkObject: p = new module::Object(id, this); break;
    case ndkPackage: p = new module::Package(id, this); break;
    case ndkAlias: p = new statement::Alias(id, this); break;
    case ndkAnnAssign: p = new statement::AnnAssign(id, this); break;
    case ndkAssert: p = new statement::Assert(id, this); break;
    case ndkAssign: p = new statement::Assign(id, this); break;
    case ndkAugAssign: p = new statement::AugAssign(id, this); break;
    case ndkBaseSpecifier: p = new statement::BaseSpecifier(id, this); break;
    case ndkBreak: p = new statement::Break(id, this); break;
    case ndkClassDef: p = new statement::ClassDef(id, this); break;
    case ndkContinue: p = new statement::Continue(id, this); break;
    case ndkDelete: p = new statement::Delete(id, this); break;
    case ndkExec: p = new statement::Exec(id, this); break;
    case ndkFor: p = new statement::For(id, this); break;
    case ndkFunctionDef: p = new statement::FunctionDef(id, this); break;
    case ndkGlobal: p = new statement::Global(id, this); break;
    case ndkHandler: p = new statement::Handler(id, this); break;
    case ndkIf: p = new statement::If(id, this); break;
    case ndkImportFrom: p = new statement::ImportFrom(id, this); break;
    case ndkImportStatement: p = new statement::ImportStatement(id, this); break;
    case ndkNonlocal: p = new statement::Nonlocal(id, this); break;
    case ndkParameter: p = new statement::Parameter(id, this); break;
    case ndkPass: p = new statement::Pass(id, this); break;
    case ndkPrint: p = new statement::Print(id, this); break;
    case ndkRaise: p = new statement::Raise(id, this); break;
    case ndkReturn: p = new statement::Return(id, this); break;
    case ndkSuite: p = new statement::Suite(id, this); break;
    case ndkTargetList: p = new statement::TargetList(id, this); break;
    case ndkTry: p = new statement::Try(id, this); break;
    case ndkWhile: p = new statement::While(id, this); break;
    case ndkWith: p = new statement::With(id, this); break;
    case ndkWithItem: p = new statement::WithItem(id, this); break;
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }

  if (container.size() <= id)
    container.resize(id + 1);

  container[id] = p;

  if (filter->container.size() < container.size())
    filter->container.resize(container.size());
  filter->container[p->getId()] = Filter::NotFiltered;

  if (reverseEdges)
    reverseEdges->insertNode(p->getId());

  return p;
}

base::Base& Factory::createNode(NodeKind kind, NodeId i) {
  base::Base *p = 0;
  switch (kind) {
    case ndkComment: p = new base::Comment(i,this); break;
    case ndkDocstring: p = new base::Docstring(i,this); break;
    case ndkArgumentList: p = new expression::ArgumentList(i,this); break;
    case ndkAttributeRef: p = new expression::AttributeRef(i,this); break;
    case ndkAwait: p = new expression::Await(i,this); break;
    case ndkBinaryArithmetic: p = new expression::BinaryArithmetic(i,this); break;
    case ndkBinaryLogical: p = new expression::BinaryLogical(i,this); break;
    case ndkBytesLiteral: p = new expression::BytesLiteral(i,this); break;
    case ndkCall: p = new expression::Call(i,this); break;
    case ndkDictComp: p = new expression::DictComp(i,this); break;
    case ndkDictionary: p = new expression::Dictionary(i,this); break;
    case ndkEllipsis: p = new expression::Ellipsis(i,this); break;
    case ndkExpressionList: p = new expression::ExpressionList(i,this); break;
    case ndkExtSlice: p = new expression::ExtSlice(i,this); break;
    case ndkFloatNumber: p = new expression::FloatNumber(i,this); break;
    case ndkFormattedValue: p = new expression::FormattedValue(i,this); break;
    case ndkGenerator: p = new expression::Generator(i,this); break;
    case ndkGeneratorExpression: p = new expression::GeneratorExpression(i,this); break;
    case ndkIdentifier: p = new expression::Identifier(i,this); break;
    case ndkIfExpression: p = new expression::IfExpression(i,this); break;
    case ndkImagNumber: p = new expression::ImagNumber(i,this); break;
    case ndkIndex: p = new expression::Index(i,this); break;
    case ndkIntegerLiteral: p = new expression::IntegerLiteral(i,this); break;
    case ndkJoinedStr: p = new expression::JoinedStr(i,this); break;
    case ndkKeyValue: p = new expression::KeyValue(i,this); break;
    case ndkKeyword: p = new expression::Keyword(i,this); break;
    case ndkLambda: p = new expression::Lambda(i,this); break;
    case ndkList: p = new expression::List(i,this); break;
    case ndkListComp: p = new expression::ListComp(i,this); break;
    case ndkLongInteger: p = new expression::LongInteger(i,this); break;
    case ndkNamedExpr: p = new expression::NamedExpr(i,this); break;
    case ndkSet: p = new expression::Set(i,this); break;
    case ndkSetComp: p = new expression::SetComp(i,this); break;
    case ndkSlice: p = new expression::Slice(i,this); break;
    case ndkStarred: p = new expression::Starred(i,this); break;
    case ndkStringConversion: p = new expression::StringConversion(i,this); break;
    case ndkStringLiteral: p = new expression::StringLiteral(i,this); break;
    case ndkSubscription: p = new expression::Subscription(i,this); break;
    case ndkUnaryOperation: p = new expression::UnaryOperation(i,this); break;
    case ndkYieldExpression: p = new expression::YieldExpression(i,this); break;
    case ndkModule: p = new module::Module(i,this); break;
    case ndkObject: p = new module::Object(i,this); break;
    case ndkPackage: p = new module::Package(i,this); break;
    case ndkAlias: p = new statement::Alias(i,this); break;
    case ndkAnnAssign: p = new statement::AnnAssign(i,this); break;
    case ndkAssert: p = new statement::Assert(i,this); break;
    case ndkAssign: p = new statement::Assign(i,this); break;
    case ndkAugAssign: p = new statement::AugAssign(i,this); break;
    case ndkBaseSpecifier: p = new statement::BaseSpecifier(i,this); break;
    case ndkBreak: p = new statement::Break(i,this); break;
    case ndkClassDef: p = new statement::ClassDef(i,this); break;
    case ndkContinue: p = new statement::Continue(i,this); break;
    case ndkDelete: p = new statement::Delete(i,this); break;
    case ndkExec: p = new statement::Exec(i,this); break;
    case ndkFor: p = new statement::For(i,this); break;
    case ndkFunctionDef: p = new statement::FunctionDef(i,this); break;
    case ndkGlobal: p = new statement::Global(i,this); break;
    case ndkHandler: p = new statement::Handler(i,this); break;
    case ndkIf: p = new statement::If(i,this); break;
    case ndkImportFrom: p = new statement::ImportFrom(i,this); break;
    case ndkImportStatement: p = new statement::ImportStatement(i,this); break;
    case ndkNonlocal: p = new statement::Nonlocal(i,this); break;
    case ndkParameter: p = new statement::Parameter(i,this); break;
    case ndkPass: p = new statement::Pass(i,this); break;
    case ndkPrint: p = new statement::Print(i,this); break;
    case ndkRaise: p = new statement::Raise(i,this); break;
    case ndkReturn: p = new statement::Return(i,this); break;
    case ndkSuite: p = new statement::Suite(i,this); break;
    case ndkTargetList: p = new statement::TargetList(i,this); break;
    case ndkTry: p = new statement::Try(i,this); break;
    case ndkWhile: p = new statement::While(i,this); break;
    case ndkWith: p = new statement::With(i,this); break;
    case ndkWithItem: p = new statement::WithItem(i,this); break;
    case ndkDictType: p = new type::DictType(i,this); break;
    case ndkReferenceType: p = new type::ReferenceType(i,this); break;
    case ndkSequenceType: p = new type::SequenceType(i,this); break;
    case ndkSimpleType: p = new type::SimpleType(i,this); break;
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }

  if (container.size() <= i)
    container.resize(i + 1);

  container[i] = p;

  if (filter->container.size() < container.size())
    filter->container.resize(container.size());
  filter->container[p->getId()] = Filter::NotFiltered;

  if (reverseEdges)
    reverseEdges->insertNode(p->getId());

  return *p;
}

  expression::ArgumentList* Factory::createArgumentListNode(){
    return  dynamic_cast <expression::ArgumentList*>( createNode(ndkArgumentList));
  }

  expression::AttributeRef* Factory::createAttributeRefNode(){
    return  dynamic_cast <expression::AttributeRef*>( createNode(ndkAttributeRef));
  }

  expression::Await* Factory::createAwaitNode(){
    return  dynamic_cast <expression::Await*>( createNode(ndkAwait));
  }

  expression::BinaryArithmetic* Factory::createBinaryArithmeticNode(){
    return  dynamic_cast <expression::BinaryArithmetic*>( createNode(ndkBinaryArithmetic));
  }

  expression::BinaryLogical* Factory::createBinaryLogicalNode(){
    return  dynamic_cast <expression::BinaryLogical*>( createNode(ndkBinaryLogical));
  }

  expression::BytesLiteral* Factory::createBytesLiteralNode(){
    return  dynamic_cast <expression::BytesLiteral*>( createNode(ndkBytesLiteral));
  }

  expression::Call* Factory::createCallNode(){
    return  dynamic_cast <expression::Call*>( createNode(ndkCall));
  }

  expression::DictComp* Factory::createDictCompNode(){
    return  dynamic_cast <expression::DictComp*>( createNode(ndkDictComp));
  }

  expression::Dictionary* Factory::createDictionaryNode(){
    return  dynamic_cast <expression::Dictionary*>( createNode(ndkDictionary));
  }

  expression::Ellipsis* Factory::createEllipsisNode(){
    return  dynamic_cast <expression::Ellipsis*>( createNode(ndkEllipsis));
  }

  expression::ExpressionList* Factory::createExpressionListNode(){
    return  dynamic_cast <expression::ExpressionList*>( createNode(ndkExpressionList));
  }

  expression::ExtSlice* Factory::createExtSliceNode(){
    return  dynamic_cast <expression::ExtSlice*>( createNode(ndkExtSlice));
  }

  expression::FloatNumber* Factory::createFloatNumberNode(){
    return  dynamic_cast <expression::FloatNumber*>( createNode(ndkFloatNumber));
  }

  expression::FormattedValue* Factory::createFormattedValueNode(){
    return  dynamic_cast <expression::FormattedValue*>( createNode(ndkFormattedValue));
  }

  expression::Generator* Factory::createGeneratorNode(){
    return  dynamic_cast <expression::Generator*>( createNode(ndkGenerator));
  }

  expression::GeneratorExpression* Factory::createGeneratorExpressionNode(){
    return  dynamic_cast <expression::GeneratorExpression*>( createNode(ndkGeneratorExpression));
  }

  expression::Identifier* Factory::createIdentifierNode(){
    return  dynamic_cast <expression::Identifier*>( createNode(ndkIdentifier));
  }

  expression::IfExpression* Factory::createIfExpressionNode(){
    return  dynamic_cast <expression::IfExpression*>( createNode(ndkIfExpression));
  }

  expression::ImagNumber* Factory::createImagNumberNode(){
    return  dynamic_cast <expression::ImagNumber*>( createNode(ndkImagNumber));
  }

  expression::Index* Factory::createIndexNode(){
    return  dynamic_cast <expression::Index*>( createNode(ndkIndex));
  }

  expression::IntegerLiteral* Factory::createIntegerLiteralNode(){
    return  dynamic_cast <expression::IntegerLiteral*>( createNode(ndkIntegerLiteral));
  }

  expression::JoinedStr* Factory::createJoinedStrNode(){
    return  dynamic_cast <expression::JoinedStr*>( createNode(ndkJoinedStr));
  }

  expression::KeyValue* Factory::createKeyValueNode(){
    return  dynamic_cast <expression::KeyValue*>( createNode(ndkKeyValue));
  }

  expression::Keyword* Factory::createKeywordNode(){
    return  dynamic_cast <expression::Keyword*>( createNode(ndkKeyword));
  }

  expression::Lambda* Factory::createLambdaNode(){
    return  dynamic_cast <expression::Lambda*>( createNode(ndkLambda));
  }

  expression::List* Factory::createListNode(){
    return  dynamic_cast <expression::List*>( createNode(ndkList));
  }

  expression::ListComp* Factory::createListCompNode(){
    return  dynamic_cast <expression::ListComp*>( createNode(ndkListComp));
  }

  expression::LongInteger* Factory::createLongIntegerNode(){
    return  dynamic_cast <expression::LongInteger*>( createNode(ndkLongInteger));
  }

  expression::NamedExpr* Factory::createNamedExprNode(){
    return  dynamic_cast <expression::NamedExpr*>( createNode(ndkNamedExpr));
  }

  expression::Set* Factory::createSetNode(){
    return  dynamic_cast <expression::Set*>( createNode(ndkSet));
  }

  expression::SetComp* Factory::createSetCompNode(){
    return  dynamic_cast <expression::SetComp*>( createNode(ndkSetComp));
  }

  expression::Slice* Factory::createSliceNode(){
    return  dynamic_cast <expression::Slice*>( createNode(ndkSlice));
  }

  expression::Starred* Factory::createStarredNode(){
    return  dynamic_cast <expression::Starred*>( createNode(ndkStarred));
  }

  expression::StringConversion* Factory::createStringConversionNode(){
    return  dynamic_cast <expression::StringConversion*>( createNode(ndkStringConversion));
  }

  expression::StringLiteral* Factory::createStringLiteralNode(){
    return  dynamic_cast <expression::StringLiteral*>( createNode(ndkStringLiteral));
  }

  expression::Subscription* Factory::createSubscriptionNode(){
    return  dynamic_cast <expression::Subscription*>( createNode(ndkSubscription));
  }

  expression::UnaryOperation* Factory::createUnaryOperationNode(){
    return  dynamic_cast <expression::UnaryOperation*>( createNode(ndkUnaryOperation));
  }

  expression::YieldExpression* Factory::createYieldExpressionNode(){
    return  dynamic_cast <expression::YieldExpression*>( createNode(ndkYieldExpression));
  }

  module::Module* Factory::createModuleNode(){
    return  dynamic_cast <module::Module*>( createNode(ndkModule));
  }

  module::Object* Factory::createObjectNode(){
    return  dynamic_cast <module::Object*>( createNode(ndkObject));
  }

  module::Package* Factory::createPackageNode(){
    return  dynamic_cast <module::Package*>( createNode(ndkPackage));
  }

  statement::Alias* Factory::createAliasNode(){
    return  dynamic_cast <statement::Alias*>( createNode(ndkAlias));
  }

  statement::AnnAssign* Factory::createAnnAssignNode(){
    return  dynamic_cast <statement::AnnAssign*>( createNode(ndkAnnAssign));
  }

  statement::Assert* Factory::createAssertNode(){
    return  dynamic_cast <statement::Assert*>( createNode(ndkAssert));
  }

  statement::Assign* Factory::createAssignNode(){
    return  dynamic_cast <statement::Assign*>( createNode(ndkAssign));
  }

  statement::AugAssign* Factory::createAugAssignNode(){
    return  dynamic_cast <statement::AugAssign*>( createNode(ndkAugAssign));
  }

  statement::BaseSpecifier* Factory::createBaseSpecifierNode(){
    return  dynamic_cast <statement::BaseSpecifier*>( createNode(ndkBaseSpecifier));
  }

  statement::Break* Factory::createBreakNode(){
    return  dynamic_cast <statement::Break*>( createNode(ndkBreak));
  }

  statement::ClassDef* Factory::createClassDefNode(){
    return  dynamic_cast <statement::ClassDef*>( createNode(ndkClassDef));
  }

  statement::Continue* Factory::createContinueNode(){
    return  dynamic_cast <statement::Continue*>( createNode(ndkContinue));
  }

  statement::Delete* Factory::createDeleteNode(){
    return  dynamic_cast <statement::Delete*>( createNode(ndkDelete));
  }

  statement::Exec* Factory::createExecNode(){
    return  dynamic_cast <statement::Exec*>( createNode(ndkExec));
  }

  statement::For* Factory::createForNode(){
    return  dynamic_cast <statement::For*>( createNode(ndkFor));
  }

  statement::FunctionDef* Factory::createFunctionDefNode(){
    return  dynamic_cast <statement::FunctionDef*>( createNode(ndkFunctionDef));
  }

  statement::Global* Factory::createGlobalNode(){
    return  dynamic_cast <statement::Global*>( createNode(ndkGlobal));
  }

  statement::Handler* Factory::createHandlerNode(){
    return  dynamic_cast <statement::Handler*>( createNode(ndkHandler));
  }

  statement::If* Factory::createIfNode(){
    return  dynamic_cast <statement::If*>( createNode(ndkIf));
  }

  statement::ImportFrom* Factory::createImportFromNode(){
    return  dynamic_cast <statement::ImportFrom*>( createNode(ndkImportFrom));
  }

  statement::ImportStatement* Factory::createImportStatementNode(){
    return  dynamic_cast <statement::ImportStatement*>( createNode(ndkImportStatement));
  }

  statement::Nonlocal* Factory::createNonlocalNode(){
    return  dynamic_cast <statement::Nonlocal*>( createNode(ndkNonlocal));
  }

  statement::Parameter* Factory::createParameterNode(){
    return  dynamic_cast <statement::Parameter*>( createNode(ndkParameter));
  }

  statement::Pass* Factory::createPassNode(){
    return  dynamic_cast <statement::Pass*>( createNode(ndkPass));
  }

  statement::Print* Factory::createPrintNode(){
    return  dynamic_cast <statement::Print*>( createNode(ndkPrint));
  }

  statement::Raise* Factory::createRaiseNode(){
    return  dynamic_cast <statement::Raise*>( createNode(ndkRaise));
  }

  statement::Return* Factory::createReturnNode(){
    return  dynamic_cast <statement::Return*>( createNode(ndkReturn));
  }

  statement::Suite* Factory::createSuiteNode(){
    return  dynamic_cast <statement::Suite*>( createNode(ndkSuite));
  }

  statement::TargetList* Factory::createTargetListNode(){
    return  dynamic_cast <statement::TargetList*>( createNode(ndkTargetList));
  }

  statement::Try* Factory::createTryNode(){
    return  dynamic_cast <statement::Try*>( createNode(ndkTry));
  }

  statement::While* Factory::createWhileNode(){
    return  dynamic_cast <statement::While*>( createNode(ndkWhile));
  }

  statement::With* Factory::createWithNode(){
    return  dynamic_cast <statement::With*>( createNode(ndkWith));
  }

  statement::WithItem* Factory::createWithItemNode(){
    return  dynamic_cast <statement::WithItem*>( createNode(ndkWithItem));
  }

  void Factory::printNodeSizes() {
    printf("base::Comment node: %dbyte(s)\n",(int)sizeof(base::Comment)); 
    printf("base::Docstring node: %dbyte(s)\n",(int)sizeof(base::Docstring)); 
    printf("expression::ArgumentList node: %dbyte(s)\n",(int)sizeof(expression::ArgumentList)); 
    printf("expression::AttributeRef node: %dbyte(s)\n",(int)sizeof(expression::AttributeRef)); 
    printf("expression::Await node: %dbyte(s)\n",(int)sizeof(expression::Await)); 
    printf("expression::BinaryArithmetic node: %dbyte(s)\n",(int)sizeof(expression::BinaryArithmetic)); 
    printf("expression::BinaryLogical node: %dbyte(s)\n",(int)sizeof(expression::BinaryLogical)); 
    printf("expression::BytesLiteral node: %dbyte(s)\n",(int)sizeof(expression::BytesLiteral)); 
    printf("expression::Call node: %dbyte(s)\n",(int)sizeof(expression::Call)); 
    printf("expression::DictComp node: %dbyte(s)\n",(int)sizeof(expression::DictComp)); 
    printf("expression::Dictionary node: %dbyte(s)\n",(int)sizeof(expression::Dictionary)); 
    printf("expression::Ellipsis node: %dbyte(s)\n",(int)sizeof(expression::Ellipsis)); 
    printf("expression::ExpressionList node: %dbyte(s)\n",(int)sizeof(expression::ExpressionList)); 
    printf("expression::ExtSlice node: %dbyte(s)\n",(int)sizeof(expression::ExtSlice)); 
    printf("expression::FloatNumber node: %dbyte(s)\n",(int)sizeof(expression::FloatNumber)); 
    printf("expression::FormattedValue node: %dbyte(s)\n",(int)sizeof(expression::FormattedValue)); 
    printf("expression::Generator node: %dbyte(s)\n",(int)sizeof(expression::Generator)); 
    printf("expression::GeneratorExpression node: %dbyte(s)\n",(int)sizeof(expression::GeneratorExpression)); 
    printf("expression::Identifier node: %dbyte(s)\n",(int)sizeof(expression::Identifier)); 
    printf("expression::IfExpression node: %dbyte(s)\n",(int)sizeof(expression::IfExpression)); 
    printf("expression::ImagNumber node: %dbyte(s)\n",(int)sizeof(expression::ImagNumber)); 
    printf("expression::Index node: %dbyte(s)\n",(int)sizeof(expression::Index)); 
    printf("expression::IntegerLiteral node: %dbyte(s)\n",(int)sizeof(expression::IntegerLiteral)); 
    printf("expression::JoinedStr node: %dbyte(s)\n",(int)sizeof(expression::JoinedStr)); 
    printf("expression::KeyValue node: %dbyte(s)\n",(int)sizeof(expression::KeyValue)); 
    printf("expression::Keyword node: %dbyte(s)\n",(int)sizeof(expression::Keyword)); 
    printf("expression::Lambda node: %dbyte(s)\n",(int)sizeof(expression::Lambda)); 
    printf("expression::List node: %dbyte(s)\n",(int)sizeof(expression::List)); 
    printf("expression::ListComp node: %dbyte(s)\n",(int)sizeof(expression::ListComp)); 
    printf("expression::LongInteger node: %dbyte(s)\n",(int)sizeof(expression::LongInteger)); 
    printf("expression::NamedExpr node: %dbyte(s)\n",(int)sizeof(expression::NamedExpr)); 
    printf("expression::Set node: %dbyte(s)\n",(int)sizeof(expression::Set)); 
    printf("expression::SetComp node: %dbyte(s)\n",(int)sizeof(expression::SetComp)); 
    printf("expression::Slice node: %dbyte(s)\n",(int)sizeof(expression::Slice)); 
    printf("expression::Starred node: %dbyte(s)\n",(int)sizeof(expression::Starred)); 
    printf("expression::StringConversion node: %dbyte(s)\n",(int)sizeof(expression::StringConversion)); 
    printf("expression::StringLiteral node: %dbyte(s)\n",(int)sizeof(expression::StringLiteral)); 
    printf("expression::Subscription node: %dbyte(s)\n",(int)sizeof(expression::Subscription)); 
    printf("expression::UnaryOperation node: %dbyte(s)\n",(int)sizeof(expression::UnaryOperation)); 
    printf("expression::YieldExpression node: %dbyte(s)\n",(int)sizeof(expression::YieldExpression)); 
    printf("module::Module node: %dbyte(s)\n",(int)sizeof(module::Module)); 
    printf("module::Object node: %dbyte(s)\n",(int)sizeof(module::Object)); 
    printf("module::Package node: %dbyte(s)\n",(int)sizeof(module::Package)); 
    printf("statement::Alias node: %dbyte(s)\n",(int)sizeof(statement::Alias)); 
    printf("statement::AnnAssign node: %dbyte(s)\n",(int)sizeof(statement::AnnAssign)); 
    printf("statement::Assert node: %dbyte(s)\n",(int)sizeof(statement::Assert)); 
    printf("statement::Assign node: %dbyte(s)\n",(int)sizeof(statement::Assign)); 
    printf("statement::AugAssign node: %dbyte(s)\n",(int)sizeof(statement::AugAssign)); 
    printf("statement::BaseSpecifier node: %dbyte(s)\n",(int)sizeof(statement::BaseSpecifier)); 
    printf("statement::Break node: %dbyte(s)\n",(int)sizeof(statement::Break)); 
    printf("statement::ClassDef node: %dbyte(s)\n",(int)sizeof(statement::ClassDef)); 
    printf("statement::Continue node: %dbyte(s)\n",(int)sizeof(statement::Continue)); 
    printf("statement::Delete node: %dbyte(s)\n",(int)sizeof(statement::Delete)); 
    printf("statement::Exec node: %dbyte(s)\n",(int)sizeof(statement::Exec)); 
    printf("statement::For node: %dbyte(s)\n",(int)sizeof(statement::For)); 
    printf("statement::FunctionDef node: %dbyte(s)\n",(int)sizeof(statement::FunctionDef)); 
    printf("statement::Global node: %dbyte(s)\n",(int)sizeof(statement::Global)); 
    printf("statement::Handler node: %dbyte(s)\n",(int)sizeof(statement::Handler)); 
    printf("statement::If node: %dbyte(s)\n",(int)sizeof(statement::If)); 
    printf("statement::ImportFrom node: %dbyte(s)\n",(int)sizeof(statement::ImportFrom)); 
    printf("statement::ImportStatement node: %dbyte(s)\n",(int)sizeof(statement::ImportStatement)); 
    printf("statement::Nonlocal node: %dbyte(s)\n",(int)sizeof(statement::Nonlocal)); 
    printf("statement::Parameter node: %dbyte(s)\n",(int)sizeof(statement::Parameter)); 
    printf("statement::Pass node: %dbyte(s)\n",(int)sizeof(statement::Pass)); 
    printf("statement::Print node: %dbyte(s)\n",(int)sizeof(statement::Print)); 
    printf("statement::Raise node: %dbyte(s)\n",(int)sizeof(statement::Raise)); 
    printf("statement::Return node: %dbyte(s)\n",(int)sizeof(statement::Return)); 
    printf("statement::Suite node: %dbyte(s)\n",(int)sizeof(statement::Suite)); 
    printf("statement::TargetList node: %dbyte(s)\n",(int)sizeof(statement::TargetList)); 
    printf("statement::Try node: %dbyte(s)\n",(int)sizeof(statement::Try)); 
    printf("statement::While node: %dbyte(s)\n",(int)sizeof(statement::While)); 
    printf("statement::With node: %dbyte(s)\n",(int)sizeof(statement::With)); 
    printf("statement::WithItem node: %dbyte(s)\n",(int)sizeof(statement::WithItem)); 
    printf("type::DictType node: %dbyte(s)\n",(int)sizeof(type::DictType)); 
    printf("type::ReferenceType node: %dbyte(s)\n",(int)sizeof(type::ReferenceType)); 
    printf("type::SequenceType node: %dbyte(s)\n",(int)sizeof(type::SequenceType)); 
    printf("type::SimpleType node: %dbyte(s)\n",(int)sizeof(type::SimpleType)); 
  }
type::SimpleType& Factory::createSimpleType(SimpleTypeKind kind){
  std::map<SimpleTypeKind, NodeId>::iterator it = simpleType.find(kind);
  
  if(it == simpleType.end()){
    type::SimpleType& type = dynamic_cast<type::SimpleType&>(createNode(ndkSimpleType, container.size()));
    type.setKind(kind);
    simpleType[kind] = type.getId();
    return type;
  }
  
  return dynamic_cast<type::SimpleType&>(getRef((*it).second));
}

type::SequenceType& Factory::createSequenceType(SequenceTypeKind kind){
  std::map<SequenceTypeKind, NodeId>::iterator it = sequenceType.find(kind);

  if(it == sequenceType.end()){
    type::SequenceType& type = dynamic_cast<type::SequenceType&>(createNode(ndkSequenceType, container.size()));
    type.setKind(kind);
    sequenceType[kind] = type.getId();
    return type;
  }
  
  return dynamic_cast<type::SequenceType&>(getRef((*it).second));
}

type::DictType& Factory::createDictType(){
  if(dictType == 0){
    dictType = container.size();
    createNode(ndkDictType, dictType);
  }
  
  return dynamic_cast<type::DictType&>(getRef(dictType));
}

type::ReferenceType& Factory::createReferenceType(NodeId refersTo){
  std::map<NodeId, NodeId>::iterator it = referenceType.find(refersTo);

  if(it == referenceType.end()){
    type::ReferenceType& type = dynamic_cast<type::ReferenceType&>(createNode(ndkReferenceType, container.size()));
    type.setRefersTo(refersTo);
    referenceType[refersTo] = type.getId();
    return type;
  }
  
  return dynamic_cast<type::ReferenceType&>(getRef((*it).second));
}

base::Docstring& Factory::createDocstring() {
  return dynamic_cast<base::Docstring&>(createNode(ndkDocstring, container.size()));
}

base::Comment& Factory::createComment() {
  return dynamic_cast<base::Comment&>(createNode(ndkComment, container.size()));
}


}}}
