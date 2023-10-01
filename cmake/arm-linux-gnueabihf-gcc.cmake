set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Without that flag CMake is not able to pass test compilation check.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PATH /root/tools/gcc-linaro/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabihf)
set(TOOLCHAIN_HOST "${TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf")

set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf-g++)

# The directory that contain the target environment for find_program, library...
set(CMAKE_FIND_ROOT_PATH
    /root/develop/arm-cyclone5-rootfs
    /root/develop/arm-cyclone5-extra
    ${CMAKE_SOURCE_DIR}/rootfs/arm-cyclone5)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)