#include "rul/inc/RulTagMetadataStore.h"
#include "rul/inc/RulTags.h"

#include <boost/algorithm/string.hpp>

namespace columbus::rul {
std::shared_ptr<TagDetailMetadata> TagDetailMetadataContainer::detail_metadata() { return detail_metadata_; }

std::shared_ptr<const TagDetailMetadata> TagDetailMetadataContainer::detail_metadata() const {
  return detail_metadata_;
}

TagDetailMetadata &TagDetailMetadataContainer::detail_metadata_ref() { return *detail_metadata_; }

const TagDetailMetadata &TagDetailMetadataContainer::detail_metadata_ref() const { return *detail_metadata_; }

bool TagDetailMetadataContainer::unused() const { return detail_metadata_.use_count() == 1; }

const TagDetailMetadataMap &TagValueMetadataContainer::detail_metadata_map() const { return detail_metadata_map_; }

std::shared_ptr<const TagValueMetadata> TagValueMetadataContainer::value_metadata() const { return value_metadata_; }

std::shared_ptr<TagValueMetadata> TagValueMetadataContainer::value_metadata() { return value_metadata_; }

TagValueMetadata &TagValueMetadataContainer::value_metadata_ref() { return *value_metadata_; }

const TagValueMetadata &TagValueMetadataContainer::value_metadata_ref() const { return *value_metadata_; }

bool TagValueMetadataContainer::unused() const { return value_metadata_.use_count() == 1; }

void TagValueMetadataContainer::remove_unused() {
  for (auto detail_it = detail_metadata_map_.begin(); detail_it != detail_metadata_map_.end();) {
    if (detail_it->second.unused()) {
      detail_it = detail_metadata_map_.erase(detail_it);
    } else {
      ++detail_it;
    }
  }
}

const TagValueMetadataMap &TagKindMetadataContainer::value_metadata_map() const { return value_metadata_map_; }

std::shared_ptr<TagKindMetadata> TagKindMetadataContainer::kind_metadata() { return kind_metadata_; }

std::shared_ptr<const TagKindMetadata> TagKindMetadataContainer::kind_metadata() const { return kind_metadata_; }

TagKindMetadata &TagKindMetadataContainer::kind_metadata_ref() { return *kind_metadata_; }

const TagKindMetadata &TagKindMetadataContainer::kind_metadata_ref() const { return *kind_metadata_; }

bool TagKindMetadataContainer::unused() const { return kind_metadata_.use_count() == 1; }

void TagKindMetadataContainer::remove_unused() {
  for (auto value_it = value_metadata_map_.begin(); value_it != value_metadata_map_.end();) {
    if (value_it->second.unused()) {
      value_it = value_metadata_map_.erase(value_it);
    } else {
      value_it->second.remove_unused();
      ++value_it;
    }
  }
}

const TagKindMetadataMap &TagMetadataStore::kind_metadata_map() const { return kind_metadata_map_; }

void TagMetadataStore::remove_unused() {
  for (auto kind_it = kind_metadata_map_.begin(); kind_it != kind_metadata_map_.end();) {
    if (kind_it->second.unused()) {
      kind_it = kind_metadata_map_.erase(kind_it);
    } else {
      kind_it->second.remove_unused();
      ++kind_it;
    }
  }
}

void TagMetadataStore::set_tag_metadata(Tag &tag) {
  if (const auto kind_entry = kind_metadata_map_.find(tag.get_kind()); kind_entry != kind_metadata_map_.end()) {
    const auto &kind_metadata_map_value = kind_entry->second;
    tag.kind_metadata_ = kind_metadata_map_value.kind_metadata();

    if (tag.get_value().empty()) { return; }

    const auto &value_metadata_map = kind_metadata_map_value.value_metadata_map();
    if (const auto value_entry = value_metadata_map.find(tag.get_value()); value_entry != value_metadata_map.end()) {
      const auto &value_metadata_map_value = value_entry->second;
      tag.value_metadata_ = value_metadata_map_value.value_metadata();

      if (tag.get_detail().empty()) { return; }

      const auto &detail_metadata_map = value_metadata_map_value.detail_metadata_map();
      if (const auto detail_entry = detail_metadata_map.find(tag.get_detail());
          detail_entry != detail_metadata_map.end()) {
        tag.detail_metadata_ = detail_entry->second.detail_metadata();
      }
    }
  }
}

const std::shared_ptr<const TagDetailMetadata> TagMetadataStore::detail_tag_metadata_default =
    std::make_shared<const TagDetailMetadata>();
const std::shared_ptr<const TagValueMetadata> TagMetadataStore::value_tag_metadata_default =
    std::make_shared<const TagValueMetadata>();
const std::shared_ptr<const TagKindMetadata> TagMetadataStore::kind_tag_metadata_default =
    std::make_shared<const TagKindMetadata>();
} // namespace columbus::rul
