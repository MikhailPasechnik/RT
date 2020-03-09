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
add_executable(cl_sandbox2 tests1/cl_sandbox.c ${SRC})

file(GLOB_RECURSE RES_CL res/ocl/* include/obj.h)

ADD_CUSTOM_TARGET(copy_runtime_dep ALL)
# we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    # list of files for which we add a copy rule
    foreach(item IN LISTS RES_CL)
        get_filename_component(barename ${item} NAME)
        message(STATUS "${item} -> ${CMAKE_CURRENT_BINARY_DIR}/res/ocl/${barename}")
        add_custom_command(TARGET copy_runtime_dep POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy "${item}" "${CMAKE_CURRENT_BINARY_DIR}/res/ocl/${barename}"
                DEPENDS "${item}"
                )
    endforeach()
endif()
ADD_DEPENDENCIES(${NAME} copy_runtime_dep)

