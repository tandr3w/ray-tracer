cmake_minimum_required(VERSION 3.1)
project(rayTracer)

add_library(math 
            src/math/tuple.cpp 
            src/math/constants.cpp
            src/math/color.cpp
            src/math/matrix.cpp
            src/math/ray.cpp
            src/math/intersection.cpp
            src/math/intersections.cpp
           )

add_library(display 
            src/display/canvas.cpp
          )

add_library(shapes 
          src/shapes/sphere.cpp
        )

target_link_libraries(display math shapes)
    
target_include_directories(math PUBLIC include)
target_include_directories(display PUBLIC include)
target_include_directories(shapes PUBLIC include)

add_executable(trace main.cpp)
target_link_libraries(trace math display shapes)
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

add_executable(test5 tests/transformation_test.cpp)
target_link_libraries(test5 math Catch2::Catch2WithMain)
catch_discover_tests(test5)

add_executable(test6 tests/ray_sphere_test.cpp)
target_link_libraries(test6 math shapes Catch2::Catch2WithMain)
catch_discover_tests(test6)
