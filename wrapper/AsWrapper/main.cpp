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

/**
 * @page ArWrapper
 *
 * @brief This wrapper program can processes parameter list of ar and calls CANLib. It uses analyzer_wrapper_config.ini file.
 *
 * 
 */

/**
 * @file wrapper/ArWrapper/main.cpp
 * @brief This wrapper program can processes parameter list of ar and calls CANLib. It uses analyzer_wrapper_config.ini file.
 */

#include "AsWrapper/AsWrapper.h"
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <AnalyzerWrapperConfig/AnalyzerWrapperConfig.h>

int main(int argc, char** argv) {
  int ret = 0;

  ColumbusWrappers::AsWrapper cw(common::getExecutableProgramDir() + DIRDIVSTRING + ANALYZER_WRAPPER_CONFIG);
  ret = cw.process(argc-1, argv+1) ? 0 : 1;

  return ret;
}