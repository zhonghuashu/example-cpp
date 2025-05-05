# tmpname
add_executable(
    pImpl
    main.cpp
    MyClass.cpp
)

target_link_libraries(
    pImpl
    PRIVATE
)

target_include_directories(
    pImpl
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
