#include "rul/inc/RulMD.h"

#include <algorithm>
#include <cctype>
#include <utility>

#include <boost/algorithm/string/predicate.hpp>
#include <common/inc/StringSup.h>

// #define LEGACY_RUL_CONVERSION
#ifdef LEGACY_RUL_CONVERSION
#include <boost/asio/io_service.hpp>
#include <boost/process.hpp>
#endif

namespace {
namespace Keyword {
constexpr std::string_view tool_description = "ToolDescription";
constexpr std::string_view tool_description_config_description = "Description";
constexpr std::string_view includes = "Includes";
constexpr std::string_view metrics = "Metrics";
constexpr std::string_view metric_config_warning = "Warning";
constexpr std::string_view metric_config_display_name = "DisplayName";
constexpr std::string_view metric_config_help_text = "HelpText";
constexpr std::string_view metric_config_warning_text = "WarningText";
constexpr std::string_view metric_config_enabled = "Enabled";
constexpr std::string_view metric_config_numeric_type = "NumericType";
constexpr std::string_view metric_config_visible = "Visible";
constexpr std::string_view metric_config_settings = "Settings";
constexpr std::string_view metric_config_calculated = "Calculated";
constexpr std::string_view metric_config_tags = "Tags";
constexpr std::string_view metric_config_original_id = "OriginalId";
constexpr std::string_view tag_metadata = "TagMetadata";
constexpr std::string_view tag_metadata_description = "Description";
constexpr std::string_view tag_metadata_url = "Url";
constexpr std::string_view tag_metadata_summarized = "Summarized";
constexpr std::string_view true_ = "true";
constexpr std::string_view false_ = "false";
} // namespace Keyword

namespace Symbol {
constexpr std::string_view comment_begin = "<!--";
constexpr std::string_view comment_end = "-->";
constexpr std::string_view text_block_indent = "  ";
constexpr char list_item = '-';
constexpr char heading = '#';
constexpr char equals = '=';
constexpr std::string_view redefine = "->";
} // namespace Symbol

std::string_view trimmed(std::string_view text) {
  constexpr auto is_space = [](const unsigned char c) { return std::isspace(c) != 0; };
  if (const auto not_space_left = std::find_if_not(text.begin(), text.end(), is_space);
      not_space_left != text.begin()) {
    text.remove_prefix(not_space_left - text.begin());
  }

  if (const auto not_space_right = std::find_if_not(text.rbegin(), text.rend(), is_space);
      not_space_right != text.rbegin()) {
    text.remove_suffix(not_space_right - text.rbegin());
  }
  return text;
}

std::size_t get_heading_level(const std::string_view heading) {
  constexpr auto is_hash = [](const char c) { return c == Symbol::heading; };
  const auto hash_end = std::find_if_not(heading.begin(), heading.end(), is_hash);
  return hash_end - heading.begin();
}

std::string_view get_heading_text(const std::size_t heading_level, const std::string_view heading) {
  return trimmed({heading.data() + heading_level, heading.size() - heading_level});
}

std::optional<std::string_view> to_list_item(std::string_view list_item) {
  static_assert(std::is_same_v<std::decay_t<decltype(Symbol::list_item)>, char>);
  if (list_item.front() == Symbol::list_item) {
    list_item.remove_prefix(1);
    return trimmed(list_item);
  }
  return {};
}

std::optional<std::string_view> to_indented_line(std::string_view indented_line) {
  if (boost::starts_with(indented_line, Symbol::text_block_indent)) {
    indented_line.remove_prefix(Symbol::text_block_indent.size());
    return indented_line;
  }
  if (indented_line.empty()) { return indented_line; }
  return {};
}

constexpr std::optional<bool> to_boolean(const std::string_view text) {
  if (text == Keyword::true_) { return true; }
  if (text == Keyword::false_) { return false; }
  return {};
}

std::pair<std::string_view, std::optional<std::string_view>> to_conf_redefine(const std::string_view text) {
  const auto arrow_pos = text.find_first_of(Symbol::redefine);
  if (arrow_pos == std::string_view::npos) { return {text, {}}; }
  auto conf = trimmed({text.data(), arrow_pos});
  const auto redef_begin_pos = arrow_pos + Symbol::redefine.size();
  auto redef = trimmed({text.data() + redef_begin_pos, text.size() - redef_begin_pos});
  return {conf, redef};
}

std::optional<std::pair<std::string_view, std::string_view>> to_key_value(const std::string_view text) {
  const auto equals_it = std::find(text.begin(), text.end(), Symbol::equals);
  if (equals_it == text.end()) { return {}; }

  const auto equals_pos = static_cast<std::size_t>(equals_it - text.begin());
  auto key = trimmed({text.data(), equals_pos});

  static_assert(std::is_same_v<std::decay_t<decltype(Symbol::equals)>, char>);
  const auto value_begin_pos = equals_pos + 1;
  auto value = trimmed({text.data() + value_begin_pos, text.size() - value_begin_pos});

  return std::make_pair(key, value);
}
} // namespace

