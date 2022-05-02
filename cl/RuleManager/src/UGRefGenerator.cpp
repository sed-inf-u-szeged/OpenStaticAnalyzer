#include "../inc/UGRefGenerator.h"
#include "../inc/MD.h"
#include "rul/inc/RulTags.h"

#include <algorithm>
#include <array>
#include <tuple>
#include <utility>

#include <rul/inc/RulMDString.h>

using columbus::rul::RulHandler;
using columbus::rul::RulMDString;
using columbus::rul::Tag;

namespace {
template <typename T>
void append_op(std::string &dest, const T &what) {
  dest += what;
}

template <typename T>
void append_op(std::ostream &dest, const T &what) {
  dest << what;
}

template <typename Out>
void append_id_text(Out &dest, const std::string &id) {
  if (!id.empty()) { append_op(dest, "ref-"); }

  for (const auto ch : id) {
    if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('0' <= ch && ch <= '9') || ch == '-' || ch == '_' ||
        ch == ':' || ch == '.') {
      append_op(dest, ch);
    } else {
      append_op(dest, '-');
    }
  }
}

template <typename Out>
void append_heading_id(Out &dest, const std::string &id) {
  append_op(dest, " {#");
  append_id_text(dest, id);
  append_op(dest, "}");
}

template <typename Out, typename Range>
void append_escaped(Out &dest, const Range &text) {
  for (const auto ch : text) {
    switch (ch) {
    case '\\':
      append_op(dest, "\\\\");
      break;
    case '@':
      append_op(dest, "\\@");
      break;
    case '*':
      append_op(dest, "\\*");
      break;
    case '_':
      append_op(dest, "\\_");
      break;
    default:
      append_op(dest, ch);
    }
  }
}

template <typename T>
void append_link_to_id(T &dest, const std::string &text, const std::string &id) {
  append_op(dest, '[');
  append_escaped(dest, text);
  append_op(dest, "](#");
  append_id_text(dest, id);
  append_op(dest, ')');
}

std::string make_link_to_id(const std::string &text, const std::string &id) {
  std::string link;
  constexpr auto extra_char_size = 5U;
  link.reserve(text.size() + id.size() + extra_char_size);
  append_link_to_id(link, text, id);
  return link;
}

template <typename T>
void append_tag_link(T &dest, const Tag &tag) {
  auto tag_last_name = tag.get_last_name();
  if (!tag.get_detail().empty()) { tag_last_name = tag.get_value() + "/" + tag_last_name; }
  append_link_to_id(dest, tag_last_name, tag_last_name);
}

template <typename T>
void append_joined_tag_links(T &dest, const std::set<std::shared_ptr<Tag>> &tags) {
  if (tags.empty()) { return; }

  append_tag_link(dest, **tags.begin());
  for (auto tag_it = ++tags.begin(); tag_it != tags.end(); ++tag_it) {
    append_op(dest, ", ");
    append_tag_link(dest, **tag_it);
  }
}

std::string make_joined_metrics(const std::vector<std::string> &metrics) {
  std::string joined_metrics;
  if (metrics.empty()) { return joined_metrics; }

  append_link_to_id(joined_metrics, metrics.front(), metrics.front());
  for (auto metric_it = ++metrics.begin(); metric_it != metrics.end(); ++metric_it) {
    joined_metrics += ", ";
    append_link_to_id(joined_metrics, *metric_it, *metric_it);
  }
  return joined_metrics;
}

std::string make_joined_tag_links(const std::set<std::shared_ptr<Tag>> &tags) {
  std::string joined_tags;
  append_joined_tag_links(joined_tags, tags);
  return joined_tags;
}

std::set<std::shared_ptr<Tag>> public_tags(RulHandler::RulConfigTagsView tags_view) {
  std::set<std::shared_ptr<Tag>> publics;
  std::copy_if(tags_view.begin(), tags_view.end(), std::inserter(publics, publics.end()),
               [](const auto &tag) { return tag->get_kind() != "internal"; });
  return publics;
}

void append_documentation(std::ostream &dest, std::string_view doc) {
  if (RulHandler::isEmptyString(doc)) {
    dest << "No documentation is available.\n\n";
  } else {
    dest << doc << "\n\n";
  }
}
} // namespace

UGRefGenerator::UGRefGenerator(const std::string &output_file_path, std::string conf, std::string lang)
    : md_file_(output_file_path), conf_(std::move(conf)), lang_(std::move(lang)) {}

