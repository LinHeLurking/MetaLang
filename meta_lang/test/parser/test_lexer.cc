#include <gtest/gtest.h>

#include "src/parser/lexer.hpp"

using namespace meta_lang;

TEST(LexerCtor, _0) {
  parser::Lexer lexer;
  char *p = "";
  auto res = lexer.Tokenize(p);
  ASSERT_TRUE(bool(res));
}

class LexerTest : public testing::Test {
 protected:
  using enum parser::Token::Type;
  void SetUp() override {}

  parser::Lexer lexer_;
};

TEST_F(LexerTest, _0) {
  char *p = "+-*/!";
  auto r = lexer_.Tokenize(p);
  ASSERT_TRUE(bool(r));
  auto stream = r.value();
  EXPECT_EQ(stream.size(), 5);
  EXPECT_EQ(stream.front().Type(), kAdd);
  stream.pop_front();
  EXPECT_EQ(stream.front().Type(), kSub);
  stream.pop_front();
  EXPECT_EQ(stream.front().Type(), kMul);
  stream.pop_front();
  EXPECT_EQ(stream.front().Type(), kDiv);
  stream.pop_front();
  EXPECT_EQ(stream.front().Type(), kNot);
  stream.pop_front();
}