namespace columbus::rul {
void RulMDParser::parse_into(RulHandler::RulData &rul_data) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 1) [[likely]] {
      const auto heading_text = get_heading_text(heading_level, line_);
      if (heading_text == Keyword::tool_description) {
        parse_tool_description(rul_data.toolDescription);
      } else if (heading_text == Keyword::includes) {
        parse_includes(rul_data);
      } else if (heading_text == Keyword::metrics) {
        parse_metrics(rul_data.metrics, {rul_data.redefines, rul_data.originalIdRuleId, rul_data.tagStore});
      } else if (heading_text == Keyword::tag_metadata) {
        parse_tag_metadata(rul_data.tagStore);
      } else [[unlikely]] {
        throw_error(COLUMBUS_LOCATION, "Unexpected heading 1 name");
      }
    } else if (heading_level > 1) {
      throw_error(COLUMBUS_LOCATION, "Expected heading 1 here");
    } else {
      throw_error(COLUMBUS_LOCATION, "Unexpected line");
    }
  }
}

void RulMDParser::next_line() {
  if (std::getline(file_, line_)) { ++line_number_; }
}

void RulMDParser::next_nonempty_line() {
  next_line();
  while (skip_if_empty()) {}
}

void RulMDParser::next_noncomment_line() {
  next_line();
  while (skip_if_comment()) {}
}

void RulMDParser::next_data_line() {
  next_line();
  while (skip_if_empty() || skip_if_comment()) {}
}

bool RulMDParser::skip_if_empty() {
  if (!line_.empty() || !file_) { return false; }
  next_line();
  return true;
}

bool RulMDParser::skip_if_comment() {
  bool inside_comment = false;
  while (file_) {
    if (inside_comment) {
      auto trimmed_line = trimmed(line_);
      if (boost::ends_with(trimmed_line, Symbol::comment_end)) {
        inside_comment = false;
        next_line();
        return true; // end of multi line comment, just next line.
      }

      if (boost::contains(trimmed_line, Symbol::comment_end)) [[unlikely]] {
        throw_error(COLUMBUS_LOCATION, "Invalid multiline comment ending.");
      }

      next_nonempty_line();
      continue; // inside multi line comment, can skip empty comment lines.
    }

    if (line_ == Symbol::comment_begin) {
      inside_comment = true;
      next_nonempty_line();
      continue; // started multi line comment, can skip empty comment lines.
    }

    if (boost::starts_with(line_, Symbol::comment_begin)) {
      auto trimmed_line = trimmed(line_);
      if (boost::ends_with(trimmed_line, Symbol::comment_end)) [[likely]] {
        next_line();
        return true; // end of single line comment, just next line.
      }

      if (boost::contains(trimmed_line, Symbol::comment_end)) { throw_error(COLUMBUS_LOCATION, "Invalid comment."); }
      throw_error(COLUMBUS_LOCATION, "Invalid comment beginning.");
    }

    return false; // called on a non comment line
  }

  return false;
}

std::optional<std::string_view> RulMDParser::try_next_indented_line() {
  next_noncomment_line(); // only skip comments, keep empty lines
  if (file_) { return to_indented_line(line_); }
  return {};
}

