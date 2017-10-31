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

#ifndef _COMMON_DIRFILTER_H_
#define _COMMON_DIRFILTER_H_

#include <string>
#include <list>
#include <map>

class DirectoryFilter {
public:
  DirectoryFilter();
  ~DirectoryFilter();
  /**
  * \brief Loads the filter file and sets filter_in and filter_out lists.
  * \param fltp       [in] The given filter file.
  */
  bool openFilterFile(std::string fltp);

  /**
  * \brief Determines if the given path is filtered or not. It depends on the given filter file.
  *        If the given directory path starts with "-" in the filter file or cannot be found in the filter file, and this path will be filtered.
  * \param path       [in] The given path.
  * \return           True, if the given path is filtered. Default is false.
  */
  bool isFilteredOut(std::string path);

  /**
  * \return           True, if the filter_list is empty, false otherwise.
  */
  bool isEmpty();

private:
  std::list<std::string> filter_list;
  std::map<std::string, bool> filter_cache;
};

#endif
