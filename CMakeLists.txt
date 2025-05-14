cmake_minimum_required(VERSION 3.15)
project(turtle_graphics CXX)

find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(
    turtle_graphics 

    app/main.cpp
    app/openglwindow.hpp
    app/drawing.hpp
    app/drawing.cpp
    app/input_processing.hpp
    app/input_processing.cpp
)
target_link_libraries(turtle_graphics PRIVATE glfw glbinding::glbinding libdomain)
target_include_directories(turtle_graphics PRIVATE app)

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

#setup domain library
add_library(
    libdomain 
    STATIC

    domain/advance_turtle.hpp
    domain/calculate_position.hpp
    domain/match.hpp
    domain/orientation.hpp
    domain/position.hpp
    domain/turtle_events.hpp
    domain/turtle.hpp

    domain/advance_turtle.cpp 
    domain/calculate_position.cpp
    domain/orientation.cpp
)
target_include_directories(libdomain PUBLIC domain)

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
                COMMAND ${LCOV} --remove coverage/coverage.info '/usr/*' '*/.conan2/*' '*/app/*' --output-file coverage/coverage.info
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