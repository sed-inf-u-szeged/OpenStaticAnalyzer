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
* Short description:                                                           *
*     This file contains the function declarations for string support.         *
*******************************************************************************/

#ifndef _STRINGSUP_H
#define _STRINGSUP_H

#include <string>
#include <vector>
#include <list>
#include <ctime>

#ifdef _WIN32
#define LowerStringOnWindows(str) stringLower(str)
#define LowerDriveLetterOnWindows(str) lowerDriveLetter(str)
#define UpperDriveLetterOnWindows(str) upperDriveLetter(str)
#else
#define LowerStringOnWindows(str)
#define LowerDriveLetterOnWindows(str)
#define UpperDriveLetterOnWindows(str)
#endif


/**
* \brief Namespace common.
*/
namespace common {

  /**
  * \brief Predicate for case insensitive string comparison.
  */
  struct case_insensitive_compare {
    bool operator()(const std::string& a, const std::string& b) const;
  };

  /**
  * \brief Converts string to integer.
  * \param str [in]  The string being converted.
  * \param num [out] The converted number if str is an integer number, undefined ortherwise.
  * \return          Returns true if it can be converted to integer.
  */
  bool str2int(const std::string& str, int& num);

  /**
  * \brief Converts string to integer.
  * \param str [in]  The string being converted.
  * \param num [out] The converted number if str is an integer number, undefined ortherwise.
  * \return          Returns true if it can be converted to integer.
  */
  bool str2int(const char* str, int& num);

  /**
  * \brief Converts string to integer.
  * \param str [in]  The string being converted.
  * \return The numeric form of the string.
  * \throw Exception If the string cannot be converted into number, columbus::Exception is thrown.
  */
  int str2int(const std::string& str);

  /**
   * \brief Converts string to unsigned.
   * \param str [in]  The string being converted.
   * \return The numeric form of the string.
   * \throw Exception If the string cannot be converted into number, columbus::Exception is thrown.
   */
  unsigned str2unsigned(const std::string& str);

  /**
  * \brief Converts string to unsigned long.
  * \param str [in]  The string being converted.
  * \param num [out] The converted number if str is an unsigned long number, undefined ortherwise.
  * \return          Returns true if it can be converted to unsigned long.
  */
  bool str2unsignedlong(const std::string& str, unsigned long& num);

  /**
  * \brief Converts string to double.
  * \param str [in]  The string being converted.
  * \param num [out] The converted number if str is a double number, undefined ortherwise.
  * \return          Returns true if it can be converted to double.
  */
  bool str2double(const std::string& str, double& num);

  /**
  * \brief Converts string to lower case.
  * \param str [in, out] String which is converted.
  * \return              The converted string.
  */
  char* stringLower(char* str);
    
  /**
  * \brief Converts string to lower case.
  * \param str [in, out] String which is converted.
  */
  std::string stringLower(std::string& str);

  /**
  * \brief Converts string to lower case.
  * \param str [in, out] String which is converted.
  */
  std::wstring string2Wstr(const std::string& str);

  /**
  * \brief Converts string to lower case.
  * \param str [in, out] String which is converted.
  */
  std::string wstring2str(const std::wstring& str);

  /**
  * \brief Converts string to lower case.
  * \param str [in] String which is converted.
  * \return              The converted string.
  */
  const std::string stringLower(const std::string& str);

  std::string removeNewline(const std::string& str);

  bool isQuoted(const std::string& source);

  /**
  * \brief Converts string to upper case.
  * \param str [in] String which is converted.
  * \return         The converted string.
  */
  const std::string stringUpper(const std::string& str);

  /**
  * \brief Compares two strings case insensitively.
  * \param str1 [in] First string.
  * \param str2 [in] Second string.
  * \return          True, if the two string is case insensitively equal.
  */
  bool caseInsensitiveComp(const std::string& str1, const std::string& str2);

