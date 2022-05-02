#ifndef RUL_RUL_MD_STRING_H_
#define RUL_RUL_MD_STRING_H_

#include <optional>
#include <string>
#include <utility>


namespace columbus::rul {
class RulMDString {
public:
  RulMDString() = default;

  template <typename T, typename = std::enable_if_t<!std::is_base_of_v<RulMDString, std::remove_reference_t<T>>>>
  explicit RulMDString(T &&raw_format);

  [[nodiscard]] const std::string &get_html_format() const;
  [[nodiscard]] const std::string &get_escaped_html_format() const;
  [[nodiscard]] const std::string &get_raw_format() const noexcept;
  void clear() noexcept;
  void trim();
  [[nodiscard]] bool empty() const noexcept;

  template <typename T>
  RulMDString &append(T &&str);

  template <typename T>
  RulMDString &append_line(T &&str);

  template <typename T, typename = std::enable_if_t<!std::is_base_of_v<RulMDString, std::remove_reference_t<T>>>>
  RulMDString &operator=(T &&raw_format);

  [[nodiscard]] bool operator==(const RulMDString &other) const noexcept;

  struct RawFormatTag {};
  [[nodiscard]] const std::string &get_format(RawFormatTag /*tag*/) const noexcept;

  struct HtmlFormatTag {};
  [[nodiscard]] const std::string &get_format(HtmlFormatTag /*tag*/) const;

  struct EscapedHTMLFormatTag {};
  [[nodiscard]] const std::string &get_format(EscapedHTMLFormatTag /*tag*/) const;

private:
  using LazyFormatedString = std::optional<std::string>;
  mutable LazyFormatedString html_format_;
  mutable LazyFormatedString escaped_html_format_;
  std::string raw_format_;

  void reset_cache() noexcept;

public:
  static constexpr HtmlFormatTag html_format_tag{};
  static constexpr RawFormatTag raw_format_tag{};
  static constexpr EscapedHTMLFormatTag escaped_html_format_tag{};
};

template <typename T, typename>
RulMDString::RulMDString(T &&raw_format) : raw_format_(std::forward<T>(raw_format)) {}

template <typename T>
RulMDString &RulMDString::append(T &&str) {
  raw_format_ += str;
  reset_cache();
  return *this;
}

template <typename T>
RulMDString &RulMDString::append_line(T &&str) {
  (raw_format_ += str) += '\n';
  reset_cache();
  return *this;
}

template <typename T, typename>
RulMDString &RulMDString::operator=(T &&raw_format) {
  raw_format_ = std::forward<T>(raw_format);
  reset_cache();
  return *this;
}
} // namespace columbus::rul

#endif
