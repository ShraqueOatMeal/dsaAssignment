cmake_minimum_required(VERSION 3.12)
project(dsaAssignment VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(dsaAssignment src/main.cpp)

# If you later add a library, uncomment and modify these lines:
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(dsaAssignment_lib src/radixSort.cpp src/WordFrequency.cpp src/JoinedData.cpp)
target_link_libraries(dsaAssignment PRIVATE dsaAssignment_lib)

