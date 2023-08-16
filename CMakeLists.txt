# 设置CMake版本支持
set(OLDEST_VALIDATED_VERSION "3.8.0")
set(NEWEST_VALIDATED_VERSION "3.25.2")
cmake_minimum_required(VERSION ${OLDEST_VALIDATED_VERSION})
if("${CMAKE_VERSION}" VERSION_LESS "${NEWEST_VALIDATED_VERSION}")
    set(CMAKE_POLICY_VERSION "${CMAKE_VERSION}")
else()
    set(CMAKE_POLICY_VERSION "${NEWEST_VALIDATED_VERSION}")
endif()
cmake_policy(VERSION ${CMAKE_POLICY_VERSION})

# 设置C++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译版本
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_program(CCACHE_EXECUTABLE "ccache" HINTS /usr/local/bin /opt/local/bin)
if(CCACHE_EXECUTABLE)
    message(STATUS "use ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}" CACHE PATH "ccache" FORCE)
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}" CACHE PATH "ccache" FORCE)
endif()

# 设置项目
project(SugerJson
    VERSION 1.0.1
    LANGUAGES CXX)
message(STATUS "SugerJson Version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(PROJECT_SOVERSION 1)

option(BUILD_EXAMPLE "Compile SugerJson example" OFF)
option(BUILD_SHARED_LIBS "Build shared library." ON)
option(BUILD_STATIC_LIBS "Build static library." ON)
option(BUILD_CMAKE_PACKAGE "Generate and install cmake package files" ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/result/lib" CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/result/lib" CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/result/bin" CACHE PATH "PDB output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/result/bin" CACHE PATH "Executable output dir.")
set(CMAKE_INCLUDE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/result/include" CACHE PATH "Include output dir.")

include_directories(${SugerJson_SOURCE_DIR}/include)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wconversion -Wshadow)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wconversion -Wshadow -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    add_compile_options(-Wall -Wconversion -Wshadow -Wextra)
endif()

add_subdirectory(src)
add_subdirectory(include)
