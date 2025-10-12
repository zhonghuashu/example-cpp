example-cpp
=================================
# Introduction
Example C/C++ code:
- C/C++ programming under Linux / WSL environment.
- CMake for cross-compiler under different target platform (x86 / ARM).
- Common code style and naming convention definition.
- SonarQube / SonarLint for static code check.
- Doxygen for code comments and API documentation generation.
- GoogleTest for unit test framework.

Contribute code in the project should adhere to the standards and conventions outlined here:
- [Product vision and goals](./PRODUCT.md): Understand the high-level vision and objectives of the product to ensure alignment with business goals.
- [System architecture and design Principles](./ARCHITECTURE.md): Overall system architecture, design patterns, and design principles that guide the development process.
- [Contributing guidelines](./CONTRIBUTING.md): Overview of the project's contributing guidelines and collaboration practices.

Suggest to update these documents if you find any incomplete or conflicting information during your work.

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
- Debug code
  - Select CMake panel: Debug target
  - Select Debug panel: Launch gdb
- Start unit test via select menu `View > Testing`
