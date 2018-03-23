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


#include "../inc/common.h"
#include "../inc/dcm.h"
#include "../inc/StatementFilter.h"
#include <vector>


bool StatementFilter::isFiltered( const columbus::genealogy::CloneClass& cc )
{
  for(columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt) {
    const columbus::genealogy::CloneInstance& ci = *cloneInstanceIt;
    unsigned ci_position = dcm.getPosition(ci.getId());
    unsigned length = dcm.getLength(cc.getId());
    for(unsigned int positionIndex = ci_position; positionIndex < ci_position + length; ++positionIndex) {
      const ClonePositioned* position = dcm.getNode(positionIndex);
      if (position == NULL)
        continue;

#if defined SCHEMA_JAVA
      if (columbus::LANGUAGE_NAMESPACE::Common::getIsBaseClassKind((columbus::LANGUAGE_NAMESPACE::NodeKind)position->getNodeKind(),columbus::LANGUAGE_NAMESPACE::ndkStatement))
        return false;

#elif defined SCHEMA_PYTHON
      if (columbus::LANGUAGE_NAMESPACE::Common::getIsBaseClassKind((columbus::LANGUAGE_NAMESPACE::NodeKind)position->getNodeKind(),columbus::LANGUAGE_NAMESPACE::ndkStatement)){
        if (!columbus::LANGUAGE_NAMESPACE::Common::getIsBaseClassKind((columbus::LANGUAGE_NAMESPACE::NodeKind)position->getNodeKind(),columbus::LANGUAGE_NAMESPACE::ndkImportStatement) &&
            !columbus::LANGUAGE_NAMESPACE::Common::getIsBaseClassKind((columbus::LANGUAGE_NAMESPACE::NodeKind)position->getNodeKind(),columbus::LANGUAGE_NAMESPACE::ndkAlias))
        return false;
      }
#elif defined SCHEMA_CSHARP
      if (columbus::LANGUAGE_NAMESPACE::Common::getIsBaseClassKind((columbus::LANGUAGE_NAMESPACE::NodeKind)position->getNodeKind(),columbus::LANGUAGE_NAMESPACE::ndkStatementSyntax))
        return false;
#endif

    }
  } // iterating over all the clone instances in this class
  return true;
}

