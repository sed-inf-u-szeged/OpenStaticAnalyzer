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


#ifndef _CONTR_PROFILE_COMMON_H_
#define _CONTR_PROFILE_COMMON_H_

#include "ProfileHandler.h"

#include <rul/inc/RulHandler.h>
#include <io/inc/CsvIO.h>


namespace columbus {

namespace controller {

  /**
  * \brief Process the rules csv and update the rule files.
  * \param profile [in] the profile
  * \param rulHandlers [in,out] the RulHandlers of the rule files, mapped by tool id
  * \param runTool [in] tool is running, mapped by tool id
  * \param rulesCSV [in] the file name of the rules csv
  */
  void profileProcessRulesCSV(const ProfileHandler& profile, std::map<std::string, columbus::rul::RulHandler*>& rulHandlers, std::map<std::string, bool>& runTool, const std::string& rulesCSV);

  /**
  * \brief Process the thresholds for a tool.
  * \param profile [in] the profile
  * \param toolName [in] the name of the tool
  * \param thresholdsFileIn [in] the original thresholds file name
  * \param thresholdsFileOut [in] the output thresholds file name
  */
  void profileProcessToolThresholds(const ProfileHandler& profile, const std::string& toolName, const std::string& thresholdsFileIn, const std::string& thresholdsFileOut);

}
}



#endif /* _CONTR_PROFILE_COMMON_H_ */