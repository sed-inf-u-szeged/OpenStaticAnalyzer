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

//#include <boost/config.hpp> // put this first to suppress some VC++ warnings

#include <time.h>
#include <fstream>

#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>

#include "../inc/Controller.h"
#include "../inc/Properties.h"
#include "../inc/messages.h"

using namespace std;
using namespace boost;
using namespace columbus;
using namespace common;

namespace columbus
{

namespace controller
{

namespace {
  void writeToLog(const boost::filesystem::path& logDir, const char* message)
  {
      ofstream controllerLog;
      controllerLog.open((logDir / "controler.txt").string().c_str(), ios_base::app);
      if (controllerLog)
      {
        controllerLog << message;
        controllerLog.close();
      }
  }
}

// Worker is a functor class defines the operator() functions.
// It can be passed for a new thread as well as a simple function,
// but it can be parameterized through it's constructor. It only
// calls the 'execute' method of a task on a new thread.

class Worker : public columbus::thread::Task 
{
public:
  Worker(columbus::controller::Task& task, promise<Controller::Result> p, boost::shared_mutex& taskLockSharedMutex, const boost::filesystem::path& logDir)
    : task(task)
    , p(std::move(p))
    , _taskLockSharedMutex(taskLockSharedMutex)
    , logDir (logDir)
  {}