void UGRefGenerator::write_metrics_part(const std::vector<std::string> &md_file_paths) {
  for (const auto &md_file_path : md_file_paths) {
    RulHandler rulHandler(md_file_path, conf_, lang_);
    const auto &tool_id = rulHandler.getToolDescription("ID");

    std::set<std::string> groups;
    rulHandler.getGroupIdList(groups);
    std::vector<std::string> rule_ids;
    rulHandler.getRuleIdList(rule_ids);
    std::vector<MetricRulData> rul_data;
    rul_data.reserve(rule_ids.size());
    std::set<std::string> calculated_for_header;
    static constexpr std::array components_to_merge = {"Annotation", "Class", "Enum", "Interface", "Union", "Struct"};
    static constexpr auto component_to_merge_into = "Class";

    for (const auto &id : rule_ids) {
      if (groups.find(id) != groups.end() || !rulHandler.getIsEnabled(id)) { continue; }

      const auto &rd = rul_data.emplace_back(
          MetricRulData{id, rulHandler.getDisplayName(id), rulHandler.getHelpText(id, RulMDString::raw_format_tag),
                        public_tags(rulHandler.getAllTags(id)), rulHandler.getCalculatedForSet(id)});

      summarize_collection_tags(tool_id, id, rd.public_tags);

      for (const auto &component : rd.calculated_for) {
        if (std::find(components_to_merge.begin(), components_to_merge.end(), component) != components_to_merge.end()) {
          calculated_for_header.emplace(component_to_merge_into);
        } else {
          calculated_for_header.insert(component);
        }
      }
    }

    md_file_ << "## Reference of ";
    if (tool_id == "MET" || tool_id == "RPG2Metrics") {
      md_file_ << "source code metrics";
      append_heading_id(md_file_, "OpenStaticAnalyzer/MET");
    } else if (tool_id == "DCF") {
      md_file_ << "code duplication metrics";
      append_heading_id(md_file_, "OpenStaticAnalyzer/DCF");
    } else {
      md_file_ << tool_id;
      append_heading_id(md_file_, tool_id);
    }
    md_file_ << "\n\n";

    append_documentation(md_file_, rulHandler.getToolDescription("Description"));

    std::vector<std::string> header;
    header.reserve(2 + calculated_for_header.size());
    header.emplace_back("Metric name");
    header.emplace_back("Abbreviation");
    header.insert(header.end(), calculated_for_header.begin(), calculated_for_header.end());
    header.emplace_back("Tags");

    // java: CloneInstance CloneClass Method Enum Annotation Interface Class Package File Component
    // cpp: CloneInstance CloneClass Function Method Enum Union Structure Class Namespace Component
    // python: CloneInstance CloneClass Function Method Class Module Package Component
    // rpg: CloneInstance CloneClass Subroutine Procedure Program System Component

    MDTable table(header);
    for (const auto &rd : rul_data) {
      std::vector<std::string> row;
      row.reserve(header.size());
      row.push_back(make_link_to_id(rd.name, rd.id));
      row.push_back(rd.id);
      for (const auto &calc_element : calculated_for_header) {
        if (rd.calculated_for.find(calc_element) != rd.calculated_for.end() ||
            (calc_element == component_to_merge_into &&
             std::any_of(components_to_merge.begin(), components_to_merge.end(), [&](const auto &component) {
               return rd.calculated_for.find(component) != rd.calculated_for.end();
             }))) {
          row.emplace_back("X");
        } else {
          row.emplace_back();
        }
      }
      row.push_back(make_joined_tag_links(rd.public_tags));
      table.addRow(row);
    }
    md_file_ << "The following table summarizes the metrics, their "
                "abbreviations and their correspondence to different "
                "source code element kinds:\n\n";
    md_file_ << table;

    write_definitions(rul_data);
  }
}

