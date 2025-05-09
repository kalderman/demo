cmake_minimum_required(VERSION 3.15)
project(turtle_graphics CXX)

find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)
find_package(Catch2 REQUIRED)


add_executable(
    turtle_graphics 

    app/main.cpp
    app/include/openglwindow.hpp
    app/include/drawing.h
    app/src/drawing.cpp
    app/include/input_processing.h
    app/src/input_processing.cpp
)
target_link_libraries(turtle_graphics PRIVATE glfw glbinding::glbinding)
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
target_link_libraries(tests PRIVATE libdomain Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)