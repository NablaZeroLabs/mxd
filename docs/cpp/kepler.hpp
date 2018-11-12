/// @file  kepler.hpp
/// @brief Example solution of Kepler's equation.
/// @date  November 06, 2018

#pragma once

// C++ Standard Library
#include <cassert>
#include <cmath>
#include <limits>

namespace mxd {

/// @brief Solve Kepler's equation with a naive algorithm.
/// @tparam T Floating-point type.
/// @param ecc Orbital eccentricity.
/// @param man Mean anomaly, rad.
/// @param max_iter Maximum number of iterations.
/// @param tolerance Desired numerical tolerance.
/// @return Eccentric anomaly, rad.
/// @exceptions std::runtime_error if the algorithm cannot converge to within
/// @p tolerance in @p max_iter iterations.
template <typename T>
inline T kepler(T ecc, T man, std::size_t max_iter, T tolerance) {
  assert((ecc >= 0) and (ecc < 1));  /// @TODO Study what is `assert`.
  assert(tolerance >=
         std::numeric_limits<T>::epsilon());  ///@TODO Why is this check needed?

  T ean{man};
  T fval{ean - ecc * std::sin(ean) - man};

  std::size_t current_iter = 0;
  while (current_iter++ <= max_iter) {
    if (std::abs(fval) <= tolerance) {
      return ean;
    }

    T dval{1 - ecc * std::cos(ean)};
    T step{-(fval / dval)};

    ean += step;

    fval = (ean - ecc * std::sin(ean) - man);
  }

  // We will only reach this point if max_iter was exceeded. Exceptions are one
  // of many ways to handle errors. In this case, it should be a truly
  // exceptional circumstance to fail convergence. An alternative to exceptions
  // are error conditions and status codes.

  std::ostringstream oss;
  // Numerical output will contain the full precision of the underlying type in
  // scientific notation. The required width is precision + 7:
  //
  //     123[p digits]4567
  //     -9.[........]E+99
  ///
  auto p = std::numeric_limits<T>::max_digits10;
  auto w = p + 7;

  oss << std::scientific << std::setprecision(p)
      << "Kepler reached the maximum number of iterations (" << max_iter
      << ") without satisfying the desired tolerance.\n"
      << "|f|: " << std::setw(w) << fval << "\n"
      << "tol: " << std::setw(w) << tolerance << "\n";

  throw std::runtime_error(oss.str());
}

/// @brief Solve Kepler's equation with a naive algorithm.
/// @tparam T Floating-point type.
/// @param ecc Orbital eccentricity.
/// @param man Mean anomaly, rad.
/// @return Eccentric anomaly, rad.
/// @exceptions std::runtime_error if the algorithm cannot converge to within
/// machine epsilon for `T` in ten iterations.
/// @note We also provide an overload of this function that allows you to
/// control number of iterations and tolerance.
template <typename T>
inline T kepler(T ecc, T man) {
  const std::size_t max_iter = 10;
  const T tolerance = std::numeric_limits<T>::epsilon();
  return kepler(ecc, man, max_iter, tolerance);
}

}  // namespace mxd
