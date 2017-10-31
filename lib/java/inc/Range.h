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

#ifndef _JAVA_RANGE_H_
#define _JAVA_RANGE_H_

#include "java/inc/java.h"

/**
* \file Range.h
* \brief Contains declaration of Range class.
*/

namespace columbus { namespace java { namespace asg {

  // ---------- Range ----------

  class Range {
    public:
      typedef struct {
        Key path;
        unsigned line;
        unsigned col;
        unsigned endLine;
        unsigned endCol;
        unsigned wideLine;
        unsigned wideCol;
        unsigned wideEndLine;
        unsigned wideEndCol;
      } PositionInfo;

      Range();
      Range(StrTable &strTable);
      Range(StrTable &strTable, const std::string& pathString, unsigned line, unsigned col, unsigned endLine, unsigned endCol, unsigned wideLine, unsigned wideCol, unsigned wideEndLine, unsigned wideEndCol);
      const std::string& getPath() const;
      Key getPathKey() const;

      unsigned getLine() const;
      unsigned getCol() const;
      unsigned getEndLine() const;
      unsigned getEndCol() const;
      unsigned getWideLine() const;
      unsigned getWideCol() const;
      unsigned getWideEndLine() const;
      unsigned getWideEndCol() const;

      void setPath(const std::string& s);
      void setLine(unsigned i);
      void setCol(unsigned i);
      void setEndLine(unsigned i);
      void setEndCol(unsigned i);
      void setWideLine(unsigned i);
      void setWideCol(unsigned i);
      void setWideEndLine(unsigned i);
      void setWideEndCol(unsigned i);

    protected:
      Range(StrTable &strTable, Key pathKey, unsigned line, unsigned col, unsigned endLine, unsigned endCol, unsigned wideLine, unsigned wideCol, unsigned wideEndLine, unsigned wideEndCol);
      Range(StrTable &strTable, PositionInfo _positionInfo);
      void setPathKey(Key pathKey);

      StrTable *strTable;
      PositionInfo positionInfo;

    friend class base::Named;
    friend class base::PositionedWithoutComment;
    friend class expr::Conditional;
    friend class expr::NewArray;
    friend class statm::Assert;
    friend class statm::BasicFor;
    friend class statm::Do;
    friend class statm::EnhancedFor;
    friend class statm::For;
    friend class statm::Handler;
    friend class statm::If;
    friend class statm::Jump;
    friend class statm::LabeledStatement;
    friend class statm::Switch;
    friend class statm::SwitchLabel;
    friend class statm::Try;
    friend class struc::AnnotationType;
    friend class struc::AnnotationTypeElement;
    friend class struc::Enum;
    friend class struc::Import;
    friend class struc::MethodDeclaration;
    friend class struc::NamedDeclaration;
    friend class struc::NormalMethod;
    friend class struc::Parameter;
    friend class struc::StaticInitializerBlock;
    friend class struc::TypeDeclaration;
    friend class struc::Variable;
    friend class Factory;
  };


  // ---------- RangeListIterator ----------

  class RangeListIterator {
    public:
      /** \brief Type definition to store Ranges in a list container. */
      typedef std::list<Range> Container;

      /** \brief Type definition to store pointers to RangeListIterators in a list container. */
      typedef std::list<RangeListIterator *> IteratorContainer;

    protected:
      /**
      * \internal
      * \brief The possible states of an iterator.
      */
      enum op {
        op_None,        ///< \internal \brief None of the add(), remove(), next() or previous() was called.
        op_Add,         ///< \internal \brief The last call was an add().
        op_Remove,      ///< \internal \brief The last call was a remove().
        op_Next,        ///< \internal \brief The last call was a previous().
        op_Previous,    ///< \internal \brief The last call was a previous().
        op_Invalidated  ///< \internal \brief The node containing the container of the iterator is deleted. 
      };

      RangeListIterator(Container *container, IteratorContainer *it);
      Container::iterator nextItem() const;
      Container::iterator previousItem() const;
      Container::iterator safeRemove(const Container::iterator& it);
      void invalidate();
      void add(const Range& r);
      void remove();

    public:
      RangeListIterator(const RangeListIterator &rli);
      RangeListIterator();
      RangeListIterator& operator=(const RangeListIterator &rli);
      ~RangeListIterator();
      const Range& next();
      const Range& previous();
      bool hasNext() const;
      bool hasPrevious() const;
      bool equals(const RangeListIterator& it) const;

    protected:
      Container *container;             ///< \internal \brief Pointer to the Container.
      Container::iterator it;           ///< \internal \brief Inner iterator of the Container.
      IteratorContainer *iterators;     ///< \internal \brief Pointer to the list of the iterators of the Container.
      op lastOp;                        ///< \internal \brief Inner state of the iterator.

    friend class base::Named;
    friend class base::PositionedWithoutComment;
    friend class expr::Conditional;
    friend class expr::NewArray;
    friend class statm::Assert;
    friend class statm::BasicFor;
    friend class statm::Do;
    friend class statm::EnhancedFor;
    friend class statm::For;
    friend class statm::Handler;
    friend class statm::If;
    friend class statm::Jump;
    friend class statm::LabeledStatement;
    friend class statm::Switch;
    friend class statm::SwitchLabel;
    friend class statm::Try;
    friend class struc::AnnotationType;
    friend class struc::AnnotationTypeElement;
    friend class struc::Enum;
    friend class struc::Import;
    friend class struc::MethodDeclaration;
    friend class struc::NamedDeclaration;
    friend class struc::NormalMethod;
    friend class struc::Parameter;
    friend class struc::StaticInitializerBlock;
    friend class struc::TypeDeclaration;
    friend class struc::Variable;
  };

  typedef struct {
      RangeListIterator::Container container;
      RangeListIterator::IteratorContainer iterators;
  } RangeList;

  typedef union {
    Range::PositionInfo posInfo;
    struct {
      RangeListIterator::Container *container;
      RangeListIterator::IteratorContainer *iterators;
    } ranges;
  } MultiRange;


}}}
#endif

