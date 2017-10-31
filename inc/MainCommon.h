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

#ifndef __MAINCOMMON_H__
#define __MAINCOMMON_H__

#include "common/inc/Arguments.h"
#include "common/inc/WriteMessage.h"
#include "common/inc/StringSup.h"
#include "Exception.h"
#include "ErrorCodes.h"
#include "ReleaseVersion.h"
#include "LanguageCommon.h"
#include <new>
#include <sstream>
#include <list>
#include <map>
#include <cstdlib>
#include <cstring>
#include <time.h>

#ifndef TOOLCHAIN_VERSION
#define TOOLCHAIN_VERSION PROJECT_VERSION
#endif

//Forward declaration of ppFile
static void ppFile(char *filename);


#define CL_KIND_FILENAME          "filename"
#define CL_KIND_FILE              "file"
#define CL_KIND_DIR               "directory"
#define CL_KIND_CONFIG            "configuration"
#define CL_KIND_CHAR              "character"
#define CL_KIND_NUMBER            "number"
#define CL_KIND_STRING            "string"
#define CL_KIND_BOOL              "(true|false)"
#define CL_KIND_URL               "url"
#define CL_KIND_REGEXP            "regexp"

#define CL_LIM \
 { false,  "-lim",       1, CL_KIND_FILENAME, 1, common::OT_WC,    ppLimFile,      NULL, "The corresponding LIM file."},

#define CL_REFLECTION_FILTER \
 { false,  "-filterrefl",0, "",               0, common::OT_NONE,  ppFilterRefl,   NULL, "Filter nodes built by reflection."},

#define CL_RUL_AND_RULCONFIG(def) \
 { false,  "-rul",       1, CL_KIND_FILENAME, 0, common::OT_WC,    ppRul,          NULL, "The .rul configuration file. If it is not specified, the '" def "' will be used " \
                                                                                         "from the directory of the executable."}, \
 { false,  "-rulconfig", 1, CL_KIND_CONFIG,   0, common::OT_WC,    ppRulConfig,    NULL, "Name of the rul configuration."},


#define CL_EXPORTRUL \
 { false, "-exportrul",  0, "",               0, common::OT_WC,    ppExportRul,    NULL, "Export the current rul configuration into the graph output."},

#define CL_CSVSEPARATOR \
 { false, "-csvseparator", 1, CL_KIND_CHAR,   0, common::OT_WC,    ppCsvSeparator, NULL, "Set the separator character for the csv output. TAB character can be set with '\\t'"},

#define CL_CSVDECIMALMARK \
 { false, "-csvdecimalmark", 1, CL_KIND_CHAR, 0, common::OT_WC,    ppCsvDecimalMark, NULL, "Set the decimal mark character for floating point values of the csv output."},

#define CL_SAFEMODE \
 { false, "-safemode",   0, "",               0, common::OT_NONE,  ppSafemode,     NULL, "Turns on safe mode, which prevents endless visiting in case of any circle in the graph."},

#define CL_FLTP \
 { false, "-fltp",       1, CL_KIND_FILENAME, 0, common::OT_WC,    ppFilterPath,   NULL, "The filter file which contains regular expressions to filter out things on a specific path."},

#define CL_INPUT_LIST \
 { false, "-inputlist",  1, CL_KIND_FILENAME, 0, common::OT_WC,    ppList,         NULL, "A list file, which contains the list of the input files."},

#define CL_HELP \
 { false, "-?",          0, "",               0, common::OT_NONE,  ppHelp,         NULL, "Displays the list of command line options"},\
 { false, "/?",          0, "",               0, common::OT_NONE,  ppHelp,         NULL, "Displays the list of command line options"},\
 { false, "-help",       0, "",               0, common::OT_NONE,  ppHelp,         NULL, "Displays the list of command line options"},\


#define CL_VERBOSE \
 { true,  "-verbose",    0, "",               0, common::OT_NONE,  ppVerbose,      NULL, "Creates more detailed log messages and files"},


#define CL_VERSION \
 { false, "-ver",        0, "",               0, common::OT_NONE,  ppVersion,      NULL, "Displays the version information"},


