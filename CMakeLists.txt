cmake_minimum_required(VERSION 3.2)

set(NAME fractol)
project(${NAME} C)
find_package(OpenCL REQUIRED)

add_subdirectory(libft)
file(GLOB SRC src/*.c opencl/src/*.c)
link_directories(minilibx libft)
add_executable(${NAME} ${SRC})
target_include_directories(${NAME} PRIVATE libft includes minilibx opencl/includes  ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${NAME} mlx Xext X11 m ft ${OpenCL_LIBRARY})
