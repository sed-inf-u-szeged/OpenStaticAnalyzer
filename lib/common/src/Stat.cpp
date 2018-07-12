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

#include <stdio.h>
#include <string>

#ifdef __unix__
#include <unistd.h>
#include <sys/types.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <process.h>
#include "psapi.h"
#endif

#include "../inc/Stat.h"
#include "../inc/messages.h"
#include "../inc/FileSup.h"
#include "Exception.h"

#ifdef __unix__
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#endif

namespace common
{

memstat getProcessUsedMemSize() {
  memstat stat = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#ifdef __unix__
  pid_t me = getpid();

  char file[100];
  sprintf(file,"/proc/%d/statm", me);

  FILE *f = fopen(file, "rt");
  if (f) {
    int read = fscanf(f, "%" PRIu64 " %" PRIu64 " %" PRIu64 " %" PRIu64 " %" PRIu64 " %" PRIu64, &stat.size, &stat.resident, &stat.shared, &stat.text, &stat.lib, &stat.data);
    fclose(f);
    if (read == EOF || read != 6) {
      throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_PROC_READ_ERROR); 
    } else {
      const int PAGESIZE = 4096;
      stat.size *= PAGESIZE;
      stat.resident *= PAGESIZE;
      stat.shared *= PAGESIZE;
      stat.text *= PAGESIZE;
      stat.lib *= PAGESIZE;
      stat.data *= PAGESIZE;
    }
  }
#endif

#ifdef _WIN32
  PROCESS_MEMORY_COUNTERS pmc;

  HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, _getpid() );

  if (hProcess)
  {
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
    {
      stat.size          = (uint64_t)pmc.WorkingSetSize;
      stat.peaksize      = (uint64_t)pmc.PeakWorkingSetSize;
      stat.pagedsize     = (uint64_t)pmc.PagefileUsage;
      stat.peakpagedsize = (uint64_t)pmc.PeakPagefileUsage;
    }
    CloseHandle(hProcess);
  }

#endif

  return stat;
}

timestat getProcessUsedTime() {
  timestat stat = { 0, 0 };

#ifdef __unix__
  pid_t me = getpid();

  char file[100];
  sprintf(file,"/proc/%d/stat", me);

  FILE *f = fopen(file, "rt");
  if (f) {
    char temp[1000];
    int read = fscanf(f, "%s %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %" PRIu64 " %" PRIu64, temp, temp, temp, (int*)temp, (int*)temp, (int*)temp, (int*)temp, (int*)temp, (long unsigned*)temp,  (long unsigned *)temp, (long unsigned*)temp, (long unsigned*)temp, (long unsigned*)temp,  &stat.user, &stat.system);
    fclose(f);
    if (read == EOF || read != 15) {
      throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_PROC_READ_ERROR); 
    }
  }
#endif

#ifdef _WIN32
  FILETIME m_createTime;
  FILETIME m_exitTime;
  FILETIME m_kernelTimeProcess;
  FILETIME m_userTimeProcess;
  ULARGE_INTEGER tmpval;

  HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, _getpid() );
  if (hProcess)
  {
    if (GetProcessTimes( hProcess, &m_createTime, &m_exitTime, &m_kernelTimeProcess, &m_userTimeProcess))
    {
      // times are in 100-nano seconds
      tmpval.LowPart = m_userTimeProcess.dwLowDateTime;
      tmpval.HighPart = m_userTimeProcess.dwHighDateTime;
      // 1/100 seconds
      tmpval.QuadPart=tmpval.QuadPart/100000;
      // converting to smaller representation
      stat.user = (uint64_t) tmpval.QuadPart;
      
      // system time means kernel time
      tmpval.LowPart = m_kernelTimeProcess.dwLowDateTime;
      tmpval.HighPart = m_kernelTimeProcess.dwHighDateTime;
      // 1/100 seconds
      tmpval.QuadPart=tmpval.QuadPart/100000;
      // converting to smaller representation
      stat.system = (uint64_t) tmpval.QuadPart;
    }
    CloseHandle( hProcess );
  }
#endif

  return stat;
}

void writeMinimalStatFile(const std::string& filename) {
  memstat maxmem = getProcessUsedMemSize();
  writeMinimalStatFile(filename, maxmem.size);
}

void writeMinimalStatFile(const std::string& filename, uint64_t maxmemory) {
  timestat totaltime = getProcessUsedTime();
  if (!filename.empty())
  {
    bool writeHeader = false;
    if (!pathFileExists(filename, false))
      writeHeader = true;
    
    FILE* csvfile = fopen(filename.c_str(), "at");
    if (csvfile) {
      if (writeHeader)
        fprintf(csvfile, "Total cpu time (s);Peak memory usage (MByte)\n");

      fprintf(csvfile, "%.2f;%u\n", (totaltime.system + totaltime.user) / 100.0f, (unsigned)(maxmemory / (1024 * 1024)));
      fclose(csvfile);
    } else 
      throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_STAT_WRITE_ERROR); 
  }
}

uint64_t updateMemoryStat(bool reset) {
  static uint64_t counter = 0;
  if (reset)
    counter = 0;
  
  memstat ms = getProcessUsedMemSize();
  if (counter < ms.size)
    counter = ms.size;
  
  return counter;
}

}

