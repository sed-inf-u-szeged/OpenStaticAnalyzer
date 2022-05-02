#include "rul/inc/RulTagStore.h"

namespace columbus::rul {
std::shared_ptr<Tag> TagStore::create_or_get(std::string &&tag_string) {
  auto [entry_it, inserted] = shared_tag_map_.try_emplace(std::move(tag_string));
  if (inserted) {
    auto [kind, value, detail] = split_tag_string(entry_it->first);
    entry_it->second = std::make_shared<Tag>(kind, value, detail);
    tag_metadata_.set_tag_metadata(*entry_it->second);
  }
  return entry_it->second;
}

std::shared_ptr<Tag> TagStore::create_or_get(const SplitTagStringView split_tag_string) {
  auto [entry_it, inserted] = shared_tag_map_.try_emplace(create_tag_string(split_tag_string));
  if (inserted) {
    entry_it->second = std::make_shared<Tag>(split_tag_string.kind, split_tag_string.value, split_tag_string.detail);
    tag_metadata_.set_tag_metadata(*entry_it->second);
  }
  return entry_it->second;
}

TagMetadataStore &TagStore::metadata_store() { return tag_metadata_; }
const TagMetadataStore &TagStore::metadata_store() const { return tag_metadata_; }
} // namespace columbus::rul
