cmake_minimum_required(VERSION 3.24.0)

# Example mods CMakeLists.txt

# Coordinate Display
add_subdirectory(coordinate_display)

# Speed Boost
add_library(SpeedBoost SHARED
    speed_boost/main.cpp
)

target_link_libraries(SpeedBoost 
    BedrockModAPI
)

# Install examples
install(TARGETS SpeedBoost
    RUNTIME DESTINATION examples
    LIBRARY DESTINATION examples
)
