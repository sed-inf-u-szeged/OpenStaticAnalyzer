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

#include "java/inc/java.h"
#include "common/inc/StringSup.h"
#include "java/inc/messages.h"
#include <cstring>


namespace columbus { namespace java { namespace asg {

  // ---------- Range ----------

  static std::string emptyString;

  Range::Range() : strTable(NULL), positionInfo() {
    memset(&positionInfo, 0, sizeof(PositionInfo));
  }

  Range::Range(StrTable &_strTable) : strTable(&_strTable), positionInfo() {
    memset(&positionInfo, 0, sizeof(PositionInfo));
  }

  Range::Range(StrTable &_strTable, const std::string& pathString, unsigned line, unsigned col, unsigned endLine, unsigned endCol, unsigned wideLine, unsigned wideCol, unsigned wideEndLine, unsigned wideEndCol) : strTable(&_strTable), positionInfo() {
    positionInfo.path = strTable->set(pathString);
    setLine(line);
    setCol(col);
    setEndLine(endLine);
    setEndCol(endCol);
    setWideLine(wideLine);
    setWideCol(wideCol);
    setWideEndLine(wideEndLine);
    setWideEndCol(wideEndCol);
  };

  const std::string& Range::getPath() const {
    if (strTable)
      return strTable->get(positionInfo.path);
    else
      return emptyString;
  }

  Key Range::getPathKey() const {
    return positionInfo.path;
  }

  void Range::setPath(const std::string& s) {
    if (!strTable)
      throw JavaException(COLUMBUS_LOCATION,CMSG_EX_UNTIL_NO_STRTABLE_IS_SET_THE_SETPATH );
    positionInfo.path = strTable->set(s);
  }

  unsigned Range::getLine() const {
    return positionInfo.line;
  }

  void Range::setLine(unsigned i) {
    positionInfo.line = i;
  }

  unsigned Range::getEndLine() const {
    return positionInfo.endLine;
  }

  void Range::setEndLine(unsigned i) {
    positionInfo.endLine = i;
  }

  unsigned Range::getWideLine() const {
    return positionInfo.wideLine;
  }

  void Range::setWideLine(unsigned i) {
    positionInfo.wideLine = i;
  }

  unsigned Range::getWideEndLine() const {
    return positionInfo.wideEndLine;
  }

  void Range::setWideEndLine(unsigned i) {
    positionInfo.wideEndLine = i;
  }

  unsigned Range::getCol() const {
    return positionInfo.col;
  }

  void Range::setCol(unsigned i) {
    positionInfo.col = i;
  }

  unsigned Range::getEndCol() const {
    return positionInfo.endCol;
  }

  void Range::setEndCol(unsigned i) {
    positionInfo.endCol = i;
  }

  unsigned Range::getWideCol() const {
    return positionInfo.wideCol;
  }

  void Range::setWideCol(unsigned i) {
    positionInfo.wideCol = i;
  }

  unsigned Range::getWideEndCol() const {
    return positionInfo.wideEndCol;
  }

  void Range::setWideEndCol(unsigned i) {
    positionInfo.wideEndCol = i;
  }

  Range::Range(StrTable &_strTable, Key pathKey, unsigned line, unsigned col, unsigned endLine, unsigned endCol, unsigned wideLine, unsigned wideCol, unsigned wideEndLine, unsigned wideEndCol) : strTable(&_strTable), positionInfo() {
    positionInfo.path = pathKey;
    setLine(line);
    setCol(col);
    setEndLine(endLine);
    setEndCol(endCol);
    setWideLine(wideLine);
    setWideCol(wideCol);
    setWideEndLine(wideEndLine);
    setWideEndCol(wideEndCol);
  };

  Range::Range(StrTable &_strTable, PositionInfo _positionInfo) : strTable(&_strTable), positionInfo(_positionInfo) {
  };

  void Range::setPathKey(Key pathKey) {
    positionInfo.path = pathKey;
  };


  // ---------- RangeListIterator ----------

  RangeListIterator:: RangeListIterator(Container *_container, IteratorContainer *itContainer) :
    container(_container),
    it(container->end()),
    iterators(itContainer),
    lastOp(op_None)
  {
    iterators->push_back(this);
  }

  void RangeListIterator::add(const Range &r) {
    switch (lastOp) {
      case op_None:
        it = container->begin();
        break;
      case op_Next:
      case op_Add:
        ++it;
        break;
      case op_Invalidated:
        throw JavaInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);
      case op_Previous:
      case op_Remove:
        break;
    }

    it = container->insert(it, r);

