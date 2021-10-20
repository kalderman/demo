cmake_minimum_required(VERSION 3.5)

project(turtle_graphics VERSION 1.0.0 LANGUAGES CXX)

#find_package(OpenGL REQUIRED)
#find_package(glbinding REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#setup OpenGL dependencies
set(GLFW_BUILD_DOCS        OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS       OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES    OFF CACHE BOOL "" FORCE)

set(OPTION_BUILD_TESTS     OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_DOCS      OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_TOOLS     OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_EXAMPLES  OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glbinding)

add_executable(
    turtle_graphics 
    app/main.cpp
    app/include/openglwindow.hpp
    app/include/drawing.h
    app/src/drawing.cpp
    app/include/input_processing.h
    app/src/input_processing.cpp
)
target_link_libraries(turtle_graphics PRIVATE glfw)
target_link_libraries(turtle_graphics PRIVATE glbinding::glbinding)
target_include_directories(turtle_graphics PRIVATE app/include)
target_link_libraries(turtle_graphics PRIVATE libdomain)

#setup domain library
add_library(
    libdomain 
    STATIC

    domain/include/advance_turtle.h
    domain/include/calculate_position.h
    domain/include/match.h
    domain/include/orientation.h
    domain/include/position.h
    domain/include/turtle_events.hpp
    domain/include/turtle.hpp

    domain/src/advance_turtle.cpp 
    domain/src/calculate_position.cpp
    domain/src/orientation.cpp
)
target_include_directories(libdomain PUBLIC domain/include)

#setup automated tests
add_executable(
    tests 
    tests/tests.cpp
    tests/orientation_tests.cpp
    tests/turtle_tests.cpp 
)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/deps/Catch2/single_include/catch2)
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/Catch2)
target_link_libraries(tests PRIVATE Catch2::Catch2)
target_link_libraries(tests PRIVATE libdomain)

include(CTest)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/deps/Catch2/contrib)
include(Catch)
catch_discover_tests(tests)
