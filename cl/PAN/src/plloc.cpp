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

#include "../inc/PlLOC.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <common/inc/WriteMessage.h>
#include "../inc/messages.h"

using namespace std;
using namespace columbus;
using namespace common;


int PlLOC::strreplace(std::string &str, const std::string &find_what, const std::string &replace_with) {
  std::string::size_type pos=0;
  int count = 0;

  while((pos=str.find(find_what, pos))!=std::string::npos) {
    str.erase(pos, find_what.length());
    str.insert(pos, replace_with);
    pos+=replace_with.length();
    count++;
  }

  return count;
}

std::string PlLOC::modifyEscapedChar( std::string str){
  std::string::size_type pos=0;
  while((pos=str.find('\\', pos))!=std::string::npos) {
    str.erase(pos, 2);
    str.insert(pos, "$$");
    pos+=2;
  }
  return str;
}

int PlLOC::strcount(std::string &str, const std::string &find_what, int endPos) {
  std::string::size_type pos=0;
  int count = 0;

  while((pos=str.find(find_what, pos))!=std::string::npos) {
    pos+=find_what.length();
    count++;
  }

  return count;
}


std::string PlLOC::leftrim(std::string str) {
  size_t start = str.find_first_not_of(" \t\n\r");
  if(start == std::string::npos) return "";
  return str.substr(start, str.length());
}

size_t PlLOC::findFirst(const std::string &line, vector<string> tokens, std::string &significantToken, int from){
  size_t lastTokenPos = string::npos;
  for (vector<string>::iterator token = tokens.begin(); token != tokens.end(); ++token){
    size_t tokenPos = line.find(*token, from);
    if (tokenPos != string::npos){
      if (lastTokenPos == string::npos || tokenPos < lastTokenPos){
        lastTokenPos = tokenPos;
        significantToken = *token;
      }
    }
  }
  return lastTokenPos;
}

vector<int> PlLOC::processLines(const std::string& name, PBuilder& builder) {
  builder.setPath(const_cast<std::string&>(name));
  std::string myline;
  int lc = 0;
  int moduleEndLine = lc;
  vector<int> lines;
  bool docstring = false;

  ifstream infile(name.c_str ());

  if (!infile.is_open()) {
    WriteMsg::write(CMSG_CANNOT_OPEN_FILE, name.c_str());
    exit(1);
  }

  vector<string> significantTokens; // search for these strings in the line, the search order is important
  significantTokens.push_back("\"\"\"");
  significantTokens.push_back("'''");
  significantTokens.push_back("\"");
  significantTokens.push_back("'");
  string multiLineLiteralStarterString = "";
  while (1) {
    getline(infile, myline);
    ++lc;
    //process comments
    string lineWithoutBackslashes = modifyEscapedChar(myline); // use this version of the line when search for quotes

    string firstSignificantToken;
    size_t bannedRangeEndPos = 0;
    size_t bannedRangeStartPos = 0;
    size_t shift = 0;
    // if we are in a multi-line stringliteral, than search for the closer quote from 0 col
    if (!multiLineLiteralStarterString.empty()){
      firstSignificantToken = multiLineLiteralStarterString;
      shift = firstSignificantToken.length();
      if (shift == 1)
        bannedRangeStartPos = string::npos;
    } else { // else search for the first quote in the line
      bannedRangeStartPos = findFirst(lineWithoutBackslashes, significantTokens, firstSignificantToken, bannedRangeEndPos);
    }
    set<size_t> bannedPositions;
    while (bannedRangeStartPos != string::npos){
      bannedRangeEndPos = lineWithoutBackslashes.find(firstSignificantToken, bannedRangeStartPos + firstSignificantToken.length() - shift); // find the closer quote for the string literal
      shift = 0;
      if (bannedRangeEndPos == string::npos){ //there is no closer quote, we ar in a multi-line literal
        bannedRangeEndPos = myline.length(); // ban the whole line
        multiLineLiteralStarterString = firstSignificantToken; // store the literal starter token
      } else {
        multiLineLiteralStarterString = "";
        bannedRangeEndPos += firstSignificantToken.length();
      }

      for (size_t i = bannedRangeStartPos; i < bannedRangeEndPos; ++i) {
        bannedPositions.insert(i);
      }
      bannedRangeStartPos = findFirst(lineWithoutBackslashes, significantTokens, firstSignificantToken, bannedRangeEndPos);
    }

    size_t hashPos = 0;
    while ( (hashPos = myline.find('#', hashPos) ) != string::npos){
      if (bannedPositions.find(hashPos) == bannedPositions.end()){
        NodeId doc = builder.buildComment(myline.substr(hashPos));
        builder.setIncreasedPosition(doc, lc, hashPos, lc, myline.length());
        commentMap.insert(std::pair<int, NodeId>(lc, doc));
        break;
      }
      hashPos++;
    }
    //process comments end

    std::string trimmedLine = leftrim(myline);    // remove leading white spaces
    if (trimmedLine.length() != 0){
      moduleEndLine = lc;
    }
    if (!docstring) {
      if (trimmedLine.length() == 0) {
      } else if (trimmedLine[0] == '#') {
      } else {
        lines.push_back(lc);
      }
    } else {
      lines.push_back(lc);
    }

    bool oddQuote = strcount(trimmedLine, "\"\"\"", trimmedLine.length()) % 2 == 1;
    bool oddApos = strcount(trimmedLine, "'''", trimmedLine.length()) % 2 == 1;
    if (oddQuote || oddApos) docstring = !docstring; 

    if (infile.eof()) break;
  }

  infile.close();
  lines.push_back(moduleEndLine); // the last stored number is the module's endLine
  return lines;
}

std::map<int, NodeId>& PlLOC::getCommentMap(){
  return commentMap;
}

