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

#ifndef __CLONE_POSITIONED_H
#define __CLONE_POSITIONED_H
/**
 * \brief This class is store the extract of asg node contain the position data of asg node. 
 */
class ClonePositioned {
private:
  static columbus::StrTable paths;
  columbus::Key path;
  unsigned int line;
  unsigned int col;
  unsigned int endLine;
  unsigned int endCol;

  unsigned int nodeKind;
  columbus::NodeId nodeId;
  columbus::NodeId limNodeId;
  columbus::NodeId limComponentId;
  
public:

  
  ClonePositioned(  const std::string& _path
                  , unsigned int _line
                  , unsigned int _col
                  , unsigned int _endLine
                  , unsigned int _endCol
                  , unsigned int _nodeKind
                  , columbus::NodeId _nodeId
                  , columbus::NodeId limNodeId
                  , columbus::NodeId limComponentId)
    : path(paths.set(_path))
    , line (_line)
    , col (_col)
    , endLine(_endLine)
    , endCol(_endCol)
    , nodeKind(_nodeKind)
    , nodeId(_nodeId)
    , limNodeId(limNodeId)
    , limComponentId(limComponentId)
  {

  }

  columbus::Key getPath() const { return path; }
  const std::string& getStringPath() const { return paths.get(path); }

  unsigned int  getLine() const { return line; }
  unsigned int  getCol() const { return col; }
  unsigned int  getEndLine() const { return endLine; }
  unsigned int  getEndCol() const { return endCol; }

  unsigned int getNodeKind() const { return nodeKind; }
  columbus::NodeId getId() const { return nodeId; }
  columbus::NodeId getLimNodeId() const { return limNodeId; }
  columbus::NodeId getLimComponentId() const { return limComponentId; }
};

#endif
