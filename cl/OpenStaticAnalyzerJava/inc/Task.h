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

#ifndef _SMJ_CONTR_TASK_H_
#define _SMJ_CONTR_TASK_H_

#include "Properties.h"
#include <controller/inc/Task.h>

DEFINETASK(CleanResultsTask)
DEFINETASK(CleanProjectTask)
DEFINETASK(DirectoryBasedAnalysisTask)
DEFINETASK(RemoveWrapperBinsTask)
DEFINETASK(CheckASGListTask)
DEFINETASK(JAN2ChangePathTask)
DEFINETASK(ASGBackupTask)
DEFINETASK(JANFilterTask)
DEFINETASK(SuperlinkTask)
DEFINETASK(JAN2limTask)
DEFINETASK(ProfileTask)
DEFINETASK(FaultHunterTask)
DEFINETASK(VulnerabilityHunterTask)
DEFINETASK(AndroidHunterTask)
DEFINETASK(DcfTask)
DEFINETASK(PMD2GraphTask)
DEFINETASK(FindBugsTask)
DEFINETASK(Lim2metricsTask)
DEFINETASK(RTEHunterTask)
DEFINETASK(GraphMergeTask)
DEFINETASK(GraphDumpTask)
DEFINETASK(MetricHunterTask)
DEFINETASK(ChangeTrackerTask)

class WrapperBasedAnalysisTask : public columbus::controller::Task
{
private:

public:
  WrapperBasedAnalysisTask(const Properties& properties);
  virtual ExecutionResult execute();

  void wrapTool(const std::string& wrappedTool, const std::string& wrapperTool, std::vector<std::string>& sv ) const;

  const static std::string name;
  virtual const std::string& getName() const{
    return name;
  }
};

class AddLicenceTask : public columbus::controller::Task
{
private:
  std::list<std::string> inactives;
public:
  const static std::string name;
  AddLicenceTask(std::list<std::string> inactives, const Properties& properties);
  virtual ExecutionResult execute();
  virtual const std::string& getName() const {
    return name;
  }
};

#endif
