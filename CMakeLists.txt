cmake_minimum_required(VERSION 3.1)
project(rayTracer)

add_library(math 
            src/math/tuple.cpp 
            src/math/constants.cpp
            src/math/color.cpp
            src/math/matrix.cpp
           )

add_library(display 
            src/display/canvas.cpp
          )

target_link_libraries(display math)
    
target_include_directories(math PUBLIC include)
target_include_directories(display PUBLIC include)

add_executable(trace main.cpp)
target_link_libraries(trace math display)
target_include_directories(trace PUBLIC include)

# UNIT TESTING
add_subdirectory(lib/Catch2)
include(CTest)
include(Catch)
enable_testing()

add_executable(test1 tests/tuple_test.cpp)
target_link_libraries(test1 math Catch2::Catch2WithMain)
catch_discover_tests(test1)

add_executable(test2 tests/color_test.cpp)
target_link_libraries(test2 math Catch2::Catch2WithMain)
catch_discover_tests(test2)

add_executable(test3 tests/canvas_test.cpp)
target_link_libraries(test3 math display Catch2::Catch2WithMain)
catch_discover_tests(test3)

add_executable(test4 tests/matrix_test.cpp)
target_link_libraries(test4 math Catch2::Catch2WithMain)
catch_discover_tests(test4)
