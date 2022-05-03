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

#ifndef _OSACPP_CONTR_M_H_
#define _OSACPP_CONTR_M_H_

#define CMSG_ERROR_CREATE_DIR                                  "ERROR: Can't create %s dir.\n"
#define CMSG_CANNOT_OPEN_LCSI_FOR_WRITING                      "WARNING: Can't open lcsi list file for writing!"
#define CMSG_TOO_SHORT_ACSI_NAME                               "WARNING: The name of the acsi file is to short!"
#define CMSG_ERROR_DELETE_DIR                                  "ERROR: Can't delete %s dir. %s.\n"
#define CMSG_WRAPPER_ERROR                                     "ERROR: During the analysis at least one of the wrappers has reported error! For further details please check the openstaticanalyzer/temp/wrapper/log/wraplog.log file in the results directory."
#define CMSG_CAN_NOT_CREATE_RM_WRAPPER_ERROR                   "ERROR: Can't create 'rm' wrapper file!"
#define CMSG_NO_OUTPUT_ERROR                                   "ERROR: During the analysis neither linked component nor static library has been created! Please check the environment and the build script to be sure that the compiler tools can be wrapped and at least one linking phase (or static library creation) is executed during the build process!"


#define CMSG_UNSUPPORTED_LINKING_MODE                           WriteMsg::mlError, "ERROR: The Linking mode 2 is not supported yet!\n"
#define CMSG_BAD_LINKING_MODE                                   WriteMsg::mlError, "ERROR: Only linking mode 1,2 and 3 are valid!\n"
#define CMSG_WARNING_FILE_MISSING                               WriteMsg::mlWarning, "WARNING: The '%s' file is missing!\n"

#define CMSG_ENV_VAR_SET_ERROR                                  WriteMsg::mlError, "ERROR: Failed to set '%s' environment variable!\n"

#define CMSG_SUCCESSFUL_TERMINATION                             WriteMsg::mlNormal, "Done!"
#define CMSG_FAILURE_TERMINATION                                WriteMsg::mlNormal, "Failed!"

#define CMSG_FAILED_TO_OPEN_FILE                                WriteMsg::mlError,    "File %s can't be opened!\n"

#endif
