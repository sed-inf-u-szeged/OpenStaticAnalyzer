#include "rul/inc/RulMDString.h"

#include <common/inc/StringSup.h>
#include <md4c-html.h>

namespace columbus::rul {
const std::string &RulMDString::get_html_format() const {
  if (!html_format_.has_value()) {
    html_format_.emplace();
    ::md_html(
        raw_format_.c_str(), raw_format_.size(),
        [](const MD_CHAR *chunk, MD_SIZE size, void *html_format_str) {
          static_cast<std::string *>(html_format_str)->append(chunk, size);
        },
        &html_format_.value(), MD_DIALECT_GITHUB, 0);
    // if (!html_format_->empty() && html_format_->back() == '\n') { html_format_->pop_back(); }
  }

  return html_format_.value();
}

const std::string &RulMDString::get_escaped_html_format() const {
  if (!escaped_html_format_.has_value()) {
    auto &escaped_html_format_str = escaped_html_format_.emplace();
    for (const char ch : get_html_format()) {
      switch (ch) {
      case '&':
        escaped_html_format_str += "&amp;";
        break;
      case '\"':
        escaped_html_format_str += "&quot;";
        break;
      case '\'':
        escaped_html_format_str += "&apos;";
        break;
      case '<':
        escaped_html_format_str += "&lt;";
        break;
      case '>':
        escaped_html_format_str += "&gt;";
        break;
      case '\n':
        escaped_html_format_str += "&#10;";
        break;
      default:
        escaped_html_format_str += ch;
        break;
      }
    }
  }

  return escaped_html_format_.value();
}

const std::string &RulMDString::get_raw_format() const noexcept { return raw_format_; }

void RulMDString::clear() noexcept {
  raw_format_.clear();
  reset_cache();
}

void RulMDString::trim() { common::trim(raw_format_); }

bool RulMDString::empty() const noexcept { return raw_format_.empty(); }

bool RulMDString::operator==(const RulMDString &other) const noexcept { return raw_format_ == other.raw_format_; }

const std::string &RulMDString::get_format(RawFormatTag /*tag*/) const noexcept { return get_raw_format(); }

const std::string &RulMDString::get_format(HtmlFormatTag /*tag*/) const { return get_html_format(); }

const std::string &RulMDString::get_format(EscapedHTMLFormatTag /*tag*/) const { return get_escaped_html_format(); }

void RulMDString::reset_cache() noexcept {
  html_format_.reset();
  escaped_html_format_.reset();
}
} // namespace columbus::rul
