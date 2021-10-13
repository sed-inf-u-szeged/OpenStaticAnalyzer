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

/********************************************************************
*                   DEFINES AND INCLUDES                            *
********************************************************************/

#define PROGRAM_NAME "JAN2Lim"
#define EXECUTABLE_NAME PROGRAM_NAME

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <list>
#include <vector>

#include <MainCommon.h>
#include <ErrorCodes.h>
#include <ReleaseVersion.h>
#include <common/inc/FileSup.h>
#include <common/inc/Stat.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/Arguments.h>
#include <csi/inc/csi.h>
#include <lim/inc/lim.h>
#include <io/inc/CsvIO.h>

#include "../inc/JAN2LimVisitor.h"
#include "../inc/CheckVisitor.h"
#include "../inc/CommentVisitor.h"
#include "../inc/messages.h"

using namespace std;
using namespace columbus;
using namespace columbus::JAN2Lim;
using namespace common;


/********************************************************************
*                     ARGUMENT PROCESSING                           *
********************************************************************/

namespace columbus { namespace JAN2Lim { namespace options
{
  using namespace std;

  // main option parser from command line arguments
  void parse( int argc, char** argv);

  // parameters
  static std::string listFile;      // file containing the files to be converted
  static std::list<std::string> inputFiles;     // the processed file list - together with ppFile
  static std::string compStructFile;

  static std::string out;

  static std::vector<std::string> fltpVector;   // the processed filter entries
  static bool noFilter = false;

  static std::string maxmem;
  static unsigned maxMem = 0;

  void checkInputFiles();
  void checkMaxMem();

  void parse( int argc, char** argv)
  {
    // read parameters
    MainInit( argc, argv, "-");

    // validate parameters
    checkInputFiles();
    checkMaxMem();
  }

  void checkInputFiles()
  {
    if ( !listFile.empty() )
    {
      ifstream ifs( listFile.c_str() );
      if ( ifs.is_open() )
      {
        string tmp;
        while ( getline(ifs, tmp) )
        {
          if ( !tmp.length() )
          {
            continue;
          }
          if ( tmp[tmp.length()-1] == 0xD ) // handle DOS line-ends in unix
          {
            inputFiles.push_back( tmp.substr(0,tmp.length()-1) );
          }
          else
          {
            inputFiles.push_back( tmp );
          }
        }
        ifs.close();
      }
    }

    if (inputFiles.size() == 0)
    {
      WriteMsg::write(CMSG_MISSING_INPUT_FILES);
      clError();
    }

    if ( inputFiles.size() == 1 )
    {
      if ( out.empty() )
      {
        string outname = *inputFiles.begin(); 
        out = outname.substr(0, outname.find_last_of('.')) + ".lim";
      }
    }
    else
    {
      if (out.empty())
      {
        out = "noname.lim";
      }
    }
  }

  void checkMaxMem()
  {
    maxMem = 0;
    if ( !maxmem.empty() )
    {
      int mm = 0;
      if ( str2int(maxmem, mm) )
      {
        if ( 0 < mm )
        {
          maxMem = (unsigned) (mm * 1024 * 1024);
        }
        else
        {
          WriteMsg::write(CMSG_NEGATIVE_MEMORY_VALUE);
          clError();
        }
      }
      else
      {
        WriteMsg::write(CMSG_INVALID_MEMORY_VALUE);
        clError();
      }
    }
  }

}}} // end options, end JAN2Lim, end columbus

// callbacks for argument processing
static bool ppList          ( const Option *o, char *argv[] ) { options::listFile = argv[0];      return true; }
static bool ppOut           ( const Option *o, char *argv[] ) { options::out = argv[0];           return true; }
static bool ppNoFilt        ( const Option *o, char *argv[] ) { options::noFilter = true;         return true; }
static bool ppMaxMem        ( const Option *o, char *argv[] ) { options::maxmem = argv[0];        return true; }
static bool ppCompStruct    ( const Option *o, char *argv[] ) { options::compStructFile= argv[0]; return true; }
static void ppFile          ( char *filename ) { columbus::JAN2Lim::options::inputFiles.push_back( filename ); }

// the list of valid options
const Option OPTIONS_OBJ [] =
{
  { false,  "-out",               1,  "filename",           0, OT_WC | OT_WS,          ppOut,            NULL,       "Name of the output LIM file"},
  { false,  "-nofilter",          0,  "",                   0, OT_NONE,                ppNoFilt,         NULL,       "Filter files are not used"},
  { false,  "-maxmem",            1,  "number",             0, OT_WC,                  ppMaxMem,         NULL,       "Maximum usable memory (not converted files are written out)"},
  CL_INPUT_LIST
  { false,  "-struct",            1, "ComponenetStructureFile",0, OT_WC,               ppCompStruct,     NULL,       "The file with the componenet structure. If it is missing the componet tree is assumed to be flat."},
  COMMON_CL_ARGS
};


