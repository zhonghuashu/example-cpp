# sembuff
add_executable(
    sembuff
    sem_buff.cpp
)

target_link_libraries(
    sembuff
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    sembuff
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# mutexprocon
add_executable(
    proconmutex
    procon_mutex.cpp
)

target_link_libraries(
    proconmutex
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    proconmutex
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# condprocon
add_executable(
    proconcond
    procon_cond.cpp
)

target_link_libraries(
    proconcond
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    proconcond
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)