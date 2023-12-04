#include <gtest/gtest.h>

#include "src/util/fs/byte_reader.hpp"

using namespace meta_lang::util;

TEST(ByteReader, Empty) {
  ByteFileReader reader(TEST_FILE_EMPTY, 128);
  EXPECT_TRUE(reader.IsFinished());
  EXPECT_EQ(reader.LastRead(), 0);
}

TEST(ByteFileReader, Small_1) {
  ByteFileReader reader(TEST_FILE_SMALL_1, 128);
  auto buf = reader.Get4BytesBuf();
  EXPECT_EQ(buf[0], 'a');
  EXPECT_EQ(buf[1], 'b');
  EXPECT_EQ(buf[2], 'c');
  EXPECT_TRUE(reader.IsFinished());
  EXPECT_EQ(reader.LastRead(), 3);
}

TEST(ByteFileReader, Small_2) {
  ByteFileReader reader(TEST_FILE_SMALL_2, 128);
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
  ByteFileReader reader(TEST_FILE_LARGE_1, 128);
  char *buf;
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
  ByteFileReader reader(TEST_FILE_SMALL_1, 128);
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