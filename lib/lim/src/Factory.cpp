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

#include "lim/inc/lim.h"

#include <string.h>
#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "common/inc/StringSup.h"
#include "common/inc/WriteMessage.h"

#include "io/inc/ZippedIO.h"

#include "lim/inc/messages.h"

#include "common/inc/FileSup.h"
#include "common/inc/PlatformDependentDefines.h"

namespace columbus { namespace lim { namespace asg {
Factory::Factory(RefDistributorStrTable& st, const std::string &rootPackageName, Language lang) :
  container(),
  strTable(&st),
  filter(NULL),
  filterOn(true),
  reverseEdges(NULL),
  registeredPointerStorage(),
  root(NULL),
  simpleTypesStartId(10),
  numberOfSimpleTypes(7),
  fileSystemId(101),
  rootComponentId(102),
  language(lang),
  scopeSeparator("unknown"),
  packageName("unknown"),
  componentNodes(),
  typeMap(),
  typeBuildStack(),
  typeFormerMethodMap(),
  typeFormerMethodBuildStack(),
  typeFormerPointerMap(),
  typeFormerArrayMap(0),
  typeFormerNonTypeMap(0),
  typeFormerTypeMap(),
  simpleTypeMap(),
  methodCallNodeIdMap(),
  attributeAccessNodeIdMap(),
  friendshipNodeIdMap()
{
  filter = new Filter(*this);
  root = dynamic_cast<logical::Package*>(&createNode(ndkPackage, 100));
  root->setName("global namespace");

  setSeparatorAndPackageName();
  root->setName(rootPackageName);

  // initial FileSystem
  physical::FileSystem *f = (physical::FileSystem*)&createNode(ndkFileSystem, fileSystemId);
  f->setName("FileSystem");

  // initial Component
  base::Component *cp = (base::Component*)&createNode(ndkComponent, rootComponentId);
  cp->setName("<System>");
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
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_HEADER_DATA_ALREADY_LOADED(unknownDataIt->first));
    if (unknownDataIt->first == hdkPropertyData) {
      hasUnkownPropertyData = true;
      break;
    }
  }
  if (!isContainPropertyData && !hasUnkownPropertyData) {
    zipIo.writeInt4(headerDataList.size() + unknownHeaderData.size() + 1);
    PropertyData propertyData;
    propertyData.add(PropertyData::csih_Type, "LanguageIndependentModel");
    propertyData.add(PropertyData::csih_APIVersion, APIVersion);
    propertyData.add(PropertyData::csih_BinaryVersion, BinaryVersion);
    propertyData.add(PropertyData::csih_Language, common::toString((int)language));
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
      propertyData.add(PropertyData::csih_Type, "LanguageIndependentModel");
      propertyData.add(PropertyData::csih_APIVersion, APIVersion);
      propertyData.add(PropertyData::csih_BinaryVersion, BinaryVersion);
    propertyData.add(PropertyData::csih_Language, common::toString((int)language));
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
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
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
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
  if (type != "LanguageIndependentModel")
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_WRONG_FILE_TYPE_INFORMATION);
  // Checking API version
  std::string apiVersion;
  if (!propertyData.get(PropertyData::csih_APIVersion, apiVersion))
    throw LimException(COLUMBUS_LOCATION,CMSG_EX_MISSING_API_VERSION_INFORMATION );
  if (apiVersion != APIVersion)
       throw LimException(COLUMBUS_LOCATION, CMSG_EX_WRONG_API_VERSION(APIVersion,apiVersion));
  // Checking binary version
  std::string binVersion;
  if (!propertyData.get(PropertyData::csih_BinaryVersion, binVersion))
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_MISSING_BINARY_VERSION_INFORMATION);
  if (binVersion != BinaryVersion)
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_WRONG_BINARY_VERSION(BinaryVersion,binVersion));
  // Checking language
  std::string tmpLang;
  tmpLang = Common::toString (limLangOther);
  if (!propertyData.get(PropertyData::csih_Language, tmpLang))
     throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_MISSING_LANGUAGE_INFORMATION);
  language = (Language) common::str2int(tmpLang);
  setSeparatorAndPackageName();
  }

