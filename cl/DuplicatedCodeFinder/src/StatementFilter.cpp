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


#include "../inc/common.h"
#include "../inc/dcm.h"
#include "../inc/StatementFilter.h"
#include <vector>

using namespace columbus;

bool StatementFilter::isFiltered( const genealogy::CloneClass& cc )
{
  for(genealogy::ListIterator<genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt) {
    const genealogy::CloneInstance& ci = *cloneInstanceIt;
    unsigned ci_position = dcm.getPosition(ci.getId());
    unsigned length = dcm.getLength(cc.getId());
    unsigned counter = 0;

#if defined SCHEMA_JAVA || defined SCHEMA_JAVASCRIPT || defined SCHEMA_CSHARP
    bool switch_found = false;
#endif
    for(unsigned int positionIndex = ci_position; positionIndex < ci_position + length; ++positionIndex) {
      const ClonePositioned* position = dcm.getNode(positionIndex);
      if (position == NULL)
        continue;

      LANGUAGE_NAMESPACE::NodeKind nodeKind = static_cast<LANGUAGE_NAMESPACE::NodeKind>(position->getNodeKind());

#if defined SCHEMA_JAVA
      if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkStatement))
      {
        if (!AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkVariableDeclaration))
        {
          if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkSwitch))
            switch_found = true;

          ++counter;
        }
      }
      else if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkSwitchLabel) && !switch_found)
        return true;

#elif defined SCHEMA_JAVASCRIPT
      if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkStatement))
      {
        if (!AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkVariableDeclaration))
        {
          if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkSwitchStatement))
            switch_found = true;

          ++counter;
        }
      }
      else if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkSwitchCase) && !switch_found)
        return true;


#elif defined SCHEMA_CSHARP

      if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkStatementSyntax))
      {

        if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkSwitchStatementSyntax))
          switch_found = true;

        ++counter;
      }
      else if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkSwitchLabelSyntax) && !switch_found)
        return true;

#elif defined SCHEMA_PYTHON

      if (AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkStatement) &&
          (!AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkImportStatement) &&
           !AlgorithmCommon::getIsBaseClassKind(nodeKind, LANGUAGE_NAMESPACE::ndkAlias)))
      {
        ++counter;
      }
#endif
    }
    if (counter >= config.minStatements)
      return false;
  } // iterating over all the clone instances in this class

  return true;
}

