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

/*******************************************************************************
* File: FileSup.h                                                              *
*    (part of the 'common' library)                                            *
*                                                                              *
* Created by  : Arpad Beszedes  16.02.2000.                                    *
*                                                                              *
* Short description:                                                           *
*     This file contains the function declarations for file support.           *
*******************************************************************************/

#ifndef _FILESUP_H
#define _FILESUP_H

#include <string>
#include <list>
#include <vector>

namespace common
{

  /**
  * \brief Splits the given path string into a directory part and a file part.
  * \param path    [in] The path string to be split.
  * \param dir     [out] The directory part of the input path.
  * \param file    [out] The file part of the input path.
  * \return        Returns the length of 'dir' (the position where the input path was split).
  */
  size_t splitPath(const std::string& path, std::string& dir, std::string& file);

  /**
  * \brief Replaces multiple directory separators with one.
  * \param str     [in] The string int that the duplivated directory separators to be replaced.
  * \param win     [in] If true then skips network name (skips the fist two characters if they are '\').
  * \return        Returns true if a result has been computed. Returns false otherwise.
  */
  std::string removeDoubleDirdivs(const std::string& str, bool win = true);

  /**
  * \brief Removes elements of a file path according to special strings inserted into that path.
  * \param dst     [out] The string that receives the canonicalized path.
  * \param src     [in] The string that contains the path to be canonicalized.
  * \return        Returns true if a result has been computed. Returns false otherwise.
  */
  bool pathCanonicalize(std::string& dst, const std::string& src);

  /**
  * \brief Creates directory resursively.
  * \param dirName [in] The path of the new directory.
  * \return        If there is no error, it returns with 0, otherwise returns with the error code.
  */
  bool makeDirectory(const std::string& dirName);

  /**
  * \brief Gives the canonicalized absolute path for the given path string.
  * \param dirName [in] The input path that can be relative (also can be home relative (~) under UNIX).
  * \return Returns the canonicalized absolute path.
  */
  std::string indep_fullpath(const std::string& path);

  /**
  * \brief It returns the directory of the runing program. It does not use argv0_ variable so that
  * it is not necessary to set it in the main function!
  */
  std::string getExecutableProgramDir();

  /**
  * \brief It returns the home path.
  */
  std::string getHomePath();

  /**
  * \brief Retrieves an integer associated with a key in the specified section of an initialization file.
  * \param appnam           [in] The name of the section containing the key name. If this parameter is NULL, the getPrivateProfileString function copies all section names in the file to the supplied buffer.
  * \param keyname          [in] The name of the key whose value is to be retrieved. This value is in the form of a string; the getPrivateProfileInt function converts the string into an integer and returns the integer.
  * \param def              [out] The default value to return if the key name cannot be found in the initialization file.
  * \param size             [in] The name of the initialization file.
  * \param casesensitive    [in] Whether needed casesensitive comparation at appname or not.
  * \return                 The return value is the integer equivalent of the string following the specified key name in the specified initialization file. If the key is not found, the return value is the specified default value. 
  */
  unsigned int getPrivateProfileInt(const char* appname, const char* keyname, unsigned int def, const char* filename, bool casesensitive = false);

  /**
  * \brief Retrieves a string from the specified section in an initialization file.
  * \param appnam           [in] The name of the section containing the key name. If this parameter is NULL, the getPrivateProfileString function copies all section names in the file to the supplied buffer.
  * \param keyname          [in] The name of the key whose associated string is to be retrieved. If this parameter is NULL, all key names in the section specified by the 'appname' parameter are copied to the buffer specified by the 'ret_string' parameter.
  * \param def              [out] A default string. If the 'keyname' key cannot be found in the initialization file, getPrivateProfileString copies the default string to the 'ret_string' buffer. If this parameter is NULL, the default is an empty string, "".
  * \param ret_string       [out] A pointer to the buffer that receives the retrieved string.
  * \param size             [in] The size of the buffer pointed to by the ret_string parameter, in characters.
  * \param filename         [in] The name of the initialization file.
  * \param casesensitive    [in] Whether needed casesensitive comparation at appname or not.
  * \return                 The return value is the number of characters copied to the buffer, not including the terminating null character.
  */
  size_t getPrivateProfileString(const char* appname, const char* keyname, const char* def, char* ret_string, size_t size, const char* filename, bool casesensitive = false);

