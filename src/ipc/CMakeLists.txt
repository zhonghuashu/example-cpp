# pipemain
add_executable(
    pipecliserv
    pipe_cliserv.cpp
    ipc_func.cpp
)

target_link_libraries(
    pipecliserv
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    pipecliserv
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# fifocliserv
add_executable(
    fifocliserv
    fifo_cliserv.cpp
    ipc_func.cpp
)

target_link_libraries(
    fifocliserv
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    fifocliserv
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# fifoclient
add_executable(
    fifoclient
    fifo_client.cpp
    ipc_func.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../tcpip/tcpip_func.cpp
)

target_link_libraries(
    fifoclient
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    fifoclient
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../tcpip
    ${FMT_INCLUDES}
)

# fifoserver
add_executable(
    fifoserver
    fifo_server.cpp
    ipc_func.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../tcpip/tcpip_func.cpp
)

target_link_libraries(
    fifoserver
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    fifoserver
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../tcpip
    ${FMT_INCLUDES}
)

# mqserver
add_executable(
    mqserver
    mq_server.cpp
)

target_link_libraries(
    mqserver
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    mqserver
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# mqclient
add_executable(
    mqclient
    mq_client.cpp
)

target_link_libraries(
    mqclient
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    mqclient
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# shmclient
add_executable(
    shmclient
    shm_client.cpp
    ipc_func.cpp
)

target_link_libraries(
    shmclient
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    shmclient
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# shmserver
add_executable(
    shmserver
    shm_server.cpp
)

target_link_libraries(
    shmserver
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    shmserver
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)