std::optional<std::string_view> RulMDParser::try_next_list_item() {
  next_data_line();
  if (file_) {
    if (auto list_item_text = to_list_item(line_)) {
      if (list_item_text->empty()) { throw_error(COLUMBUS_LOCATION, "Empty list item"); }
      return list_item_text;
    }
  }
  return {};
}

bool RulMDParser::try_get_bool(std::string_view line_part) {
  if (line_part.empty()) [[unlikely]] { throw_error(COLUMBUS_LOCATION, "Empty boolean value"); }
  if (auto summarized = to_boolean(line_part)) [[likely]] { return summarized.value(); }
  throw_error(COLUMBUS_LOCATION, "Unexpected value for boolean");
}

RulHandler::RulBoolean RulMDParser::try_get_rul_boolean(std::string_view line_part) {
  return try_get_bool(line_part) ? RulHandler::RulBoolean::rulTrue : RulHandler::RulBoolean::rulFalse;
}

void RulMDParser::throw_error(const std::string &location, const std::string &message) {
  auto full_message = file_path_ + ':';
  full_message += std::to_string(line_number_);
  full_message += ": error: ";
  full_message += message;
  full_message += '\n';
  full_message += line_;
  throw columbus::Exception(location, full_message);
}

void RulMDParser::parse_indented_text_block(RulMDString &md_string) {
  md_string.clear();
  while (auto line_without_indent = try_next_indented_line()) {
    md_string.append_line(line_without_indent.value());
  }
  md_string.trim();
}

void RulMDParser::parse_indented_text_block(std::string &string) {
  string.clear();
  while (auto line_without_indent = try_next_indented_line()) {
    string += line_without_indent.value();
    string += '\n';
  }
  common::trim(string);
}

void RulMDParser::parse_tool_description(std::map<std::string, std::map<std::string, RulMDString>> &tool_description) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 2) {
      const auto heading_text = get_heading_text(heading_level, line_);
      auto &current_tool_description = tool_description.try_emplace(std::string(heading_text)).first->second;
      parse_tool_description_config(current_tool_description);
    } else if (heading_level > 2) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "Expected heading 2 or less here");
    } else {
      return;
    }
  }
}

void RulMDParser::parse_tool_description_config(std::map<std::string, RulMDString> &tool_description_config) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 3) {
      const auto heading_text = get_heading_text(heading_level, line_);

      if (const auto key_value = to_key_value(heading_text); key_value.has_value()) {
        const auto [key, value] = key_value.value();
        auto [tool_desc_it, inserted] = tool_description_config.try_emplace(std::string(key), value);
        if (!inserted) { tool_desc_it->second = value; }
        next_data_line();
      } else if (heading_text == Keyword::tool_description_config_description) {
        auto [tool_desc_desc_it, inserted] =
            tool_description_config.try_emplace(std::string(Keyword::tool_description_config_description));
        auto &md_string = tool_desc_desc_it->second;
        parse_indented_text_block(md_string);
      } else [[unlikely]] {
        throw_error(COLUMBUS_LOCATION, "Unknown heading 3 here");
      }
    } else if (heading_level > 3) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "Expected heading 3 or less here");
    } else {
      return;
    }
  }
}

void RulMDParser::parse_includes(RulHandler::RulData &rul_data) {
  while (auto list_item_text = try_next_list_item()) {
    RulMDParser included_rul((working_directory_ / list_item_text.value()).string());
    included_rul.parse_into(rul_data);
  }
}

void RulMDParser::parse_metrics(std::map<std::string, RulHandler::RulMetric> &metrics,
                                const ExtraMetricsContext &extra_context) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 2) {
      const auto heading_text = get_heading_text(heading_level, line_);
      if (heading_text.empty()) [[unlikely]] { throw_error(COLUMBUS_LOCATION, "Empty metric name"); }
      auto metric_it = metrics.try_emplace(std::string(heading_text)).first;
      parse_metric(metric_it->second, {extra_context.redefines, extra_context.original_id_rule_id,
                                       extra_context.tag_store, metric_it->first});
    } else if (heading_level > 2) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "Expected heading 2 or less here");
    } else {
      return;
    }
  }
}

