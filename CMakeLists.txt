cmake_minimum_required(VERSION 3.5)

project(helloworld VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(helloworld helloworld.cpp)

#OpenGL dependencies
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)
target_link_libraries(helloworld glfw)
add_subdirectory(lib/glbinding)
target_link_libraries(helloworld glbinding)

#setup automated tests
add_executable(tests tests.cpp)
target_include_directories(tests PRIVATE lib/Catch2/single_include/catch2)
add_subdirectory(lib/Catch2)
target_link_libraries(tests Catch2::Catch2)

include(CTest)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/Catch2/contrib)
include(Catch)
catch_discover_tests(tests)
