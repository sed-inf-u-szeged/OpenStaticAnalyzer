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

#include "javascript/inc/javascript.h"

#include <string.h>
#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "common/inc/StringSup.h"
#include "common/inc/WriteMessage.h"

#include "io/inc/ZippedIO.h"

#include "javascript/inc/messages.h"

namespace columbus { namespace javascript { namespace asg {
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
  root = dynamic_cast<base::System*>(&createNode(ndkSystem, 100));
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

void Factory::save(const std::string &filename, std::list<HeaderData*> &headerDataList, std::streampos& startPos, bool zip) const {
  io::ZippedIO zipIo(filename.c_str(), io::IOBase::omWrite, false);
  zipIo.setStartWritePosition(startPos);
  save(zipIo, headerDataList, zip);
}

void Factory::save(const std::string &filename, std::list<HeaderData*> &headerDataList, bool zip) const {
  io::ZippedIO zipIo(filename.c_str(), io::IOBase::omWrite, false);
  save(zipIo, headerDataList, zip);
}

void Factory::save(io::ZippedIO& zipIo, std::list<HeaderData*> &headerDataList, bool zip) const {
  TurnFilterOffSafely t(*this);
  zipIo.setEndianState(io::BinaryIO::etLittle);
  // storage the headerData Full size 
  if (zip) {
    zipIo.writeString("zsi");
  } else {
    zipIo.writeString("csi");
  }
  bool isContainPropertyData = false;
  for (  std::list<HeaderData*>::iterator it = headerDataList.begin(); it != headerDataList.end(); it++ ) {
    if ((*it)->getType() == hdkPropertyData){
      if (it != headerDataList.begin()) {
        headerDataList.insert(headerDataList.begin(), *it);
        headerDataList.erase(++it);
      }
      isContainPropertyData = true;
      break;
    }
  }
  bool hasUnkownPropertyData = false;
  for (std::vector<std::pair<unsigned short, std::vector< unsigned char > > >::const_iterator unknownDataIt = unknownHeaderData.begin(); unknownDataIt != unknownHeaderData.end(); ++unknownDataIt) {
    for (  std::list<HeaderData*>::iterator givenDataIt = headerDataList.begin(); givenDataIt != headerDataList.end(); givenDataIt++ )
      if ((*givenDataIt)->getType() == unknownDataIt->first)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_HEADER_DATA_ALREADY_LOADED(unknownDataIt->first));
    if (unknownDataIt->first == hdkPropertyData) {
      hasUnkownPropertyData = true;
      break;
    }
  }
  if (!isContainPropertyData && !hasUnkownPropertyData) {
    zipIo.writeInt4(headerDataList.size() + unknownHeaderData.size() + 1);
    PropertyData propertyData;
    propertyData.add(PropertyData::csih_Type, "JavaScriptLanguage");
    propertyData.add(PropertyData::csih_APIVersion, APIVersion);
    propertyData.add(PropertyData::csih_BinaryVersion, BinaryVersion);
    zipIo.writeUShort2(propertyData.getType());
    zipIo.writeStartSizeOfBlock();
    propertyData.save(zipIo);
    zipIo.writeEndSizeOfBlock();
  }
  else {
    zipIo.writeInt4(headerDataList.size() + unknownHeaderData.size());
  }
  for (  std::list<HeaderData*>::iterator it = headerDataList.begin(); it != headerDataList.end(); it++ ) {
    if ((*it)->getType() == hdkPropertyData){
      PropertyData& propertyData = dynamic_cast<PropertyData&>(*(*it));
      propertyData.add(PropertyData::csih_Type, "JavaScriptLanguage");
      propertyData.add(PropertyData::csih_APIVersion, APIVersion);
      propertyData.add(PropertyData::csih_BinaryVersion, BinaryVersion);
    }
    zipIo.writeUShort2((*it)->getType());
    zipIo.writeStartSizeOfBlock();
    (*it)->save(zipIo);
    zipIo.writeEndSizeOfBlock();
  }

  for (std::vector<std::pair<unsigned short, std::vector< unsigned char > > >::const_iterator it = unknownHeaderData.begin(); it != unknownHeaderData.end(); ++it) {
    zipIo.writeUShort2(it->first);
    zipIo.writeLongLong8(it->second.size() + 8);
    zipIo.writeData(it->second.data(), it->second.size());
  }

