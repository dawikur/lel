// Copyright 2016, Dawid Kurek, <dawikur@gmail.com>

#ifndef TEST_UNIT_SEG_TEST_HPP_
#define TEST_UNIT_SEG_TEST_HPP_

#include "gtest/gtest.h"

#ifdef SEG_HAS_BOOST
# include <boost/core/demangle.hpp>
#endif  // SEG_HAS_BOOST

template <typename T1, typename T2>
::testing::AssertionResult AssertSameType(const char *T1_str,
                                          const char *T2_str,
                                          const T1 * /*T1_*/,
                                          const T2 & /*T2_*/) {
  if (std::is_same<T1, T2>::value)
    return ::testing::AssertionSuccess();

  return ::testing::AssertionFailure()
         << "Types incorrect: " << T1_str << " , " << T2_str
         << "\n       Expected: " << typeid(T1).name()
#ifdef SEG_HAS_BOOST
         << "\n       Which is: " << boost::core::demangle(typeid(T1).name())
#endif  // SEG_HAS_BOOST
         << std::endl
         << "\n         Actual: " << typeid(T2).name()
#ifdef SEG_HAS_BOOST
         << "\n       Which is: " << boost::core::demangle(typeid(T2).name())
#endif  // SEG_HAS_BOOST
         << std::endl;
}

#define ASSERT_SAME(T1, T2)                                                    \
  ASSERT_PRED_FORMAT2(AssertSameType, (T1 *) nullptr, T2);

template <class Type>
void Unused(Type const&) {}

#endif  // TEST_UNIT_SEG_TEST_HPP_

