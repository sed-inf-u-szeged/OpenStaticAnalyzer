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

#include "csharp/inc/csharp.h"

#include <string.h>
#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "common/inc/StringSup.h"
#include "common/inc/WriteMessage.h"

#include "io/inc/ZippedIO.h"

#include "csharp/inc/messages.h"

namespace columbus { namespace csharp { namespace asg {
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
  root = dynamic_cast<structure::CompilationUnitSyntax*>(&createNode(ndkCompilationUnitSyntax, 100));
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
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_HEADER_DATA_ALREADY_LOADED(unknownDataIt->first));
    if (unknownDataIt->first == hdkPropertyData) {
      hasUnkownPropertyData = true;
      break;
    }
  }
  if (!isContainPropertyData && !hasUnkownPropertyData) {
    zipIo.writeInt4(headerDataList.size() + unknownHeaderData.size() + 1);
    PropertyData propertyData;
    propertyData.add(PropertyData::csih_Type, "CSharpLanguage");
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
      propertyData.add(PropertyData::csih_Type, "CSharpLanguage");
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
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
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
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
  if (type != "CSharpLanguage")
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_WRONG_FILE_TYPE_INFORMATION);
  // Checking API version
  std::string apiVersion;
  if (!propertyData.get(PropertyData::csih_APIVersion, apiVersion))
    throw CsharpException(COLUMBUS_LOCATION,CMSG_EX_MISSING_API_VERSION_INFORMATION );
  if (apiVersion != APIVersion)
       throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_WRONG_API_VERSION(APIVersion,apiVersion));
  // Checking binary version
  std::string binVersion;
  if (!propertyData.get(PropertyData::csih_BinaryVersion, binVersion))
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_MISSING_BINARY_VERSION_INFORMATION);
  if (binVersion != BinaryVersion)
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_WRONG_BINARY_VERSION(BinaryVersion,binVersion));
  }

