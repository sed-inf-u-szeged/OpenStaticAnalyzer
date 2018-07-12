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

#ifndef _SMJ_CONTR_M_H_
#define _SMJ_CONTR_M_H_

#define CMSG_ERROR_CREATE_DIR                             "ERROR: Can't create %s dir.\n"
#define CMSG_ERROR_EXECUTION_FAILURE                      "ERROR: Execution failure! Exit:%d\n"
#define CMSG_ERROR_DELETE_DIR                             "ERROR: Can't delete %s dir. %s.\n"

#define CMSG_JAVA_CURR_VERSION                            WriteMsg::mlNormal, "Java version: %s\n"
#define CMSG_ERROR_JAVA_VERSION                           WriteMsg::mlError, "ERROR: Required java version is 1.8 or later!\n"

#define CMSG_ANT_CURR_VERSION                             WriteMsg::mlNormal, "Ant version: %s\n"
#define CMSG_WARNING_ANT_VERSION                          WriteMsg::mlWarning, "WARNING: Required Ant version is 1.8.4 or later!\n"
#define CMSG_WRAPPER_ERROR                                "ERROR: During the analysis at least one of the wrappers has reported error! For further details please check the openstaticanalyzer/temp/wrapper/log/wrapper.log file in the results directory."

#define CMSG_MAVEN_CURR_VERSION                           WriteMsg::mlNormal, "Maven version: %s\n"
#define CMSG_WARNING_MAVEN_VERSION                        WriteMsg::mlWarning, "WARNING: Required Maven version is 2.2.1, 3.0.5, 3.1.1, 3.2.2 or 3.2.5!\n"

#define CMSG_WARNING_FILE_MISSING                         WriteMsg::mlWarning, "WARNING: The '%s' file is missing!\n"
#define CMSG_PMD_ERROR                                    "PMD has failed! The PMD can be disabled with the -runPMD=false command line option."
#define CMSG_FINDBUGS_ERROR                               "FindBugs has failed! The FindBugs can be disabled with the -runFB=false command line option."

#endif
