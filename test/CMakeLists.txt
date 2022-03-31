cmake_minimum_required(VERSION 3.20)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# TEST UNITS - START

add_executable(headers ${sources} headers.cpp)
target_link_libraries(headers gtest_main)
target_include_directories(headers
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_executable(request ${sources} request.cpp)
target_link_libraries(request gtest_main)
target_include_directories(request
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_executable(string ${sources} string.cpp)
target_link_libraries(string gtest_main)
target_include_directories(string
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# TEST UNITS - END

include(GoogleTest)
gtest_discover_tests(headers request)