  /**
  * \brief Retrieves all the keys and values for the specified section of an initialization file.
  * \param appnam           [in] The name of the section in the initialization file.
  * \param ret_string       [out] A pointer to a buffer that receives the key name and value pairs associated with the named section. The buffer is filled with one or more null-terminated strings; the last string is followed by a second null character.
  * \param size             [in] The size of the buffer pointed to by the 'ret_string' parameter, in characters.
  * \param filename         [in] The name of the initialization file.
  * \return                 The return value specifies the number of characters copied to the buffer, not including the terminating null character. If the buffer is not large enough to contain all the key name and value pairs associated with the named section, the return value is equal to parameter 'size' minus two.
  */
  size_t getPrivateProfileSection(const char* appname, char* ret_string, size_t size, const char* filename);

  /**
  * \brief Retrieves all the keys and values for the specified section of an initialization file.
  * \param appnam           [in] The name of the section to which the string will be copied. If the section does not exist, it is created. The name of the section is case-independent; the string can be any combination of uppercase and lowercase letters.
  * \param keyname          [in] The name of the key to be associated with a string. If the key does not exist in the specified section, it is created.
  * \param str              [in] A null-terminated string to be written to the file.
  * \param filename         [in] The name of the initialization file.
  * \param casesensitive    [in] Whether needed casesensitive comparation at appname or not.
  * \return                 If the function successfully copies the string to the initialization file, the return value is nonzero.
  */
  unsigned int writePrivateProfileString(const char* appname, const char* keyname, const char* str, const char* filename, bool casesensitive = false);

  /**
  * \brief Copies the content of a zero-terminated string list to an std list. After the last string there must be an extra zero to mark the list end.
  * \param input_list       [in] The list, which contains the zero terminated strings.
  * \param output_list      [out] The list<string> in which the strings are copied.
  * \return                 The number of the copied strings.
  */
   unsigned int convertZeroTerminatedStringList(const char *input_list, std::list<std::string>& output_list);

  /**
  * \brief Gets the directory part of the given path (NOTE: returns with the input parameter 'path' if it is a filename only).
  * \param path             [in] The input path string.
  * \return                 Returns the directory part of the given path (NOTE: returns with the input parameter 'path' if it is a filename only).
  */
  std::string pathRemoveFileSpec(const std::string& path);

  /**
  * \brief Gets the file part of the given path.
  * \param path             [in] The input path string.
  * \return                 Returns the file part of the given path.
  */
  std::string pathFindFileName(const std::string& path);

  /**
  * \brief Gets the extension of the given file path.
  * \param path             [in] The input path string.
  * \return                 Returns the part of the given 'path' that follows the last '.' character. (NOTE: it may gives wrong result in case of there is no extension, but the filename contains '.' character (e.g. with the input "/usr/bin/gcc-4.3" under linux returns with "3"))
  */
  std::string pathFindExtension(const std::string& path);

  /**
  * \brief Removes the extension from the given file path.
  * \param path             [in] The input path string.
  * \return                 Returns the part of the given 'path' that is before the last '.' character. (NOTE: it may gives wrong result in case of there is no extension, but the filename contains '.' character (e.g. with the input "/usr/bin/gcc-4.3" under linux returns with "/usr/bin/gcc-4"))
  */
  std::string pathRemoveExtension(const std::string& path);

  /**
  * \brief Removes all extensions from the given file path.
  * \param path             [in] The input path string.
  * \return                 Returns the part of the given 'path' that is before the '.' character that is the fist '.' after the last path separator character. (NOTE: it may gives wrong result in case of there is no extension, but the filename contains '.' character (e.g. with the input "/usr/bin/gcc-4.3" under linux returns with "/usr/bin/gcc-4"))
  */
  std::string pathRemoveAllExtensions(const std::string& path);

  /**
  * \brief Removes all extensions from the given file path.
  * \param path             [in] The input path string.
  * \param extension        [in] The extension to be added.
  * \return                 Returns the concatenation of the 'path' and 'extension'.
  */
  bool pathAddExtension(std::string& path, const std::string& extension);

  /**
  * \brief Splits the given file into filename and ext (if it has).
  * \param file           [in] The input file name.
  * \param filename       [out] The file name without extension.
  * \param ext            [out] The file extension.
  * \return                     True if there is an extension at the end of the file.
  */
  bool splitExt(const std::string& file, std::string& filename, std::string& ext);

  /**
  * \brief Checks whether the given string is an existing file (or directory).
  * \param path             [in] The checked path.
  * \param dirAllowed       [in] Tells that directories take part of checking.
  * \return                 Returns true if the given file (or directory in case the dirAllowed is true) exists.
  */
  bool pathFileExists(const std::string& path, bool dirAllowed = true);

