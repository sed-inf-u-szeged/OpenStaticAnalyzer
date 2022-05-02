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

#ifndef __CLONE_POSITIONED_H
#define __CLONE_POSITIONED_H
/**
 * \brief This class is store the extract of asg node contain the position data of asg node. 
 */

#include <AsgCommon.h>
#include <strtable/inc/StrTable.h>
#include <set>

class ASTNodeInfo
{
private:
  static columbus::StrTable paths;

  columbus::Key path;
  unsigned int line;
  unsigned int col;
  unsigned int endLine;
  unsigned int endCol;

  columbus::NodeId nodeId;
  columbus::NodeId limNodeId;
  columbus::NodeId translationUnitId;
  columbus::Key    TUPathKey;
  columbus::NodeId limComponentId;
  std::vector<int>* extraLines;

public:

  
  ASTNodeInfo(const std::string& _path,
              unsigned int _line,
              unsigned int _col,
              unsigned int _endLine,
              unsigned int _endCol,
              columbus::NodeId _nodeId,
              columbus::NodeId limNodeId,
              columbus::NodeId translationUnitId,
              const std::string& _tuPath,
              columbus::NodeId limComponentId)
    : path(paths.set(_path))
    , line (_line)
    , col (_col)
    , endLine(_endLine)
    , endCol(_endCol)
    , nodeId(_nodeId)
    , limNodeId(limNodeId)
    , translationUnitId(translationUnitId)
    , TUPathKey(paths.set(_tuPath))
    , limComponentId(limComponentId)
    , extraLines (nullptr)
  {

  }

  ~ASTNodeInfo()
  {
    delete extraLines;
  }

  ASTNodeInfo& operator=(const ASTNodeInfo&) = delete;

  static const std::string& getStringPath(columbus::Key path) { return paths.get(path); }
  static columbus::Key getPathKey(const std::string& path) { return paths.set(path); }

  columbus::Key getPath() const { return path; }
  const std::string& getStringPath() const { return paths.get(path); }
  unsigned int getLine() const { return line; }
  unsigned int getCol() const { return col; }
  unsigned int getEndLine() const { return endLine; }
  unsigned int getEndCol() const { return endCol; }
  int getPathsSize() const { return paths.getNumberOfBuckets(); }

  columbus::NodeId getId() const { return nodeId; }
  columbus::NodeId getLimNodeId() const { return limNodeId; }
  columbus::NodeId getTranslationUnitId() const { return translationUnitId; }
  columbus::Key getTUPath() const { return TUPathKey; }
  const std::string& getStringTUPath() const { return paths.get(TUPathKey); }
  columbus::NodeId getLimComponentId() const { return limComponentId; }
  void setLimNodeId(columbus::NodeId nId) { limNodeId = nId; }
  void setLimComponentId(columbus::NodeId nId) { limComponentId = nId; }

  void addLine(int line)
  {
    if (extraLines == nullptr)
      extraLines = new std::vector<int>();

    if (extraLines != nullptr)
      extraLines->push_back(line);
  }

  std::vector<int>* getExtraLines() const
  {
    return extraLines;
  }


  void dump() const;
};

#endif
