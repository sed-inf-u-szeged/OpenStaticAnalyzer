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

#include "AsWrapper/AsWrapper.h"
#include <AbstractWrapperLib/inc/messages.h>
#include <AbstractWrapperLib/inc/abstractwrapper/AbstractWrapper.h>
#include <AbstractWrapperLib/inc/paramsup/ArParamsup.h>
#include <common/inc/WriteMessage.h>

#include <boost/filesystem.hpp>
#include <string>
#include <list>

using namespace std;
using namespace common;

#define AS_WRAPPER  "AsWrapper"


ColumbusWrappers::AsWrapper::AsWrapper( std::string configfile )
  :AbstractWrapper(configfile)
{

}

bool ColumbusWrappers::AsWrapper::process( int argc, char** argv )
{
  char* env = getenv("WRAPPER_ENVIRONMENT");
  if (env == NULL){
    writeWarningMsg(AS_WRAPPER,CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
    return false;
  }
  
  if (!parsingParameters(argc, argv))
    return false;


  inputFile = createCsiName(inputFile);
  outputFile = createCsiName(outputFile);
  

  writeWarningMsg(AS_WRAPPER,"copy %s to %s",inputFile.c_str(),outputFile.c_str());
  boost::filesystem::create_directories(boost::filesystem::path(outputFile).remove_leaf());
  boost::filesystem::copy_file(boost::filesystem::path(inputFile),boost::filesystem::path(outputFile));
  return true;
}

bool ColumbusWrappers::AsWrapper::parsingParameters( int argc, char** argv )
{

  for (int i=0; i<argc; ++i){
     string tmp(argv[i]);
  
     if (!tmp.compare(0,1,"-")) {
       if (!tmp.compare("-o")) {
         outputFile = argv[i+1];
         ++i;
       }
       if ((!tmp.compare("-a"))|| (!tmp.compare("-n"))|| (!tmp.compare("-m"))) {
         ++i;
       }
     } else {
       inputFile = argv[i];
     }
  }

  return true;
}

std::string ColumbusWrappers::AsWrapper::createCsiName(const std::string& outputFile) const 
{
  boost::filesystem::path outputPath(outputFile);
  outputPath.remove_filename();
  outputPath/=outputdir;
  outputPath/=boost::filesystem::path(outputFile).leaf();
  
  return outputPath.string()+".csi";
}
