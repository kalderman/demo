cmake_minimum_required(VERSION 3.15)
project(turtle_graphics CXX)

find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)
find_package(Catch2 REQUIRED)

# Code coverage setup
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options(--coverage -O0 -g)
        add_link_options(--coverage)
    else()
        message(WARNING "Coverage is only supported for GCC")
    endif()
endif()

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

# Code coverage target setup
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        find_program(LCOV lcov)
        find_program(GENHTML genhtml)
        if(LCOV AND GENHTML)
            add_custom_target(coverage
                COMMAND ${CMAKE_COMMAND} -E make_directory coverage
                COMMAND tests
                COMMAND ${LCOV} --capture --directory . --output-file coverage/coverage.info
                COMMAND ${LCOV} --remove coverage/coverage.info '/usr/*' '*/catch2/*' --output-file coverage/coverage.info
                COMMAND ${GENHTML} coverage/coverage.info --output-directory coverage/html
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Generating coverage report"
            )
        else()
            message(WARNING "lcov or genhtml not found, coverage target disabled")
        endif()
    endif()
endif()

include(CTest)
include(Catch)
catch_discover_tests(tests)