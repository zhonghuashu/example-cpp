# PRODUCT.md

## Product Overview

`example-cpp` is a modular, cross-platform C/C++ toolkit designed for system-level programming, rapid prototyping, and educational purposes. It provides reusable components for file I/O, math, threading, networking, inter-process communication, and more, supporting both x86_64 and ARM platforms.

---

## Key Features

### 1. File I/O Utilities
- Read/write files, directories, and device nodes
- Example: Efficient file copying, directory traversal, and file attribute queries

### 2. Math Functions
- Arithmetic, statistics, and utility math operations
- Example: Custom math library for embedded or performance-critical use

### 3. Threading & Concurrency
- Thread creation, synchronization (mutex, condition variable), and thread pools
- Example: Producer-consumer, detached threads, and thread-safe patterns

### 4. Networking & IPC
- TCP/UDP client/server, UNIX domain sockets, pipes, message queues, shared memory
- Example: Simple echo server, IPC demo, and networked data transfer

### 5. Time & Performance
- High-resolution timers, sleep utilities, and performance measurement
- Example: Timer test, nanosleep, and benchmarking tools

### 6. Usage Examples
- Ready-to-run sample programs for each module
- Example: `usage_cplus.cpp` demonstrates idiomatic C++ usage

### 7. ASN.1 Encoding/Decoding
- ASN.1 BER encoding/decoding using `libtasn1`
- Example: `asn1_example.cpp` for protocol or data serialization

### 8. Unit Testing
- Each module includes unit tests for correctness and regression
- Example: Automated test suite in `test/` directory

---

## Typical Use Cases

- **System Programming:** Rapidly build and test system-level utilities and daemons.
- **Embedded Development:** Cross-compile for ARM, use math/thread/file/network modules on resource-constrained devices.
- **Education:** Learn and demonstrate C/C++ best practices, concurrency, IPC, and networking.
- **Prototyping:** Quickly assemble and validate new algorithms or system components.
- **Protocol Implementation:** Use ASN.1 support for custom protocol encoding/decoding.

---

## User Workflow

1. **Build the Project:**
   - Configure with CMake for your target platform
   - Build all modules and tests with `make`
2. **Run Examples:**
   - Execute sample programs in the build directory (e.g., `./fileio`, `./thread_simple`)
3. **Extend Functionality:**
   - Add new modules or features in `src/`, update CMake, and add tests
4. **Test and Validate:**
   - Run unit tests in `test/` to ensure correctness

---

## Extensibility

- Add new modules by creating a subdirectory in `src/` and updating CMake
- Write new usage examples and tests to demonstrate and validate features
- Platform-specific code is isolated for easy porting

---

## Example Product Map

| Module         | Functionality Example           | CLI/Program         |
| -------------- | ------------------------------ | ------------------- |
| fileio         | File copy, dir listing         | `fileio`, `printdir`|
| math_func      | Math/statistics                | `libmath_func.so`   |
| thread         | Threading, sync, procon        | `thread_simple`     |
| tcpip          | TCP/UDP client/server          | `tcpserver`         |
| asn1           | ASN.1 encode/decode            | `asn1_example`      |
| usage          | C++ idioms, usage patterns     | `usage_cplus.cpp`   |

---

## Limitations & Target Audience

- Not a full application framework; focused on reusable, composable building blocks
- Intended for developers, students, and engineers needing portable C/C++ utilities

---

For more details, see the README.md, ARCHITECTURE.md, and module documentation.
