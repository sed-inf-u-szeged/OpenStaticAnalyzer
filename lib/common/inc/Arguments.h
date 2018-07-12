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

#ifndef _ARGUMENTS_H
#define _ARGUMENTS_H

#include <string>

namespace common
{
  const unsigned OT_NONE            = 0; 

    /** \brief With space (opt value). */
  const unsigned OT_WS              = 1;   // 0000000000000001   

    /** \brief Without space (optvalue). */
  const unsigned OT_WOS             = 2;   // 0000000000000010   

    /** \brief With equal sign (opt=value). */
  const unsigned OT_WE              = 4;   // 0000000000000100   
  
    /** \brief With colon (opt:value). */
  const unsigned OT_WC              = 8;   // 0000000000001000   
  
    /** \brief The unambiguous prefix is enough. */
  const unsigned OT_PREFIX          = 16;  // 0000000000010000  

    /** \brief The parameter is a filename which contains additional options.
    * The process function will be called before the options in the file are processed.
    * If the function return false then the file won't be processed.
    */
  const unsigned OT_OPTION_FILE     = 32;   // 0000000000100000

    /** \brief The option has 1 parameter but not given then a default value used */
  const unsigned OT_DEFAULT         = 64;   // 0000000001000000

  /** \brief Structure to store a command line option of a tool. */
  typedef struct Option {
    bool internal;                                        /**< Internal option (not displayed!). */
    const char* name;                                     /**< Commandline option. */
    int param_num;                                        /**< The number of the parameters of the option. */
    const char *param_name;                               /**< The parameter kind name (for example: filename, value etc.) */
    int needed;                                           /**< The number of the needed option. If 0 is not needed, if the number is equal other option needed number, then just one of them is needed (optional) */
    unsigned type;                                        /**< Type of the option. */
    bool (*process)(const Option*, char* args[]);         /**< Process to be called. */
    bool (*defaultProcess)(const Option*);                /**< Process to be called if the option needs paramater but not set (using the default parameter value). */
    const char *descr;                                    /**< Description of the option. */
  } Option;

  /**
   * \brief Creation arguments from a string.
   * \param str thestr what contains the arguments
   * \param argc outgoing parameter, the number of the arguments
   * \param argv array containing the arguments. The malloced memory have to be free.
   */
  void constructArguments(const std::string& str, int& argc, char ** &argv);

  /**
   * \brief Processes the arguments.
   *
   * This function processes the argv array and calls the corresponding callback function.
   * \return true if all argumetnst are successfuly processed
   * \param argc the numner of the arguments
   * \param argv array containing the pointers for each argument
   * \param options array containing the options, which must be recognized
   * \param optionPrefixes arguments starting with any character from that string is considered as an option
   * \param unrecOption this function will be called at every unrecogized option. 
   * \param fileParam this function will be called at every non option argument. 
   */
  bool processArguments(int argc, char* argv[], const Option* options, const char *optionPrefixes, void (*unrecOption)(char*), void (*fileParam)(char*));
}


#endif