void RulMDParser::parse_metric(RulHandler::RulMetric &metric, const ExtraMetricContext &extra_context) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 3) {
      const auto heading_text = get_heading_text(heading_level, line_);

      const auto [conf, maybe_redef] = to_conf_redefine(heading_text);
      if (conf.empty()) [[unlikely]] { throw_error(COLUMBUS_LOCATION, "Empty configuration name"); }

      auto config_it = metric.configs.try_emplace(std::string(conf)).first;
      auto &config = config_it->second;
      config.group = "false";

      auto &lang = config.langs.try_emplace(std::string("eng")).first->second;
      lang.description.clear();

      constexpr std::string_view default_conf = "Default";
      if (maybe_redef.has_value()) {
        const auto &redef = maybe_redef.value();
        if (redef.empty()) [[unlikely]] { throw_error(COLUMBUS_LOCATION, "Redefine arrow with empty right side"); }
        auto [redef_it, redef_inserted] = extra_context.redefines.try_emplace(std::string(conf), redef);
        if (!redef_inserted) {
          if (redef_it->second == default_conf) {
            redef_it->second = redef;
          } else if (redef_it->second != redef) [[unlikely]] {
            throw_error(COLUMBUS_LOCATION, "Conflicting redefine");
          }
        }
      } else if (conf != default_conf) {
        extra_context.redefines.try_emplace(std::string(conf), default_conf);
      }

      parse_metric_config(config, lang, extra_context);
    } else if (heading_level > 3) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "Excepted heading 3 or less here");
    } else {
      return;
    }
  }
}

void RulMDParser::parse_metric_config(RulHandler::RulConfiguration &config, RulHandler::RulLang &lang,
                                      const ExtraMetricContext &extra_context) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 4) {
      const auto heading_text = get_heading_text(heading_level, line_);

      if (heading_text == Keyword::metric_config_settings) {
        parse_metric_config_settings(config.settings);
      } else if (heading_text == Keyword::metric_config_calculated) {
        parse_metric_config_calculated(config.calculated);
      } else if (heading_text == Keyword::metric_config_tags) {
        parse_metric_config_tags(config, extra_context.tag_store);
      } else if (heading_text == Keyword::metric_config_help_text) {
        parse_indented_text_block(lang.helpText);
      } else if (heading_text == Keyword::metric_config_warning_text) {
        parse_indented_text_block(lang.warningText);
      } else {
        const auto key_value = to_key_value(heading_text);
        if (!key_value.has_value()) [[unlikely]] { throw_error(COLUMBUS_LOCATION, "Unexpected name for heading 4"); }

        const auto [key, value] = key_value.value();
        if (key == Keyword::metric_config_enabled) {
          config.enabled = try_get_rul_boolean(value);
          next_data_line();
        } else if (key == Keyword::metric_config_numeric_type) {
          config.numeric = try_get_rul_boolean(value);
          next_data_line();
        } else if (key == Keyword::metric_config_visible) {
          config.visiable = try_get_rul_boolean(value);
          next_data_line();
        } else if (key == Keyword::metric_config_warning) {
          lang.warning = try_get_rul_boolean(value);
          next_data_line();
        } else if (key == Keyword::metric_config_display_name) {
          lang.displayName = value;
          next_data_line();
        } else if (key == Keyword::metric_config_original_id) {
          config.originalId = value;
          extra_context.original_id_rule_id.try_emplace(config.originalId, extra_context.metric_name);
          next_data_line();
        } else [[unlikely]] {
          throw_error(COLUMBUS_LOCATION, "Unexpected key for key = value heading 4");
        }
      }
    } else if (heading_level > 4) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "Expected heading 4 or less here");
    } else {
      return;
    }
  }
}

