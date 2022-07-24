# libasdf

### header


 1. **shared object library** `bin/libasdf.so`,
 2. **A command line binary `bin/sample`**, which links with the library,
 3. **An executable unit test** `bin/asdf_tests`
 4. **An optional BASH build script** `build-and-run` that you can use to quickly test if the project compiles, and runs.

## Usage

### Prerequisites

You will need:

 * A modern C/C++ compiler
 * CMake 3.1+ installed (on a Mac, run `brew install cmake`)

### Building The Project

#### Running the tests

```bash
❯ bin/asdf_tests
```

#### Running the CLI Executable

TODO:

```

### Using it as a C++ Library

We build a shared object, c++ usage:

```cpp
```

## File Locations

 * `src/*` — C++ code that ultimately compiles into a shared object
 * `test/lib` — C++ libraries used for tests
 * `test/src` — C++ test suite
 * `bin/`, `lib`, `include` are all empty directories, until the `make install` install the project artifacts there.

Tests:

 * A `test` folder with the automated tests and fixtures that mimics the directory structure of `src`.
 * For every C++ file in `src/A/B/<name>.cpp` there is a corresponding test file `test/A/B/<name>_test.cpp`
 * Tests compile into a single binary `test/bin/runner` that is run on a command line to run the tests.
 
### License

Open sourced under MIT license, the terms of which can be read here — [MIT License](http://opensource.org/licenses/MIT).
