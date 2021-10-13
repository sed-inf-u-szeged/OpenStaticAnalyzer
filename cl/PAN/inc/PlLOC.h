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

#ifndef LLOC_H
#define LLOC_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "PBuilder.h"

namespace columbus {
class PlLOC {

private:
  int strreplace( std::string &str, const std::string &find_what, const std::string &replace_with);
  std::string modifyEscapedChar( std::string str);
  size_t findFirst( const std::string& line, std::vector<std::string> what, std::string& significantChar, int from);
  int strcount( std::string &str, const std::string &find_what, int endPos);

  std::string leftrim(std::string str);

  std::map<int, NodeId> commentMap;

public:
  PlLOC(){};

  // return the logical lines of the file, process comments
  std::vector<int> processLines (const std::string &file, PBuilder& builder);

  std::map<int, NodeId>& getCommentMap();

};
}

#endif