  if (zip)
    zipIo.setZip(true);
  // saving the ASG
  AlgorithmPreorder algPre;
  algPre.setSafeMode();
  VisitorSave vSave(zipIo);
  algPre.run(*this, vSave);
  // Writing the ENDMARK!
  zipIo.writeUInt4(0); // NodeId
  zipIo.writeUShort2(0); // NodeKind
  strTable->save(zipIo);
  zipIo.close();
}

void Factory::loadHeader(const std::string &filename, const std::list<HeaderData*> &headerDataList) {
  io::BinaryIO binIo(filename.c_str(), io::IOBase::omRead);
  clear();
  char tag[4];
  binIo.readData (tag,4);
  if (strcmp(tag,"csi") && strcmp(tag,"zsi"))
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
  loadHeader(binIo, headerDataList);
  binIo.close();
}
void Factory::loadHeader(io::BinaryIO &binIo, const std::list<HeaderData*> &headerDataList) {
  int CsiHeaderSize = binIo.readInt4();
  for ( int i = 0;i < CsiHeaderSize ;i++) {
    HeaderDataTypeKind type = (HeaderDataTypeKind)binIo.readUShort2();
    std::list<HeaderData*>::const_iterator listIt = headerDataList.begin();
    bool handled = false;
    while (listIt != headerDataList.end()) {
      if (type == ((*listIt)->getType())) {
        handled = true;
        binIo.readLongLong8();  /// read block size, but never use another place after load, so doesnt need to assign it with a variable 
        (*listIt)->load(binIo);
        if (type == hdkPropertyData) {
           checkPropertyData (dynamic_cast<PropertyData&>(*(*listIt))); 
        }
        break;
      }
      listIt++;
    }

    if (!handled) {
      unknownHeaderData.push_back(std::make_pair(type, std::vector<unsigned char>()));
      std::streamsize size = binIo.readLongLong8();
      std::vector<unsigned char>& container = unknownHeaderData.back().second;
      container.resize(size - 8);
      binIo.readData(container.data(), size - 8);
      if (type == hdkPropertyData){
        PropertyData propertyData;
        std::stringbuf sbuff;
        io::BinaryIO tempIO;
        tempIO.open(&sbuff);
        tempIO.writeData(container.data(), container.size());
        propertyData.load(tempIO);
        checkPropertyData (propertyData);
      }
    }
  }
}

void Factory::checkPropertyData( PropertyData& propertyData) {
  // Checking the type
  std::string type;
  if (!propertyData.get(PropertyData::csih_Type, type))
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
  if (type != "JavaScriptLanguage")
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_WRONG_FILE_TYPE_INFORMATION);
  // Checking API version
  std::string apiVersion;
  if (!propertyData.get(PropertyData::csih_APIVersion, apiVersion))
    throw JavascriptException(COLUMBUS_LOCATION,CMSG_EX_MISSING_API_VERSION_INFORMATION );
  if (apiVersion != APIVersion)
       throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_WRONG_API_VERSION(APIVersion,apiVersion));
  // Checking binary version
  std::string binVersion;
  if (!propertyData.get(PropertyData::csih_BinaryVersion, binVersion))
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_MISSING_BINARY_VERSION_INFORMATION);
  if (binVersion != BinaryVersion)
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_WRONG_BINARY_VERSION(BinaryVersion,binVersion));
  }

void Factory::load( io::ZippedIO &zipIo, const std::list<HeaderData*> &headerDataList)
{
  bool zip = false;
  clear();
  char tag[4];
  zipIo.readData (tag,4);
  if ( strcmp(tag,"csi") && strcmp(tag,"zsi") ) {
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
  } else if (strcmp(tag,"zsi") == 0) {
    zip = true;
  }
  loadHeader(zipIo, headerDataList);
  if (zip)
    zipIo.setZip(true);
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
  zipIo.close();
  root = dynamic_cast<base::System*>(container[100]);
  // fill the deletedNodeIdList with the free ids
  for (size_t id = 100; id < container.size(); ++id)
    if (container[id] == NULL)
      deletedNodeIdList.push_back(id);

}
void Factory::load(const std::string &filename, std::list<HeaderData*> &headerDataList) {
  io::ZippedIO zipIo(filename.c_str(), io::IOBase::omRead, false);
  load(zipIo, headerDataList);
}

