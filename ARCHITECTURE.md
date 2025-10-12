# ARCHITECTURE.md

## Overview

`example-cpp` is a modular, cross-platform C/C++ project targeting both x86_64 and ARM. It uses CMake for build management and is organized for clarity, portability, and maintainability.


## Project overview
- **Type:** C/C++ multi-target project (x86_64, ARM)
- **Build System:** CMake
- **Structure:**
  - `src/` — Main source code (modules: fileio, math_func, thread, usage, etc.)
  - `test/` — Unit tests
  - `build_x86_64/`, `build_arm/` — Out-of-source build directories
  - `cmake/` — Toolchain and CMake helper scripts


## Directory structure

```
root/
├── src/           # Main source code (modules)
│   ├── fileio/    # File I/O utilities
│   ├── math_func/ # Math functions
│   ├── thread/    # Threading utilities
│   ├── usage/     # Usage examples
│   └── ...        # Other modules (process, time, sync, etc.)
├── test/          # Unit tests for each module
├── build_x86_64/  # Out-of-source build (x86_64)
├── build_arm/     # Out-of-source build (ARM)
├── cmake/         # Toolchain and CMake helper scripts
└── rootfs/        # Root filesystem overlays (optional)
```


## Build system
- **CMake** is used for configuration and build.
- Out-of-source builds (e.g., `build_x86_64/`, `build_arm/`).
- Toolchain files in `cmake/` enable cross-compilation.
- Each module and test has its own `CMakeLists.txt`.


## Module design
- **Separation of Concerns:** Each module (e.g., `fileio`, `math_func`, `thread`) is self-contained, with clear interfaces and minimal dependencies.
- **Naming Conventions:**
  - `camelCase` for variables/functions
  - `PascalCase` for classes/structs
  - `UPPER_SNAKE_CASE` for macros/constants
- **Header Guards:** All headers use include guards.
- **C++11 Features:** Modern C++ features are encouraged.
- **Error Handling:** Consistent error codes or exceptions, documented per module.


## Example: math module
- Located in `src/math_func/`
- Provides reusable math utilities
- Unit tests in `test/math_func/`


## Networking & IPC
- Modules like `tcpip/`, `ipc/`, `sync/` provide networking, inter-process communication, and synchronization primitives.
- Designed for portability and POSIX compliance.


## Asn.1 support
- ASN.1 encoding/decoding via `libtasn1` in `src/asn1/`
- Example: `asn1_example.cpp` demonstrates BER encoding/decoding
- CMake links with `tasn1` as needed


## Testing
- All modules have corresponding unit tests in `test/`
- CMake integrates test targets for automated builds


## Extensibility & portability
- New modules can be added by creating a subdirectory in `src/` and updating CMake
- Platform-specific code is isolated and documented
- Code style and structure are enforced via `copilot-instructions.md`


## Architecture diagram

```
+-------------------+
|   Application     |
+-------------------+
         |
+-------------------+
|    Modules        |
| (fileio, math,    |
|  thread, ... )    |
+-------------------+
         |
+-------------------+
|   Platform/OS     |
+-------------------+
```

---
For more details, see the README.md and module-specific documentation.