  /**
  * \brief Compares two strings case insensitively.
  * \param str1 [in] First string.
  * \param str2 [in] Second string.
  * \return          True, if the two string is case insensitively equal.
  */
  bool caseInsensitiveComp(const char* str1, const char* str2);

  /**
  * \brief Splits a command line taking the quoutes into consideration as well.
  * \param str1 [in] command line
  * \param out  [out] Vector of the arguments
  */
  void splitArgs(const char* str1, std::vector<std::string>& out);

  /**
  * \brief Articulates the number (e.g. it makes 123.456.789 from 123456789).
  * \param num [in] The number.
  * \return Returns with the articulated number.
  */
  std::string articulateNumber(long num);

  /**
  * \brief Splits the string by the separator character and puts the elements into strList vector.
  * \param str       [in]      The string which is split.
  * \param strList   [in, out] Vector which contains the parts of the string.
  * \param separator [in]      The separator character.
  */
  void split(const std::string& str, std::vector<std::string>& strList, char separator);

  /**
  * \brief Splits the string by the separator character and puts the first maxSplits elements into strList vector.
  * \param str       [in]      The string which is split.
  * \param strList   [in, out] Vector which contains the parts of the string.
  * \param separator [in]      The separator character.
  * \param maxSplits [in]      Maximum the first maxSplits number of elements are split from the input string.
  */
  void split(const std::string& str, std::vector<std::string>& strList, char separator, unsigned int maxSplits);

  /**
  * \brief Splits the string by the separator character and puts the first maxSplits elements into strList vector.
  * \param str       [in]      The string which is split.
  * \param strList   [in, out] Vector which contains the parts of the string.
  * \param separator [in]      The separator character.
  * \param maxSplits [in]      Maximum the first maxSplits number of elements are split from the input string (if endless is false.
  * \param endless   [in]      if endless is true the limit is not taken into account.
  */
  void split(const std::string& str, std::vector<std::string>& strList, char separator, unsigned int maxSplits, bool endless);

  /**
  * \brief Splits the string by the separator character and puts the first maxSplits elements into strList list.
  * \param str       [in]      The string which is split.
  * \param strList   [in, out] List which contains the parts of the string.
  * \param separator [in]      The separator character.
  */
  void split(const std::string& str, std::list<std::string>& strlist, char separator);

  /**
  * \brief Removes the first and the last character of a string if it is '"' or '`'.
  * \param s              [in] Input string.
  * \return               Returns the modified string from that the first and last character is removed if it is '"' or '`'.
  */
  std::string removeQuotes(const std::string& s);

  /**
  * \brief Tries to find the given 'filename' file in the directories set in the PATH.
  * \param str              [in] The string in which the 'from' will be replaced with 'to'.
  * \param from             [in] The string being searched for.
  * \param to               [in] The replacement string.
  * \return                 Returns a string which contains the 'str' but every occurrence of 'from' is replaced with 'to'.
  */
  std::string replace(const char *str, const char *from, const char *to);

  /**
  * \brief Transform the given Java unique name to jni form. 
  * \param name [inout] The string need to be fixed.
  */
  void convertJavaUniqueNameToJniName(std::string& name);

  /**
  * \brief Converts long to string.
  * \param value [in] The long long which will be converted.
  * \return           The converted long long (in string form).
  */
  const std::string toString(const long value);

  /**
  * \brief Converts unsigned long to string.
  * \param value [in] The long long which will be converted.
  * \return           The converted long long (in string form).
  */
  const std::string toString(const unsigned long value);

  /**
  * \brief Converts long long to string.
  * \param value [in] The long long which will be converted.
  * \return           The converted long long (in string form).
  */
  const std::string toString(const long long value);

  /**
  * \brief Converts int to string.
  * \param value [in] The integer which will be converted.
  * \return           The converted integer (in string form).
  */
  const std::string toString(const int value);

  /**
  * \brief Converts short to string.
  * \param value [in] The short which will be converted.
  * \return           The converted short (in string form).
  */
  const std::string toString(const short value);

