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

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <list>
#include <fstream>
#include <common/inc/Arguments.h>
#include <common/inc/WriteMessage.h>
#include "ErrorCodes.h"
#include <common/inc/messages.h>

#if defined(__unix__)
#define CL_PAR_PLUS           '\''                // 'one parameter'
#elif  defined(_WIN32)
#define CL_PAR_PLUS           '"'                 // 'one parameter'
#endif

using namespace std;

#define MAX_BUFFER 4096

namespace common {

  static int countQuotationMarks(const char *s)
  {
    int counter = 0;
    const char *c = s;
    bool bs = false;
    while (*c) {
      switch (*c) {
        case '\\':
          bs = !bs;  
          break;
        case CL_PAR_PLUS:
          if (!bs)
            counter++;
          bs = false;
          break;
        default:
          bs = false;
          break;
      }
      c++;
    }
    return counter;
  }

  static string removeQuotationMarks(string s)
  {
    string::size_type ib = 0, ie = s.length()-1;
    while( s[ib] == CL_PAR_PLUS ) ++ib;
    while( s[ie] == CL_PAR_PLUS ) --ie;
    if( ib || ie != s.length()-1 )
      return s.substr(ib, ie);
    return s;
  }

  void constructArguments(const string& str, int& argc, char ** &argv)
  {
    list<string> params;   
    string param="";
    int qmc = 0;
    bool bs=false;

    unsigned int i;
    for (i=0; i<str.length(); i++){
      switch(str[i]){
        case '"':
          if (!bs)
            qmc++;
          param += str[i];
          bs = false;
          break;
        case '\\':
          bs = true;
          param += str[i];
          break;
        case '\n':
        case ' ':
          if (qmc%2){
            bs=false;
            param+=str[i];
          } else {
            params.push_back(param);
            param = "";
            qmc = 0;
            bs = false;
          }
          break;
        default:
          param += str[i];
          bs = false;
      }
    }

    // creating the new argv array
    argc = (int)params.size();
    argv = (char**)malloc(sizeof(char*) * argc);
    if (!argv){
      argc = 0;
      return;
    }

    i = 0;
    for (list<string>::const_iterator it = params.begin(); it != params.end(); ++it, i++) {   
      (argv)[i] = (char*) malloc(sizeof(char)*it->length());
      strcpy((argv)[i],(char*)it->c_str());
    }
  }

  static bool processOptionFile(const Option* options, const char *optionPrefixes, void (*unrecOption)(char*), void (*fileParam)(char*), const Option* found_option, char* found_option_args[])
  {
    if (found_option->type & OT_OPTION_FILE) {   // 
      bool ret = true;
      if (found_option->process)
        ret = found_option->process(found_option, found_option_args);

      if (ret) {   // The file have to be processed
        common::WriteMsg::write(CMSG_DUINFO_OPTIONFILE, found_option_args[0]);
        FILE *f = fopen(found_option_args[0], "rt"); 
        if (!f) {
          common::WriteMsg::write(CMSG_DUINFO_FAILED_TO_OPEN, found_option_args[0]);
          return false;
        }
        // allocating buffer for the parameters
        char *buffer = (char*)malloc(MAX_BUFFER);   
        if (!buffer) {
          fclose(f);
          return false;
        }

        list<string> params;      
        string param;
        int qmc = 0;

        // reading the parameters
        while (fscanf(f, "%s", buffer) != EOF) {
          if (qmc %2)
            param += " ";

          qmc += countQuotationMarks(buffer);
          param += buffer;

          if (qmc % 2 == 0) {
            params.push_back(removeQuotationMarks(param));

            qmc = 0;
            param = "";
          }

        }
        if (qmc % 2)
          params.push_back(removeQuotationMarks(param));

        free(buffer);
        fclose(f);

        // creating the new argv array
        int newargc = (int)params.size();
        char **newargv = (char**)malloc(sizeof(char*) * newargc);
        if (!newargv)
          return false;
    
        int i = 0;
        for (list<string>::const_iterator it = params.begin(); it != params.end(); ++it, i++) {
          common::WriteMsg::write(CMSG_DUINFO_READ_PARAM, it->c_str());
          newargv[i] = (char*)it->c_str();
        }
        bool result = processArguments(newargc, newargv, options, optionPrefixes, unrecOption, fileParam);
        free(newargv);
        return result;
      }
  
    } else
      if (found_option->process)
        return found_option->process(found_option, found_option_args);
  
    return true;    
  }