void UGRefGenerator::write_analyzer_part(const std::vector<std::string> &md_file_paths) {
  md_file_ << "## Reference of OpenStaticAnalyzer coding rule violations";
  append_heading_id(md_file_, "OpenStaticAnalyzer");
  md_file_ << '\n';

  std::vector<std::pair<std::string, std::vector<ToolRulData>>> tool_rul_data;
  tool_rul_data.reserve(md_file_paths.size());
  std::vector<RulHandler> rul_handlers;
  rul_handlers.reserve(md_file_paths.size());

  for (const auto &md_file_path : md_file_paths) {
    auto &rulHandler = rul_handlers.emplace_back(md_file_path, conf_, lang_);
    std::set<std::string> groups;
    rulHandler.getGroupIdList(groups);
    std::vector<std::string> rule_ids;
    rulHandler.getRuleIdList(rule_ids);
    auto &[tool_id, rul_data] = tool_rul_data.emplace_back(
        std::piecewise_construct, std::forward_as_tuple(rulHandler.getToolDescription("ID")), std::forward_as_tuple());
    rul_data.reserve(rule_ids.size());
    for (const auto &id : rule_ids) {
      if (groups.find(id) != groups.end() || !rulHandler.getIsEnabled(id)) { continue; }

      const auto &rd = rul_data.emplace_back(
          ToolRulData{id, rulHandler.getDisplayName(id), rulHandler.getSettingValue(id, "Priority"),
                      rulHandler.getHelpText(id, RulMDString::raw_format_tag), public_tags(rulHandler.getAllTags(id)),
                      rulHandler.getCalculatedForSet(id)});

      summarize_collection_tags(tool_id, id, rd.public_tags);
    }

    md_file_ << "### " << tool_id << " Description";
    append_heading_id(md_file_, "OpenStaticAnalyzer/" + tool_id);
    md_file_ << "\n\n";
    append_documentation(md_file_, rulHandler.getToolDescription("Description"));
  }

  std::vector<std::string> header;
  header.reserve(4);
  header.emplace_back("Name");
  header.emplace_back("Abbreviation");
  header.emplace_back("Prio.");
  header.emplace_back("Tags");

  MDTable table(header);
  for (const auto &[tool_name, data] : tool_rul_data) {
    for (const auto &rd : data) {
      std::vector<std::string> row;
      row.reserve(4);
      row.push_back(make_link_to_id(rd.name, rd.id));
      row.push_back(rd.id);
      row.push_back(rd.priority);
      row.push_back(make_joined_tag_links(rd.public_tags));
      table.addRow(row);
    }
  }

  md_file_ << "The following table contains the enabled rules and their "
              "priorities:\n\n";
  md_file_ << table;

  std::vector<ToolRulData> flat_rul_data;
  for (auto &[tool_name, data] : tool_rul_data) {
    for (auto &rd : data) {
      flat_rul_data.push_back(std::move(rd));
    }
  }

  write_definitions(flat_rul_data);
}

void UGRefGenerator::write_thirdparty_part(const std::vector<std::string> &md_file_paths) {
  for (const auto &md_file_path : md_file_paths) {
    RulHandler rulHandler(md_file_path, conf_, lang_);
    const auto &tool_id = rulHandler.getToolDescription("ID");

    std::set<std::string> groups;
    rulHandler.getGroupIdList(groups);
    std::vector<std::string> rule_ids;
    rulHandler.getRuleIdList(rule_ids);
    std::vector<ToolRulData> rul_data;
    rul_data.reserve(rule_ids.size());
    for (const auto &id : rule_ids) {
      if (groups.find(id) != groups.end() || !rulHandler.getIsEnabled(id)) { continue; }

      const auto &rd = rul_data.emplace_back(
          ToolRulData{id, rulHandler.getDisplayName(id), rulHandler.getSettingValue(id, "Priority"),
                      rulHandler.getHelpText(id, RulMDString::raw_format_tag), public_tags(rulHandler.getAllTags(id)),
                      rulHandler.getCalculatedForSet(id)});
      summarize_collection_tags(tool_id, id, rd.public_tags);
    }

    md_file_ << "## Reference of " << tool_id << " coding rule violations";
    append_heading_id(md_file_, tool_id);
    md_file_ << "\n\n";
    append_documentation(md_file_, rulHandler.getToolDescription("Description"));

    std::vector<std::string> header;
    header.reserve(4);
    header.emplace_back("Name");
    header.emplace_back("Abbreviation");
    header.emplace_back("Prio.");
    header.emplace_back("Tags");

    MDTable table(header);
    for (const auto &rd : rul_data) {
      std::vector<std::string> row;
      row.reserve(4);
      row.push_back(make_link_to_id(rd.name, rd.id));
      row.push_back(rd.id);
      row.push_back(rd.priority);
      row.push_back(make_joined_tag_links(rd.public_tags));
      table.addRow(row);
    }
    md_file_ << "The following table contains the enabled rules and their "
                "priorities:\n\n";
    md_file_ << table;

    write_definitions(rul_data);
  }
}

