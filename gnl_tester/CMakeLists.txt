# general settings
cmake_minimum_required(VERSION 3.14)
project(get_next_line C CXX)

# set(PRINTF_PATH ../../printf)

find_package(GTest REQUIRED)

# add_subdirectory(${PRINTF_PATH} build)
# include_directories(${PRINTF_PATH})

add_executable(
  test
  gtest.cpp
  ../get_next_line.c
  ../get_next_line_utils.c
)
target_link_libraries(
  test
  GTest::Main
)

include(GoogleTest)
