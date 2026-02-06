cmake_minimum_required(VERSION 3.5)
project(libqrcode)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-Wall -Wextra -Werror)
endif()

set(CMAKE_C_FLAGS_RELEASE "-O3 -mavx2 -march=native")
add_compile_definitions(POSIX_C_SOURCE=200809L)

file(GLOB_RECURSE sources ../src/*.c)

add_library(qrcode ${sources})
target_include_directories(qrcode PUBLIC ../include)
set_target_properties(qrcode
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

file(GLOB_RECURSE example_sources ../examples/*.c)

foreach(example_file ${example_sources})
    get_filename_component(exe_name ${example_file} NAME_WE)
    add_executable(${exe_name} ${example_file} ${sources})
    target_link_libraries(${exe_name} PRIVATE qrcode)
    set_target_properties(${exe_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()