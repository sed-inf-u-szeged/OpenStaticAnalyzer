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

#ifndef _LINK_WRAPPER_H
#define _LINK_WRAPPER_H

#include <AbstractWrapperLib/inc/abstractwrapper/AbstractLinker.h>
#include <AbstractWrapperLib/inc/paramsup/ParamsupCommon.h>
#include <string>

namespace ColumbusWrappers {
  class LinkWrapper : public AbstractLinker {
/**
 * @brief This class can processes parameter list of link.exe and calls CANLink.
 */
  public:
    /**
     * @brief Public constructor for LinkWrapper class.
     *
     * @param configfile     [in] The input configuration file (analyzer_wrapper_config.ini) for analyzer wrapper.
     */
    LinkWrapper(std::string configfile);

    /**
     * @brief It calls parameter processor functions and calls CANLib.
     *
     * @param argc            [in] Number of input arguments of wrapper tool.
     * @param argv            [in] Array for input arguments of wrapper tool.
     */
    bool process(int argc, char** argv);

  private:
    Warnings linkWarnings;        ///< The problematic and unknow arguments are put into this struct.
    LinkerArgs linkArgs;          ///< The arguments of CANLinker and not handled arguments are put into this struct.
  };
}
#endif
