# Copilot Instructions for example-cpp

This document provides guidelines and context for using GitHub Copilot or similar AI coding assistants in the `example-cpp` codebase.

## Project Overview
- **Type:** C/C++ multi-target project (x86_64, ARM)
- **Build System:** CMake
- **Structure:**
  - `src/` — Main source code (modules: fileio, math_func, thread, usage, etc.)
  - `test/` — Unit tests
  - `build_x86_64/`, `build_arm/` — Out-of-source build directories
  - `cmake/` — Toolchain and CMake helper scripts

## Coding Style
- **Naming:**
  - Use `camelCase` for variables and function names (e.g., `myVariable`, `calculateSum`).
  - Use `PascalCase` for class/struct names (e.g., `MyClass`).
  - Use `UPPER_SNAKE_CASE` for macros and constants (e.g., `MAX_SIZE`).
  - Use `std::` library features where applicable (e.g., `std::vector`, `std::string`, `std::thread`).
  - Start with a module abbreviation (module_functionName) for C exported function name or global variable, e.g., `i2c_sendBuffer()`, `int i2c_busStatus()`.
  - Start with prefix `m_` for C++ class member (e.g., `m_someClassMember`).
  - Start with prefix `m` for C static file variable (e.g., `mSomeStaticVar`).
- **File Names:** Use lowercase with underscores (e.g., `math_func.cpp`).
- **Indentation:** 4 spaces per level.
- **Comments:**
  - Use English for code comments and documentation.
  - Use doxygen javadoc style for function/class documentation.
  - Begin comment text with an uppercase letter, end comment text with a period.
- **Error Handling:**
  - Use consistent error handling strategies (e.g., return codes, exceptions).
  - Document error cases and recovery strategies.
- **Namespace**:
  - Use a consistent naming scheme for namespaces, following the same rules as for file names.
  - Use unnamed namespace for static global variable or function.
- **Open braces**: Place the opening brace `{` on the new line for functions and control structures.
- **Pointer reference**: Place pointer reference at right position (e.g., `int *ptr;`).
- **C++ language standard:**
  - C++11 is recommended to use in the new code, e.g., `nullptr`, `std::unique_ptr`, `std::make_shared`, lambda, range-based for loop, etc.
  - `auto` is acceptable but not overused.
  - Prefer `nullptr` over `NULL` or `0` for pointers.
- Use header file guard in C/C++:
  ```cpp
  #ifndef MODULE_FILEIO_H
  #define MODULE_FILEIO_H
  // Header file content
  #endif // MODULE_FILEIO_H
  ```

## Build Instructions
- Create a build directory (e.g., `build_x86_64`):
  ```bash
  mkdir -p build_x86_64
  cd build_x86_64
  cmake ..
  make -j$(nproc)
  ```
- For ARM or other targets, use the appropriate toolchain file in `cmake/`.

## Adding New Modules
- Place new source files in the appropriate `src/` subdirectory.
- Update the relevant `CMakeLists.txt` to include new files.
- Follow the naming and style conventions above.

## Example: ASN.1 Module
- ASN.1 encoding/decoding examples are in `src/asn1/`.
- Use `libtasn1` for ASN.1 BER operations.
- Link with `tasn1` in CMake:
  ```cmake
  target_link_libraries(your_target PRIVATE tasn1)
  ```

## Testing
- Place unit tests in `test/`.
- Use CMake to add and build test targets.

## Miscellaneous
- Keep code portable and standard-compliant.
- Document any platform-specific code.

---
For more details, see the project README or ask a maintainer.
