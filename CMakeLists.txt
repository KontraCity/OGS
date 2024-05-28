### --- Initial configuration --- ###
cmake_minimum_required(VERSION 3.10)
project(OGS)

### --- C++ configuration --- ###
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

### --- Libraries configuration --- ###
find_package(fmt CONFIG REQUIRED)

### --- Executable configuration --- ###
add_executable(ogs "source/main.cpp")
target_include_directories(ogs PRIVATE "include/")
target_link_libraries(ogs PRIVATE fmt::fmt)
