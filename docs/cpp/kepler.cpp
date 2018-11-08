/// @file  kepler.cpp
/// @brief Run example solutions of Kepler's equation.
/// @date  November 06, 2018

// C++ Standard Library
#include <cmath>
#include <iomanip>
#include <iostream>

// mxd Library
#include "kepler.hpp"

int main() {
  double ecc;
  double man;

  std::cout << std::scientific << std::setprecision(16);

  while (true) {
    std::cout << "enter eccentricity and mean anomaly: " << std::flush;

    if ((not(std::cin >> ecc >> man))) {
      std::cout << "[exit] parameters not correct << std::endl";
      return 0;
    }
    
    if((ecc >= 1) or (ecc < 0)){
        std::cout << "[exit] eccentricity is not within domain: 0 <= ecc < 1" << std::endl;
      return 0;
    }

    std::cout << "solving new problem\n"
              << "ecc = " << std::setw(23) << ecc << "\n"
              << "man = " << std::setw(23) << man << std::endl;

    double ean = mxd::kepler(ecc, man);
    double error = ean - ecc * std::sin(ean) - man;

    std::cout << "ean = " << std::setw(23) << ean << "\n"
              << "err = " << std::setw(23) << error << std::endl;
  }
}
