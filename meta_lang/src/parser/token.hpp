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
  TokenPtr() = delete;
  TokenPtr(const TokenPtr& rhs) {
    size_t len = sizeof(Token) + strlen(rhs.p_ + sizeof(Token)) + 1;
    p_ = new char[len];
    memcpy(p_, rhs.p_, len);
#ifndef NDEBUG
    tk_ = reinterpret_cast<Token*>(p_);
#endif
  }
  TokenPtr(TokenPtr&& rhs) noexcept {
    p_ = rhs.p_;
    rhs.p_ = nullptr;
#ifndef NDEBUG
    tk_ = reinterpret_cast<Token*>(p_);
#endif
  }

  ~TokenPtr() { delete[] p_; }

  explicit TokenPtr(TokenType t) {
    size_t len = sizeof(Token) + 1;
    p_ = static_cast<char*>(malloc(len));
    MY_TOKEN->t_ = t;
    p_[len - 1] = '\0';
#ifndef NDEBUG
    tk_ = reinterpret_cast<Token*>(p_);
#endif
  }

  TokenPtr(TokenType t, const char* name, size_t name_len) {
    size_t len = sizeof(Token) + name_len + 1;
    p_ = static_cast<char*>(malloc(len));
    MY_TOKEN->t_ = t;
    memcpy(MY_TOKEN->body_, name, name_len);
    p_[len - 1] = '\0';
#ifndef NDEBUG
    tk_ = reinterpret_cast<Token*>(p_);
#endif
  }

  TokenPtr(TokenType t, const char* name) {
    size_t name_len = strlen(name);
    size_t len = sizeof(Token) + name_len + 1;
    p_ = static_cast<char*>(malloc(len));
    MY_TOKEN->t_ = t;
    memcpy(MY_TOKEN->body_, name, name_len);
    p_[len - 1] = '\0';
#ifndef NDEBUG
    tk_ = reinterpret_cast<Token*>(p_);
#endif
  }

  template <class T>
    requires std::integral<T> || std::floating_point<T>
  [[nodiscard]] std::remove_const_t<T> As() const noexcept {
    return *reinterpret_cast<T*>(MY_TOKEN->body_);
  }

  template <class T>
    requires std::is_same_v<T, const char*>
  [[nodiscard]] const char* As() const noexcept {
    return reinterpret_cast<T>(MY_TOKEN->body_);
  }

  [[nodiscard]] auto AsStr() const noexcept { return As<const char*>(); }

  [[nodiscard]] auto Type() const noexcept { return MY_TOKEN->t_; }

 private:
  char* p_ = nullptr;
#undef MY_TOKEN

#ifndef NDEBUG
  Token* tk_ = reinterpret_cast<Token*>(p_);
#endif
};

}  // namespace meta_lang::parser

#endif  // METALANG_TOKEN_HPP
