cmake_minimum_required(VERSION 3.2)

project(libft C)

set(GCC_COVERAGE_COMPILE_FLAGS "${GCC_COVERAGE_COMPILE_FLAGS} -Wall -Wextra -Werror")


file(GLOB SRC ft_*.c)
add_executable(libft tests.c ${SRC})
target_compile_definitions(libft PRIVATE FT_ALL)
