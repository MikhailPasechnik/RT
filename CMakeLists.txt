cmake_minimum_required(VERSION 3.2)

project(libft C)

file(GLOB SRC ft_*.c)
add_executable(libft main.c ${SRC})
