cmake_minimum_required(VERSION 3.2)

set(NAME fractol)
project(${NAME} C)

file(GLOB SRC src/*.c)

link_directories(minilibx libft)
add_executable(${NAME} ${SRC})
target_link_libraries(${NAME} libmlx.a -lXext -lX11 -lm -lft)
target_include_directories(${NAME} PUBLIC includes minilibx libft)
