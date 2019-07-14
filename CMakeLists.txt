# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.0)

# Set the project name
project (phone_res_tool)
set(SOURCE main.cpp)

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCE})
