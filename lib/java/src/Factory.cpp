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

#include "java/inc/java.h"

#include <string.h>
#include <algorithm>
#include <stdexcept>

#include "common/inc/StringSup.h"
#include "common/inc/WriteMessage.h"

#include "io/inc/ZippedIO.h"

#include "java/inc/messages.h"

namespace columbus { namespace java { namespace asg {
Factory::Factory(RefDistributorStrTable& st) :
  container(),
  strTable(&st),
  filter(NULL),
  filterOn(true),
  reverseEdges(NULL),
  registeredPointerStorage(),
  root(NULL),
  uniqueNameMap(),
  apspecNodes()
{
  filter = new Filter(*this);
  root = dynamic_cast<struc::Package*>(&createNode(ndkPackage, 100));
  root->setName(JAVA_ROOT_NAME);
  root->setQualifiedName(JAVA_ROOT_NAME);

  init();
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
  header.add(CsiHeader::csih_Type, "JavaLanguage");
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
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
  if (type != "JavaLanguage")
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_WRONG_FILE_TYPE_INFORMATION);

  // Checking API version
  std::string apiVersion;
  if (!header.get(CsiHeader::csih_APIVersion, apiVersion))
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_MISSING_API_VERSION_INFORMATION);
  if (apiVersion != APIVersion)
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_WRONG_API_VERSION(APIVersion,apiVersion));

  // Checking binary version
  std::string binVersion;
  if (!header.get(CsiHeader::csih_BinaryVersion, binVersion))
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_MISSING_BINARY_VERSION_INFORMATION);
  if (binVersion != BinaryVersion)
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_WRONG_BINARY_VERSION(BinaryVersion,binVersion));

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

  root = dynamic_cast<struc::Package*>(container[100]);
  // fill the deletedNodeIdList with the free ids
  for (size_t id = 100; id < container.size(); ++id)
    if (container[id] == NULL)
      deletedNodeIdList.push_back(id);

  zipIo.close();

  init();
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
  uniqueNameMap.clear();
  apspecNodes.clear();
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

struc::Package* Factory::getRoot() const {
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
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  return *p;
}

base::Base* Factory::getPointer(NodeId id) const {
  base::Base* p = NULL;
  try {
    p = container.at(id);
  } catch (const std::out_of_range&) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  }
  return p;
}

RefDistributorStrTable& Factory::getStringTable() const {
  return *strTable;
}

