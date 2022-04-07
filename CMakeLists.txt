cmake_minimum_required(VERSION 3.20)

project(letschat)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED On)

set(sources ${sources} 
    ${CMAKE_SOURCE_DIR}/src/request.c
    ${CMAKE_SOURCE_DIR}/src/response.c
    ${CMAKE_SOURCE_DIR}/src/hashtable.c
    ${CMAKE_SOURCE_DIR}/src/headers.c
    ${CMAKE_SOURCE_DIR}/src/string.c
    ${CMAKE_SOURCE_DIR}/src/thread.c
)

add_library(letschat STATIC ${sources})

target_include_directories(letschat
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_subdirectory(test)