void RulMDParser::parse_metric_config_settings(std::map<std::string, RulHandler::RulSetting> &settings) {
  while (auto list_item_text = try_next_list_item()) {
    const auto key_value = to_key_value(list_item_text.value());
    if (!key_value.has_value()) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "Expected key = value list elements for Settings here");
    }
    auto &setting = settings.try_emplace(std::string(key_value->first)).first->second;
    setting.text = key_value->second;
    setting.editable = RulHandler::RulBoolean::rulTrue;
  }
}

void RulMDParser::parse_metric_config_calculated(std::set<std::string> &calculated) {
  while (auto list_item_text = try_next_list_item()) {
    calculated.emplace(list_item_text.value());
  }
}

void RulMDParser::parse_metric_config_tags(RulHandler::RulConfiguration &rul_config, TagStore &tag_store) {
  while (auto list_item_text = try_next_list_item()) {
    auto tag = tag_store.create_or_get(std::string(list_item_text.value()));
    RulHandler::tryAddTagForConfig(rul_config, std::move(tag));
  }
}

void RulMDParser::parse_tag_metadata(TagStore &tag_store) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 2) {
      const auto heading_text = get_heading_text(heading_level, line_);

      auto &tag_kind_metadata = tag_store.metadata_store().try_add_kind(std::string(heading_text));
      parse_tag_metadata_kind(tag_kind_metadata);
    } else if (heading_level > 2) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "Should be only heading level 2 or less here");
    } else {
      return;
    }
  }
}

void RulMDParser::parse_tag_metadata_kind(TagKindMetadataContainer &tag_kind_metadata_container) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 5) {
      const auto heading_text = get_heading_text(heading_level, line_);

      if (heading_text == Keyword::tag_metadata_description) {
        auto &tag_kind_metadata_desc = tag_kind_metadata_container.kind_metadata_ref().description;
        parse_indented_text_block(tag_kind_metadata_desc);
      } else [[unlikely]] {
        throw_error(COLUMBUS_LOCATION, "Unknown heading 5 name inside kind matadata");
      }
    } else if (heading_level == 3) {
      const auto heading_text = get_heading_text(heading_level, line_);
      auto &tag_value_metadata_container = tag_kind_metadata_container.try_add_value(std::string(heading_text));
      parse_tag_metadata_value(tag_value_metadata_container);
    } else if (heading_level > 5) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "There is no heading level more than 5 inside tag kind metadata");
    } else {
      return;
    }
  }
}

void RulMDParser::parse_tag_metadata_value(TagValueMetadataContainer &tag_value_metadata_container) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 5) {
      const auto heading_text = get_heading_text(heading_level, line_);
      auto &tag_value_metadata = tag_value_metadata_container.value_metadata_ref();

      if (heading_text == Keyword::tag_metadata_description) {
        auto &tag_value_metadata_desc = tag_value_metadata.description;
        parse_indented_text_block(tag_value_metadata_desc);
      } else {
        const auto key_value = to_key_value(heading_text);
        if (!key_value.has_value()) [[unlikely]] {
          throw_error(COLUMBUS_LOCATION, "Unknown heading 5 name inside kind matadata");
        }

        const auto [heading_key, heading_value] = key_value.value();
        if (heading_key == Keyword::tag_metadata_summarized) {
          tag_value_metadata.summarized = try_get_bool(heading_value);
          next_data_line();
        } else if (heading_key == Keyword::tag_metadata_url) {
          tag_value_metadata.url = heading_value;
          next_data_line();
        }
      }
    } else if (heading_level == 4) {
      const auto heading_text = get_heading_text(heading_level, line_);
      auto &tag_detail_metadata_container = tag_value_metadata_container.try_add_detail(std::string(heading_text));
      parse_tag_metadata_detail(tag_detail_metadata_container);
    } else if (heading_level > 5) [[unlikely]] {
      throw_error(COLUMBUS_LOCATION, "There is no heading level more than 5 inside tag value metadata");
    } else {
      return;
    }
  }
}

