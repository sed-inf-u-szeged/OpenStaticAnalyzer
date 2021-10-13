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

#ifndef __ABSTRACT_ARCHIVE_H
#define __ABSTRACT_ARCHIVE_H

#include <string>
#include <set>
#include "AbstractWrapper.h"
#include "AbstractWrapperLib/inc/paramsup/ParamsupCommon.h"

namespace ColumbusWrappers {
  class AbstractArchive : public AbstractWrapper {
  public:
    /**
     * @brief Constructor of AbstractArchive class.
     * @param configfile     [in] The name of the config file.
     */
    AbstractArchive(std::string configfile);

    /**
     * @brief Collects the arguments for CANLib and calls CANLib with this command line it.
     * @param arArgs        [out] The arguments of CANLib and the not handled arguments are in this struct.
     * @return                    True, if there is no problem with execution.
     */
    bool executeArchive(ArchiveArgs& arArgs) const;
    
  protected:
    /**
     * @brief Reads options from config file.
     */
    void readConfig();

    /**
     * @brief calculate the name of the aast.
     */
    std::string objectNameToAstName(const std::string& objectName) const ;

    int archive_needtorun;                                                 ///< archiving needed or not from config
    int archive_needstat;                                                  ///< CANLib needed to create stat file or not
    int archive_ml;                                                        ///< CANLib message level
    std::set<std::pair<std::string, int> > archive_paramtoskip;            ///< arguments and their number of parameters to skip
    int archive_numofparamtoskip;                                          ///< number of arguments to skip
    std::vector<std::string> archive_extraparam;                           ///< extra parameters for CANLib
    int archive_numofextraparam;                                           ///< number of extra parameters

    std::string archive_tool;                                              ///< name of the compiler tool (CANLib)
  };
}

#endif
