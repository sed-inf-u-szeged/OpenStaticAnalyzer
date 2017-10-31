/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#ifndef _GRAPHDUMP_M_H_
#define _GRAPHDUMP_M_H_

#define CMSG_NO_INPUT_FILE        WriteMsg::mlNormal, "Error: No input file\n"
#define CMSG_TOO_MANY_INPUT_FILES WriteMsg::mlNormal, "Error: Too many input files\n"
#define CMSG_LOAD_FILE            WriteMsg::mlNormal, "Loading: %s\n"
#define CMSG_CSV_DUMP             WriteMsg::mlNormal, "Creating csv dump ...\n"
#define CMSG_XML_DUMP             WriteMsg::mlNormal, "Creating xml dump ...\n"

#endif