void RulMDParser::parse_tag_metadata_detail(TagDetailMetadataContainer &tag_detail_metadata_container) {
  next_data_line();
  while (file_) {
    if (const auto heading_level = get_heading_level(line_); heading_level == 5) {
      const auto heading_text = get_heading_text(heading_level, line_);
      auto &tag_value_metadata = tag_detail_metadata_container.detail_metadata_ref();

      if (heading_text == Keyword::tag_metadata_description) {
        auto &tag_value_metadata_desc = tag_value_metadata.description;
        parse_indented_text_block(tag_value_metadata_desc);
      } else {
        const auto heading_key_value = to_key_value(heading_text);
        if (!heading_key_value.has_value()) [[unlikely]] {
          throw_error(COLUMBUS_LOCATION, "Unknown heading 5 name inside kind matadata");
        }

        const auto [heading_key, heading_value] = heading_key_value.value();
        if (heading_key == Keyword::tag_metadata_summarized) {
          tag_value_metadata.summarized = try_get_bool(heading_value);
          next_data_line();
        } else if (heading_key == Keyword::tag_metadata_url) {
          tag_value_metadata.url = heading_value;
          next_data_line();
        }
      }
    } else if (heading_level > 5) {
      throw_error(COLUMBUS_LOCATION, "There is no heading level more than 5 inside tag detail metadata");
    } else {
      return;
    }
  }
}

void RulMDWriter::write_metric_config_key_value(std::ofstream &file, std::string_view key,
                                                RulHandler::RulBoolean value) {
  if (value == RulHandler::RulBoolean::rulUndefined) { return; }
  file << "#### " << key << Symbol::equals
       << (value == RulHandler::RulBoolean::rulTrue ? Keyword::true_ : Keyword::false_) << '\n';
}

void RulMDWriter::write_metric_config_key_value(std::ofstream &file, std::string_view key, const std::string &value) {
  if (value == RulHandler::_empty_string) { return; }
  file << "#### " << key << Symbol::equals << value << '\n';
}

void RulMDWriter::write_indented_text_block(std::ofstream &file, const std::string &string) {
  if (string.empty()) { return; }
  if (string.front() != '\n') { file << Symbol::text_block_indent << string.front(); }
  for (auto char_it = ++string.begin(); char_it != string.end(); ++char_it) {
    if (*(char_it - 1) == '\n' && *char_it != '\n') { file << Symbol::text_block_indent; }
    file << *char_it;
  }
  file << '\n' << '\n';
}

void RulMDWriter::write_tool_description(
    std::ofstream &file, const std::map<std::string, std::map<std::string, RulMDString>> &tool_description) {
  if (tool_description.empty()) { return; }
  file << "# " << Keyword::tool_description << '\n';
  for (const auto &[config_name, config] : tool_description) {
    file << "## " << config_name << '\n';
    for (const auto &[key, value] : config) {
      file << "### " << key;
      if (key == Keyword::tool_description_config_description) {
        file << '\n';
        write_indented_text_block(file, value.get_raw_format());
      } else {
        file << Symbol::equals << value.get_raw_format() << '\n';
      }
    }
  }
  file << '\n';
}

void RulMDWriter::write_tag_metadata_description(std::ofstream &file, const std::string &description) {
  if (description.empty()) { return; }
  file << "##### " << Keyword::tag_metadata_description << '\n';
  write_indented_text_block(file, description);
}

void RulMDWriter::write_tag_metadata_summarized(std::ofstream &file, bool summarized) {
  if (summarized == TagValueMetadata::summarized_default) { return; }
  file << "##### " << Keyword::tag_metadata_summarized << Symbol::equals
       << (summarized ? Keyword::true_ : Keyword::false_) << '\n';
}

void RulMDWriter::write_tag_metadata_url(std::ofstream &file, const std::string &url) {
  if (url.empty()) { return; }
  file << "##### " << Keyword::tag_metadata_url << Symbol::equals << url << '\n';
}

