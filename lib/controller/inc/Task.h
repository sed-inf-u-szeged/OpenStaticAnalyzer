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

#ifndef _CONTROLLER_TASK_H_
#define _CONTROLLER_TASK_H_

#include <vector>
#include <string>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include "Properties.h"

#define DEFINETASK(taskname)                          \
class taskname : public columbus::controller::Task    \
{                                                     \
public:                                               \
  const static std::string name;                      \
  taskname (const Properties&);                       \
  virtual ExecutionResult execute();                  \
  virtual const std::string& getName() const {        \
    return name;                                      \
  }                                                   \
};

#define TASK_NAME_DEF(_NAME)  const string  _NAME::name(#_NAME)

#define HANDLE_TASK_EXCEPTIONS                                                \
  catch (const columbus::Exception& cex) {                                    \
    logstream << "EXCEPTION:" << cex.getLocation() << ":" << cex.getMessage() << "\n";  \
    result.setCriticalError();                                                \
  } catch (const std::exception& ex) {                                        \
    logstream << "EXCEPTION:" << ex.what() << "\n";                           \
    result.setCriticalError();                                                \
  } catch (...) {                                                             \
    logstream << "EXCEPTION: Unknown exception!\n";                           \
    result.setCriticalError();                                                \
  }

namespace columbus
{

namespace controller
{

class Task
{
public:
  class ExecutionResult {
    public:
      ExecutionResult() : warning(false), error(false), criticalError(false) { }

      void setError() {
        error = true;
      }

      void setCriticalError() {
        error = true;
        criticalError = true;
      }

      void setWarning(){
        warning = true;
      }

      bool hasError() const {
        return error;
      }

      bool hasCriticalError() const {
        return criticalError;
      }

      bool hasWarning() const {
        return warning;
      }

      std::string toString() const;
    private:
      bool warning;
      bool error;
      bool criticalError;
  };


public:
  Task(const BaseProperties& properties) : properties(properties) {}
  virtual ~Task() {}
  virtual ExecutionResult execute() = 0;
  void addDependsOn(const std::string& taskName);
  const std::vector<std::string>& getDependsOn() const;
  virtual const std::string& getName() const = 0;
  std::string getLog() const;

protected:

  class ExecutionLogger {
    public:
      ExecutionLogger(Task* task, ExecutionResult& result);
      ~ExecutionLogger();

      bool warningIfFail(bool conditon, const char* format, ...);
      bool errorIfFail(bool condition, const char* format, ...);
      void criticalErrorIfFail(bool condition, const char* format, ...);
    private:
      Task* task;
      ExecutionResult& result;
  };

  class SafeEnvironmentModifier {
    public:
      SafeEnvironmentModifier(const char* variable, const char* value, ExecutionLogger& logger, bool warningOnOverWrite = true);
      SafeEnvironmentModifier(const char* variable, const boost::filesystem::path& value, ExecutionLogger& logger, bool warningOnOverWrite = true);
      ~SafeEnvironmentModifier();
  private:
      void setVariable(const char* variable, const char* value, ExecutionLogger& logger, bool warningOnOverWrite);

      ExecutionLogger& logger;
      std::string oldValue;
      std::string variable;
      bool exists;
  };

  static void copyAllFiles(const boost::filesystem::path& source, const boost::filesystem::path& dest);
  static void copyBinaryExecutable(const boost::filesystem::path& source, const boost::filesystem::path& dest, const std::string& binaryName);
  static void copyDirectory(const boost::filesystem::path& source, const boost::filesystem::path& dest, const std::string& dirName);
  static int  exec (const boost::filesystem::path& program, const std::vector<std::string>& args, const boost::filesystem::path& log );
  static int  exec (const boost::filesystem::path& program, const std::vector<std::string>& args, std::stringstream& std_out_err);
  static void createDirectories(const boost::filesystem::path& dir, ExecutionLogger& logger);

  void checkedExec(const boost::filesystem::path& program, const std::vector<std::string>& args, ExecutionLogger& logger, bool critical = true);
  void addMessageLevel(std::vector<std::string>& args);
  void addMessageLevelNumber(std::vector<std::string>& args, unsigned verbose, unsigned normal);

  std::vector<std::string> dependsOn;
  std::stringstream logstream;
  const BaseProperties& properties;

  friend class ExecutionLogger;
};

} // namespace controller

} // namespace columbus


#endif
