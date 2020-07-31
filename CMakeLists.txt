# Declare the project

	cmake_minimum_required(VERSION 3.18)
	project(ndd VERSION 1.0.0)


# Set the project's structure

	set(PROJECT_SOURCE_DIR src)
	set(PROJECT_BINARY_DIR build)

	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/ar)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

	include_directories(include)


# Define the C and C++ standards to use

	set(CMAKE_C_STANDARD 11)
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_C_STANDARD_REQUIRED True)
	set(CMAKE_CXX_STANDARD_REQUIRED True)


# Define the remaining aspects of the project

	add_executable(ndd ${PROJECT_SOURCE_DIR}/main/ndd.cpp)
	target_link_libraries(ndd baseconvert_lib)

	add_library(baseconvert_lib STATIC
		${PROJECT_SOURCE_DIR}/runtime/baseconvert.cpp)

