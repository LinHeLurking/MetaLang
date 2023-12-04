#include <gtest/gtest.h>

#include "src/parser/meta/meta_grammar.hpp"

using namespace meta_lang::meta_grammar::parser;

TEST(MetaGrammar, Parser_1) {
  auto parser = MetaParser(TEST_GRAMMAR_FILE_1);
  EXPECT_TRUE(parser.Identifier().has_value());
  EXPECT_TRUE(parser.RightArrow().has_value());
  EXPECT_TRUE(parser.StrLiteral().has_value());
  EXPECT_TRUE(parser.Semicolon().has_value());

  EXPECT_EQ(parser.GetToken(0).type_, TokenType::kIdentifier);
  EXPECT_EQ(parser.GetToken(0).body_, "test");

  EXPECT_EQ(parser.GetToken(1).type_, TokenType::kRightArrow);
  EXPECT_EQ(parser.GetToken(1).body_, "->");

  EXPECT_EQ(parser.GetToken(2).type_, TokenType::kStrLiteral);
  EXPECT_EQ(parser.GetToken(2).body_, "a");

  EXPECT_EQ(parser.GetToken(3).type_, TokenType::kSemicolon);
  EXPECT_EQ(parser.GetToken(3).body_, ";");
}

TEST(MetaGrammar, Parser_2) {
  auto parser = MetaParser(TEST_GRAMMAR_FILE_2);
  while (!parser.IsFinished()) {
    auto res = parser.Identifier()
                   .and_then([](auto self) { return self->RightArrow(); })
                   .and_then([](auto self) { return self->StrLiteral(); })
                   .and_then([](auto self) { return self->Semicolon(); });
    EXPECT_TRUE(res.has_value());
  }
  EXPECT_EQ(parser.GetToken(0).type_, TokenType::kIdentifier);
  EXPECT_EQ(parser.GetToken(0).body_, "abcd");
  EXPECT_EQ(parser.GetToken(1).type_, TokenType::kRightArrow);
  EXPECT_EQ(parser.GetToken(1).body_, "->");
  EXPECT_EQ(parser.GetToken(2).type_, TokenType::kStrLiteral);
  EXPECT_EQ(parser.GetToken(2).body_, "xyz");
  EXPECT_EQ(parser.GetToken(3).type_, TokenType::kSemicolon);
  EXPECT_EQ(parser.GetToken(3).body_, ";");

  EXPECT_EQ(parser.GetToken(4).type_, TokenType::kIdentifier);
  EXPECT_EQ(parser.GetToken(4).body_, "中文标识");
  EXPECT_EQ(parser.GetToken(5).type_, TokenType::kRightArrow);
  EXPECT_EQ(parser.GetToken(5).body_, "->");
  EXPECT_EQ(parser.GetToken(6).type_, TokenType::kStrLiteral);
  EXPECT_EQ(parser.GetToken(6).body_, "中文字符串");
  EXPECT_EQ(parser.GetToken(7).type_, TokenType::kSemicolon);
  EXPECT_EQ(parser.GetToken(7).body_, ";");
}

TEST(MetaGrammar, ParserStrLiteralUnion) {
  auto parser = MetaParser(TEST_GRAMMAR_FILE_3);
  while (!parser.IsFinished()) {
    auto res = parser.Identifier()
                   .and_then([](auto self) { return self->RightArrow(); })
                   .and_then([](auto self) { return self->StrLiteralUnion(); })
                   .and_then([](auto self) { return self->Semicolon(); });
    EXPECT_TRUE(res.has_value());
  }

  EXPECT_EQ(parser.GetToken(0).type_, TokenType::kIdentifier);
  EXPECT_EQ(parser.GetToken(0).body_, "abcd");
  EXPECT_EQ(parser.GetToken(1).type_, TokenType::kRightArrow);
  EXPECT_EQ(parser.GetToken(1).body_, "->");
  EXPECT_EQ(parser.GetToken(2).type_, TokenType::kStrLiteral);
  EXPECT_EQ(parser.GetToken(2).body_, "xyz");
  EXPECT_EQ(parser.GetToken(3).type_, TokenType::kSemicolon);
  EXPECT_EQ(parser.GetToken(3).body_, ";");

  EXPECT_EQ(parser.GetToken(4).type_, TokenType::kIdentifier);
  EXPECT_EQ(parser.GetToken(4).body_, "xyz");
  EXPECT_EQ(parser.GetToken(5).type_, TokenType::kRightArrow);
  EXPECT_EQ(parser.GetToken(5).body_, "->");
  EXPECT_EQ(parser.GetToken(6).type_, TokenType::kStrLiteral);
  EXPECT_EQ(parser.GetToken(6).body_, "abcd");
  EXPECT_EQ(parser.GetToken(7).type_, TokenType::kUnion);
  EXPECT_EQ(parser.GetToken(7).body_, "|");
  EXPECT_EQ(parser.GetToken(8).type_, TokenType::kStrLiteral);
  EXPECT_EQ(parser.GetToken(8).body_, "uvw");
  EXPECT_EQ(parser.GetToken(9).type_, TokenType::kSemicolon);
  EXPECT_EQ(parser.GetToken(9).body_, ";");
}
