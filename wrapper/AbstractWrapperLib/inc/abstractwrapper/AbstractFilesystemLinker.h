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

#ifndef __ABSTRACT_FS_LINKER_H
#define __ABSTRACT_FS_LINKER_H

#include <string>
#include <vector>

#include "AbstractWrapper.h"
#include "../paramsup/ParamsupCommon.h"

namespace ColumbusWrappers {
  class AbstractFSLinker : public AbstractWrapper {
  public:
    /**
     * @brief Constructor of AbstractArchive class.
     * @param configfile     [in] The name of the config file.
     */
    AbstractFSLinker(const std::string& configfile);

    /**
     * @brief Creates symbolic links for the .ast and .aast files of the .o and .a files
     * @param arArgs        [in] The arguments of the ln.
     * @return                   True, if there is no problem with execution.
     */
    bool executeFSLink(const LnArgs& arArgs) const;

  protected:
    /**
     * @brief Reads options from config file.
     */
    void readConfig();

    /**
     * @brief Creates links with the given base file name and extensions
     */
    void createLink(const std::string &target, const std::string &link, const std::vector<std::string> &exts) const;

  };
}

#endif