void Factory::destroyNode(NodeId id) {
  if (!reverseEdges)
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (!getExist(id))
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (id >= container.size())
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_NEXT_ELEMENT_DOES_NOT_EXIST);
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
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_LOADED_FILTER_DOES_NOT_MATCH_TO_THE_CURRENT);

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

  void Factory::createAsgStat() const {
    createAsgStat(true, true, true);
  }

  void Factory::createAsgStat(bool allNodesStat, bool usedNodesStatOnly, bool edgeStat) const {
    VisitorAsgStat vas;
    AlgorithmPreorder ap;
    ap.setSafeMode();
    ap.setVisitSpecialNodes(allNodesStat, usedNodesStatOnly);
    ap.run(*this, vas);
    unsigned long totalMemUsage = 0; /* it is the sum of memory of nodes */
    common::WriteMsg::write(common::WriteMsg::mlNormal, "Nodes,All,This,Obj Size,Used Mem,Used Mem\n");
    for (int i = 0; i < 157; ++i) {
      totalMemUsage += vas.nodeStatSimple[i] * vas.nodeSizes[i];
      common::WriteMsg::write(common::WriteMsg::mlNormal, "%s,%d,%d,%d,%d,%d\n", vas.nodeNames[i], vas.nodeStatParent[i], vas.nodeStatSimple[i], vas.nodeSizes[i], vas.nodeStatSimple[i] * vas.nodeSizes[i], vas.nodeStatSimple[i] * vas.nodeSizes[i] / 1024);
    }    common::WriteMsg::write(common::WriteMsg::mlNormal, "\n");
    common::WriteMsg::write(common::WriteMsg::mlNormal, "Memory used by nodes: %d (%d KB)\n\n", totalMemUsage, totalMemUsage );
    if (edgeStat) {
      common::WriteMsg::write(common::WriteMsg::mlNormal, "Edges,Cardinality\n");
      for (int i = 0; i < 133; ++i)
        common::WriteMsg::write(common::WriteMsg::mlNormal, "%s,%d\n", Common::toString((EdgeKind)i).c_str(), vas.edgeStat[i]);
      common::WriteMsg::write(common::WriteMsg::mlNormal, "\n\n");
    }

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
    case ndkAnnotatedTypeExpression: p = new expr::AnnotatedTypeExpression(id, this); break;
    case ndkArrayAccess: p = new expr::ArrayAccess(id, this); break;
    case ndkArrayTypeExpression: p = new expr::ArrayTypeExpression(id, this); break;
    case ndkAssignment: p = new expr::Assignment(id, this); break;
    case ndkBooleanLiteral: p = new expr::BooleanLiteral(id, this); break;
    case ndkCharacterLiteral: p = new expr::CharacterLiteral(id, this); break;
    case ndkClassLiteral: p = new expr::ClassLiteral(id, this); break;
    case ndkConditional: p = new expr::Conditional(id, this); break;
    case ndkDoubleLiteral: p = new expr::DoubleLiteral(id, this); break;
    case ndkErroneous: p = new expr::Erroneous(id, this); break;
    case ndkErroneousTypeExpression: p = new expr::ErroneousTypeExpression(id, this); break;
    case ndkExternalTypeExpression: p = new expr::ExternalTypeExpression(id, this); break;
    case ndkFieldAccess: p = new expr::FieldAccess(id, this); break;
    case ndkFloatLiteral: p = new expr::FloatLiteral(id, this); break;
    case ndkIdentifier: p = new expr::Identifier(id, this); break;
    case ndkInfixExpression: p = new expr::InfixExpression(id, this); break;
    case ndkInstanceOf: p = new expr::InstanceOf(id, this); break;
    case ndkIntegerLiteral: p = new expr::IntegerLiteral(id, this); break;
    case ndkLambda: p = new expr::Lambda(id, this); break;
    case ndkLongLiteral: p = new expr::LongLiteral(id, this); break;
    case ndkMarkerAnnotation: p = new expr::MarkerAnnotation(id, this); break;
    case ndkMemberReference: p = new expr::MemberReference(id, this); break;
    case ndkMethodInvocation: p = new expr::MethodInvocation(id, this); break;
    case ndkNewArray: p = new expr::NewArray(id, this); break;
    case ndkNewClass: p = new expr::NewClass(id, this); break;
    case ndkNormalAnnotation: p = new expr::NormalAnnotation(id, this); break;
    case ndkNullLiteral: p = new expr::NullLiteral(id, this); break;
    case ndkParenthesizedExpression: p = new expr::ParenthesizedExpression(id, this); break;
    case ndkPostfixExpression: p = new expr::PostfixExpression(id, this); break;
    case ndkPrefixExpression: p = new expr::PrefixExpression(id, this); break;
    case ndkPrimitiveTypeExpression: p = new expr::PrimitiveTypeExpression(id, this); break;
    case ndkQualifiedTypeExpression: p = new expr::QualifiedTypeExpression(id, this); break;
    case ndkSimpleTypeExpression: p = new expr::SimpleTypeExpression(id, this); break;
    case ndkSingleElementAnnotation: p = new expr::SingleElementAnnotation(id, this); break;
    case ndkStringLiteral: p = new expr::StringLiteral(id, this); break;
    case ndkSuper: p = new expr::Super(id, this); break;
    case ndkThis: p = new expr::This(id, this); break;
    case ndkTypeApplyExpression: p = new expr::TypeApplyExpression(id, this); break;
    case ndkTypeCast: p = new expr::TypeCast(id, this); break;
    case ndkTypeIntersectionExpression: p = new expr::TypeIntersectionExpression(id, this); break;
    case ndkTypeUnionExpression: p = new expr::TypeUnionExpression(id, this); break;
    case ndkWildcardExpression: p = new expr::WildcardExpression(id, this); break;
    case ndkExports: p = new module::Exports(id, this); break;
    case ndkOpens: p = new module::Opens(id, this); break;
    case ndkProvides: p = new module::Provides(id, this); break;
    case ndkRequires: p = new module::Requires(id, this); break;
    case ndkUses: p = new module::Uses(id, this); break;
    case ndkAssert: p = new statm::Assert(id, this); break;
    case ndkBasicFor: p = new statm::BasicFor(id, this); break;
    case ndkBlock: p = new statm::Block(id, this); break;
    case ndkBreak: p = new statm::Break(id, this); break;
    case ndkCase: p = new statm::Case(id, this); break;
    case ndkContinue: p = new statm::Continue(id, this); break;
    case ndkDefault: p = new statm::Default(id, this); break;
    case ndkDo: p = new statm::Do(id, this); break;
    case ndkEmpty: p = new statm::Empty(id, this); break;
    case ndkEnhancedFor: p = new statm::EnhancedFor(id, this); break;
    case ndkExpressionStatement: p = new statm::ExpressionStatement(id, this); break;
    case ndkHandler: p = new statm::Handler(id, this); break;
    case ndkIf: p = new statm::If(id, this); break;
    case ndkLabeledStatement: p = new statm::LabeledStatement(id, this); break;
    case ndkReturn: p = new statm::Return(id, this); break;
    case ndkSwitch: p = new statm::Switch(id, this); break;
    case ndkSynchronized: p = new statm::Synchronized(id, this); break;
    case ndkThrow: p = new statm::Throw(id, this); break;
    case ndkTry: p = new statm::Try(id, this); break;
    case ndkWhile: p = new statm::While(id, this); break;
    case ndkAnnotationType: p = new struc::AnnotationType(id, this); break;
    case ndkAnnotationTypeElement: p = new struc::AnnotationTypeElement(id, this); break;
    case ndkAnonymousClass: p = new struc::AnonymousClass(id, this); break;
    case ndkClass: p = new struc::Class(id, this); break;
    case ndkClassGeneric: p = new struc::ClassGeneric(id, this); break;
    case ndkCompilationUnit: p = new struc::CompilationUnit(id, this); break;
    case ndkEnum: p = new struc::Enum(id, this); break;
    case ndkEnumConstant: p = new struc::EnumConstant(id, this); break;
    case ndkImport: p = new struc::Import(id, this); break;
    case ndkInstanceInitializerBlock: p = new struc::InstanceInitializerBlock(id, this); break;
    case ndkInterface: p = new struc::Interface(id, this); break;
    case ndkInterfaceGeneric: p = new struc::InterfaceGeneric(id, this); break;
    case ndkMethod: p = new struc::Method(id, this); break;
    case ndkMethodGeneric: p = new struc::MethodGeneric(id, this); break;
    case ndkModule: p = new struc::Module(id, this); break;
    case ndkModuleDeclaration: p = new struc::ModuleDeclaration(id, this); break;
    case ndkPackage: p = new struc::Package(id, this); break;
    case ndkPackageDeclaration: p = new struc::PackageDeclaration(id, this); break;
    case ndkParameter: p = new struc::Parameter(id, this); break;
    case ndkStaticInitializerBlock: p = new struc::StaticInitializerBlock(id, this); break;
    case ndkTypeParameter: p = new struc::TypeParameter(id, this); break;
    case ndkVariable: p = new struc::Variable(id, this); break;
    case ndkIntersectionType: p = new type::IntersectionType(id, this); break;
    case ndkModuleType: p = new type::ModuleType(id, this); break;
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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
    case ndkBlockComment: p = new base::BlockComment(i,this); break;
    case ndkJavadocComment: p = new base::JavadocComment(i,this); break;
    case ndkLineComment: p = new base::LineComment(i,this); break;
    case ndkAnnotatedTypeExpression: p = new expr::AnnotatedTypeExpression(i,this); break;
    case ndkArrayAccess: p = new expr::ArrayAccess(i,this); break;
    case ndkArrayTypeExpression: p = new expr::ArrayTypeExpression(i,this); break;
    case ndkAssignment: p = new expr::Assignment(i,this); break;
    case ndkBooleanLiteral: p = new expr::BooleanLiteral(i,this); break;
    case ndkCharacterLiteral: p = new expr::CharacterLiteral(i,this); break;
    case ndkClassLiteral: p = new expr::ClassLiteral(i,this); break;
    case ndkConditional: p = new expr::Conditional(i,this); break;
    case ndkDoubleLiteral: p = new expr::DoubleLiteral(i,this); break;
    case ndkErroneous: p = new expr::Erroneous(i,this); break;
    case ndkErroneousTypeExpression: p = new expr::ErroneousTypeExpression(i,this); break;
    case ndkExternalTypeExpression: p = new expr::ExternalTypeExpression(i,this); break;
    case ndkFieldAccess: p = new expr::FieldAccess(i,this); break;
    case ndkFloatLiteral: p = new expr::FloatLiteral(i,this); break;
    case ndkIdentifier: p = new expr::Identifier(i,this); break;
    case ndkInfixExpression: p = new expr::InfixExpression(i,this); break;
    case ndkInstanceOf: p = new expr::InstanceOf(i,this); break;
    case ndkIntegerLiteral: p = new expr::IntegerLiteral(i,this); break;
    case ndkLambda: p = new expr::Lambda(i,this); break;
    case ndkLongLiteral: p = new expr::LongLiteral(i,this); break;
    case ndkMarkerAnnotation: p = new expr::MarkerAnnotation(i,this); break;
    case ndkMemberReference: p = new expr::MemberReference(i,this); break;
    case ndkMethodInvocation: p = new expr::MethodInvocation(i,this); break;
    case ndkNewArray: p = new expr::NewArray(i,this); break;
    case ndkNewClass: p = new expr::NewClass(i,this); break;
    case ndkNormalAnnotation: p = new expr::NormalAnnotation(i,this); break;
    case ndkNullLiteral: p = new expr::NullLiteral(i,this); break;
    case ndkParenthesizedExpression: p = new expr::ParenthesizedExpression(i,this); break;
    case ndkPostfixExpression: p = new expr::PostfixExpression(i,this); break;
    case ndkPrefixExpression: p = new expr::PrefixExpression(i,this); break;
    case ndkPrimitiveTypeExpression: p = new expr::PrimitiveTypeExpression(i,this); break;
    case ndkQualifiedTypeExpression: p = new expr::QualifiedTypeExpression(i,this); break;
    case ndkSimpleTypeExpression: p = new expr::SimpleTypeExpression(i,this); break;
    case ndkSingleElementAnnotation: p = new expr::SingleElementAnnotation(i,this); break;
    case ndkStringLiteral: p = new expr::StringLiteral(i,this); break;
    case ndkSuper: p = new expr::Super(i,this); break;
    case ndkThis: p = new expr::This(i,this); break;
    case ndkTypeApplyExpression: p = new expr::TypeApplyExpression(i,this); break;
    case ndkTypeCast: p = new expr::TypeCast(i,this); break;
    case ndkTypeIntersectionExpression: p = new expr::TypeIntersectionExpression(i,this); break;
    case ndkTypeUnionExpression: p = new expr::TypeUnionExpression(i,this); break;
    case ndkWildcardExpression: p = new expr::WildcardExpression(i,this); break;
    case ndkExports: p = new module::Exports(i,this); break;
    case ndkOpens: p = new module::Opens(i,this); break;
    case ndkProvides: p = new module::Provides(i,this); break;
    case ndkRequires: p = new module::Requires(i,this); break;
    case ndkUses: p = new module::Uses(i,this); break;
    case ndkAssert: p = new statm::Assert(i,this); break;
    case ndkBasicFor: p = new statm::BasicFor(i,this); break;
    case ndkBlock: p = new statm::Block(i,this); break;
    case ndkBreak: p = new statm::Break(i,this); break;
    case ndkCase: p = new statm::Case(i,this); break;
    case ndkContinue: p = new statm::Continue(i,this); break;
    case ndkDefault: p = new statm::Default(i,this); break;
    case ndkDo: p = new statm::Do(i,this); break;
    case ndkEmpty: p = new statm::Empty(i,this); break;
    case ndkEnhancedFor: p = new statm::EnhancedFor(i,this); break;
    case ndkExpressionStatement: p = new statm::ExpressionStatement(i,this); break;
    case ndkHandler: p = new statm::Handler(i,this); break;
    case ndkIf: p = new statm::If(i,this); break;
    case ndkLabeledStatement: p = new statm::LabeledStatement(i,this); break;
    case ndkReturn: p = new statm::Return(i,this); break;
    case ndkSwitch: p = new statm::Switch(i,this); break;
    case ndkSynchronized: p = new statm::Synchronized(i,this); break;
    case ndkThrow: p = new statm::Throw(i,this); break;
    case ndkTry: p = new statm::Try(i,this); break;
    case ndkWhile: p = new statm::While(i,this); break;
    case ndkAnnotationType: p = new struc::AnnotationType(i,this); break;
    case ndkAnnotationTypeElement: p = new struc::AnnotationTypeElement(i,this); break;
    case ndkAnonymousClass: p = new struc::AnonymousClass(i,this); break;
    case ndkClass: p = new struc::Class(i,this); break;
    case ndkClassGeneric: p = new struc::ClassGeneric(i,this); break;
    case ndkCompilationUnit: p = new struc::CompilationUnit(i,this); break;
    case ndkEnum: p = new struc::Enum(i,this); break;
    case ndkEnumConstant: p = new struc::EnumConstant(i,this); break;
    case ndkImport: p = new struc::Import(i,this); break;
    case ndkInstanceInitializerBlock: p = new struc::InstanceInitializerBlock(i,this); break;
    case ndkInterface: p = new struc::Interface(i,this); break;
    case ndkInterfaceGeneric: p = new struc::InterfaceGeneric(i,this); break;
    case ndkMethod: p = new struc::Method(i,this); break;
    case ndkMethodGeneric: p = new struc::MethodGeneric(i,this); break;
    case ndkModule: p = new struc::Module(i,this); break;
    case ndkModuleDeclaration: p = new struc::ModuleDeclaration(i,this); break;
    case ndkPackage: p = new struc::Package(i,this); break;
    case ndkPackageDeclaration: p = new struc::PackageDeclaration(i,this); break;
    case ndkParameter: p = new struc::Parameter(i,this); break;
    case ndkStaticInitializerBlock: p = new struc::StaticInitializerBlock(i,this); break;
    case ndkTypeParameter: p = new struc::TypeParameter(i,this); break;
    case ndkVariable: p = new struc::Variable(i,this); break;
    case ndkArrayType: p = new type::ArrayType(i,this); break;
    case ndkBooleanType: p = new type::BooleanType(i,this); break;
    case ndkByteType: p = new type::ByteType(i,this); break;
    case ndkCharType: p = new type::CharType(i,this); break;
    case ndkClassType: p = new type::ClassType(i,this); break;
    case ndkDoubleType: p = new type::DoubleType(i,this); break;
    case ndkErrorType: p = new type::ErrorType(i,this); break;
    case ndkFloatType: p = new type::FloatType(i,this); break;
    case ndkIntType: p = new type::IntType(i,this); break;
    case ndkIntersectionType: p = new type::IntersectionType(i,this); break;
    case ndkLongType: p = new type::LongType(i,this); break;
    case ndkLowerBoundedWildcardType: p = new type::LowerBoundedWildcardType(i,this); break;
    case ndkMethodType: p = new type::MethodType(i,this); break;
    case ndkModuleType: p = new type::ModuleType(i,this); break;
    case ndkNoType: p = new type::NoType(i,this); break;
    case ndkNullType: p = new type::NullType(i,this); break;
    case ndkPackageType: p = new type::PackageType(i,this); break;
    case ndkParameterizedType: p = new type::ParameterizedType(i,this); break;
    case ndkShortType: p = new type::ShortType(i,this); break;
    case ndkTypeVariable: p = new type::TypeVariable(i,this); break;
    case ndkUnboundedWildcardType: p = new type::UnboundedWildcardType(i,this); break;
    case ndkUnionType: p = new type::UnionType(i,this); break;
    case ndkUpperBoundedWildcardType: p = new type::UpperBoundedWildcardType(i,this); break;
    case ndkVoidType: p = new type::VoidType(i,this); break;
    default: throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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

void Factory::sort() {
  TurnFilterOffSafely tfos(*this);

  for (Container::iterator it = container.begin(); it != container.end(); ++it) {
    if (*it) {
      if (!Common::getIsScope(**it))
        continue;

      (*it)->sort();
    }
  }
}

  expr::AnnotatedTypeExpression* Factory::createAnnotatedTypeExpressionNode(){
    return  dynamic_cast <expr::AnnotatedTypeExpression*>( createNode(ndkAnnotatedTypeExpression));
  }

  expr::ArrayAccess* Factory::createArrayAccessNode(){
    return  dynamic_cast <expr::ArrayAccess*>( createNode(ndkArrayAccess));
  }

  expr::ArrayTypeExpression* Factory::createArrayTypeExpressionNode(){
    return  dynamic_cast <expr::ArrayTypeExpression*>( createNode(ndkArrayTypeExpression));
  }

  expr::Assignment* Factory::createAssignmentNode(){
    return  dynamic_cast <expr::Assignment*>( createNode(ndkAssignment));
  }

  expr::BooleanLiteral* Factory::createBooleanLiteralNode(){
    return  dynamic_cast <expr::BooleanLiteral*>( createNode(ndkBooleanLiteral));
  }

  expr::CharacterLiteral* Factory::createCharacterLiteralNode(){
    return  dynamic_cast <expr::CharacterLiteral*>( createNode(ndkCharacterLiteral));
  }

  expr::ClassLiteral* Factory::createClassLiteralNode(){
    return  dynamic_cast <expr::ClassLiteral*>( createNode(ndkClassLiteral));
  }

  expr::Conditional* Factory::createConditionalNode(){
    return  dynamic_cast <expr::Conditional*>( createNode(ndkConditional));
  }

  expr::DoubleLiteral* Factory::createDoubleLiteralNode(){
    return  dynamic_cast <expr::DoubleLiteral*>( createNode(ndkDoubleLiteral));
  }

  expr::Erroneous* Factory::createErroneousNode(){
    return  dynamic_cast <expr::Erroneous*>( createNode(ndkErroneous));
  }

  expr::ErroneousTypeExpression* Factory::createErroneousTypeExpressionNode(){
    return  dynamic_cast <expr::ErroneousTypeExpression*>( createNode(ndkErroneousTypeExpression));
  }

  expr::ExternalTypeExpression* Factory::createExternalTypeExpressionNode(){
    return  dynamic_cast <expr::ExternalTypeExpression*>( createNode(ndkExternalTypeExpression));
  }

  expr::FieldAccess* Factory::createFieldAccessNode(){
    return  dynamic_cast <expr::FieldAccess*>( createNode(ndkFieldAccess));
  }

  expr::FloatLiteral* Factory::createFloatLiteralNode(){
    return  dynamic_cast <expr::FloatLiteral*>( createNode(ndkFloatLiteral));
  }

  expr::Identifier* Factory::createIdentifierNode(){
    return  dynamic_cast <expr::Identifier*>( createNode(ndkIdentifier));
  }

  expr::InfixExpression* Factory::createInfixExpressionNode(){
    return  dynamic_cast <expr::InfixExpression*>( createNode(ndkInfixExpression));
  }

  expr::InstanceOf* Factory::createInstanceOfNode(){
    return  dynamic_cast <expr::InstanceOf*>( createNode(ndkInstanceOf));
  }

  expr::IntegerLiteral* Factory::createIntegerLiteralNode(){
    return  dynamic_cast <expr::IntegerLiteral*>( createNode(ndkIntegerLiteral));
  }

  expr::Lambda* Factory::createLambdaNode(){
    return  dynamic_cast <expr::Lambda*>( createNode(ndkLambda));
  }

  expr::LongLiteral* Factory::createLongLiteralNode(){
    return  dynamic_cast <expr::LongLiteral*>( createNode(ndkLongLiteral));
  }

  expr::MarkerAnnotation* Factory::createMarkerAnnotationNode(){
    return  dynamic_cast <expr::MarkerAnnotation*>( createNode(ndkMarkerAnnotation));
  }

  expr::MemberReference* Factory::createMemberReferenceNode(){
    return  dynamic_cast <expr::MemberReference*>( createNode(ndkMemberReference));
  }

  expr::MethodInvocation* Factory::createMethodInvocationNode(){
    return  dynamic_cast <expr::MethodInvocation*>( createNode(ndkMethodInvocation));
  }

  expr::NewArray* Factory::createNewArrayNode(){
    return  dynamic_cast <expr::NewArray*>( createNode(ndkNewArray));
  }

  expr::NewClass* Factory::createNewClassNode(){
    return  dynamic_cast <expr::NewClass*>( createNode(ndkNewClass));
  }

  expr::NormalAnnotation* Factory::createNormalAnnotationNode(){
    return  dynamic_cast <expr::NormalAnnotation*>( createNode(ndkNormalAnnotation));
  }

  expr::NullLiteral* Factory::createNullLiteralNode(){
    return  dynamic_cast <expr::NullLiteral*>( createNode(ndkNullLiteral));
  }

  expr::ParenthesizedExpression* Factory::createParenthesizedExpressionNode(){
    return  dynamic_cast <expr::ParenthesizedExpression*>( createNode(ndkParenthesizedExpression));
  }

  expr::PostfixExpression* Factory::createPostfixExpressionNode(){
    return  dynamic_cast <expr::PostfixExpression*>( createNode(ndkPostfixExpression));
  }

  expr::PrefixExpression* Factory::createPrefixExpressionNode(){
    return  dynamic_cast <expr::PrefixExpression*>( createNode(ndkPrefixExpression));
  }

  expr::PrimitiveTypeExpression* Factory::createPrimitiveTypeExpressionNode(){
    return  dynamic_cast <expr::PrimitiveTypeExpression*>( createNode(ndkPrimitiveTypeExpression));
  }

  expr::QualifiedTypeExpression* Factory::createQualifiedTypeExpressionNode(){
    return  dynamic_cast <expr::QualifiedTypeExpression*>( createNode(ndkQualifiedTypeExpression));
  }

  expr::SimpleTypeExpression* Factory::createSimpleTypeExpressionNode(){
    return  dynamic_cast <expr::SimpleTypeExpression*>( createNode(ndkSimpleTypeExpression));
  }

  expr::SingleElementAnnotation* Factory::createSingleElementAnnotationNode(){
    return  dynamic_cast <expr::SingleElementAnnotation*>( createNode(ndkSingleElementAnnotation));
  }

  expr::StringLiteral* Factory::createStringLiteralNode(){
    return  dynamic_cast <expr::StringLiteral*>( createNode(ndkStringLiteral));
  }

  expr::Super* Factory::createSuperNode(){
    return  dynamic_cast <expr::Super*>( createNode(ndkSuper));
  }

  expr::This* Factory::createThisNode(){
    return  dynamic_cast <expr::This*>( createNode(ndkThis));
  }

  expr::TypeApplyExpression* Factory::createTypeApplyExpressionNode(){
    return  dynamic_cast <expr::TypeApplyExpression*>( createNode(ndkTypeApplyExpression));
  }

  expr::TypeCast* Factory::createTypeCastNode(){
    return  dynamic_cast <expr::TypeCast*>( createNode(ndkTypeCast));
  }

  expr::TypeIntersectionExpression* Factory::createTypeIntersectionExpressionNode(){
    return  dynamic_cast <expr::TypeIntersectionExpression*>( createNode(ndkTypeIntersectionExpression));
  }

  expr::TypeUnionExpression* Factory::createTypeUnionExpressionNode(){
    return  dynamic_cast <expr::TypeUnionExpression*>( createNode(ndkTypeUnionExpression));
  }

  expr::WildcardExpression* Factory::createWildcardExpressionNode(){
    return  dynamic_cast <expr::WildcardExpression*>( createNode(ndkWildcardExpression));
  }

  module::Exports* Factory::createExportsNode(){
    return  dynamic_cast <module::Exports*>( createNode(ndkExports));
  }

  module::Opens* Factory::createOpensNode(){
    return  dynamic_cast <module::Opens*>( createNode(ndkOpens));
  }

  module::Provides* Factory::createProvidesNode(){
    return  dynamic_cast <module::Provides*>( createNode(ndkProvides));
  }

  module::Requires* Factory::createRequiresNode(){
    return  dynamic_cast <module::Requires*>( createNode(ndkRequires));
  }

  module::Uses* Factory::createUsesNode(){
    return  dynamic_cast <module::Uses*>( createNode(ndkUses));
  }

  statm::Assert* Factory::createAssertNode(){
    return  dynamic_cast <statm::Assert*>( createNode(ndkAssert));
  }

  statm::BasicFor* Factory::createBasicForNode(){
    return  dynamic_cast <statm::BasicFor*>( createNode(ndkBasicFor));
  }

  statm::Block* Factory::createBlockNode(){
    return  dynamic_cast <statm::Block*>( createNode(ndkBlock));
  }

  statm::Break* Factory::createBreakNode(){
    return  dynamic_cast <statm::Break*>( createNode(ndkBreak));
  }

  statm::Case* Factory::createCaseNode(){
    return  dynamic_cast <statm::Case*>( createNode(ndkCase));
  }

  statm::Continue* Factory::createContinueNode(){
    return  dynamic_cast <statm::Continue*>( createNode(ndkContinue));
  }

  statm::Default* Factory::createDefaultNode(){
    return  dynamic_cast <statm::Default*>( createNode(ndkDefault));
  }

  statm::Do* Factory::createDoNode(){
    return  dynamic_cast <statm::Do*>( createNode(ndkDo));
  }

  statm::Empty* Factory::createEmptyNode(){
    return  dynamic_cast <statm::Empty*>( createNode(ndkEmpty));
  }

  statm::EnhancedFor* Factory::createEnhancedForNode(){
    return  dynamic_cast <statm::EnhancedFor*>( createNode(ndkEnhancedFor));
  }

  statm::ExpressionStatement* Factory::createExpressionStatementNode(){
    return  dynamic_cast <statm::ExpressionStatement*>( createNode(ndkExpressionStatement));
  }

  statm::Handler* Factory::createHandlerNode(){
    return  dynamic_cast <statm::Handler*>( createNode(ndkHandler));
  }

  statm::If* Factory::createIfNode(){
    return  dynamic_cast <statm::If*>( createNode(ndkIf));
  }

  statm::LabeledStatement* Factory::createLabeledStatementNode(){
    return  dynamic_cast <statm::LabeledStatement*>( createNode(ndkLabeledStatement));
  }

  statm::Return* Factory::createReturnNode(){
    return  dynamic_cast <statm::Return*>( createNode(ndkReturn));
  }

  statm::Switch* Factory::createSwitchNode(){
    return  dynamic_cast <statm::Switch*>( createNode(ndkSwitch));
  }

  statm::Synchronized* Factory::createSynchronizedNode(){
    return  dynamic_cast <statm::Synchronized*>( createNode(ndkSynchronized));
  }

  statm::Throw* Factory::createThrowNode(){
    return  dynamic_cast <statm::Throw*>( createNode(ndkThrow));
  }

  statm::Try* Factory::createTryNode(){
    return  dynamic_cast <statm::Try*>( createNode(ndkTry));
  }

  statm::While* Factory::createWhileNode(){
    return  dynamic_cast <statm::While*>( createNode(ndkWhile));
  }

  struc::AnnotationType* Factory::createAnnotationTypeNode(){
    return  dynamic_cast <struc::AnnotationType*>( createNode(ndkAnnotationType));
  }

  struc::AnnotationTypeElement* Factory::createAnnotationTypeElementNode(){
    return  dynamic_cast <struc::AnnotationTypeElement*>( createNode(ndkAnnotationTypeElement));
  }

  struc::AnonymousClass* Factory::createAnonymousClassNode(){
    return  dynamic_cast <struc::AnonymousClass*>( createNode(ndkAnonymousClass));
  }

  struc::Class* Factory::createClassNode(){
    return  dynamic_cast <struc::Class*>( createNode(ndkClass));
  }

  struc::ClassGeneric* Factory::createClassGenericNode(){
    return  dynamic_cast <struc::ClassGeneric*>( createNode(ndkClassGeneric));
  }

  struc::CompilationUnit* Factory::createCompilationUnitNode(){
    return  dynamic_cast <struc::CompilationUnit*>( createNode(ndkCompilationUnit));
  }

  struc::Enum* Factory::createEnumNode(){
    return  dynamic_cast <struc::Enum*>( createNode(ndkEnum));
  }

  struc::EnumConstant* Factory::createEnumConstantNode(){
    return  dynamic_cast <struc::EnumConstant*>( createNode(ndkEnumConstant));
  }

  struc::Import* Factory::createImportNode(){
    return  dynamic_cast <struc::Import*>( createNode(ndkImport));
  }

  struc::InstanceInitializerBlock* Factory::createInstanceInitializerBlockNode(){
    return  dynamic_cast <struc::InstanceInitializerBlock*>( createNode(ndkInstanceInitializerBlock));
  }

  struc::Interface* Factory::createInterfaceNode(){
    return  dynamic_cast <struc::Interface*>( createNode(ndkInterface));
  }

  struc::InterfaceGeneric* Factory::createInterfaceGenericNode(){
    return  dynamic_cast <struc::InterfaceGeneric*>( createNode(ndkInterfaceGeneric));
  }

  struc::Method* Factory::createMethodNode(){
    return  dynamic_cast <struc::Method*>( createNode(ndkMethod));
  }

  struc::MethodGeneric* Factory::createMethodGenericNode(){
    return  dynamic_cast <struc::MethodGeneric*>( createNode(ndkMethodGeneric));
  }

  struc::Module* Factory::createModuleNode(){
    return  dynamic_cast <struc::Module*>( createNode(ndkModule));
  }

  struc::ModuleDeclaration* Factory::createModuleDeclarationNode(){
    return  dynamic_cast <struc::ModuleDeclaration*>( createNode(ndkModuleDeclaration));
  }

  struc::Package* Factory::createPackageNode(){
    return  dynamic_cast <struc::Package*>( createNode(ndkPackage));
  }

  struc::PackageDeclaration* Factory::createPackageDeclarationNode(){
    return  dynamic_cast <struc::PackageDeclaration*>( createNode(ndkPackageDeclaration));
  }

  struc::Parameter* Factory::createParameterNode(){
    return  dynamic_cast <struc::Parameter*>( createNode(ndkParameter));
  }

  struc::StaticInitializerBlock* Factory::createStaticInitializerBlockNode(){
    return  dynamic_cast <struc::StaticInitializerBlock*>( createNode(ndkStaticInitializerBlock));
  }

  struc::TypeParameter* Factory::createTypeParameterNode(){
    return  dynamic_cast <struc::TypeParameter*>( createNode(ndkTypeParameter));
  }

  struc::Variable* Factory::createVariableNode(){
    return  dynamic_cast <struc::Variable*>( createNode(ndkVariable));
  }

  type::IntersectionType* Factory::createIntersectionTypeNode(){
    return  dynamic_cast <type::IntersectionType*>( createNode(ndkIntersectionType));
  }

  type::ModuleType* Factory::createModuleTypeNode(){
    return  dynamic_cast <type::ModuleType*>( createNode(ndkModuleType));
  }

  void Factory::printNodeSizes() {
    printf("base::BlockComment node: %dbyte(s)\n",(int)sizeof(base::BlockComment)); 
    printf("base::JavadocComment node: %dbyte(s)\n",(int)sizeof(base::JavadocComment)); 
    printf("base::LineComment node: %dbyte(s)\n",(int)sizeof(base::LineComment)); 
    printf("expr::AnnotatedTypeExpression node: %dbyte(s)\n",(int)sizeof(expr::AnnotatedTypeExpression)); 
    printf("expr::ArrayAccess node: %dbyte(s)\n",(int)sizeof(expr::ArrayAccess)); 
    printf("expr::ArrayTypeExpression node: %dbyte(s)\n",(int)sizeof(expr::ArrayTypeExpression)); 
    printf("expr::Assignment node: %dbyte(s)\n",(int)sizeof(expr::Assignment)); 
    printf("expr::BooleanLiteral node: %dbyte(s)\n",(int)sizeof(expr::BooleanLiteral)); 
    printf("expr::CharacterLiteral node: %dbyte(s)\n",(int)sizeof(expr::CharacterLiteral)); 
    printf("expr::ClassLiteral node: %dbyte(s)\n",(int)sizeof(expr::ClassLiteral)); 
    printf("expr::Conditional node: %dbyte(s)\n",(int)sizeof(expr::Conditional)); 
    printf("expr::DoubleLiteral node: %dbyte(s)\n",(int)sizeof(expr::DoubleLiteral)); 
    printf("expr::Erroneous node: %dbyte(s)\n",(int)sizeof(expr::Erroneous)); 
    printf("expr::ErroneousTypeExpression node: %dbyte(s)\n",(int)sizeof(expr::ErroneousTypeExpression)); 
    printf("expr::ExternalTypeExpression node: %dbyte(s)\n",(int)sizeof(expr::ExternalTypeExpression)); 
    printf("expr::FieldAccess node: %dbyte(s)\n",(int)sizeof(expr::FieldAccess)); 
    printf("expr::FloatLiteral node: %dbyte(s)\n",(int)sizeof(expr::FloatLiteral)); 
    printf("expr::Identifier node: %dbyte(s)\n",(int)sizeof(expr::Identifier)); 
    printf("expr::InfixExpression node: %dbyte(s)\n",(int)sizeof(expr::InfixExpression)); 
    printf("expr::InstanceOf node: %dbyte(s)\n",(int)sizeof(expr::InstanceOf)); 
    printf("expr::IntegerLiteral node: %dbyte(s)\n",(int)sizeof(expr::IntegerLiteral)); 
    printf("expr::Lambda node: %dbyte(s)\n",(int)sizeof(expr::Lambda)); 
    printf("expr::LongLiteral node: %dbyte(s)\n",(int)sizeof(expr::LongLiteral)); 
    printf("expr::MarkerAnnotation node: %dbyte(s)\n",(int)sizeof(expr::MarkerAnnotation)); 
    printf("expr::MemberReference node: %dbyte(s)\n",(int)sizeof(expr::MemberReference)); 
    printf("expr::MethodInvocation node: %dbyte(s)\n",(int)sizeof(expr::MethodInvocation)); 
    printf("expr::NewArray node: %dbyte(s)\n",(int)sizeof(expr::NewArray)); 
    printf("expr::NewClass node: %dbyte(s)\n",(int)sizeof(expr::NewClass)); 
    printf("expr::NormalAnnotation node: %dbyte(s)\n",(int)sizeof(expr::NormalAnnotation)); 
    printf("expr::NullLiteral node: %dbyte(s)\n",(int)sizeof(expr::NullLiteral)); 
    printf("expr::ParenthesizedExpression node: %dbyte(s)\n",(int)sizeof(expr::ParenthesizedExpression)); 
    printf("expr::PostfixExpression node: %dbyte(s)\n",(int)sizeof(expr::PostfixExpression)); 
    printf("expr::PrefixExpression node: %dbyte(s)\n",(int)sizeof(expr::PrefixExpression)); 
    printf("expr::PrimitiveTypeExpression node: %dbyte(s)\n",(int)sizeof(expr::PrimitiveTypeExpression)); 
    printf("expr::QualifiedTypeExpression node: %dbyte(s)\n",(int)sizeof(expr::QualifiedTypeExpression)); 
    printf("expr::SimpleTypeExpression node: %dbyte(s)\n",(int)sizeof(expr::SimpleTypeExpression)); 
    printf("expr::SingleElementAnnotation node: %dbyte(s)\n",(int)sizeof(expr::SingleElementAnnotation)); 
    printf("expr::StringLiteral node: %dbyte(s)\n",(int)sizeof(expr::StringLiteral)); 
    printf("expr::Super node: %dbyte(s)\n",(int)sizeof(expr::Super)); 
    printf("expr::This node: %dbyte(s)\n",(int)sizeof(expr::This)); 
    printf("expr::TypeApplyExpression node: %dbyte(s)\n",(int)sizeof(expr::TypeApplyExpression)); 
    printf("expr::TypeCast node: %dbyte(s)\n",(int)sizeof(expr::TypeCast)); 
    printf("expr::TypeIntersectionExpression node: %dbyte(s)\n",(int)sizeof(expr::TypeIntersectionExpression)); 
    printf("expr::TypeUnionExpression node: %dbyte(s)\n",(int)sizeof(expr::TypeUnionExpression)); 
    printf("expr::WildcardExpression node: %dbyte(s)\n",(int)sizeof(expr::WildcardExpression)); 
    printf("module::Exports node: %dbyte(s)\n",(int)sizeof(module::Exports)); 
    printf("module::Opens node: %dbyte(s)\n",(int)sizeof(module::Opens)); 
    printf("module::Provides node: %dbyte(s)\n",(int)sizeof(module::Provides)); 
    printf("module::Requires node: %dbyte(s)\n",(int)sizeof(module::Requires)); 
    printf("module::Uses node: %dbyte(s)\n",(int)sizeof(module::Uses)); 
    printf("statm::Assert node: %dbyte(s)\n",(int)sizeof(statm::Assert)); 
    printf("statm::BasicFor node: %dbyte(s)\n",(int)sizeof(statm::BasicFor)); 
    printf("statm::Block node: %dbyte(s)\n",(int)sizeof(statm::Block)); 
    printf("statm::Break node: %dbyte(s)\n",(int)sizeof(statm::Break)); 
    printf("statm::Case node: %dbyte(s)\n",(int)sizeof(statm::Case)); 
    printf("statm::Continue node: %dbyte(s)\n",(int)sizeof(statm::Continue)); 
    printf("statm::Default node: %dbyte(s)\n",(int)sizeof(statm::Default)); 
    printf("statm::Do node: %dbyte(s)\n",(int)sizeof(statm::Do)); 
    printf("statm::Empty node: %dbyte(s)\n",(int)sizeof(statm::Empty)); 
    printf("statm::EnhancedFor node: %dbyte(s)\n",(int)sizeof(statm::EnhancedFor)); 
    printf("statm::ExpressionStatement node: %dbyte(s)\n",(int)sizeof(statm::ExpressionStatement)); 
    printf("statm::Handler node: %dbyte(s)\n",(int)sizeof(statm::Handler)); 
    printf("statm::If node: %dbyte(s)\n",(int)sizeof(statm::If)); 
    printf("statm::LabeledStatement node: %dbyte(s)\n",(int)sizeof(statm::LabeledStatement)); 
    printf("statm::Return node: %dbyte(s)\n",(int)sizeof(statm::Return)); 
    printf("statm::Switch node: %dbyte(s)\n",(int)sizeof(statm::Switch)); 
    printf("statm::Synchronized node: %dbyte(s)\n",(int)sizeof(statm::Synchronized)); 
    printf("statm::Throw node: %dbyte(s)\n",(int)sizeof(statm::Throw)); 
    printf("statm::Try node: %dbyte(s)\n",(int)sizeof(statm::Try)); 
    printf("statm::While node: %dbyte(s)\n",(int)sizeof(statm::While)); 
    printf("struc::AnnotationType node: %dbyte(s)\n",(int)sizeof(struc::AnnotationType)); 
    printf("struc::AnnotationTypeElement node: %dbyte(s)\n",(int)sizeof(struc::AnnotationTypeElement)); 
    printf("struc::AnonymousClass node: %dbyte(s)\n",(int)sizeof(struc::AnonymousClass)); 
    printf("struc::Class node: %dbyte(s)\n",(int)sizeof(struc::Class)); 
    printf("struc::ClassGeneric node: %dbyte(s)\n",(int)sizeof(struc::ClassGeneric)); 
    printf("struc::CompilationUnit node: %dbyte(s)\n",(int)sizeof(struc::CompilationUnit)); 
    printf("struc::Enum node: %dbyte(s)\n",(int)sizeof(struc::Enum)); 
    printf("struc::EnumConstant node: %dbyte(s)\n",(int)sizeof(struc::EnumConstant)); 
    printf("struc::Import node: %dbyte(s)\n",(int)sizeof(struc::Import)); 
    printf("struc::InstanceInitializerBlock node: %dbyte(s)\n",(int)sizeof(struc::InstanceInitializerBlock)); 
    printf("struc::Interface node: %dbyte(s)\n",(int)sizeof(struc::Interface)); 
    printf("struc::InterfaceGeneric node: %dbyte(s)\n",(int)sizeof(struc::InterfaceGeneric)); 
    printf("struc::Method node: %dbyte(s)\n",(int)sizeof(struc::Method)); 
    printf("struc::MethodGeneric node: %dbyte(s)\n",(int)sizeof(struc::MethodGeneric)); 
    printf("struc::Module node: %dbyte(s)\n",(int)sizeof(struc::Module)); 
    printf("struc::ModuleDeclaration node: %dbyte(s)\n",(int)sizeof(struc::ModuleDeclaration)); 
    printf("struc::Package node: %dbyte(s)\n",(int)sizeof(struc::Package)); 
    printf("struc::PackageDeclaration node: %dbyte(s)\n",(int)sizeof(struc::PackageDeclaration)); 
    printf("struc::Parameter node: %dbyte(s)\n",(int)sizeof(struc::Parameter)); 
    printf("struc::StaticInitializerBlock node: %dbyte(s)\n",(int)sizeof(struc::StaticInitializerBlock)); 
    printf("struc::TypeParameter node: %dbyte(s)\n",(int)sizeof(struc::TypeParameter)); 
    printf("struc::Variable node: %dbyte(s)\n",(int)sizeof(struc::Variable)); 
    printf("type::ArrayType node: %dbyte(s)\n",(int)sizeof(type::ArrayType)); 
    printf("type::BooleanType node: %dbyte(s)\n",(int)sizeof(type::BooleanType)); 
    printf("type::ByteType node: %dbyte(s)\n",(int)sizeof(type::ByteType)); 
    printf("type::CharType node: %dbyte(s)\n",(int)sizeof(type::CharType)); 
    printf("type::ClassType node: %dbyte(s)\n",(int)sizeof(type::ClassType)); 
    printf("type::DoubleType node: %dbyte(s)\n",(int)sizeof(type::DoubleType)); 
    printf("type::ErrorType node: %dbyte(s)\n",(int)sizeof(type::ErrorType)); 
    printf("type::FloatType node: %dbyte(s)\n",(int)sizeof(type::FloatType)); 
    printf("type::IntType node: %dbyte(s)\n",(int)sizeof(type::IntType)); 
    printf("type::IntersectionType node: %dbyte(s)\n",(int)sizeof(type::IntersectionType)); 
    printf("type::LongType node: %dbyte(s)\n",(int)sizeof(type::LongType)); 
    printf("type::LowerBoundedWildcardType node: %dbyte(s)\n",(int)sizeof(type::LowerBoundedWildcardType)); 
    printf("type::MethodType node: %dbyte(s)\n",(int)sizeof(type::MethodType)); 
    printf("type::ModuleType node: %dbyte(s)\n",(int)sizeof(type::ModuleType)); 
    printf("type::NoType node: %dbyte(s)\n",(int)sizeof(type::NoType)); 
    printf("type::NullType node: %dbyte(s)\n",(int)sizeof(type::NullType)); 
    printf("type::PackageType node: %dbyte(s)\n",(int)sizeof(type::PackageType)); 
    printf("type::ParameterizedType node: %dbyte(s)\n",(int)sizeof(type::ParameterizedType)); 
    printf("type::ShortType node: %dbyte(s)\n",(int)sizeof(type::ShortType)); 
    printf("type::TypeVariable node: %dbyte(s)\n",(int)sizeof(type::TypeVariable)); 
    printf("type::UnboundedWildcardType node: %dbyte(s)\n",(int)sizeof(type::UnboundedWildcardType)); 
    printf("type::UnionType node: %dbyte(s)\n",(int)sizeof(type::UnionType)); 
    printf("type::UpperBoundedWildcardType node: %dbyte(s)\n",(int)sizeof(type::UpperBoundedWildcardType)); 
    printf("type::VoidType node: %dbyte(s)\n",(int)sizeof(type::VoidType)); 
  }

base::Base* Factory::replaceNode(base::Base &node) {
  NodeId id = node.getId();
  base::Base* p = NULL;

  if (node.getNodeKind() == ndkClass) {
    p = new struc::ClassGeneric(id, this);
    dynamic_cast<struc::ClassDeclaration*>(p)->clone(dynamic_cast<struc::ClassDeclaration&>(node), true);

  } else if (node.getNodeKind() == ndkInterface) {
    p = new struc::InterfaceGeneric(id, this);
    dynamic_cast<struc::InterfaceDeclaration*>(p)->clone(dynamic_cast<struc::InterfaceDeclaration&>(node), true);

  } else if (node.getNodeKind() == ndkMethod) {
    p = new struc::MethodGeneric(id, this);
    dynamic_cast<struc::NormalMethod*>(p)->clone(dynamic_cast<struc::NormalMethod&>(node), true);

  } else {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_REPLACE_WRONG_NODE(id, node.getNodeKind()));
  }

  delete container[id];
  container[id] = p;

  return p;
}

