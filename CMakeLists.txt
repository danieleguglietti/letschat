cmake_minimum_required(VERSION 3.20)

project(letschat)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED On)

add_library(letschat STATIC
    src/request.c
    src/response.c
    src/hashtable.c
    src/headers.c
)

target_include_directories(letschat
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
