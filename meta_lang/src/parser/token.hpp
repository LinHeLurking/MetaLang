#ifndef METALANG_TOKEN_HPP
#define METALANG_TOKEN_HPP

#include "./token_type.hpp"

namespace meta_lang::parser {

class Token {
 public:
  using Type = _lexer_detail::TokenType;
  Type t_;
  char body_[0];  // name placeholder
};
static_assert(sizeof(Token) <= 4);  // Bodies are hidden :P

class TokenPtr {
 public:
  TokenPtr() = delete;

  explicit TokenPtr(Token::Type t) {
    token_ = new Token;
    token_->t_ = t;
  }

  TokenPtr(Token::Type t, void* body, size_t body_size) {
    // handcrafted in-place construction
    auto p = new char[sizeof(Token) + body_size + 1];
    token_ = reinterpret_cast<Token*>(p);
    token_->t_ = t;
    token_->body_[body_size] = '\0';
    memcpy(p + sizeof(Token), body, body_size);
  }

  bool operator==(void* ptr) const noexcept { return token_ == ptr; }
  bool operator!=(void* ptr) const noexcept { return token_ != ptr; }

  ~TokenPtr() { free(token_); }

  [[nodiscard]] Token::Type Type() const noexcept {
    assert(token_ != nullptr);
    return token_->t_;
  }

  [[nodiscard]] const char* Name() const noexcept { return token_->body_; }

  template <class T>
    requires std::is_same_v<T, std::remove_cvref_t<T>>
  T As() const noexcept {
    return *reinterpret_cast<T*>(token_->body_);
  }

  TokenPtr* operator->() { return this; }

 private:
  Token* token_;
};

}  // namespace meta_lang::parser

#endif  // METALANG_TOKEN_HPP