base::Base* Factory::createSimpleAPSpecNodeSafely(NodeKind ndk, NodeId id) {
  base::Base* node = container[id];
  if (node) {
    if (node->getNodeKind() != ndk) {
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_WRONG_NODE_KIND(id,node->getNodeKind(),ndk));
    }
  } else {
    node = &createNode(ndk, id);
  }
  apspecNodes[ndk] = node;
  return node;
}

void Factory::init() {
  apspecNodes.clear();
  apspecNodes.resize(ndkLAST, NULL);

  NodeId id = 10;

  createSimpleAPSpecNodeSafely(ndkVoidType, id++);
  createSimpleAPSpecNodeSafely(ndkBooleanType, id++);
  createSimpleAPSpecNodeSafely(ndkCharType, id++);
  createSimpleAPSpecNodeSafely(ndkByteType, id++);
  createSimpleAPSpecNodeSafely(ndkShortType, id++);
  createSimpleAPSpecNodeSafely(ndkIntType, id++);
  createSimpleAPSpecNodeSafely(ndkLongType, id++);
  createSimpleAPSpecNodeSafely(ndkFloatType, id++);
  createSimpleAPSpecNodeSafely(ndkDoubleType, id++);

  createSimpleAPSpecNodeSafely(ndkNullType, id++);
  createSimpleAPSpecNodeSafely(ndkNoType, id++);
  createSimpleAPSpecNodeSafely(ndkErrorType, id++);
}

base::Base* Factory::getAPSpecNode(NodeKind ndk) {
  base::Base* node = apspecNodes[ndk];
  if (!node) {
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND_VALUE(ndk));
  }
  return node;
}


}}}
