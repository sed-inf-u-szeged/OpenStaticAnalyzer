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

#ifndef _CONTROLLER_PROPERTIES_H
#define _CONTROLLER_PROPERTIES_H

namespace columbus
{

namespace controller
{

struct BaseProperties {
  BaseProperties()
    : maxThreads (0)
    , verbose (false)
  {}
  boost::filesystem::path logDir;       // Absolute path of the directory of the log files
  int maxThreads;                       // The maximum number of concurent threads the controller can start
  bool verbose;                         // Verbose mode
};

} // namespace controller

} // namespace columbus

#endif
