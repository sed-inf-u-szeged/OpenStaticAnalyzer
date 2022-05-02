#ifndef COMMON_XERCESSUP_H_
#define COMMON_XERCESSUP_H_

#include <utility>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/Xerces_autoconf_config.hpp>

namespace common::Xerces {

namespace Concept {
template <typename T>
constexpr bool is_xerces_string = std::is_same_v<std::remove_cv_t<T>, XMLCh *> || std::is_same_v<std::remove_cv_t<T>, const XMLCh *>;

template <typename T>
constexpr bool is_c_string = std::is_same_v<std::remove_cv_t<T>, char *> || std::is_same_v<std::remove_cv_t<T>, const char *>;

template <typename Output>
constexpr bool is_transcode_output = is_xerces_string<Output> || is_c_string<Output>;

template <typename Input, typename Output>
constexpr bool is_transcode_input = (is_c_string<Input> && is_xerces_string<Output>) || (is_c_string<Output> && is_xerces_string<Input>);

} // namespace Concept

template <typename Output, typename = std::enable_if_t<Concept::is_transcode_output<Output>>>
class ScopedTranscode {
public:
  template <typename Input, typename = std::enable_if_t<Concept::is_transcode_input<Input, Output>>>
  explicit ScopedTranscode(const Input ptr) noexcept : ptr{xercesc::XMLString::transcode(ptr)} {}
  ~ScopedTranscode() { xercesc::XMLString::release(&ptr); }

  ScopedTranscode(const ScopedTranscode &) = delete;
  ScopedTranscode &operator=(const ScopedTranscode &) = delete;

  ScopedTranscode(ScopedTranscode &&other) noexcept : ptr{std::exchange(other.ptr, nullptr)} {}
  ScopedTranscode &operator=(ScopedTranscode &&other) noexcept {
    if (this != &other) {
      xercesc::XMLString::release(&ptr);
      ptr = std::exchange(other.ptr, nullptr);
    }
    return *this;
  }

  operator Output() const noexcept { return ptr; }

private:
  Output ptr;
};

class ScopedInitialization {
public:
  ScopedInitialization() noexcept { xercesc::XMLPlatformUtils::Initialize(); }
  ScopedInitialization(const ScopedInitialization & /*other*/) noexcept { xercesc::XMLPlatformUtils::Initialize(); }
  ScopedInitialization &operator=(const ScopedInitialization &other) noexcept {
    if (this != &other) { xercesc::XMLPlatformUtils::Initialize(); }
    return *this;
  }
  ScopedInitialization(ScopedInitialization && /*other*/) noexcept { xercesc::XMLPlatformUtils::Initialize(); }
  ScopedInitialization &operator=(ScopedInitialization &&other) noexcept {
    if (this != &other) { xercesc::XMLPlatformUtils::Initialize(); }
    return *this;
  }
  ~ScopedInitialization() { xercesc::XMLPlatformUtils::Terminate(); }
};
} // namespace common::Xerces

#endif