void RulMDWriter::write_tag_metadata(std::ofstream &file, const TagStore &tag_store) {
  const auto &tag_metadata_map = tag_store.metadata_store().kind_metadata_map();
  if (tag_metadata_map.empty()) { return; }

  file << "# " << Keyword::tag_metadata << '\n';
  for (const auto &[kind_key, kind_value] : tag_metadata_map) {
    file << "## " << kind_key << '\n';

    const auto &kind_metadata = kind_value.kind_metadata_ref();
    write_tag_metadata_description(file, kind_metadata.description.get_raw_format());

    for (const auto &[value_key, value_value] : kind_value.value_metadata_map()) {
      file << "### " << value_key << '\n';

      const auto &value_metadata = value_value.value_metadata_ref();
      write_tag_metadata_summarized(file, value_metadata.summarized);
      write_tag_metadata_url(file, value_metadata.url);
      write_tag_metadata_description(file, value_metadata.description.get_raw_format());

      for (const auto &[detail_key, detail_value] : value_value.detail_metadata_map()) {
        file << "#### " << detail_key << '\n';

        const auto &detail_metadata = detail_value.detail_metadata_ref();
        write_tag_metadata_summarized(file, detail_metadata.summarized);
        write_tag_metadata_url(file, detail_metadata.url);
        write_tag_metadata_description(file, detail_metadata.description.get_raw_format());
      }
    }
  }
}

void RulMDWriter::write_metric_config_settings(std::ofstream &file,
                                               const std::map<std::string, RulHandler::RulSetting> &settings) {

  if (settings.empty()) { return; }
  file << "#### " << Keyword::metric_config_settings << '\n';
  for (const auto &[setting_name, setting] : settings) {
    file << Symbol::list_item << ' ' << setting_name << Symbol::equals;
    for (const char c : trimmed(setting.text)) {
      if (c == '\r' || c == '\n') { continue; }
      file << c;
    }
    file << '\n';
  }
  file << '\n';
}

#ifdef LEGACY_RUL_CONVERSION
void RulMDWriter::write_metric_config_tags(std::ofstream &file, const RulHandler::RulConfiguration &config,
                                           const RulHandler::RulData &rul_data) {
  file << "#### " << Keyword::metric_config_tags << '\n';
  const auto tool_id = rul_data.toolDescription.at("Default").at("ID").get_raw_format();
  file << Symbol::list_item << ' ' << "/tool/";
  static constexpr std::array sm_tools = {"MET",         "DCF", "VulnerabilityHunter", "RTEHunter", "AndroidHunter",
                                          "FaultHunter", "UDM"};
  if (std::find(sm_tools.begin(), sm_tools.end(), tool_id) != sm_tools.end()) { file << "SourceMeter/"; }
  file << tool_id << '\n';
  for (const auto &conf : RulHandler::RulConfigInheritanceView(config)) {
    if (conf.groupMember.empty()) { continue; }

    assert(conf.groupMember.size() == 1);
    file << Symbol::list_item << ' ' << "/general/" << *conf.groupMember.begin() << '\n';
  }

  if (config.groupMember.empty()) {
    if (auto *parent = config.parentConfig) {
      if (!parent->groupMember.empty() &&
          rul_data.metrics.at(*parent->groupMember.begin()).configs.at("Default").group != "summarized") {
        file << Symbol::list_item << ' ' << "/internal/csv_column\n";
      }
    }
  } else {
    if (rul_data.metrics.at(*config.groupMember.begin()).configs.at("Default").group != "summarized") {
      file << Symbol::list_item << ' ' << "/internal/csv_column\n";
    }
  }
  file << '\n';
}

#else

void RulMDWriter::write_metric_config_tags(std::ofstream &file, const std::set<std::shared_ptr<Tag>> &tags) {
  if (tags.empty()) { return; }
  file << "#### " << Keyword::metric_config_tags << '\n';
  for (const auto &tag_ptr : tags) {
    file << Symbol::list_item << ' ' << tag_ptr->get_full_name() << '\n';
  }
  file << '\n';
}

#endif

void RulMDWriter::write_metric_config_calculated(std::ofstream &file, const std::set<std::string> &calculated) {
  if (calculated.empty()) { return; }
  file << "#### " << Keyword::metric_config_calculated << '\n';
  for (const auto &calc : calculated) {
    file << Symbol::list_item << ' ' << calc << '\n';
  }
  file << '\n';
}

