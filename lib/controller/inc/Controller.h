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

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <map>
#include <string>
#include "Task.h"
#include "Properties.h"

namespace columbus
{

namespace controller
{

class Controller {
  
  public:
    enum ExecutionMode {
      EM_FAIL_ON_ANY_ERROR,
      EM_FAIL_ON_CRITICAL_ERROR_ONLY
    };
    
  public:
    Controller(const BaseProperties& properties) : _props(properties) {}
    ~Controller();

    int executeTasks(ExecutionMode executionMode);
    void addTask(Task* task);

  protected:

    int getTaskId(Task* t);
    Task* getTask(const std::string& str);
    std::map<std::string, Task*> _taskMap;
    std::vector<Task*> _tasks;
    const BaseProperties& _props;
  
};

} // namespace controller

} // namespace columbus

#endif
