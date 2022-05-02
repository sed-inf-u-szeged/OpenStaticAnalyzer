#ifndef RUL_RUL_TAG_STORE_H_
#define RUL_RUL_TAG_STORE_H_

#include <memory>
#include <unordered_map>

#include "RulTagString.h"
#include "RulTags.h"

namespace columbus::rul {
class TagStore {
public:
  [[nodiscard]] std::shared_ptr<Tag> create_or_get(std::string &&tag_string);
  [[nodiscard]] std::shared_ptr<Tag> create_or_get(SplitTagStringView split_tag_string);
  [[nodiscard]] TagMetadataStore &metadata_store();
  [[nodiscard]] const TagMetadataStore &metadata_store() const;

private:
  TagMetadataStore tag_metadata_;
  std::unordered_map<std::string, std::shared_ptr<Tag>> shared_tag_map_;
};

[[nodiscard]] inline bool operator<(const std::shared_ptr<Tag> &lhs, const std::shared_ptr<Tag> &rhs) noexcept {
  return *lhs < *rhs;
}

[[nodiscard]] inline bool operator==(const std::shared_ptr<Tag> &lhs, const std::shared_ptr<Tag> &rhs) noexcept {
  return *lhs == *rhs;
}
} // namespace columbus::rul

#endif
