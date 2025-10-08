# asn1_example
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBTASN1 REQUIRED libtasn1)
message(STATUS "LIBTASN1_INCLUDE_DIRS: ${LIBTASN1_INCLUDE_DIRS}")
message(STATUS "LIBTASN1_LIBRARIES: ${LIBTASN1_LIBRARIES}")

add_executable(
	asn1_example
	asn1_example.cpp
)

target_include_directories(
	asn1_example
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBTASN1_INCLUDE_DIRS}
)

target_link_libraries(
	asn1_example
	PRIVATE
	${LIBTASN1_LIBRARIES}
    pthread
)

# 拷贝 my_schema.asn 到可执行文件输出目录
add_custom_command(TARGET asn1_example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_SOURCE_DIR}/my_schema.asn
		$<TARGET_FILE_DIR:asn1_example>/my_schema.asn)
