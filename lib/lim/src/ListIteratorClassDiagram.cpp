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

namespace columbus { namespace lim { namespace asg {
  //ListIteratorAssocACDEdge::ListIteratorAssocACDEdge() : ListIteratorAssoc() {}

  ListIteratorAssocACDEdge::ListIteratorAssocACDEdge
    //(AssocContainer *assocContainer, AssocIteratorContainer *aitContainer, const Factory* factory)
    (const Container *container, const Factory* factory, bool createAsBegin)
    : ListIteratorAssoc<base::Base, acdLinkInfo>(container, factory, createAsBegin), _stable(factory->getStringTable()) {}

  ListIteratorAssocACDEdge::ListIteratorAssocACDEdge
    (const ListIteratorAssocACDEdge& iterator)
    : ListIteratorAssoc<base::Base, acdLinkInfo>(iterator), _stable(fact->getStringTable()) {}

  ListIteratorAssocACDEdge::~ListIteratorAssocACDEdge() { }

  short ListIteratorAssocACDEdge::getLowMul() 
  {
    selfTest();
    return it->assocClass.low;
  }

  short ListIteratorAssocACDEdge::getHighMul() 
  {
    selfTest();
    return it->assocClass.high;
  }

  const std::string& ListIteratorAssocACDEdge::getName() 
  {
    selfTest();
    return _stable.get(it->assocClass.name_key);
  }

  void ListIteratorAssocACDEdge::selfTest() const
  {
    /*switch (lastOp) {
    case op_None:
    case op_Remove:
    case op_Add:
      throw LimIllegalStateException("columbus::lim::asg::ListIteratorAssocUShort::getAssocClass()", "Neither next() nor previous() have been called, or remove() or add() have been called after the last call to next() or previous()!");
    case op_Previous:
    case op_Next:
      return;
    case op_Invalidated:
    default:
      throw LimIllegalStateException("columbus::lim::asg::ListIteratorAssocUShort::getAssocClass()", "The iterator is invalid!");
    }*/
  }

}}}