void UGRefGenerator::write_tags_summary() {
  if (const auto &[collection_desc, value_map] = collection_tags_summary_; !value_map.empty()) {
    md_file_ << "## Collection Tags\n\n";
    append_documentation(md_file_, collection_desc);
    for (const auto &[value, value_desc_detail_map_pair] : value_map) {
      const auto &[value_desc, value_link, detail_map] = value_desc_detail_map_pair;

      md_file_ << "### " << value << '\n';
      append_documentation(md_file_, value_desc);
      if (!value_link.empty()) { md_file_ << "[More info](" << value_link << ")\n\n"; }

      std::vector<std::string> header;
      header.reserve(2);
      header.emplace_back("Name");
      header.emplace_back("Rules");
      MDTable table(header);
      for (const auto &[detail, detail_desc_metrics_map_pair] : detail_map) {
        const auto &[detail_desc, detail_link, marked_metrics] = detail_desc_metrics_map_pair;
        std::vector<std::string> first_row;
        first_row.reserve(2);
        first_row.push_back(make_link_to_id(detail, detail));
        first_row.push_back(make_joined_metrics(marked_metrics));
        table.addRow(first_row);
      }
      md_file_ << table << "\n\n";
      md_file_ << "<div class=\"definitions\">Definitions</div>\n";
      for (const auto &[detail, detail_desc_metrics_map_pair] : detail_map) {
        md_file_ << "#### ";
        append_escaped(md_file_, detail);
        append_heading_id(md_file_, detail);
        md_file_ << "\n\n";

        append_documentation(md_file_, detail_desc_metrics_map_pair.description);

        if (const auto &general_link = detail_desc_metrics_map_pair.link; !general_link.empty()) {
          md_file_ << "[More info](" << general_link << ")\n\n";
        }
      }
    }
  }

  if (const auto &[tools_desc, tool_map, sm_tool_map] = tool_tags_summary_; !tool_map.empty() || !sm_tool_map.empty()) {
    md_file_ << "## Tool Tags\n";
    append_documentation(md_file_, tools_desc);
    std::vector<std::string> header;
    header.reserve(2);
    header.emplace_back("Name");
    header.emplace_back("Rules");
    MDTable table(header);
    for (const auto &[tool_name, metrics_vec] : tool_map) {
      std::vector<std::string> row;
      row.reserve(2);
      row.push_back(make_link_to_id(tool_name, tool_name));
      row.push_back(make_joined_metrics(metrics_vec));
      table.addRow(row);
    }

    if (!sm_tool_map.empty()) {
      {
        std::vector<std::string> row;
        row.reserve(2);
        row.emplace_back(make_link_to_id("OpenStaticAnalyzer", "OpenStaticAnalyzer"));
        row.emplace_back(make_link_to_id("OpenStaticAnalyzer", "OpenStaticAnalyzer"));
        table.addRow(row);
      }

      for (const auto &[tool_name, metrics_vec] : sm_tool_map) {
        std::vector<std::string> row;
        row.reserve(2);
        row.push_back(make_link_to_id(tool_name, tool_name));
        row.push_back(make_joined_metrics(metrics_vec));
        table.addRow(row);
      }
    }

    md_file_ << table << "\n\n";
  }

  if (const auto &[general_desc, general_map] = general_tags_summary_; !general_map.empty()) {
    md_file_ << "## General Tags\n";
    append_documentation(md_file_, general_desc);
    std::vector<std::string> header;
    header.reserve(2);
    header.emplace_back("Name");
    header.emplace_back("Rules");
    MDTable table(header);
    for (const auto &[tag_name, general_desc_metric_vec_pair] : general_map) {
      std::vector<std::string> row;
      row.reserve(2);
      row.push_back(make_link_to_id(tag_name, tag_name));
      row.push_back(make_joined_metrics(general_desc_metric_vec_pair.marked_metrics));
      table.addRow(row);
    }
    md_file_ << table << "\n\n";

    md_file_ << "<div class=\"definitions\">Definitions</div>\n";
    for (const auto &[tag_name, general_desc_metric_vec_pair] : general_map) {
      md_file_ << "#### ";
      append_escaped(md_file_, tag_name);
      append_heading_id(md_file_, tag_name);
      md_file_ << "\n\n";

      append_documentation(md_file_, general_desc_metric_vec_pair.description);
    }
  }
}

