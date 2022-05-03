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

#ifndef _CAN_CANCOMMON_H
#define _CAN_CANCOMMON_H

#include<string>
#include<tuple>
#include<cctype>
#include <lim/inc/lim.h>
#include <common/inc/StringSup.h>

struct SourcePoint {
  unsigned line, column;

  bool operator<(const SourcePoint& rhs) const
  {
    return std::tie(line, column) < std::tie(rhs.line, rhs.column);
  }
  bool operator==(const SourcePoint& rhs) const
  {
    return std::tie(line, column) == std::tie(rhs.line, rhs.column);
  }
};

struct MyScope
{
  SourcePoint begin, end;
  columbus::lim::asg::logical::Member* member;

  bool operator==(const MyScope& rhs) const
  {
    return std::tie(begin, end, member) == std::tie(rhs.begin, rhs.end, rhs.member);
  }
};

struct ScopeGuard
{
  enum GuardType { BEGIN, END };

  MyScope scope;
  GuardType guardType;

  SourcePoint getSourcePoint() const
  {
    if (guardType == BEGIN)
      return scope.begin;
    else
      return scope.end;
  }

  bool operator<(const ScopeGuard& rhs) const
  {
    return getSourcePoint() < rhs.getSourcePoint();
  }
};

struct CommentData
{
  struct Compare
  {
    // Since the comment field is not used in the comparison it can be modified after a CommantData is inserted into a set.
    // If the comparison is changed the insertion has to be modified in the loadCommentStructure function too!
    bool operator()(const CommentData& lhs, const CommentData& rhs) const
    {
      if (lhs.begin.line != rhs.begin.line)
        return lhs.begin.line < rhs.begin.line;

      return lhs.begin.column < rhs.begin.column;
    }
  };

  SourcePoint begin, end;

  std::string text;

  unsigned numberOfLines() const
  {
    return end.line - begin.line + 1;
  }

  bool overlaps(const CommentData& other) const
  {
    return this->begin.line == other.end.line || other.begin.line == this->end.line;
  }

};

class CANFilePathRenamer {
  std::string &changePathFrom, &changePathTo;
public:
  CANFilePathRenamer(std::string &changePathFrom, std::string &changePathTo)
    : changePathFrom(changePathFrom), changePathTo(changePathTo) {}

  std::string changeToLIMCompatible(std::string filePath) {
    std::string ret;
    if (changePathFrom.empty())
      ret = filePath;
    else
      ret = common::replace(filePath.data(), changePathFrom.c_str(), changePathTo.c_str());
    if (ret.size() >= 2 && ret[1] == ':')
      ret[0] = (char)tolower(ret[0]);
    return ret;
  }
};
#endif