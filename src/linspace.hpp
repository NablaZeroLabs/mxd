// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      linspace.hpp
/// @brief     A linearly-spaced vector of values.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      December 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace nzl {

/// @brief Generate a linearly-spaced vector of values.
/// @tparam P Type of the initial bound
/// @tparam Q Type fo the final bound
/// @param begin Initial bound
/// @param end Final bound
/// @param n Number of points (n >= 2).
/// @return std::vector<T>, where @p T is the promoted type, containing @p n
/// equally-spaced points [begin, ..., end].
/// @throws std::runtime_error if n < 2.
/// @note To derive the promoted type, we first promote independently @p P and
/// @p Q to at least @p float (or leave unchanged if already float or higher
/// precision). We then find the common type of the promoted @p P and promoted
/// @p Q to derive the @p T.
/// @note Other classes provide linspace specializations (e.g., TimePoint).
template <typename P, typename Q>
auto linspace(P begin, Q end, std::size_t n = 100) {
  using PromotedP = typename std::common_type<P, float>::type;
  using PromotedQ = typename std::common_type<Q, float>::type;
  using T = typename std::common_type<PromotedP, PromotedQ>::type;
  T b = begin;
  T e = end;
  if (n < 2) {
    std::ostringstream oss;
    oss << "linspace must have at least two points (you requested " << n << ")";
    throw std::runtime_error(oss.str());
  } else if (n == 2) {
    return std::vector<T>{b, e};
  } else {
    std::vector<T> result(n);
    const auto step = (e - b) / (n - 1);
    result[0] = b;
    for (auto k = 1u; k < n - 1; ++k) {
      result[k] = result[k - 1] + step;
    }
    result[n - 1] = e;
    return result;
  }
}

}  // namespace nzl