    lastOp = op_Add;
  }

  void RangeListIterator::remove() {
    switch (lastOp) {
      case op_None:
      case op_Add:
      case op_Remove:
        throw JavaIllegalStateException(COLUMBUS_LOCATION, CMSG_EX_NEITHER_NEXT_NOR_PREVIOUS_HAVE_BEEN_CALLED);
      case op_Next:
      case op_Previous:
        it = safeRemove(it);
        break;
      case op_Invalidated:
        throw JavaInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);
    }

    lastOp = op_Remove;
  }

  RangeListIterator::RangeListIterator() :
    container(NULL),
    it(),
    iterators(NULL),
    lastOp(op_Invalidated)
  {
  }

  RangeListIterator::RangeListIterator(const RangeListIterator &iterator) :
    container(iterator.container),
    it(iterator.it),
    iterators(iterator.iterators),
    lastOp(iterator.lastOp)
  {
    if (lastOp != op_Invalidated && iterators)
      iterators->push_back(this);
  }

  RangeListIterator::~RangeListIterator() {
    if (lastOp != op_Invalidated) {
      for (IteratorContainer::iterator _it = iterators->begin(); _it != iterators->end(); ++_it) {
        if (*_it == this) {
          iterators->erase(_it);
          return;
        }
      }
    }
  }

  RangeListIterator& RangeListIterator::operator=(const RangeListIterator &otherIt) {
    if (this == &otherIt)
      return *this;

    if (otherIt.lastOp == op_Invalidated)
      throw JavaInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);

    bool insertIntoIterators = true;
    if (lastOp != op_Invalidated && iterators) {
      if (iterators == otherIt.iterators) {
        insertIntoIterators = false;
      } else {
        for (IteratorContainer::iterator _it = iterators->begin(); _it != iterators->end(); ++_it) {
          if (*_it == this) {
            iterators->erase(_it);
            break;
          }
        }
      }
    }

    container = otherIt.container;
    it = otherIt.it;
    iterators = otherIt.iterators;
    lastOp = otherIt.lastOp;

    if (lastOp != op_Invalidated && iterators && insertIntoIterators)
      iterators->push_back(this);

    return *this;
  }

  bool RangeListIterator::hasNext() const {
    return nextItem() != container->end();
  }

  const Range& RangeListIterator::next() {
    it = nextItem();
    lastOp = op_Next;

    if (it == container->end())
        throw JavaNoSuchElementException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATION_HAS_NOT_NEXT_ELEMENT);

    return *it;
  }

  bool RangeListIterator::hasPrevious() const {
    return previousItem() != container->end();
  }

  const Range& RangeListIterator::previous() {
    it = previousItem();
    lastOp = op_Previous;

    if (it == container->end())
        throw JavaNoSuchElementException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATION_HAS_NOT_PREVIOUS_ELEMENT);

    return *it;
  }

  bool RangeListIterator::equals(const RangeListIterator& otherIt) const {
    if (lastOp == op_Invalidated)
      throw JavaInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);

    return (it == otherIt.it) && (lastOp == otherIt.lastOp);
  }

  RangeListIterator::Container::iterator RangeListIterator::nextItem() const {
    switch (lastOp) {
      case op_None:       return container->begin();
      case op_Add:
      case op_Next:       return ++Container::iterator(it);
      case op_Remove:
      case op_Previous:   return it;
      case op_Invalidated:
        throw JavaInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);
    }
    return container->end();
  }

  RangeListIterator::Container::iterator RangeListIterator::previousItem() const {
    switch (lastOp) {
      case op_None:       return container->end();
      case op_Add:
      case op_Next:       return it;
      case op_Remove:
      case op_Previous:   return it == container->begin() ? container->end() : --Container::iterator(it);
      case op_Invalidated:
        throw JavaInvalidIteratorException(COLUMBUS_LOCATION, CMSG_EX_THE_ITERATOR_IS_INVALID);
    }
    return container->end();
  }

  RangeListIterator::Container::iterator RangeListIterator::safeRemove(const Container::iterator &_it) {
    Container::iterator nextElement = _it;
    ++nextElement;

    for (IteratorContainer::iterator icIt = iterators->begin(); icIt != iterators->end(); ++icIt) {
      if (((*icIt)->it == _it) && (*icIt != this)) {
        (*icIt)->it = nextElement;
        (*icIt)->lastOp = op_Remove;
      }
    }

    return container->erase(_it);
  }

  void RangeListIterator::invalidate() {
    lastOp = op_Invalidated;
  }


}}}
