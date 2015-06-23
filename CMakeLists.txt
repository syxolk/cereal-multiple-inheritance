cmake_minimum_required(VERSION 2.8)
project(CornflakesWithMilk)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -std=c++0x -Wall -Wextra -pedantic -O0")

add_subdirectory(cereal)
add_subdirectory(googletest_lib)

include_directories(cereal/include)
include_directories(googletest_lib/include)
include_directories(include)

set(SOURCES
	src/base.cpp
    src/other_base.cpp
	src/derived.cpp
)

set(HEADERS
	include/base.h
    include/other_base.h
	include/derived.h
)

set(TESTS
    test/test.cpp
)

add_library (milk SHARED ${SOURCES} ${HEADERS})

add_executable(cornflakes ${TESTS})
target_link_libraries(cornflakes PRIVATE gtest gtest_main milk)

enable_testing()
add_test(CornflakesAndMilk cornflakes)
