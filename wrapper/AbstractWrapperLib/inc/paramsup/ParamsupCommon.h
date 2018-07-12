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

#ifndef _PARAMSUP_COMMON_H
#define _PARAMSUP_COMMON_H

#include <list>
#include <string>
#include <map>
#include <common/inc/WriteMessage.h>

namespace ColumbusWrappers {

  /**
   * @brief Enum for error codes
   */
  typedef enum {
    EC_FOUND = 0,
    EC_NOT_FOUND,
    EC_ERROR
  } ParErrorCode;

  /**
   * @brief Type for arguments, its position in the input argumentlist, and if it is an input file, then its language (c, cpp).
   */
  struct Argument {
    Argument() : name(),
                 position(0),
                 lang() {}
    std::string name;
    int position;
    std::string lang;
  };

  /**
   * @brief Struct for archive arguments.
   *
   * archive_modifiers       String list for CANLib modifier options.
   * archive_operations      String list for CANLib operations.
   * input_files             String list for input files.
   * archive_file            String for output archive file.
   * asg_file                String for the name of asg (object) file where we want to insert another asg (object) file.
   * not_handled_args        String list for recognized but not handled arguments.
   * archive_mode            String for CANLib archive mode (-l or -w).
   * put_before              True, if we want to insert asg (object) before the given asg_file.
   * put_after               True, if we want to insert asg (object) after the given asg_file.
   * delete_or_extract       True, it we want to delete an asg or extract one from the given archive file.
   * need_create             True, if output archive file need to be created.
   * no_output               True, if no output switch was given.
   * first_input             The first lib or object file in the command line (needed to LIB wrapper).
   */
  struct ArchiveArgs {
    ArchiveArgs() : archive_modifiers(),
                    archive_operations(),
                    input_files(),
                    archive_file(),
                    asg_file(),
                    asgMemberName(),
                    not_handled_args(),
                    archive_mode(),
                    put_before(false),
                    put_after(false),
                    delete_or_extract(false),
                    need_create(false),
                    no_output(true),
                    first_input(),
                    original_dates(false ) {}
    std::list<std::string> archive_modifiers;
    std::list<std::string> archive_operations;
    std::list<std::string> input_files;
    std::string archive_file;
    std::string asg_file;
    std::string asgMemberName;
    std::list<std::string> not_handled_args;
    std::string archive_mode;
    bool put_before;
    bool put_after;
    bool delete_or_extract;
    bool need_create;
    bool no_output;
    std::string first_input;
    bool original_dates;
  };

  /**
   * @brief Struct for argument warnings and unrecognized arguments.
   *
   * can_warning       String list for argument warnings.
   * unrec_args        String list for unrecognized arguments.
   */
  struct Warnings {
    Warnings() : can_warning(), unrec_args() {}
    std::list<std::string> can_warning;
    std::list<std::string> unrec_args;
  };

  /**
   * @brief Struct for preprocessor arguments for CAN.
   *
   * prep_inc_paths        String list for preprocessor include paths.
   * prep_inc_files        String list for preprocessor include files.
   * prep_defs             String list for preprocessor macro definitions.
   * prep_undefs           String list for preprocessor macro undefinitions.
   * prep_args             String list for preprocessor arguments.
   * prep_isystem_dirs     String list for -isystem arguments.
   */
  struct PreprocArgs {
    PreprocArgs() : prep_inc_paths(), prep_inc_files(), prep_defs(), prep_undefs(), prep_args(), prep_isystem_dirs() {}
    std::list<Argument> prep_inc_paths;
    std::list<Argument> prep_inc_files;
    std::list<Argument> prep_defs;
    std::list<Argument> prep_undefs;
    std::list<Argument> prep_args;
    std::list<Argument> prep_isystem_dirs;
  };

  /**
   * @brief Struct for compiler arguments.
   *
   * compiling           True if compiling is needed by arguments.
   * use_pch             True if need to use automatic PCH creation mechanism.
   * comp_output_file    The name of the output file.
   * comp_input_file     String list for compiler input files.
   * comp_args           String list for compiler arguments.
   * max_arg             The maximum number read arguments.
   * no_output           True, if no output switch was given.
   */
  struct CompilerArgs {
    CompilerArgs() : compiling(true),
                     use_pch(false),
                     comp_output_file(),
                     comp_input_files(),
                     comp_args(),
                     max_arg(8192),
                     no_output(true) {}
    bool compiling;
    bool use_pch;
    Argument comp_output_file;
    std::list<Argument> comp_input_files;
    std::list<Argument> comp_args;
    int max_arg;
    bool no_output;
  };