#define CL_MESSAGELEVEL \
 { false, "-ml",        1, CL_KIND_NUMBER,   0, common::OT_WC,    NULL,           NULL, "Sets the message level of the program\n"\
                                                                                         "0 (silent)  does not write any message\n"\
                                                                                         "1 (error)   writes out error messages only\n"\
                                                                                         "2 (warning) writes out error and warning messages\n"\
                                                                                         "3 (normal)  writes out information about execution of the program\n"},


#define CL_LAST \
 { true,  "",            0, "",               0, common::OT_NONE,  NULL,           NULL, "This must be the last one!"}

//Defining the common command line arguments

#define COMMON_CL_ARGS \
 CL_HELP               \
 CL_MESSAGELEVEL       \
 CL_VERSION            \
 CL_LAST

//Defining the try-catch blocks of the main() method
#ifdef NDEBUG

#define TRY_BEGIN       try {
#define TRY_END         }
#define CATCH_EXCEPTION catch (const columbus::Exception& e) {\
  common::WriteMsg::write(common::WriteMsg::mlError, "Internal error: %s : %s\n", e.getLocation().c_str(), e.getMessage().c_str());\
  return EXIT_FAILURE;\
}

#define CATCH_STD_EXCEPTION catch (const std::exception& e) {\
  common::WriteMsg::write(common::WriteMsg::mlError, "Internal error: %s \n", e.what());\
  return EXIT_FAILURE;\
}

#define CATCH_STD_BAD_ALLOC_EXCEPTION catch (const std::bad_alloc&) {\
  common::WriteMsg::write(common::WriteMsg::mlError, "Internal error: Out of memory!\n");\
  return EXIT_FAILURE;\
}

#define CATCH_SPEC_EXCEPTION(ex)  catch (const ex& e) {\
  common::WriteMsg::write(common::WriteMsg::mlError, "Internal error: %s : %s\n", e.getLocation().c_str(), e.getMessage().c_str());\
  return EXIT_FAILURE;\
}
#define CATCH_ALL_OTHER catch(...) {\
  common::WriteMsg::write(common::WriteMsg::mlError, "Internal error: Unknown exception occured\n");\
  return EXIT_FAILURE;\
}
#else

#define TRY_BEGIN
#define TRY_END
#define CATCH_EXCEPTION
#define CATCH_STD_EXCEPTION
#define CATCH_STD_BAD_ALLOC_EXCEPTION
#define CATCH_SPEC_EXCEPTION(ex)
#define CATCH_ALL_OTHER

#endif


#define MAIN_BEGIN TRY_BEGIN

#define MAIN_END TRY_END\
  CATCH_EXCEPTION\
  CATCH_STD_BAD_ALLOC_EXCEPTION\
  CATCH_STD_EXCEPTION\
  CATCH_ALL_OTHER

//Forward declaration of the Option object which contains the existing cl options 
extern const common::Option OPTIONS_OBJ [];

/**
* \brief A callback function for the -version cl option
* \param o [in] A pointer to the Option object
* \param argv[] [in] A pointer to the main methods argv[] array
* \return true
*/
static bool ppVersion(const common::Option *o, char *argv[]) {
  exit(EXIT_SUCCESS);
}

/**
* \brief This method writes the copyright message and information to std::out
*/
void copyright() {
#ifdef HAS_LANGUAGE_CONFIG
  common::WriteMsg::write(common::WriteMsg::mlNormal, "%s %s %s (Build:%s) - %s\n", PROGRAM_NAME, TOOLCHAIN_VERSION, LANGUAGE_STR, REVISION_NUMBER, CopyRightMessage);
#else
  common::WriteMsg::write(common::WriteMsg::mlNormal, "%s %s (Build:%s) - %s\n", PROGRAM_NAME, TOOLCHAIN_VERSION, REVISION_NUMBER, CopyRightMessage);
#endif
}


