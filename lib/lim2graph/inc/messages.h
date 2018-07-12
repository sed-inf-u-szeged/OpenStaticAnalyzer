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

#ifndef _LIM2GRAPH_MSG_H_
#define _LIM2GRAPH_MSG_H_

#define CMSG_VISITORGRAPHCONVERTER      common::WriteMsg::mlDDDDebug, "DDDDebug: VisitorGraphConverter\n"
#define CMSG_COMPONENT                  common::WriteMsg::mlDDDDebug, "DDDDebug: Component %u %s \n"
#define CMSG_PACKAGE                    common::WriteMsg::mlDDDDebug, "DDDDebug: Package %u %s %s \n"
#define CMSG_CLASS                      common::WriteMsg::mlDDDDebug, "DDDDebug: Class %u %s %s\n"
#define CMSG_METHODE                    common::WriteMsg::mlDDDDebug, "DDDDebug: Method %u %s %s\n"
#define CMSG_ATTRIBUTE                  common::WriteMsg::mlDDDDebug, "DDDDebug: Attribute %u %s %s\n"

#endif