void Factory::load( io::ZippedIO &zipIo, const std::list<HeaderData*> &headerDataList)
{
  bool zip = false;
  clear();
  char tag[4];
  zipIo.readData (tag,4);
  if ( strcmp(tag,"csi") && strcmp(tag,"zsi") ) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
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
  root = dynamic_cast<logical::Package*>(container[100]);
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

logical::Package* Factory::getRoot() const {
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
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  return *p;
}

base::Base* Factory::getPointer(NodeId id) const {
  base::Base* p = NULL;
  try {
    p = container.at(id);
  } catch (std::out_of_range e) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  }
  return p;
}

RefDistributorStrTable& Factory::getStringTable() const {
  return *strTable;
}

void Factory::destroyNode(NodeId id) {
  if (!reverseEdges)
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (!getExist(id))
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (id >= container.size())
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_NEXT_ELEMENT_DOES_NOT_EXIST);
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
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_LOADED_FILTER_DOES_NOT_MATCH_TO_THE_CURRENT);

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
    case ndkControlFlowBlock: p = new base::ControlFlowBlock(id, this); break;
    case ndkAttribute: p = new logical::Attribute(id, this); break;
    case ndkClass: p = new logical::Class(id, this); break;
    case ndkClassGeneric: p = new logical::ClassGeneric(id, this); break;
    case ndkClassGenericInstance: p = new logical::ClassGenericInstance(id, this); break;
    case ndkClassGenericSpec: p = new logical::ClassGenericSpec(id, this); break;
    case ndkGenericParameter: p = new logical::GenericParameter(id, this); break;
    case ndkMethod: p = new logical::Method(id, this); break;
    case ndkMethodGeneric: p = new logical::MethodGeneric(id, this); break;
    case ndkMethodGenericInstance: p = new logical::MethodGenericInstance(id, this); break;
    case ndkMethodGenericSpec: p = new logical::MethodGenericSpec(id, this); break;
    case ndkPackage: p = new logical::Package(id, this); break;
    case ndkParameter: p = new logical::Parameter(id, this); break;
    case ndkFile: p = new physical::File(id, this); break;
    case ndkFolder: p = new physical::Folder(id, this); break;
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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
    case ndkComponent: p = new base::Component(i,this); break;
    case ndkControlFlowBlock: p = new base::ControlFlowBlock(i,this); break;
    case ndkAttribute: p = new logical::Attribute(i,this); break;
    case ndkAttributeAccess: p = new logical::AttributeAccess(i,this); break;
    case ndkClass: p = new logical::Class(i,this); break;
    case ndkClassGeneric: p = new logical::ClassGeneric(i,this); break;
    case ndkClassGenericInstance: p = new logical::ClassGenericInstance(i,this); break;
    case ndkClassGenericSpec: p = new logical::ClassGenericSpec(i,this); break;
    case ndkFriendship: p = new logical::Friendship(i,this); break;
    case ndkGenericParameter: p = new logical::GenericParameter(i,this); break;
    case ndkMethod: p = new logical::Method(i,this); break;
    case ndkMethodCall: p = new logical::MethodCall(i,this); break;
    case ndkMethodGeneric: p = new logical::MethodGeneric(i,this); break;
    case ndkMethodGenericInstance: p = new logical::MethodGenericInstance(i,this); break;
    case ndkMethodGenericSpec: p = new logical::MethodGenericSpec(i,this); break;
    case ndkPackage: p = new logical::Package(i,this); break;
    case ndkParameter: p = new logical::Parameter(i,this); break;
    case ndkFile: p = new physical::File(i,this); break;
    case ndkFileSystem: p = new physical::FileSystem(i,this); break;
    case ndkFolder: p = new physical::Folder(i,this); break;
    case ndkSimpleType: p = new type::SimpleType(i,this); break;
    case ndkType: p = new type::Type(i,this); break;
    case ndkTypeFormerArray: p = new type::TypeFormerArray(i,this); break;
    case ndkTypeFormerMethod: p = new type::TypeFormerMethod(i,this); break;
    case ndkTypeFormerNonType: p = new type::TypeFormerNonType(i,this); break;
    case ndkTypeFormerPointer: p = new type::TypeFormerPointer(i,this); break;
    case ndkTypeFormerType: p = new type::TypeFormerType(i,this); break;
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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

  base::ControlFlowBlock* Factory::createControlFlowBlockNode(){
    return  dynamic_cast <base::ControlFlowBlock*>( createNode(ndkControlFlowBlock));
  }

  logical::Attribute* Factory::createAttributeNode(){
    return  dynamic_cast <logical::Attribute*>( createNode(ndkAttribute));
  }

  logical::Class* Factory::createClassNode(){
    return  dynamic_cast <logical::Class*>( createNode(ndkClass));
  }

  logical::ClassGeneric* Factory::createClassGenericNode(){
    return  dynamic_cast <logical::ClassGeneric*>( createNode(ndkClassGeneric));
  }

  logical::ClassGenericInstance* Factory::createClassGenericInstanceNode(){
    return  dynamic_cast <logical::ClassGenericInstance*>( createNode(ndkClassGenericInstance));
  }

  logical::ClassGenericSpec* Factory::createClassGenericSpecNode(){
    return  dynamic_cast <logical::ClassGenericSpec*>( createNode(ndkClassGenericSpec));
  }

  logical::GenericParameter* Factory::createGenericParameterNode(){
    return  dynamic_cast <logical::GenericParameter*>( createNode(ndkGenericParameter));
  }

  logical::Method* Factory::createMethodNode(){
    return  dynamic_cast <logical::Method*>( createNode(ndkMethod));
  }

  logical::MethodGeneric* Factory::createMethodGenericNode(){
    return  dynamic_cast <logical::MethodGeneric*>( createNode(ndkMethodGeneric));
  }

  logical::MethodGenericInstance* Factory::createMethodGenericInstanceNode(){
    return  dynamic_cast <logical::MethodGenericInstance*>( createNode(ndkMethodGenericInstance));
  }

  logical::MethodGenericSpec* Factory::createMethodGenericSpecNode(){
    return  dynamic_cast <logical::MethodGenericSpec*>( createNode(ndkMethodGenericSpec));
  }

  logical::Package* Factory::createPackageNode(){
    return  dynamic_cast <logical::Package*>( createNode(ndkPackage));
  }

  logical::Parameter* Factory::createParameterNode(){
    return  dynamic_cast <logical::Parameter*>( createNode(ndkParameter));
  }

  physical::File* Factory::createFileNode(){
    return  dynamic_cast <physical::File*>( createNode(ndkFile));
  }

  physical::Folder* Factory::createFolderNode(){
    return  dynamic_cast <physical::Folder*>( createNode(ndkFolder));
  }

  void Factory::printNodeSizes() {
    printf("base::Comment node: %dbyte(s)\n",(int)sizeof(base::Comment)); 
    printf("base::Component node: %dbyte(s)\n",(int)sizeof(base::Component)); 
    printf("base::ControlFlowBlock node: %dbyte(s)\n",(int)sizeof(base::ControlFlowBlock)); 
    printf("logical::Attribute node: %dbyte(s)\n",(int)sizeof(logical::Attribute)); 
    printf("logical::AttributeAccess node: %dbyte(s)\n",(int)sizeof(logical::AttributeAccess)); 
    printf("logical::Class node: %dbyte(s)\n",(int)sizeof(logical::Class)); 
    printf("logical::ClassGeneric node: %dbyte(s)\n",(int)sizeof(logical::ClassGeneric)); 
    printf("logical::ClassGenericInstance node: %dbyte(s)\n",(int)sizeof(logical::ClassGenericInstance)); 
    printf("logical::ClassGenericSpec node: %dbyte(s)\n",(int)sizeof(logical::ClassGenericSpec)); 
    printf("logical::Friendship node: %dbyte(s)\n",(int)sizeof(logical::Friendship)); 
    printf("logical::GenericParameter node: %dbyte(s)\n",(int)sizeof(logical::GenericParameter)); 
    printf("logical::Method node: %dbyte(s)\n",(int)sizeof(logical::Method)); 
    printf("logical::MethodCall node: %dbyte(s)\n",(int)sizeof(logical::MethodCall)); 
    printf("logical::MethodGeneric node: %dbyte(s)\n",(int)sizeof(logical::MethodGeneric)); 
    printf("logical::MethodGenericInstance node: %dbyte(s)\n",(int)sizeof(logical::MethodGenericInstance)); 
    printf("logical::MethodGenericSpec node: %dbyte(s)\n",(int)sizeof(logical::MethodGenericSpec)); 
    printf("logical::Package node: %dbyte(s)\n",(int)sizeof(logical::Package)); 
    printf("logical::Parameter node: %dbyte(s)\n",(int)sizeof(logical::Parameter)); 
    printf("physical::File node: %dbyte(s)\n",(int)sizeof(physical::File)); 
    printf("physical::FileSystem node: %dbyte(s)\n",(int)sizeof(physical::FileSystem)); 
    printf("physical::Folder node: %dbyte(s)\n",(int)sizeof(physical::Folder)); 
    printf("type::SimpleType node: %dbyte(s)\n",(int)sizeof(type::SimpleType)); 
    printf("type::Type node: %dbyte(s)\n",(int)sizeof(type::Type)); 
    printf("type::TypeFormerArray node: %dbyte(s)\n",(int)sizeof(type::TypeFormerArray)); 
    printf("type::TypeFormerMethod node: %dbyte(s)\n",(int)sizeof(type::TypeFormerMethod)); 
    printf("type::TypeFormerNonType node: %dbyte(s)\n",(int)sizeof(type::TypeFormerNonType)); 
    printf("type::TypeFormerPointer node: %dbyte(s)\n",(int)sizeof(type::TypeFormerPointer)); 
    printf("type::TypeFormerType node: %dbyte(s)\n",(int)sizeof(type::TypeFormerType)); 
    printf("SourcePosition composite type: %dbyte(s)\n",(int)sizeof(SourcePosition)); 
  }

