
# tcpserver
add_executable(
    tcpserver
    tcp_server.cpp
    tcpip_func.cpp
)

target_link_libraries(
    tcpserver
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    tcpserver
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# tcpclient
add_executable(
    tcpclient
    tcp_client.cpp
    tcpip_func.cpp
)

target_link_libraries(
    tcpclient
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    tcpclient
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# udpserver
add_executable(
    udpserver
    udp_server.cpp
    tcpip_func.cpp
)

target_link_libraries(
    udpserver
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    udpserver
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# udpclient
add_executable(
    udpclient
    udp_client.cpp
    tcpip_func.cpp
)

target_link_libraries(
    udpclient
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    udpclient
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

# udpconnect
add_executable(
    udpconnect
    udp_connect.cpp
    tcpip_func.cpp
)

target_link_libraries(
    udpconnect
    PRIVATE
    ${FMT_LIBRARY}
)

target_include_directories(
    udpconnect
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FMT_INCLUDES}
)

install(TARGETS tcpserver DESTINATION bin)
install(TARGETS tcpclient DESTINATION bin)
install(TARGETS udpserver DESTINATION bin)
install(TARGETS udpclient DESTINATION bin)
install(TARGETS udpconnect DESTINATION bin)