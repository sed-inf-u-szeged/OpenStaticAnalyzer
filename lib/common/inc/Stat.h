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

#ifndef _STAT_H_
#define _STAT_H_

#include <cstring>
#include <stdint.h>
#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <map>


namespace common
{

  /**
  * \brief Structure to hold the memory statistic values of a process.
  */
  typedef struct {
    uint64_t size;
    uint64_t resident;
    uint64_t shared;
    uint64_t text;
    uint64_t lib;
    uint64_t data;
    uint64_t peaksize;
    uint64_t pagedsize;
    uint64_t peakpagedsize;
  } memstat;

  /**
  * \brief Structure to hold the time statistic values of a process.
  */
  typedef struct {
    uint64_t user;   /**< User time. */
    uint64_t system; /**< System time. */
  } timestat;

  /**
  * \brief Fills a memstat structure with the memory statistic values of the current process.
  * \return Returns the filled memstat structure.
  */
  memstat  getProcessUsedMemSize();

  /**
  * \brief Fills a timestat structure with the time statistic values of the current process.
  * \return Returns the filled timestat structure.
  */
  timestat getProcessUsedTime();

  /**
   * \brief Writes a minimal stat file with the current memory consumption and runtime values.
   * \param filename [in] The name of the stat file to be written.
   */
  void writeMinimalStatFile(const std::string& filename);

  /**
   * \brief Writes a minimal stat file with the given memory consumption and current runtime values.
   * \param filename  [in] The name of the stat file to be written.
   * \param maxmemory [in] The maximal value of the memory consumption.
   */
  void writeMinimalStatFile(const std::string& filename, uint64_t maxmemory);

  /**
   * \brief Updates the peak memory counter if the current memory consumption is higher than the former value.
   * \param reset  [in] If it is set to true then the counter will be reset to 0 before the update.
   * \return the current value of the memory counter
   */
  uint64_t updateMemoryStat(bool reset = false);

  class PerformanceLogger
  {
  private:
      struct Section
      {
        const char* name;
        timestat startTime;
        timestat endTime;
        std::vector<Section> subSections;
      };

  public:
      class SectionHandler
      {
      public:
        SectionHandler(SectionHandler&& other);
        void addTimeStamp(const char* name);
        ~SectionHandler();

      private:
        SectionHandler(PerformanceLogger* performanceLogger, Section* section);
        SectionHandler(const SectionHandler&) = delete;
        Section* section;
        PerformanceLogger* performanceLogger;

        friend class PerformanceLogger;
      };

  public:
      static PerformanceLogger& getPerformanceLogger(const char* logFilename = "PerfStats.txt");

      void enable();
      void disable();
      void setSectionLimit(size_t sectionLimit);
      SectionHandler startSection(const char* name);

      ~PerformanceLogger();

  private:
      PerformanceLogger(const char* logFilename);
      void endSection(Section* name);
      void addTimeStamp(const char* name);
      void dumpSection(FILE* logFile, const Section& section, int level, timestat relativeTime) const;
      void recalculateAlignedSectionNameMaxLength(const Section& section, int level);

  private:
      static std::unique_ptr<PerformanceLogger> instance;
      Section rootSection;
      std::stack<Section*> sectionStack;
      bool enabled;
      size_t sectionLimit;
      size_t sectionCounter;
      size_t alignedSectionNameMaxLength;
      std::string logFilename;

  };


  template <typename key_type, typename value_type>
  class Cache
  {
    public:

      struct FindResult
      {
          bool found;
          const value_type& value;
      };

      Cache()
        : hit_counter (0)
        , miss_counter (0)
      {}

      FindResult getValue(const key_type& key) const
      {

        const auto result = values.find(key);
        if (result != values.end())
        {
          ++hit_counter;
          return { true, result->second };
        }
        else
        {
          ++ miss_counter;
          return  { false, value_type() };
        }
      }

      const value_type& setValue(const key_type& key, const value_type& value)
      {
        return values[key] = value;
      }

      size_t getHitCount() const
      {
        return hit_counter;
      }

      size_t getMissCount() const
      {
        return miss_counter;
      }


    private:
      mutable size_t hit_counter;
      mutable size_t miss_counter;

      std::map<key_type, value_type> values;
  };
}

#endif
