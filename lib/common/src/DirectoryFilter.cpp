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

#include "../inc/DirectoryFilter.h"
#include "../inc/WriteMessage.h"
#include "../inc/messages.h"
#include "../inc/StringSup.h"
#include <boost/regex.hpp>
#include <fstream>

using namespace common;

bool DirectoryFilter::isFilteredOut( std::string path )
{
  if (filter_list.empty())
    return false;

  std::map<std::string, bool>::const_iterator pathIt = filter_cache.find(path);
  if (pathIt != filter_cache.end())
    return pathIt->second;
    
  bool isFiltered = false;

  for (std::list<std::string>::const_reverse_iterator rit = filter_list.rbegin(); rit != filter_list.rend(); ++rit) {
    try {
      char fltp = (*rit)[0];
      std::string tmp = rit->substr(1, std::string::npos);


#ifdef __unix__
      boost::regex re(tmp, boost::regex::extended);
#endif

#ifdef _WIN32
      boost::regex re(tmp, boost::regex::extended | boost::regex::icase);
#endif

      if(boost::regex_search(path, re)) {
        if (fltp == '-') {
          isFiltered = true;
        }
        break;
      }
    }
    catch (boost::bad_expression e ){
      WriteMsg::write(CMSG_CANT_PARSE,rit->c_str(),e.what());
    }
  }
  
  filter_cache.insert(std::make_pair(path, isFiltered));
    
  return isFiltered;
}

bool DirectoryFilter::openFilterFile( std::string fltp )
{
  std::ifstream ifs(fltp.c_str());
  if (ifs.is_open()) {
    std::string line;
    while (ifs.good()) {
      std::getline(ifs,line);
      
      if (!line.empty()) {
        if (line[line.length()-1] == 0xD) {
          line.erase(line.length()-1,1);
        }
      }

      if (!line.empty()) {
        if (line[0] == '+' || line[0] == '-') {
          filter_list.push_back(line);
        } else {
          continue;
        }
      }
    }
  } else {
    return false;
  }
  return true;
}

bool DirectoryFilter::isEmpty()
{
  return filter_list.empty();
}

DirectoryFilter::DirectoryFilter()
  :filter_list()
{
}

DirectoryFilter::~DirectoryFilter()
{
}
