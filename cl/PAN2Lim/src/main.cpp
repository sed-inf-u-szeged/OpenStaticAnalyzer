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

#define PROGRAM_NAME "PAN2Lim"
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

#include <lim/inc/lim.h>
#include <io/inc/CsvIO.h>

#include "../inc/python2lim.h"
#include "../inc/messages.h"

using namespace std;
using namespace columbus;
using namespace common;


/********************************************************************
*                     ARGUMENT PROCESSING                           *
********************************************************************/

namespace columbus { namespace PAN2Lim { namespace options
{
  using namespace std;

  // main option parser from command line arguments
  void parse( int argc, char** argv);

  // parameters
  static std::string listFile;      // file containing the files to be converted
  static std::list<std::string> inputFiles;     // the processed file list - together with ppFile

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
          maxMem = static_cast<unsigned>(mm * 1024 * 1024);
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

}}} // end options, end PAN2Lim, end columbus


using namespace columbus::PAN2Lim;

// callbacks for argument processing
static bool ppList          ( const Option *o, char *argv[] ) { options::listFile = argv[0];      return true; }
static bool ppOut           ( const Option *o, char *argv[] ) { options::out = argv[0];           return true; }
static bool ppNoFilt        ( const Option *o, char *argv[] ) { options::noFilter = true;         return true; }
static bool ppMaxMem        ( const Option *o, char *argv[] ) { options::maxmem = argv[0];        return true; }
static void ppFile          ( char *filename ) { columbus::PAN2Lim::options::inputFiles.push_back( filename ); }


// the list of valid options
const Option OPTIONS_OBJ [] =
{
  { false,  "-out",               1,  "filename",           0, OT_WC | OT_WS,          ppOut,            NULL,       CLARG_LIM},
  { false,  "-nofilter",          0,  "",                   0, OT_NONE,                ppNoFilt,         NULL,       CLARG_NOFILTER},
  { false,  "-maxmem",            1,  "number",             0, OT_WC,                  ppMaxMem,         NULL,       CLARG_MAXMEM},
  CL_INPUT_LIST
  COMMON_CL_ARGS
};


/********************************************************************
*                      UTILITY FUNCTIONS                            *
********************************************************************/

void loadFilter( python::asg::Factory& fact, const string& file )
{
  string flt = pathRemoveExtension(file) + ".fpsi";
  if ( fileTimeCmp(flt, file) == -1 )
  {
    WriteMsg::write(CMSG_FILTER_FILE_DEPRECATED, flt.c_str());
    return;
  }

  try
  {
    fact.loadFilter( flt );
  }
  catch ( IOException e )
  {
    WriteMsg::write(CMSG_CANNOT_OPEN_FILTER_FILE, flt.c_str());
  }
}

static inline void setStartTime(uint64_t *time)
{
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system;
}

static inline void setElapsedTime(uint64_t *time)
{
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system - *time;
}

static inline void updateMemStat(uint64_t *max_mem)
{
  memstat ms = getProcessUsedMemSize();
  if (*max_mem < ms.size) {
    *max_mem = ms.size;
  }
}

int main( int argc, char* argv[] )
{
  int exitCode = 0;
  MAIN_BEGIN

  uint64_t totalTime;
  uint64_t conversionTime;
  uint64_t saveTime;

  uint64_t maxMem = 0;

  int missingFiles = 0;

  setStartTime( &totalTime );

  // preparing comman line options
  columbus::PAN2Lim::options::parse( argc, argv);

  // lim graph
  RefDistributorStrTable limStrTable;
  lim::asg::Factory limFactory( limStrTable, "", lim::asg::limLangPython );

  // origin
  LimOrigin origin;

  setStartTime( &conversionTime );

  for ( list<string>::const_iterator it = PAN2Lim::options::inputFiles.begin(); it != PAN2Lim::options::inputFiles.end(); ++it )
  {
    // creating factory
    RefDistributorStrTable javaStrTable;
    python::asg::Factory factory( javaStrTable );

    // load schema instance
    WriteMsg::write(CMSG_LOADING_FILE, it->c_str());

    CsiHeader header;
    try
    {
      factory.load( it->c_str(), header );
    }
    catch ( IOException e )
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
    if ( ! PAN2Lim::options::noFilter )
    {
      factory.turnFilterOn();
      factory.initializeFilter();
      loadFilter( factory, *it );

      factory.turnFilterOff();
    }

    // PAN2Lim visitor is created and called
    WriteMsg::write(CMSG_CONVERTING_FILE, it->c_str());

    python::Python2LimVisitor::Key2IdMapType uname2NodeId;

    python::Python2LimVisitor visitor(factory, limFactory, origin, compPath, uname2NodeId);
    python::asg::AlgorithmPreorder().run( factory, visitor, *factory.getRoot() );

    updateMemStat( &maxMem );

    if ( PAN2Lim::options::maxMem != 0 && maxMem > PAN2Lim::options::maxMem )
    {
      WriteMsg::write( CMSG_MAXMEM_EXCEEDED );
      break;
    }
  }

  // finalizing and cleanup
  python::Python2LimVisitor::finalize( limFactory );

  updateMemStat( &maxMem );

  setElapsedTime( &conversionTime );
  setStartTime( &saveTime );

  // saving the lim graph
  WriteMsg::write(CMSG_SAVING_FILE, options::out.c_str());

  std::list<HeaderData*> limHeader;
  limHeader.push_back( &origin );

  try
  {
    limFactory.save( PAN2Lim::options::out, limHeader );
  }
  catch  (IOException e)
  {
    WriteMsg::write(CMSG_WARN_CANNOT_WRITE_FILE, options::out.c_str());
  }

  // saving the filter
  string filterfile = options::out.substr(0, options::out.find_last_of('.')) + ".flim";
  try
  {
    limFactory.saveFilter(filterfile);
  }
  catch  (IOException e)
  {
    WriteMsg::write(CMSG_WARN_CANNOT_WRITE_FILE, filterfile.c_str());
  }

  setElapsedTime( &saveTime );
  setElapsedTime( &totalTime );

  WriteMsg::write(
      CMSG_STATISTICS,
      conversionTime / 100.0f,
      saveTime / 100.0f,
      totalTime / 100.0f,
      maxMem / 1048576,
      missingFiles
  );

  MAIN_END

  return exitCode;
}
