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

#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <common/inc/WriteMessage.h>
#include <common/inc/messages.h>
#include "../inc/StringSup.h"


namespace common {

  WriteMsg::MsgLevel WriteMsg::msgLevel = WriteMsg::mlNormal;
  bool WriteMsg::writeOutWarningMessages = true;
  bool WriteMsg::wasWarning = false;
  FILE *WriteMsg::writeOutput = stdout;
  bool WriteMsg::canBeChanged = true;
  bool WriteMsg::needToFlush = false;
  bool WriteMsg::enableTimestamps = false;


  bool WriteMsg::setMessageLevel(MsgLevel newLevel)
  {
    if (!canBeChanged)
      return false;

    msgLevel = newLevel;
    return true;
  }

  void WriteMsg::enableWarningMessages()
  {
    writeOutWarningMessages = true;
  }

  void WriteMsg::disableWarningMessages()
  {
    writeOutWarningMessages = false;
  }

  void WriteMsg::writeToOut(MsgLevel level, const char* format, ...)
  {
    if (msgLevel == mlSilent || msgLevel < level)
      return;

    if (enableTimestamps)
      fprintf(stdout, "[%s] ", getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str());

    va_list al;
    va_start(al, format);
    vfprintf(stdout, format, al);
    va_end(al);
    if (needToFlush)
      fflush(stdout);
  }

  void WriteMsg::writeToFile(FILE *out, MsgLevel level, const char* format, ...)
  {
    if (msgLevel == mlSilent || msgLevel < level)
      return;

    if (enableTimestamps)
      fprintf(out, "[%s] ", getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str());

    va_list al;
    va_start(al, format);
    vfprintf(out, format, al);
    va_end(al);
    if (needToFlush)
      fflush(out);
  }

  void WriteMsg::writeToErr(MsgLevel level, const char* format, ...)
  {
    if (msgLevel == mlSilent || msgLevel < level)
      return;

    if (enableTimestamps)
      fprintf(stderr, "[%s] ", getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str());

    va_list al;
    va_start(al, format);
    vfprintf(stderr, format, al);
    va_end(al);
    if (needToFlush)
      fflush(stderr);
  }

  void WriteMsg::write(MsgLevel level, const char* format, ...)
  {
    if (level < WriteMsg::mlNormal)
      wasWarning = true;

    if (msgLevel == mlSilent || msgLevel < level)
      return;

    if (enableTimestamps)
      fprintf(writeOutput, "[%s] ", getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str());

    va_list al;
    va_start(al, format);
    vfprintf(writeOutput, format, al);
    va_end(al);
    if (needToFlush)
      fflush(writeOutput);
  }

  void WriteMsg::writeVaList(MsgLevel level, const char* format, va_list ap)
  {
    if ( level < WriteMsg::mlNormal)
      wasWarning = true;

    if (msgLevel == mlSilent || msgLevel < level)
      return;

    if (enableTimestamps)
      fprintf(writeOutput, "[%s] ", getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str());

    vfprintf(writeOutput, format, ap);
    if (needToFlush)
      fflush(writeOutput);
  }

  void WriteMsg::write(MsgLevel level, const std::string& message)
  {
    if ( level < WriteMsg::mlNormal) {
      wasWarning = true;
    }

    if (msgLevel == mlSilent || msgLevel < level)
      return;

    if (enableTimestamps)
      fprintf(writeOutput, "[%s] ", getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str());

    fprintf(writeOutput, "%s", message.c_str());
    if (needToFlush)
      fflush(writeOutput);
  }

  void WriteMsg::writeWarningMessage(const char* format, ...)
  {
    if (!writeOutWarningMessages)
      return;

    if (enableTimestamps)
      fprintf(writeOutput, "[%s] ", getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str());

    va_list al;
    va_start(al, format);
    vfprintf(writeOutput, format, al);
    va_end(al);
    if (needToFlush)
      fflush(writeOutput);
  }

  void WriteMsg::writeWarningMessage(FILE *out, const char* format, ...)
  {
    if (!writeOutWarningMessages)
      return;

    if (enableTimestamps)
      fprintf(out, "[%s] ", getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str());

    va_list al;
    va_start(al, format);
    vfprintf(out, format, al);
    va_end(al);
    if (needToFlush)
      fflush(out);
  }

  void WriteMsg::setMessageLevel(int argc, char* argv[])
  {
    // searching for "-silent"
    for (int i = 0; i < argc; i++)
      if (!strcmp(argv[i], "-silent")) {
        WriteMsg::msgLevel = WriteMsg::mlError;
        canBeChanged = false;
        return;
      }

    // searching for "-ml:NUM" or "-ml NUM" paramater
    for (int i = 0; i < argc; i++) {
      if (!strncmp(argv[i], "-ml", 3)) {
        if (!strncmp(argv[i], "-ml:", 4)) { // -ml:NUM
          setMessageLevel(argv[i]+4);
        } else if (strlen(argv[i]) == 3 && i + 1 < argc) { // -ml NUM
          setMessageLevel(argv[i+1]);
        }
        return;
      }
    }
  }

  void WriteMsg::setMessageLevel(const char* level)
  {
    if (!canBeChanged) {
      write(CMSG_NOT_TAKEN_INTO_ACCOUNT);
      return;
    }

    if (!strcmp(level, "0")) { // silent
      msgLevel = mlSilent;
      write(CMSG_DUINFO_ML_SILENT);
    } else if (!strcmp(level, "1")) { // error
      msgLevel = mlError;
      write(CMSG_DUINFO_ML_ERROR);
    } else if (!strcmp(level, "2")) { // warning
      msgLevel = mlWarning;
      write(CMSG_DUINFO_ML_WARNING);
    } else if (!strcmp(level, "3")) { // normal
      msgLevel = mlNormal;
      write(CMSG_DUINFO_ML_NORMAL);
    } else if (!strcmp(level, "4")) { // debug
      msgLevel = mlDebug;
      write(CMSG_DUINFO_ML_DEBUG);
    } else {
      msgLevel = (MsgLevel)atoi(level);
      write(CMSG_DUINFO_SET_ML,  msgLevel);
    }
  }

  WriteMsg::MsgLevel WriteMsg::getMessageLevel()
  {
    return msgLevel;
  }

  void WriteMsg::setAutomaticFlush(bool needToFlush)
  {
    WriteMsg::needToFlush = needToFlush;
  }

  void WriteMsg::setSetTimestampPrefixes(bool enable)
  {
    WriteMsg::enableTimestamps = enable;
  }
  
  bool WriteMsg::getWasWarning()
  {
    return wasWarning;
  }

  void WriteMsg::setOuputFile(FILE *file)
  {
    writeOutput = file;
  }
} // columbus
