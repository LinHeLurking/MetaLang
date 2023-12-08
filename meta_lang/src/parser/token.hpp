#ifndef METALANG_TOKEN_HPP
#define METALANG_TOKEN_HPP

#include <concepts>
#include <type_traits>

#include "./token_type.hpp"

namespace meta_lang::parser {

class TokenPtr;

class Token {
 public:
  [[nodiscard]] TokenType Type() const noexcept { return t_; }

  template <class T>
    requires std::integral<T> || std::floating_point<T>
  [[nodiscard]] std::remove_const_t<T> As() const noexcept {
    return *reinterpret_cast<T*>(const_cast<char*>(body_));
  }

  template <class T>
    requires std::is_same_v<T, const char*>
  [[nodiscard]] auto As() const noexcept {
    return reinterpret_cast<const char*>(body_);
  }

  [[nodiscard]] auto AsStr() const noexcept { return As<const char*>(); }

 private:
  friend class TokenPtr;
  TokenType t_;
  char body_[0];  // placeholder
};
static_assert(sizeof(Token) <= 4);  // Bodies are hidden :P

class TokenPtr {
 public:
  TokenPtr() = delete;
  TokenPtr(const TokenPtr&) = default;
  TokenPtr(TokenPtr&& rhs) = default;

  explicit TokenPtr(TokenType t) {
    p_.reset(new char[sizeof(Token)]);
    reinterpret_cast<Token*>(p_.get())->t_ = t;
#ifndef NDEBUG
    _token_ = reinterpret_cast<Token*>(p_.get());
#endif
  }

  TokenPtr(TokenType t, const char* name, size_t len) {
    p_.reset(new char[sizeof(Token) + len + 1]);
    reinterpret_cast<Token*>(p_.get())->t_ = t;
    auto p = p_.get() + sizeof(Token);
    memcpy(p, name, len);
    p[len] = '\0';
#ifndef NDEBUG
    _token_ = reinterpret_cast<Token*>(p_.get());
#endif
  }

  TokenPtr(TokenType t, const char* name) {
    size_t len = strlen(name);
    p_.reset(new char[sizeof(Token) + len + 1]);
    reinterpret_cast<Token*>(p_.get())->t_ = t;
    auto p = p_.get() + sizeof(Token);
    memcpy(p, name, len);
    p[len] = '\0';
#ifndef NDEBUG
    _token_ = reinterpret_cast<Token*>(p_.get());
#endif
  }

  Token* operator->() const noexcept {
    return reinterpret_cast<Token*>(p_.get());
  }
  Token& operator*() const noexcept {
    return *reinterpret_cast<Token*>(p_.get());
  }

 private:
  std::shared_ptr<char[]> p_;

#ifndef NDEBUG
  const Token* _token_ = nullptr;
#endif
};

}  // namespace meta_lang::parser

#endif  // METALANG_TOKEN_HPP
