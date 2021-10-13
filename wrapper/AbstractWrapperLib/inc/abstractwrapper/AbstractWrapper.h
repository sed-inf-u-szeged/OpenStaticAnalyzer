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

#ifndef __ABSTRACT_WRAPPER_H
#define __ABSTRACT_WRAPPER_H

#include <string>
#include <list>
#include <set>
#include <vector>

namespace ColumbusWrappers {
  class AbstractWrapper {

  public:
    /**
     * @brief Enum for different wrapper modes: gcc, cl, lib, ar or unknown.
     */
    enum WrapperModes {
      wrapper_gcc,
      wrapper_cl,
      wrapper_clang,
      wrapper_lib,
      wrapper_ar,
      wrapper_armcc,
      wrapper_unknown
    };

  protected:
    WrapperModes mode;              ///< variable for actual wrapper mode

  public:
    /**
     * @brief Constructor for AbstractWrapper class. Reads config file, reads environmental variables, sets message level.
     * @param configfile         [in] The name of the config file.
     */
    AbstractWrapper(std::string configfile);

    /**
     * @brief Destructor for AbstractWrapper class.
     */
    virtual ~AbstractWrapper();

    /**
     * @brief Pure virtual method process which processes argumentlist.
     * @param argc         [in] Number of arguments.
     * @param argv         [in] Array of arguments.
     * @return                  True if no problem with processing.
     */
    virtual bool process(int argc, char** argv) = 0;

  protected:
    /**
     * @brief Reads options from config file.
     */
    void readConfig();

    /**
     * @brief Reads environmental variables.
     */
    void getEnvVars();

    /**
     * @brief Wraps common::getPrivateProfileInt()
     */
    int getConfigInt(const char* section, const char* key, int def);

    /**
     * @brief Wraps common::getPrivateProfileString()
     */
    std::string getConfigString(const char* section, const char* key, const char* def);

    /**
     * @brief Collects arguments and their number of parameters from the configuration which are need to be skipped.
     * @param section             [in] Section name in config file.
     * @param numofparamtoskip    [in] Number of the arguments which are need to be skipped.
     * @param paramSet            [out] The arguments and their number of parameters are put into this set.
     */
    void getParamToSkip(const char* section, int numofparamtoskip, std::set<std::pair<std::string, int> >& paramSet);

    /**
     * @brief Collects extra parameters for wrapper tools.
     * @param section             [in] Section name in config file.
     * @param numofextraparam     [in] Number of the extra parameters.
     * @param paramVector         [out] The extra parameters are put into this vector.
     */
    void getExtraParam(const char* section, int numofextraparam, std::vector<std::string>& paramVector);

    /**
     * @brief Wraps insertDir(std::string& file, const std::string& dirname, bool createDir)
     */
    void insertDir(std::string& file, bool createDir) const;

    /**
     * @brief Adds given directory to path. Creates if it is necessary.
     * @param file           [in out] The given path.
     * @param dirname        [in] The given directory.
     * @param createDir      [in] If it is true it is necessary to creates directory.
     */
    void insertDir(std::string& file, const std::string& dirname, bool createDir) const;

    /**
     * @brief Replaces ' for '\'' and and " for \" in the given parameter.
     * @param param          [in out] The given parameter.
     */
    void replaceQuoteForQuoteWithBackslash(std::string& param) const;

    /**
     * @brief Calls replaceQuoteToQuoteWithBackslash for each member of given list.
     * @param paramlist      [in out] The given parameter list.
     */
    void corrigateParamList(std::list<std::string>& paramlist) const;

    /**
     * @brief Collects arguments into a string list from command line and command file.
     * @param argc           [in] Number of input arguments.
     * @param argv           [in] The input argument list.
     * @param paramlist      [out] String list for command line and command file arguments.
     * @param paramtoskip    [in] Arguments and their number of parameters to skip.
     */
    void setParams(int argc, char** argv, std::list<std::string>& paramlist, std::set<std::pair<std::string, int> > paramtoskip);

    /**
     * @brief If the string is between quotation marks or single quotes this function removes them and returns the string without these marks.
     * @param s          [in] Input string.
     * @return                The string without quotation marks.
     */
    std::string checkedRemoveQuotes(const std::string& s);

    /**
     * @brief Checks whether the given parameter has to be skipped or not.
     * @param param          [in] The given parameter.
     * @param paramtoskip    [in] Arguments and their number of parameters to skip.
     * @param skip           [out] The number of params of the given parameter = the number of the skipped parameters.
     * @return                    True, if the parameter need to skip is found.
     */
    bool checkSkipParam(std::string& param, std::set<std::pair<std::string, int> > paramtoskip, int& skip);

    /**
     * @brief Determines whether the given parameter is a command file or not.
     * @param param          [in] The given parameter.
     * @return                    True if the given parameter is a command file.
     */
    bool isCommandFile(std::string& param);

    /**
     * @brief Processes command file and puts the arguments into a list.
     * @param param          [in] The name of the given command file
     */
    void processCommandFile(std::string& param);

    /**
     * @brief Wraps common::run function.
     * @param cmd            [in] Command string.
     * @param filename       [in] Name of the given log file.
     * @return                    The exit code.
     */
    int systemCall (const std::string& cmd, const std::string& filename="") const ;

    /**
     * @brief Wraps common::run function.
     * @param executable     [in] Executable to be invoked.
     * @param arguments      [in] Arguments of the executable.
     * @param filename       [in] Name of the given log file.
     * @return                    The exit code.
     */
    int systemCall (const std::string& executable, const std::vector<std::string>& arguments, const std::string& filename="") const ;

    /**
     * @brief Wraps common::run function without any logging.
     */
    int  silentSystemCall (const std::string& cmd) const; 

    /**
     * @brief Determines whether the given file is an object file or not.
     * @param name           [in] The given file name.
     * @return                    True if it's an object file.
     */
    bool isObjectFile(std::string& name) const;

    /**
     * @brief Determines whether the given file is an archive file or not.
     * @param name           [in] The given file name.
     * @return                    True if it's an archive file.
     */
    bool isArchiveFile(std::string& name) const;

    /**
     * @brief Returns the object file extension.
     * @return                    The object file extension (.o or .obj)
     */
    std::string getObjectFileExtension() const;


    /**
     * @breif Returns the ID of current process.
     * @return                    The ID of the current process.
     */
    int getCurrentProcessId() const;

    std::string configfile;                           ///< The name of the config file

    std::vector<std::string> input_paramvector;       ///< String vector for input parameters.

    std::string wrapper_work_dir;                     ///< Path of the wrapper working directory
    std::string wrapper_bin_dir;                      ///< Path of the wrapper bin directory
    std::string wrapper_log_dir;                      ///< Path of the wrapper log directory
    std::string wrapper_temp_dir;                     ///< Path of the wrapper temp directory

    std::string outputdir;                            ///< The name of the directory where the .csi, .acsi, .lcsi files are found (.columbus).
    std::string configdir;                            ///< The name of the directory where the CAN find its config files.
    int messagelevel;                                 ///< The message level (default 3).

    std::string wrappedExe;                           ///< The name of the wrapped program.

    int instrument_enable;                            ///< instrument is enabled or not
    int prep_instrument;                              ///< prepare for instrument: it means that the CAN analyzes preprocessed files, so we have to preprocess these files before CAN calling
  };
}

#endif
