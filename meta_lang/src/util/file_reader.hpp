#ifndef METALANG_FILE_READER_HPP
#define METALANG_FILE_READER_HPP

#include <cstdio>
#include <expected>
#include <filesystem>

#include "./string_like.hpp"
#include "./expecetd.hpp"

namespace meta_lang::util {
class FileReader {
 public:
  enum Error {
    kNotExist,
    kCannotRead,
  };

  static std::expected<FileReader, Error> LoadFile(StringLike auto s) noexcept {
    std::filesystem::path path(s);
    if (!std::filesystem::exists(path)) {
      E_RET(kNotExist);
    }
    size_t size = std::filesystem::file_size(path);
    char *buf = new char[size + 5];
    std::fill(buf, buf + size, EOF);
    FILE *f;
    auto err = fopen_s(&f, absolute(path).string().c_str(), "rb");
    if (err != 0) {
      E_RET(kCannotRead);
    }
    fread_s(buf, size + 1, 1, size, f);
    fclose(f);
    return FileReader(buf, size);
  }

  [[nodiscard]] char *GetBuf() const noexcept { return buf_; }
  [[nodiscard]] size_t GetSize() const noexcept { return size_; }

  ~FileReader() { delete[] buf_; }

  FileReader() = delete;

 private:
  FileReader(char *b, size_t s) : buf_(b), size_(s) {}
  char *buf_ = nullptr;
  size_t size_ = 0;
};
}  // namespace meta_lang::util::fs

#endif  // METALANG_FILE_READER_HPP
