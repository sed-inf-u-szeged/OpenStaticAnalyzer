#ifndef RUL_RUL_TAG_METADATA_STORE_H_
#define RUL_RUL_TAG_METADATA_STORE_H_

#include <map>
#include <memory>

#include "RulTagMetadata.h"

namespace columbus::rul {
class TagDetailMetadataContainer {
public:
  [[nodiscard]] std::shared_ptr<TagDetailMetadata> detail_metadata();
  [[nodiscard]] std::shared_ptr<const TagDetailMetadata> detail_metadata() const;
  [[nodiscard]] TagDetailMetadata &detail_metadata_ref();
  [[nodiscard]] const TagDetailMetadata &detail_metadata_ref() const;
  [[nodiscard]] bool unused() const;

private:
  std::shared_ptr<TagDetailMetadata> detail_metadata_{std::make_shared<TagDetailMetadata>()};
};

using TagDetailMetadataMap = std::map<std::string, TagDetailMetadataContainer>;

class TagValueMetadataContainer {
public:
  template <typename DetailStr, typename... DetailTagMetadataAttrs>
  TagDetailMetadataContainer &try_add_detail(DetailStr &&detail, DetailTagMetadataAttrs &&...attrs) {
    return detail_metadata_map_.try_emplace(std::forward<DetailStr>(detail), std::forward<DetailTagMetadataAttrs>(attrs)...)
        .first->second;
  }

  [[nodiscard]] const TagDetailMetadataMap &detail_metadata_map() const;
  [[nodiscard]] std::shared_ptr<const TagValueMetadata> value_metadata() const;
  [[nodiscard]] std::shared_ptr<TagValueMetadata> value_metadata();
  [[nodiscard]] TagValueMetadata &value_metadata_ref();
  [[nodiscard]] const TagValueMetadata &value_metadata_ref() const;
  [[nodiscard]] bool unused() const;
  void remove_unused();

private:
  TagDetailMetadataMap detail_metadata_map_;
  std::shared_ptr<TagValueMetadata> value_metadata_{std::make_shared<TagValueMetadata>()};
};

using TagValueMetadataMap = std::map<std::string, TagValueMetadataContainer>;

class TagKindMetadataContainer {
public:
  template <typename ValueStr, typename... ValueTagMetadataAttrs>
  TagValueMetadataContainer &try_add_value(ValueStr &&value, ValueTagMetadataAttrs &&...attrs) {
    return value_metadata_map_.try_emplace(std::forward<ValueStr>(value), std::forward<ValueTagMetadataAttrs>(attrs)...)
        .first->second;
  }

  [[nodiscard]] const TagValueMetadataMap &value_metadata_map() const;
  [[nodiscard]] std::shared_ptr<TagKindMetadata> kind_metadata();
  [[nodiscard]] std::shared_ptr<const TagKindMetadata> kind_metadata() const;
  [[nodiscard]] TagKindMetadata &kind_metadata_ref();
  [[nodiscard]] const TagKindMetadata &kind_metadata_ref() const;
  [[nodiscard]] bool unused() const;
  void remove_unused();

private:
  TagValueMetadataMap value_metadata_map_;
  std::shared_ptr<TagKindMetadata> kind_metadata_{std::make_shared<TagKindMetadata>()};
};

using TagKindMetadataMap = std::map<std::string, TagKindMetadataContainer>;

class Tag;

class TagMetadataStore {
public:
  template <typename KindStr, typename... TagKindMetadataMapAttrs>
  TagKindMetadataContainer &try_add_kind(KindStr &&kind, TagKindMetadataMapAttrs &&...attrs) {
    return kind_metadata_map_.try_emplace(std::forward<KindStr>(kind), std::forward<TagKindMetadataMapAttrs>(attrs)...).first->second;
  }

  void set_tag_metadata(Tag &tag);
  [[nodiscard]] const TagKindMetadataMap &kind_metadata_map() const;
  void remove_unused();

  static const std::shared_ptr<const TagDetailMetadata> detail_tag_metadata_default;
  static const std::shared_ptr<const TagValueMetadata> value_tag_metadata_default;
  static const std::shared_ptr<const TagKindMetadata> kind_tag_metadata_default;

private:
  TagKindMetadataMap kind_metadata_map_;
};
} // namespace columbus::rul

#endif
