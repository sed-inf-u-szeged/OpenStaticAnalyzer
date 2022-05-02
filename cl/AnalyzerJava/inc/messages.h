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

#ifndef _OSAJ_CONTR_M_H_
#define _OSAJ_CONTR_M_H_

#define CMSG_ERROR_CREATE_DIR                             "ERROR: Can't create %s dir.\n"
#define CMSG_ERROR_EXECUTION_FAILURE                      "ERROR: Execution failure! Exit:%d\n"
#define CMSG_ERROR_ENVSET_FAILURE                         "ERROR: Failed to set '%s' environment variable!\n"
#define CMSG_WARNING_ENVSET_OVERWRITE                     "WARNING: Overwriting '%s' environment variable!\n"
#define CMSG_ERROR_DELETE_DIR                             "ERROR: Can't delete %s dir. %s.\n"

#define CMSG_JAVA_CURR_VERSION                            WriteMsg::mlNormal, "Java version: %s\n"
#define CMSG_ERROR_JAVA_VERSION                           WriteMsg::mlError, "ERROR: Required java version is Java 11!\n"

#define CMSG_WARNING_FILE_MISSING                         WriteMsg::mlWarning, "WARNING: The '%s' file is missing!\n"
#define CMSG_PMD_ERROR                                    "PMD has failed! The PMD can be disabled with the -runPMD=false command line option."
#define CMSG_FINDBUGS_ERROR                               "SpotBugs has failed! The SpotBugs can be disabled with the -runFB=false command line option."

#endif
