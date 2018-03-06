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

#include "../inc/Task.h"
#include "../inc/messages.h"
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <boost/filesystem.hpp>
#include <cstdarg>
#include <Exception.h>

using namespace common;
using namespace boost::filesystem;
using namespace std;

namespace columbus
{

namespace controller
{

void Task::addMessageLevel(std::vector<std::string>& args) {
  if (properties.verbose) {
    args.push_back("-ml:4");
  }
}

void Task::addMessageLevelNumber(std::vector<std::string>& args, unsigned verbose, unsigned normal) {
  if (properties.verbose) {
    args.push_back(common::toString(verbose));
  } else {
    args.push_back(common::toString(normal));
  }
}


int Task::exec(const boost::filesystem::path& program, const std::vector<std::string>& args, std::ostream& std_out_err) {
  if (WriteMsg::getMessageLevel() >= WriteMsg::mlDebug) {
    std_out_err << "[" << common::getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S") << "]";
    std_out_err << current_path().string() << "> " << program.string();
    for (std::vector<std::string>::const_iterator it = args.begin();it != args.end();++it) {
      std_out_err << " " << *it ;
    }
    std_out_err << "\n";
  }

  int ret = common::run(program.string(), args, std_out_err);

  if (WriteMsg::getMessageLevel() >= WriteMsg::mlDebug) {
    std_out_err << "[" << common::getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S") << "] ExitCode:" << ret << "\n";
  }

  return ret;
}

void Task::createDirectories(const boost::filesystem::path& dir, ExecutionLogger& logger) {
  logger.criticalErrorIfFail(create_directories(dir), CMSG_ERROR_CREATE_DIR, dir.string().c_str());
}


void Task::addDependsOn( const string& taskName )
{
  dependsOn.push_back(taskName);
}

const vector<string>& Task::getDependsOn() const
{
  return dependsOn;
}

bool Task::openLogFile()
{
  logstream.open((properties.logDir / (getName() + ".log")).string(), ios_base::binary);
  return logstream.is_open();
}

void Task::copyAllFiles(const  path& source,const  path& dest)
{
  if( exists( path (source)) )
  {
    directory_iterator end ;
    directory_iterator begin(source);
    for( directory_iterator iter = begin; iter != end ; ++iter ) {
      copy_file( source/ iter->path().filename()  ,dest/iter->path().filename() );
    }
  }
}

void Task::copyBinaryExecutable(const path& source, const path& dest, const string& binaryName) {
    copy_file( source / (binaryName + BINARYEXT), dest / (binaryName + BINARYEXT));
}

void Task::copyDirectory(const path& source, const path& dest, const string& dirName) {
  path sourceDir = source / dirName;
  path destDir = dest / dirName;
  create_directory(destDir);
  for(directory_iterator file(sourceDir); file != directory_iterator(); ++file) {
    path current(file->path());
    if(is_directory(current)) {
      copyDirectory(sourceDir, destDir, current.filename().string());
    } else {
      copy_file(current, destDir / current.filename());
    }
  }
}

Task::ExecutionLogger::ExecutionLogger(Task* task, ExecutionResult& result) : task(task), result(result) {
  task->logstream << "[" << common::getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S") << "] Start:" << task->getName() << "\n";
}

Task::ExecutionLogger::~ExecutionLogger() {
  task->logstream << "[" << common::getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S") << "] End:" << task->getName() << " Result:" << result.toString() << "\n";
}


#define GET_VA_PARAMETER(x, length)        \
    va_list al;                            \
    va_start(al, format);                  \
    char x[length];                        \
    vsnprintf(buffer, length, format, al); \
    va_end(al);


bool Task::ExecutionLogger::warningIfFail( bool conditon, const char* format, ... )
{
  if (!conditon) {
    result.setWarning();
    GET_VA_PARAMETER(buffer, 1024)
    task->logstream << buffer;
  }
  return conditon;
}


bool Task::ExecutionLogger::errorIfFail( bool conditon, const char* format, ... )
{
  if (!conditon) {
    result.setError();
    GET_VA_PARAMETER(buffer, 1024)
    task->logstream << buffer;
  }
  return conditon;
}


void Task::ExecutionLogger::criticalErrorIfFail( bool conditon, const char* format, ... )
{
  if (!conditon) {
    result.setCriticalError();
    GET_VA_PARAMETER(buffer, 1024)
    throw Exception(COLUMBUS_LOCATION, buffer);
  }
}


string Task::ExecutionResult::toString() const {
  string result;
  if (warning)
    result += "warning ";

  if (criticalError)
    result += "critical ";

  if (error)
    result += "error ";
  else
    result += "OK";

  return result;
}

void Task::checkedExec(const boost::filesystem::path& program, const std::vector<std::string>& args, ExecutionLogger& logger, bool critical) {
  int res = exec(program, args, logstream);
  if (critical)
    logger.criticalErrorIfFail(res == 0, CMSG_ERROR_EXECUTION_FAILURE, res);
  else
    logger.errorIfFail(res == 0, CMSG_ERROR_EXECUTION_FAILURE, res);
}


void Task::SafeEnvironmentModifier::setVariable(const char* variable, const char* value, ExecutionLogger& logger, bool warningOnOverWrite) {
  const char* old = getenv(variable);

  if (warningOnOverWrite)
    logger.warningIfFail(old == NULL, CMSG_WARNING_ENVSET_OVERWRITE, variable);

  if (old != NULL) {
    oldValue = old;
    exists = true;
  }
  logger.criticalErrorIfFail(setEnvironmentVariable(variable, value) == 0, CMSG_ERROR_ENVSET_FAILURE, variable);
}

Task::SafeEnvironmentModifier::SafeEnvironmentModifier(const char* variable, const char* value, ExecutionLogger& logger, bool warningOnOverWrite) : logger(logger), variable(variable) {
  setVariable(variable, value, logger, warningOnOverWrite);
}


Task::SafeEnvironmentModifier::SafeEnvironmentModifier(const char* variable, const boost::filesystem::path& value, ExecutionLogger& logger, bool warningOnOverWrite) : logger(logger), variable(variable) {
  setVariable(variable, value.string().c_str(), logger, warningOnOverWrite);
}


Task::SafeEnvironmentModifier::~SafeEnvironmentModifier() {
  if (exists) {
    logger.criticalErrorIfFail(setEnvironmentVariable(variable.c_str(), oldValue.c_str()) == 0, CMSG_ERROR_ENVSET_FAILURE, variable.c_str());
  } else {
    logger.warningIfFail(setEnvironmentVariable(variable.c_str(), oldValue.c_str()) == 0, CMSG_ERROR_ENVSET_FAILURE, variable.c_str());
  }
}

} // namespace controller

} // namespace columbus
