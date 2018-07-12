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

#include "genealogy/inc/genealogy.h"

#include <string.h>
#include <algorithm>
#include <stdexcept>

#include "common/inc/StringSup.h"
#include "common/inc/WriteMessage.h"

#include "io/inc/ZippedIO.h"

#include "genealogy/inc/messages.h"

namespace columbus { namespace genealogy { 
Factory::Factory(RefDistributorStrTable& st) :
  container(),
  strTable(&st),
  reverseEdges(NULL),
  registeredPointerStorage(),
  root(NULL)
{
  root = dynamic_cast<Project*>(&createNode(ndkProject, 100));
}

Factory::~Factory() {
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
  io::ZippedIO zipIo(filename.c_str(), io::IOBase::omWrite, false);
  zipIo.setEndianState(io::BinaryIO::etLittle);

  // saving header ...
  header.add(CsiHeader::csih_Type, "GenealogyModel");
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
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_MISSING_FILE_TYPE_INFORMATION);
  if (type != "GenealogyModel")
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_WRONG_FILE_TYPE_INFORMATION);

  // Checking API version
  std::string apiVersion;
  if (!header.get(CsiHeader::csih_APIVersion, apiVersion))
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_MISSING_API_VERSION_INFORMATION);
  if (apiVersion != APIVersion)
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_WRONG_API_VERSION(APIVersion,apiVersion));

  // Checking binary version
  std::string binVersion;
  if (!header.get(CsiHeader::csih_BinaryVersion, binVersion))
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_MISSING_BINARY_VERSION_INFORMATION);
  if (binVersion != BinaryVersion)
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_WRONG_BINARY_VERSION(BinaryVersion,binVersion));

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

  root = dynamic_cast<Project*>(container[100]);
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
}

void Factory::regPointerStorage(SchemaPointerSorage* storage) {
  registeredPointerStorage.push_back(storage);
}

void Factory::unregPointerStorage(SchemaPointerSorage* storage) {
  registeredPointerStorage.erase(std::find(registeredPointerStorage.begin(),registeredPointerStorage.end(),storage));
}

void Factory::alertNodeDestroy(const Base* node) {
  for ( std::list<SchemaPointerSorage*>::iterator it = registeredPointerStorage.begin();it != registeredPointerStorage.end();++it) {
    (*it)->onDestroyNode(node);
  }

}

Project* Factory::getRoot() const {
  return root;
}

bool Factory::getExist(NodeId id) const {
  if (container.size() <= id)
    return false;
  return container[id] != NULL;
}

Base& Factory::getRef(NodeId id) const {
  Base* p = NULL;
  if (id < container.size())
    p = container[id];
  if (!p)
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  return *p;
}

Base* Factory::getPointer(NodeId id) const {
  Base* p = NULL;
  try {
    p = container.at(id);
  } catch (std::out_of_range e) {
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  }
  return p;
}

RefDistributorStrTable& Factory::getStringTable() const {
  return *strTable;
}

void Factory::destroyNode(NodeId id) {
  if (!reverseEdges)
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (!getExist(id))
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_ENABLE_THE_REVERSE_EDGE_FIRST);

  if (id >= container.size())
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_DOES_NOT_EXISTS);

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
  while (j != container->end() && !*j)
     ++j;
  return j != container->end();
}

const Base& Factory::ConstIterator::next() {
  while (i != container->end() && !*i)
     ++i;
  if (i == container->end())
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_NEXT_ELEMENT_DOES_NOT_EXIST);
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

Base* Factory::createNode(NodeKind kind) {
  Base *p = 0;
  NodeId id;
  if (deletedNodeIdList.empty())
    id = container.size();
  else {
    id = deletedNodeIdList.front();
    deletedNodeIdList.pop_front();
  }
  switch (kind) {
    case ndkProject: p = new Project(id, this); break;
    case ndkTrackable: p = new Trackable(id, this); break;
    case ndkComponent: p = new Component(id, this); break;
    case ndkSourceCodeElement: p = new SourceCodeElement(id, this); break;
    case ndkSystem: p = new System(id, this); break;
    case ndkClone: p = new Clone(id, this); break;
    case ndkStructuralClone: p = new StructuralClone(id, this); break;
    case ndkCloneClass: p = new CloneClass(id, this); break;
    case ndkCloneInstance: p = new CloneInstance(id, this); break;
    case ndkDataClumpsClass: p = new DataClumpsClass(id, this); break;
    case ndkDataClumps: p = new DataClumps(id, this); break;
    case ndkDataElement: p = new DataElement(id, this); break;
    case ndkSwitchStatementClass: p = new SwitchStatementClass(id, this); break;
    case ndkSwitchStatement: p = new SwitchStatement(id, this); break;
    case ndkCaseLabel: p = new CaseLabel(id, this); break;
    default: throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }

  if (container.size() <= id)
    container.resize(id + 1);

  container[id] = p;

  if (reverseEdges)
    reverseEdges->insertNode(p->getId());

  return p;
}

