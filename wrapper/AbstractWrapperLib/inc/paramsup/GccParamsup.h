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

#ifndef _GCCPARAMSUP_H
#define _GCCPARAMSUP_H

#include <list>
#include <string>
#include "ParamsupCommon.h"

namespace ColumbusWrappers {

namespace GccWrapperSup {

  /**
   * @brief Examines the given preprocessor argument. If it has parameter and this parameter is the next element of the argument list,
   *        the iterator is moved to the next element (if that is not the end iterator of the argument list).
   *        If it is known argument, puts the argument of CAN (which is according to actual known argument) into the preprocArgs struct.
   *        If there is some problem with the argument, puts it into the can_warning list of gccWarnings struct.
   *
   * @param args_it        [in] Iterator pointed to the actual element of the argument list.
   * @param args_end       [in] Iterator pointed to the end of the argument list.
   * @param gccWarnings    [out] The problematic argument is put into this struct.
   * @param preprocArgs    [out] The argument of CAN (which is according to actual known argument) is put into this struct.
   * @param actArg         [out] The actual argument is represented by this struct.
   * @return                     EC_FOUND if recognizes the argument
   * @return                     EC_NOT_FOUND if not recognizes the argument
   * @return                     EC_ERROR if the given argument is not correct.
   */
  ParErrorCode examinePreprocArg (std::list<std::string>::iterator& args_it, const std::list<std::string>::const_iterator& args_end, Warnings& gccWarnings, PreprocArgs& preprocArgs, Argument& actArg);

  /**
   * @brief Examines the given linker argument. If it has parameter and this parameter is the next element of the argument list,
   *        the iterator is moved to the next element (if that is not the end iterator of the argument list).
   *        If it is known argument, puts the argument of CANLinker (which is according to actual known argument) into the linkerArgs struct.
   *
   * @param args_it        [in] Iterator pointed to the actual element of the argument list.
   * @param args_end       [in] Iterator pointed to the end of the argument list.
   * @param linkerArgs     [out] The argument of CANLinker (which is according to actual known argument) is put into this struct.
   * @param actArg         [out] The actual argument is represented by this struct.
   * @param fullCheck      [in] True if we need to check the output file arguments too.
   * @return                     EC_FOUND if recognizes the argument
   * @return                     EC_NOT_FOUND if not recognizes the argument
   * @return                     EC_ERROR if the given argument is not correct.
   */
  ParErrorCode examineLinkerArg (std::list<std::string>::iterator& args_it, const std::list<std::string>::const_iterator& args_end, LinkerArgs& linkerArgs, Argument& actArg, const bool fullCheck = false);

  /**
   * @brief Processes the given linker argument list. It calls examineLinkerArg method. The arguments of CANLinker (which are according to known linker arguments) are put into linkerArgs struct.
   *        If there are some problematic arguments, they are put into the can_warnings list of gccWarnings struct.
   *        If there are some unknown arguments, they are put into the unrec_args list of gccWarnings struct.
   *
   * @param args           [in] The given linker argument list.
   * @param gccWarnings    [out] The problematic or unknown arguments are put into this struct.
   * @param linkerArgs     [out] The arguments of CANLinker (which are according to known linker arguments) are put into this struct.
   * @return                     True if it can processes the given argument list.
   */
  bool linkerArguments (std::list<std::string> args, Warnings& gccWarnings, LinkerArgs& linkerArgs);

  /**
   * @brief Processes the given compiler argument list. It calls examinePreprocArg and examineLinkerArg methods.
   *        The arguments of CAN (which are according to known preprocessor arguments) are put into preprocArgs struct.
   *        The arguments of CAN (which are according to known compiler arguments) are put into compilerArgs struct.
   *        The arguments of CANLinker (which are according to known linker arguments) are put into linkerArgs struct.
   *        If there are some problematic arguments, they are put into the can_warnings list of gccWarnings struct.
   *        If there are some unknown arguments, they are put into the unrec_args list of gccWarnings struct.
   *
   * @param args           [in] The given compiler argument list.
   * @param gccWarnings    [out] The problematic or unknown arguments are put into this struct.
   * @param preprocArgs    [out] The arguments of CAN (which are according to known preprocessor arguments) are put into this struct.
   * @param compilerArgs   [out] The arguments of CAN (which are according to known compiler arguments) are put into this struct.
   * @param linkerArgs     [out] The arguments of CANLinker (which are according to known linker arguments) are put into linkerArgs struct.
   * @return                     True if it can processes the given argument list.
   */
  bool compilerArguments (std::list<std::string> args, Warnings& gccWarnings, PreprocArgs& preprocArgs, CompilerArgs& compilerArgs, LinkerArgs& linkerArgs);
}}

#endif