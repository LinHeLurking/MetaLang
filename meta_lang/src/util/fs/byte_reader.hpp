#ifndef METALANG_BYTE_READER_HPP
#define METALANG_BYTE_READER_HPP

#include <fstream>

#include "../concept/string_like.hpp"

namespace meta_lang::util {
class ByteFileReader {
 public:
  ByteFileReader(StringLike auto s, int buf_size)
      : f_(s, std::ios_base::binary | std::ios_base::in), cap_(buf_size) {
    buf_ = new char[buf_size];
    memset(buf_, 0, buf_size);
    if (!f_.is_open()) {
      throw std::runtime_error("Error when opening file: " + std::string(s));
    }
    f_.read(buf_, buf_size);
    size_ = int(f_.gcount());
  }

  ~ByteFileReader() { delete[] buf_; }

  char* Get4BytesBuf() {
    if (size_ > 8 && p_ + 4 > size_) {
      int offset = size_ - p_;
      memcpy(buf_, buf_ + p_, offset);
      f_.read(buf_ + offset, cap_ - offset);
      size_ = int(f_.gcount()) + offset;
      p_ = 0;
    }
    auto ret = buf_ + p_;
    int next_p = std::min(p_ + 4, size_);
    last_read_ = next_p - p_;
    p_ = next_p;
    return ret;
  }

  int Unget() noexcept {
    if (p_ == 0) {
      return 0;
    }
    p_--;
    return 1;
  }

  [[nodiscard]] bool IsFinished() const noexcept { return p_ >= size_; }

  [[nodiscard]] int LastRead() const noexcept { return last_read_; }

 private:
  char* buf_;
  int size_ = 0;
  int cap_;
  int p_ = 0;
  int last_read_ = 0;
  std::ifstream f_;
};
}  // namespace meta_lang::util

#endif  // METALANG_BYTE_READER_HPP
