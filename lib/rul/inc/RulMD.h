#ifndef RUL_RUL_MD_H_
#define RUL_RUL_MD_H_

#include "Exception.h"
#include "rul/inc/RulHandler.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>

namespace columbus::rul {

class RulMDParser {
public:
  template <typename T, typename = std::enable_if_t<!std::is_base_of_v<RulMDParser, std::remove_reference_t<T>>>>
  explicit RulMDParser(T &&rul_file_path) : file_path_(std::forward<T>(rul_file_path)) {
    if (!file_.is_open()) { throw columbus::Exception(COLUMBUS_LOCATION, "Could not open: " + file_path_); }
    working_directory_.remove_filename();
  }

  void parse_into(RulHandler::RulData &rul_data);

private:
  std::string file_path_;
  std::filesystem::path working_directory_{file_path_};
  std::ifstream file_{file_path_};
  std::string line_;
  std::size_t line_number_ = 0;

  void next_line();
  void next_data_line();
  void next_nonempty_line();
  void next_noncomment_line();
  bool skip_if_empty();
  bool skip_if_comment();

  std::optional<std::string_view> try_next_indented_line();
  std::optional<std::string_view> try_next_list_item();
  bool try_get_bool(std::string_view line_part);
  RulHandler::RulBoolean try_get_rul_boolean(std::string_view line_part);

  [[noreturn]] void throw_error(const std::string &location, const std::string &message);

  void parse_indented_text_block(RulMDString &md_string);
  void parse_indented_text_block(std::string &string);

  void parse_tool_description(std::map<std::string, std::map<std::string, RulMDString>> &tool_description);
  void parse_tool_description_config(std::map<std::string, RulMDString> &tool_description_config);

  void parse_includes(RulHandler::RulData &rul_data);

  void parse_tag_metadata(TagStore &tag_store);
  void parse_tag_description(RulMDString &description);
  void parse_tag_summarized(bool &summarized);
  void parse_tag_url(std::string &url);
  void parse_tag_metadata_kind(TagKindMetadataContainer &tag_kind_metadata);
  void parse_tag_metadata_value(TagValueMetadataContainer &tag_value_metadata);
  void parse_tag_metadata_detail(TagDetailMetadataContainer &tag_detail_metadata_container);

  struct ExtraMetricsContext;
  struct ExtraMetricContext;
  void parse_metrics(std::map<std::string, RulHandler::RulMetric> &metrics, const ExtraMetricsContext &extra_context);
  void parse_metric(RulHandler::RulMetric &metric, const ExtraMetricContext &extra_context);
  void parse_metric_config(RulHandler::RulConfiguration &config, RulHandler::RulLang &lang,
                           const ExtraMetricContext &extra_context);
  void parse_metric_config_settings(std::map<std::string, RulHandler::RulSetting> &settings);
  void parse_metric_config_calculated(std::set<std::string> &calculated);
  void parse_metric_config_tags(RulHandler::RulConfiguration &rul_config, TagStore &tag_store);

  struct ExtraMetricsContext {
    std::map<std::string, std::string> &redefines;
    std::map<std::string, std::string> &original_id_rule_id;
    TagStore &tag_store;
  };

  struct ExtraMetricContext {
    std::map<std::string, std::string> &redefines;
    std::map<std::string, std::string> &original_id_rule_id;
    TagStore &tag_store;
    const std::string &metric_name;
  };
};

class RulMDWriter {
public:
  static void write(const std::string &file_path, const RulHandler::RulData &rul_data);

private:
  static void write_indented_text_block(std::ofstream &file, const std::string &string);
  static void write_tool_description(std::ofstream &file,
                                     const std::map<std::string, std::map<std::string, RulMDString>> &tool_description);
  static void write_tag_metadata_description(std::ofstream &file, const std::string &description);
  static void write_tag_metadata_summarized(std::ofstream &file, bool summarized);
  static void write_tag_metadata_url(std::ofstream &file, const std::string &url);
  static void write_tag_metadata(std::ofstream &file, const TagStore &tag_store);
  static void write_metrics(std::ofstream &file, const RulHandler::RulData &rul_data);
  static void write_metric_config_settings(std::ofstream &file,
                                           const std::map<std::string, RulHandler::RulSetting> &settings);
  static void write_metric_config_calculated(std::ofstream &file, const std::set<std::string> &calculated);
  static void write_metric_config_help_text(std::ofstream &file, const std::string &help_text);
  static void write_metric_config_tags(std::ofstream &file, const std::set<std::shared_ptr<Tag>> &tags);
  static void write_metric_config_tags(std::ofstream &file, const RulHandler::RulConfiguration &config,
                                       const RulHandler::RulData &rul_data);
  static void write_metric_config_key_value(std::ofstream &file, std::string_view key, RulHandler::RulBoolean value);
  static void write_metric_config_key_value(std::ofstream &file, std::string_view key, const std::string &value);
};

} // namespace columbus::rul

#endif
