cmake_minimum_required(VERSION 3.2)

set(NAME RTv1)
project(${NAME} C)
find_package(OpenCL REQUIRED)

add_subdirectory(libft)
add_subdirectory(ft_printf)
add_subdirectory(SDL)

file(GLOB SRC src/*.c src/ocl/*.c src/math3d/*.c)

link_directories(libft SDL ft_printf)
include_directories(libft include ${OpenCL_INCLUDE_DIRS} SDL/include ft_printf/include)
link_libraries(m ft_printf ft ${OpenCL_LIBRARY} SDL2)

add_executable(${NAME} ${SRC})

# Tests
list(FILTER SRC EXCLUDE REGEX "main.c")
add_executable(cl_sandbox tests/cl_sandbox.c ${SRC})
