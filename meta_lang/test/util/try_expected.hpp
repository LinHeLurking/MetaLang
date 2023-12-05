#ifndef METALANG_TRY_EXPECTED_HPP
#define METALANG_TRY_EXPECTED_HPP

#include <gtest/gtest.h>

#ifndef E_TRY
#define E_TRY(expr)          \
  ({                       \
    auto _v = (expr);      \
    ASSERT_TRUE(bool(_v)); \
    std::move(*_v);        \
  })
#endif

#endif  // METALANG_TRY_EXPECTED_HPP