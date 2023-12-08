#ifndef METALANG_EXPECETD_HPP
#define METALANG_EXPECETD_HPP

#ifndef E_TRY
#define E_TRY(expr)                       \
  ({                                      \
    auto _v = std::move(expr);            \
    if (!bool(_v)) {                      \
      return std::unexpected(_v.error()); \
    }                                     \
    std::move(_v.value());                \
  })
#endif

#ifndef E_RET
#define E_RET(expr) \
  { return std::unexpected{expr}; }
#endif

#endif  // METALANG_EXPECETD_HPP
