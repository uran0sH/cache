cmake_minimum_required(VERSION 3.23)
project(cache)

set(CMAKE_CXX_STANDARD 14)

add_executable(cache main.cc lru.cc lru.h)

add_library(lru lru.cc lru.h)

#include_directories(${PROJECT_SOURCE_DIR} / googletest / googletest / include)

add_subdirectory(./googletest)

enable_testing()
add_executable(lru_test tests/lru_test.cc lru.h)
target_link_libraries(lru_test GTest::gtest_main lru)
include(GoogleTest)
gtest_discover_tests(lru_test)
