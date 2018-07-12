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

#ifdef _WIN32
#include <Windows.h>
#else
#ifdef __unix__
#include <unistd.h>
#endif
#endif

#include "../inc/ThreadPool.h"

using namespace boost;
using namespace std;

namespace columbus { namespace thread {

  class ThreadPoolTaskRunner {
  protected:
    ThreadPool::PtrTask _task;
  public:
    ThreadPoolTaskRunner(ThreadPool::PtrTask task)
      : _task(task)
    {};

    void operator()()
    {
      (*_task)();
    }

  };

  class ThreadPoolTask {
  protected:
    ThreadPool* _pool;
    ThreadPool::PtrTask _task;
  public:
    ThreadPoolTask(ThreadPool* pool, ThreadPool::PtrTask task)
      : _pool(pool)
      , _task(task)
    {
    }

    ThreadPoolTask(const ThreadPoolTask& tpt)
      : _pool(tpt._pool)
      , _task(tpt._task)
    {
    }

    ThreadPoolTask& operator=(const ThreadPoolTask& tpt)
    {
      _pool = tpt._pool;
      _task = tpt._task;
      return *this;
    }

    void operator()()
    {
      while(true)
      {
        {
          boost::unique_lock<boost::recursive_mutex > safe_running_lock(_pool->_running_lock);
          if(_pool->_runnum < _pool->_poolSize) {
            _pool->_runnum++;
            break;
          }
        }
        boost::unique_lock<boost::mutex> lock(_pool->_mutex_queue);
        _pool->task_queue_cond.wait(lock);
      }

      try
      {
        (*_task)();
      }
      catch (...)
      {
        boost::unique_lock<boost::recursive_mutex > safe_running_lock(_pool->_running_lock);
        ++_pool->_errors;
      }

      {
        boost::unique_lock<boost::recursive_mutex > safe_running_lock(_pool->_running_lock);
        _pool->_runnum--;
      }
      _pool->task_queue_cond.notify_all();
    }
    
  };

  PtrThread ThreadPool::add(PtrTask task)
  {
    PtrThread newTask(new boost::thread(ThreadPoolTask(this, task)));
    _threads.push_back(newTask);
    return newTask;
  }

  PtrThread ThreadPool::addSingleThread(PtrTask task)
  {
    ThreadPoolTaskRunner taskRunner(task);
    PtrThread newTask(new boost::thread(taskRunner));
    _threads.push_back(newTask);
    return newTask;
  }

  unsigned int ThreadPool::getPoolSize() const
  {
    return _poolSize;
  }

  unsigned int ThreadPool::getErrors() const
  {
    return _errors;
  }

  void ThreadPool::wait()
  {
    for(auto& threadPtr : _threads)
    {
      threadPtr->join();
    }
  }

  ThreadPool::ThreadPool(unsigned int poolSize)
    : _poolSize(poolSize)
    , _running_lock()
    , _mutex_queue()
    , task_queue_cond()
    , _runnum(0)
    , _errors(0)
  {
  }

  ThreadPool::ThreadPool()
    : _poolSize(1)
    , _running_lock()
    , _mutex_queue()
    , task_queue_cond()
    , _runnum(0)
    , _errors(0)
  {
    // get number of cpu cores
    _poolSize = getNumberOfCores();
  }

  ThreadPool::~ThreadPool(void)
  {
    wait();
  }

  boost::shared_mutex& ThreadPool::getTaskLockMutex()
  {
    return _exclusive_task_lock;
  }

  int ThreadPool::getNumberOfCores()
  {
    int poolSize = 1;
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo( &sysinfo );
    poolSize = sysinfo.dwNumberOfProcessors;
#else
#ifdef __unix__
    poolSize = sysconf( _SC_NPROCESSORS_ONLN );
#endif
#endif
    return poolSize;
  }

}}
