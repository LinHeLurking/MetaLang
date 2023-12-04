#include <gtest/gtest.h>

#include "src/util/string/utf8.hpp"

using namespace meta_lang;

TEST(BytesToCodepoint, Engligh) {
  auto buf = "Hello World";
  int len = strlen(buf);
  EXPECT_EQ(len, 11);

  std::vector<uint32_t> codes;
  for (int i = 0; i < len;) {
    auto [ch, cnt] = util::BytesToCodepoint(buf + i);
    i += cnt;
    codes.push_back(ch);
  }
  EXPECT_EQ(codes.size(), 11);
  EXPECT_EQ(codes[0], 'H');
  EXPECT_EQ(codes[1], 'e');
  EXPECT_EQ(codes[2], 'l');
  EXPECT_EQ(codes[3], 'l');
  EXPECT_EQ(codes[4], 'o');
  EXPECT_EQ(codes[5], ' ');
  EXPECT_EQ(codes[6], 'W');
  EXPECT_EQ(codes[7], 'o');
  EXPECT_EQ(codes[8], 'r');
  EXPECT_EQ(codes[9], 'l');
  EXPECT_EQ(codes[10], 'd');
}

TEST(BytesToCodepoint, Chinese) {
  auto buf = "你好";
  int len = strlen(buf);
  EXPECT_EQ(len, 6);
  EXPECT_EQ(buf[0], '\xE4');
  EXPECT_EQ(buf[1], '\xBD');
  EXPECT_EQ(buf[2], '\xA0');
  EXPECT_EQ(buf[3], '\xE5');
  EXPECT_EQ(buf[4], '\xA5');
  EXPECT_EQ(buf[5], '\xBD');

  std::vector<uint32_t> codes;
  for (int i = 0; i < len;) {
    auto [ch, cnt] = util::BytesToCodepoint(buf + i);
    i += cnt;
    codes.push_back(ch);
  }
  EXPECT_EQ(codes.size(), 2);
  EXPECT_EQ(codes[0], 0x4F60);
  EXPECT_EQ(codes[1], 0x597D);
}

TEST(CodepointToBytes, Chinese) {
  char buf[4];
  {
    std::fill(buf, buf + 4, '\0');
    auto cnt = util::CodepointToBytes(0x4F60, buf);
    EXPECT_EQ(cnt, 3);
    auto flag = strcmp(buf, "你");
    EXPECT_EQ(flag, 0);
  }
  {
    std::fill(buf, buf + 4, '\0');
    auto cnt = util::CodepointToBytes(0x597D, buf);
    EXPECT_EQ(cnt, 3);
    auto flag = strcmp(buf, "好");
    EXPECT_EQ(flag, 0);
  }
}

TEST(CodepointToBytes, English) {
  char buf[4];
  std::vector<char> codes = {' ', '.'};
  for (int i = 0; i < 26; ++i) {
    codes.push_back('a' + i);
    codes.push_back('A' + i);
  }
  for (auto code : codes) {
    std::fill(buf, buf + 4, '\0');
    auto cnt = util::CodepointToBytes(code, buf);
    EXPECT_EQ(cnt, 1);
    EXPECT_EQ(buf[0], code);
  }
}