  /**
  * \brief Converts unsigned long long integer to string.
  * \param value [in] The unsigned long long integer which will be converted.
  * \return           The converted unsigned long long integer (in string form).
  */
  const std::string toString(const unsigned long long value);
  /**
  * \brief Converts unsigned integer to string.
  * \param value [in] The unsigned integer which will be converted.
  * \return           The converted unsigned integer (in string form).
  */
  const std::string toString(const unsigned value);
  /**
  * \brief Converts unsigned short integer to string.
  * \param value [in] The unsigned short integer which will be converted.
  * \return           The converted unsigned short integer (in string form).
  */
  const std::string toString(const unsigned short value);

  /**
  * \brief Converts double to string.
  * \param value [in] The double which will be converted.
  * \return           The converted double (in string form).
  */
  const std::string toString(double value);

  /**
  * \brief Converts float to string.
  * \param value [in] The float which will be converted.
  * \return           The converted float (in string form).
  */
  const std::string toString(const float value);

  /**
  * \brief Converts character to string.
  * \param value [in] The char which will be converted.
  * \return           The converted character (in string form).
  */
  const std::string toString(const char value);

  /**
  * \brief Converts boolean to string.
  * \param value [in] The boolean which will be converted.
  * \return           The converted boolean (in string form).
  */
  const std::string toString(const bool value);

  /**
   * \brief Removes the white charaters before and after the given string.
   * \param string        [in/out] The string, which will be trimmed.
   * \param whitespaces   [in]     The whitespaces, which will be removed.
   */
  void trim(std::string& string, const char* whitespaces = " \t\r\n");

  /**
   * \brief Removes the white charaters before and after the given string.
   * \param string        [in/out] The string, which needs to be trimmed.
   * \param whitespaces   [in]     The whitespaces, which will be removed.
   * \return                       The trimmed string
   */
  std::string trim(const std::string& string, const char* whitespaces = " \t\r\n");
   
  void writeMessage(const char* msg);
   
  /**
   * \brief Change path from somthing to somthing else
   * \param path      [in/out] The string, which needs to be replaced.
   * \param from      [in]     from path.
   * \param to        [in]     to path.
   * \return                   True if there was at least one replace
   */
  bool changePath(std::string& path, const std::string& from, const std::string& to);

  /**
  * \brief Converts the drive letter in the given path string to lower case.
  * \param path [in/out] The path.
  */
  void lowerDriveLetter(std::string& path);

  /**
  * \brief Converts the drive letter in the given path string to upper case.
  * \param path [in/out] The path.
  */
  void upperDriveLetter(std::string& path);

  /**
   * \brief Gives back the current time and date.
   * \return            The tm structure filled with the current time and date.
   */
  std::tm getCurrentTimeAndDate();

  /**
   * \brief Gives back the current time and date in the given format.The length of the formatted string is maximum 200 character.
   * \param format [in] Formatter string. (Described in the manual of the strftime function.)
   * \return            The preformatted date and time.
   */
  std::string getCurrentTimeAndDate(const char* format);

  /**
   * \brief Gives back the time and date stored in the `td` parameter in the given format .The length of the formatted string is maximum 200 character.
   * \param format [in] Formatter string. (Described in the manual of the strftime function.)
   * \param td     [in] The time and date to be formatted.
   * \return            The preformatted date and time.
   */
  std::string getCurrentTimeAndDate(const char* format, const std::tm& td);


  /**
   * \brief Returns whether the name is a "getter", i.e. it must be
   *   - be at least 4 characters long
   *   - start with the substring "get"
   *   - have an underscore or an uppercase letter on the fourth position
   * \param name [in] the name of the method
   * \return true if it is a getter
   */
  bool isGetter( const std::string& name );

  /**
   * \brief Returns whether the name is a "setter", i.e. it must be
   *   - be at least 4 characters long
   *   - start with the substring "set"
   *   - have an underscore or an uppercase letter on the fourth position
   * \param name [in] the name of the method
   * \return true if it is a setter
   */
  bool isSetter( const std::string& name );
  
} // namespace common

#endif
