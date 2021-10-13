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

#ifndef _SONAR2GRAPH_MESSAGES_H_
#define _SONAR2GRAPH_MESSAGES_H_

#define CMSG_SONAR2GRAPH_NO_NODE_FOUND_AT_PATH                 WriteMsg::mlWarning,  "Warning: Warning '%s' cannot be added as no node found at [path:%s line:%d col:%d endline:%d endcol:%d]\n"
#define CMSG_SONAR2GRAPH_WARNING_ALREADY_ADDED                 WriteMsg::mlWarning,  "Warning: Warning '%s' has already been added. (node:%s path:%s line:%d col:%d endline:%d endcol:%d text:'%s')\n"
#define CMSG_SONAR2GRAPH_WARNING_GREATER_THEN                  WriteMsg::mlWarning,  "Warning: Cannot get all the %d issues from SonarQube, because the limit by the api is %d\n"
#define CMSG_SONAR2GRAPH_WARNING_DO_NOT_HAVE_LINE_INFO         WriteMsg::mlWarning,  "Warning: Warning '%s' do not have line info, skipped. (path: %s text:'%s')\n"
#define CMSG_SONAR2GRAPH_FILTER_OLDER                          WriteMsg::mlWarning,  "Warning: Filter file (%s) is older than the input file (.lim). Filter file is not used.\n"
#define CMSG_SONAR2GRAPH_FILTER_CANNOT_BE_LOADED               WriteMsg::mlWarning,  "Warning: Filter file cannot be loaded (%s)\n"
#define CMSG_SONAR2GRAPH_WARNING_SUCCESSFULLY_ADDED            WriteMsg::mlNormal,   "Info: Warning '%s' is successfully added. (node:%s path:%s line:%d col:%d endline:%d endcol:%d text:'%s')\n"
#define CMSG_SONAR2GRAPH_API_CALL_STRING                       WriteMsg::mlNormal,   "Info: API call string: %s\n"
#define CMSG_SONAR2GRAPH_ISSUES_PROCESSED                      WriteMsg::mlNormal,   "Info: %d issues were processed\n"
#define CMSG_SONAR2GRAPH_API_CALL_EXCEPTION                    WriteMsg::mlError,    "Error: An exception were occured while doing API call: %s\n Exception message: %s\n"
#define CMSG_SONAR2GRAPH_WARNING_GREATER_THEN_IN_FILE          WriteMsg::mlError,    "Error: Cannot get all the %d issues from this file: %s, because the limit by the api is %d. If -strict=true, then the tool will stop working.\n"
#define CMSG_SONAR2GRAPH_WARNING_NO_PORT_AND_IP                WriteMsg::mlError,    "Error: Please set the IP(-host:) address and the port(-port:) number of the SonarQube server.\n"
#endif