template <typename RulData>
void UGRefGenerator::write_definitions(const std::vector<RulData> &rul_data) {
  md_file_ << "<div class=\"definitions\">Definitions</div>\n";

  for (const auto &rd : rul_data) {
    md_file_ << "#### ";
    append_escaped(md_file_, rd.name);
    md_file_ << " (" << rd.id << ")";
    append_heading_id(md_file_, rd.id);
    md_file_ << "\n";
    if (!rd.public_tags.empty()) {
      md_file_ << "Tags: ";
      append_joined_tag_links(md_file_, rd.public_tags);
      md_file_ << "\n\n";
    }

    if (!rd.calculated_for.empty()) {
      md_file_ << "Defined: " << *rd.calculated_for.begin();
      for (auto calc_it = ++rd.calculated_for.begin(); calc_it != rd.calculated_for.end(); ++calc_it) {
        md_file_ << ", " << *calc_it;
      }
      md_file_ << "\n\n";
    }

    append_documentation(md_file_, rd.help_text);
  }
}

void UGRefGenerator::summarize_collection_tags(const std::string &tool_id, const std::string &tool_metric_id,
                                               const std::set<std::shared_ptr<Tag>> &tags) {
  for (const auto &tag : tags) {
    const auto &tag_kind = tag->get_kind();
    const auto &tag_value = tag->get_value();
    const auto &tag_detail = tag->get_detail();
    const auto &tag_kind_desc = tag->get_kind_description().get_raw_format();

    if (tag_kind == "collection") {
      if (auto &saved_collection_desc = collection_tags_summary_.description;
          saved_collection_desc.empty() && !tag_kind_desc.empty()) {
        saved_collection_desc = tag_kind_desc;
      }

      if (!tag_value.empty()) {
        const auto &tag_value_desc = tag->get_value_description().get_raw_format();
        const auto &tag_value_url = tag->get_value_url();
        auto [value_map_it, inserted] = collection_tags_summary_.value_map.try_emplace(
            tag_value, TagValueDescriptionLinkAndDetails{tag_value_desc, tag_value_url});
        if (!inserted) {
          auto &saved_value_desc = value_map_it->second.description;
          if (saved_value_desc.empty() && !tag_value_desc.empty()) { saved_value_desc = tag_value_desc; }
          auto &saved_value_link = value_map_it->second.link;
          if (saved_value_link.empty() && !tag_value_url.empty()) { saved_value_link = tag_value_url; }
        }

        if (!tag_detail.empty()) {
          auto value_detail = tag_value + "/" + tag_detail;
          auto [detail_map_it, inserted] = value_map_it->second.detail_map.try_emplace(
              std::move(value_detail), TagDetailDescriptionLinkAndMarkedMetrics{
                                           tag->get_detail_description().get_raw_format(), tag->get_detail_url()});
          detail_map_it->second.marked_metrics.push_back(tool_metric_id);
        }
      }
    } else if (tag_kind == "tool") {
      if (auto &saved_tool_desc = tool_tags_summary_.description; saved_tool_desc.empty() && !tag_kind_desc.empty()) {
        saved_tool_desc = tag_kind_desc;
      }

      if (!tag_value.empty()) {
        if (tag_value == "OpenStaticAnalyzer") {
          if (!tag_detail.empty()) {
            auto [tool_map_it, inserted] = tool_tags_summary_.sm_tool_map.try_emplace("OpenStaticAnalyzer/" + tag_detail);
            tool_map_it->second.push_back(tool_metric_id);
          }
        } else {
          auto [tool_map_it, inserted] = tool_tags_summary_.tool_map.try_emplace(tag_value);
          if (inserted) { tool_map_it->second.push_back(tag_value); }
        }
      }
    } else if (tag_kind == "general") {
      if (auto &saved_general_desc = general_tags_summary_.description;
          saved_general_desc.empty() && !tag_kind_desc.empty()) {
        saved_general_desc = tag_kind_desc;
      }
      const auto &tag_value_desc = tag->get_value_description().get_raw_format();
      auto [general_map_it, inserted] = general_tags_summary_.general_map.try_emplace(
          tag_value, GeneralTagDescriptionAndMarkedMetrics{tag_value_desc});
      auto &[saved_value_desc, metrics_vec] = general_map_it->second;
      metrics_vec.push_back(tool_metric_id);

      if (!inserted && saved_value_desc.empty() && !tag_value_desc.empty()) { saved_value_desc = tag_value_desc; }
    }
  }
}
