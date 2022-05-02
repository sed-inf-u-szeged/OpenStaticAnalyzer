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

#ifndef _OSAJ_CONTR_TASK_H_
#define _OSAJ_CONTR_TASK_H_

#include "Properties.h"
#include <controller/inc/Task.h>

DEFINETASK(CleanResultsTask)
DEFINETASK(CleanProjectTask)
DEFINETASK(DirectoryBasedAnalysisTask)
DEFINETASK(JAN2ChangePathTask)
DEFINETASK(ASGBackupTask)
DEFINETASK(JANFilterTask)
DEFINETASK(JAN2limTask)
DEFINETASK(ProfileTask)
DEFINETASK(DcfTask)
DEFINETASK(PMD2GraphTask)
DEFINETASK(FindBugsTask)
DEFINETASK(Lim2metricsTask)
DEFINETASK(GraphMergeTask)
DEFINETASK(GraphDumpTask)
DEFINETASK(MetricHunterTask)
DEFINETASK(Sonar2GraphTask)
DEFINETASK(LIM2PatternsTask)

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
