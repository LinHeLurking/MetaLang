#include <gtest/gtest.h>

#include <filesystem>

#include "src/util/fs/byte_reader.hpp"

using namespace meta_lang::util;

auto GetPath(const char* f) {
  std::filesystem::path path(TEST_FILE_PATH);
  path /= f;
  return absolute(path).string();
}

TEST(ByteReader, Empty) {
  ByteFileReader reader(GetPath("empty.txt"), 128);
  EXPECT_TRUE(reader.IsFinished());
  EXPECT_EQ(reader.LastRead(), 0);
}

TEST(ByteFileReader, Small_1) {
  ByteFileReader reader(GetPath("small_1.txt"), 128);
  auto buf = reader.Get4BytesBuf();
  EXPECT_EQ(buf[0], 'a');
  EXPECT_EQ(buf[1], 'b');
  EXPECT_EQ(buf[2], 'c');
  EXPECT_TRUE(reader.IsFinished());
  EXPECT_EQ(reader.LastRead(), 3);
}

TEST(ByteFileReader, Small_2) {
  ByteFileReader reader(GetPath("small_2.txt"), 128);
  auto buf = reader.Get4BytesBuf();
  EXPECT_EQ(buf[0], 'a');
  EXPECT_EQ(buf[1], 'b');
  EXPECT_EQ(buf[2], 'c');
  EXPECT_EQ(buf[3], 'd');
  EXPECT_EQ(reader.LastRead(), 4);
  buf = reader.Get4BytesBuf();
  EXPECT_EQ(buf[0], 'e');
  EXPECT_EQ(buf[1], 'f');
  EXPECT_EQ(buf[2], 'g');
  EXPECT_TRUE(reader.IsFinished());
  EXPECT_EQ(reader.LastRead(), 3);
}

TEST(ByteFileReader, Large_1) {
  ByteFileReader reader(GetPath("large_1.txt"), 128);
  char* buf;
  for (int i = 0; i < 10; ++i) {
    if (i % 4 == 0) {
      buf = reader.Get4BytesBuf();
    }
    EXPECT_EQ(buf[i % 4], '0' + i);
  }
  // 2 more bytes are read;
  EXPECT_TRUE(reader.Unget());
  EXPECT_TRUE(reader.Unget());
  for (int i = 0; i < 26; ++i) {
    if (i % 4 == 0) {
      buf = reader.Get4BytesBuf();
    }
    EXPECT_EQ(buf[i % 4], 'a' + i);
  }
  // 2 more bytes are read;
  EXPECT_TRUE(reader.Unget());
  EXPECT_TRUE(reader.Unget());
  for (int i = 0; i < 26; ++i) {
    if (i % 4 == 0) {
      buf = reader.Get4BytesBuf();
    }
    EXPECT_EQ(buf[i % 4], 'A' + i);
  }
  EXPECT_TRUE(reader.IsFinished());
}

TEST(ByteFileReader, BeyondUnget) {
  ByteFileReader reader(GetPath("small_1.txt"), 128);
  reader.Get4BytesBuf();
  EXPECT_TRUE(reader.IsFinished());
  EXPECT_TRUE(reader.Unget());
  EXPECT_TRUE(reader.Unget());
  EXPECT_FALSE(reader.IsFinished());
  auto buf = reader.Get4BytesBuf();
  EXPECT_EQ(reader.LastRead(), 2);
  EXPECT_EQ(buf[0], 'b');
  EXPECT_EQ(buf[1], 'c');
}