Language Factory::getLanguage() const {
  return language;
}

void Factory::setScopeSeparator(const std::string& newSeparator) {
  if (language == limLangOther) {
    scopeSeparator = newSeparator;
  } else {
    throw LimException("columbus::lim::Factory::setScopeSeparator(const std::string&)", "Scope separator cannot be changed for this language (" + Common::toString(language) + ")");
  }
}

const std::string Factory::getScopeSeparator() const {
  return scopeSeparator;
}

void Factory::setPackageName(const std::string& newPackageName) {
  if (language == limLangOther) {
    packageName = newPackageName;
  } else {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_PACKAGE_CANNOT_BE_CHANGED);
  }
}

const std::string Factory::getPackageName() const {
  return packageName;
}

NodeId Factory::getFileSystemRoot() const {
  if (!getExist(fileSystemId)) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_MISSING_ROOT_OF_FILESYSTEM);
  }
  return fileSystemId;
}

NodeId Factory::getComponentRoot() const {
  if (!getExist(rootComponentId)) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_MISSING_ROOT_COMPONENT);
  }
  return rootComponentId;
}

base::Component& Factory::getComponentRootRef() const {
  return (base::Component&)getRef(rootComponentId);
}


base::Component& Factory::createComponent(const std::string& name) {
  Key namekey = strTable->set(name);
  std::map<Key, NodeId>::iterator it = componentNodes.find(namekey);
  if (it != componentNodes.end()) {
    if (getExist(it->second)) {
      base::Base& n = getRef(it->second);
      if (n.getNodeKind() == ndkComponent && ((base::Component&)n).getNameKey() == namekey) {
        return (base::Component&)n;
      }
    }
  }

  base::Component& component = (base::Component&)createNode(ndkComponent, container.size());
  component.setNameKey(namekey);
  if (it != componentNodes.end()) {
    it->second = component.getId();
  } else {
    componentNodes.insert(std::make_pair(namekey, component.getId()));
  }

  return component;
}

