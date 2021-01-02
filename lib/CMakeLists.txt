cmake_minimum_required(VERSION 3.13)

project(lib VERSION 0.0.1)

setup()

option(${FULL_PROJECT_NAME_UPPER}_BUILD_SHARED_LIB "Enable compilation of shared libraries" ${BUILD_SHARED_LIBS})
option(${FULL_PROJECT_NAME_UPPER}_BUILD_TESTS "Build ${PROJECT_NAME} tests" OFF)
option(${FULL_PROJECT_NAME_UPPER}_BUILD_EXAMPLES "Build ${PROJECT_NAME} examples" OFF)

file(GLOB ${FULL_PROJECT_NAME_UPPER}_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/*.hpp)

configure_file(config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/config.hpp)

set(${FULL_PROJECT_NAME_UPPER}_LIB_TYPE STATIC)
if(${PROJECT_NAME_UPPER}_BUILD_SHARED_LIB)
	set(${FULL_PROJECT_NAME_UPPER}_LIB_TYPE SHARED)
endif()

add_library(${PROJECT_NAME} ${${FULL_PROJECT_NAME_UPPER}_LIB_TYPE})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

add_subdirectory(src)

if(${PROJECT_NAME_UPPER}_BUILD_TESTS)
	add_subdirectory(tests)
endif()
if(${PROJECT_NAME_UPPER}_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
