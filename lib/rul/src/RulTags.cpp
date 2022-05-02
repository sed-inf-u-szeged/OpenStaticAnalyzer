#include "rul/inc/RulTags.h"
#include "rul/inc/RulMDString.h"
#include "rul/inc/RulTagString.h"

namespace columbus::rul {

const std::string &Tag::get_kind() const noexcept { return kind_; }
const std::string &Tag::get_detail() const noexcept { return detail_; }
const std::string &Tag::get_value() const noexcept { return value_; }

const RulMDString &Tag::get_kind_description() const noexcept { return kind_metadata_->description; }
const RulMDString &Tag::get_value_description() const noexcept { return value_metadata_->description; }
const RulMDString &Tag::get_detail_description() const noexcept { return detail_metadata_->description; }

const std::string &Tag::get_value_url() const noexcept { return value_metadata_->url; }
const std::string &Tag::get_detail_url() const noexcept { return detail_metadata_->url; }

bool Tag::get_value_summarized() const noexcept { return value_metadata_->summarized; }
bool Tag::get_detail_summarized() const noexcept { return detail_metadata_->summarized; }

const std::string &Tag::get_last_name() const noexcept {
  return !detail_.empty() ? detail_ : !value_.empty() ? value_ : kind_;
}

std::string Tag::get_full_name() const { return create_tag_string({kind_, value_, detail_}); }

void Tag::throw_if_incorrect_hierarchy(const std::string_view location) {
  if (kind_.empty() || value_.empty()) {
    throw columbus::Exception(std::string(location), R"(Tag must have "kind" and "value")");
  }
}

bool operator<(const Tag &lhs, const Tag &rhs) noexcept {
  if (const auto kind_ord = lhs.get_kind().compare(rhs.get_kind()); kind_ord != 0) { return kind_ord < 0; }
  if (const auto value_ord = lhs.get_value().compare(rhs.get_value()); value_ord != 0) { return value_ord < 0; }
  return lhs.get_detail() < rhs.get_detail();
}

bool operator==(const Tag &lhs, const Tag &rhs) noexcept {
  return lhs.get_kind() == rhs.get_kind() && lhs.get_value() == rhs.get_value() && lhs.get_detail() == rhs.get_detail();
}

std::ostream &operator<<(std::ostream &out, const Tag &tag) {
  out << "{"
      << "\n  kind: " << tag.get_kind() << "\n  value: " << tag.get_value() << "\n  detail: " << tag.get_detail()
      << "\n  kind_description: " << tag.get_kind_description().get_raw_format()
      << "\n  value_description: " << tag.get_value_description().get_raw_format()
      << "\n  detail_description: " << tag.get_detail_description().get_raw_format()
      << "\n  value_url: " << tag.get_value_url() << "\n  detail_url: " << tag.get_detail_url()
      << "\n  value_summarized: " << tag.get_value_summarized()
      << "\n  detail_summarized: " << tag.get_detail_summarized() << "\n}";
  return out;
}
} // namespace columbus::rul
