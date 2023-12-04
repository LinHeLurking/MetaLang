#include <gtest/gtest.h>

#include <filesystem>

#include "src/util/fs/file_range_builder.hpp"

using namespace meta_lang::util;

auto GetPath(const char* f) {
  auto path = std::filesystem::path(TEST_FILE_PATH);
  path /= f;
  return absolute(path).string();
}

TEST(FileRangeBuilder, Raw) {
  auto frb = FileRangeBuilder(GetPath("with_space.txt"));
  auto e = frb.GetRawView();
  EXPECT_TRUE(bool(e));
  auto s = std::ranges::to<std::string>(e.value());
  EXPECT_EQ(s, "123 abc 456 xyz");
}

TEST(FileRangeBuilder, NoWhitespace) {
  auto frb = FileRangeBuilder(GetPath("with_space.txt"));
  auto e = frb.GetNonEmptyView();
  EXPECT_TRUE(bool(e));
  auto s = std::ranges::to<std::string>(e.value());
  EXPECT_EQ(s, "123abc456xyz");
}