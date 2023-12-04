#ifndef METALANG_FILE_RANGE_BUILDER_HPP
#define METALANG_FILE_RANGE_BUILDER_HPP

#include <expected>
#include <fstream>
#include <ranges>
#include <string>

#include "../inline/force_inline.hpp"

namespace meta_lang::util {
class FileRangeBuilder {
 public:
  explicit FileRangeBuilder(std::string p) : path_(std::move(p)) {}
  enum Error {
    kFileRead,
  };

  FORCE_INLINE std::expected<void, Error> OpenFile() {
    f_ = std::ifstream(path_);
    if (!f_.is_open()) {
      return std::unexpected(kFileRead);
    }
    // keep whitespaces
    f_.unsetf(std::ios_base::skipws);
    return {};
  }

  FORCE_INLINE std::expected<std::ranges::istream_view<char>, Error>
  GetRawView() {
    auto r = OpenFile();
    if (!r) return std::unexpected(r.error());
    auto v = std::views::istream<char>(f_);
    return v;
  }

  FORCE_INLINE auto GetNonEmptyView() {
    auto filter = std::views::filter([](char el) { return el != ' '; });
    using RawT = decltype(GetRawView().value() | filter);
    using RT = std::expected<RawT, Error>;
    return GetRawView().and_then(
        [&filter](auto v) -> RT { return v | filter; });
  }

 private:
  std::string path_;
  std::ifstream f_;
};
}  // namespace meta_lang::util

#endif  // METALANG_FILE_RANGE_BUILDER_HPP
