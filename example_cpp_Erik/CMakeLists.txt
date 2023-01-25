cmake_minimum_required(VERSION 3.10)
project(example_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_CXX_FLAGS "-g3 -Wall -O0 -Wextra -Wunused -pthread")

set(SOURCES
  src/main.cpp
  src/example.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
  ${PROJECT_SOURCE_DIR}/include
)
