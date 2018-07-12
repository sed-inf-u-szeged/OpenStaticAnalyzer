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

#ifndef _LIBPARAMSUP_H
#define _LIBPARAMSUP_H

#include <list>
#include <string>
#include "ParamsupCommon.h"

namespace ColumbusWrappers { 

namespace LibWrapperSup {

  /**
   * @brief Determines whether the given file is object file or not.
   * @param filename     [in] The given filename.
   * @return                  True, if the given file is object file.
   */
  bool isObjectFile(std::string filename);

  /**
   * @brief Determines whether the given file is archive file or not.
   * @param filename     [in] The given filename.
   * @return                  True, if the given file is archive file.
   */
  bool isArchiveFile(std::string filename);

  /**
   * @brief Examines the given lib argument whether it is a known but not handled argument or not. 
   *        If it is a known but not handled argument, puts this into the not_handled_args list of libArgs struct.
   *
   * @param it             [in] Iterator pointed to the actual element of the argument list.
   * @param libArgs        [out] The known but not handled argument is put into this struct.
   * @return                     EC_FOUND if recognizes the argument
   * @return                     EC_NOT_FOUND if not recognizes the argument
   * @return                     EC_ERROR if the given argument is not correct.
   */
  ColumbusWrappers::ParErrorCode examineNotHandledArgument(const std::list<std::string>::iterator& it, ArchiveArgs& libArgs);

  /**
   * @brief Processes the given argument list. It calls the examineNotHandledArgument method.
   *        The arguments of CANLib (which are according to known arguments) are put into the libArgs struct.
   *        The unknown or problematic arguments are put into the arWarnings struct.
   *
   * @param args           [in] The given lib argument list.
   * @param libArgs        [out] The arguments of CANLib (which are according to known lib arguments) and the not handled arguments are put into this struct.
   * @param libWarnings    [out] The unknown or problematic arguments are put into this struct.
   * @return                     True, if it can processes the given argument list.
   */
  bool archiveArguments(std::list<std::string> args, ArchiveArgs& libArgs, Warnings& libWarnings);

}}

#endif