  bool processArguments(int argc, char* argv[], const Option* options, const char *optionPrefixes, void (*unrecOption)(char*), void (*fileParam)(char*))
  {
    std::list<const Option*> defCallbacks;
    
    if (!options) {
      common::WriteMsg::write(CMSG_NO_OPTION_GIVEN);
      return false;
    }
  
    // for every parameter 
    for (int pnum = 0; pnum < argc; ++pnum) {   
      const Option* found_option = NULL;
    
      // check all the given options
      for (const Option* opt = options; opt->name[0]; ++opt) {
        
        bool match = false;
      
        if (opt->type & OT_PREFIX && !(opt->type & ( OT_WOS | OT_WC | OT_WE))) { // The unambiguous prefix is enough
        
          if (strstr(opt->name, argv[pnum]) == opt->name) 
            match = true;
      
        } else {   // The prefix is not enough
        
          if (strstr(argv[pnum], opt->name) == argv[pnum]) {
            size_t oplen = strlen(opt->name);
            if (
                (!argv[pnum][oplen] && ((!opt->param_num && !(opt->type & OT_OPTION_FILE)) || (opt->param_num && (opt->type & OT_WS) && !(opt->type & OT_DEFAULT)))) ||
                (!argv[pnum][oplen] && opt->param_num == 1 && (opt->type & OT_DEFAULT) && !(opt->type & OT_WS) && !(opt->type & OT_OPTION_FILE) && !(opt->type & OT_WOS)) ||
                (argv[pnum][oplen] && opt->param_num == 1 && (opt->type & OT_WOS) && !(opt->type & OT_DEFAULT)) ||
                (argv[pnum][oplen] == '=' && opt->param_num == 1 && (opt->type & OT_WE)) ||
                (argv[pnum][oplen] == ':' && opt->param_num == 1 && (opt->type & OT_WC)))
            {
              match = true;
            }
          }
        }
      
        if (match) {
          if (found_option) {
            common::WriteMsg::write(CMSG_AMBIGUOUS_PARAM);
            return false;            
          }
          found_option = opt;    
        }
      }

      // process the option parameters
      if (found_option) {
        if (found_option->param_num == 0) {         // The option doesn't have any parameter 
          if (found_option->process && !found_option->process(found_option, NULL)) {
            common::WriteMsg::write(CMSG_FAILED_PROCESSING, found_option->name);
            return false;
          }          
        } else if (found_option->param_num == 1) {  // The option has 1 parameter


          if (found_option->type & OT_PREFIX) {    

            if (pnum + 1 >= argc) { // The parameter must be separated from the option 
              common::WriteMsg::write(CMSG_FAILED_PROCESSING, found_option->name);
              return false;
            }

            if (!processOptionFile(options, optionPrefixes, unrecOption, fileParam, found_option, argv + pnum + 1)) {
              common::WriteMsg::write(CMSG_FAILED_PROCESSING, found_option->name);
              return false;
            }
            pnum++;
          }
          else if (found_option->type & OT_DEFAULT) {
            
            bool needProcess = true;
            size_t oplen = strlen(found_option->name);
            char* prm = NULL;

            if (argv[pnum][oplen] == '=')         //  -option=value (OT_WE)
              prm = argv[pnum] + oplen + 1;
            else if (argv[pnum][oplen] == ':')    //  -option:value (OT_WC)
              prm = argv[pnum] + oplen + 1;
            else {
              if (found_option->defaultProcess != NULL) {
                //if there's no parameter for the option a default value used (calling the default callback method)
                defCallbacks.push_back(found_option);
                needProcess = false;
              } else {
                common::WriteMsg::write(CMSG_NO_DEFAULT_VALUE, found_option->name);
                return false;
              }
            }

            if (needProcess) {
              if (!processOptionFile(options, optionPrefixes, unrecOption, fileParam, found_option, &prm)) {
                common::WriteMsg::write(CMSG_FAILED_PROCESSING, found_option->name);
                return false;
              }
            }

          } else {    
            size_t oplen = strlen(found_option->name);
            char* prm = NULL;

            if (argv[pnum][oplen] == '=')         //  -option=value (OT_WE)
              prm = argv[pnum] + oplen + 1;
            else if (argv[pnum][oplen] == ':')    //  -option:value (OT_WC)
              prm = argv[pnum] + oplen + 1;
            else if (argv[pnum][oplen])           //  -optionvalue (OT_WOS)
              prm = argv[pnum] + oplen;  
            else {                                // -option value (OT_WS)
              if (pnum + 1 >= argc)  {
                common::WriteMsg::write(CMSG_FAILED_PROCESSING, found_option->name);
                return false;
              }
              prm = argv[pnum+1];
              pnum++;
            }

            if (!processOptionFile(options, optionPrefixes, unrecOption, fileParam, found_option, &prm)) {
              common::WriteMsg::write(CMSG_FAILED_PROCESSING, found_option->name);
              return false;
            }          
          }        
        } else if (found_option->param_num > 1) {   // The option has more than 1 parameter
        
          if (pnum + found_option->param_num >= argc) {
            common::WriteMsg::write(CMSG_FAILED_PROCESSING, found_option->name);
            return false;
          }

          if (found_option->process && !found_option->process(found_option, argv + pnum + 1)) {
            common::WriteMsg::write(CMSG_FAILED_PROCESSING, found_option->name);
            return false;
          }
        
          pnum += found_option->param_num;
        }
      } else {  // Unrecognized option or file
        if (strchr(optionPrefixes, argv[pnum][0]))  {  // This is an unrecegnized option
          if (unrecOption) 
            unrecOption(argv[pnum]);
          else
            common::WriteMsg::write(CMSG_UNRECOGNIZED_PARAM, argv[pnum]);
        } else {  // This is not an option
          if (fileParam)
            fileParam(argv[pnum]);
        } 
      } //if(found_option) + else
    } //for (int pnum = 0; pnum < argc; ++pnum) {
    
    std::list<const Option*>::iterator it;
    for (it = defCallbacks.begin(); it != defCallbacks.end(); it++) {
       const Option* opt = *it;
       opt->defaultProcess(*it);
    }
  
    return true;
  } //processArguments

}



