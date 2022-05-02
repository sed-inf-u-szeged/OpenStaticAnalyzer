#ifndef RUL_RUL_TAG_STRING_H_
#define RUL_RUL_TAG_STRING_H_

#include <string>
#include <string_view>

#include "Exception.h"

namespace columbus::rul {
struct SplitTagStringView {
  std::string_view kind;
  std::string_view value;
  std::string_view detail;
};

[[nodiscard]] inline SplitTagStringView split_tag_string(const std::string_view tag_string) {
  const auto kind_sep = tag_string.begin();
  if (kind_sep == tag_string.end()) [[unlikely]] { throw columbus::Exception(COLUMBUS_LOCATION, "Empty tag."); }

  if (*kind_sep != '/') [[unlikely]] {
    std::string message = "Tag: \"";
    message += tag_string;
    message += "\" should start with '/'.";
    throw columbus::Exception(COLUMBUS_LOCATION, std::move(message));
  }

  const auto kind_begin = kind_sep + 1;
  const auto value_sep = std::find(kind_begin, tag_string.end(), '/');
  std::string_view kind(&*kind_begin, value_sep - kind_begin);

  if (value_sep == tag_string.end()) { return {kind, {}, {}}; }

  const auto value_begin = value_sep + 1;
  const auto detail_sep = std::find(value_begin, tag_string.end(), '/');
  std::string_view value(&*value_begin, detail_sep - value_begin);

  if (detail_sep == tag_string.end()) { return {kind, value, {}}; }

  const auto detail_begin = detail_sep + 1;
  std::string_view detail(&*detail_begin, tag_string.end() - detail_begin);

  return {kind, value, detail};
}

[[nodiscard]] inline std::string create_tag_string(const SplitTagStringView split_tag_string) {
  std::string full_name;
  full_name.reserve(split_tag_string.kind.size() + split_tag_string.value.size() + split_tag_string.detail.size() + 3);
  (full_name += '/') += split_tag_string.kind;
  if (split_tag_string.value.empty()) { return full_name; }
  (full_name += '/') += split_tag_string.value;
  if (split_tag_string.detail.empty()) { return full_name; }
  (full_name += '/') += split_tag_string.detail;
  return full_name;
}
} // namespace columbus::rul
#endif
