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

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <map>
#include <queue>
#include <string>
#include <unordered_set>

#include <boost/thread.hpp>

#include <threadpool/inc/ThreadPool.h>

#include "Task.h"
#include "Properties.h"
#include "DirectedAcyclicGraph.h"

namespace columbus
{

namespace controller
{

class Controller {
  
public:
  typedef std::pair<std::string, Task::ExecutionResult> Result;
    
  enum ExecutionMode {
    EM_FAIL_ON_ANY_ERROR,
    EM_FAIL_ON_CRITICAL_ERROR_ONLY
  };

public:
  Controller(const BaseProperties& properties, columbus::thread::ThreadPool& threadPool) : _props(properties), threadPool(threadPool) {}
  ~Controller();

  int executeTasks(ExecutionMode executionMode);
  void addTask(Task* task);

protected:
  std::map<const std::string, Task*> tasks;
  const BaseProperties& _props;
  columbus::thread::ThreadPool& threadPool;
  
  bool isReady(const std::string& taskName, const DirectedAcyclicGraph<std::string>& dependencyGraph);
  void executeTask(const std::string& taskName, std::vector<boost::shared_future<Result>>& futures);
  bool buildGraph(DirectedAcyclicGraph<std::string>& dependencyGraph);
};

void logCommandLineArguments(const BaseProperties& props, int argc, char* argv[]);
void logEnvironment(const BaseProperties& props);

} // namespace controller

} // namespace columbus

#endif
