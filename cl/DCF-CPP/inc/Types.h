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

#ifndef _DCF_TYPES_H_
#define _DCF_TYPES_H_

#include <map>
#include <set>
#include <AsgCommon.h>
#include <strtable/inc/StrTable.h>


namespace columbus
{

typedef std::map<Key, std::map<NodeId, NodeId>> ASTNodeReferenceMap;
typedef std::map<Key, std::map<NodeId, std::vector<NodeId>>> ASTNodeInverseReferenceMap;
typedef std::map<Key, std::map<NodeId, Key>> ASTNodeReferencePathMap;

struct LineIdentifier {

  LineIdentifier()
    : path(0)
    , line(0)
  {
  }

  LineIdentifier (const LineIdentifier & p)
    : path(p.path)
    , line(p.line)
  {
  }

  LineIdentifier (columbus::Key path, int line)
    : path(path)
    , line(line)
  {
  }

  bool operator<(const LineIdentifier& second) const
  {
    if (line != second.line)
      return line < second.line;

    return path < second.path;
  }

  //This is the key of the path string (in the lim asg string table)
  columbus::Key path;
  int line;
};


struct SerializationData
{
  // Vector containing the sequence of node kinds
  std::vector<int> nodeKindSequence;

  // Vector containing sequence of additional information about each node
  std::vector<ASTNodeInfo*> nodeInfoSequence;

  // Node references in each AST
  ASTNodeReferenceMap referencesMap;

  // Inverse of the references
  ASTNodeInverseReferenceMap inverseReferencesMap;

  // Path info for all the nodes stored in the reference maps for CE metrics
  ASTNodeReferencePathMap nodeReferencePathMap;


  std::set<LineIdentifier> visitedLines;
};

}


#endif