/********************************************************************
*                      UTILITY FUNCTIONS                            *
********************************************************************/

void loadFilter( java::asg::Factory& fact, const string& file )
{
  string flt = pathRemoveExtension(file) + ".fjsi";
  if ( fileTimeCmp(flt, file) == -1 )
  {
    WriteMsg::write(CMSG_FILTER_FILE_DEPRECATED, flt.c_str());
    return;
  }

  try
  {
    fact.loadFilter( flt );
  }
  catch (const IOException&)
  {
    WriteMsg::write(CMSG_CANNOT_OPEN_FILTER_FILE, flt.c_str());
  }
}

static inline void setStartTime(unsigned long *time)
{
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system;
}

static inline void setElapsedTime(unsigned long *time)
{
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system - *time;
}

static inline void updateMemStat(size_t *max_mem)
{
  memstat ms = getProcessUsedMemSize();
  if (*max_mem < ms.size) {
    *max_mem = ms.size;
  }
}

void writeClassStats( JAN2LimVisitor::VisitStat& classStats, lim::asg::Factory& limFactory, bool forced = false )
{
    WriteMsg::MsgLevel level = forced ? WriteMsg::mlNormal : WriteMsg::mlDDebug;

    WriteMsg::write( level , CMSG_STAT_NOSC, classStats.source);
    WriteMsg::write( level , CMSG_STAT_NOEC, classStats.external);
    WriteMsg::write( level , CMSG_STAT_NOIC, classStats.irrelevant);
    WriteMsg::write( level , CMSG_STAT_NOCC, classStats.converted);
    WriteMsg::write( level , CMSG_STAT_NOSKC, classStats.skip);
    WriteMsg::write( level , CMSG_STAT_NOC, classStats.total);

    CheckVisitor checkVisitor( limFactory );
    int classCheckCnt = checkVisitor.classCount();
    WriteMsg::write(level, CMSG_STAT_NODC, classCheckCnt);
}


/********************************************************************
*                           MAIN                                    *
********************************************************************/

int getDepthOfIndent (const std::string& line) {
  int retvalue = 0;
  for (;retvalue < (int)line.length(); retvalue++){
    if (line.at(retvalue) != '\t') 
      break;
  }
  return retvalue;
}

bool organizeCompStruct(lim::asg::Factory& limFactory) {
  limFactory.turnFilterOff();
  //build the index of component
  //open the file
  std::stack<NodeId> componentStack;
  std::ifstream inputStuctFile(options::compStructFile.c_str());
  if (!inputStuctFile.good()) {
    return false;
  }

  std::string line;
  componentStack.push(limFactory.getComponentRootRef().getId());
  
  while (inputStuctFile.good()) {
    std::getline(inputStuctFile,line);
    if (!line.empty()) {
      int currentDepth = getDepthOfIndent(line);
      if (currentDepth == 0)
        continue;

      int diffDept = currentDepth - (componentStack.size());
      if (diffDept > 0 )  {
        return false;
      }

      line.erase(0,currentDepth);
      std::vector<std::string> args;
      common::split(line,args,'\t');
      std::string componentName    = args[0];
      std::string aritfactIncState = args[1];
      std::string aritfactDepScope = args[2];
      std::string aritfactAnaTime  = args[3];

      for (;diffDept<0;diffDept++) {
        if (componentStack.empty()) {
          return false;
        }
        componentStack.pop();
      }

      lim::asg::base::Component& childComponent = limFactory.createComponent(componentName);
      lim::asg::base::Component& parentComponent = (lim::asg::base::Component&)limFactory.getRef(componentStack.top());

      componentStack.push(childComponent.getId());

      if (!aritfactIncState.compare("INCLUDE")) {
        parentComponent.addContains(&childComponent);
        childComponent.setAnalysisTime(columbus::lim::asg::atkNever);
      } 

      if (!aritfactAnaTime.compare("CURRENT")) {
        childComponent.setAnalysisTime(columbus::lim::asg::atkNow);
      }
      

      if (parentComponent.getId() != limFactory.getComponentRoot()) {
        parentComponent.addDependsOn(&childComponent,aritfactDepScope);
      }
    }
  }
   
  inputStuctFile.close();
  limFactory.turnFilterOn();
  return true;
}

