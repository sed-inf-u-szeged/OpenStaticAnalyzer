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

//#include <boost/config.hpp> // put this first to suppress some VC++ warnings


#include <iterator>
#include <algorithm>
#include <time.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/date_time.hpp>

#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>

#include <threadpool/inc/ThreadPool.h>


#include "../inc/Controller.h"
#include "../inc/Properties.h"

using namespace std;
using namespace boost;
using namespace columbus;
using namespace common;

namespace columbus
{

namespace controller
{

// Worker is a functor class defines the operator() functions.
// It can be passed for a new thread as well as a simple function,
// but it can be parameterized through it's constructor. It only
// calls the 'execute' method of a task on a new thread.
class Worker : public columbus::thread::Task 
{
public:
  Worker(columbus::controller::Task* task, columbus::controller::Task::ExecutionResult* result, boost::shared_mutex& taskLockSharedMutex) : _task(task), _result(result), _taskLockSharedMutex(taskLockSharedMutex) {}

  void operator()()
  {
    {
      columbus::thread::ThreadPool::TaskLock lock(_taskLockSharedMutex);
      WriteMsg::write(WriteMsg::mlNormal, "  [%s] Starting task: %s\n",  common::getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str(), _task->getName().c_str());
    }
    
    fflush(stdout);
    fflush(stderr);
    *_result = _task->execute();
    
    {
      columbus::thread::ThreadPool::TaskLock lock(_taskLockSharedMutex);
      WriteMsg::write(WriteMsg::mlNormal, "  [%s] Task ended: %s Result:%s\n", common::getCurrentTimeAndDate("%Y-%m-%d %H:%M:%S").c_str(), _task->getName().c_str(), _result->toString().c_str());
    }
  }
      
protected:
  columbus::controller::Task* _task;
  columbus::controller::Task::ExecutionResult* _result;
  boost::shared_mutex& _taskLockSharedMutex;
};


// Gets a pointer to a Task object by it's name.
Task* Controller::getTask(const string& str)
{
  map<string, Task*>::iterator it = _taskMap.find(str);
  if(it != _taskMap.end())
    return it->second;
  else return NULL;
}

int Controller::getTaskId(Task* t)
{
  int ret = 0;
  for( vector<Task*>::iterator it = _tasks.begin(); it != _tasks.end(); it++, ret++)
    if(*it == t)
      return ret;

  // task not found
  return -1;
}

int Controller::executeTasks(ExecutionMode executionMode)
{
  // contains the parallel topological sort's result. The key is the execution level, the 
  // second vector contains the tasks, that are can be executed in the same time parallelly
  map<unsigned, vector<string> > sortedMap;
  
  vector<string> names;
  typedef pair<int, int> Edge_s;
  vector<Edge_s> edges;

  for(vector<Task*>::iterator it = _tasks.begin(); it != _tasks.end(); it++)
  {
    Task* t = *it;
    int currentTaskId = getTaskId(t);
    string n = t->getName();
    names.push_back(n);
    vector<string> dep = t->getDependsOn();
    for(vector<string>::iterator it2 = dep.begin(); it2 != dep.end(); it2++) {
      int dependentTaskId = getTaskId(getTask(*it2));
      if (dependentTaskId != -1)
        edges.push_back(make_pair(dependentTaskId, currentTaskId));
    }
  }

  WriteMsg::write(WriteMsg::mlDDebug, "TASKS:\n");

  for(vector<string>::iterator it = names.begin(); it != names.end(); it++)
    WriteMsg::write(WriteMsg::mlDDebug, "  %s\n", it->c_str());

  WriteMsg::write(WriteMsg::mlDDebug, "\nDEPENDENCIES BETWEEN TASKS:\n");

  for(vector<Edge_s>::iterator it = edges.begin(); it != edges.end(); it++)
    WriteMsg::write(WriteMsg::mlDDebug, "  %d -> %d\n", it->first, it->second);
  WriteMsg::write(WriteMsg::mlDDebug, "\n");

  size_t N = names.size();
  
  const size_t nedges = edges.size();
  typedef pair<int,int> Edge;
  vector<Edge> used_by;
  used_by.resize(nedges);

  vector<Edge_s>::iterator it2;
  size_t cnt;
  for(it2 = edges.begin(), cnt = 0; it2 != edges.end(); it2++, cnt++)
    used_by[cnt] = make_pair(it2->first, it2->second);


  typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
  Graph g(N);
  
  for (size_t j = 0; j < nedges; ++j)
    add_edge(used_by[j].first, used_by[j].second, g);
  

  typedef graph_traits<Graph>::vertex_descriptor Vertex;
  
  bool failed = false;

  // Determine ordering for a full run of the tasks
  // and provide the order of tasks that can be executed in parallel
  {
    typedef list<Vertex> MakeOrder;
    MakeOrder::iterator i;
    MakeOrder make_order;
    
    // Linear execution ordering
    topological_sort(g, front_inserter(make_order));
    
    // Parallel execution ordering
    vector<int> time(N, 0);
    for (i = make_order.begin(); i != make_order.end(); ++i) {    
      // Walk through the in_edges an calculate the maximum time.
      if (in_degree (*i, g) > 0) {
        Graph::in_edge_iterator j, j_end;
        int maxdist = 0;
        // Through the order from topological sort, we are sure that every 
        // time we are using here is already initialized.
        for (boost::tuples::tie(j, j_end) = in_edges(*i, g); j != j_end; ++j)
          maxdist = max(time[source(*j, g)], maxdist);
        time[*i] = maxdist+1;
      }
    }

    {
      graph_traits<Graph>::vertex_iterator i, iend;
      for (boost::tuples::tie(i,iend) = vertices(g); i != iend; ++i)
      {
        sortedMap[time[*i]].push_back(names[*i]);
      }

      WriteMsg::write(WriteMsg::mlDebug, "EXECUTION ORDER:\n");
      
      map<unsigned, vector<string> >::iterator it;
      for(it = sortedMap.begin(); it != sortedMap.end(); it++) {
        WriteMsg::write(WriteMsg::mlDebug, "  ");
        for(vector<string>::iterator s_it = it->second.begin(); s_it != it->second.end(); s_it++)
          WriteMsg::write(WriteMsg::mlDebug, "%s ", getTask(*s_it)->getName().c_str());
        WriteMsg::write(WriteMsg::mlDebug, "\n");
      }
      WriteMsg::write(WriteMsg::mlDebug, "\n");
      
      WriteMsg::write(WriteMsg::mlNormal, "Executing tasks. (Multithread:%d)\n",  _props.maxThreads);

      for(it = sortedMap.begin(); it != sortedMap.end() && !failed; it++)
      {
        typedef list<pair<Task*, Task::ExecutionResult> > TaskResultVector;
        TaskResultVector runningTasks;
        
        columbus::thread::ThreadPool threadPool(_props.maxThreads);
        
        for(vector<string>::iterator s_it = it->second.begin(); s_it != it->second.end(); s_it++)
        {
          Task* task = getTask(*s_it);

          runningTasks.push_back(make_pair(task, Task::ExecutionResult()));
          threadPool.add(columbus::thread::ThreadPool::PtrTask(new Worker(runningTasks.back().first, &runningTasks.back().second, threadPool.getTaskLockMutex())));
        }
        threadPool.wait();
        
        for(TaskResultVector::const_iterator taskIt = runningTasks.begin(); taskIt != runningTasks.end(); taskIt++) {
          const Task* task = taskIt->first;
          const Task::ExecutionResult& result = taskIt->second;
                  
          string logfilename = (_props.logDir / (task->getName() + ".log")).string();
          FILE* logfile = fopen(logfilename.c_str(), "wb");
          string log = task->getLog();
          if (logfile != NULL) {
            fwrite(log.c_str(), log.size(), 1 , logfile);
            fclose(logfile);
          } else {
            WriteMsg::write(WriteMsg::mlError, "Can not open log file for writing: %s\n", logfilename.c_str());
            WriteMsg::write(WriteMsg::mlError, "The log is printed to the stdout:\n%s\n", log.c_str());
          }

          if (result.hasCriticalError()) {
            failed = true;
          }
          
          if (result.hasError() && executionMode == EM_FAIL_ON_ANY_ERROR) {
            failed = true;
          }
        }
      }
    }
    WriteMsg::write(WriteMsg::mlDebug, "\nParallel runing is finished.\n");
  }
  
  return failed?1:0;
}

void Controller::addTask( Task* task )
{
  _taskMap[task->getName()] = task;
  _tasks.push_back(task);
}

Controller::~Controller()
{
  for(unsigned i = 0; i < _tasks.size(); i++) {
    delete _tasks[i];
  }
}

} // namespace controller

} // namespace columbus




