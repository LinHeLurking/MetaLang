#ifndef METALANG_FILE_RANGE_HPP
#define METALANG_FILE_RANGE_HPP

#include <concepts>
#include <cstdio>
#include <expected>
#include <fstream>
#include <iterator>
#include <ranges>
#include <string>
#include <utility>

#include "../concept/string_like.hpp"
#include "../inline/force_inline.hpp"

namespace meta_lang::util {

class FileRange {
 public:
  class Iterator {
   public:
    using iterator_concept = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = char;

    Iterator() = default;
    explicit Iterator(char* cur, char* end) : cur_(cur), end_(end) {}

    Iterator& operator++() noexcept {
      if (cur_ < end_) cur_++;
      return *this;
    }

    void operator++(int) noexcept { ++*this; }

    bool operator==(const Iterator& rhs) const noexcept {
      return cur_ == rhs.cur_;
    }

    bool operator!=(const Iterator& rhs) const noexcept {
      return !(rhs == *this);
    }

    char& operator*() const noexcept { return *cur_; }

   private:
    friend class FileRange;
    char* cur_ = nullptr;
    char* end_ = nullptr;
  };
  // ensure this is a valid range
  static_assert(std::input_iterator<Iterator>);
  // don't know why not satisfied :(
  // static_assert(std::forward_iterator<Iterator>);

  enum Error {
    kFileRead,
  };

  static std::expected<FileRange, Error> Create(StringLike auto name) noexcept {
    FileRange fr{};
    std::string_view sv{name};
    auto err = fopen_s(&fr.f_, sv.data(), "rb");
    if (err != 0) {
      return std::unexpected(kFileRead);
    }
    fseek(fr.f_, 0, SEEK_END);
    size_t len = ftell(fr.f_);
    rewind(fr.f_);
    fr.buf_ = new char[len + 1];
    fr.end_ = fr.buf_ + len;
    fread(fr.buf_, 1, len, fr.f_);
    fr.buf_[len] = EOF;
    return fr;
  }

  Iterator begin() { return Iterator(buf_, end_); }
  Iterator end() { return Iterator(end_, end_); }

 private:
  FileRange() = default;
  FILE* f_;
  char* buf_;
  char* end_;
};
static_assert(std::ranges::range<FileRange>);
}  // namespace meta_lang::util

#endif  // METALANG_FILE_RANGE_HPP
