#include <gtest/gtest.h>

#include "src/parser/meta/meta_grammar.hpp"

using namespace meta_lang::meta_grammar::parser;

TEST(MetaGrammar, Parser_1) {
  auto parser = MetaParser(TEST_GRAMMAR_FILE_1);
  ASSERT_TRUE(parser.Identifier().has_value());
  ASSERT_TRUE(parser.RightArrow().has_value());
  ASSERT_TRUE(parser.StrLiteral().has_value());
  ASSERT_TRUE(parser.Semicolon().has_value());

  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kIdentifier);
    ASSERT_EQ(t.body_, "test");
  }

  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kRightArrow);
    ASSERT_EQ(t.body_, "->");
  }

  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kStrLiteral);
    ASSERT_EQ(t.body_, "a");
  }

  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kSemicolon);
    ASSERT_EQ(t.body_, ";");
  }
}

TEST(MetaGrammar, Parser_2) {
  auto parser = MetaParser(TEST_GRAMMAR_FILE_2);
  while (!parser.IsFinished()) {
    auto res = parser.Identifier()
                   .and_then([](auto self) { return self->RightArrow(); })
                   .and_then([](auto self) { return self->StrLiteral(); })
                   .and_then([](auto self) { return self->Semicolon(); });
    ASSERT_TRUE(res.has_value());
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kIdentifier);
    ASSERT_EQ(t.body_, "abcd");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kRightArrow);
    ASSERT_EQ(t.body_, "->");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kStrLiteral);
    ASSERT_EQ(t.body_, "xyz");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kSemicolon);
    ASSERT_EQ(t.body_, ";");
  }

  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kIdentifier);
    ASSERT_EQ(t.body_, "中文标识");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kRightArrow);
    ASSERT_EQ(t.body_, "->");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kStrLiteral);
    ASSERT_EQ(t.body_, "中文字符串");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kSemicolon);
    ASSERT_EQ(t.body_, ";");
  }
}

TEST(MetaGrammar, ParserStrLiteralUnion) {
  auto parser = MetaParser(TEST_GRAMMAR_FILE_3);
  auto res = parser.Tokenize();
  ASSERT_TRUE(res.has_value());

  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kIdentifier);
    ASSERT_EQ(t.body_, "abcd");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kRightArrow);
    ASSERT_EQ(t.body_, "->");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kStrLiteral);
    ASSERT_EQ(t.body_, "xyz");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kSemicolon);
    ASSERT_EQ(t.body_, ";");
  }

  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kIdentifier);
    ASSERT_EQ(t.body_, "xyz");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kRightArrow);
    ASSERT_EQ(t.body_, "->");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kStrLiteral);
    ASSERT_EQ(t.body_, "abcd");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kUnion);
    ASSERT_EQ(t.body_, "|");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kStrLiteral);
    ASSERT_EQ(t.body_, "uvw");
  }
  {
    auto t = parser.ConsumeToken();
    ASSERT_EQ(t.type_, TokenType::kSemicolon);
    ASSERT_EQ(t.body_, ";");
  }
}

TEST(MetaGrammar, ParserAst) {
  auto parser = MetaParser(TEST_GRAMMAR_FILE_3);
  {
    auto res = parser.Tokenize();
    ASSERT_TRUE(res.has_value());
  }
  {
    auto res = parser.BuildAst();
    ASSERT_TRUE(res.has_value());
  }
  auto &ast = parser.GetAst();
  ASSERT_EQ(ast.type_, AstNodeType::kGrammar);
  for (auto &rule : ast.children_) {
    ASSERT_EQ(rule.type_, AstNodeType::kRule);
  }
  ASSERT_EQ(ast.children_.size(), 2);
  {
    auto &rule = ast.children_[0];
    ASSERT_EQ(rule.children_.size(), 2);
    auto &id = rule.children_[0];
    ASSERT_EQ(id.type_, AstNodeType::kIdentifier);
    auto &str_literal = rule.children_[1];
    ASSERT_EQ(str_literal.type_, AstNodeType::kStrLiteral);
  }
  {
    auto rule = ast.children_[1];
    ASSERT_EQ(rule.children_.size(), 2);
    auto &id = rule.children_[0];
    ASSERT_EQ(id.type_, AstNodeType::kIdentifier);
    auto &literal_union = rule.children_[1];
    ASSERT_EQ(literal_union.type_, AstNodeType::kStrLiteralUnion);
    auto &literals = literal_union.children_;
    ASSERT_EQ(literals.size(), 2);
    for (auto &literal : literals) {
      ASSERT_EQ(literal.type_, AstNodeType::kStrLiteral);
    }
    auto &abcd = literals[0];
    ASSERT_EQ(abcd.body_, "abcd");
    auto &uvw = literals[1];
    ASSERT_EQ(uvw.body_, "uvw");
  }
}