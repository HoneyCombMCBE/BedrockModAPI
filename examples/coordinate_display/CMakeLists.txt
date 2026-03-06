cmake_minimum_required(VERSION 3.24.0)
project(CoordinateDisplay)

set(CMAKE_CXX_STANDARD 20)

# Find BedrockModAPI
find_package(BedrockModAPI REQUIRED)

# Create mod DLL
add_library(CoordinateDisplay SHARED
    main.cpp
)

target_link_libraries(CoordinateDisplay 
    BedrockModAPI::BedrockModAPI
)
