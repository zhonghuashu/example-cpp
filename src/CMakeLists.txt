add_subdirectory(math_func)
add_subdirectory(pattern)
add_subdirectory(usage)
add_subdirectory(thread)
add_subdirectory(tcpip)
add_subdirectory(fileio)
add_subdirectory(linux_env)
add_subdirectory(process)
add_subdirectory(time)
if(NOT ${CMAKE_CROSSCOMPILING})
add_subdirectory(ipc)
add_subdirectory(sync)
endif()
add_subdirectory(perf)