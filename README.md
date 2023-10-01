example-cpp
=================================
# Introduction
Sample code C/C++ building system for Linux:
- Common code style and naming convention definition.
- SonarQube / SonarLint for static code check.
- Doxygen for code comments and API documentation generation.
- GoogleTest for unit test framework.
- CMake for cross-compiler under different target platform (x86 / ARM).

# Build for ARM Linux
```shell
mkdir build_arm && cd build_arm

# Run CMake to configure the project and generate a native build system.
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-linux-gnueabihf-gcc.cmake

# Call that build system to actually compile/link the project.
# Make building with cmake verbose: --verbose
# Clean build: --target clean
cmake --build .

# Install the binaries that we had built from the source code.
cmake --install .

# Build installation packages that support binary installations.
# -C debug
cpack
```

# Build for x86 Linux
```shell
mkdir build_x86_64 && cd build_x86_64

# Run CMake to configure the project and generate a native build system.
cmake ..
```

# Unit test
```shell
# Run unit test.
./build/ut-main
[==========] Running 12 tests from 7 test suites.
[----------] Global test environment set-up.
[----------] 1 test from MyTest
[ RUN      ] MyTest.AddTest
[       OK ] MyTest.AddTest (0 ms)
[----------] 1 test from MyTest (0 ms total)
...
[----------] Global test environment tear-down
[==========] 12 tests from 7 test suites ran. (6 ms total)
[  PASSED  ] 12 tests.

# Run unit test with lcov code coverage report under ./coverage/report/index.html
./unittest.sh
```

# VSCode
- Debug code via select menu `View > Command Paletter > CMake: Debug`
- Start unit test via select menu `View > Testing`