base::Comment& Factory::createComment(const std::string& text) {
  base::Comment& comment = (base::Comment&)createNode(ndkComment, container.size());
  Key key = strTable->set(text);
  comment.setTextKey(key);
  return comment;
}


physical::File& Factory::createFile(const std::string& path) {
  return createFile(path, fileSystemId);
}

physical::File& Factory::createFile(const std::string& path, NodeId nodeId) {
  if (path.empty()) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_PATH_IS_EMPTY);
  }

  if (!getExist(nodeId)) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_INVALID_NODEID);
  }

  if (nodeId != fileSystemId && container[nodeId]->getNodeKind() != ndkFolder) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_INVALID_NODEKIND);
  }

  std::string str = path;
  std::string::size_type pos = 0;
#if defined(_WIN32)
  while ((pos = str.find("\\",pos)) != std::string::npos)
    str.replace(pos,1,"/");
#endif

  pos = 0;
  while ((pos = str.find("//",pos)) != std::string::npos) {
	str = common::replace(str.c_str(), "//", "/");
	pos = 0;
  }
  
  physical::FileSystem *fs = NULL;
  physical::Folder *folder = NULL;
  if (nodeId == fileSystemId) {
    fs = (physical::FileSystem*)container[nodeId];
  } else {
    folder = (physical::Folder*)container[nodeId];
  }

  pos = 0;
  std::string::size_type lastpos = 0;
  std::string name;
  while ((pos = str.find("/",pos)) != std::string::npos) {
    if (lastpos) {
      name = str.substr(lastpos, pos - lastpos);
    } else {
      if (str[0]=='/') {
        name = DIRDIVSTRING;
      } else {
        name = str.substr(0, pos);
      }
    }
    if (name.empty()) {
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_EMPTY_FOLDER_NAME);
    }

    // searching for the folder name
    ListIterator<physical::FSEntry> it_begin = fs ? fs->getFSEntryListIteratorBegin() : folder->getContainsListIteratorBegin();
    ListIterator<physical::FSEntry> it_end = fs ? fs->getFSEntryListIteratorEnd() : folder->getContainsListIteratorEnd();
    NodeId found = 0;
    for (ListIterator<physical::FSEntry> it = it_begin; it != it_end; ++it) {
      if (found) {
        break;
      }
	  std::string tmpName = name;
	  if (folder) {
		//tmpName = folder->getName() + DIRDIVSTRING + tmpName;
	  }
      const physical::FSEntry& entry = *it;
      if (entry.getNodeKind() == ndkFolder && entry.getName() == tmpName) {
        found = entry.getId();
      }
    }

    if (found) {
      fs = NULL;
      folder = (physical::Folder*)container[found];
    } else {
      // creating a new Folder
      physical::Folder& newFolder = (physical::Folder&)createNode(ndkFolder, container.size());
	  newFolder.setName(name);
//      std::string uname = "";
//      if (folder) {
//        std::string foldUname = folder->getName();
//        uname += foldUname;
//        if (foldUname != "/" && foldUname != "\\") {
//          uname += DIRDIVSTRING;
//        }
//      }
//      newFolder.setName(uname + name);
      if (fs) {
        fs->addFSEntry(&newFolder);
        fs = NULL;
      } else {
        folder->addContains(&newFolder);
      }
      folder = &newFolder;
    }

    pos++;
    lastpos = pos;
  }

  name = "";
  if (lastpos != std::string::npos) {
    name = str.substr(lastpos);
  }
  if (name.empty()) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_EMPTY_FILE_NAME);
  }

  // searching for the file name
  ListIterator<physical::FSEntry> it_begin = fs ? fs->getFSEntryListIteratorBegin() : folder->getContainsListIteratorBegin();
  ListIterator<physical::FSEntry> it_end = fs ? fs->getFSEntryListIteratorEnd() : folder->getContainsListIteratorEnd();
  NodeId found = 0;
  for (ListIterator<physical::FSEntry> it = it_begin; it != it_end; ++it) {
    if (found) {
      break;
    }
	std::string tmpName = name;
	if (folder) {
	//tmpName = folder->getName() + DIRDIVSTRING + tmpName;
	}
    const physical::FSEntry& entry = *it;
    if (entry.getNodeKind() == ndkFile && entry.getName() == tmpName) {
      found = entry.getId();
    }
  }

  if (found) {
    return (physical::File&)*container[found];
  }

  // the File node is not found, creating a new one
  physical::File& file = (physical::File&)createNode(ndkFile, container.size());
  file.setName(name);