/**
* \brief This method breaks the long description lines at whitespaces or line breaks in order to fit the text to screen.
* \param str [in] The string needs to be fit to screen
*/
static void tokenizeString(const std::string& str, std::list<std::string>& tokens) {
  size_t endlPos;
  size_t pos;

  endlPos = str.find_first_of("\n");
  if ((endlPos != std::string::npos) && (endlPos < 70)) {
    tokens.push_back(str.substr(0,endlPos));
    tokenizeString(str.substr(endlPos+1,str.length()), tokens);
    return;
  }
  if (str.length() > 70) {
    pos = str.substr(0,70).find_last_of(" ");
    tokens.push_back(str.substr(0,pos));
    tokenizeString(str.substr(pos+1,str.length()-pos), tokens);
  }
  else {
    tokens.push_back(str);
  }
}

void writeOptionWithParams(const char* optionName, const char* token, const char* paramName, const unsigned int otMode) {
  if (otMode == common::OT_OPTION_FILE) 
    common::WriteMsg::write(common::WriteMsg::mlNormal, "  %s %s\n", optionName, paramName);
  else if (otMode == common::OT_DEFAULT)
    common::WriteMsg::write(common::WriteMsg::mlNormal, "  %s\n", optionName);
  else if (otMode == common::OT_PREFIX)
    common::WriteMsg::write(common::WriteMsg::mlNormal, "  %s %s (unambiguous prefix is enough)\n", optionName, paramName);
  else 
    common::WriteMsg::write(common::WriteMsg::mlNormal, "  %s%s%s\n", optionName, token, paramName);
}

void formatAndWriteString(const std::string& description, std::list<std::string>& tokens){
  // checks whether the description is longer than 70 characters, or containing a newline character
  if (description.length() > 70 || description.find("\n") != std::string::npos) {
    tokenizeString(description, tokens);
    for (std::list<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
      if (it == tokens.begin()) 
        common::WriteMsg::write(common::WriteMsg::mlNormal, "    %s\n", it->c_str());
      else 
        common::WriteMsg::write(common::WriteMsg::mlNormal, "   %s %s\n", "", it->c_str());    
    }
  }
  else 
    common::WriteMsg::write(common::WriteMsg::mlNormal, "    %s\n", description.c_str());  
}
/**
* \brief Writes the help of cl options to std::out
*/
static void Help(bool isInternalEnabled = false) {
  const common::Option *option = OPTIONS_OBJ;
  
  std::map<int,std::list<std::string> >::iterator it;
  std::map<int,std::list<std::string> > optionMap; //<< map to storage the needed option name
  std::string optionsString;  //<< string to storage the option usage description

  // find the needed options and put in the map where the key will be the option->needed number
  while (option->name[0]) {
    if (option->needed != 0) {
      it = optionMap.find(option->needed);
      if (it != optionMap.end()) {
        it->second.push_back(option->name);

      }
      else {
        std::list<std::string> optionNames;
        optionNames.push_back(option->name);
        optionMap.insert(std::pair<int,std::list<std::string> >(option->needed,optionNames));
      }
    }
    option++;
  }

  
  optionsString.append(EXECUTABLE_NAME);  //<< append programName to the usage description
  optionsString.append(" [options] "); 
  for (it=optionMap.begin(); it!=optionMap.end(); it++) {
    std::list<std::string>::iterator iter;
    if (it->second.size()>1) { //<<if possible to choose beetween needed options
      optionsString.append("{ ");
      for (iter=it->second.begin(); iter!=it->second.end();iter++) {
        if (iter!=it->second.begin())
          optionsString.append(" | ");
        optionsString.append(*iter);
      }
      optionsString.append(" } ");

    }
    else {
      iter = it->second.begin();
      optionsString.append(*iter);
      optionsString.append(" ");
    }
  }

  optionsString.append(" input file(s)\n\n");
  std::list<std::string> tokens;
  common::WriteMsg::write(common::WriteMsg::mlNormal, "\n  Usage:\n\n");
  formatAndWriteString(optionsString, tokens);
  common::WriteMsg::write(common::WriteMsg::mlNormal, "  Options:\n");

  tokens.clear();

  option = OPTIONS_OBJ;
  std::string description = "";  
  bool skipped=false, prevInternal=false;
  // find and write the possible given mode for the options and write their description 
  while (option->name[0]) {
    if (description != option->descr && (skipped || !prevInternal || isInternalEnabled)) {
      formatAndWriteString(description, tokens);
      common::WriteMsg::write(common::WriteMsg::mlNormal, "\n");
      skipped = false;
    }
    else {
      if (!skipped && !prevInternal)
        skipped = true;
    }
    if (!option->internal || isInternalEnabled) {
       
      if (option->param_num == 0) {
        common::WriteMsg::write(common::WriteMsg::mlNormal, "  %s\n", option->name);
      }
      // the different given mode tokens
      else {
        if ((option->type & common::OT_NONE) == common::OT_NONE) {}
        if ((option->type & common::OT_WS) == common::OT_WS) {
          writeOptionWithParams(option->name, " ", option->param_name, common::OT_WS);

        } 
        if ((option->type & common::OT_WOS) == common::OT_WOS) {
          writeOptionWithParams(option->name, "", option->param_name, common::OT_WOS);
        }
        if ((option->type & common::OT_WE) == common::OT_WE) {
          writeOptionWithParams(option->name, "=", option->param_name, common::OT_WE);
        }
        if ((option->type & common::OT_WC) == common::OT_WC) {
          writeOptionWithParams(option->name, ":", option->param_name, common::OT_WC);
        }
        if ((option->type & common::OT_PREFIX)  == common::OT_PREFIX ) {
          writeOptionWithParams(option->name, "", option->param_name, common::OT_PREFIX);
        }
        if ((option->type & common::OT_OPTION_FILE)  == common::OT_OPTION_FILE ) {
          writeOptionWithParams(option->name, "", option->param_name, common::OT_OPTION_FILE);
        }
        if ((option->type & common::OT_DEFAULT)  == common::OT_DEFAULT ) {
          writeOptionWithParams(option->name, "", option->param_name, common::OT_DEFAULT);
        }

      }
    }
    description=option->descr;
    prevInternal=option->internal;
    tokens.clear();
    option++;
  }
  if (!prevInternal || isInternalEnabled) {
      formatAndWriteString(description, tokens);
      common::WriteMsg::write(common::WriteMsg::mlNormal, "\n");
      skipped = false;
  }
}

