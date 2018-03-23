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

#include "csharp/inc/csharp.h"
#include "csharp/inc/messages.h"

namespace columbus { namespace csharp { namespace asg {
Filter::Filter(Factory& fact) : container(),factory(fact) {
}

void Filter::initializeFilter() {
  if (container.size() < factory.size())
    container.resize(factory.size());
  for (Container::iterator i = container.begin(); i != container.end(); ++i)
    *i = NotFiltered;
}

bool Filter::getIsFiltered(NodeId id) const {
  if (container.size() <= id)
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  return container[id] == Filtered;
}

void Filter::setFiltered(NodeId id) {
  if (Common::getIsValid(id)) {
    VisitorFilter v;
    AlgorithmPreorder ap;
    ap.run(factory, v, id);
  }
}

void Filter::setNotFiltered(NodeId id) {
  if (factory.getExist(id)) {
    Factory::TurnFilterOffSafely tfos(factory);
    VisitorFilter v(false);
    AlgorithmPreorder ap;
    ap.run(factory, v, id);
    // none of the ancestors are allowed to be filtered
    base::Base *node = factory.getPointer(id);
    do {
      container[node->getId()] = NotFiltered;
      node = node->getParent();
    } while (node);
  }
}

void Filter::setNotFilteredThisNode(NodeId id) {
  if (factory.getExist(id)) {
    base::Base *node = factory.getPointer(id);
    do {
      container[node->getId()] = NotFiltered;
      node = node->getParent();
    } while (node && container[node->getId()] == Filtered);
  }
}

void Filter::setFilteredThisNodeOnly(NodeId id) {
  if (container.size() <= id)
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  // do not let filter the root node
  if (id == factory.getRoot()->getId())
    return;
  container[id] = Filtered;
}

void Filter::setNotFilteredThisNodeOnly(NodeId id) {
  if (container.size() <= id)
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  container[id] = NotFiltered;
}

Filter::FilterState Filter::getFilterState(NodeId id) const {
  if (container.size() <= id)
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_ID(id));
  return container[id];
}

void Filter::save(io::BinaryIO *binIo) const {
  binIo->writeUInt4((unsigned int)container.size());
  for (Container::const_iterator it = container.begin(); it != container.end(); ++it)
    binIo->writeUByte1(*it);
}

void Filter::load(io::BinaryIO *binIo) {
  unsigned long size = binIo->readUInt4();
  container.resize(size);
  for (unsigned long i = 0; i < size; ++i)
    container[i] = (FilterState)binIo->readUByte1();
}


}}}
