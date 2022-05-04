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

#include <vector>

#include "../inc/RepeatingLinesFilter.h"
#include "../inc/dcm.h"
#include "../inc/messages.h"


bool RepeatingLinesFilter::isFiltered(const columbus::genealogy::CloneClass& cc) {
  for(columbus::genealogy::ListIterator<columbus::genealogy::CloneInstance> cloneInstanceIt = cc.getItemsListIteratorBegin();cloneInstanceIt != cc.getItemsListIteratorEnd();++cloneInstanceIt) {
    const columbus::genealogy::CloneInstance& ci = *cloneInstanceIt;
    std::vector<int> cppNodes;
    unsigned int counter = 0;
    bool firstLine = true;
    bool firstNode = true;
    long currentLine = 0;
    unsigned ci_position = dcm.getPosition(ci.getId());
    unsigned length = dcm.getLength(cc.getId());
    for(unsigned int positionIndex = ci_position; positionIndex < ci_position + length; ++positionIndex)
    {
      const ASTNodeInfo* position = dcm.getNode(positionIndex);
      if(!position) continue;
      if(firstNode)
        currentLine = position->getLine();
      else if(currentLine != position->getLine()) {
        // we are in a new line
        counter = 0;
        currentLine = position->getLine();
        firstLine = false;
      }
      if(firstLine) {
        cppNodes.push_back(dcm.getNodeKindAt(positionIndex));
      } else {
        //we are just comparing
        //:HACK
        if(cppNodes.size() <= counter) 
          return false;
        if (cppNodes[counter++] != dcm.getNodeKindAt(positionIndex)) {
          //the clone class does not consist of same lines only
          return false;
        }
      }
      firstNode=false;
    }
  } // iterating over all the clone instances in this class
  return true;
}