  /**
   * @brief Struct for linker arguments.
   *
   * linking               True if linking is needed by arguments.
   * create_lib            True if linker has to create lib.
   * create_dll            True if linker has to create dll.
   * relocatable           True if "-r", "--relocateable", "--relocatable" or "-Ur" argument found.
   * import_lib_name       The name of the /implib import lib.
   * linker_output_name    The name of the output file.
   * linker_input_files    String list for input files.
   * linker_lib_paths      String list for linker input lib paths.
   * linker_lib_files      String list for linker input lib files.
   * linker_args           String list for linker arguments.
   * max_arg               The maximum number read arguments.
   * no_output             True, if no output switch was given.
   */
  struct LinkerArgs {
    LinkerArgs() : linking(true),
                   create_lib(false),
                   create_dll(false),
                   relocatable(false),
                   import_lib_name(),
                   linker_output_file(),
                   linker_input_files(),
                   linker_lib_paths(),
                   linker_lib_files(),
                   linker_args(),
                   max_arg(8192),
                   no_output(true) {}
    bool linking;
    bool create_lib;
    bool create_dll;
    bool relocatable;
    Argument import_lib_name;
    Argument linker_output_file;
    std::list<Argument> linker_input_files;
    std::list<Argument> linker_lib_paths;
    std::list<Argument> linker_lib_files;
    std::list<Argument> linker_args;
    int max_arg;
    bool no_output;
  };

  /**
   * @brief Determines whether the given iterator is the last before the given end_it.
   * @param it         [in] Iterator pointed to an element of the argument list.
   * @param end_it     [in] Iterator pointed to the end of the argument list.
   * @return                True if the given iterator is the last before the given end_it.
   */
  bool isLast(const std::list<std::string>::iterator& it, const std::list<std::string>::const_iterator& end_it);

  /**
   * @brief Wraps common::indep_fullpath()
   */
  std::string indepFullpath(const std::string& path);

  /**
   * @brief Wraps common::indep_fullpath()
   */
  std::string indepFullpath(const char* path);

  /**
   * @brief Wraps common::indep_fullpath()
   */
  void indepFullpath(const char* path, std::string& str_path);


  /**
   * @brief Function for std::list<Argument>::sort() method. It compares the position of the two input Argument type variables.
   * @param first        [in] The first Argument.
   * @param second       [in] The second Argument.
   * @return                  True if position of the first argument is less than the position of the second.
   */
  bool compareArguments(Argument first, Argument second);

  /**
   * @brief Writes timestamp from actual time.
   * @return                  Actual time in string in "[weekday month day hour:min:sec year]" format
   */
  std::string writeTimeStamp();

  /**
   * @brief Writes info message in "[INFO][timestamp][location] message" format.
   *        It calls WriteMsg::write in mlNormal level.
   * @param location       [in] The location of the message (in which class or file is found).
   * @param msg            [in] The given message.
   */
  void writeInfoMsg(const char* location, const char* msg, ...);

  /**
   * @brief Writes info message in "[ERROR][timestamp][location] message" format.
   *        It calls WriteMsg::write in mlError level.
   * @param location       [in] The location of the message (in which class or file is found).
   * @param msg            [in] The given message.
   */
  void writeErrorMsg(const char* location, const char* msg, ...);

  /**
   * @brief Writes info message in "[WARNING][timestamp][location] message" format.
   *        It calls WriteMsg::write in mlWarning level.
   * @param location       [in] The location of the message (in which class or file is found).
   * @param msg            [in] The given message.
   */
  void writeWarningMsg(const char* location, const char* msg, ...);

    /**
   * @brief Writes info message in "[level][timestamp][location] message" format.
   *        It calls WriteMsg::write in given level.
   * @param file           [in] The path of the destination file. If it is NULL or it cannot be opened, then stdout is used.
   * @param location       [in] The location of the message (in which class or file is found).
   * @param level          [in] The given message level: mlDebug, mlDDebug, mlDDDebug, mlDDDDebug
   * @param msg            [in] The given message.
   */
  void writeMsgToFile(const char* file, const char* location,common::WriteMsg::MsgLevel level, const char* msg, ...);

