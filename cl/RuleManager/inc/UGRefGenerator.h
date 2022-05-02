#ifndef RULE_MANAGER_UG_REF_GENERATOR_H_
#define RULE_MANAGER_UG_REF_GENERATOR_H_

#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <rul/inc/RulHandler.h>
#include <rul/inc/RulTags.h>


struct MetricRulData {
  std::string id;
  std::string name;
  std::string help_text;
  std::set<std::shared_ptr<columbus::rul::Tag>> public_tags;
  std::set<std::string> calculated_for;
};

struct ToolRulData {
  std::string id;
  std::string name;
  std::string priority;
  std::string help_text;
  std::set<std::shared_ptr<columbus::rul::Tag>> public_tags;
  std::set<std::string> calculated_for;
};

class UGRefGenerator {
public:
  explicit UGRefGenerator(const std::string &output_file_path, std::string conf, std::string lang = "eng");

  void write_metrics_part(const std::vector<std::string> &md_file_paths);
  void write_analyzer_part(const std::vector<std::string> &md_file_paths);
  void write_thirdparty_part(const std::vector<std::string> &md_file_paths);
  void write_tags_summary();

private:
  struct TagDetailDescriptionLinkAndMarkedMetrics {
    std::string description;
    std::string link;
    std::vector<std::string> marked_metrics;
  };
  struct TagValueDescriptionLinkAndDetails {
    std::string description;
    std::string link;
    std::map<std::string, TagDetailDescriptionLinkAndMarkedMetrics> detail_map;
  };
  struct CollectionTagsSummary {
    std::string description;
    std::map<std::string, TagValueDescriptionLinkAndDetails> value_map;
  };

  struct ToolTagsSummary {
    std::string description;
    std::map<std::string, std::vector<std::string>> tool_map;
    std::map<std::string, std::vector<std::string>> sm_tool_map;
  };

  struct GeneralTagDescriptionAndMarkedMetrics {
    std::string description;
    std::vector<std::string> marked_metrics;
  };
  struct GeneralTagSummary {
    std::string description;
    std::map<std::string, GeneralTagDescriptionAndMarkedMetrics> general_map;
  };

  std::ofstream md_file_;
  ToolTagsSummary tool_tags_summary_;
  CollectionTagsSummary collection_tags_summary_;
  GeneralTagSummary general_tags_summary_;
  std::string conf_;
  std::string lang_;

  void summarize_collection_tags(const std::string &tool_id, const std::string &tool_metric_id,
                                 const std::set<std::shared_ptr<columbus::rul::Tag>> &tags);

  template <typename RulData>
  void write_definitions(const std::vector<RulData> &rul_data);
};

#endif
