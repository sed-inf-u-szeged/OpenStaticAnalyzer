#include "Exception.h"
#include "common/inc/WriteMessage.h"
#include "io/inc/CsvIO.h"
#include "rul/inc/RulHandler.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>

#define PROGRAM_NAME "RuleManager"
#define EXECUTABLE_NAME "RuleManager"

#include "../inc/UGRefGenerator.h"
#include <MainCommon.h>

using namespace std;
using namespace common;
using namespace columbus;

static std::string output_file_path;
static void ppFile(char *filename) {
  output_file_path = filename;
}

static std::string rulConfig = "Default";
static bool ppConf (const Option *o, char *argv[]) {
  rulConfig = argv[0];
  return true;
}


static std::vector<std::string> metric_file_paths;
static bool ppMetric(const Option *o, char *argv[]) {
  common::split(argv[0], metric_file_paths, ' ');
  return true;
}

static std::vector<std::string> analyzer_file_paths;
static bool ppOSA(const Option *o, char *argv[]) {
  common::split(argv[0], analyzer_file_paths, ' ');
  return true;
}

static std::vector<std::string> tool_file_paths;
static bool ppTool(const Option *o, char *argv[]) {
  common::split(argv[0], tool_file_paths, ' ');
  return true;
}

static std::vector<std::string> rules2csv_args;
static bool ppRules2Csv(const Option *o, char *argv[]) {
  common::split(argv[0], rules2csv_args, ' ');
  return true;
}



const Option OPTIONS_OBJ [] = {
  { false,  "-conf",          1, "confName",                  0, OT_WC, ppConf,   nullptr, "Specify the name of the rul configuration to be used.\n" },
  { false,  "-osaRuls",       1, "file_1 file_2 ... file_n",  0, OT_WC, ppOSA,    nullptr, "OpenStaticAnalyzer rul files to be used.\n" },
  { false,  "-3rdPartyRuls",  1, "file_1 file_2 ... file_n",  0, OT_WC, ppTool,   nullptr, "Rul files of 3rd party tools to be used.\n" },
  { false,  "-metricRuls",    1, "file_1 file_2 ... file_n",  0, OT_WC, ppMetric, nullptr, "Metric rul files to be used.\n" },
  { false,  "-rules2csv",     1, "rulfile_1 rulfile_2 ... rulfile_n output_file", 0, OT_WC, ppRules2Csv,  nullptr, "Generate rules_*.csv from rul files.\n" },
  COMMON_CL_ARGS
};

void rules2Csv(const std::vector<std::string> &args) {
  if (args.size() < 2) { return; }

  const auto rul_file_count = args.size() - 1;

  std::map<std::string, std::vector<unsigned>> rules_map;
  std::vector<std::string> tool_order;
  tool_order.reserve(rul_file_count);

  for (std::size_t i = 0; i < rul_file_count; ++i) {
    rul::RulHandler rul_handler(args[i], "Default", "eng");
    std::vector<std::string> rule_ids;
    rul_handler.getRuleIdList(rule_ids);

    if (rule_ids.empty()) [[unlikely]] { throw columbus::Exception(COLUMBUS_LOCATION, "No rules inside " + args[i]); }
    const auto prefix_end = rule_ids.front().find('_');
    if (prefix_end == std::string::npos) [[unlikely]] {
      std::string message = "Can't find prefix of rule " + rule_ids.front();
      (message += " in ") += args[i];
      throw columbus::Exception(COLUMBUS_LOCATION, message);
    }
    const auto &prefix = tool_order.emplace_back(rule_ids.front().substr(0, prefix_end));

    for (const auto &rul_id : rule_ids) {
      if (rul_id.size() < prefix_end || prefix != std::string_view(&rul_id.front(), prefix_end)) [[unlikely]] {
        std::string message = "Expected rule " + rul_id;
        (message += " to have prefix ") += prefix;
        (message += " in ") += args[i];
        throw columbus::Exception(COLUMBUS_LOCATION, message);
      }

      auto [entry, inserted] = rules_map.try_emplace(rul_id.substr(prefix_end + 1), rul_file_count, 0);
      auto &priorites = entry->second;

      if (inserted) {
        priorites[i] = 1;
      } else {
        const auto next_prio =
            std::count_if(priorites.begin(), priorites.end(), [](unsigned prio) { return prio != 0; }) + 1;
        priorites[i] = next_prio;
        if (next_prio == 2) {
          WriteMsg::write(WriteMsg::MsgLevel::mlNormal, "%s rule is defined by multiple tools!\n",
                                  entry->first.c_str());
        }
      }
    }
  }

  const auto &output = args.back();
  io::CsvIO csv(output, io::IOBase::omWrite);

  csv.writeColumn("toolId");
  for (const auto &tool_name : tool_order) {
    csv.writeColumn(tool_name);
  }
  csv.writeNewLine();

  for (const auto &[rul_id, priorites] : rules_map) {
    csv.writeColumn(rul_id);
    for (const auto &priority : priorites) {
      if (priority == 0) {
        csv.writeColumn("-");
      } else {
        csv.writeColumn(priority);
      }
    }
    csv.writeNewLine();
  }

  csv.close();
}

int main(int argc, char *argv[])
{
  MAIN_BEGIN
      
  MainInit( argc, argv, "-");

  if (!rules2csv_args.empty()) 
  {
    rules2Csv(rules2csv_args); 
  } 
  else
  {
    UGRefGenerator ug_generator(output_file_path, rulConfig);

    if (!metric_file_paths.empty()) {
      ug_generator.write_metrics_part(metric_file_paths);
    }

    if (!analyzer_file_paths.empty()) {
      ug_generator.write_analyzer_part(analyzer_file_paths);
     }

    if (!tool_file_paths.empty()) {
      ug_generator.write_thirdparty_part(tool_file_paths);
    }

    ug_generator.write_tags_summary();
  }
  MAIN_END

  return 0;
}
