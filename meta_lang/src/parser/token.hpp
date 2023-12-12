#ifndef METALANG_TOKEN_HPP
#define METALANG_TOKEN_HPP

#include <concepts>

#include "./token_type.hpp"

namespace meta_lang::parser {

class TokenPtr;

class Token {
  friend class TokenPtr;
  TokenType t_;
  char body_[0];  // placeholder
};
static_assert(sizeof(Token) <= 4);  // Bodies are hidden :P

class TokenPtr {
#define MY_TOKEN reinterpret_cast<Token*>(p_)
 public:
  template <class T>
    requires std::integral<T> || std::floating_point<T> || std::is_enum_v<T>
  [[nodiscard]] std::remove_const_t<T> As() const noexcept {
    return *reinterpret_cast<T*>(MY_TOKEN->body_);
  }

  template <class T>
    requires std::is_same_v<T, char*> || std::is_same_v<T, const char*>
  [[nodiscard]] auto As() const noexcept {
    return reinterpret_cast<T>(MY_TOKEN->body_);
  }

  [[nodiscard]] auto AsStr() const noexcept { return As<const char*>(); }

  [[nodiscard]] auto Type() const noexcept { return MY_TOKEN->t_; }

  TokenPtr() = delete;
  TokenPtr(const TokenPtr& rhs) {
    size_t len = sizeof(Token) + strlen(rhs.AsStr() + sizeof(Token)) + 1;
    p_ = reinterpret_cast<Token*>(new char[len]);
    memcpy(p_, rhs.p_, len);
  }
  TokenPtr(TokenPtr&& rhs) noexcept {
    p_ = rhs.p_;
    rhs.p_ = nullptr;
  }

  ~TokenPtr() { delete[] p_; }

  explicit TokenPtr(TokenType t) {
    size_t len = sizeof(Token);
    p_ = static_cast<Token*>(malloc(len));
    MY_TOKEN->t_ = t;
  }

  TokenPtr(TokenType t, const char* name, size_t name_len) {
    size_t len = sizeof(Token) + name_len + 1;
    p_ = static_cast<Token*>(malloc(len));
    MY_TOKEN->t_ = t;
    memcpy(MY_TOKEN->body_, name, name_len);
    As<char*>()[name_len - 1] = '\0';
  }

  TokenPtr(TokenType t, const char* name) {
    size_t name_len = strlen(name);
    size_t len = sizeof(Token) + name_len + 1;
    p_ = static_cast<Token*>(malloc(len));
    MY_TOKEN->t_ = t;
    memcpy(MY_TOKEN->body_, name, name_len);
    As<char*>()[name_len - 1] = '\0';
  }

  template <class T>
    requires std::is_enum_v<T>
  TokenPtr(TokenType t, T k) {
    size_t len = sizeof(Token) + sizeof(k);
    p_ = static_cast<Token*>(malloc(len));
    MY_TOKEN->t_ = t;
    memcpy(MY_TOKEN->body_, &k, sizeof(k));
  }

 private:
  Token* p_ = nullptr;
#undef MY_TOKEN
};

}  // namespace meta_lang::parser

#endif  // METALANG_TOKEN_HPP
