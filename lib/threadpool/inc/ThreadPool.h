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

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <queue>
#include <set>
#include <map>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>

#include <iostream>

/**
 * \file ThreadPool.h
 * \brief Interafce of thread pool class
 *
 */

namespace columbus { namespace thread {

  /**
   * \brief smart pointer to boost thread
  */
  typedef  boost::shared_ptr<boost::thread> PtrThread;

  /**
   * \brief thread pool task
   */
  class Task {
    public:
      /**
       * \brief virtual destructor
       */
      virtual ~Task() {}

      /**
       * \brief start operator() in new thread
       */
      virtual void operator()() {};
  };

  class ThreadPool {

  private:

    /**
     * \internal \brief task pool maximum size
     */
    unsigned int _poolSize;

    /**
     * \internal \brief lock for runnum variable (incrase, decrase running threads number)
     */
    boost::recursive_mutex _running_lock;

    /**
     * \internal \brief mutex for task_queue_cond condition variable
     */
    boost::mutex _mutex_queue;

    /**
     * \internal \brief condition variable for waiting tasks
     */
    boost::condition_variable task_queue_cond;

    /**
     * \internal \brief lock for the threads for thread unsafe operations
     */
    boost::shared_mutex _exclusive_task_lock;

    /**
     * \internal \brief number of running tasks
     */
    unsigned int _runnum;

    /**
     * \internal \brief number of failed threads
     */
    unsigned int _errors;

    /**
     * \internal \brief contains the smart pointers to threads
     */
    std::vector<columbus::thread::PtrThread> _threads;

  public:

    /**
     * \brief smart pointer to a Task object
     */
    typedef boost::shared_ptr<Task> PtrTask;

    typedef boost::lock_guard<boost::shared_mutex> TaskLock;

    /**
     * \brief add new task to thread pool
     * \param task [in] smart pointer to a task object
     * \return smart pointer to started thread
     */
    PtrThread add(PtrTask task);

    /**
     * \brief start thread outside of thread pool
     * \param task [in] smart pointer to a task object
     * \return smart pointer to started thread
     */
    PtrThread addSingleThread(PtrTask task);

    /**
     * \brief get maximum size of thread pool
     * \return maximum size of thread pool
     */
    unsigned int getPoolSize() const;

    /**
     * \brief get the number of threads terminated with error
     * \return number of errors
     */
    unsigned int getErrors() const;

    /**
     * \brief wait until the threads are terminated
     */
    void wait();

    /**
     * \brief get mutex to synchronyze with the other tastks 
     */
    boost::shared_mutex& getTaskLockMutex();

    /**
     * \brief thread pool constructor
     * \param poolSize [in] maximum size of thread pool
     */
    ThreadPool(unsigned int poolSize);

    /**
     * \brief thread pool default constructor, set maximum size to number of cpu cores
     */
    ThreadPool();

    /**
     * \brief destructor, wait end of all added thread
     */
    ~ThreadPool();

    static int getNumberOfCores();

    friend class ThreadPoolTask;
    friend class ThreadPoolTaskRunner;
  };

}}

#endif
