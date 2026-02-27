# CONTRIBUTING.md

Thank you for your interest in contributing to `example-cpp`! To ensure code quality, maintainability, and a welcoming community, please follow these guidelines:

## Getting started
- Fork the repository and create a feature branch from `main`.
- Use descriptive branch names (e.g., `feature/thread-optim`, `defect/math-divzero`).
- Keep your changes focused and atomic—one feature or fix per pull request.

## Coding style
- **Naming:**
  - Use `camelCase` for variables and function names (e.g., `myVariable`, `calculateSum`).
  - Use `PascalCase` for class/struct names (e.g., `MyClass`).
  - Use `UPPER_SNAKE_CASE` for macros and constants (e.g., `MAX_SIZE`).
  - Use `std::` library features where applicable (e.g., `std::vector`, `std::string`, `std::thread`).
  - Prefix with a module abbreviation (e.g., `module_functionName`) for C exported function name or global variable, e.g., `i2c_sendBuffer()`, `int i2c_busStatus()`.
  - Prefix `m_` for C++ private class member (e.g., `m_someClassMember`).
  - Prefix `m` for C file scope variable (e.g., `mSomeStaticVar`).
- **File names:** Use lowercase with underscores (e.g., `math_func.cpp`).
- **Indentation:** 4 spaces per level.
- **Comments:**
  - Use English for code comments and documentation.
  - Use doxygen javadoc style for function/class documentation.
  - Begin comment text with an uppercase letter, end comment text with a period.
- **Error handling:**
  - Use consistent error handling strategies (e.g., return codes, exceptions).
  - Document error cases and recovery strategies.
- **Namespace**:
  - Use a consistent naming scheme for namespaces, following the same rules as for file names.
  - Use unnamed namespace for static global variable or function.
- **Open braces**: Place the opening brace `{` on the new line for functions and control structures.
- **Pointer reference**: Place pointer reference at right position (e.g., `int *ptr;`).
- **C++ language standard:**
  - C++11 is recommended to use in the new code, e.g., `nullptr`, `std::unique_ptr`, `std::make_shared`, range-based for loop, etc.
  - `auto` is acceptable but not overused.
  - Prefer `nullptr` over `NULL` or `0` for pointers.
- Use header file guard in C/C++:
  ```cpp
  #ifndef MODULE_FILEIO_H
  #define MODULE_FILEIO_H
  // Header file content
  #endif // MODULE_FILEIO_H
  ```
- **Title case (First letter only)**: All headings and section titles in Markdown files and documentation should use title case with only the first letter capitalized and the rest lowercase (e.g., use "Project general coding standards", not "Project General Coding Standards" or "PROJECT GENERAL CODING STANDARDS").

## Adding new modules
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

## Adding code
- Place new modules in the appropriate `src/` subdirectory
- Update the relevant `CMakeLists.txt` to include new files
- Add or update unit tests in `test/` for all new features and bug fixes
- Document public APIs and error handling in comments

## Build instructions
- Create a build directory (e.g., `build_x86_64`):
  ```bash
  mkdir -p build_x86_64
  cd build_x86_64
  cmake ..
  make -j$(nproc)
  ```
- For ARM or other targets, use the appropriate toolchain file in `cmake/`.

## Testing
- Place unit tests in `test/`.
- Use CMake to add and build test targets.

## Pull requests
- Ensure your code builds and passes all tests (`make` and `ctest`)
- Run static analysis or linters if available
- Write a clear, concise PR description (what, why, how tested)
- Reference related issues or discussions if applicable

## Communication
- Be respectful and constructive in code reviews and discussions
- Ask questions if unsure—maintainers are happy to help
- Report bugs or suggest features via GitHub Issues

## License
By contributing, you agree that your code will be licensed under the project's open source license.

## Miscellaneous
- Keep code portable and standard-compliant.
- Document any platform-specific code.

---
For more details, see the README.md, ARCHITECTURE.md, and copilot-instructions.md.
