cmake_minimum_required(VERSION 3.2)

project(ft C)

set(GCC_COVERAGE_COMPILE_FLAGS "${GCC_COVERAGE_COMPILE_FLAGS} -Wall -Wextra -Werror")


file(GLOB SRC ft_*.c get_next_line.c)
add_library(ft STATIC ${SRC})
add_subdirectory (tests)