int main( int argc, char* argv[] )
{
  int exitCode = 0;
  MAIN_BEGIN

  unsigned long totalTime;
  unsigned long conversionTime;
  unsigned long saveTime;
  unsigned long dumpTime;

  size_t maxMem = 0;

  int missingFiles = 0;

  setStartTime( &totalTime );

  // preparing comman line options
  options::parse( argc, argv);

  // lim graph
  RefDistributorStrTable limStrTable;
  lim::asg::Factory limFactory( limStrTable, java::asg::JAVA_ROOT_NAME, lim::asg::limLangJava );

  // origin
  LimOrigin origin;

  //overrides
  lim::asg::OverrideRelations overrides(limFactory);
  // utils
  JAN2LimVisitor::JAN2LimMap map;
  JAN2LimVisitor::CGIMap cgiMap;
  std::map<NodeId, JAN2LimVisitor::CompletionStates> nodeStates;
  JAN2LimVisitor::VisitStat classStats;

  setStartTime( &conversionTime );


  if (!options::compStructFile.empty()) {
    if (!organizeCompStruct(limFactory)) {
      options::compStructFile.clear();
      WriteMsg::write(CMSG_COMPSTRUCT_NOT_BUILD);
    }
  }

  for ( list<string>::const_iterator it = options::inputFiles.begin(); it != options::inputFiles.end(); ++it )
  {
    // creating factory
    RefDistributorStrTable javaStrTable;
    java::asg::Factory factory( javaStrTable );

    // load schema instance
    WriteMsg::write(CMSG_LOADING_FILE, it->c_str());

    CsiHeader header;
    try
    {
      factory.load( it->c_str(), header );
    }
    catch (const IOException&)
    {
      WriteMsg::write(CMSG_WARN_CANNOT_READ_FILE, it->c_str());
      exitCode = 1;
      missingFiles++;
      continue;
    }

    // component name
    string compPath;
    header.get(CsiHeader::csih_OriginalLocation, compPath);
    if ( compPath.empty() ) compPath = *it;

    // filter init
    if ( ! options::noFilter )
    {
      factory.turnFilterOn();
      factory.initializeFilter();
      loadFilter( factory, *it );

      factory.turnFilterOff();
    }

    // JAN2Lim visitor is created and called
    WriteMsg::write(CMSG_CONVERTING_FILE, it->c_str());
    string  changesetID = "";

    header.get(CsiHeader::csih_ChangesetID, changesetID);

    HalsteadVisitor halsteadVisitor( factory );
    java::asg::AlgorithmPreorder().run( factory, halsteadVisitor );
    std::map<NodeId, HalsteadVisitor::HalsteadInfo> halMap = halsteadVisitor.getHalsteadValues();
    JAN2LimVisitor jan2LimVisitor(limFactory, factory, map, cgiMap, nodeStates, compPath, classStats, origin, overrides, options::compStructFile.empty(), false, changesetID, halMap);
    java::asg::AlgorithmPreorder().run( factory, jan2LimVisitor );
    
    writeClassStats( classStats, limFactory );

    updateMemStat( &maxMem );

    if ( options::maxMem != 0 && maxMem > options::maxMem )
    {
      WriteMsg::write( CMSG_MAXMEM_EXCEEDED );
      break;
    }
  }

  // finalizing and cleanup
  JAN2LimVisitor::setLineMetrics( limFactory );
  JAN2LimVisitor::filterInitBlocks( limFactory );

  updateMemStat( &maxMem );

  setElapsedTime( &conversionTime );
  setStartTime( &saveTime );

  // saving the lim graph
  WriteMsg::write(CMSG_SAVING_FILE, options::out.c_str());

  std::list<HeaderData*> limHeader;
  limHeader.push_back( &origin );
  limHeader.push_back( &overrides );

  try
  {
    limFactory.save( options::out, limHeader );
  }
  catch (const IOException&)
  {
    WriteMsg::write(CMSG_WARN_CANNOT_WRITE_FILE, options::out.c_str());
  }

  // saving the filter
  string filterfile = options::out.substr(0, options::out.find_last_of('.')) + ".flim";
  try
  {
    limFactory.saveFilter(filterfile);
  }
  catch (const IOException&)
  {
    WriteMsg::write(CMSG_WARN_CANNOT_WRITE_FILE, filterfile.c_str());
  }

  setElapsedTime( &saveTime );
  setStartTime( &dumpTime );

  setElapsedTime( &totalTime );

  WriteMsg::write(
      CMSG_STATISTICS,
      ((float)conversionTime)/100,
      ((float)saveTime)/100,
      ((float)totalTime)/100,
      ((float)maxMem)/1048576,
      missingFiles
  );

  MAIN_END

  return exitCode;
}
