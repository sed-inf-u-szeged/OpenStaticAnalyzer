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

/*
 * MethodDecorator.cpp
 *
 *  Created on: Aug 3, 2010
 *      Author: kissmarci
 */

#include "lim/inc/lim.h"
#include "lim/inc/messages.h"

namespace columbus {
namespace lim {
namespace asg {

OverrideRelations::OverrideRelations(const Factory& f) :
  _factory(f) {
}

OverrideRelations::~OverrideRelations() {
  for (OverrideContainer::const_iterator it = _overrides.begin(); it != _overrides.end(); ++it) {
    if(it->second.flag == OverrideStruct::multi) {
      delete it->second.OverrideUnion.list;
    }
  }
}

const bool OverrideRelations::getIsOverride(const NodeId id) {
  return _overrides.find(id) != _overrides.end();
}

const NodeId OverrideRelations::getOverride(const NodeId id) {
  OverrideContainer::iterator it = _overrides.find(id);
  if(it == _overrides.end()) {
    return 0;
  }
  if(it->second.flag==OverrideStruct::single) {
    return it->second.OverrideUnion.id;
  } else {
    return *it->second.OverrideUnion.list->begin();
  }
  return id;
}
OverrideRelations::IdList OverrideRelations::getOverrideList(const NodeId id) {
  OverrideContainer::iterator it = _overrides.find(id);
  if(it == _overrides.end()) {
    return IdList();
  }
  if(it->second.flag==OverrideStruct::single) {
    IdList l;
    l.push_front(it->second.OverrideUnion.id);
    return l;
  } else {
    return *it->second.OverrideUnion.list;
  }
}
const int OverrideRelations::getNumberOfOverrides(const NodeId id) {
  OverrideContainer::iterator it = _overrides.find(id);
  if(it == _overrides.end()) {
    return 0;
  }
  if(it->second.flag==OverrideStruct::single) {
    return 1;
  } else {
    return it->second.OverrideUnion.list->size();
  }
}

void OverrideRelations::_addOverride(const Method& m, const Method& om) {
  _addOverride(m.getId(), om.getId());
}

void OverrideRelations::_addOverride(const NodeId mid, const NodeId omid) {
  if (!_factory.getExist(mid) || !_factory.getExist(omid))
  {
    throw new LimException(COLUMBUS_LOCATION, CMSG_EX_OVERRIDE_RELATION_END_POINT_NOT_EXISTS);
  }
  base::Base &mnode = _factory.getRef(mid);
  base::Base &onode = _factory.getRef(omid);

  if (Common::getIsMethod(mnode) && Common::getIsMethod(onode))
  {
    OverrideContainer::iterator it = _overrides.find(mid);
    if(it == _overrides.end()) {
      OverrideStruct oStruct;
      oStruct.flag= OverrideStruct::single;
      oStruct.OverrideUnion.id = omid;
      _overrides[mid] = oStruct;
    } else {
      if(it->second.flag==OverrideStruct::single) {
        NodeId id = it->second.OverrideUnion.id;
        it->second.OverrideUnion.list = new std::list<NodeId>();
        it->second.OverrideUnion.list->push_back(id);
        it->second.flag = OverrideStruct::multi;
      }
      it->second.OverrideUnion.list->push_back(omid);
    }
  }
  else
  {
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_OVERRIDE_RELATION_INVALID_NODEKIND);
  }
}

void OverrideRelations::save(io::BinaryIO &binIo) const {
  binIo.writeUInt4(_overrides.size());
  for (OverrideContainer::const_iterator it = _overrides.begin(); it != _overrides.end(); ++it) {
    binIo.writeUInt4(it->first);
    if(it->second.flag == OverrideStruct::single) {
      binIo.writeUInt4(1);
      binIo.writeUInt4(it->second.OverrideUnion.id);
    } else {
      IdList *l = it->second.OverrideUnion.list;
      binIo.writeUInt4(l->size());
      for (IdList::const_iterator it2 = l->begin(); it2 != l->end(); ++it2) {
        binIo.writeUInt4(*it2);
      }
    }
  }
}


void OverrideRelations::load(io::BinaryIO &binIo) {
  unsigned int size = binIo.readUInt4();
  for (unsigned int pos = 0; pos < size; ++pos) {
    unsigned int id = binIo.readUInt4();
    unsigned int numOfOverrides = binIo.readUInt4();
    OverrideStruct oStruct;
    if(numOfOverrides==1) {
      oStruct.flag= OverrideStruct::single;
      oStruct.OverrideUnion.id = binIo.readUInt4();
    } else {
      oStruct.flag = OverrideStruct::multi;
      oStruct.OverrideUnion.list = new IdList();
      for(unsigned int i = 0; i < numOfOverrides; ++i) {
        oStruct.OverrideUnion.list->push_back(binIo.readUInt4());
      }
    }
    _overrides[id] = oStruct;
  }
}

HeaderDataTypeKind OverrideRelations::getType() const {
  return hdkOverride;
}

  std::string OverrideRelations::toString() const {
    return "";
  }


}
}
}
