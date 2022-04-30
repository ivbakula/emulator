cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set new variable called PROJECT
# set(PROJECT <projectname>)

set(PROJECT project)
project(${PROJECT} C CXX)

add_subdirectory(main)
add_subdirectory(src)
add_subdirectory(test)
