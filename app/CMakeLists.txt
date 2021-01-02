cmake_minimum_required(VERSION 3.13)

project(app VERSION 0.0.1)

setup()

add_executable(${PROJECT_NAME} MACOSX_BUNDLE src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}::lib)
set_target_properties(${PROJECT_NAME}
	PROPERTIES
		MACOSX_RPATH @executable_path
)
