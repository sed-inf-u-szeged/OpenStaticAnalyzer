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

#ifndef _LINKER_H
#define _LINKER_H

#include <cstring>
#include <list>
#include <java/inc/java.h>
#include <common/inc/DirectoryFilter.h>

class Linker
{
public:

  static const std::string TIME_STAMP;

  struct JANLinkStat {
    JANLinkStat() : inputFiles(0), peakMemory(0), linkingTime(0) {}
    unsigned long inputFiles;
    uint64_t        peakMemory;
    unsigned long linkingTime;
  };

  Linker(std::string OutputPath,
         std::string OutputFilterPath,
         bool bDumpJML,
         std::string mem,
         DirectoryFilter& filter,
         bool filterRefl,
         bool safemode,
         JANLinkStat& janlinkStat,
         std::string changesetID);
  ~Linker();
  common::ErrorCode link(std::list<std::string>&);
  columbus::java::asg::Factory* getFactory();

private:
  common::ErrorCode loadASG(std::list<std::string>&);
  common::ErrorCode saveASG();

  void saveJML();
  void updateMemoryStat();

  DirectoryFilter& filter;
  bool filterRefl;
  std::string _OutputPath;        // Output file name with full path
  std::string _OutputFilterPath;  // Output filter file name with full path
  bool _bDumpJML;                 // Create JML dump?

  unsigned long _maxMemMB;
  bool _safemode;

  columbus::RefDistributorStrTable* _stt;
  columbus::java::asg::Factory* _fact;

  JANLinkStat& janlinkStat;

  std::string _changesetID;

};

extern const std::string jmlext;

#endif
