#include "../inc/Metadata.h"
#include "../inc/GraphConstants.h"
#include <graph/inc/Attribute.h>
#include "rul/inc/RulTagMetadataStore.h"
#include "rul/inc/RulTagString.h"

namespace columbus::graphsupport {
void addTagMetadataToGraph(columbus::graph::Graph &graph, const columbus::rul::TagMetadataStore &metadata_store) {
  auto metadata_node = [&graph] {
    auto metadata_node_ = graph.findNode(graphconstants::UID_RUL_TAG_METADATA);
    return metadata_node_ != graph::Graph::invalidNode
               ? metadata_node_
               : graph.createNode(graphconstants::UID_RUL_TAG_METADATA, graphconstants::NTYPE_RUL_METADATA);
  }();

  const auto try_add_description = [&graph](graph::AttributeComposite &attr, const std::string &description) {
    if (description.empty()) { return; }
    attr.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_TAG_METADATA_DESCRIPTION,
                                                  graphconstants::CONTEXT_RUL, description));
  };

  const auto try_add_url = [&graph](graph::AttributeComposite &attr, const std::string &url) {
    if (url.empty()) { return; }
    attr.addAttribute(
        graph.createAttributeString(graphconstants::ATTR_RUL_TAG_METADATA_URL, graphconstants::CONTEXT_RUL, url));
  };

  const auto try_add_summarized = [&graph](graph::AttributeComposite &attr, const bool summarized,
                                           const bool summarized_default) {
    if (summarized == summarized_default) { return; }
    attr.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED,
                                                  graphconstants::CONTEXT_RUL,
                                                  summarized ? graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED_TRUE
                                                             : graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED_FALSE));
  };

  const auto try_remove_empty_attr = [&metadata_node](graph::AttributeComposite &attr) {
    if (attr.getAttributes().hasNext()) { return; }
    metadata_node.deleteAttribute(attr);
  };

  for (const auto &[kind_key, kind_value] : metadata_store.kind_metadata_map()) {
    {
      const auto &kind_metadata_key = rul::create_tag_string({kind_key});
      auto &kind_metadata_attr = static_cast<graph::AttributeComposite &>(
          metadata_node.addAttribute(graph.createAttributeComposite(kind_metadata_key, graphconstants::CONTEXT_RUL)));

      try_add_description(kind_metadata_attr, kind_value.kind_metadata_ref().description.get_escaped_html_format());
      try_remove_empty_attr(kind_metadata_attr);
    }

    for (const auto &[value_key, value_value] : kind_value.value_metadata_map()) {
      {
        const auto &value_metadata_key = rul::create_tag_string({kind_key, value_key});
        auto &value_metadata_attr = static_cast<graph::AttributeComposite &>(metadata_node.addAttribute(
            graph.createAttributeComposite(value_metadata_key, graphconstants::CONTEXT_RUL)));

        auto &value_metadata = value_value.value_metadata_ref();
        try_add_summarized(value_metadata_attr, value_metadata.summarized, value_metadata.summarized_default);
        try_add_url(value_metadata_attr, value_metadata.url);
        try_add_description(value_metadata_attr, value_metadata.description.get_escaped_html_format());
        try_remove_empty_attr(value_metadata_attr);
      }

      for (const auto &[detail_key, detail_value] : value_value.detail_metadata_map()) {
        const auto &detail_metadata_key = rul::create_tag_string({kind_key, value_key, detail_key});
        auto &detail_metadata_attr = static_cast<graph::AttributeComposite &>(metadata_node.addAttribute(
            graph.createAttributeComposite(detail_metadata_key, graphconstants::CONTEXT_RUL)));

        auto &detail_metadata = detail_value.detail_metadata_ref();
        try_add_summarized(detail_metadata_attr, detail_metadata.summarized, detail_metadata.summarized_default);
        try_add_url(detail_metadata_attr, detail_metadata.url);
        try_add_description(detail_metadata_attr, detail_metadata.description.get_escaped_html_format());
        try_remove_empty_attr(detail_metadata_attr);
      }
    }
  }
}

void readTagMetadataFromGraph(graph::Graph &graph, rul::TagMetadataStore &metadata_store) {
  if (const auto &metadata_node = graph.findNode(graphconstants::UID_RUL_TAG_METADATA);
      metadata_node != graph::Graph::invalidNode) {
    auto attr_it = metadata_node.getAttributes();

    while (attr_it.hasNext()) {
      auto &attr = dynamic_cast<graph::AttributeComposite &>(attr_it.next());

      const auto get_attr_str = [&attr](const std::string &name) -> graph::AttributeString * {
        if (auto attr_it = attr.findAttributeByName(name); attr_it.hasNext()) {
          return dynamic_cast<graph::AttributeString *>(&attr_it.next());
        }
        return nullptr;
      };

      auto [kind, value, detail] = rul::split_tag_string(attr.getName());
      auto &kind_metadata_map_value = metadata_store.try_add_kind(std::string(kind));

      if (value.empty()) {
        if (auto *desc_attr_ptr = get_attr_str(graphconstants::ATTR_RUL_TAG_METADATA_DESCRIPTION)) {
          kind_metadata_map_value.kind_metadata_ref().description = desc_attr_ptr->getStringValue();
        }

        return;
      }

      auto &value_metadata_map_value = kind_metadata_map_value.try_add_value(std::string(value));

      if (detail.empty()) {
        if (auto *desc_attr_ptr = get_attr_str(graphconstants::ATTR_RUL_TAG_METADATA_DESCRIPTION)) {
          value_metadata_map_value.value_metadata_ref().description = desc_attr_ptr->getStringValue();
        }
        if (auto *summarized_attr_ptr = get_attr_str(graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED)) {
          value_metadata_map_value.value_metadata_ref().summarized =
              summarized_attr_ptr->getValue() == graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED_TRUE;
        }
        if (auto *url_attr_ptr = get_attr_str(graphconstants::ATTR_RUL_TAG_METADATA_URL)) {
          value_metadata_map_value.value_metadata_ref().url = url_attr_ptr->getStringValue();
        }

        return;
      }

      auto &detail_metadata_map_value = value_metadata_map_value.try_add_detail(std::string(detail));
      if (auto *desc_attr_ptr = get_attr_str(graphconstants::ATTR_RUL_TAG_METADATA_DESCRIPTION)) {
        detail_metadata_map_value.detail_metadata_ref().description = desc_attr_ptr->getStringValue();
      }
      if (auto *summarized_attr_ptr = get_attr_str(graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED)) {
        detail_metadata_map_value.detail_metadata_ref().summarized =
            summarized_attr_ptr->getValue() == graphconstants::ATTR_RUL_TAG_METADATA_SUMMARIZED_TRUE;
      }
      if (auto *url_attr_ptr = get_attr_str(graphconstants::ATTR_RUL_TAG_METADATA_URL)) {
        detail_metadata_map_value.detail_metadata_ref().url = url_attr_ptr->getStringValue();
      }
    }
  }
}
} // namespace columbus::graphsupport
