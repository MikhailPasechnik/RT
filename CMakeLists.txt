cmake_minimum_required(VERSION 3.2)

set(NAME fractol)
project(${NAME} C)
find_package(OpenCL REQUIRED)

add_subdirectory(libft)
add_subdirectory(SDL)
file(GLOB SRC src/*.c src/ocl/*.c)
find_package(OpenCL REQUIRED)

link_directories(libft SDL)
add_executable(${NAME} ${SRC})
target_include_directories(${NAME} PRIVATE libft include ${OpenCL_INCLUDE_DIRS} SDL/include)
target_link_libraries(${NAME} m ft ${OpenCL_LIBRARY} SDL2)
