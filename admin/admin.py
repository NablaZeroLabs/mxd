# -*- coding:utf-8; mode:python; mode:auto-fill; fill-column:79; -*-
"""
admin.py

This tool provides some handy features to ease mxd development.

J. Arrieta, Nabla Zero Labs
"""

# Python Standard Library
import os
import sys
import argparse
import datetime

_HPP_TEMPLATE = """\
// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      {component}.hpp
/// @brief
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      {date:%B %d, %Y}
/// @copyright (C) {date:%Y} Nabla Zero Labs

#pragma once

// C++ Standard Library

// mxd Library

namespace nzl {{


}}  // namespace nzl
"""

_CPP_TEMPLATE = """\
// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      {component}.cpp
/// @brief     Implementation of {component}.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      {date:%B %d, %Y}
/// @copyright (C) {date:%Y} Nabla Zero Labs

// Related mxd header
#include "{component}.hpp"

// C++ Standard Library

// mxd Library

namespace nzl {{



}}  // namespace nzl
"""

_TPP_TEMPLATE = """\
// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      {component}.t.cpp
/// @brief     Unit tests for {component}.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      {date:%B %d, %Y}
/// @copyright (C) {date:%Y} Nabla Zero Labs

// Related mxd header
#include "{component}.hpp"

// C++ Standard Library

// mxd Library

// Google Test Framework
#include <gtest/gtest.h>

TEST( {component}, Failing ) {{
    ASSERT_TRUE( false ) << "You must add unit tests for {component}.hpp";
}}

int main( int argc, char** argv ) {{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}}
"""
def write(component, template, path):
    date = datetime.datetime.now()
    if os.path.exists(path):
        print(f"I will not overwrite {path}... skipping")
    else:
        with open(path, "wb") as fp:
            print(f"writing {path}")
            text = template.format(date=date, component=component).encode("utf-8")
            fp.write(text)

def dispatch(args):
    component = args.component

    cpp = f"{component}.cpp"
    hpp = f"{component}.hpp"
    tpp = f"{component}.t.cpp"

    write(component, _HPP_TEMPLATE, hpp)
    write(component, _CPP_TEMPLATE, cpp)
    write(component, _TPP_TEMPLATE, tpp)

def parse_commandline():
    parser = argparse.ArgumentParser(description="Developer support for mxd Library")
    parser.add_argument("component", help="Create files for the given component")
    return parser.parse_args()

def main():
    args = parse_commandline()
    return dispatch(args)

if __name__ == "__main__":
    sys.exit(main())
