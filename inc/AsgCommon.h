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

#ifndef _ASGCOMMON_H_
#define _ASGCOMMON_H_

#include <string>
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>

namespace columbus {

  /**
  * \brief Type definition for NodeId which can be used in all asgs.
  */
  typedef unsigned int NodeId;


  /**
  * \brief Loads the filter file for the given ASG file if it is not older than it.
  */

  template <typename Factory>
  bool loadFilter(Factory& factory, const std::string& asgFilename, const std::string& filterExtension) {
    factory.initializeFilter();
    std::string filterFilename = common::pathRemoveExtension(asgFilename) + filterExtension;
    int compareResult = common::fileTimeCmp(asgFilename, filterFilename);
    switch (compareResult) {
      case 0:
      case -1:
        factory.loadFilter(filterFilename);
        return true;
      case 1:
        common::WriteMsg::write(common::WriteMsg::mlWarning, "WARNING: Filter file (%s) is older than the ASG file (%s). Filter is not loaded! \n", filterFilename.c_str(), asgFilename.c_str());
        return false;
      case -2:
        common::WriteMsg::write(common::WriteMsg::mlWarning, "WARNING: File (%s) is not found! \n", asgFilename.c_str());
        return false;
      case -3:
        common::WriteMsg::write(common::WriteMsg::mlWarning, "WARNING: File (%s) is not found!  Filter is not loaded! \n", filterFilename.c_str());
        return false;
    }
    return false;
  }

}

#endif // _ASGCOMMON_H_
