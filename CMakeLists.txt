cmake_minimum_required(VERSION 3.25)
project(zkv)

# To be LSP-friendly :)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

# Use clang
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# Latest standrd
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# Enable TSAN for all targets
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -fsanitize=thread -Wall -Wextra -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=thread -Wall -Wextra -pedantic-errors")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# Find absl
find_package(absl CONFIG REQUIRED)

# Add executables. One for absl thread-safe queue, and one for std.
add_executable(AbslMain absl_main.cpp)
set_target_properties(AbslMain PROPERTIES CXX_STANDARD 23)
target_include_directories(AbslMain INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AbslMain abseil::abseil)

add_executable(StdMain std_main.cpp)
set_target_properties(StdMain PROPERTIES CXX_STANDARD 23)
target_include_directories(StdMain INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(StdMain)

