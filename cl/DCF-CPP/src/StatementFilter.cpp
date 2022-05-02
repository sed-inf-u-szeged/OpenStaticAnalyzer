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


#include "../inc/messages.h"
#include "../inc/dcm.h"
#include "../inc/StatementFilter.h"
#include "../inc/CppSerializeAST.h"
#include <clang/AST/Stmt.h>


bool StatementFilter::isFiltered( const columbus::genealogy::CloneClass& cc )
{
  for(columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt)
  {
    const columbus::genealogy::CloneInstance& ci = *cloneInstanceIt;
    unsigned ci_position = dcm.getPosition(ci.getId());
    unsigned length = dcm.getLength(cc.getId());
    unsigned counter = 0;
    bool switch_found = false;
    for(unsigned int positionIndex = ci_position; positionIndex < ci_position + length; ++positionIndex)
    {
      int nodeKind = dcm.getNodeKindAt(positionIndex);
      const ASTNodeInfo* nodeInfo = dcm.getNode(positionIndex);
      if (nodeInfo == nullptr)
      {
        continue;
      }

      if ((nodeKind & NodeMask::NodeTypeMask) == NodeType::Statement)
      {
        if ((nodeKind & NodeMask::NodeKindMask) == clang::Stmt::SwitchStmtClass)
          switch_found = true;
        else if (((nodeKind & NodeMask::NodeKindMask) == clang::Stmt::CaseStmtClass) && !switch_found)
          return true;

        ++counter;
      }

    }
    if (counter >= config.minStatements)
      return false;
  } // iterating over all the clone instances in this class
  return true;
}