  /**
  * \brief Checks whether the given string is an absolute path.
  * \param path             [in] The checked path.
  * \return                 Returns true if the given path is absolute.
  */
  bool pathIsAbsolute(const std::string& path);

  /**
  * \brief Checks whether the given string is a relative path.
  * \param path             [in] The checked path.
  * \return                 Returns true if the given path is relative.
  */
  bool pathIsRelative(const std::string& path);

  /**
  * \brief Gets the current working directory.
  * \return                 Returns the current working directory.
  */
  std::string getCwd();

  /**
  * \brief Changes the current working directory.
  * \param path             [in] Path of new working directory.
  * \return                 Returns a value of 0 if successful. A return value of -1 indicates that the specified path could not be found.
  */
  int chDir(const std::string& dirname);

  /**
  * \brief Replaces the path separator characters to the platform dependent separator character (/ under UNIX, \ under Windows).
  * \param path             [in] The input path string.
  * \return                 Returns the modified path in that all path separators fit to the operating system.
  */
  std::string correctDirDivs(std::string path);

  /**
  * \brief Compares the given files' last modification time.
  * \param first            [in] The first input path string.
  * \param second           [in] The second input path string.
  * \return                 Returns -2 if file 'first' does not exist. Returns -3 if file 'second' does not exist. Returns -1 if the file second's last modification time is later than seconds', +1 if the first was modificated later than the second. Returns 0 if the two modification times are equivalent.
  */
  int fileTimeCmp(const std::string& first, const std::string& second);  // -1: first < second; 0: first==second; 1: first > second

  /**
  * \brief Deletes the given path.
  * \param path             [in] The input path string.
  * \return                 Returns true if the deletion successful, false otherwise.
  */
  bool pathDeleteFile(const std::string& path);

  /**
  * \brief Checks whether the given string is a valid directory.
  * \param name             [in] The checked path.
  * \return                 Returns true if the given string is a valid directory.
  */
  bool pathIsDirectory (const std::string& path); 

  /**
  * \brief Executes the given command and redirects the output streams into the given files.
  * \param cmd              [in] The command to be executed.
  * \param silent           [in] If true then the output and error messages of the created process won't be written out.
  * \param out              [in] The file name where the output messages are written to.
  * \param err              [in] The file name where the error messages are written to.
  * \return                 Returns 0 if the process executed successfully. Otherwise returns with an (operating system dependent) error code.
  */
  int run(const std::string& cmd, bool silent = false, const std::string& out = "", const std::string& err = "");

  /**
  * \brief Executes the given program with the given arguments and redirects the output streams into the given files.
  * \param program          [in] The program to be executed.
  * \param args             [in] Arguments of the program.
  * \param out              [in] The file name where the output messages are written to.
  * \param err              [in] The file name where the error messages are written to.
  * \return                 Returns 0 if the process executed successfully. Otherwise returns with an (operating system dependent) error code.
  */
  int run(const std::string& program, const std::vector<std::string>& args, const std::string& out = std::string(), const std::string& err = std::string());

  /**
  * \brief Executes the given program with the given arguments and redirects the output streams into the given outputstream.
  * \param program          [in] The program to be executed.
  * \param args             [in] Arguments of the program.
  * \param out              [out] The output stream into which the standard output and standard error is printed.
  * \return                 Returns 0 if the process executed successfully. Otherwise returns with an (operating system dependent) error code.
  */
  int run(const std::string& program, const std::vector<std::string>& args, std::ostream& out);

  /**
  * \brief Tries to find the given 'filename' file in the directories set in the PATH.
  * \param filename         [in] The name of the file searching for.
  * \param skip             [in] The 'skip' directory is skipped form the searching.
  * \return                 Returns the name of the file found or an empty string.
  */
  std::string findFile(const char *filename, const char *skip);

  /**
  * \brief It uses setenv on Linux and _putenv_s on Windows to set environmental variable instead of putenv.
  * \param envname          [in] The name of the environmental variable.
  * \param envval           [in] The value of the environmental variable.
  * \return                      Returns 0 if it was successful.
  */
  int setEnvironmentVariable(const char* envname, const char* envval);

  /**
  * \brief It uses unsetenv on Linux and _putenv_s on Windows to unset/remove environmental variable instead of putenv.
  * \param envname          [in] The name of the environmental variable.
  * \return                      Returns 0 if it was successful.
  */
  int unsetEnvironmentVariable(const char* envname);

  /**
  * \brief Gets the environmental variables.
  * \param variables        [out] It contains the environmental variables.
  */
  void getEnvironmentVariables(std::vector<std::string>& variables);

