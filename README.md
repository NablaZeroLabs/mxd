# `mxd` &mdash; Space Mission Design Support Tools


## Developer Guidelines

`mxd` is built of components. A component is a triplet (`name.hpp`, `name.cpp`,
`name.t.cpp`) with the following characteristics:

* `name.hpp` Declares the interface for the component.
* `name.cpp` Defines the implementation of the component.
* `name.t.cpp` Provides unit tests for the component.

All components live under `src` in a flat arrangement (no sub-folders). In the
future, when we understand `mxd` better, we may sub-divide `src` into
sub-directories, but not right now.

Some hard rules:

* `name.hpp` cannot `#include` any third-party library. Only C++ Standard
  Library and possibly other headers from the `mxd` library.

* `name.cpp` will add `#include "name.hpp"` as the first line of source code.

* `name.t.cpp` will add `#include "name.hpp"` as the first line of source code.

* All tests are written using Google Test Framework and are named after the
  component/feature they test. Additionally, they will be stand-alone (will have
  a `int main()`). For example:

```c++
TEST(Name, FeatureWithinName) {
// ... some assertion.
}

TEST(Name, AnotherFeatureWithinName) {
// ... some assertion.
}

TEST(Name, YetAnotherFeatureWithinName) {
// ... some assertion.
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

Some guidelines:

* We use UNIX newlines: `\n` (as opposed to Windows newlines `\r\n`). Please
  configure your Git client to clean the newlines before storing the commit
  (Google how to do it).