void Factory::load( const std::string &filename , std::list<HeaderData*> &headerDataList, std::streampos& startPosition) {
  io::ZippedIO zipIo(filename.c_str(), io::IOBase::omRead, false);
  zipIo.setStartReadPosition(startPosition);
  load( zipIo, headerDataList);
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

base::System* Factory::getRoot() const {
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
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  return *p;
}

base::Base* Factory::getPointer(NodeId id) const {
  base::Base* p = NULL;
  try {
    p = container.at(id);
  } catch (const std::out_of_range&) {
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  }
  return p;
}

RefDistributorStrTable& Factory::getStringTable() const {
  return *strTable;
}

void Factory::destroyNode(NodeId id) {
  if (!reverseEdges)
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (!getExist(id))
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

  std::list<NodeId> nodesToDelete;
  VisitorSubtreeCollector visitor(nodesToDelete);
  AlgorithmPreorder ap;
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
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (id >= container.size())
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_NEXT_ELEMENT_DOES_NOT_EXIST);
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
    throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_LOADED_FILTER_DOES_NOT_MATCH_TO_THE_CURRENT);

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
    ap.run(*this, vas);
    unsigned long totalMemUsage = 0; /* it is the sum of memory of nodes */
    common::WriteMsg::write(common::WriteMsg::mlNormal, "Nodes,All,This,Obj Size,Used Mem,Used Mem\n");
    for (int i = 0; i < 86; ++i) {
      totalMemUsage += vas.nodeStatSimple[i] * vas.nodeSizes[i];
      common::WriteMsg::write(common::WriteMsg::mlNormal, "%s,%d,%d,%d,%d,%d\n", vas.nodeNames[i], vas.nodeStatParent[i], vas.nodeStatSimple[i], vas.nodeSizes[i], vas.nodeStatSimple[i] * vas.nodeSizes[i], vas.nodeStatSimple[i] * vas.nodeSizes[i] / 1024);
    }    common::WriteMsg::write(common::WriteMsg::mlNormal, "\n");
    common::WriteMsg::write(common::WriteMsg::mlNormal, "Memory used by nodes: %d (%d KB)\n\n", totalMemUsage, totalMemUsage );
    if (edgeStat) {
      common::WriteMsg::write(common::WriteMsg::mlNormal, "Edges,Cardinality\n");
      for (int i = 0; i < 95; ++i)
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
    case ndkComment: p = new base::Comment(id, this); break;
    case ndkProgram: p = new base::Program(id, this); break;
    case ndkSystem: p = new base::System(id, this); break;
    case ndkClassDeclaration: p = new declaration::ClassDeclaration(id, this); break;
    case ndkExportAllDeclaration: p = new declaration::ExportAllDeclaration(id, this); break;
    case ndkExportDefaultDeclaration: p = new declaration::ExportDefaultDeclaration(id, this); break;
    case ndkExportNamedDeclaration: p = new declaration::ExportNamedDeclaration(id, this); break;
    case ndkFunctionDeclaration: p = new declaration::FunctionDeclaration(id, this); break;
    case ndkImportDeclaration: p = new declaration::ImportDeclaration(id, this); break;
    case ndkModuleDeclaration: p = new declaration::ModuleDeclaration(id, this); break;
    case ndkVariableDeclaration: p = new declaration::VariableDeclaration(id, this); break;
    case ndkVariableDeclarator: p = new declaration::VariableDeclarator(id, this); break;
    case ndkArrayExpression: p = new expression::ArrayExpression(id, this); break;
    case ndkArrowFunctionExpression: p = new expression::ArrowFunctionExpression(id, this); break;
    case ndkAssignmentExpression: p = new expression::AssignmentExpression(id, this); break;
    case ndkAssignmentProperty: p = new expression::AssignmentProperty(id, this); break;
    case ndkAwaitExpression: p = new expression::AwaitExpression(id, this); break;
    case ndkBinaryExpression: p = new expression::BinaryExpression(id, this); break;
    case ndkBooleanLiteral: p = new expression::BooleanLiteral(id, this); break;
    case ndkCallExpression: p = new expression::CallExpression(id, this); break;
    case ndkClassExpression: p = new expression::ClassExpression(id, this); break;
    case ndkConditionalExpression: p = new expression::ConditionalExpression(id, this); break;
    case ndkFunctionExpression: p = new expression::FunctionExpression(id, this); break;
    case ndkIdentifier: p = new expression::Identifier(id, this); break;
    case ndkLogicalExpression: p = new expression::LogicalExpression(id, this); break;
    case ndkMemberExpression: p = new expression::MemberExpression(id, this); break;
    case ndkMetaProperty: p = new expression::MetaProperty(id, this); break;
    case ndkNewExpression: p = new expression::NewExpression(id, this); break;
    case ndkNullLiteral: p = new expression::NullLiteral(id, this); break;
    case ndkNumberLiteral: p = new expression::NumberLiteral(id, this); break;
    case ndkObjectExpression: p = new expression::ObjectExpression(id, this); break;
    case ndkProperty: p = new expression::Property(id, this); break;
    case ndkRegExpLiteral: p = new expression::RegExpLiteral(id, this); break;
    case ndkSequenceExpression: p = new expression::SequenceExpression(id, this); break;
    case ndkSpreadElement: p = new expression::SpreadElement(id, this); break;
    case ndkStringLiteral: p = new expression::StringLiteral(id, this); break;
    case ndkSuper: p = new expression::Super(id, this); break;
    case ndkTaggedTemplateExpression: p = new expression::TaggedTemplateExpression(id, this); break;
    case ndkTemplateElement: p = new expression::TemplateElement(id, this); break;
    case ndkTemplateLiteral: p = new expression::TemplateLiteral(id, this); break;
    case ndkThisExpression: p = new expression::ThisExpression(id, this); break;
    case ndkUnaryExpression: p = new expression::UnaryExpression(id, this); break;
    case ndkUpdateExpression: p = new expression::UpdateExpression(id, this); break;
    case ndkYieldExpression: p = new expression::YieldExpression(id, this); break;
    case ndkArrayPattern: p = new statement::ArrayPattern(id, this); break;
    case ndkAssignmentPattern: p = new statement::AssignmentPattern(id, this); break;
    case ndkBlockStatement: p = new statement::BlockStatement(id, this); break;
    case ndkBreakStatement: p = new statement::BreakStatement(id, this); break;
    case ndkCatchClause: p = new statement::CatchClause(id, this); break;
    case ndkContinueStatement: p = new statement::ContinueStatement(id, this); break;
    case ndkDebuggerStatement: p = new statement::DebuggerStatement(id, this); break;
    case ndkDoWhileStatement: p = new statement::DoWhileStatement(id, this); break;
    case ndkEmptyStatement: p = new statement::EmptyStatement(id, this); break;
    case ndkExpressionStatement: p = new statement::ExpressionStatement(id, this); break;
    case ndkForInStatement: p = new statement::ForInStatement(id, this); break;
    case ndkForOfStatement: p = new statement::ForOfStatement(id, this); break;
    case ndkForStatement: p = new statement::ForStatement(id, this); break;
    case ndkFunction: p = new statement::Function(id, this); break;
    case ndkIfStatement: p = new statement::IfStatement(id, this); break;
    case ndkLabeledStatement: p = new statement::LabeledStatement(id, this); break;
    case ndkObjectPattern: p = new statement::ObjectPattern(id, this); break;
    case ndkRestElement: p = new statement::RestElement(id, this); break;
    case ndkReturnStatement: p = new statement::ReturnStatement(id, this); break;
    case ndkSwitchCase: p = new statement::SwitchCase(id, this); break;
    case ndkSwitchStatement: p = new statement::SwitchStatement(id, this); break;
    case ndkThrowStatement: p = new statement::ThrowStatement(id, this); break;
    case ndkTryStatement: p = new statement::TryStatement(id, this); break;
    case ndkWhileStatement: p = new statement::WhileStatement(id, this); break;
    case ndkWithStatement: p = new statement::WithStatement(id, this); break;
    case ndkClassBody: p = new structure::ClassBody(id, this); break;
    case ndkExportSpecifier: p = new structure::ExportSpecifier(id, this); break;
    case ndkImportDefaultSpecifier: p = new structure::ImportDefaultSpecifier(id, this); break;
    case ndkImportNamespaceSpecifier: p = new structure::ImportNamespaceSpecifier(id, this); break;
    case ndkImportSpecifier: p = new structure::ImportSpecifier(id, this); break;
    case ndkMethodDefinition: p = new structure::MethodDefinition(id, this); break;
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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
    case ndkProgram: p = new base::Program(i,this); break;
    case ndkSystem: p = new base::System(i,this); break;
    case ndkClassDeclaration: p = new declaration::ClassDeclaration(i,this); break;
    case ndkExportAllDeclaration: p = new declaration::ExportAllDeclaration(i,this); break;
    case ndkExportDefaultDeclaration: p = new declaration::ExportDefaultDeclaration(i,this); break;
    case ndkExportNamedDeclaration: p = new declaration::ExportNamedDeclaration(i,this); break;
    case ndkFunctionDeclaration: p = new declaration::FunctionDeclaration(i,this); break;
    case ndkImportDeclaration: p = new declaration::ImportDeclaration(i,this); break;
    case ndkModuleDeclaration: p = new declaration::ModuleDeclaration(i,this); break;
    case ndkVariableDeclaration: p = new declaration::VariableDeclaration(i,this); break;
    case ndkVariableDeclarator: p = new declaration::VariableDeclarator(i,this); break;
    case ndkArrayExpression: p = new expression::ArrayExpression(i,this); break;
    case ndkArrowFunctionExpression: p = new expression::ArrowFunctionExpression(i,this); break;
    case ndkAssignmentExpression: p = new expression::AssignmentExpression(i,this); break;
    case ndkAssignmentProperty: p = new expression::AssignmentProperty(i,this); break;
    case ndkAwaitExpression: p = new expression::AwaitExpression(i,this); break;
    case ndkBinaryExpression: p = new expression::BinaryExpression(i,this); break;
    case ndkBooleanLiteral: p = new expression::BooleanLiteral(i,this); break;
    case ndkCallExpression: p = new expression::CallExpression(i,this); break;
    case ndkClassExpression: p = new expression::ClassExpression(i,this); break;
    case ndkConditionalExpression: p = new expression::ConditionalExpression(i,this); break;
    case ndkFunctionExpression: p = new expression::FunctionExpression(i,this); break;
    case ndkIdentifier: p = new expression::Identifier(i,this); break;
    case ndkLogicalExpression: p = new expression::LogicalExpression(i,this); break;
    case ndkMemberExpression: p = new expression::MemberExpression(i,this); break;
    case ndkMetaProperty: p = new expression::MetaProperty(i,this); break;
    case ndkNewExpression: p = new expression::NewExpression(i,this); break;
    case ndkNullLiteral: p = new expression::NullLiteral(i,this); break;
    case ndkNumberLiteral: p = new expression::NumberLiteral(i,this); break;
    case ndkObjectExpression: p = new expression::ObjectExpression(i,this); break;
    case ndkProperty: p = new expression::Property(i,this); break;
    case ndkRegExpLiteral: p = new expression::RegExpLiteral(i,this); break;
    case ndkSequenceExpression: p = new expression::SequenceExpression(i,this); break;
    case ndkSpreadElement: p = new expression::SpreadElement(i,this); break;
    case ndkStringLiteral: p = new expression::StringLiteral(i,this); break;
    case ndkSuper: p = new expression::Super(i,this); break;
    case ndkTaggedTemplateExpression: p = new expression::TaggedTemplateExpression(i,this); break;
    case ndkTemplateElement: p = new expression::TemplateElement(i,this); break;
    case ndkTemplateLiteral: p = new expression::TemplateLiteral(i,this); break;
    case ndkThisExpression: p = new expression::ThisExpression(i,this); break;
    case ndkUnaryExpression: p = new expression::UnaryExpression(i,this); break;
    case ndkUpdateExpression: p = new expression::UpdateExpression(i,this); break;
    case ndkYieldExpression: p = new expression::YieldExpression(i,this); break;
    case ndkArrayPattern: p = new statement::ArrayPattern(i,this); break;
    case ndkAssignmentPattern: p = new statement::AssignmentPattern(i,this); break;
    case ndkBlockStatement: p = new statement::BlockStatement(i,this); break;
    case ndkBreakStatement: p = new statement::BreakStatement(i,this); break;
    case ndkCatchClause: p = new statement::CatchClause(i,this); break;
    case ndkContinueStatement: p = new statement::ContinueStatement(i,this); break;
    case ndkDebuggerStatement: p = new statement::DebuggerStatement(i,this); break;
    case ndkDoWhileStatement: p = new statement::DoWhileStatement(i,this); break;
    case ndkEmptyStatement: p = new statement::EmptyStatement(i,this); break;
    case ndkExpressionStatement: p = new statement::ExpressionStatement(i,this); break;
    case ndkForInStatement: p = new statement::ForInStatement(i,this); break;
    case ndkForOfStatement: p = new statement::ForOfStatement(i,this); break;
    case ndkForStatement: p = new statement::ForStatement(i,this); break;
    case ndkFunction: p = new statement::Function(i,this); break;
    case ndkIfStatement: p = new statement::IfStatement(i,this); break;
    case ndkLabeledStatement: p = new statement::LabeledStatement(i,this); break;
    case ndkObjectPattern: p = new statement::ObjectPattern(i,this); break;
    case ndkRestElement: p = new statement::RestElement(i,this); break;
    case ndkReturnStatement: p = new statement::ReturnStatement(i,this); break;
    case ndkSwitchCase: p = new statement::SwitchCase(i,this); break;
    case ndkSwitchStatement: p = new statement::SwitchStatement(i,this); break;
    case ndkThrowStatement: p = new statement::ThrowStatement(i,this); break;
    case ndkTryStatement: p = new statement::TryStatement(i,this); break;
    case ndkWhileStatement: p = new statement::WhileStatement(i,this); break;
    case ndkWithStatement: p = new statement::WithStatement(i,this); break;
    case ndkClassBody: p = new structure::ClassBody(i,this); break;
    case ndkExportSpecifier: p = new structure::ExportSpecifier(i,this); break;
    case ndkImportDefaultSpecifier: p = new structure::ImportDefaultSpecifier(i,this); break;
    case ndkImportNamespaceSpecifier: p = new structure::ImportNamespaceSpecifier(i,this); break;
    case ndkImportSpecifier: p = new structure::ImportSpecifier(i,this); break;
    case ndkMethodDefinition: p = new structure::MethodDefinition(i,this); break;
    default: throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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

  base::Comment* Factory::createCommentNode(){
    return  dynamic_cast <base::Comment*>( createNode(ndkComment));
  }

  base::Program* Factory::createProgramNode(){
    return  dynamic_cast <base::Program*>( createNode(ndkProgram));
  }

  base::System* Factory::createSystemNode(){
    return  dynamic_cast <base::System*>( createNode(ndkSystem));
  }

  declaration::ClassDeclaration* Factory::createClassDeclarationNode(){
    return  dynamic_cast <declaration::ClassDeclaration*>( createNode(ndkClassDeclaration));
  }

  declaration::ExportAllDeclaration* Factory::createExportAllDeclarationNode(){
    return  dynamic_cast <declaration::ExportAllDeclaration*>( createNode(ndkExportAllDeclaration));
  }

  declaration::ExportDefaultDeclaration* Factory::createExportDefaultDeclarationNode(){
    return  dynamic_cast <declaration::ExportDefaultDeclaration*>( createNode(ndkExportDefaultDeclaration));
  }

  declaration::ExportNamedDeclaration* Factory::createExportNamedDeclarationNode(){
    return  dynamic_cast <declaration::ExportNamedDeclaration*>( createNode(ndkExportNamedDeclaration));
  }

  declaration::FunctionDeclaration* Factory::createFunctionDeclarationNode(){
    return  dynamic_cast <declaration::FunctionDeclaration*>( createNode(ndkFunctionDeclaration));
  }

  declaration::ImportDeclaration* Factory::createImportDeclarationNode(){
    return  dynamic_cast <declaration::ImportDeclaration*>( createNode(ndkImportDeclaration));
  }

  declaration::ModuleDeclaration* Factory::createModuleDeclarationNode(){
    return  dynamic_cast <declaration::ModuleDeclaration*>( createNode(ndkModuleDeclaration));
  }

  declaration::VariableDeclaration* Factory::createVariableDeclarationNode(){
    return  dynamic_cast <declaration::VariableDeclaration*>( createNode(ndkVariableDeclaration));
  }

  declaration::VariableDeclarator* Factory::createVariableDeclaratorNode(){
    return  dynamic_cast <declaration::VariableDeclarator*>( createNode(ndkVariableDeclarator));
  }

  expression::ArrayExpression* Factory::createArrayExpressionNode(){
    return  dynamic_cast <expression::ArrayExpression*>( createNode(ndkArrayExpression));
  }

  expression::ArrowFunctionExpression* Factory::createArrowFunctionExpressionNode(){
    return  dynamic_cast <expression::ArrowFunctionExpression*>( createNode(ndkArrowFunctionExpression));
  }

  expression::AssignmentExpression* Factory::createAssignmentExpressionNode(){
    return  dynamic_cast <expression::AssignmentExpression*>( createNode(ndkAssignmentExpression));
  }

  expression::AssignmentProperty* Factory::createAssignmentPropertyNode(){
    return  dynamic_cast <expression::AssignmentProperty*>( createNode(ndkAssignmentProperty));
  }

  expression::AwaitExpression* Factory::createAwaitExpressionNode(){
    return  dynamic_cast <expression::AwaitExpression*>( createNode(ndkAwaitExpression));
  }

  expression::BinaryExpression* Factory::createBinaryExpressionNode(){
    return  dynamic_cast <expression::BinaryExpression*>( createNode(ndkBinaryExpression));
  }

  expression::BooleanLiteral* Factory::createBooleanLiteralNode(){
    return  dynamic_cast <expression::BooleanLiteral*>( createNode(ndkBooleanLiteral));
  }

  expression::CallExpression* Factory::createCallExpressionNode(){
    return  dynamic_cast <expression::CallExpression*>( createNode(ndkCallExpression));
  }

  expression::ClassExpression* Factory::createClassExpressionNode(){
    return  dynamic_cast <expression::ClassExpression*>( createNode(ndkClassExpression));
  }

  expression::ConditionalExpression* Factory::createConditionalExpressionNode(){
    return  dynamic_cast <expression::ConditionalExpression*>( createNode(ndkConditionalExpression));
  }

  expression::FunctionExpression* Factory::createFunctionExpressionNode(){
    return  dynamic_cast <expression::FunctionExpression*>( createNode(ndkFunctionExpression));
  }

  expression::Identifier* Factory::createIdentifierNode(){
    return  dynamic_cast <expression::Identifier*>( createNode(ndkIdentifier));
  }

  expression::LogicalExpression* Factory::createLogicalExpressionNode(){
    return  dynamic_cast <expression::LogicalExpression*>( createNode(ndkLogicalExpression));
  }

  expression::MemberExpression* Factory::createMemberExpressionNode(){
    return  dynamic_cast <expression::MemberExpression*>( createNode(ndkMemberExpression));
  }

  expression::MetaProperty* Factory::createMetaPropertyNode(){
    return  dynamic_cast <expression::MetaProperty*>( createNode(ndkMetaProperty));
  }

  expression::NewExpression* Factory::createNewExpressionNode(){
    return  dynamic_cast <expression::NewExpression*>( createNode(ndkNewExpression));
  }

  expression::NullLiteral* Factory::createNullLiteralNode(){
    return  dynamic_cast <expression::NullLiteral*>( createNode(ndkNullLiteral));
  }

  expression::NumberLiteral* Factory::createNumberLiteralNode(){
    return  dynamic_cast <expression::NumberLiteral*>( createNode(ndkNumberLiteral));
  }

  expression::ObjectExpression* Factory::createObjectExpressionNode(){
    return  dynamic_cast <expression::ObjectExpression*>( createNode(ndkObjectExpression));
  }

  expression::Property* Factory::createPropertyNode(){
    return  dynamic_cast <expression::Property*>( createNode(ndkProperty));
  }

  expression::RegExpLiteral* Factory::createRegExpLiteralNode(){
    return  dynamic_cast <expression::RegExpLiteral*>( createNode(ndkRegExpLiteral));
  }

  expression::SequenceExpression* Factory::createSequenceExpressionNode(){
    return  dynamic_cast <expression::SequenceExpression*>( createNode(ndkSequenceExpression));
  }

  expression::SpreadElement* Factory::createSpreadElementNode(){
    return  dynamic_cast <expression::SpreadElement*>( createNode(ndkSpreadElement));
  }

  expression::StringLiteral* Factory::createStringLiteralNode(){
    return  dynamic_cast <expression::StringLiteral*>( createNode(ndkStringLiteral));
  }

  expression::Super* Factory::createSuperNode(){
    return  dynamic_cast <expression::Super*>( createNode(ndkSuper));
  }

  expression::TaggedTemplateExpression* Factory::createTaggedTemplateExpressionNode(){
    return  dynamic_cast <expression::TaggedTemplateExpression*>( createNode(ndkTaggedTemplateExpression));
  }

  expression::TemplateElement* Factory::createTemplateElementNode(){
    return  dynamic_cast <expression::TemplateElement*>( createNode(ndkTemplateElement));
  }

  expression::TemplateLiteral* Factory::createTemplateLiteralNode(){
    return  dynamic_cast <expression::TemplateLiteral*>( createNode(ndkTemplateLiteral));
  }

  expression::ThisExpression* Factory::createThisExpressionNode(){
    return  dynamic_cast <expression::ThisExpression*>( createNode(ndkThisExpression));
  }

  expression::UnaryExpression* Factory::createUnaryExpressionNode(){
    return  dynamic_cast <expression::UnaryExpression*>( createNode(ndkUnaryExpression));
  }

  expression::UpdateExpression* Factory::createUpdateExpressionNode(){
    return  dynamic_cast <expression::UpdateExpression*>( createNode(ndkUpdateExpression));
  }

  expression::YieldExpression* Factory::createYieldExpressionNode(){
    return  dynamic_cast <expression::YieldExpression*>( createNode(ndkYieldExpression));
  }

  statement::ArrayPattern* Factory::createArrayPatternNode(){
    return  dynamic_cast <statement::ArrayPattern*>( createNode(ndkArrayPattern));
  }

  statement::AssignmentPattern* Factory::createAssignmentPatternNode(){
    return  dynamic_cast <statement::AssignmentPattern*>( createNode(ndkAssignmentPattern));
  }

  statement::BlockStatement* Factory::createBlockStatementNode(){
    return  dynamic_cast <statement::BlockStatement*>( createNode(ndkBlockStatement));
  }

  statement::BreakStatement* Factory::createBreakStatementNode(){
    return  dynamic_cast <statement::BreakStatement*>( createNode(ndkBreakStatement));
  }

  statement::CatchClause* Factory::createCatchClauseNode(){
    return  dynamic_cast <statement::CatchClause*>( createNode(ndkCatchClause));
  }

  statement::ContinueStatement* Factory::createContinueStatementNode(){
    return  dynamic_cast <statement::ContinueStatement*>( createNode(ndkContinueStatement));
  }

  statement::DebuggerStatement* Factory::createDebuggerStatementNode(){
    return  dynamic_cast <statement::DebuggerStatement*>( createNode(ndkDebuggerStatement));
  }

  statement::DoWhileStatement* Factory::createDoWhileStatementNode(){
    return  dynamic_cast <statement::DoWhileStatement*>( createNode(ndkDoWhileStatement));
  }

  statement::EmptyStatement* Factory::createEmptyStatementNode(){
    return  dynamic_cast <statement::EmptyStatement*>( createNode(ndkEmptyStatement));
  }

  statement::ExpressionStatement* Factory::createExpressionStatementNode(){
    return  dynamic_cast <statement::ExpressionStatement*>( createNode(ndkExpressionStatement));
  }

  statement::ForInStatement* Factory::createForInStatementNode(){
    return  dynamic_cast <statement::ForInStatement*>( createNode(ndkForInStatement));
  }

  statement::ForOfStatement* Factory::createForOfStatementNode(){
    return  dynamic_cast <statement::ForOfStatement*>( createNode(ndkForOfStatement));
  }

  statement::ForStatement* Factory::createForStatementNode(){
    return  dynamic_cast <statement::ForStatement*>( createNode(ndkForStatement));
  }

  statement::Function* Factory::createFunctionNode(){
    return  dynamic_cast <statement::Function*>( createNode(ndkFunction));
  }

  statement::IfStatement* Factory::createIfStatementNode(){
    return  dynamic_cast <statement::IfStatement*>( createNode(ndkIfStatement));
  }

  statement::LabeledStatement* Factory::createLabeledStatementNode(){
    return  dynamic_cast <statement::LabeledStatement*>( createNode(ndkLabeledStatement));
  }

  statement::ObjectPattern* Factory::createObjectPatternNode(){
    return  dynamic_cast <statement::ObjectPattern*>( createNode(ndkObjectPattern));
  }

  statement::RestElement* Factory::createRestElementNode(){
    return  dynamic_cast <statement::RestElement*>( createNode(ndkRestElement));
  }

  statement::ReturnStatement* Factory::createReturnStatementNode(){
    return  dynamic_cast <statement::ReturnStatement*>( createNode(ndkReturnStatement));
  }

  statement::SwitchCase* Factory::createSwitchCaseNode(){
    return  dynamic_cast <statement::SwitchCase*>( createNode(ndkSwitchCase));
  }

  statement::SwitchStatement* Factory::createSwitchStatementNode(){
    return  dynamic_cast <statement::SwitchStatement*>( createNode(ndkSwitchStatement));
  }

  statement::ThrowStatement* Factory::createThrowStatementNode(){
    return  dynamic_cast <statement::ThrowStatement*>( createNode(ndkThrowStatement));
  }

  statement::TryStatement* Factory::createTryStatementNode(){
    return  dynamic_cast <statement::TryStatement*>( createNode(ndkTryStatement));
  }

  statement::WhileStatement* Factory::createWhileStatementNode(){
    return  dynamic_cast <statement::WhileStatement*>( createNode(ndkWhileStatement));
  }

  statement::WithStatement* Factory::createWithStatementNode(){
    return  dynamic_cast <statement::WithStatement*>( createNode(ndkWithStatement));
  }

  structure::ClassBody* Factory::createClassBodyNode(){
    return  dynamic_cast <structure::ClassBody*>( createNode(ndkClassBody));
  }

  structure::ExportSpecifier* Factory::createExportSpecifierNode(){
    return  dynamic_cast <structure::ExportSpecifier*>( createNode(ndkExportSpecifier));
  }

  structure::ImportDefaultSpecifier* Factory::createImportDefaultSpecifierNode(){
    return  dynamic_cast <structure::ImportDefaultSpecifier*>( createNode(ndkImportDefaultSpecifier));
  }

  structure::ImportNamespaceSpecifier* Factory::createImportNamespaceSpecifierNode(){
    return  dynamic_cast <structure::ImportNamespaceSpecifier*>( createNode(ndkImportNamespaceSpecifier));
  }

  structure::ImportSpecifier* Factory::createImportSpecifierNode(){
    return  dynamic_cast <structure::ImportSpecifier*>( createNode(ndkImportSpecifier));
  }

  structure::MethodDefinition* Factory::createMethodDefinitionNode(){
    return  dynamic_cast <structure::MethodDefinition*>( createNode(ndkMethodDefinition));
  }

  void Factory::printNodeSizes() {
    printf("base::Comment node: %dbyte(s)\n",(int)sizeof(base::Comment)); 
    printf("base::Program node: %dbyte(s)\n",(int)sizeof(base::Program)); 
    printf("base::System node: %dbyte(s)\n",(int)sizeof(base::System)); 
    printf("declaration::ClassDeclaration node: %dbyte(s)\n",(int)sizeof(declaration::ClassDeclaration)); 
    printf("declaration::ExportAllDeclaration node: %dbyte(s)\n",(int)sizeof(declaration::ExportAllDeclaration)); 
    printf("declaration::ExportDefaultDeclaration node: %dbyte(s)\n",(int)sizeof(declaration::ExportDefaultDeclaration)); 
    printf("declaration::ExportNamedDeclaration node: %dbyte(s)\n",(int)sizeof(declaration::ExportNamedDeclaration)); 
    printf("declaration::FunctionDeclaration node: %dbyte(s)\n",(int)sizeof(declaration::FunctionDeclaration)); 
    printf("declaration::ImportDeclaration node: %dbyte(s)\n",(int)sizeof(declaration::ImportDeclaration)); 
    printf("declaration::ModuleDeclaration node: %dbyte(s)\n",(int)sizeof(declaration::ModuleDeclaration)); 
    printf("declaration::VariableDeclaration node: %dbyte(s)\n",(int)sizeof(declaration::VariableDeclaration)); 
    printf("declaration::VariableDeclarator node: %dbyte(s)\n",(int)sizeof(declaration::VariableDeclarator)); 
    printf("expression::ArrayExpression node: %dbyte(s)\n",(int)sizeof(expression::ArrayExpression)); 
    printf("expression::ArrowFunctionExpression node: %dbyte(s)\n",(int)sizeof(expression::ArrowFunctionExpression)); 
    printf("expression::AssignmentExpression node: %dbyte(s)\n",(int)sizeof(expression::AssignmentExpression)); 
    printf("expression::AssignmentProperty node: %dbyte(s)\n",(int)sizeof(expression::AssignmentProperty)); 
    printf("expression::AwaitExpression node: %dbyte(s)\n",(int)sizeof(expression::AwaitExpression)); 
    printf("expression::BinaryExpression node: %dbyte(s)\n",(int)sizeof(expression::BinaryExpression)); 
    printf("expression::BooleanLiteral node: %dbyte(s)\n",(int)sizeof(expression::BooleanLiteral)); 
    printf("expression::CallExpression node: %dbyte(s)\n",(int)sizeof(expression::CallExpression)); 
    printf("expression::ClassExpression node: %dbyte(s)\n",(int)sizeof(expression::ClassExpression)); 
    printf("expression::ConditionalExpression node: %dbyte(s)\n",(int)sizeof(expression::ConditionalExpression)); 
    printf("expression::FunctionExpression node: %dbyte(s)\n",(int)sizeof(expression::FunctionExpression)); 
    printf("expression::Identifier node: %dbyte(s)\n",(int)sizeof(expression::Identifier)); 
    printf("expression::LogicalExpression node: %dbyte(s)\n",(int)sizeof(expression::LogicalExpression)); 
    printf("expression::MemberExpression node: %dbyte(s)\n",(int)sizeof(expression::MemberExpression)); 
    printf("expression::MetaProperty node: %dbyte(s)\n",(int)sizeof(expression::MetaProperty)); 
    printf("expression::NewExpression node: %dbyte(s)\n",(int)sizeof(expression::NewExpression)); 
    printf("expression::NullLiteral node: %dbyte(s)\n",(int)sizeof(expression::NullLiteral)); 
    printf("expression::NumberLiteral node: %dbyte(s)\n",(int)sizeof(expression::NumberLiteral)); 
    printf("expression::ObjectExpression node: %dbyte(s)\n",(int)sizeof(expression::ObjectExpression)); 
    printf("expression::Property node: %dbyte(s)\n",(int)sizeof(expression::Property)); 
    printf("expression::RegExpLiteral node: %dbyte(s)\n",(int)sizeof(expression::RegExpLiteral)); 
    printf("expression::SequenceExpression node: %dbyte(s)\n",(int)sizeof(expression::SequenceExpression)); 
    printf("expression::SpreadElement node: %dbyte(s)\n",(int)sizeof(expression::SpreadElement)); 
    printf("expression::StringLiteral node: %dbyte(s)\n",(int)sizeof(expression::StringLiteral)); 
    printf("expression::Super node: %dbyte(s)\n",(int)sizeof(expression::Super)); 
    printf("expression::TaggedTemplateExpression node: %dbyte(s)\n",(int)sizeof(expression::TaggedTemplateExpression)); 
    printf("expression::TemplateElement node: %dbyte(s)\n",(int)sizeof(expression::TemplateElement)); 
    printf("expression::TemplateLiteral node: %dbyte(s)\n",(int)sizeof(expression::TemplateLiteral)); 
    printf("expression::ThisExpression node: %dbyte(s)\n",(int)sizeof(expression::ThisExpression)); 
    printf("expression::UnaryExpression node: %dbyte(s)\n",(int)sizeof(expression::UnaryExpression)); 
    printf("expression::UpdateExpression node: %dbyte(s)\n",(int)sizeof(expression::UpdateExpression)); 
    printf("expression::YieldExpression node: %dbyte(s)\n",(int)sizeof(expression::YieldExpression)); 
    printf("statement::ArrayPattern node: %dbyte(s)\n",(int)sizeof(statement::ArrayPattern)); 
    printf("statement::AssignmentPattern node: %dbyte(s)\n",(int)sizeof(statement::AssignmentPattern)); 
    printf("statement::BlockStatement node: %dbyte(s)\n",(int)sizeof(statement::BlockStatement)); 
    printf("statement::BreakStatement node: %dbyte(s)\n",(int)sizeof(statement::BreakStatement)); 
    printf("statement::CatchClause node: %dbyte(s)\n",(int)sizeof(statement::CatchClause)); 
    printf("statement::ContinueStatement node: %dbyte(s)\n",(int)sizeof(statement::ContinueStatement)); 
    printf("statement::DebuggerStatement node: %dbyte(s)\n",(int)sizeof(statement::DebuggerStatement)); 
    printf("statement::DoWhileStatement node: %dbyte(s)\n",(int)sizeof(statement::DoWhileStatement)); 
    printf("statement::EmptyStatement node: %dbyte(s)\n",(int)sizeof(statement::EmptyStatement)); 
    printf("statement::ExpressionStatement node: %dbyte(s)\n",(int)sizeof(statement::ExpressionStatement)); 
    printf("statement::ForInStatement node: %dbyte(s)\n",(int)sizeof(statement::ForInStatement)); 
    printf("statement::ForOfStatement node: %dbyte(s)\n",(int)sizeof(statement::ForOfStatement)); 
    printf("statement::ForStatement node: %dbyte(s)\n",(int)sizeof(statement::ForStatement)); 
    printf("statement::Function node: %dbyte(s)\n",(int)sizeof(statement::Function)); 
    printf("statement::IfStatement node: %dbyte(s)\n",(int)sizeof(statement::IfStatement)); 
    printf("statement::LabeledStatement node: %dbyte(s)\n",(int)sizeof(statement::LabeledStatement)); 
    printf("statement::ObjectPattern node: %dbyte(s)\n",(int)sizeof(statement::ObjectPattern)); 
    printf("statement::RestElement node: %dbyte(s)\n",(int)sizeof(statement::RestElement)); 
    printf("statement::ReturnStatement node: %dbyte(s)\n",(int)sizeof(statement::ReturnStatement)); 
    printf("statement::SwitchCase node: %dbyte(s)\n",(int)sizeof(statement::SwitchCase)); 
    printf("statement::SwitchStatement node: %dbyte(s)\n",(int)sizeof(statement::SwitchStatement)); 
    printf("statement::ThrowStatement node: %dbyte(s)\n",(int)sizeof(statement::ThrowStatement)); 
    printf("statement::TryStatement node: %dbyte(s)\n",(int)sizeof(statement::TryStatement)); 
    printf("statement::WhileStatement node: %dbyte(s)\n",(int)sizeof(statement::WhileStatement)); 
    printf("statement::WithStatement node: %dbyte(s)\n",(int)sizeof(statement::WithStatement)); 
    printf("structure::ClassBody node: %dbyte(s)\n",(int)sizeof(structure::ClassBody)); 
    printf("structure::ExportSpecifier node: %dbyte(s)\n",(int)sizeof(structure::ExportSpecifier)); 
    printf("structure::ImportDefaultSpecifier node: %dbyte(s)\n",(int)sizeof(structure::ImportDefaultSpecifier)); 
    printf("structure::ImportNamespaceSpecifier node: %dbyte(s)\n",(int)sizeof(structure::ImportNamespaceSpecifier)); 
    printf("structure::ImportSpecifier node: %dbyte(s)\n",(int)sizeof(structure::ImportSpecifier)); 
    printf("structure::MethodDefinition node: %dbyte(s)\n",(int)sizeof(structure::MethodDefinition)); 
  }

}}}
