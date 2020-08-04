cmake_minimum_required(VERSION 3.2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(OpenGL_GL_PREFERENCE LEGACY)

set(NAME RT)
project(${NAME} C)
find_package(OpenCL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(libft)
add_subdirectory(ft_printf)

file(GLOB SRC src/*.c src/ocl/*.c src/math3d/*.c src/gui/*.c)

link_directories(libft ft_printf)
include_directories(
        libft include nuklear
        ${OpenCL_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ft_printf/include
        ${GLEW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
)

link_libraries(
        m ft_printf ft
        ${OpenCL_LIBRARY}
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
)

add_executable(${NAME} ${SRC})

# Tests
list(FILTER SRC EXCLUDE REGEX "main.c")

file(GLOB_RECURSE RES_CL resources/ocl/* resources/textures/* include/obj.h)

ADD_CUSTOM_TARGET(copy_runtime_dep ALL)
# we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    # list of files for which we add a copy rule
    foreach(item IN LISTS RES_CL)
        get_filename_component(barename ${item} NAME)
        message(STATUS "${item} -> ${CMAKE_CURRENT_BINARY_DIR}/resources/ocl/${barename}")
        add_custom_command(TARGET copy_runtime_dep POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy "${item}" "${CMAKE_CURRENT_BINARY_DIR}/resources/ocl/${barename}"
                DEPENDS "${item}"
                )
    endforeach()
endif()
ADD_DEPENDENCIES(${NAME} copy_runtime_dep)

