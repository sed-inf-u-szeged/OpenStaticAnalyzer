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

#ifndef _SMJ_CONTR_PROP_H_
#define _SMJ_CONTR_PROP_H_

#include <string>
#include <boost/filesystem/path.hpp>
#include <controller/inc/Properties.h>

typedef struct WrappedTool {
  bool fullpath;
  boost::filesystem::path wrappedToolName;
  boost::filesystem::path wrapperToolName;
} WrappedTool;

struct Properties : public columbus::controller::BaseProperties
{
  Properties() : 
     cloneGenealogy(false),
     cloneMinLines(-1),
     csvSeparator(','),
     csvDecimalmark('.'),
     cleanResults(-1),
     cleanProject(false),
     runPMD(true),
     runFindBugs(false),
     runDCF(true),
     runLimMetrics(true),
     runMetricHunter(true),
     analysisOutputDir(".columbus_java")
  {}

  bool cloneGenealogy;                                // Create clone genealogy or no.
  
  std::string projectName;                            // The name of the project which is given by the user

  boost::filesystem::path startCurrentDir;            // Absolute path of the current directory when the CAC was started
  boost::filesystem::path toolchainDir;               // Absolute path of the directory of the CA toolchain
  boost::filesystem::path wrapperDir;                 // Absolute path of the directory of the wrapper inside the CA package
  boost::filesystem::path wrapperBinDir;              // Absolute path of the directory of the wrapper binaries inside the CA package
  boost::filesystem::path wrapperToolsDir;            // Absolute path of the directory of the wrapper tools inside the CA package
  boost::filesystem::path toolsDir;                   // Absolute path of the directory of the tools inside the CA package
  
  boost::filesystem::path resultsDir;                 // Absolute path of the result directory given by the user
  boost::filesystem::path buildScript;                // Absolute path of the build script given by the user
  boost::filesystem::path currentDate;                // The current date
  boost::filesystem::path projectResultDir;           // resultsDir / projectName /
  boost::filesystem::path projectTimedResultDir;      // projectResultDir / currentDate
  boost::filesystem::path projectBaseDir;             // Absolute path of the base directory given by the user
  boost::filesystem::path tempDir;                    // Absolute path of the directory of the temporary files
  boost::filesystem::path asgDir;                     // Absolute path of the directory of the asg files
  boost::filesystem::path graphDir;                   // Absolute path of the directory of the graph files
  boost::filesystem::path columbusWrapperTmpDir;      // Absolute path of the directory where the wrapper is assembled
  boost::filesystem::path columbusWrapperTmpDirName;  // Name of the directory where the wrapper is assembled (osaDir / temp / wrapper)
  boost::filesystem::path externalHardFilter;         // Absolute path of the external hardfilter file
  boost::filesystem::path externalSoftFilter;         // Absolute path of the external softfilter file
  boost::filesystem::path metricThreshold;            // Absolute path of the metric threshold file

  boost::filesystem::path profileXML;
  boost::filesystem::path rulesCSV;

  boost::filesystem::path superLinkList;
  boost::filesystem::path pmdXmlList;

  std::string javacOptions;                           // In directory analysis mode, the necessary parameters for compilation can be set with this option.
  std::string JVMOptions;                             // TODO:
  std::string JANJvmOptions;                          // 
  std::string PMDOptions;                             // 
  std::string FBOptions;                              // 
  std::string mavenFilter;                            //
  std::string FBFileList;                             //
  int cloneMinLines;                                  //

  char csvSeparator;                                  // Column separator character of the csv outputs.
  char csvDecimalmark;                                // Decimal mark character in the csv outputs.
  int cleanResults;                                   // Keep the last 'cleanResults' number of timestamped directory of the project in the results.
  bool cleanProject;                                  // Removes all files created outside the results directory during previous analyses, but does not remove anything from the results directory.
  bool runPMD;                                        // Run PMD.
  bool runFindBugs;                                   // Run FindBugs.
  bool runDCF;                                        // Run DCF.
  bool runLimMetrics;                                 // Run Lim2Metrics.
  bool runMetricHunter;                               // Run MetricHunter.
  bool runChangeTracker;                              // Run ChangeTracker.
  std::string analysisOutputDir;                      // The name of the output directory (.columbus_java)
};

extern Properties props;

#endif