  void operator()()
  {
    std::tm startTime;
    {
      columbus::thread::ThreadPool::TaskLock lock(_taskLockSharedMutex);
      startTime = common::getCurrentTimeAndDate();
      char buffer[1024];
      snprintf(buffer, 1023, "  [%s] Starting task:          %s\n",  common::getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S", startTime).c_str(), task.getName().c_str());
      WriteMsg::write(WriteMsg::mlNormal, "%s", buffer);
      writeToLog(logDir, buffer);
    }
    
    fflush(stdout);
    fflush(stderr);
    columbus::controller::Task::ExecutionResult exResult = task.execute();
    fflush(stdout);
    fflush(stderr);

    task.closeLogFile();
    std::tm endTime = common::getCurrentTimeAndDate();
    
    {
      columbus::thread::ThreadPool::TaskLock lock(_taskLockSharedMutex);
      int diff = difftime(mktime(&endTime), mktime(&startTime));
      char buffer[1024];
      snprintf(buffer, 1023, "  [%s] Task ended (+%02d:%02d:%02d): %-30s Result:%s\n", common::getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S", endTime).c_str(), diff / 3600, (diff / 60) % 60, diff % 60, task.getName().c_str(), exResult.toString().c_str());
      WriteMsg::write(WriteMsg::mlNormal, buffer);
      writeToLog(logDir, buffer);
    }
    // Use promise to set value of it's corresponding future owned by the main thread
    p.set_value(Controller::Result(task.getName(), exResult));
  }
      
protected:
  columbus::controller::Task& task;
  promise<Controller::Result> p;
  boost::shared_mutex& _taskLockSharedMutex;
  const boost::filesystem::path& logDir;
};



int Controller::executeTasks(ExecutionMode executionMode)
{
  // Set up a representation of the dependencies, also output debug info consisting of a list of all edges
  DirectedAcyclicGraph<string> dependencyGraph;
  if (!buildGraph(dependencyGraph))
    return 1;

  // Execute Tasks
  WriteMsg::write(WriteMsg::mlNormal, "Executing tasks. (Multithread:%d)\n", _props.maxThreads);

  // Stores the results of each task
  vector<shared_future<Result>> futures;
  bool failed = false;
  
  futures.reserve(tasks.size());

  // Execute tasks with no dependencies
  for (const auto& it : tasks)
    if (isReady(it.second->getName(), dependencyGraph))
      executeTask(it.second->getName(), futures);

  // futures will be empty only if there are no tasks running and no results waiting to be processed
  while (!futures.empty())
  {
    // Wait for a task to finish
    auto futureIterator = wait_for_any(futures.begin(), futures.end());
    Result result = futureIterator->get();
    futures.erase(futureIterator);

    // Process finished task
    const Task::ExecutionResult& taskResult = result.second;
    if (taskResult.hasCriticalError())
      failed = true;

    if (taskResult.hasError() && executionMode == EM_FAIL_ON_ANY_ERROR)
      failed = true;

    if (!failed)
    {
      const string& finishedTaskName = result.first;
      const list<string> *dependents = dependencyGraph.getOutEdges(finishedTaskName);

      if (dependents != nullptr)
      {
        const list<string> savedDependents = *dependents;
        // Remove the task from the dependencyGraph
        dependencyGraph.removeNode(finishedTaskName);

        // Execute ready dependent tasks
        for (const string& dependent : savedDependents)
          if (isReady(dependent, dependencyGraph))
            executeTask(dependent, futures);
      }
  
    }
  }

  WriteMsg::write(WriteMsg::mlDebug, "\nParallel runing is finished.\n");

  if (failed)
  {
    writeToLog(_props.logDir, CMSG_FAILURE);
    WriteMsg::write(WriteMsg::mlNormal, CMSG_FAILURE);
  }
  else
  {
    writeToLog(_props.logDir, CMSG_SUCCESSFUL);
    WriteMsg::write(WriteMsg::mlNormal, CMSG_SUCCESSFUL);
  }

  return failed?1:0;
}
  
void Controller::executeTask(const string& taskName, vector<shared_future<Result>>& futures)
{
  // Check task exists
  const auto& it = tasks.find(taskName);
  if (it == tasks.end())
    return;
  
  Task& task = *it->second;

  if (!task.openLogFile())
  {
    string logfilename = (_props.logDir / (task.getName() + ".log")).string();
    WriteMsg::write(WriteMsg::mlError, "Can not open log file for writing: %s\n", logfilename.c_str());
  }
  
  // Add future result to futures, give Worker a promise to that future, allowing it to set it's result which notifies the main thread of the Worker thread's result.
  promise<Result> p;
  shared_future<Result> f = p.get_future();
  futures.push_back(std::move(f));

  // Start running task
  threadPool.add(columbus::thread::ThreadPool::PtrTask(new Worker(task, std::move(p), threadPool.getTaskLockMutex(), _props.logDir)));
}
    
bool Controller::isReady(const string& taskName, const DirectedAcyclicGraph<string>& dependencyGraph)
{
  // Check it exists
  const list<string>* dependencies = dependencyGraph.getInEdges(taskName);
  if (!dependencies)
    return false;
    
  // Check if all dependencies have been completed
  if (dependencies->empty())
    return true;

  return false;
}

bool Controller::buildGraph(DirectedAcyclicGraph<string>& dependencyGraph)
{
  WriteMsg::write(WriteMsg::mlDDebug, "DEPENDENCIES BETWEEN TASKS:\n");
      
  // For each task add it to the graph and set up it's edges
  for (const auto& it : tasks)
  {
    const Task* task = it.second;
    const string& taskName = task->getName();
      
    // Add task to the dependency graph
    dependencyGraph.addNode(taskName);

    // Add edges between the task and it's dependencies
    for (const auto& dependencyName : task->getDependsOn())
    {
      if (tasks.find(dependencyName) != tasks.end())
      {
        auto result = dependencyGraph.addEdge(dependencyName, taskName);
        if(result == DirectedAcyclicGraph<string>::errorType::EDGE_ADDED)
          WriteMsg::write(WriteMsg::mlDDebug, "  %s -> %s\n", dependencyName.c_str(), taskName.c_str());
        else if(result == DirectedAcyclicGraph<string>::errorType::EDGE_ALREADY_EXISTS)
          WriteMsg::write(WriteMsg::mlDDebug, "Attempted to add duplicate dependency: %s -> %s \n", dependencyName.c_str(), taskName.c_str());
        else if(result == DirectedAcyclicGraph<string>::errorType::NODE_CANNOT_HAVE_EDGE_TO_ITSELF)
          WriteMsg::write(WriteMsg::mlDDebug, "Attempted to add task dependency to self: %s -> %s \n", dependencyName.c_str(), taskName.c_str());
        else
        {
          // Return error if edge would of introduced a cycle
          WriteMsg::write(WriteMsg::mlError, "Adding dependency would introduce cycle:  %s -> %s \n", dependencyName.c_str(), taskName.c_str());
          return false;
        }
      }
    }
  }
  WriteMsg::write(WriteMsg::mlDDebug, "\n");
  
  return true;
}

void Controller::addTask(Task* task)
{
  // Add it to the task map
  tasks.insert(make_pair(task->getName(), task));
}

Controller::~Controller()
{
  // Delete all the tasks
  for (auto it : tasks)
    delete it.second;
}



void logCommandLineArguments(const BaseProperties& props, int argc, char* argv[])
{
  ofstream commandlineLogFile;
  commandlineLogFile.open((props.logDir / "commandline.txt").string().c_str());

  if (commandlineLogFile)
  {
    for(int i = 0; i < argc; ++i)
      commandlineLogFile << argv[i] << endl;
    commandlineLogFile.close();
  }
}

void logEnvironment(const BaseProperties& props)
{
  ofstream envlog;
  envlog.open((props.logDir / "environment.txt").string().c_str());
  vector<string> variables;

  common::getEnvironmentVariables(variables);

  for(vector<string>::iterator it = variables.begin(); it != variables.end(); ++it){
    envlog << *it <<endl;
  }
  envlog.close();
}


} // namespace controller

} // namespace columbus