//  std::string uname = name;
//  if (folder) {
//    uname = DIRDIVSTRING + uname;
//    std::string foldUname = folder->getName();
//    if (foldUname != "/" && foldUname != "\\") {
//      uname = folder->getName() + uname;
//    }
//  }
//  file.setName(uname);
  if (fs) {
    fs->addFSEntry(&file);
  } else {
    folder->addContains(&file);
  }
  return file;
}


void Factory::setSeparatorAndPackageName() {
  switch (language) {
    default:
    case limLangOther:
      break;
    case limLangC:
      scopeSeparator = "::";
      packageName = "Namespace";
      break;
    case limLangCpp:
      scopeSeparator = "::";
      packageName = "Namespace";
      break;
    case limLangJava:
      scopeSeparator = ".";
      packageName = "Package";
      break;
    case limLangCsharp:
      scopeSeparator = ".";
      packageName = "Namespace";
      break;
    case limLangFsql:
      scopeSeparator = "::";
      packageName = "Module";
      break;
    case limLangPython:
      scopeSeparator = ".";
      packageName = "Package";
      break;
    case limLangJavaScript:
      scopeSeparator = ".";
      packageName = "Module";
      break;
  }
}

void Factory::beginType() {
  typeBuildStack.push(std::string());
}

void Factory::addTypeFormer(NodeId typeFormer) {
  if (typeBuildStack.empty()) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_TYPE_BUILDER_STACK_IS_EMPTY);
  }

  typeBuildStack.top() += std::string((char*)&typeFormer, sizeof(NodeId));
}

