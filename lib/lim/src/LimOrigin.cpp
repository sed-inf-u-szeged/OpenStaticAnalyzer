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

#include "lim/inc/lim.h"
#include "lim/inc/messages.h"
#include <sstream>

using namespace std;

namespace columbus {
  LimOrigin::LimOrigin() : compIdCppId2LimIdMap(), extraPathMap() {
  }


  LimOrigin::~LimOrigin() {
  }


  void LimOrigin::save(io::BinaryIO &binIo) const {
    binIo.writeUInt4(compIdCppId2LimIdMap.size());
    for (NodeIdPairToNodeId::const_iterator it = compIdCppId2LimIdMap.begin(); it != compIdCppId2LimIdMap.end(); ++it) {
      binIo.writeUInt4(it->first.first);
      binIo.writeUInt4(it->first.second);
      binIo.writeUInt4(it->second);
    }
    binIo.writeUInt4(extraPathMap.size());
    for (NodeId2KeyMapType::const_iterator it = extraPathMap.begin(); it != extraPathMap.end(); ++it) {
      binIo.writeUInt4(it->first);
      binIo.writeUInt4(it->second);
    }
  }


  void LimOrigin::load(io::BinaryIO &binIo) {
    unsigned int sizeCompIdCppId2LimIdMap = binIo.readUInt4();
    NodeId compId;
    NodeId cppId;
    NodeId limId;
    for (unsigned int positionOfMap = 0; positionOfMap < sizeCompIdCppId2LimIdMap; ++positionOfMap) {
      compId = binIo.readUInt4();
      cppId = binIo.readUInt4();
      limId = binIo.readUInt4();
      std::pair<NodeId, NodeId> compId2CppId = make_pair(compId, cppId);
      compIdCppId2LimIdMap.insert(make_pair(compId2CppId, limId));
    }
    unsigned int sizeExtraPathMap = binIo.readUInt4();
    for (unsigned int positionOfMap = 0; positionOfMap < sizeExtraPathMap; ++positionOfMap) {
      NodeId nodeId = binIo.readUInt4();
      NodeId pathKey = binIo.readUInt4();
      extraPathMap.insert(make_pair(nodeId, pathKey));
    }
  }


  bool LimOrigin::addCompIdCppIdLimIdToMap(NodeId compId, NodeId cppId, NodeId limId) {
    std::pair<NodeId, NodeId> compId2CppId = make_pair(compId, cppId);
    return compIdCppId2LimIdMap.insert(make_pair(compId2CppId, limId)).second;
  }


  NodeId LimOrigin::getLimIdToCompIdAndCppId(NodeId compId, NodeId cppId) const {
    NodeId limId = 0;
    std::pair<NodeId, NodeId> compId2CppId = make_pair(compId, cppId);
    NodeIdPairToNodeId::const_iterator found = compIdCppId2LimIdMap.find(compId2CppId);
    if (found != compIdCppId2LimIdMap.end()) {
      limId = found->second;
    }
    return limId;
  }


  HeaderDataTypeKind LimOrigin::getType() const {
    return hdkLimOrigin;
  }
  
  
  std::string LimOrigin::toString() const {
    std::stringstream dumpstream;
    for (NodeIdPairToNodeId::const_iterator itemIt = compIdCppId2LimIdMap.begin(); itemIt != compIdCppId2LimIdMap.end(); ++itemIt)
      dumpstream << "Component (LIM)ID:" << itemIt->first.first << " CPP ASG ID:" << itemIt->first.second << " LIM ID:" << itemIt->second << "\n";
     for (NodeId2KeyMapType::const_iterator itemIt = extraPathMap.begin(); itemIt != extraPathMap.end(); ++itemIt)
      dumpstream << "LIM ID:" << itemIt->first << " EXTRA PATH KEY:" << itemIt->second << "\n";
    return dumpstream.str();
  }

  NodeIdPairToNodeId LimOrigin::getCompIdCppId2LimIdMap() const {
    return this->compIdCppId2LimIdMap;
  }

  bool LimOrigin::setExtraPath(NodeId nodeId, Key pathKey) {
    return extraPathMap.insert(make_pair(nodeId, pathKey)).second;
  }

  Key LimOrigin::getExtraPath(NodeId nodeId) const {
    Key pathKey = 0;
    NodeId2KeyMapType::const_iterator it = extraPathMap.find(nodeId);
    if (it != extraPathMap.end()) {
      pathKey = it->second;
    }
    return pathKey;
  }

}