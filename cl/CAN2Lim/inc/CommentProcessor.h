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

#ifndef _CAN2LIM_COMMENTPROCESSOR_H
#define _CAN2LIM_COMMENTPROCESSOR_H

#include <lim/inc/lim.h>
#include <clangsupport/CANCommon.h>
#include <vector>
#include <unordered_map>

class GlobalASTConversionInfo;

class CommentProcessor {
public:
  GlobalASTConversionInfo& conversionInfo;

  std::vector<std::pair<columbus::lim::asg::logical::Member*, CommentData>> docCache;

  // Stores comments ordered according to source position.
  std::unordered_map<columbus::lim::asg::physical::File*,std::set<CommentData, CommentData::Compare>> commentTablePerFile;

  void addDocumentationToMember(columbus::lim::asg::logical::Member * member, const CommentData & comment, bool postAdd);
  void addCommentToMember(columbus::lim::asg::logical::Member * member, const CommentData & comment, const CommentData * prevComment);

public:
  CommentProcessor(GlobalASTConversionInfo & conversionInfo);

  void bindCommentsToLimTree(columbus::lim::asg::physical::File* file);
  void loadCommentStructure(const std::string & astFile);

};

#endif