cmake_minimum_required(VERSION 3.24.0)
project(BedrockModAPI VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build options
option(BUILD_EXAMPLES "Build example mods" ON)
option(BUILD_DOCS "Build documentation" ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /bigobj /utf-8)
    add_compile_options($<$<CONFIG:Release>:/O2 /Oi /Gy /Gw /GF /MT>)
    add_compile_options($<$<CONFIG:Debug>:/Od /Zi /MT>)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Dependencies
add_subdirectory(lib)

# Core API library
file(GLOB_RECURSE API_SOURCES 
    "src/core/*.cpp"
    "src/sdk/*.cpp"
    "src/memory/*.cpp"
    "src/hooks/*.cpp"
)

file(GLOB_RECURSE API_HEADERS
    "include/bedrock/*.hpp"
    "include/bedrock/*.h"
)

add_library(BedrockModAPI SHARED
    ${API_SOURCES}
    ${API_HEADERS}
)

target_include_directories(BedrockModAPI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_compile_definitions(BedrockModAPI PRIVATE
    BEDROCK_API_EXPORT
    BEDROCK_VERSION="${PROJECT_VERSION}"
)

# Link dependencies (MinHook, etc.)
target_link_libraries(BedrockModAPI PRIVATE
    d3d11.lib
    d3d12.lib
    dxgi.lib
)

# Examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation
install(TARGETS BedrockModAPI
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/bedrock
    DESTINATION include
)
