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

#ifndef _OSAPY_PROP_H_
#define _OSAPY_PROP_H_

#include <string>
#include <list>
#include <boost/filesystem/path.hpp>
#include <controller/inc/Properties.h>

struct Properties : public columbus::controller::BaseProperties
{
  Properties()
    : cloneGenealogy(false)
    , csvSeparator(',')
    , csvDecimalmark('.')
    , cleanResults(-1)
    , cloneMinLines(-1)
    , runDCF(true)
    , runPylint(true)
    , runMetricHunter(true)
    , runLimMetrics(true)
  {}

  bool cloneGenealogy;                                // Create clone genealogy or no.

  std::string projectName;                            // The name of the project which is given by the user

  boost::filesystem::path startCurrentDir;            // Absolute path of the current directory when the CAC was started
  boost::filesystem::path toolchainDir;               // Absolute path of the directory of the CA toolchain
  boost::filesystem::path toolsDir;                   // Absolute path of the directory of the tools inside the CA package
  
  boost::filesystem::path profileXML;
  boost::filesystem::path rulesCSV;
  
  boost::filesystem::path resultsDir;                 // Absolute path of the result directory given by the user
  boost::filesystem::path currentDate;                // The current date
  boost::filesystem::path projectResultDir;           // resultsDir / projectName /
  boost::filesystem::path projectTimedResultDir;      // projectResultDir / currentDate
  boost::filesystem::path projectBaseDir;             // Absolute path of the base directory given by the user
  boost::filesystem::path tempDir;                    // Absolute path of the directory of the temporary files
  boost::filesystem::path asgDir;                     // Absolute path of the directory of the asg files
  boost::filesystem::path graphDir;                   // Absolute path of the directory of the graph files
  boost::filesystem::path externalHardFilter;         // Absolute path of the external hardfilter file
  boost::filesystem::path pythonBinary;               // Path of the Python 2.7/3.x binary
  std::string pythonVersion;                          // Python version (2 or 3)
  std::list<std::string> pylintOptions;               // Options passed to Pylint
  char csvSeparator;                                  // Column separator character of the csv outputs.
  char csvDecimalmark;                                // Decimal mark character in the csv outputs.
  int cleanResults;                                   // Keep the last 'cleanResults' number of timestamped directory of the project in the results.
  int cloneMinLines;                                  // Minimum number of lines of clone instances.

  bool runDCF;                                        // Run DCF.
  bool runPylint;                                     // Run Pylint2Graph
  bool runMetricHunter;                               // Run MetricHunter.
  bool runLimMetrics;                                 // Run Lim2Metrics.
};

extern Properties props;

#endif
