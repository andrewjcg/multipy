// Copyright (c) Meta Platforms, Inc. and affiliates.
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#ifndef MULTIPY_EXCEPTION_H
#define MULTIPY_EXCEPTION_H

#include <exception>
#include <stdexcept>

#define MULTIPY_INTERNAL_ASSERT_WITH_MESSAGE(condition, message)               \
  if (!(condition)) {                                                          \
    throw std::runtime_error(                                                  \
        "Internal Assertion failed: (" + std::string(#condition) + "), " +     \
        "function " + __FUNCTION__ + ", file " + __FILE__ + ", line " +        \
        std::to_string(__LINE__) + ".\n" + "Please report bug to Pytorch.\n" + \
        message + "\n");                                                       \
  }

#define MULTIPY_INTERNAL_ASSERT_NO_MESSAGE(condition) \
  MULTIPY_INTERNAL_ASSERT_WITH_MESSAGE(condition, #condition)

#define MULTIPY_INTERNAL_ASSERT_(x, condition, message, FUNC, ...) FUNC

#define MULTIPY_INTERNAL_ASSERT(...)                     \
  MULTIPY_INTERNAL_ASSERT_(                              \
      ,                                                  \
      ##__VA_ARGS__,                                     \
      MULTIPY_INTERNAL_ASSERT_WITH_MESSAGE(__VA_ARGS__), \
      MULTIPY_INTERNAL_ASSERT_NO_MESSAGE(__VA_ARGS__));

#define MULTIPY_CHECK_WITH_MESSAGE(condition, message)                      \
  if (!(condition)) {                                                       \
    throw std::runtime_error(                                               \
        "Check failed: (" + std::string(#condition) + "), " + "function " + \
        __FUNCTION__ + ", file " + __FILE__ + ", line " +                   \
        std::to_string(__LINE__) + ".\n" + message + "\n");                 \
  }

#define MULTIPY_CHECK_NO_MESSAGE(condition) \
  MULTIPY_CHECK_WITH_MESSAGE(condition, #condition)

#define MULTIPY_CHECK_(x, condition, message, FUNC, ...) FUNC

#define MULTIPY_CHECK(...)                     \
  MULTIPY_CHECK_(                              \
      ,                                        \
      ##__VA_ARGS__,                           \
      MULTIPY_CHECK_WITH_MESSAGE(__VA_ARGS__), \
      MULTIPY_CHECK_NO_MESSAGE(__VA_ARGS__));

#endif // MULTIPY_EXCEPTION_H

namespace torch {
namespace deploy {
class MultipyEmbeddedException : public std::runtime_error {
 public:
  explicit MultipyEmbeddedException(const std::string& error)
      : std::runtime_error(error) {}
};
} // namespace deploy
} // namespace torch