void Factory::load( io::ZippedIO &zipIo, const std::list<HeaderData*> &headerDataList)
{
  bool zip = false;
  clear();
  char tag[4];
  zipIo.readData (tag,4);
  if ( strcmp(tag,"csi") && strcmp(tag,"zsi") ) {
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
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
  root = dynamic_cast<structure::CompilationUnitSyntax*>(container[100]);
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

structure::CompilationUnitSyntax* Factory::getRoot() const {
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
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  return *p;
}

base::Base* Factory::getPointer(NodeId id) const {
  base::Base* p = NULL;
  try {
    p = container.at(id);
  } catch (const std::out_of_range&) {
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  }
  return p;
}

RefDistributorStrTable& Factory::getStringTable() const {
  return *strTable;
}

void Factory::destroyNode(NodeId id) {
  if (!reverseEdges)
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (!getExist(id))
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (id >= container.size())
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_NEXT_ELEMENT_DOES_NOT_EXIST);
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
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_LOADED_FILTER_DOES_NOT_MATCH_TO_THE_CURRENT);

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
    case ndkAliasQualifiedNameSyntax: p = new expression::AliasQualifiedNameSyntax(id, this); break;
    case ndkAnonymousMethodExpressionSyntax: p = new expression::AnonymousMethodExpressionSyntax(id, this); break;
    case ndkAnonymousObjectCreationExpressionSyntax: p = new expression::AnonymousObjectCreationExpressionSyntax(id, this); break;
    case ndkArrayCreationExpressionSyntax: p = new expression::ArrayCreationExpressionSyntax(id, this); break;
    case ndkArrayTypeSyntax: p = new expression::ArrayTypeSyntax(id, this); break;
    case ndkAssignmentExpressionSyntax: p = new expression::AssignmentExpressionSyntax(id, this); break;
    case ndkAwaitExpressionSyntax: p = new expression::AwaitExpressionSyntax(id, this); break;
    case ndkBaseExpressionSyntax: p = new expression::BaseExpressionSyntax(id, this); break;
    case ndkBinaryExpressionSyntax: p = new expression::BinaryExpressionSyntax(id, this); break;
    case ndkCastExpressionSyntax: p = new expression::CastExpressionSyntax(id, this); break;
    case ndkCheckedExpressionSyntax: p = new expression::CheckedExpressionSyntax(id, this); break;
    case ndkConditionalAccessExpressionSyntax: p = new expression::ConditionalAccessExpressionSyntax(id, this); break;
    case ndkConditionalExpressionSyntax: p = new expression::ConditionalExpressionSyntax(id, this); break;
    case ndkDeclarationExpressionSyntax: p = new expression::DeclarationExpressionSyntax(id, this); break;
    case ndkDefaultExpressionSyntax: p = new expression::DefaultExpressionSyntax(id, this); break;
    case ndkElementAccessExpressionSyntax: p = new expression::ElementAccessExpressionSyntax(id, this); break;
    case ndkElementBindingExpressionSyntax: p = new expression::ElementBindingExpressionSyntax(id, this); break;
    case ndkGenericNameSyntax: p = new expression::GenericNameSyntax(id, this); break;
    case ndkIdentifierNameSyntax: p = new expression::IdentifierNameSyntax(id, this); break;
    case ndkImplicitArrayCreationExpressionSyntax: p = new expression::ImplicitArrayCreationExpressionSyntax(id, this); break;
    case ndkImplicitElementAccessSyntax: p = new expression::ImplicitElementAccessSyntax(id, this); break;
    case ndkImplicitStackAllocArrayCreationExpressionSyntax: p = new expression::ImplicitStackAllocArrayCreationExpressionSyntax(id, this); break;
    case ndkInitializerExpressionSyntax: p = new expression::InitializerExpressionSyntax(id, this); break;
    case ndkInterpolatedStringExpressionSyntax: p = new expression::InterpolatedStringExpressionSyntax(id, this); break;
    case ndkInvocationExpressionSyntax: p = new expression::InvocationExpressionSyntax(id, this); break;
    case ndkIsPatternExpressionSyntax: p = new expression::IsPatternExpressionSyntax(id, this); break;
    case ndkLiteralExpressionSyntax: p = new expression::LiteralExpressionSyntax(id, this); break;
    case ndkMakeRefExpressionSyntax: p = new expression::MakeRefExpressionSyntax(id, this); break;
    case ndkMemberAccessExpressionSyntax: p = new expression::MemberAccessExpressionSyntax(id, this); break;
    case ndkMemberBindingExpressionSyntax: p = new expression::MemberBindingExpressionSyntax(id, this); break;
    case ndkNullableTypeSyntax: p = new expression::NullableTypeSyntax(id, this); break;
    case ndkObjectCreationExpressionSyntax: p = new expression::ObjectCreationExpressionSyntax(id, this); break;
    case ndkOmittedArraySizeExpressionSyntax: p = new expression::OmittedArraySizeExpressionSyntax(id, this); break;
    case ndkOmittedTypeArgumentSyntax: p = new expression::OmittedTypeArgumentSyntax(id, this); break;
    case ndkParenthesizedExpressionSyntax: p = new expression::ParenthesizedExpressionSyntax(id, this); break;
    case ndkParenthesizedLambdaExpressionSyntax: p = new expression::ParenthesizedLambdaExpressionSyntax(id, this); break;
    case ndkPointerTypeSyntax: p = new expression::PointerTypeSyntax(id, this); break;
    case ndkPostfixUnaryExpressionSyntax: p = new expression::PostfixUnaryExpressionSyntax(id, this); break;
    case ndkPredefinedTypeSyntax: p = new expression::PredefinedTypeSyntax(id, this); break;
    case ndkPrefixUnaryExpressionSyntax: p = new expression::PrefixUnaryExpressionSyntax(id, this); break;
    case ndkQualifiedNameSyntax: p = new expression::QualifiedNameSyntax(id, this); break;
    case ndkQueryExpressionSyntax: p = new expression::QueryExpressionSyntax(id, this); break;
    case ndkRangeExpressionSyntax: p = new expression::RangeExpressionSyntax(id, this); break;
    case ndkRefExpressionSyntax: p = new expression::RefExpressionSyntax(id, this); break;
    case ndkRefTypeExpressionSyntax: p = new expression::RefTypeExpressionSyntax(id, this); break;
    case ndkRefTypeSyntax: p = new expression::RefTypeSyntax(id, this); break;
    case ndkRefValueExpressionSyntax: p = new expression::RefValueExpressionSyntax(id, this); break;
    case ndkSimpleLambdaExpressionSyntax: p = new expression::SimpleLambdaExpressionSyntax(id, this); break;
    case ndkSizeOfExpressionSyntax: p = new expression::SizeOfExpressionSyntax(id, this); break;
    case ndkStackAllocArrayCreationExpressionSyntax: p = new expression::StackAllocArrayCreationExpressionSyntax(id, this); break;
    case ndkSwitchExpressionSyntax: p = new expression::SwitchExpressionSyntax(id, this); break;
    case ndkThisExpressionSyntax: p = new expression::ThisExpressionSyntax(id, this); break;
    case ndkThrowExpressionSyntax: p = new expression::ThrowExpressionSyntax(id, this); break;
    case ndkTupleExpressionSyntax: p = new expression::TupleExpressionSyntax(id, this); break;
    case ndkTupleTypeSyntax: p = new expression::TupleTypeSyntax(id, this); break;
    case ndkTypeOfExpressionSyntax: p = new expression::TypeOfExpressionSyntax(id, this); break;
    case ndkBlockSyntax: p = new statement::BlockSyntax(id, this); break;
    case ndkBreakStatementSyntax: p = new statement::BreakStatementSyntax(id, this); break;
    case ndkCheckedStatementSyntax: p = new statement::CheckedStatementSyntax(id, this); break;
    case ndkContinueStatementSyntax: p = new statement::ContinueStatementSyntax(id, this); break;
    case ndkDoStatementSyntax: p = new statement::DoStatementSyntax(id, this); break;
    case ndkEmptyStatementSyntax: p = new statement::EmptyStatementSyntax(id, this); break;
    case ndkExpressionStatementSyntax: p = new statement::ExpressionStatementSyntax(id, this); break;
    case ndkFixedStatementSyntax: p = new statement::FixedStatementSyntax(id, this); break;
    case ndkForEachStatementSyntax: p = new statement::ForEachStatementSyntax(id, this); break;
    case ndkForEachVariableStatementSyntax: p = new statement::ForEachVariableStatementSyntax(id, this); break;
    case ndkForStatementSyntax: p = new statement::ForStatementSyntax(id, this); break;
    case ndkGotoStatementSyntax: p = new statement::GotoStatementSyntax(id, this); break;
    case ndkIfStatementSyntax: p = new statement::IfStatementSyntax(id, this); break;
    case ndkLabeledStatementSyntax: p = new statement::LabeledStatementSyntax(id, this); break;
    case ndkLocalDeclarationStatementSyntax: p = new statement::LocalDeclarationStatementSyntax(id, this); break;
    case ndkLocalFunctionStatementSyntax: p = new statement::LocalFunctionStatementSyntax(id, this); break;
    case ndkLockStatementSyntax: p = new statement::LockStatementSyntax(id, this); break;
    case ndkReturnStatementSyntax: p = new statement::ReturnStatementSyntax(id, this); break;
    case ndkSwitchStatementSyntax: p = new statement::SwitchStatementSyntax(id, this); break;
    case ndkThrowStatementSyntax: p = new statement::ThrowStatementSyntax(id, this); break;
    case ndkTryStatementSyntax: p = new statement::TryStatementSyntax(id, this); break;
    case ndkUnsafeStatementSyntax: p = new statement::UnsafeStatementSyntax(id, this); break;
    case ndkUsingStatementSyntax: p = new statement::UsingStatementSyntax(id, this); break;
    case ndkWhileStatementSyntax: p = new statement::WhileStatementSyntax(id, this); break;
    case ndkYieldStatementSyntax: p = new statement::YieldStatementSyntax(id, this); break;
    case ndkAccessorDeclarationSyntax: p = new structure::AccessorDeclarationSyntax(id, this); break;
    case ndkAccessorListSyntax: p = new structure::AccessorListSyntax(id, this); break;
    case ndkAnonymousObjectMemberDeclaratorSyntax: p = new structure::AnonymousObjectMemberDeclaratorSyntax(id, this); break;
    case ndkArgumentListSyntax: p = new structure::ArgumentListSyntax(id, this); break;
    case ndkArgumentSyntax: p = new structure::ArgumentSyntax(id, this); break;
    case ndkArrayRankSpecifierSyntax: p = new structure::ArrayRankSpecifierSyntax(id, this); break;
    case ndkArrowExpressionClauseSyntax: p = new structure::ArrowExpressionClauseSyntax(id, this); break;
    case ndkAttributeArgumentListSyntax: p = new structure::AttributeArgumentListSyntax(id, this); break;
    case ndkAttributeArgumentSyntax: p = new structure::AttributeArgumentSyntax(id, this); break;
    case ndkAttributeListSyntax: p = new structure::AttributeListSyntax(id, this); break;
    case ndkAttributeSyntax: p = new structure::AttributeSyntax(id, this); break;
    case ndkAttributeTargetSpecifierSyntax: p = new structure::AttributeTargetSpecifierSyntax(id, this); break;
    case ndkBaseListSyntax: p = new structure::BaseListSyntax(id, this); break;
    case ndkBracketedArgumentListSyntax: p = new structure::BracketedArgumentListSyntax(id, this); break;
    case ndkBracketedParameterListSyntax: p = new structure::BracketedParameterListSyntax(id, this); break;
    case ndkCasePatternSwitchLabelSyntax: p = new structure::CasePatternSwitchLabelSyntax(id, this); break;
    case ndkCaseSwitchLabelSyntax: p = new structure::CaseSwitchLabelSyntax(id, this); break;
    case ndkCatchClauseSyntax: p = new structure::CatchClauseSyntax(id, this); break;
    case ndkCatchDeclarationSyntax: p = new structure::CatchDeclarationSyntax(id, this); break;
    case ndkCatchFilterClauseSyntax: p = new structure::CatchFilterClauseSyntax(id, this); break;
    case ndkClassDeclarationSyntax: p = new structure::ClassDeclarationSyntax(id, this); break;
    case ndkClassOrStructConstraintSyntax: p = new structure::ClassOrStructConstraintSyntax(id, this); break;
    case ndkCompilationUnitSyntax: p = new structure::CompilationUnitSyntax(id, this); break;
    case ndkConstantPatternSyntax: p = new structure::ConstantPatternSyntax(id, this); break;
    case ndkConstructorConstraintSyntax: p = new structure::ConstructorConstraintSyntax(id, this); break;
    case ndkConstructorDeclarationSyntax: p = new structure::ConstructorDeclarationSyntax(id, this); break;
    case ndkConstructorInitializerSyntax: p = new structure::ConstructorInitializerSyntax(id, this); break;
    case ndkConversionOperatorDeclarationSyntax: p = new structure::ConversionOperatorDeclarationSyntax(id, this); break;
    case ndkConversionOperatorMemberCrefSyntax: p = new structure::ConversionOperatorMemberCrefSyntax(id, this); break;
    case ndkCrefBracketedParameterListSyntax: p = new structure::CrefBracketedParameterListSyntax(id, this); break;
    case ndkCrefParameterListSyntax: p = new structure::CrefParameterListSyntax(id, this); break;
    case ndkCrefParameterSyntax: p = new structure::CrefParameterSyntax(id, this); break;
    case ndkDeclarationPatternSyntax: p = new structure::DeclarationPatternSyntax(id, this); break;
    case ndkDefaultSwitchLabelSyntax: p = new structure::DefaultSwitchLabelSyntax(id, this); break;
    case ndkDelegateDeclarationSyntax: p = new structure::DelegateDeclarationSyntax(id, this); break;
    case ndkDestructorDeclarationSyntax: p = new structure::DestructorDeclarationSyntax(id, this); break;
    case ndkDiscardDesignationSyntax: p = new structure::DiscardDesignationSyntax(id, this); break;
    case ndkDiscardPatternSyntax: p = new structure::DiscardPatternSyntax(id, this); break;
    case ndkElseClauseSyntax: p = new structure::ElseClauseSyntax(id, this); break;
    case ndkEnumDeclarationSyntax: p = new structure::EnumDeclarationSyntax(id, this); break;
    case ndkEnumMemberDeclarationSyntax: p = new structure::EnumMemberDeclarationSyntax(id, this); break;
    case ndkEqualsValueClauseSyntax: p = new structure::EqualsValueClauseSyntax(id, this); break;
    case ndkEventDeclarationSyntax: p = new structure::EventDeclarationSyntax(id, this); break;
    case ndkEventFieldDeclarationSyntax: p = new structure::EventFieldDeclarationSyntax(id, this); break;
    case ndkExplicitInterfaceSpecifierSyntax: p = new structure::ExplicitInterfaceSpecifierSyntax(id, this); break;
    case ndkExternAliasDirectiveSyntax: p = new structure::ExternAliasDirectiveSyntax(id, this); break;
    case ndkFieldDeclarationSyntax: p = new structure::FieldDeclarationSyntax(id, this); break;
    case ndkFinallyClauseSyntax: p = new structure::FinallyClauseSyntax(id, this); break;
    case ndkFromClauseSyntax: p = new structure::FromClauseSyntax(id, this); break;
    case ndkGlobalStatementSyntax: p = new structure::GlobalStatementSyntax(id, this); break;
    case ndkGroupClauseSyntax: p = new structure::GroupClauseSyntax(id, this); break;
    case ndkIncompleteMemberSyntax: p = new structure::IncompleteMemberSyntax(id, this); break;
    case ndkIndexerDeclarationSyntax: p = new structure::IndexerDeclarationSyntax(id, this); break;
    case ndkIndexerMemberCrefSyntax: p = new structure::IndexerMemberCrefSyntax(id, this); break;
    case ndkInterfaceDeclarationSyntax: p = new structure::InterfaceDeclarationSyntax(id, this); break;
    case ndkInterpolatedStringTextSyntax: p = new structure::InterpolatedStringTextSyntax(id, this); break;
    case ndkInterpolationAlignmentClauseSyntax: p = new structure::InterpolationAlignmentClauseSyntax(id, this); break;
    case ndkInterpolationFormatClauseSyntax: p = new structure::InterpolationFormatClauseSyntax(id, this); break;
    case ndkInterpolationSyntax: p = new structure::InterpolationSyntax(id, this); break;
    case ndkJoinClauseSyntax: p = new structure::JoinClauseSyntax(id, this); break;
    case ndkJoinIntoClauseSyntax: p = new structure::JoinIntoClauseSyntax(id, this); break;
    case ndkLetClauseSyntax: p = new structure::LetClauseSyntax(id, this); break;
    case ndkMethodDeclarationSyntax: p = new structure::MethodDeclarationSyntax(id, this); break;
    case ndkNameColonSyntax: p = new structure::NameColonSyntax(id, this); break;
    case ndkNameEqualsSyntax: p = new structure::NameEqualsSyntax(id, this); break;
    case ndkNameMemberCrefSyntax: p = new structure::NameMemberCrefSyntax(id, this); break;
    case ndkNamespaceDeclarationSyntax: p = new structure::NamespaceDeclarationSyntax(id, this); break;
    case ndkOperatorDeclarationSyntax: p = new structure::OperatorDeclarationSyntax(id, this); break;
    case ndkOperatorMemberCrefSyntax: p = new structure::OperatorMemberCrefSyntax(id, this); break;
    case ndkOrderByClauseSyntax: p = new structure::OrderByClauseSyntax(id, this); break;
    case ndkOrderingSyntax: p = new structure::OrderingSyntax(id, this); break;
    case ndkParameterListSyntax: p = new structure::ParameterListSyntax(id, this); break;
    case ndkParameterSyntax: p = new structure::ParameterSyntax(id, this); break;
    case ndkParenthesizedVariableDesignationSyntax: p = new structure::ParenthesizedVariableDesignationSyntax(id, this); break;
    case ndkPositionalPatternClauseSyntax: p = new structure::PositionalPatternClauseSyntax(id, this); break;
    case ndkPropertyDeclarationSyntax: p = new structure::PropertyDeclarationSyntax(id, this); break;
    case ndkPropertyPatternClauseSyntax: p = new structure::PropertyPatternClauseSyntax(id, this); break;
    case ndkQualifiedCrefSyntax: p = new structure::QualifiedCrefSyntax(id, this); break;
    case ndkQueryBodySyntax: p = new structure::QueryBodySyntax(id, this); break;
    case ndkQueryContinuationSyntax: p = new structure::QueryContinuationSyntax(id, this); break;
    case ndkRecursivePatternSyntax: p = new structure::RecursivePatternSyntax(id, this); break;
    case ndkSelectClauseSyntax: p = new structure::SelectClauseSyntax(id, this); break;
    case ndkSimpleBaseTypeSyntax: p = new structure::SimpleBaseTypeSyntax(id, this); break;
    case ndkSingleVariableDesignationSyntax: p = new structure::SingleVariableDesignationSyntax(id, this); break;
    case ndkStructDeclarationSyntax: p = new structure::StructDeclarationSyntax(id, this); break;
    case ndkSubpatternSyntax: p = new structure::SubpatternSyntax(id, this); break;
    case ndkSwitchExpressionArmSyntax: p = new structure::SwitchExpressionArmSyntax(id, this); break;
    case ndkSwitchSectionSyntax: p = new structure::SwitchSectionSyntax(id, this); break;
    case ndkSyntaxToken: p = new structure::SyntaxToken(id, this); break;
    case ndkTupleElementSyntax: p = new structure::TupleElementSyntax(id, this); break;
    case ndkTypeArgumentListSyntax: p = new structure::TypeArgumentListSyntax(id, this); break;
    case ndkTypeConstraintSyntax: p = new structure::TypeConstraintSyntax(id, this); break;
    case ndkTypeCrefSyntax: p = new structure::TypeCrefSyntax(id, this); break;
    case ndkTypeParameterConstraintClauseSyntax: p = new structure::TypeParameterConstraintClauseSyntax(id, this); break;
    case ndkTypeParameterListSyntax: p = new structure::TypeParameterListSyntax(id, this); break;
    case ndkTypeParameterSyntax: p = new structure::TypeParameterSyntax(id, this); break;
    case ndkUsingDirectiveSyntax: p = new structure::UsingDirectiveSyntax(id, this); break;
    case ndkVarPatternSyntax: p = new structure::VarPatternSyntax(id, this); break;
    case ndkVariableDeclarationSyntax: p = new structure::VariableDeclarationSyntax(id, this); break;
    case ndkVariableDeclaratorSyntax: p = new structure::VariableDeclaratorSyntax(id, this); break;
    case ndkWhenClauseSyntax: p = new structure::WhenClauseSyntax(id, this); break;
    case ndkWhereClauseSyntax: p = new structure::WhereClauseSyntax(id, this); break;
    case ndkXmlCDataSectionSyntax: p = new structure::XmlCDataSectionSyntax(id, this); break;
    case ndkXmlCommentSyntax: p = new structure::XmlCommentSyntax(id, this); break;
    case ndkXmlCrefAttributeSyntax: p = new structure::XmlCrefAttributeSyntax(id, this); break;
    case ndkXmlElementEndTagSyntax: p = new structure::XmlElementEndTagSyntax(id, this); break;
    case ndkXmlElementStartTagSyntax: p = new structure::XmlElementStartTagSyntax(id, this); break;
    case ndkXmlElementSyntax: p = new structure::XmlElementSyntax(id, this); break;
    case ndkXmlEmptyElementSyntax: p = new structure::XmlEmptyElementSyntax(id, this); break;
    case ndkXmlNameAttributeSyntax: p = new structure::XmlNameAttributeSyntax(id, this); break;
    case ndkXmlNameSyntax: p = new structure::XmlNameSyntax(id, this); break;
    case ndkXmlPrefixSyntax: p = new structure::XmlPrefixSyntax(id, this); break;
    case ndkXmlProcessingInstructionSyntax: p = new structure::XmlProcessingInstructionSyntax(id, this); break;
    case ndkXmlTextAttributeSyntax: p = new structure::XmlTextAttributeSyntax(id, this); break;
    case ndkXmlTextSyntax: p = new structure::XmlTextSyntax(id, this); break;
    default: throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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
    case ndkAliasQualifiedNameSyntax: p = new expression::AliasQualifiedNameSyntax(i,this); break;
    case ndkAnonymousMethodExpressionSyntax: p = new expression::AnonymousMethodExpressionSyntax(i,this); break;
    case ndkAnonymousObjectCreationExpressionSyntax: p = new expression::AnonymousObjectCreationExpressionSyntax(i,this); break;
    case ndkArrayCreationExpressionSyntax: p = new expression::ArrayCreationExpressionSyntax(i,this); break;
    case ndkArrayTypeSyntax: p = new expression::ArrayTypeSyntax(i,this); break;
    case ndkAssignmentExpressionSyntax: p = new expression::AssignmentExpressionSyntax(i,this); break;
    case ndkAwaitExpressionSyntax: p = new expression::AwaitExpressionSyntax(i,this); break;
    case ndkBaseExpressionSyntax: p = new expression::BaseExpressionSyntax(i,this); break;
    case ndkBinaryExpressionSyntax: p = new expression::BinaryExpressionSyntax(i,this); break;
    case ndkCastExpressionSyntax: p = new expression::CastExpressionSyntax(i,this); break;
    case ndkCheckedExpressionSyntax: p = new expression::CheckedExpressionSyntax(i,this); break;
    case ndkConditionalAccessExpressionSyntax: p = new expression::ConditionalAccessExpressionSyntax(i,this); break;
    case ndkConditionalExpressionSyntax: p = new expression::ConditionalExpressionSyntax(i,this); break;
    case ndkDeclarationExpressionSyntax: p = new expression::DeclarationExpressionSyntax(i,this); break;
    case ndkDefaultExpressionSyntax: p = new expression::DefaultExpressionSyntax(i,this); break;
    case ndkElementAccessExpressionSyntax: p = new expression::ElementAccessExpressionSyntax(i,this); break;
    case ndkElementBindingExpressionSyntax: p = new expression::ElementBindingExpressionSyntax(i,this); break;
    case ndkGenericNameSyntax: p = new expression::GenericNameSyntax(i,this); break;
    case ndkIdentifierNameSyntax: p = new expression::IdentifierNameSyntax(i,this); break;
    case ndkImplicitArrayCreationExpressionSyntax: p = new expression::ImplicitArrayCreationExpressionSyntax(i,this); break;
    case ndkImplicitElementAccessSyntax: p = new expression::ImplicitElementAccessSyntax(i,this); break;
    case ndkImplicitStackAllocArrayCreationExpressionSyntax: p = new expression::ImplicitStackAllocArrayCreationExpressionSyntax(i,this); break;
    case ndkInitializerExpressionSyntax: p = new expression::InitializerExpressionSyntax(i,this); break;
    case ndkInterpolatedStringExpressionSyntax: p = new expression::InterpolatedStringExpressionSyntax(i,this); break;
    case ndkInvocationExpressionSyntax: p = new expression::InvocationExpressionSyntax(i,this); break;
    case ndkIsPatternExpressionSyntax: p = new expression::IsPatternExpressionSyntax(i,this); break;
    case ndkLiteralExpressionSyntax: p = new expression::LiteralExpressionSyntax(i,this); break;
    case ndkMakeRefExpressionSyntax: p = new expression::MakeRefExpressionSyntax(i,this); break;
    case ndkMemberAccessExpressionSyntax: p = new expression::MemberAccessExpressionSyntax(i,this); break;
    case ndkMemberBindingExpressionSyntax: p = new expression::MemberBindingExpressionSyntax(i,this); break;
    case ndkNullableTypeSyntax: p = new expression::NullableTypeSyntax(i,this); break;
    case ndkObjectCreationExpressionSyntax: p = new expression::ObjectCreationExpressionSyntax(i,this); break;
    case ndkOmittedArraySizeExpressionSyntax: p = new expression::OmittedArraySizeExpressionSyntax(i,this); break;
    case ndkOmittedTypeArgumentSyntax: p = new expression::OmittedTypeArgumentSyntax(i,this); break;
    case ndkParenthesizedExpressionSyntax: p = new expression::ParenthesizedExpressionSyntax(i,this); break;
    case ndkParenthesizedLambdaExpressionSyntax: p = new expression::ParenthesizedLambdaExpressionSyntax(i,this); break;
    case ndkPointerTypeSyntax: p = new expression::PointerTypeSyntax(i,this); break;
    case ndkPostfixUnaryExpressionSyntax: p = new expression::PostfixUnaryExpressionSyntax(i,this); break;
    case ndkPredefinedTypeSyntax: p = new expression::PredefinedTypeSyntax(i,this); break;
    case ndkPrefixUnaryExpressionSyntax: p = new expression::PrefixUnaryExpressionSyntax(i,this); break;
    case ndkQualifiedNameSyntax: p = new expression::QualifiedNameSyntax(i,this); break;
    case ndkQueryExpressionSyntax: p = new expression::QueryExpressionSyntax(i,this); break;
    case ndkRangeExpressionSyntax: p = new expression::RangeExpressionSyntax(i,this); break;
    case ndkRefExpressionSyntax: p = new expression::RefExpressionSyntax(i,this); break;
    case ndkRefTypeExpressionSyntax: p = new expression::RefTypeExpressionSyntax(i,this); break;
    case ndkRefTypeSyntax: p = new expression::RefTypeSyntax(i,this); break;
    case ndkRefValueExpressionSyntax: p = new expression::RefValueExpressionSyntax(i,this); break;
    case ndkSimpleLambdaExpressionSyntax: p = new expression::SimpleLambdaExpressionSyntax(i,this); break;
    case ndkSizeOfExpressionSyntax: p = new expression::SizeOfExpressionSyntax(i,this); break;
    case ndkStackAllocArrayCreationExpressionSyntax: p = new expression::StackAllocArrayCreationExpressionSyntax(i,this); break;
    case ndkSwitchExpressionSyntax: p = new expression::SwitchExpressionSyntax(i,this); break;
    case ndkThisExpressionSyntax: p = new expression::ThisExpressionSyntax(i,this); break;
    case ndkThrowExpressionSyntax: p = new expression::ThrowExpressionSyntax(i,this); break;
    case ndkTupleExpressionSyntax: p = new expression::TupleExpressionSyntax(i,this); break;
    case ndkTupleTypeSyntax: p = new expression::TupleTypeSyntax(i,this); break;
    case ndkTypeOfExpressionSyntax: p = new expression::TypeOfExpressionSyntax(i,this); break;
    case ndkBlockSyntax: p = new statement::BlockSyntax(i,this); break;
    case ndkBreakStatementSyntax: p = new statement::BreakStatementSyntax(i,this); break;
    case ndkCheckedStatementSyntax: p = new statement::CheckedStatementSyntax(i,this); break;
    case ndkContinueStatementSyntax: p = new statement::ContinueStatementSyntax(i,this); break;
    case ndkDoStatementSyntax: p = new statement::DoStatementSyntax(i,this); break;
    case ndkEmptyStatementSyntax: p = new statement::EmptyStatementSyntax(i,this); break;
    case ndkExpressionStatementSyntax: p = new statement::ExpressionStatementSyntax(i,this); break;
    case ndkFixedStatementSyntax: p = new statement::FixedStatementSyntax(i,this); break;
    case ndkForEachStatementSyntax: p = new statement::ForEachStatementSyntax(i,this); break;
    case ndkForEachVariableStatementSyntax: p = new statement::ForEachVariableStatementSyntax(i,this); break;
    case ndkForStatementSyntax: p = new statement::ForStatementSyntax(i,this); break;
    case ndkGotoStatementSyntax: p = new statement::GotoStatementSyntax(i,this); break;
    case ndkIfStatementSyntax: p = new statement::IfStatementSyntax(i,this); break;
    case ndkLabeledStatementSyntax: p = new statement::LabeledStatementSyntax(i,this); break;
    case ndkLocalDeclarationStatementSyntax: p = new statement::LocalDeclarationStatementSyntax(i,this); break;
    case ndkLocalFunctionStatementSyntax: p = new statement::LocalFunctionStatementSyntax(i,this); break;
    case ndkLockStatementSyntax: p = new statement::LockStatementSyntax(i,this); break;
    case ndkReturnStatementSyntax: p = new statement::ReturnStatementSyntax(i,this); break;
    case ndkSwitchStatementSyntax: p = new statement::SwitchStatementSyntax(i,this); break;
    case ndkThrowStatementSyntax: p = new statement::ThrowStatementSyntax(i,this); break;
    case ndkTryStatementSyntax: p = new statement::TryStatementSyntax(i,this); break;
    case ndkUnsafeStatementSyntax: p = new statement::UnsafeStatementSyntax(i,this); break;
    case ndkUsingStatementSyntax: p = new statement::UsingStatementSyntax(i,this); break;
    case ndkWhileStatementSyntax: p = new statement::WhileStatementSyntax(i,this); break;
    case ndkYieldStatementSyntax: p = new statement::YieldStatementSyntax(i,this); break;
    case ndkAccessorDeclarationSyntax: p = new structure::AccessorDeclarationSyntax(i,this); break;
    case ndkAccessorListSyntax: p = new structure::AccessorListSyntax(i,this); break;
    case ndkAnonymousObjectMemberDeclaratorSyntax: p = new structure::AnonymousObjectMemberDeclaratorSyntax(i,this); break;
    case ndkArgumentListSyntax: p = new structure::ArgumentListSyntax(i,this); break;
    case ndkArgumentSyntax: p = new structure::ArgumentSyntax(i,this); break;
    case ndkArrayRankSpecifierSyntax: p = new structure::ArrayRankSpecifierSyntax(i,this); break;
    case ndkArrowExpressionClauseSyntax: p = new structure::ArrowExpressionClauseSyntax(i,this); break;
    case ndkAttributeArgumentListSyntax: p = new structure::AttributeArgumentListSyntax(i,this); break;
    case ndkAttributeArgumentSyntax: p = new structure::AttributeArgumentSyntax(i,this); break;
    case ndkAttributeListSyntax: p = new structure::AttributeListSyntax(i,this); break;
    case ndkAttributeSyntax: p = new structure::AttributeSyntax(i,this); break;
    case ndkAttributeTargetSpecifierSyntax: p = new structure::AttributeTargetSpecifierSyntax(i,this); break;
    case ndkBaseListSyntax: p = new structure::BaseListSyntax(i,this); break;
    case ndkBracketedArgumentListSyntax: p = new structure::BracketedArgumentListSyntax(i,this); break;
    case ndkBracketedParameterListSyntax: p = new structure::BracketedParameterListSyntax(i,this); break;
    case ndkCasePatternSwitchLabelSyntax: p = new structure::CasePatternSwitchLabelSyntax(i,this); break;
    case ndkCaseSwitchLabelSyntax: p = new structure::CaseSwitchLabelSyntax(i,this); break;
    case ndkCatchClauseSyntax: p = new structure::CatchClauseSyntax(i,this); break;
    case ndkCatchDeclarationSyntax: p = new structure::CatchDeclarationSyntax(i,this); break;
    case ndkCatchFilterClauseSyntax: p = new structure::CatchFilterClauseSyntax(i,this); break;
    case ndkClassDeclarationSyntax: p = new structure::ClassDeclarationSyntax(i,this); break;
    case ndkClassOrStructConstraintSyntax: p = new structure::ClassOrStructConstraintSyntax(i,this); break;
    case ndkCompilationUnitSyntax: p = new structure::CompilationUnitSyntax(i,this); break;
    case ndkConstantPatternSyntax: p = new structure::ConstantPatternSyntax(i,this); break;
    case ndkConstructorConstraintSyntax: p = new structure::ConstructorConstraintSyntax(i,this); break;
    case ndkConstructorDeclarationSyntax: p = new structure::ConstructorDeclarationSyntax(i,this); break;
    case ndkConstructorInitializerSyntax: p = new structure::ConstructorInitializerSyntax(i,this); break;
    case ndkConversionOperatorDeclarationSyntax: p = new structure::ConversionOperatorDeclarationSyntax(i,this); break;
    case ndkConversionOperatorMemberCrefSyntax: p = new structure::ConversionOperatorMemberCrefSyntax(i,this); break;
    case ndkCrefBracketedParameterListSyntax: p = new structure::CrefBracketedParameterListSyntax(i,this); break;
    case ndkCrefParameterListSyntax: p = new structure::CrefParameterListSyntax(i,this); break;
    case ndkCrefParameterSyntax: p = new structure::CrefParameterSyntax(i,this); break;
    case ndkDeclarationPatternSyntax: p = new structure::DeclarationPatternSyntax(i,this); break;
    case ndkDefaultSwitchLabelSyntax: p = new structure::DefaultSwitchLabelSyntax(i,this); break;
    case ndkDelegateDeclarationSyntax: p = new structure::DelegateDeclarationSyntax(i,this); break;
    case ndkDestructorDeclarationSyntax: p = new structure::DestructorDeclarationSyntax(i,this); break;
    case ndkDiscardDesignationSyntax: p = new structure::DiscardDesignationSyntax(i,this); break;
    case ndkDiscardPatternSyntax: p = new structure::DiscardPatternSyntax(i,this); break;
    case ndkElseClauseSyntax: p = new structure::ElseClauseSyntax(i,this); break;
    case ndkEnumDeclarationSyntax: p = new structure::EnumDeclarationSyntax(i,this); break;
    case ndkEnumMemberDeclarationSyntax: p = new structure::EnumMemberDeclarationSyntax(i,this); break;
    case ndkEqualsValueClauseSyntax: p = new structure::EqualsValueClauseSyntax(i,this); break;
    case ndkEventDeclarationSyntax: p = new structure::EventDeclarationSyntax(i,this); break;
    case ndkEventFieldDeclarationSyntax: p = new structure::EventFieldDeclarationSyntax(i,this); break;
    case ndkExplicitInterfaceSpecifierSyntax: p = new structure::ExplicitInterfaceSpecifierSyntax(i,this); break;
    case ndkExternAliasDirectiveSyntax: p = new structure::ExternAliasDirectiveSyntax(i,this); break;
    case ndkFieldDeclarationSyntax: p = new structure::FieldDeclarationSyntax(i,this); break;
    case ndkFinallyClauseSyntax: p = new structure::FinallyClauseSyntax(i,this); break;
    case ndkFromClauseSyntax: p = new structure::FromClauseSyntax(i,this); break;
    case ndkGlobalStatementSyntax: p = new structure::GlobalStatementSyntax(i,this); break;
    case ndkGroupClauseSyntax: p = new structure::GroupClauseSyntax(i,this); break;
    case ndkIncompleteMemberSyntax: p = new structure::IncompleteMemberSyntax(i,this); break;
    case ndkIndexerDeclarationSyntax: p = new structure::IndexerDeclarationSyntax(i,this); break;
    case ndkIndexerMemberCrefSyntax: p = new structure::IndexerMemberCrefSyntax(i,this); break;
    case ndkInterfaceDeclarationSyntax: p = new structure::InterfaceDeclarationSyntax(i,this); break;
    case ndkInterpolatedStringTextSyntax: p = new structure::InterpolatedStringTextSyntax(i,this); break;
    case ndkInterpolationAlignmentClauseSyntax: p = new structure::InterpolationAlignmentClauseSyntax(i,this); break;
    case ndkInterpolationFormatClauseSyntax: p = new structure::InterpolationFormatClauseSyntax(i,this); break;
    case ndkInterpolationSyntax: p = new structure::InterpolationSyntax(i,this); break;
    case ndkJoinClauseSyntax: p = new structure::JoinClauseSyntax(i,this); break;
    case ndkJoinIntoClauseSyntax: p = new structure::JoinIntoClauseSyntax(i,this); break;
    case ndkLetClauseSyntax: p = new structure::LetClauseSyntax(i,this); break;
    case ndkMethodDeclarationSyntax: p = new structure::MethodDeclarationSyntax(i,this); break;
    case ndkNameColonSyntax: p = new structure::NameColonSyntax(i,this); break;
    case ndkNameEqualsSyntax: p = new structure::NameEqualsSyntax(i,this); break;
    case ndkNameMemberCrefSyntax: p = new structure::NameMemberCrefSyntax(i,this); break;
    case ndkNamespaceDeclarationSyntax: p = new structure::NamespaceDeclarationSyntax(i,this); break;
    case ndkOperatorDeclarationSyntax: p = new structure::OperatorDeclarationSyntax(i,this); break;
    case ndkOperatorMemberCrefSyntax: p = new structure::OperatorMemberCrefSyntax(i,this); break;
    case ndkOrderByClauseSyntax: p = new structure::OrderByClauseSyntax(i,this); break;
    case ndkOrderingSyntax: p = new structure::OrderingSyntax(i,this); break;
    case ndkParameterListSyntax: p = new structure::ParameterListSyntax(i,this); break;
    case ndkParameterSyntax: p = new structure::ParameterSyntax(i,this); break;
    case ndkParenthesizedVariableDesignationSyntax: p = new structure::ParenthesizedVariableDesignationSyntax(i,this); break;
    case ndkPositionalPatternClauseSyntax: p = new structure::PositionalPatternClauseSyntax(i,this); break;
    case ndkPropertyDeclarationSyntax: p = new structure::PropertyDeclarationSyntax(i,this); break;
    case ndkPropertyPatternClauseSyntax: p = new structure::PropertyPatternClauseSyntax(i,this); break;
    case ndkQualifiedCrefSyntax: p = new structure::QualifiedCrefSyntax(i,this); break;
    case ndkQueryBodySyntax: p = new structure::QueryBodySyntax(i,this); break;
    case ndkQueryContinuationSyntax: p = new structure::QueryContinuationSyntax(i,this); break;
    case ndkRecursivePatternSyntax: p = new structure::RecursivePatternSyntax(i,this); break;
    case ndkSelectClauseSyntax: p = new structure::SelectClauseSyntax(i,this); break;
    case ndkSimpleBaseTypeSyntax: p = new structure::SimpleBaseTypeSyntax(i,this); break;
    case ndkSingleVariableDesignationSyntax: p = new structure::SingleVariableDesignationSyntax(i,this); break;
    case ndkStructDeclarationSyntax: p = new structure::StructDeclarationSyntax(i,this); break;
    case ndkSubpatternSyntax: p = new structure::SubpatternSyntax(i,this); break;
    case ndkSwitchExpressionArmSyntax: p = new structure::SwitchExpressionArmSyntax(i,this); break;
    case ndkSwitchSectionSyntax: p = new structure::SwitchSectionSyntax(i,this); break;
    case ndkSyntaxToken: p = new structure::SyntaxToken(i,this); break;
    case ndkTupleElementSyntax: p = new structure::TupleElementSyntax(i,this); break;
    case ndkTypeArgumentListSyntax: p = new structure::TypeArgumentListSyntax(i,this); break;
    case ndkTypeConstraintSyntax: p = new structure::TypeConstraintSyntax(i,this); break;
    case ndkTypeCrefSyntax: p = new structure::TypeCrefSyntax(i,this); break;
    case ndkTypeParameterConstraintClauseSyntax: p = new structure::TypeParameterConstraintClauseSyntax(i,this); break;
    case ndkTypeParameterListSyntax: p = new structure::TypeParameterListSyntax(i,this); break;
    case ndkTypeParameterSyntax: p = new structure::TypeParameterSyntax(i,this); break;
    case ndkUsingDirectiveSyntax: p = new structure::UsingDirectiveSyntax(i,this); break;
    case ndkVarPatternSyntax: p = new structure::VarPatternSyntax(i,this); break;
    case ndkVariableDeclarationSyntax: p = new structure::VariableDeclarationSyntax(i,this); break;
    case ndkVariableDeclaratorSyntax: p = new structure::VariableDeclaratorSyntax(i,this); break;
    case ndkWhenClauseSyntax: p = new structure::WhenClauseSyntax(i,this); break;
    case ndkWhereClauseSyntax: p = new structure::WhereClauseSyntax(i,this); break;
    case ndkXmlCDataSectionSyntax: p = new structure::XmlCDataSectionSyntax(i,this); break;
    case ndkXmlCommentSyntax: p = new structure::XmlCommentSyntax(i,this); break;
    case ndkXmlCrefAttributeSyntax: p = new structure::XmlCrefAttributeSyntax(i,this); break;
    case ndkXmlElementEndTagSyntax: p = new structure::XmlElementEndTagSyntax(i,this); break;
    case ndkXmlElementStartTagSyntax: p = new structure::XmlElementStartTagSyntax(i,this); break;
    case ndkXmlElementSyntax: p = new structure::XmlElementSyntax(i,this); break;
    case ndkXmlEmptyElementSyntax: p = new structure::XmlEmptyElementSyntax(i,this); break;
    case ndkXmlNameAttributeSyntax: p = new structure::XmlNameAttributeSyntax(i,this); break;
    case ndkXmlNameSyntax: p = new structure::XmlNameSyntax(i,this); break;
    case ndkXmlPrefixSyntax: p = new structure::XmlPrefixSyntax(i,this); break;
    case ndkXmlProcessingInstructionSyntax: p = new structure::XmlProcessingInstructionSyntax(i,this); break;
    case ndkXmlTextAttributeSyntax: p = new structure::XmlTextAttributeSyntax(i,this); break;
    case ndkXmlTextSyntax: p = new structure::XmlTextSyntax(i,this); break;
    default: throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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

  expression::AliasQualifiedNameSyntax* Factory::createAliasQualifiedNameSyntaxNode(){
    return  dynamic_cast <expression::AliasQualifiedNameSyntax*>( createNode(ndkAliasQualifiedNameSyntax));
  }

  expression::AnonymousMethodExpressionSyntax* Factory::createAnonymousMethodExpressionSyntaxNode(){
    return  dynamic_cast <expression::AnonymousMethodExpressionSyntax*>( createNode(ndkAnonymousMethodExpressionSyntax));
  }

  expression::AnonymousObjectCreationExpressionSyntax* Factory::createAnonymousObjectCreationExpressionSyntaxNode(){
    return  dynamic_cast <expression::AnonymousObjectCreationExpressionSyntax*>( createNode(ndkAnonymousObjectCreationExpressionSyntax));
  }

  expression::ArrayCreationExpressionSyntax* Factory::createArrayCreationExpressionSyntaxNode(){
    return  dynamic_cast <expression::ArrayCreationExpressionSyntax*>( createNode(ndkArrayCreationExpressionSyntax));
  }

  expression::ArrayTypeSyntax* Factory::createArrayTypeSyntaxNode(){
    return  dynamic_cast <expression::ArrayTypeSyntax*>( createNode(ndkArrayTypeSyntax));
  }

  expression::AssignmentExpressionSyntax* Factory::createAssignmentExpressionSyntaxNode(){
    return  dynamic_cast <expression::AssignmentExpressionSyntax*>( createNode(ndkAssignmentExpressionSyntax));
  }

  expression::AwaitExpressionSyntax* Factory::createAwaitExpressionSyntaxNode(){
    return  dynamic_cast <expression::AwaitExpressionSyntax*>( createNode(ndkAwaitExpressionSyntax));
  }

  expression::BaseExpressionSyntax* Factory::createBaseExpressionSyntaxNode(){
    return  dynamic_cast <expression::BaseExpressionSyntax*>( createNode(ndkBaseExpressionSyntax));
  }

  expression::BinaryExpressionSyntax* Factory::createBinaryExpressionSyntaxNode(){
    return  dynamic_cast <expression::BinaryExpressionSyntax*>( createNode(ndkBinaryExpressionSyntax));
  }

  expression::CastExpressionSyntax* Factory::createCastExpressionSyntaxNode(){
    return  dynamic_cast <expression::CastExpressionSyntax*>( createNode(ndkCastExpressionSyntax));
  }

  expression::CheckedExpressionSyntax* Factory::createCheckedExpressionSyntaxNode(){
    return  dynamic_cast <expression::CheckedExpressionSyntax*>( createNode(ndkCheckedExpressionSyntax));
  }

  expression::ConditionalAccessExpressionSyntax* Factory::createConditionalAccessExpressionSyntaxNode(){
    return  dynamic_cast <expression::ConditionalAccessExpressionSyntax*>( createNode(ndkConditionalAccessExpressionSyntax));
  }

  expression::ConditionalExpressionSyntax* Factory::createConditionalExpressionSyntaxNode(){
    return  dynamic_cast <expression::ConditionalExpressionSyntax*>( createNode(ndkConditionalExpressionSyntax));
  }

  expression::DeclarationExpressionSyntax* Factory::createDeclarationExpressionSyntaxNode(){
    return  dynamic_cast <expression::DeclarationExpressionSyntax*>( createNode(ndkDeclarationExpressionSyntax));
  }

  expression::DefaultExpressionSyntax* Factory::createDefaultExpressionSyntaxNode(){
    return  dynamic_cast <expression::DefaultExpressionSyntax*>( createNode(ndkDefaultExpressionSyntax));
  }

  expression::ElementAccessExpressionSyntax* Factory::createElementAccessExpressionSyntaxNode(){
    return  dynamic_cast <expression::ElementAccessExpressionSyntax*>( createNode(ndkElementAccessExpressionSyntax));
  }

  expression::ElementBindingExpressionSyntax* Factory::createElementBindingExpressionSyntaxNode(){
    return  dynamic_cast <expression::ElementBindingExpressionSyntax*>( createNode(ndkElementBindingExpressionSyntax));
  }

  expression::GenericNameSyntax* Factory::createGenericNameSyntaxNode(){
    return  dynamic_cast <expression::GenericNameSyntax*>( createNode(ndkGenericNameSyntax));
  }

  expression::IdentifierNameSyntax* Factory::createIdentifierNameSyntaxNode(){
    return  dynamic_cast <expression::IdentifierNameSyntax*>( createNode(ndkIdentifierNameSyntax));
  }

  expression::ImplicitArrayCreationExpressionSyntax* Factory::createImplicitArrayCreationExpressionSyntaxNode(){
    return  dynamic_cast <expression::ImplicitArrayCreationExpressionSyntax*>( createNode(ndkImplicitArrayCreationExpressionSyntax));
  }

  expression::ImplicitElementAccessSyntax* Factory::createImplicitElementAccessSyntaxNode(){
    return  dynamic_cast <expression::ImplicitElementAccessSyntax*>( createNode(ndkImplicitElementAccessSyntax));
  }

  expression::ImplicitStackAllocArrayCreationExpressionSyntax* Factory::createImplicitStackAllocArrayCreationExpressionSyntaxNode(){
    return  dynamic_cast <expression::ImplicitStackAllocArrayCreationExpressionSyntax*>( createNode(ndkImplicitStackAllocArrayCreationExpressionSyntax));
  }

  expression::InitializerExpressionSyntax* Factory::createInitializerExpressionSyntaxNode(){
    return  dynamic_cast <expression::InitializerExpressionSyntax*>( createNode(ndkInitializerExpressionSyntax));
  }

  expression::InterpolatedStringExpressionSyntax* Factory::createInterpolatedStringExpressionSyntaxNode(){
    return  dynamic_cast <expression::InterpolatedStringExpressionSyntax*>( createNode(ndkInterpolatedStringExpressionSyntax));
  }

  expression::InvocationExpressionSyntax* Factory::createInvocationExpressionSyntaxNode(){
    return  dynamic_cast <expression::InvocationExpressionSyntax*>( createNode(ndkInvocationExpressionSyntax));
  }

  expression::IsPatternExpressionSyntax* Factory::createIsPatternExpressionSyntaxNode(){
    return  dynamic_cast <expression::IsPatternExpressionSyntax*>( createNode(ndkIsPatternExpressionSyntax));
  }

  expression::LiteralExpressionSyntax* Factory::createLiteralExpressionSyntaxNode(){
    return  dynamic_cast <expression::LiteralExpressionSyntax*>( createNode(ndkLiteralExpressionSyntax));
  }

  expression::MakeRefExpressionSyntax* Factory::createMakeRefExpressionSyntaxNode(){
    return  dynamic_cast <expression::MakeRefExpressionSyntax*>( createNode(ndkMakeRefExpressionSyntax));
  }

  expression::MemberAccessExpressionSyntax* Factory::createMemberAccessExpressionSyntaxNode(){
    return  dynamic_cast <expression::MemberAccessExpressionSyntax*>( createNode(ndkMemberAccessExpressionSyntax));
  }

  expression::MemberBindingExpressionSyntax* Factory::createMemberBindingExpressionSyntaxNode(){
    return  dynamic_cast <expression::MemberBindingExpressionSyntax*>( createNode(ndkMemberBindingExpressionSyntax));
  }

  expression::NullableTypeSyntax* Factory::createNullableTypeSyntaxNode(){
    return  dynamic_cast <expression::NullableTypeSyntax*>( createNode(ndkNullableTypeSyntax));
  }

  expression::ObjectCreationExpressionSyntax* Factory::createObjectCreationExpressionSyntaxNode(){
    return  dynamic_cast <expression::ObjectCreationExpressionSyntax*>( createNode(ndkObjectCreationExpressionSyntax));
  }

  expression::OmittedArraySizeExpressionSyntax* Factory::createOmittedArraySizeExpressionSyntaxNode(){
    return  dynamic_cast <expression::OmittedArraySizeExpressionSyntax*>( createNode(ndkOmittedArraySizeExpressionSyntax));
  }

  expression::OmittedTypeArgumentSyntax* Factory::createOmittedTypeArgumentSyntaxNode(){
    return  dynamic_cast <expression::OmittedTypeArgumentSyntax*>( createNode(ndkOmittedTypeArgumentSyntax));
  }

  expression::ParenthesizedExpressionSyntax* Factory::createParenthesizedExpressionSyntaxNode(){
    return  dynamic_cast <expression::ParenthesizedExpressionSyntax*>( createNode(ndkParenthesizedExpressionSyntax));
  }

  expression::ParenthesizedLambdaExpressionSyntax* Factory::createParenthesizedLambdaExpressionSyntaxNode(){
    return  dynamic_cast <expression::ParenthesizedLambdaExpressionSyntax*>( createNode(ndkParenthesizedLambdaExpressionSyntax));
  }

  expression::PointerTypeSyntax* Factory::createPointerTypeSyntaxNode(){
    return  dynamic_cast <expression::PointerTypeSyntax*>( createNode(ndkPointerTypeSyntax));
  }

  expression::PostfixUnaryExpressionSyntax* Factory::createPostfixUnaryExpressionSyntaxNode(){
    return  dynamic_cast <expression::PostfixUnaryExpressionSyntax*>( createNode(ndkPostfixUnaryExpressionSyntax));
  }

  expression::PredefinedTypeSyntax* Factory::createPredefinedTypeSyntaxNode(){
    return  dynamic_cast <expression::PredefinedTypeSyntax*>( createNode(ndkPredefinedTypeSyntax));
  }

  expression::PrefixUnaryExpressionSyntax* Factory::createPrefixUnaryExpressionSyntaxNode(){
    return  dynamic_cast <expression::PrefixUnaryExpressionSyntax*>( createNode(ndkPrefixUnaryExpressionSyntax));
  }

  expression::QualifiedNameSyntax* Factory::createQualifiedNameSyntaxNode(){
    return  dynamic_cast <expression::QualifiedNameSyntax*>( createNode(ndkQualifiedNameSyntax));
  }

  expression::QueryExpressionSyntax* Factory::createQueryExpressionSyntaxNode(){
    return  dynamic_cast <expression::QueryExpressionSyntax*>( createNode(ndkQueryExpressionSyntax));
  }

  expression::RangeExpressionSyntax* Factory::createRangeExpressionSyntaxNode(){
    return  dynamic_cast <expression::RangeExpressionSyntax*>( createNode(ndkRangeExpressionSyntax));
  }

  expression::RefExpressionSyntax* Factory::createRefExpressionSyntaxNode(){
    return  dynamic_cast <expression::RefExpressionSyntax*>( createNode(ndkRefExpressionSyntax));
  }

  expression::RefTypeExpressionSyntax* Factory::createRefTypeExpressionSyntaxNode(){
    return  dynamic_cast <expression::RefTypeExpressionSyntax*>( createNode(ndkRefTypeExpressionSyntax));
  }

  expression::RefTypeSyntax* Factory::createRefTypeSyntaxNode(){
    return  dynamic_cast <expression::RefTypeSyntax*>( createNode(ndkRefTypeSyntax));
  }

  expression::RefValueExpressionSyntax* Factory::createRefValueExpressionSyntaxNode(){
    return  dynamic_cast <expression::RefValueExpressionSyntax*>( createNode(ndkRefValueExpressionSyntax));
  }

  expression::SimpleLambdaExpressionSyntax* Factory::createSimpleLambdaExpressionSyntaxNode(){
    return  dynamic_cast <expression::SimpleLambdaExpressionSyntax*>( createNode(ndkSimpleLambdaExpressionSyntax));
  }

  expression::SizeOfExpressionSyntax* Factory::createSizeOfExpressionSyntaxNode(){
    return  dynamic_cast <expression::SizeOfExpressionSyntax*>( createNode(ndkSizeOfExpressionSyntax));
  }

  expression::StackAllocArrayCreationExpressionSyntax* Factory::createStackAllocArrayCreationExpressionSyntaxNode(){
    return  dynamic_cast <expression::StackAllocArrayCreationExpressionSyntax*>( createNode(ndkStackAllocArrayCreationExpressionSyntax));
  }

  expression::SwitchExpressionSyntax* Factory::createSwitchExpressionSyntaxNode(){
    return  dynamic_cast <expression::SwitchExpressionSyntax*>( createNode(ndkSwitchExpressionSyntax));
  }

  expression::ThisExpressionSyntax* Factory::createThisExpressionSyntaxNode(){
    return  dynamic_cast <expression::ThisExpressionSyntax*>( createNode(ndkThisExpressionSyntax));
  }

  expression::ThrowExpressionSyntax* Factory::createThrowExpressionSyntaxNode(){
    return  dynamic_cast <expression::ThrowExpressionSyntax*>( createNode(ndkThrowExpressionSyntax));
  }

  expression::TupleExpressionSyntax* Factory::createTupleExpressionSyntaxNode(){
    return  dynamic_cast <expression::TupleExpressionSyntax*>( createNode(ndkTupleExpressionSyntax));
  }

  expression::TupleTypeSyntax* Factory::createTupleTypeSyntaxNode(){
    return  dynamic_cast <expression::TupleTypeSyntax*>( createNode(ndkTupleTypeSyntax));
  }

  expression::TypeOfExpressionSyntax* Factory::createTypeOfExpressionSyntaxNode(){
    return  dynamic_cast <expression::TypeOfExpressionSyntax*>( createNode(ndkTypeOfExpressionSyntax));
  }

  statement::BlockSyntax* Factory::createBlockSyntaxNode(){
    return  dynamic_cast <statement::BlockSyntax*>( createNode(ndkBlockSyntax));
  }

  statement::BreakStatementSyntax* Factory::createBreakStatementSyntaxNode(){
    return  dynamic_cast <statement::BreakStatementSyntax*>( createNode(ndkBreakStatementSyntax));
  }

  statement::CheckedStatementSyntax* Factory::createCheckedStatementSyntaxNode(){
    return  dynamic_cast <statement::CheckedStatementSyntax*>( createNode(ndkCheckedStatementSyntax));
  }

  statement::ContinueStatementSyntax* Factory::createContinueStatementSyntaxNode(){
    return  dynamic_cast <statement::ContinueStatementSyntax*>( createNode(ndkContinueStatementSyntax));
  }

  statement::DoStatementSyntax* Factory::createDoStatementSyntaxNode(){
    return  dynamic_cast <statement::DoStatementSyntax*>( createNode(ndkDoStatementSyntax));
  }

  statement::EmptyStatementSyntax* Factory::createEmptyStatementSyntaxNode(){
    return  dynamic_cast <statement::EmptyStatementSyntax*>( createNode(ndkEmptyStatementSyntax));
  }

  statement::ExpressionStatementSyntax* Factory::createExpressionStatementSyntaxNode(){
    return  dynamic_cast <statement::ExpressionStatementSyntax*>( createNode(ndkExpressionStatementSyntax));
  }

  statement::FixedStatementSyntax* Factory::createFixedStatementSyntaxNode(){
    return  dynamic_cast <statement::FixedStatementSyntax*>( createNode(ndkFixedStatementSyntax));
  }

  statement::ForEachStatementSyntax* Factory::createForEachStatementSyntaxNode(){
    return  dynamic_cast <statement::ForEachStatementSyntax*>( createNode(ndkForEachStatementSyntax));
  }

  statement::ForEachVariableStatementSyntax* Factory::createForEachVariableStatementSyntaxNode(){
    return  dynamic_cast <statement::ForEachVariableStatementSyntax*>( createNode(ndkForEachVariableStatementSyntax));
  }

  statement::ForStatementSyntax* Factory::createForStatementSyntaxNode(){
    return  dynamic_cast <statement::ForStatementSyntax*>( createNode(ndkForStatementSyntax));
  }

  statement::GotoStatementSyntax* Factory::createGotoStatementSyntaxNode(){
    return  dynamic_cast <statement::GotoStatementSyntax*>( createNode(ndkGotoStatementSyntax));
  }

  statement::IfStatementSyntax* Factory::createIfStatementSyntaxNode(){
    return  dynamic_cast <statement::IfStatementSyntax*>( createNode(ndkIfStatementSyntax));
  }

  statement::LabeledStatementSyntax* Factory::createLabeledStatementSyntaxNode(){
    return  dynamic_cast <statement::LabeledStatementSyntax*>( createNode(ndkLabeledStatementSyntax));
  }

  statement::LocalDeclarationStatementSyntax* Factory::createLocalDeclarationStatementSyntaxNode(){
    return  dynamic_cast <statement::LocalDeclarationStatementSyntax*>( createNode(ndkLocalDeclarationStatementSyntax));
  }

  statement::LocalFunctionStatementSyntax* Factory::createLocalFunctionStatementSyntaxNode(){
    return  dynamic_cast <statement::LocalFunctionStatementSyntax*>( createNode(ndkLocalFunctionStatementSyntax));
  }

  statement::LockStatementSyntax* Factory::createLockStatementSyntaxNode(){
    return  dynamic_cast <statement::LockStatementSyntax*>( createNode(ndkLockStatementSyntax));
  }

  statement::ReturnStatementSyntax* Factory::createReturnStatementSyntaxNode(){
    return  dynamic_cast <statement::ReturnStatementSyntax*>( createNode(ndkReturnStatementSyntax));
  }

  statement::SwitchStatementSyntax* Factory::createSwitchStatementSyntaxNode(){
    return  dynamic_cast <statement::SwitchStatementSyntax*>( createNode(ndkSwitchStatementSyntax));
  }

  statement::ThrowStatementSyntax* Factory::createThrowStatementSyntaxNode(){
    return  dynamic_cast <statement::ThrowStatementSyntax*>( createNode(ndkThrowStatementSyntax));
  }

  statement::TryStatementSyntax* Factory::createTryStatementSyntaxNode(){
    return  dynamic_cast <statement::TryStatementSyntax*>( createNode(ndkTryStatementSyntax));
  }

  statement::UnsafeStatementSyntax* Factory::createUnsafeStatementSyntaxNode(){
    return  dynamic_cast <statement::UnsafeStatementSyntax*>( createNode(ndkUnsafeStatementSyntax));
  }

  statement::UsingStatementSyntax* Factory::createUsingStatementSyntaxNode(){
    return  dynamic_cast <statement::UsingStatementSyntax*>( createNode(ndkUsingStatementSyntax));
  }

  statement::WhileStatementSyntax* Factory::createWhileStatementSyntaxNode(){
    return  dynamic_cast <statement::WhileStatementSyntax*>( createNode(ndkWhileStatementSyntax));
  }

  statement::YieldStatementSyntax* Factory::createYieldStatementSyntaxNode(){
    return  dynamic_cast <statement::YieldStatementSyntax*>( createNode(ndkYieldStatementSyntax));
  }

  structure::AccessorDeclarationSyntax* Factory::createAccessorDeclarationSyntaxNode(){
    return  dynamic_cast <structure::AccessorDeclarationSyntax*>( createNode(ndkAccessorDeclarationSyntax));
  }

  structure::AccessorListSyntax* Factory::createAccessorListSyntaxNode(){
    return  dynamic_cast <structure::AccessorListSyntax*>( createNode(ndkAccessorListSyntax));
  }

  structure::AnonymousObjectMemberDeclaratorSyntax* Factory::createAnonymousObjectMemberDeclaratorSyntaxNode(){
    return  dynamic_cast <structure::AnonymousObjectMemberDeclaratorSyntax*>( createNode(ndkAnonymousObjectMemberDeclaratorSyntax));
  }

  structure::ArgumentListSyntax* Factory::createArgumentListSyntaxNode(){
    return  dynamic_cast <structure::ArgumentListSyntax*>( createNode(ndkArgumentListSyntax));
  }

  structure::ArgumentSyntax* Factory::createArgumentSyntaxNode(){
    return  dynamic_cast <structure::ArgumentSyntax*>( createNode(ndkArgumentSyntax));
  }

  structure::ArrayRankSpecifierSyntax* Factory::createArrayRankSpecifierSyntaxNode(){
    return  dynamic_cast <structure::ArrayRankSpecifierSyntax*>( createNode(ndkArrayRankSpecifierSyntax));
  }

  structure::ArrowExpressionClauseSyntax* Factory::createArrowExpressionClauseSyntaxNode(){
    return  dynamic_cast <structure::ArrowExpressionClauseSyntax*>( createNode(ndkArrowExpressionClauseSyntax));
  }

  structure::AttributeArgumentListSyntax* Factory::createAttributeArgumentListSyntaxNode(){
    return  dynamic_cast <structure::AttributeArgumentListSyntax*>( createNode(ndkAttributeArgumentListSyntax));
  }

  structure::AttributeArgumentSyntax* Factory::createAttributeArgumentSyntaxNode(){
    return  dynamic_cast <structure::AttributeArgumentSyntax*>( createNode(ndkAttributeArgumentSyntax));
  }

  structure::AttributeListSyntax* Factory::createAttributeListSyntaxNode(){
    return  dynamic_cast <structure::AttributeListSyntax*>( createNode(ndkAttributeListSyntax));
  }

  structure::AttributeSyntax* Factory::createAttributeSyntaxNode(){
    return  dynamic_cast <structure::AttributeSyntax*>( createNode(ndkAttributeSyntax));
  }

  structure::AttributeTargetSpecifierSyntax* Factory::createAttributeTargetSpecifierSyntaxNode(){
    return  dynamic_cast <structure::AttributeTargetSpecifierSyntax*>( createNode(ndkAttributeTargetSpecifierSyntax));
  }

  structure::BaseListSyntax* Factory::createBaseListSyntaxNode(){
    return  dynamic_cast <structure::BaseListSyntax*>( createNode(ndkBaseListSyntax));
  }

  structure::BracketedArgumentListSyntax* Factory::createBracketedArgumentListSyntaxNode(){
    return  dynamic_cast <structure::BracketedArgumentListSyntax*>( createNode(ndkBracketedArgumentListSyntax));
  }

  structure::BracketedParameterListSyntax* Factory::createBracketedParameterListSyntaxNode(){
    return  dynamic_cast <structure::BracketedParameterListSyntax*>( createNode(ndkBracketedParameterListSyntax));
  }

  structure::CasePatternSwitchLabelSyntax* Factory::createCasePatternSwitchLabelSyntaxNode(){
    return  dynamic_cast <structure::CasePatternSwitchLabelSyntax*>( createNode(ndkCasePatternSwitchLabelSyntax));
  }

  structure::CaseSwitchLabelSyntax* Factory::createCaseSwitchLabelSyntaxNode(){
    return  dynamic_cast <structure::CaseSwitchLabelSyntax*>( createNode(ndkCaseSwitchLabelSyntax));
  }

  structure::CatchClauseSyntax* Factory::createCatchClauseSyntaxNode(){
    return  dynamic_cast <structure::CatchClauseSyntax*>( createNode(ndkCatchClauseSyntax));
  }

  structure::CatchDeclarationSyntax* Factory::createCatchDeclarationSyntaxNode(){
    return  dynamic_cast <structure::CatchDeclarationSyntax*>( createNode(ndkCatchDeclarationSyntax));
  }

  structure::CatchFilterClauseSyntax* Factory::createCatchFilterClauseSyntaxNode(){
    return  dynamic_cast <structure::CatchFilterClauseSyntax*>( createNode(ndkCatchFilterClauseSyntax));
  }

  structure::ClassDeclarationSyntax* Factory::createClassDeclarationSyntaxNode(){
    return  dynamic_cast <structure::ClassDeclarationSyntax*>( createNode(ndkClassDeclarationSyntax));
  }

  structure::ClassOrStructConstraintSyntax* Factory::createClassOrStructConstraintSyntaxNode(){
    return  dynamic_cast <structure::ClassOrStructConstraintSyntax*>( createNode(ndkClassOrStructConstraintSyntax));
  }

  structure::CompilationUnitSyntax* Factory::createCompilationUnitSyntaxNode(){
    return  dynamic_cast <structure::CompilationUnitSyntax*>( createNode(ndkCompilationUnitSyntax));
  }

  structure::ConstantPatternSyntax* Factory::createConstantPatternSyntaxNode(){
    return  dynamic_cast <structure::ConstantPatternSyntax*>( createNode(ndkConstantPatternSyntax));
  }

  structure::ConstructorConstraintSyntax* Factory::createConstructorConstraintSyntaxNode(){
    return  dynamic_cast <structure::ConstructorConstraintSyntax*>( createNode(ndkConstructorConstraintSyntax));
  }

  structure::ConstructorDeclarationSyntax* Factory::createConstructorDeclarationSyntaxNode(){
    return  dynamic_cast <structure::ConstructorDeclarationSyntax*>( createNode(ndkConstructorDeclarationSyntax));
  }

  structure::ConstructorInitializerSyntax* Factory::createConstructorInitializerSyntaxNode(){
    return  dynamic_cast <structure::ConstructorInitializerSyntax*>( createNode(ndkConstructorInitializerSyntax));
  }

  structure::ConversionOperatorDeclarationSyntax* Factory::createConversionOperatorDeclarationSyntaxNode(){
    return  dynamic_cast <structure::ConversionOperatorDeclarationSyntax*>( createNode(ndkConversionOperatorDeclarationSyntax));
  }

  structure::ConversionOperatorMemberCrefSyntax* Factory::createConversionOperatorMemberCrefSyntaxNode(){
    return  dynamic_cast <structure::ConversionOperatorMemberCrefSyntax*>( createNode(ndkConversionOperatorMemberCrefSyntax));
  }

  structure::CrefBracketedParameterListSyntax* Factory::createCrefBracketedParameterListSyntaxNode(){
    return  dynamic_cast <structure::CrefBracketedParameterListSyntax*>( createNode(ndkCrefBracketedParameterListSyntax));
  }

  structure::CrefParameterListSyntax* Factory::createCrefParameterListSyntaxNode(){
    return  dynamic_cast <structure::CrefParameterListSyntax*>( createNode(ndkCrefParameterListSyntax));
  }

  structure::CrefParameterSyntax* Factory::createCrefParameterSyntaxNode(){
    return  dynamic_cast <structure::CrefParameterSyntax*>( createNode(ndkCrefParameterSyntax));
  }

  structure::DeclarationPatternSyntax* Factory::createDeclarationPatternSyntaxNode(){
    return  dynamic_cast <structure::DeclarationPatternSyntax*>( createNode(ndkDeclarationPatternSyntax));
  }

  structure::DefaultSwitchLabelSyntax* Factory::createDefaultSwitchLabelSyntaxNode(){
    return  dynamic_cast <structure::DefaultSwitchLabelSyntax*>( createNode(ndkDefaultSwitchLabelSyntax));
  }

  structure::DelegateDeclarationSyntax* Factory::createDelegateDeclarationSyntaxNode(){
    return  dynamic_cast <structure::DelegateDeclarationSyntax*>( createNode(ndkDelegateDeclarationSyntax));
  }

  structure::DestructorDeclarationSyntax* Factory::createDestructorDeclarationSyntaxNode(){
    return  dynamic_cast <structure::DestructorDeclarationSyntax*>( createNode(ndkDestructorDeclarationSyntax));
  }

  structure::DiscardDesignationSyntax* Factory::createDiscardDesignationSyntaxNode(){
    return  dynamic_cast <structure::DiscardDesignationSyntax*>( createNode(ndkDiscardDesignationSyntax));
  }

  structure::DiscardPatternSyntax* Factory::createDiscardPatternSyntaxNode(){
    return  dynamic_cast <structure::DiscardPatternSyntax*>( createNode(ndkDiscardPatternSyntax));
  }

  structure::ElseClauseSyntax* Factory::createElseClauseSyntaxNode(){
    return  dynamic_cast <structure::ElseClauseSyntax*>( createNode(ndkElseClauseSyntax));
  }

  structure::EnumDeclarationSyntax* Factory::createEnumDeclarationSyntaxNode(){
    return  dynamic_cast <structure::EnumDeclarationSyntax*>( createNode(ndkEnumDeclarationSyntax));
  }

  structure::EnumMemberDeclarationSyntax* Factory::createEnumMemberDeclarationSyntaxNode(){
    return  dynamic_cast <structure::EnumMemberDeclarationSyntax*>( createNode(ndkEnumMemberDeclarationSyntax));
  }

  structure::EqualsValueClauseSyntax* Factory::createEqualsValueClauseSyntaxNode(){
    return  dynamic_cast <structure::EqualsValueClauseSyntax*>( createNode(ndkEqualsValueClauseSyntax));
  }

  structure::EventDeclarationSyntax* Factory::createEventDeclarationSyntaxNode(){
    return  dynamic_cast <structure::EventDeclarationSyntax*>( createNode(ndkEventDeclarationSyntax));
  }

  structure::EventFieldDeclarationSyntax* Factory::createEventFieldDeclarationSyntaxNode(){
    return  dynamic_cast <structure::EventFieldDeclarationSyntax*>( createNode(ndkEventFieldDeclarationSyntax));
  }

  structure::ExplicitInterfaceSpecifierSyntax* Factory::createExplicitInterfaceSpecifierSyntaxNode(){
    return  dynamic_cast <structure::ExplicitInterfaceSpecifierSyntax*>( createNode(ndkExplicitInterfaceSpecifierSyntax));
  }

  structure::ExternAliasDirectiveSyntax* Factory::createExternAliasDirectiveSyntaxNode(){
    return  dynamic_cast <structure::ExternAliasDirectiveSyntax*>( createNode(ndkExternAliasDirectiveSyntax));
  }

  structure::FieldDeclarationSyntax* Factory::createFieldDeclarationSyntaxNode(){
    return  dynamic_cast <structure::FieldDeclarationSyntax*>( createNode(ndkFieldDeclarationSyntax));
  }

  structure::FinallyClauseSyntax* Factory::createFinallyClauseSyntaxNode(){
    return  dynamic_cast <structure::FinallyClauseSyntax*>( createNode(ndkFinallyClauseSyntax));
  }

  structure::FromClauseSyntax* Factory::createFromClauseSyntaxNode(){
    return  dynamic_cast <structure::FromClauseSyntax*>( createNode(ndkFromClauseSyntax));
  }

  structure::GlobalStatementSyntax* Factory::createGlobalStatementSyntaxNode(){
    return  dynamic_cast <structure::GlobalStatementSyntax*>( createNode(ndkGlobalStatementSyntax));
  }

  structure::GroupClauseSyntax* Factory::createGroupClauseSyntaxNode(){
    return  dynamic_cast <structure::GroupClauseSyntax*>( createNode(ndkGroupClauseSyntax));
  }

  structure::IncompleteMemberSyntax* Factory::createIncompleteMemberSyntaxNode(){
    return  dynamic_cast <structure::IncompleteMemberSyntax*>( createNode(ndkIncompleteMemberSyntax));
  }

  structure::IndexerDeclarationSyntax* Factory::createIndexerDeclarationSyntaxNode(){
    return  dynamic_cast <structure::IndexerDeclarationSyntax*>( createNode(ndkIndexerDeclarationSyntax));
  }

  structure::IndexerMemberCrefSyntax* Factory::createIndexerMemberCrefSyntaxNode(){
    return  dynamic_cast <structure::IndexerMemberCrefSyntax*>( createNode(ndkIndexerMemberCrefSyntax));
  }

  structure::InterfaceDeclarationSyntax* Factory::createInterfaceDeclarationSyntaxNode(){
    return  dynamic_cast <structure::InterfaceDeclarationSyntax*>( createNode(ndkInterfaceDeclarationSyntax));
  }

  structure::InterpolatedStringTextSyntax* Factory::createInterpolatedStringTextSyntaxNode(){
    return  dynamic_cast <structure::InterpolatedStringTextSyntax*>( createNode(ndkInterpolatedStringTextSyntax));
  }

  structure::InterpolationAlignmentClauseSyntax* Factory::createInterpolationAlignmentClauseSyntaxNode(){
    return  dynamic_cast <structure::InterpolationAlignmentClauseSyntax*>( createNode(ndkInterpolationAlignmentClauseSyntax));
  }

  structure::InterpolationFormatClauseSyntax* Factory::createInterpolationFormatClauseSyntaxNode(){
    return  dynamic_cast <structure::InterpolationFormatClauseSyntax*>( createNode(ndkInterpolationFormatClauseSyntax));
  }

  structure::InterpolationSyntax* Factory::createInterpolationSyntaxNode(){
    return  dynamic_cast <structure::InterpolationSyntax*>( createNode(ndkInterpolationSyntax));
  }

  structure::JoinClauseSyntax* Factory::createJoinClauseSyntaxNode(){
    return  dynamic_cast <structure::JoinClauseSyntax*>( createNode(ndkJoinClauseSyntax));
  }

  structure::JoinIntoClauseSyntax* Factory::createJoinIntoClauseSyntaxNode(){
    return  dynamic_cast <structure::JoinIntoClauseSyntax*>( createNode(ndkJoinIntoClauseSyntax));
  }

  structure::LetClauseSyntax* Factory::createLetClauseSyntaxNode(){
    return  dynamic_cast <structure::LetClauseSyntax*>( createNode(ndkLetClauseSyntax));
  }

  structure::MethodDeclarationSyntax* Factory::createMethodDeclarationSyntaxNode(){
    return  dynamic_cast <structure::MethodDeclarationSyntax*>( createNode(ndkMethodDeclarationSyntax));
  }

  structure::NameColonSyntax* Factory::createNameColonSyntaxNode(){
    return  dynamic_cast <structure::NameColonSyntax*>( createNode(ndkNameColonSyntax));
  }

  structure::NameEqualsSyntax* Factory::createNameEqualsSyntaxNode(){
    return  dynamic_cast <structure::NameEqualsSyntax*>( createNode(ndkNameEqualsSyntax));
  }

  structure::NameMemberCrefSyntax* Factory::createNameMemberCrefSyntaxNode(){
    return  dynamic_cast <structure::NameMemberCrefSyntax*>( createNode(ndkNameMemberCrefSyntax));
  }

  structure::NamespaceDeclarationSyntax* Factory::createNamespaceDeclarationSyntaxNode(){
    return  dynamic_cast <structure::NamespaceDeclarationSyntax*>( createNode(ndkNamespaceDeclarationSyntax));
  }

  structure::OperatorDeclarationSyntax* Factory::createOperatorDeclarationSyntaxNode(){
    return  dynamic_cast <structure::OperatorDeclarationSyntax*>( createNode(ndkOperatorDeclarationSyntax));
  }

  structure::OperatorMemberCrefSyntax* Factory::createOperatorMemberCrefSyntaxNode(){
    return  dynamic_cast <structure::OperatorMemberCrefSyntax*>( createNode(ndkOperatorMemberCrefSyntax));
  }

  structure::OrderByClauseSyntax* Factory::createOrderByClauseSyntaxNode(){
    return  dynamic_cast <structure::OrderByClauseSyntax*>( createNode(ndkOrderByClauseSyntax));
  }

  structure::OrderingSyntax* Factory::createOrderingSyntaxNode(){
    return  dynamic_cast <structure::OrderingSyntax*>( createNode(ndkOrderingSyntax));
  }

  structure::ParameterListSyntax* Factory::createParameterListSyntaxNode(){
    return  dynamic_cast <structure::ParameterListSyntax*>( createNode(ndkParameterListSyntax));
  }

  structure::ParameterSyntax* Factory::createParameterSyntaxNode(){
    return  dynamic_cast <structure::ParameterSyntax*>( createNode(ndkParameterSyntax));
  }

  structure::ParenthesizedVariableDesignationSyntax* Factory::createParenthesizedVariableDesignationSyntaxNode(){
    return  dynamic_cast <structure::ParenthesizedVariableDesignationSyntax*>( createNode(ndkParenthesizedVariableDesignationSyntax));
  }

  structure::PositionalPatternClauseSyntax* Factory::createPositionalPatternClauseSyntaxNode(){
    return  dynamic_cast <structure::PositionalPatternClauseSyntax*>( createNode(ndkPositionalPatternClauseSyntax));
  }

  structure::PropertyDeclarationSyntax* Factory::createPropertyDeclarationSyntaxNode(){
    return  dynamic_cast <structure::PropertyDeclarationSyntax*>( createNode(ndkPropertyDeclarationSyntax));
  }

  structure::PropertyPatternClauseSyntax* Factory::createPropertyPatternClauseSyntaxNode(){
    return  dynamic_cast <structure::PropertyPatternClauseSyntax*>( createNode(ndkPropertyPatternClauseSyntax));
  }

  structure::QualifiedCrefSyntax* Factory::createQualifiedCrefSyntaxNode(){
    return  dynamic_cast <structure::QualifiedCrefSyntax*>( createNode(ndkQualifiedCrefSyntax));
  }

  structure::QueryBodySyntax* Factory::createQueryBodySyntaxNode(){
    return  dynamic_cast <structure::QueryBodySyntax*>( createNode(ndkQueryBodySyntax));
  }

  structure::QueryContinuationSyntax* Factory::createQueryContinuationSyntaxNode(){
    return  dynamic_cast <structure::QueryContinuationSyntax*>( createNode(ndkQueryContinuationSyntax));
  }

  structure::RecursivePatternSyntax* Factory::createRecursivePatternSyntaxNode(){
    return  dynamic_cast <structure::RecursivePatternSyntax*>( createNode(ndkRecursivePatternSyntax));
  }

  structure::SelectClauseSyntax* Factory::createSelectClauseSyntaxNode(){
    return  dynamic_cast <structure::SelectClauseSyntax*>( createNode(ndkSelectClauseSyntax));
  }

  structure::SimpleBaseTypeSyntax* Factory::createSimpleBaseTypeSyntaxNode(){
    return  dynamic_cast <structure::SimpleBaseTypeSyntax*>( createNode(ndkSimpleBaseTypeSyntax));
  }

  structure::SingleVariableDesignationSyntax* Factory::createSingleVariableDesignationSyntaxNode(){
    return  dynamic_cast <structure::SingleVariableDesignationSyntax*>( createNode(ndkSingleVariableDesignationSyntax));
  }

  structure::StructDeclarationSyntax* Factory::createStructDeclarationSyntaxNode(){
    return  dynamic_cast <structure::StructDeclarationSyntax*>( createNode(ndkStructDeclarationSyntax));
  }

  structure::SubpatternSyntax* Factory::createSubpatternSyntaxNode(){
    return  dynamic_cast <structure::SubpatternSyntax*>( createNode(ndkSubpatternSyntax));
  }

  structure::SwitchExpressionArmSyntax* Factory::createSwitchExpressionArmSyntaxNode(){
    return  dynamic_cast <structure::SwitchExpressionArmSyntax*>( createNode(ndkSwitchExpressionArmSyntax));
  }

  structure::SwitchSectionSyntax* Factory::createSwitchSectionSyntaxNode(){
    return  dynamic_cast <structure::SwitchSectionSyntax*>( createNode(ndkSwitchSectionSyntax));
  }

  structure::SyntaxToken* Factory::createSyntaxTokenNode(){
    return  dynamic_cast <structure::SyntaxToken*>( createNode(ndkSyntaxToken));
  }

  structure::TupleElementSyntax* Factory::createTupleElementSyntaxNode(){
    return  dynamic_cast <structure::TupleElementSyntax*>( createNode(ndkTupleElementSyntax));
  }

  structure::TypeArgumentListSyntax* Factory::createTypeArgumentListSyntaxNode(){
    return  dynamic_cast <structure::TypeArgumentListSyntax*>( createNode(ndkTypeArgumentListSyntax));
  }

  structure::TypeConstraintSyntax* Factory::createTypeConstraintSyntaxNode(){
    return  dynamic_cast <structure::TypeConstraintSyntax*>( createNode(ndkTypeConstraintSyntax));
  }

  structure::TypeCrefSyntax* Factory::createTypeCrefSyntaxNode(){
    return  dynamic_cast <structure::TypeCrefSyntax*>( createNode(ndkTypeCrefSyntax));
  }

  structure::TypeParameterConstraintClauseSyntax* Factory::createTypeParameterConstraintClauseSyntaxNode(){
    return  dynamic_cast <structure::TypeParameterConstraintClauseSyntax*>( createNode(ndkTypeParameterConstraintClauseSyntax));
  }

  structure::TypeParameterListSyntax* Factory::createTypeParameterListSyntaxNode(){
    return  dynamic_cast <structure::TypeParameterListSyntax*>( createNode(ndkTypeParameterListSyntax));
  }

  structure::TypeParameterSyntax* Factory::createTypeParameterSyntaxNode(){
    return  dynamic_cast <structure::TypeParameterSyntax*>( createNode(ndkTypeParameterSyntax));
  }

  structure::UsingDirectiveSyntax* Factory::createUsingDirectiveSyntaxNode(){
    return  dynamic_cast <structure::UsingDirectiveSyntax*>( createNode(ndkUsingDirectiveSyntax));
  }

  structure::VarPatternSyntax* Factory::createVarPatternSyntaxNode(){
    return  dynamic_cast <structure::VarPatternSyntax*>( createNode(ndkVarPatternSyntax));
  }

  structure::VariableDeclarationSyntax* Factory::createVariableDeclarationSyntaxNode(){
    return  dynamic_cast <structure::VariableDeclarationSyntax*>( createNode(ndkVariableDeclarationSyntax));
  }

  structure::VariableDeclaratorSyntax* Factory::createVariableDeclaratorSyntaxNode(){
    return  dynamic_cast <structure::VariableDeclaratorSyntax*>( createNode(ndkVariableDeclaratorSyntax));
  }

  structure::WhenClauseSyntax* Factory::createWhenClauseSyntaxNode(){
    return  dynamic_cast <structure::WhenClauseSyntax*>( createNode(ndkWhenClauseSyntax));
  }

  structure::WhereClauseSyntax* Factory::createWhereClauseSyntaxNode(){
    return  dynamic_cast <structure::WhereClauseSyntax*>( createNode(ndkWhereClauseSyntax));
  }

  structure::XmlCDataSectionSyntax* Factory::createXmlCDataSectionSyntaxNode(){
    return  dynamic_cast <structure::XmlCDataSectionSyntax*>( createNode(ndkXmlCDataSectionSyntax));
  }

  structure::XmlCommentSyntax* Factory::createXmlCommentSyntaxNode(){
    return  dynamic_cast <structure::XmlCommentSyntax*>( createNode(ndkXmlCommentSyntax));
  }

  structure::XmlCrefAttributeSyntax* Factory::createXmlCrefAttributeSyntaxNode(){
    return  dynamic_cast <structure::XmlCrefAttributeSyntax*>( createNode(ndkXmlCrefAttributeSyntax));
  }

  structure::XmlElementEndTagSyntax* Factory::createXmlElementEndTagSyntaxNode(){
    return  dynamic_cast <structure::XmlElementEndTagSyntax*>( createNode(ndkXmlElementEndTagSyntax));
  }

  structure::XmlElementStartTagSyntax* Factory::createXmlElementStartTagSyntaxNode(){
    return  dynamic_cast <structure::XmlElementStartTagSyntax*>( createNode(ndkXmlElementStartTagSyntax));
  }

  structure::XmlElementSyntax* Factory::createXmlElementSyntaxNode(){
    return  dynamic_cast <structure::XmlElementSyntax*>( createNode(ndkXmlElementSyntax));
  }

  structure::XmlEmptyElementSyntax* Factory::createXmlEmptyElementSyntaxNode(){
    return  dynamic_cast <structure::XmlEmptyElementSyntax*>( createNode(ndkXmlEmptyElementSyntax));
  }

  structure::XmlNameAttributeSyntax* Factory::createXmlNameAttributeSyntaxNode(){
    return  dynamic_cast <structure::XmlNameAttributeSyntax*>( createNode(ndkXmlNameAttributeSyntax));
  }

  structure::XmlNameSyntax* Factory::createXmlNameSyntaxNode(){
    return  dynamic_cast <structure::XmlNameSyntax*>( createNode(ndkXmlNameSyntax));
  }

  structure::XmlPrefixSyntax* Factory::createXmlPrefixSyntaxNode(){
    return  dynamic_cast <structure::XmlPrefixSyntax*>( createNode(ndkXmlPrefixSyntax));
  }

  structure::XmlProcessingInstructionSyntax* Factory::createXmlProcessingInstructionSyntaxNode(){
    return  dynamic_cast <structure::XmlProcessingInstructionSyntax*>( createNode(ndkXmlProcessingInstructionSyntax));
  }

  structure::XmlTextAttributeSyntax* Factory::createXmlTextAttributeSyntaxNode(){
    return  dynamic_cast <structure::XmlTextAttributeSyntax*>( createNode(ndkXmlTextAttributeSyntax));
  }

  structure::XmlTextSyntax* Factory::createXmlTextSyntaxNode(){
    return  dynamic_cast <structure::XmlTextSyntax*>( createNode(ndkXmlTextSyntax));
  }

  void Factory::printNodeSizes() {
    printf("expression::AliasQualifiedNameSyntax node: %dbyte(s)\n",(int)sizeof(expression::AliasQualifiedNameSyntax)); 
    printf("expression::AnonymousMethodExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::AnonymousMethodExpressionSyntax)); 
    printf("expression::AnonymousObjectCreationExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::AnonymousObjectCreationExpressionSyntax)); 
    printf("expression::ArrayCreationExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ArrayCreationExpressionSyntax)); 
    printf("expression::ArrayTypeSyntax node: %dbyte(s)\n",(int)sizeof(expression::ArrayTypeSyntax)); 
    printf("expression::AssignmentExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::AssignmentExpressionSyntax)); 
    printf("expression::AwaitExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::AwaitExpressionSyntax)); 
    printf("expression::BaseExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::BaseExpressionSyntax)); 
    printf("expression::BinaryExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::BinaryExpressionSyntax)); 
    printf("expression::CastExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::CastExpressionSyntax)); 
    printf("expression::CheckedExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::CheckedExpressionSyntax)); 
    printf("expression::ConditionalAccessExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ConditionalAccessExpressionSyntax)); 
    printf("expression::ConditionalExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ConditionalExpressionSyntax)); 
    printf("expression::DeclarationExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::DeclarationExpressionSyntax)); 
    printf("expression::DefaultExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::DefaultExpressionSyntax)); 
    printf("expression::ElementAccessExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ElementAccessExpressionSyntax)); 
    printf("expression::ElementBindingExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ElementBindingExpressionSyntax)); 
    printf("expression::GenericNameSyntax node: %dbyte(s)\n",(int)sizeof(expression::GenericNameSyntax)); 
    printf("expression::IdentifierNameSyntax node: %dbyte(s)\n",(int)sizeof(expression::IdentifierNameSyntax)); 
    printf("expression::ImplicitArrayCreationExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ImplicitArrayCreationExpressionSyntax)); 
    printf("expression::ImplicitElementAccessSyntax node: %dbyte(s)\n",(int)sizeof(expression::ImplicitElementAccessSyntax)); 
    printf("expression::ImplicitStackAllocArrayCreationExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ImplicitStackAllocArrayCreationExpressionSyntax)); 
    printf("expression::InitializerExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::InitializerExpressionSyntax)); 
    printf("expression::InterpolatedStringExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::InterpolatedStringExpressionSyntax)); 
    printf("expression::InvocationExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::InvocationExpressionSyntax)); 
    printf("expression::IsPatternExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::IsPatternExpressionSyntax)); 
    printf("expression::LiteralExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::LiteralExpressionSyntax)); 
    printf("expression::MakeRefExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::MakeRefExpressionSyntax)); 
    printf("expression::MemberAccessExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::MemberAccessExpressionSyntax)); 
    printf("expression::MemberBindingExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::MemberBindingExpressionSyntax)); 
    printf("expression::NullableTypeSyntax node: %dbyte(s)\n",(int)sizeof(expression::NullableTypeSyntax)); 
    printf("expression::ObjectCreationExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ObjectCreationExpressionSyntax)); 
    printf("expression::OmittedArraySizeExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::OmittedArraySizeExpressionSyntax)); 
    printf("expression::OmittedTypeArgumentSyntax node: %dbyte(s)\n",(int)sizeof(expression::OmittedTypeArgumentSyntax)); 
    printf("expression::ParenthesizedExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ParenthesizedExpressionSyntax)); 
    printf("expression::ParenthesizedLambdaExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ParenthesizedLambdaExpressionSyntax)); 
    printf("expression::PointerTypeSyntax node: %dbyte(s)\n",(int)sizeof(expression::PointerTypeSyntax)); 
    printf("expression::PostfixUnaryExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::PostfixUnaryExpressionSyntax)); 
    printf("expression::PredefinedTypeSyntax node: %dbyte(s)\n",(int)sizeof(expression::PredefinedTypeSyntax)); 
    printf("expression::PrefixUnaryExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::PrefixUnaryExpressionSyntax)); 
    printf("expression::QualifiedNameSyntax node: %dbyte(s)\n",(int)sizeof(expression::QualifiedNameSyntax)); 
    printf("expression::QueryExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::QueryExpressionSyntax)); 
    printf("expression::RangeExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::RangeExpressionSyntax)); 
    printf("expression::RefExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::RefExpressionSyntax)); 
    printf("expression::RefTypeExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::RefTypeExpressionSyntax)); 
    printf("expression::RefTypeSyntax node: %dbyte(s)\n",(int)sizeof(expression::RefTypeSyntax)); 
    printf("expression::RefValueExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::RefValueExpressionSyntax)); 
    printf("expression::SimpleLambdaExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::SimpleLambdaExpressionSyntax)); 
    printf("expression::SizeOfExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::SizeOfExpressionSyntax)); 
    printf("expression::StackAllocArrayCreationExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::StackAllocArrayCreationExpressionSyntax)); 
    printf("expression::SwitchExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::SwitchExpressionSyntax)); 
    printf("expression::ThisExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ThisExpressionSyntax)); 
    printf("expression::ThrowExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::ThrowExpressionSyntax)); 
    printf("expression::TupleExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::TupleExpressionSyntax)); 
    printf("expression::TupleTypeSyntax node: %dbyte(s)\n",(int)sizeof(expression::TupleTypeSyntax)); 
    printf("expression::TypeOfExpressionSyntax node: %dbyte(s)\n",(int)sizeof(expression::TypeOfExpressionSyntax)); 
    printf("statement::BlockSyntax node: %dbyte(s)\n",(int)sizeof(statement::BlockSyntax)); 
    printf("statement::BreakStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::BreakStatementSyntax)); 
    printf("statement::CheckedStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::CheckedStatementSyntax)); 
    printf("statement::ContinueStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::ContinueStatementSyntax)); 
    printf("statement::DoStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::DoStatementSyntax)); 
    printf("statement::EmptyStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::EmptyStatementSyntax)); 
    printf("statement::ExpressionStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::ExpressionStatementSyntax)); 
    printf("statement::FixedStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::FixedStatementSyntax)); 
    printf("statement::ForEachStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::ForEachStatementSyntax)); 
    printf("statement::ForEachVariableStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::ForEachVariableStatementSyntax)); 
    printf("statement::ForStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::ForStatementSyntax)); 
    printf("statement::GotoStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::GotoStatementSyntax)); 
    printf("statement::IfStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::IfStatementSyntax)); 
    printf("statement::LabeledStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::LabeledStatementSyntax)); 
    printf("statement::LocalDeclarationStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::LocalDeclarationStatementSyntax)); 
    printf("statement::LocalFunctionStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::LocalFunctionStatementSyntax)); 
    printf("statement::LockStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::LockStatementSyntax)); 
    printf("statement::ReturnStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::ReturnStatementSyntax)); 
    printf("statement::SwitchStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::SwitchStatementSyntax)); 
    printf("statement::ThrowStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::ThrowStatementSyntax)); 
    printf("statement::TryStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::TryStatementSyntax)); 
    printf("statement::UnsafeStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::UnsafeStatementSyntax)); 
    printf("statement::UsingStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::UsingStatementSyntax)); 
    printf("statement::WhileStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::WhileStatementSyntax)); 
    printf("statement::YieldStatementSyntax node: %dbyte(s)\n",(int)sizeof(statement::YieldStatementSyntax)); 
    printf("structure::AccessorDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::AccessorDeclarationSyntax)); 
    printf("structure::AccessorListSyntax node: %dbyte(s)\n",(int)sizeof(structure::AccessorListSyntax)); 
    printf("structure::AnonymousObjectMemberDeclaratorSyntax node: %dbyte(s)\n",(int)sizeof(structure::AnonymousObjectMemberDeclaratorSyntax)); 
    printf("structure::ArgumentListSyntax node: %dbyte(s)\n",(int)sizeof(structure::ArgumentListSyntax)); 
    printf("structure::ArgumentSyntax node: %dbyte(s)\n",(int)sizeof(structure::ArgumentSyntax)); 
    printf("structure::ArrayRankSpecifierSyntax node: %dbyte(s)\n",(int)sizeof(structure::ArrayRankSpecifierSyntax)); 
    printf("structure::ArrowExpressionClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::ArrowExpressionClauseSyntax)); 
    printf("structure::AttributeArgumentListSyntax node: %dbyte(s)\n",(int)sizeof(structure::AttributeArgumentListSyntax)); 
    printf("structure::AttributeArgumentSyntax node: %dbyte(s)\n",(int)sizeof(structure::AttributeArgumentSyntax)); 
    printf("structure::AttributeListSyntax node: %dbyte(s)\n",(int)sizeof(structure::AttributeListSyntax)); 
    printf("structure::AttributeSyntax node: %dbyte(s)\n",(int)sizeof(structure::AttributeSyntax)); 
    printf("structure::AttributeTargetSpecifierSyntax node: %dbyte(s)\n",(int)sizeof(structure::AttributeTargetSpecifierSyntax)); 
    printf("structure::BaseListSyntax node: %dbyte(s)\n",(int)sizeof(structure::BaseListSyntax)); 
    printf("structure::BracketedArgumentListSyntax node: %dbyte(s)\n",(int)sizeof(structure::BracketedArgumentListSyntax)); 
    printf("structure::BracketedParameterListSyntax node: %dbyte(s)\n",(int)sizeof(structure::BracketedParameterListSyntax)); 
    printf("structure::CasePatternSwitchLabelSyntax node: %dbyte(s)\n",(int)sizeof(structure::CasePatternSwitchLabelSyntax)); 
    printf("structure::CaseSwitchLabelSyntax node: %dbyte(s)\n",(int)sizeof(structure::CaseSwitchLabelSyntax)); 
    printf("structure::CatchClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::CatchClauseSyntax)); 
    printf("structure::CatchDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::CatchDeclarationSyntax)); 
    printf("structure::CatchFilterClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::CatchFilterClauseSyntax)); 
    printf("structure::ClassDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::ClassDeclarationSyntax)); 
    printf("structure::ClassOrStructConstraintSyntax node: %dbyte(s)\n",(int)sizeof(structure::ClassOrStructConstraintSyntax)); 
    printf("structure::CompilationUnitSyntax node: %dbyte(s)\n",(int)sizeof(structure::CompilationUnitSyntax)); 
    printf("structure::ConstantPatternSyntax node: %dbyte(s)\n",(int)sizeof(structure::ConstantPatternSyntax)); 
    printf("structure::ConstructorConstraintSyntax node: %dbyte(s)\n",(int)sizeof(structure::ConstructorConstraintSyntax)); 
    printf("structure::ConstructorDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::ConstructorDeclarationSyntax)); 
    printf("structure::ConstructorInitializerSyntax node: %dbyte(s)\n",(int)sizeof(structure::ConstructorInitializerSyntax)); 
    printf("structure::ConversionOperatorDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::ConversionOperatorDeclarationSyntax)); 
    printf("structure::ConversionOperatorMemberCrefSyntax node: %dbyte(s)\n",(int)sizeof(structure::ConversionOperatorMemberCrefSyntax)); 
    printf("structure::CrefBracketedParameterListSyntax node: %dbyte(s)\n",(int)sizeof(structure::CrefBracketedParameterListSyntax)); 
    printf("structure::CrefParameterListSyntax node: %dbyte(s)\n",(int)sizeof(structure::CrefParameterListSyntax)); 
    printf("structure::CrefParameterSyntax node: %dbyte(s)\n",(int)sizeof(structure::CrefParameterSyntax)); 
    printf("structure::DeclarationPatternSyntax node: %dbyte(s)\n",(int)sizeof(structure::DeclarationPatternSyntax)); 
    printf("structure::DefaultSwitchLabelSyntax node: %dbyte(s)\n",(int)sizeof(structure::DefaultSwitchLabelSyntax)); 
    printf("structure::DelegateDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::DelegateDeclarationSyntax)); 
    printf("structure::DestructorDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::DestructorDeclarationSyntax)); 
    printf("structure::DiscardDesignationSyntax node: %dbyte(s)\n",(int)sizeof(structure::DiscardDesignationSyntax)); 
    printf("structure::DiscardPatternSyntax node: %dbyte(s)\n",(int)sizeof(structure::DiscardPatternSyntax)); 
    printf("structure::ElseClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::ElseClauseSyntax)); 
    printf("structure::EnumDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::EnumDeclarationSyntax)); 
    printf("structure::EnumMemberDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::EnumMemberDeclarationSyntax)); 
    printf("structure::EqualsValueClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::EqualsValueClauseSyntax)); 
    printf("structure::EventDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::EventDeclarationSyntax)); 
    printf("structure::EventFieldDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::EventFieldDeclarationSyntax)); 
    printf("structure::ExplicitInterfaceSpecifierSyntax node: %dbyte(s)\n",(int)sizeof(structure::ExplicitInterfaceSpecifierSyntax)); 
    printf("structure::ExternAliasDirectiveSyntax node: %dbyte(s)\n",(int)sizeof(structure::ExternAliasDirectiveSyntax)); 
    printf("structure::FieldDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::FieldDeclarationSyntax)); 
    printf("structure::FinallyClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::FinallyClauseSyntax)); 
    printf("structure::FromClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::FromClauseSyntax)); 
    printf("structure::GlobalStatementSyntax node: %dbyte(s)\n",(int)sizeof(structure::GlobalStatementSyntax)); 
    printf("structure::GroupClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::GroupClauseSyntax)); 
    printf("structure::IncompleteMemberSyntax node: %dbyte(s)\n",(int)sizeof(structure::IncompleteMemberSyntax)); 
    printf("structure::IndexerDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::IndexerDeclarationSyntax)); 
    printf("structure::IndexerMemberCrefSyntax node: %dbyte(s)\n",(int)sizeof(structure::IndexerMemberCrefSyntax)); 
    printf("structure::InterfaceDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::InterfaceDeclarationSyntax)); 
    printf("structure::InterpolatedStringTextSyntax node: %dbyte(s)\n",(int)sizeof(structure::InterpolatedStringTextSyntax)); 
    printf("structure::InterpolationAlignmentClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::InterpolationAlignmentClauseSyntax)); 
    printf("structure::InterpolationFormatClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::InterpolationFormatClauseSyntax)); 
    printf("structure::InterpolationSyntax node: %dbyte(s)\n",(int)sizeof(structure::InterpolationSyntax)); 
    printf("structure::JoinClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::JoinClauseSyntax)); 
    printf("structure::JoinIntoClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::JoinIntoClauseSyntax)); 
    printf("structure::LetClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::LetClauseSyntax)); 
    printf("structure::MethodDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::MethodDeclarationSyntax)); 
    printf("structure::NameColonSyntax node: %dbyte(s)\n",(int)sizeof(structure::NameColonSyntax)); 
    printf("structure::NameEqualsSyntax node: %dbyte(s)\n",(int)sizeof(structure::NameEqualsSyntax)); 
    printf("structure::NameMemberCrefSyntax node: %dbyte(s)\n",(int)sizeof(structure::NameMemberCrefSyntax)); 
    printf("structure::NamespaceDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::NamespaceDeclarationSyntax)); 
    printf("structure::OperatorDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::OperatorDeclarationSyntax)); 
    printf("structure::OperatorMemberCrefSyntax node: %dbyte(s)\n",(int)sizeof(structure::OperatorMemberCrefSyntax)); 
    printf("structure::OrderByClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::OrderByClauseSyntax)); 
    printf("structure::OrderingSyntax node: %dbyte(s)\n",(int)sizeof(structure::OrderingSyntax)); 
    printf("structure::ParameterListSyntax node: %dbyte(s)\n",(int)sizeof(structure::ParameterListSyntax)); 
    printf("structure::ParameterSyntax node: %dbyte(s)\n",(int)sizeof(structure::ParameterSyntax)); 
    printf("structure::ParenthesizedVariableDesignationSyntax node: %dbyte(s)\n",(int)sizeof(structure::ParenthesizedVariableDesignationSyntax)); 
    printf("structure::PositionalPatternClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::PositionalPatternClauseSyntax)); 
    printf("structure::PropertyDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::PropertyDeclarationSyntax)); 
    printf("structure::PropertyPatternClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::PropertyPatternClauseSyntax)); 
    printf("structure::QualifiedCrefSyntax node: %dbyte(s)\n",(int)sizeof(structure::QualifiedCrefSyntax)); 
    printf("structure::QueryBodySyntax node: %dbyte(s)\n",(int)sizeof(structure::QueryBodySyntax)); 
    printf("structure::QueryContinuationSyntax node: %dbyte(s)\n",(int)sizeof(structure::QueryContinuationSyntax)); 
    printf("structure::RecursivePatternSyntax node: %dbyte(s)\n",(int)sizeof(structure::RecursivePatternSyntax)); 
    printf("structure::SelectClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::SelectClauseSyntax)); 
    printf("structure::SimpleBaseTypeSyntax node: %dbyte(s)\n",(int)sizeof(structure::SimpleBaseTypeSyntax)); 
    printf("structure::SingleVariableDesignationSyntax node: %dbyte(s)\n",(int)sizeof(structure::SingleVariableDesignationSyntax)); 
    printf("structure::StructDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::StructDeclarationSyntax)); 
    printf("structure::SubpatternSyntax node: %dbyte(s)\n",(int)sizeof(structure::SubpatternSyntax)); 
    printf("structure::SwitchExpressionArmSyntax node: %dbyte(s)\n",(int)sizeof(structure::SwitchExpressionArmSyntax)); 
    printf("structure::SwitchSectionSyntax node: %dbyte(s)\n",(int)sizeof(structure::SwitchSectionSyntax)); 
    printf("structure::SyntaxToken node: %dbyte(s)\n",(int)sizeof(structure::SyntaxToken)); 
    printf("structure::TupleElementSyntax node: %dbyte(s)\n",(int)sizeof(structure::TupleElementSyntax)); 
    printf("structure::TypeArgumentListSyntax node: %dbyte(s)\n",(int)sizeof(structure::TypeArgumentListSyntax)); 
    printf("structure::TypeConstraintSyntax node: %dbyte(s)\n",(int)sizeof(structure::TypeConstraintSyntax)); 
    printf("structure::TypeCrefSyntax node: %dbyte(s)\n",(int)sizeof(structure::TypeCrefSyntax)); 
    printf("structure::TypeParameterConstraintClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::TypeParameterConstraintClauseSyntax)); 
    printf("structure::TypeParameterListSyntax node: %dbyte(s)\n",(int)sizeof(structure::TypeParameterListSyntax)); 
    printf("structure::TypeParameterSyntax node: %dbyte(s)\n",(int)sizeof(structure::TypeParameterSyntax)); 
    printf("structure::UsingDirectiveSyntax node: %dbyte(s)\n",(int)sizeof(structure::UsingDirectiveSyntax)); 
    printf("structure::VarPatternSyntax node: %dbyte(s)\n",(int)sizeof(structure::VarPatternSyntax)); 
    printf("structure::VariableDeclarationSyntax node: %dbyte(s)\n",(int)sizeof(structure::VariableDeclarationSyntax)); 
    printf("structure::VariableDeclaratorSyntax node: %dbyte(s)\n",(int)sizeof(structure::VariableDeclaratorSyntax)); 
    printf("structure::WhenClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::WhenClauseSyntax)); 
    printf("structure::WhereClauseSyntax node: %dbyte(s)\n",(int)sizeof(structure::WhereClauseSyntax)); 
    printf("structure::XmlCDataSectionSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlCDataSectionSyntax)); 
    printf("structure::XmlCommentSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlCommentSyntax)); 
    printf("structure::XmlCrefAttributeSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlCrefAttributeSyntax)); 
    printf("structure::XmlElementEndTagSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlElementEndTagSyntax)); 
    printf("structure::XmlElementStartTagSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlElementStartTagSyntax)); 
    printf("structure::XmlElementSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlElementSyntax)); 
    printf("structure::XmlEmptyElementSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlEmptyElementSyntax)); 
    printf("structure::XmlNameAttributeSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlNameAttributeSyntax)); 
    printf("structure::XmlNameSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlNameSyntax)); 
    printf("structure::XmlPrefixSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlPrefixSyntax)); 
    printf("structure::XmlProcessingInstructionSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlProcessingInstructionSyntax)); 
    printf("structure::XmlTextAttributeSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlTextAttributeSyntax)); 
    printf("structure::XmlTextSyntax node: %dbyte(s)\n",(int)sizeof(structure::XmlTextSyntax)); 
    printf("SourcePosition composite type: %dbyte(s)\n",(int)sizeof(SourcePosition)); 
  }

}}}
