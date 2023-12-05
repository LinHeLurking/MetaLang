#include <gtest/gtest.h>

#include <filesystem>

#include "../try_expected.hpp"
#include "src/util/fs/file_range.hpp"

using namespace meta_lang::util;

auto GetPath(const char* f) {
  auto path = std::filesystem::path(TEST_FILE_PATH);
  path /= f;
  return absolute(path).string();
}

TEST(FileRange, Raw) {
  auto fr = E_TRY(FileRange::Create(GetPath("with_space.txt")));
  {
    auto s = std::ranges::to<std::string>(fr);
    EXPECT_EQ(s, "123 abc 456 xyz");
  }
  {
    auto v = fr | std::views::filter([](char el) { return el != ' '; });
    auto s = std::ranges::to<std::string>(v);
    EXPECT_EQ(s, "123abc456xyz");
  }
}

TEST(FileRange, _EOF) {
  auto fr = E_TRY(FileRange::Create(GetPath("with_space.txt")));
  auto it = fr.begin();
  for (int i = 0; i < 15; ++i) {
    it++;
  }
  // reading beyond contents get EOF
  EXPECT_EQ(EOF, *it);
  it++;
  EXPECT_EQ(EOF, *it);
  it++;
}
