cmake_minimum_required(VERSION 3.20)

project(my_project VERSION 1.0)

# Use modern C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create the executable
add_executable(CarbonPY
    src/CarbonPY.cpp
)

# Add include directory for headers
target_include_directories(CarbonPY PRIVATE include)