Base& Factory::createNode(NodeKind kind, NodeId i) {
  Base *p = 0;
  switch (kind) {
    case ndkProject: p = new Project(i,this); break;
    case ndkTrackable: p = new Trackable(i,this); break;
    case ndkComponent: p = new Component(i,this); break;
    case ndkSourceCodeElement: p = new SourceCodeElement(i,this); break;
    case ndkSystem: p = new System(i,this); break;
    case ndkClone: p = new Clone(i,this); break;
    case ndkStructuralClone: p = new StructuralClone(i,this); break;
    case ndkCloneClass: p = new CloneClass(i,this); break;
    case ndkCloneInstance: p = new CloneInstance(i,this); break;
    case ndkDataClumpsClass: p = new DataClumpsClass(i,this); break;
    case ndkDataClumps: p = new DataClumps(i,this); break;
    case ndkDataElement: p = new DataElement(i,this); break;
    case ndkSwitchStatementClass: p = new SwitchStatementClass(i,this); break;
    case ndkSwitchStatement: p = new SwitchStatement(i,this); break;
    case ndkCaseLabel: p = new CaseLabel(i,this); break;
    default: throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }

  if (container.size() <= i)
    container.resize(i + 1);

  container[i] = p;

  if (reverseEdges)
    reverseEdges->insertNode(p->getId());

  return *p;
}

  Project* Factory::createProjectNode(){
    return  dynamic_cast <Project*>( createNode(ndkProject));
  }

  Trackable* Factory::createTrackableNode(){
    return  dynamic_cast <Trackable*>( createNode(ndkTrackable));
  }

  Component* Factory::createComponentNode(){
    return  dynamic_cast <Component*>( createNode(ndkComponent));
  }

  SourceCodeElement* Factory::createSourceCodeElementNode(){
    return  dynamic_cast <SourceCodeElement*>( createNode(ndkSourceCodeElement));
  }

  System* Factory::createSystemNode(){
    return  dynamic_cast <System*>( createNode(ndkSystem));
  }

  Clone* Factory::createCloneNode(){
    return  dynamic_cast <Clone*>( createNode(ndkClone));
  }

  StructuralClone* Factory::createStructuralCloneNode(){
    return  dynamic_cast <StructuralClone*>( createNode(ndkStructuralClone));
  }

  CloneClass* Factory::createCloneClassNode(){
    return  dynamic_cast <CloneClass*>( createNode(ndkCloneClass));
  }

  CloneInstance* Factory::createCloneInstanceNode(){
    return  dynamic_cast <CloneInstance*>( createNode(ndkCloneInstance));
  }

  DataClumpsClass* Factory::createDataClumpsClassNode(){
    return  dynamic_cast <DataClumpsClass*>( createNode(ndkDataClumpsClass));
  }

  DataClumps* Factory::createDataClumpsNode(){
    return  dynamic_cast <DataClumps*>( createNode(ndkDataClumps));
  }

  DataElement* Factory::createDataElementNode(){
    return  dynamic_cast <DataElement*>( createNode(ndkDataElement));
  }

  SwitchStatementClass* Factory::createSwitchStatementClassNode(){
    return  dynamic_cast <SwitchStatementClass*>( createNode(ndkSwitchStatementClass));
  }

  SwitchStatement* Factory::createSwitchStatementNode(){
    return  dynamic_cast <SwitchStatement*>( createNode(ndkSwitchStatement));
  }

  CaseLabel* Factory::createCaseLabelNode(){
    return  dynamic_cast <CaseLabel*>( createNode(ndkCaseLabel));
  }

  void Factory::printNodeSizes() {
    printf("Project node: %dbyte(s)\n",(int)sizeof(Project)); 
    printf("Trackable node: %dbyte(s)\n",(int)sizeof(Trackable)); 
    printf("Component node: %dbyte(s)\n",(int)sizeof(Component)); 
    printf("SourceCodeElement node: %dbyte(s)\n",(int)sizeof(SourceCodeElement)); 
    printf("System node: %dbyte(s)\n",(int)sizeof(System)); 
    printf("Clone node: %dbyte(s)\n",(int)sizeof(Clone)); 
    printf("StructuralClone node: %dbyte(s)\n",(int)sizeof(StructuralClone)); 
    printf("CloneClass node: %dbyte(s)\n",(int)sizeof(CloneClass)); 
    printf("CloneInstance node: %dbyte(s)\n",(int)sizeof(CloneInstance)); 
    printf("DataClumpsClass node: %dbyte(s)\n",(int)sizeof(DataClumpsClass)); 
    printf("DataClumps node: %dbyte(s)\n",(int)sizeof(DataClumps)); 
    printf("DataElement node: %dbyte(s)\n",(int)sizeof(DataElement)); 
    printf("SwitchStatementClass node: %dbyte(s)\n",(int)sizeof(SwitchStatementClass)); 
    printf("SwitchStatement node: %dbyte(s)\n",(int)sizeof(SwitchStatement)); 
    printf("CaseLabel node: %dbyte(s)\n",(int)sizeof(CaseLabel)); 
  }

}}