  /**
  * \brief Array containing the valid 'c' file extensions.
  */
  extern const char * cextensions[];

  /**
  * \brief Array containing the valid 'c++' file extensions.
  */
  extern const char * cppextensions[];

  /**
  * \brief Array containing the predefined macro names.
  */
  extern const char * macronames[];

  /**
  * \brief Checks whether the given extension is a valid 'c' file extension.
  * \param ext           [in] The extension to be checked.
  * \return              Returns true if the given extension is a valid 'c' file extension.
  */
  bool isclang(const std::string& ext);

  /**
  * \brief Checks whether the given extension is a valid 'c++' file extension.
  * \param ext           [in] The extension to be checked.
  * \return              Returns true if the given extension is a valid 'c++' file extension.
  */
  bool iscpplang(const std::string& ext);

  /**
  * \brief Checks whether the given name is a predefined macro name.
  * \param name          [in] The name to be checked.
  * \return              Returns true if the given name is a predefined macro name.
  */
  bool isPredefinedMacroName(const std::string& name);

  /**
  * \brief Checks whether a given string is a prefix of another string. Returns true if 'test' is a prefix of 'str'. 'remain' is set to the remaining part of the 'str'. ( where str = ppprrrrrr, prefix = ppp, remain = rrrrr) If 'skipeq' is true than if the 'remain' first character is '=' than the remain won't contain it.
  * \param str              [in] The input string that may contains the searched prefix.
  * \param test             [in] The string that will tested whether it is a prefix of the input string 'str'.
  * \param remain           [out] The output that is the remaining string when the 'test' is removed from the front of the input string. If the remain's frist character is '=' and the parameter 'skipeq' is true than the remain won't contain the '=' character.
  * \param skipeq           [in] If true than if the 'remain' first character is '=' than the remain won't contain it
  * \return                 Returns the list of the input files sorted by descending by size. If the 'skipFirst' parameter is true than the first item does not take part of the sorting, it remains the first in the output list.
  */
  bool isPrefix(const std::string& str, const std::string& test, std::string& remain, bool skipeq = false);

  /**
  * \brief Sorts the list of filenames by the sizes of the files (except the first one if the 'skipFirst' is true).
  * \param fileList         [in-out] The filename list. It contains the input list, and contains the sorted filelist at the end of the function.
  * \param skipFirst        [in] If true than the first item of the input file list remains the first in the output list.
  * \return                 Returns the list of the input files sorted by descending by size. If the 'skipFirst' parameter is true than the first item does not take part of the sorting, it remains the first in the output list.
  */
  void sortBySizeDescending(std::list<std::string>& fileList, bool skipFirst);

  /**
  * \brief Give back a new filename by replacing the extension of the given filename with the given extension. 
  *        If the given filename does not have extension, then the new_extetension will be added to the filename.
  * \param filename         [in] The name of the original file.
  * \param new_extension    [in] The name of the new extension.
  * \return                 Returns the modified filename with the new extension.
  */
  std::string replaceExtension(const std::string& filename, const std::string& new_extension);

  /**
  * \brief Replace the extension of the given filename with the given extension. If the given filename does not have extension, 
  *        then the new_extetension will be added to the filename. 
  * \param filename         [in] The name of the original file.
  * \param new_extension    [in-out] The name of the new extension.
  */
  void replaceExtensionInPlace(std::string& filename, const std::string& new_extension);

  /**
  * \brief Loads the given filter file.
  * \param filename         [in] The name of the filter file.
  * \param fltpPaths        [out] Include paths.
  * \param fltpExcludePaths [out] Exclude paths.
  * \param pathLower        [in] If it is true the paths will be converted to lower case.
  * \return                 Returns true if the file was loaded successfully.
  */
  bool loadFltpFile(const std::string& filename, std::vector<std::string>& fltpPaths, std::vector<std::string>& fltpExcludePaths, bool pathLower = false);

  /**
   * \brief Processes the file.
   *
   * \param listFileName the file name which contain the list 
   * \param fileNameList the output list which will be filled
   * \return             Returns true if the file was loaded successfully.
   */
  bool loadStringListFromFile(const std::string& listFileName, std::list<std::string>& fileNameList);
  
  /**
   * \brief Gives back the name of the lock file for the given file.
   *
   * \param fileName     the name of the file
   * \return             Returns the name of the lock file.
   */
  std::string getLockFileName(const std::string& fileName);

} // namespace common

#endif /* _FILESUP_H */
