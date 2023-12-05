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

class FileRange : public std::ranges::view_interface<FileRange> {
 public:
  class Iterator {
   public:
    using difference_type = std::ptrdiff_t;
    using value_type = char;
    Iterator() = default;

    Iterator& operator++() noexcept {
      if (p_ < size_) {
        p_++;
      }
      return *this;
    }

    Iterator operator++(int) noexcept {
      auto tmp = *this;
      ++*this;
      return tmp;
    }

    Iterator& operator--() noexcept {
      if (p_ > 0) --p_;
      return *this;
    }

    Iterator operator--(int) noexcept {
      auto tmp = *this;
      --*this;
      return tmp;
    }

    char& operator*() const noexcept {
      fsetpos(f_, &p_);
#ifndef NDEBUG
      int64_t pos = -1;
      auto err = fgetpos(f_, &pos);
      assert(err == 0);
      assert(pos == p_);
#endif
      auto cnt = fread(const_cast<char*>(&buf_), 1, 1, f_);
      auto& ret = const_cast<char&>(buf_);
      assert(cnt == 0 || cnt == 1);
      if (cnt == 0) {
        ret = EOF;
      }
      return ret;
    }

    bool operator==(const Iterator& rhs) const {
      return f_ == rhs.f_ && p_ == rhs.p_;
    }

    bool operator!=(const Iterator& rhs) const { return !(rhs == *this); }

   private:
    friend class FileRange;

    Iterator(FILE* f, int64_t p, int64_t size)
        : f_(f), p_(p), size_(size), buf_(0) {}
    FILE* f_;
    int64_t p_;
    int64_t size_;
    char buf_;
  };
  // ensure this is a valid range
  static_assert(std::input_iterator<Iterator>);
  static_assert(std::forward_iterator<Iterator>);
  static_assert(std::bidirectional_iterator<Iterator>);

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
    err = fseek(fr.f_, 0, SEEK_END);
    if (err != 0) {
      return std::unexpected(kFileRead);
    }
    int64_t len;
    err = fgetpos(fr.f_, &len);
    if (err != 0) {
      return std::unexpected(kFileRead);
    }
    err = fseek(fr.f_, 0, SEEK_SET);
    if (err != 0) {
      return std::unexpected(kFileRead);
    }
    int64_t pos = -1;
    err = fgetpos(fr.f_, &pos);
    if (err != 0) {
      return std::unexpected(kFileRead);
    }
    assert(pos == 0);
    fr.size_ = len;
    return fr;
  }

  Iterator begin() { return {f_, 0, size_}; }
  Iterator end() { return {f_, size_, size_}; }

  // ~FileRange() { fclose(f_); }

 private:
  FileRange() = default;
  FILE* f_;
  int64_t size_;
};
// ensure range concepts are satisfied
static_assert(std::ranges::range<FileRange>);
static_assert(std::ranges::forward_range<FileRange>);
static_assert(std::ranges::bidirectional_range<FileRange>);
// ensure this can be used as view
static_assert(std::ranges::view<FileRange>);
}  // namespace meta_lang::util

#endif  // METALANG_FILE_RANGE_HPP
