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

#ifndef _OSAJS_CONTR_M_H_
#define _OSAJS_CONTR_M_H_

#define CMSG_ERROR_CREATE_DIR                             "ERROR: Can't create %s dir.\n"
#define CMSG_ERROR_EXECUTION_FAILURE                      "ERROR: Execution failure! Exit:%d\n"
#define CMSG_ERROR_ENVSET_FAILURE                         "ERROR: Failed to set '%s' environment variable!\n"
#define CMSG_WARNING_ENVSET_OVERWRITE                     "WARNING: Overwriting '%s' environment variable!\n"
#define CMSG_ERROR_DELETE_DIR                             "ERROR: Can't delete %s dir. %s.\n"

#define CMSG_ERROR_NODE_VERSION                           WriteMsg::mlError, "ERROR: Required Node version is %d.x.x or later!\n"

#define CMSG_WARNING_FILE_MISSING                         WriteMsg::mlWarning, "WARNING: The '%s' file is missing!\n"

#endif
