#ifndef RUL_RUL_TAG_METADATA_
#define RUL_RUL_TAG_METADATA_

#include <string>

#include "RulMDString.h"

namespace columbus::rul {
struct TagDetailMetadata {
  RulMDString description;
  std::string url;
  bool summarized = summarized_default;
  static constexpr bool summarized_default = false;
};

struct TagValueMetadata {
  RulMDString description;
  std::string url;
  bool summarized = summarized_default;
  static constexpr bool summarized_default = false;
};

struct TagKindMetadata {
  RulMDString description;
};
} // namespace columbus::rul

#endif