type::Type& Factory::endType() {
  
  if (typeBuildStack.empty()) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_TYPE_BUILDER_STACK_IS_EMPTY);
  }
  
  std::string& imprint = typeBuildStack.top();
  Key key = tmpStringTable.set(imprint);
  
  std::map<Key, NodeId>::iterator result = typeMap.find(key);
  if (result != typeMap.end()) {
    typeBuildStack.pop();
    return (type::Type&)getRef(result->second);
  }
  
  type::Type& newNode = (type::Type&)createNode(ndkType, container.size());
  
  NodeId* typeFormers = (NodeId*)imprint.c_str();
  unsigned numberOfTypeFormers = imprint.size() / sizeof(NodeId);
  for (unsigned i = 0; i < numberOfTypeFormers; i++) {
    newNode.addTypeFormer(typeFormers[i]);
  }

  typeMap.insert(std::make_pair(key, newNode.getId()));
  typeBuildStack.pop();
  
  return newNode;
}


void Factory::beginTypeFormerMethod() {
  typeFormerMethodBuildStack.push(std::string());
  
}

void Factory::setTypeFormerMethodHasReturnType(NodeId returnType) {
  if (typeFormerMethodBuildStack.empty()) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_TYPEFORMERMETHOD_BUILDER_STACK_IS_EMPTY);
  }

  std::string& imprint = typeFormerMethodBuildStack.top();
  
  if (imprint.empty()) {
    imprint = std::string((char*)&returnType, sizeof(NodeId));
  } else {
    imprint.replace(0, sizeof(NodeId), std::string((char*)&returnType, sizeof(NodeId)));
  }
    
}