/**
* \brief Writes error message and Help()
*/
void clError() {
  common::WriteMsg::write(common::WriteMsg::mlError, "\nBad command line!\n\n");
  Help();
  exit(common::retBadArgError);
}


/**
* \brief A callback function for the -help cl option
* \param o [in] A pointer to the Option object
* \param argv[] [in] A pointer to the main methods argv[] array
* \return true
*/
static bool ppHelp(const common::Option *o, char *argv[]) {
  Help();
  exit(EXIT_SUCCESS);
  return true;
}

/**
* \brief Callback function for an unrecognized cl option
* \param o [in] Pointer to a char
*/
static void ppUnknownOption(char *o) {
  common::WriteMsg::write(common::WriteMsg::mlNormal, "Unrecognized option:%s\n", o);
  Help();
  exit(EXIT_FAILURE);
}

/**
* \brief This method encapsulates all the necessary things can be done in the beginning of main method.
* \param argc [in] The same as argc of main. (Number of command line parameters)
* \param argv [in] The same as argv of main. (The command line parameters stored in this array)
* \param optionPrefixes [in] The character which is the prefix of commnad line paramteres
* \param rVersion [in] The release version of the program. The license checking needs it.
*/
static void MainInit(int argc, char* argv[], const char* optionPrefixes) {
  //processing -ml and -silent
  common::WriteMsg::setMessageLevel(argc, argv);

  srand((unsigned)time(NULL));
  
  //Writes out the copyright message
  copyright();

  //processing the command line arguments
  processArguments(argc - 1, argv + 1, OPTIONS_OBJ, optionPrefixes, ppUnknownOption, ppFile);
}

#endif //__MAINCOMMON_H__
