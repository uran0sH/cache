cmake_minimum_required(VERSION 3.23)
project(cache)

set(CMAKE_CXX_STANDARD 14)

add_executable(cache main.cc lru.cc lru.h arc.cc arc.h lib.h)

add_library(lru lru.cc lru.h lib.h)
add_library(arc arc.cc arc.h lib.h)

#include_directories(${PROJECT_SOURCE_DIR} / googletest / googletest / include)

add_subdirectory(./googletest)

enable_testing()

add_executable(lru_test tests/lru_test.cc lru.h lib.h)
target_link_libraries(lru_test GTest::gtest_main lru)

add_executable(arc_test tests/arc_test.cc arc.h lib.h lru.h)
target_link_libraries(arc_test GTest::gtest_main arc lru)

include(GoogleTest)
gtest_discover_tests(lru_test)
gtest_discover_tests(arc_test)
