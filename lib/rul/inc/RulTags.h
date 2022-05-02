#ifndef RUL_RUL_TAGS_H_
#define RUL_RUL_TAGS_H_

#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include "Exception.h"
#include "RulMDString.h"
#include "RulTagMetadataStore.h"

namespace columbus::rul {
class Tag {
public:
  template <typename T1, typename T2>
  Tag(T1 &&kind, T2 &&value);

  template <typename T1, typename T2, typename T3>
  Tag(T1 &&kind, T2 &&value, T3 &&detail);

  [[nodiscard]] const std::string &get_kind() const noexcept;
  [[nodiscard]] const std::string &get_detail() const noexcept;
  [[nodiscard]] const std::string &get_value() const noexcept;

  [[nodiscard]] const RulMDString &get_kind_description() const noexcept;
  [[nodiscard]] const RulMDString &get_value_description() const noexcept;
  [[nodiscard]] const RulMDString &get_detail_description() const noexcept;

  [[nodiscard]] const std::string &get_value_url() const noexcept;
  [[nodiscard]] const std::string &get_detail_url() const noexcept;

  [[nodiscard]] bool get_value_summarized() const noexcept;
  [[nodiscard]] bool get_detail_summarized() const noexcept;

  [[nodiscard]] const std::string &get_last_name() const noexcept;
  [[nodiscard]] std::string get_full_name() const;

private:
  std::string kind_;
  std::string value_;
  std::string detail_;

  std::shared_ptr<const TagDetailMetadata> detail_metadata_{TagMetadataStore::detail_tag_metadata_default};
  std::shared_ptr<const TagValueMetadata> value_metadata_{TagMetadataStore::value_tag_metadata_default};
  std::shared_ptr<const TagKindMetadata> kind_metadata_{TagMetadataStore::kind_tag_metadata_default};

  friend class TagMetadataStore;

  void throw_if_incorrect_hierarchy(std::string_view location);
};

[[nodiscard]] bool operator<(const Tag &lhs, const Tag &rhs) noexcept;
[[nodiscard]] bool operator==(const Tag &lhs, const Tag &rhs) noexcept;
std::ostream &operator<<(std::ostream &out, const Tag &tag);

template <typename T1, typename T2>
Tag::Tag(T1 &&kind, T2 &&value) : kind_(std::forward<T1>(kind)), value_(std::forward<T2>(value)) {
  throw_if_incorrect_hierarchy(COLUMBUS_LOCATION);
}

template <typename T1, typename T2, typename T3>
Tag::Tag(T1 &&kind, T2 &&value, T3 &&detail)
    : kind_(std::forward<T1>(kind)), value_(std::forward<T2>(value)), detail_(std::forward<T3>(detail)) {
  throw_if_incorrect_hierarchy(COLUMBUS_LOCATION);
}
} // namespace columbus::rul

#endif