  /**
   * @brief Writes info message in "[DEBUG][timestamp][location] message" format.
   *        It calls WriteMsg::write in given level.
   * @param location       [in] The location of the message (in which class or file is found).
   * @param level          [in] The given message level: mlDebug, mlDDebug, mlDDDebug, mlDDDDebug
   * @param msg            [in] The given message.
   */
  void writeDebugMsg(const char* location, common::WriteMsg::MsgLevel level, const char* msg, ...);

  /**
   * @brief Inserts the parameter of the actual member of include argument list into the given argument list. The parameter is given to an argument as name
   *        and that argument is put into the argumentlist. (e.g.: -Iinclude\\dir\\path -> include\\dir\\path is given to an argument as name)
   * @param it                            [in] Iterator pointed to the actual element of the input argument list. The parameter of this element is given to actArg as name.
   * @param args_end                      [in] Iterator pointed to the end of the argument list.
   * @param actArg                        [in out] The actual argument is represented by this struct. This argument is put into the given argumentlist. This argument got the given parameter as name.
   * @param argList                       [out] The given argument list of the analyzer tool where the actArg is put in.
   * @param argName                       [in] The name of the given parameter which is set to name of actual argument.
   * @param maybeSpaceSeparatedArgument   [in] It is true if there can be a space between the argument and its parameter.
   * @return                                  EC_FOUND if recognizes the argument
   * @return                                  EC_NOT_FOUND if not recognizes the argument
   * @return                                  EC_ERROR if the given argument is not correct.
   */
  ColumbusWrappers::ParErrorCode insertParameterOfArgumentIntoArgumentList(std::list<std::string>::iterator& it, const std::list<std::string>::const_iterator& args_end, Argument& actArg, std::list<Argument>& argList, std::string argName, bool maybeSpaceSeparatedArgument);

  /**
   * @brief Sets parameter of the actual argument to the given argument as name. (e.g.: -o outputfile -> outputfile is set to name of given argument).
   * @param it                            [in] Iterator pointed to the actual element of the input argument list. The parameter of this element is given to actArg as name.
   * @param args_end                      [in] Iterator pointed to the end of the argument list.
   * @param actArg                        [in out] The actual argument is represented by this struct. This argument got the given parameter as name.
   * @param actualArgument                [in out] It is the same as actArg. It needs for error message if there is some problem.
   * @param argName                       [in] The name of the given parameter which is set to name of actual argument.
   * @param maybeSpaceSeparatedArgument   [in] It is true if there can be a space between the argument and its parameter.
   * @return                                  EC_FOUND if recognizes the argument
   * @return                                  EC_NOT_FOUND if not recognizes the argument
   * @return                                  EC_ERROR if the given argument is not correct.
   */
  ColumbusWrappers::ParErrorCode setParameterOfArgumentToArgument(std::list<std::string>::iterator& it, const std::list<std::string>::const_iterator& args_end, Argument& actArg, Argument& actualArgument, std::string argName, bool maybeSpaceSeparatedArgument);

  /**
   * @brief Inserts the given argument into an argumentlist. It is got a parameter as the name of actual argument.
   * @param actArg                        [in out] The actual argument is represented by this struct. This argument is put into the given argumentlist. This argument got the given parameter as name.
   * @param argList                       [out] The given argument list of the analyzer tool where the actArg is put in.
   * @param argName                       [in] The name of the given parameter which is set to name of actual argument.
   */
  void insertArgumentIntoArgumentList(Argument& actArg, std::list<Argument>& argList, std::string argName);

   /**
   * @brief Inserts the given argument into an argumentlist. It is got a parameter as the name of actual argument.
   * @param pattern                        [in] The actual argument is represented by this struct. This argument is put into the given list. This argument got the given parameter as name.
   * @param argList                        [out] The given argument list of the analyzer tool where the actArg is put in.
   */
  void resolveFilePatterToFiles(Argument& actArg , std::list<Argument>& argList) ;

   /**
   * @brief Inserts the given argument into an argumentlist. It is got a parameter as the name of actual argument.
   * @param pattern                        [in] The actual argument is represented by this struct. This argument is put into the given list. This argument got the given parameter as name.
   * @param argList                        [out] The given argument list of the analyzer tool where the actArg is put in.
   */
  void resolveFilePatterToFiles(const std::string& actArg , std::list<std::string>& argList) ;
}

#endif