void Factory::addTypeFormerMethodHasParameterType(NodeId parameterType, ParameterKind paramKind) {
  if (typeFormerMethodBuildStack.empty()) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_TYPEFORMERMETHOD_BUILDER_STACK_IS_EMPTY);
  }
  
  std::string& imprint = typeFormerMethodBuildStack.top();
  if (imprint.empty()) {
    NodeId returnType = 0;
    imprint = std::string((char*)&returnType, sizeof(NodeId));
  }
  imprint += std::string((char*)&parameterType, sizeof(NodeId));
  imprint += std::string(1, (char)paramKind);
  
}

type::TypeFormerMethod& Factory::endTypeFormerMethod() {
  if (typeFormerMethodBuildStack.empty()) {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_FACTORY_TYPEFORMERMETHOD_BUILDER_STACK_IS_EMPTY);
  }
  
  std::string& imprint = typeFormerMethodBuildStack.top();
  Key key = tmpStringTable.set(imprint);
  
  std::map<Key, NodeId>::iterator result = typeFormerMethodMap.find(key);
  if (result != typeFormerMethodMap.end()) {
    typeFormerMethodBuildStack.pop();
    return (type::TypeFormerMethod&)getRef(result->second);
  }
  
  type::TypeFormerMethod& newNode = (type::TypeFormerMethod&)createNode(ndkTypeFormerMethod, container.size());
  
  if (!imprint.empty()) {
    NodeId returnType = *((NodeId*)imprint.c_str());
    if (returnType) {
      newNode.setReturnType(returnType);
    }

    unsigned numberOfTypes = (imprint.size() - sizeof(NodeId)) / (sizeof(NodeId) + 1);
  
    for (unsigned i = 0; i < numberOfTypes; i++) {
      const char *position = imprint.c_str() + sizeof(NodeId) + i * (sizeof(NodeId) + 1);
      newNode.addParameterType(*(NodeId*)position, (ParameterKind)(*(position + sizeof(NodeId))));
    }
  }

  typeFormerMethodMap.insert(std::make_pair(key, newNode.getId()));
  typeFormerMethodBuildStack.pop();
  
  return newNode;

}


type::TypeFormerPointer& Factory::createTypeFormerPointer(PointerKind ptk) {
  
  std::map<PointerKind, NodeId>::iterator it = typeFormerPointerMap.find(ptk);
  if (it != typeFormerPointerMap.end()) {
    return (type::TypeFormerPointer&)getRef(it->second);
  }
    
  type::TypeFormerPointer& newNode = (type::TypeFormerPointer&)createNode(ndkTypeFormerPointer, container.size());
  
  newNode.setPointerKind(ptk);
  
  typeFormerPointerMap.insert(std::make_pair(ptk, newNode.getId()));

  return newNode;
}

type::TypeFormerArray& Factory::createTypeFormerArray() {
  if (typeFormerArrayMap) {
    return (type::TypeFormerArray&)getRef(typeFormerArrayMap);
  }

  type::TypeFormerArray& newNode = (type::TypeFormerArray&)createNode(ndkTypeFormerArray, container.size());
  
  typeFormerArrayMap = newNode.getId();
  
  return newNode;
}


type::TypeFormerType& Factory::createTypeFormerType(NodeId refersTo) {

  std::map<Key, NodeId>::iterator it = typeFormerTypeMap.find(refersTo);
  if (it != typeFormerTypeMap.end()) {
    return (type::TypeFormerType&)getRef(it->second);
  }
  
  type::TypeFormerType& newNode = (type::TypeFormerType&)createNode(ndkTypeFormerType, container.size());
  
  if (refersTo) {
    newNode.setRefersTo(refersTo);
  }
  
  typeFormerTypeMap.insert(std::make_pair(refersTo, newNode.getId()));
  
  return newNode;
}

type::TypeFormerNonType& Factory::createTypeFormerNonType() {
  if (typeFormerNonTypeMap) {
    return (type::TypeFormerNonType&)getRef(typeFormerNonTypeMap);
  }

  type::TypeFormerNonType& newNode = (type::TypeFormerNonType&)createNode(ndkTypeFormerNonType, container.size());
  
  typeFormerNonTypeMap = newNode.getId();
  
  return newNode;
}