void RulMDWriter::write_metric_config_help_text(std::ofstream &file, const std::string &help_text) {
  if (help_text == RulHandler::_empty_string) { return; }

  file << "#### " << Keyword::metric_config_help_text << '\n';
#ifdef LEGACY_RUL_CONVERSION
  boost::asio::io_service ios;
  boost::process::opstream in;
  std::future<std::string> out;
  boost::process::child pandoc("pandoc --from html --to markdown_github", boost::process::std_out > out,
                               boost::process::std_in < in, ios);
  in << help_text;
  in.close();
  in.pipe().close();

  ios.run();

  auto markdown_help_text = out.get();
#ifdef _WIN32
  // On Windows pandoc gives it's output with '\r\n' line endings, (after
  // pandoc version 2, the --eof=lf flag can be used instead of this) but
  // the standard lib will convert '\n' to '\r\n' (on windows) when
  // outputting to a text file, so it will end up as '\r\r\n' which going
  // to be shown as double newlines (on windows).
  boost::replace_all(markdown_help_text, "\r\n", "\n");
#endif
  write_indented_text_block(file, markdown_help_text);
#else
  write_indented_text_block(file, help_text);
#endif
}

void RulMDWriter::write_metrics(std::ofstream &file, const RulHandler::RulData &rul_data) {
  const auto &metrics = rul_data.metrics;
  const auto &redefines = rul_data.redefines;

  if (metrics.empty()) { return; }
  file << "# " << Keyword::metrics << '\n';
  for (const auto &[metric_name, metric] : metrics) {
#ifdef LEGACY_RUL_CONVERSION
    bool wrote_metric_name = false;
#else
    file << "## " << metric_name << '\n';
#endif

    for (const auto &[config_name, config] : metric.configs) {
#ifdef LEGACY_RUL_CONVERSION
      const auto is_group = [config_inheritance = RulHandler::RulConfigInheritanceView(config)]() {
        for (const auto &conf : config_inheritance) {
          if (conf.group == "false") { return false; }
          if (conf.group != RulHandler::_empty_string) { return true; }
        }
        return false;
      }();
      // don't write out groups, metrics use tags now
      if (is_group) { break; }

      // to prevent writing out metric that only have group configs
      if (!wrote_metric_name) {
        file << "## " << metric_name << '\n';
        wrote_metric_name = true;
      }
#endif
      file << "### " << config_name;
      if (auto redefine_entry_it = redefines.find(config_name); redefine_entry_it != redefines.end()) {
        file << ' ' << Symbol::redefine << ' ' << redefine_entry_it->second;
      }
      file << '\n';

      write_metric_config_key_value(file, Keyword::metric_config_original_id, config.originalId);
      write_metric_config_key_value(file, Keyword::metric_config_enabled, config.enabled);
      write_metric_config_key_value(file, Keyword::metric_config_numeric_type, config.numeric);
      write_metric_config_key_value(file, Keyword::metric_config_visible, config.visiable);

      if (const auto lang_it = config.langs.find("eng"); lang_it != config.langs.end()) {
        write_metric_config_key_value(file, Keyword::metric_config_warning, lang_it->second.warning);
        write_metric_config_key_value(file, Keyword::metric_config_display_name, lang_it->second.displayName);

        if (const auto &warning_text = lang_it->second.warningText; warning_text != RulHandler::_empty_string) {
          file << "#### " << Keyword::metric_config_warning_text << '\n';
          write_indented_text_block(file, warning_text);
        }

        write_metric_config_help_text(file, lang_it->second.helpText.get_raw_format());
      }

      write_metric_config_calculated(file, config.calculated);
#ifdef LEGACY_RUL_CONVERSION
      write_metric_config_tags(file, config, rul_data);
#else
      write_metric_config_tags(file, config.tags);
#endif
      write_metric_config_settings(file, config.settings);
    }
    file << '\n';
  }
  file << '\n';
}

void RulMDWriter::write(const std::string &file_path, const RulHandler::RulData &rul_data) {
  std::ofstream file(file_path);
  write_tool_description(file, rul_data.toolDescription);
  write_tag_metadata(file, rul_data.tagStore);
  write_metrics(file, rul_data);
}
} // namespace columbus::rul
