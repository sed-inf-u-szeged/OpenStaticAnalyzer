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

#ifndef _OSACPP_CONTR_TASK_H_
#define _OSACPP_CONTR_TASK_H_

#include <atomic>
#include <boost/thread.hpp>

#include "Properties.h"
#include <controller/inc/Task.h>
#include <threadpool/inc/ThreadPool.h>


DEFINETASK(CleanupTask)
DEFINETASK(Can2limTask)
DEFINETASK(ProfileTask)
DEFINETASK(Cppcheck2GraphTask)
DEFINETASK(Lim2metricsTask)
DEFINETASK(DcfTask)
DEFINETASK(Lim2umlTask)
DEFINETASK(GraphMergeTask)
DEFINETASK(GraphDumpTask)
DEFINETASK(CleanResultsTask)
DEFINETASK(CleanProjectTask)
DEFINETASK(MetricHunterTask)
DEFINETASK(LinkStaticLibsTask)
DEFINETASK(StaticLibHandlerTask)
DEFINETASK(Sonar2GraphTask)
DEFINETASK(LIM2PatternsTask)

class ClangTidyTask : public columbus::controller::Task
{
  class Worker : public columbus::thread::Task
  {
  public:
    Worker(const boost::filesystem::path program, std::queue<std::vector<std::string>>& clangtidy_args, std::string& logDir, boost::mutex& m, boost::condition_variable& cv, std::atomic<int>& threadsLeft, int* failure) : program(program), clangtidy_args(clangtidy_args), logDir(logDir), m(m), cv(cv), threadsLeft(threadsLeft), failure(failure) {}
    void operator()();

  private:
    const boost::filesystem::path program;
    std::queue<std::vector<std::string>>& clangtidy_args;
    std::string logDir;
    boost::mutex& m;
    boost::condition_variable& cv;
    std::atomic<int>& threadsLeft;
    int* failure;
  };

public:
  ClangTidyTask(const Properties& properties, columbus::thread::ThreadPool& threadPool);
  virtual ExecutionResult execute();

  const static std::string name;
  virtual const std::string& getName() const {
    return name;
  }

private:
  columbus::thread::ThreadPool& threadPool;

  friend class Worker;
};

class WrapperTask : public columbus::controller::Task
{
public:
  WrapperTask(const Properties& properties);
  virtual ExecutionResult execute();

  void wrapTool(const std::string& wrappedTool, const std::string& wrapperTool, std::vector<std::string>& sv ) const;

  const static std::string name;
  virtual const std::string& getName() const{
    return name;
  }
};

class UserDefinedMetricsTask : public columbus::controller::Task
{
private:
  std::list<std::string>& inactives;
public:
  const static std::string name;
  UserDefinedMetricsTask(std::list<std::string>& inactives, const Properties& properties);
  virtual ExecutionResult execute();
  virtual const std::string& getName() const {
    return name;
  }
};

#endif