type::SimpleType& Factory::createSimpleType(SimpleTypeKind stk) {
  
  std::map<SimpleTypeKind, NodeId>::iterator it = simpleTypeMap.find(stk);
  if (it != simpleTypeMap.end()) {
    return (type::SimpleType&)getRef(it->second);
  }
    
  type::SimpleType& newNode = (type::SimpleType&)createNode(ndkSimpleType, container.size());
  
  newNode.setSimpleTypeKind(stk);
  
  simpleTypeMap.insert(std::make_pair(stk, newNode.getId()));

  return newNode;
}



logical::MethodCall& Factory::createMethodCall(NodeId method) {

  std::map<Key, NodeId>::iterator it = methodCallNodeIdMap.find(method);
  if (it != methodCallNodeIdMap.end()) {
    return (logical::MethodCall&)getRef(it->second);
  }
  
  logical::MethodCall& newNode = (logical::MethodCall&)createNode(ndkMethodCall, container.size());
  
  if (method) {
    newNode.setMethod(method);
  }
  
  methodCallNodeIdMap.insert(std::make_pair(method, newNode.getId()));
  
  return newNode;
}

logical::MethodCall& Factory::createMethodCall(const std::string& imprint) {
  Key imprintkey = strTable->set(imprint);
  std::map<Key, NodeId>::iterator it = callImprintMethodCallNodeIdMap.find(imprintkey);
  
  if (it != callImprintMethodCallNodeIdMap.end())
    return (logical::MethodCall&)getRef(it->second);
  
  logical::MethodCall& newNode = (logical::MethodCall&)createNode(ndkMethodCall, container.size());
  
  newNode.setCalls(imprint);
  
  callImprintMethodCallNodeIdMap.insert(std::make_pair(imprintkey, newNode.getId()));
  
  return newNode;
}

logical::AttributeAccess& Factory::createAttributeAccess(NodeId attribute) {

  std::map<Key, NodeId>::iterator it = attributeAccessNodeIdMap.find(attribute);
  if (it != attributeAccessNodeIdMap.end()) {
    return (logical::AttributeAccess&)getRef(it->second);
  }
  
  logical::AttributeAccess& newNode = (logical::AttributeAccess&)createNode(ndkAttributeAccess, container.size());
  
  if (attribute) {
    newNode.setAttribute(attribute);
  }
  
  attributeAccessNodeIdMap.insert(std::make_pair(attribute, newNode.getId()));
  
  return newNode;
}

logical::Friendship& Factory::createFriendship(NodeId friendNode) {

  std::map<Key, NodeId>::iterator it = friendshipNodeIdMap.find(friendNode);
  if (it != friendshipNodeIdMap.end()) {
    return (logical::Friendship&)getRef(it->second);
  }
  
  logical::Friendship& newNode = (logical::Friendship&)createNode(ndkFriendship, container.size());
  
  if (friendNode) {
    newNode.setFriend(friendNode);
  }
  
  friendshipNodeIdMap.insert(std::make_pair(friendNode, newNode.getId()));
  
  return newNode;
}

base::Base* Factory::replaceNode(base::Base &node)
{
  NodeId id = node.getId();
  base::Base* p = NULL;

  if ( node.getNodeKind() == ndkClass )
  {
    p = new logical::ClassGeneric( id, this );
    dynamic_cast<logical::Class*>( p )->clone( dynamic_cast<logical::Class&>(node), true );
  }
  else if ( node.getNodeKind() == ndkMethod )
  {
    p = new logical::MethodGeneric( id, this );
    dynamic_cast<logical::Method*>( p )->clone( dynamic_cast<logical::Method&>(node), true );
  }
  else throw LimException( COLUMBUS_LOCATION, CMSG_EX_FACTORY_REPLACE_WRONG_NODE(id, node.getNodeKind()) );

  delete container[id];
  container[id] = p;

  return p;
}
}}}
