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

#ifndef _COMMON_WRITEMESSAGE_H_
#define _COMMON_WRITEMESSAGE_H_

#include <string>
#include <cstdio>

namespace common {

  /**
  * \brief Class to write out every kind of messages.
  */
  class WriteMsg {
  public:

    /** \brief Possible levels of messages */
    enum MsgLevel {
      /** \brief Do not write out any message. */
      mlSilent,

      /** \brief Only error messages can be written out. */
      mlError,

      /** \brief Error and warning messages can be written out. */
      mlWarning,

      /** \brief All but debug message are written out. */
      mlNormal,

      /** \brief Besides the error, warning and normal messages the debug level 1 messages are also written out. */
      mlDebug,

      /** \brief Besides the error, warning and normal messages the debug level 2 messages are also written out. */
      mlDDebug,

      /** \brief Besides the error, warning and normal messages the debug level 3 messages are also written out. */
      mlDDDebug,

      /** \brief Besides the error, warning and normal messages the debug level 4 messages are also written out. */
      mlDDDDebug
    };

    /**
    * \brief Sets the message level.
    * \param newLevel [in] The new message level.
    *\return Returns true if the message level is set succesfully, otherwise returns false.
    */
    static bool setMessageLevel(MsgLevel newLevel);

    /**
    * \brief Warning messages can be written out.
    */
    static void enableWarningMessages();

    /**
    * \brief Disable writing out warning messages.
    */
    static void disableWarningMessages();

    /**
    * \brief Writes message to the standard output.
    * \param level  [in] The level of the message.
    * \param format [in] The message.
    */
    static void writeToOut(MsgLevel level, const char* format, ...);

    /**
    * \brief Writes message to file.
    * \param out    [in] The path of the destination file.
    * \param level  [in] The level of the message.
    * \param format [in] The message.
    */
    static void writeToFile(FILE *out, MsgLevel level, const char* format, ...);

    /**
    * \brief Writes message to the standard error.
    * \param level  [in] The level of the message.
    * \param format [in] The message.
    */
    static void writeToErr(MsgLevel level, const char* format, ...);

    /**
    * \brief Writes message to the given output (set by writeOutput varibale).
    * \param level  [in] The level of the message.
    * \param format [in] The message.
    */
    static void write(MsgLevel level, const char* format, ...);

    /**
    * \brief Writes message to the given output (set by writeOutput varibale).
    * \param level  [in] The level of the message.
    * \param format [in] The message.
    * \param ap     [in] The va_list.
    */
    static void writeVaList(MsgLevel level, const char* format, va_list ap);

    /**
    * \brief Writes message to the given output (set by writeOutput varibale).
    * \param level  [in] The level of the message.
    * \param message [in] The message.
    */
    static void write(MsgLevel level, const std::string& message);

    /**
    * \brief Writes out checker output (depends on enableWarningMessages instead of message level).
    * \param format [in] The message.
    */
    static void writeWarningMessage(const char* format, ...);

    /**
    * \brief Writes out checker output to file (depends on enableWarningMessages instead of message level).
    * \param out    [in] The destination file.
    * \param format [in] The message.
    */
    static void writeWarningMessage(FILE *out, const char* format, ...);

    /**
    * \brief Processes the parameters of main and sets the proper message level.
    * \param argc [in] The number of arguments.
    * \param argv [in] The arguments.
    */
    static void setMessageLevel(int argc, char* argv[]);

    /**
    * \brief Gives back the current message level.
    */
    static MsgLevel getMessageLevel();

    /**
    * \brief Controls the automatic fulshing. 
    * \param needToFlush [in] If it is true, than the automatic flush will be set. Otherwise it will be turned off. 
    */
    static void setAutomaticFlush(bool needToFlush);

    /**
    * \brief Give back the write functin has been get warring or error messges.
    */
    static bool getWasWarning();

    /**
     * \brief Changes the output of the messages. The default value is stdout.
     * \param file [in] The new outout file of the warning messages.
     */
     static void setOuputFile(FILE *file);
  private:

    /**
    * \brief Sets the message level.
    * \param level [in] The message level is char* form.
    */
    static void setMessageLevel(const char* level);

    /** \brief Influence which messages can be written out (default value is mlNormal). */
    static MsgLevel msgLevel;

    /** \brief If it is true, warning messages can be written out (default value is true). */
    static bool writeOutWarningMessages;

    /** \brief The write(MsgLevel, const char*, ...) function writes messages to this output (default value is stdout). */
    static FILE *writeOutput;

    /** \brief If it is true, message level cannot be changed. */
    static bool canBeChanged;
        
    /** \brief If it is true, than the messages will be flushed after every write. */
    static bool needToFlush;    

    /** \brief If it is true, The warning messages has been flashed. */
    static bool wasWarning;

  }; // writeMsg

} // common

#endif
