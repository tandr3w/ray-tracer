add_test( Color C:/Users/every/OneDrive/Documents/Programming/raytracer/build/Debug/test2.exe Color  )
set_tests_properties( Color PROPERTIES WORKING_DIRECTORY C:/Users/every/OneDrive/Documents/Programming/raytracer/build)
add_test( [==[Adding Colors]==] C:/Users/every/OneDrive/Documents/Programming/raytracer/build/Debug/test2.exe [==[Adding Colors]==]  )
set_tests_properties( [==[Adding Colors]==] PROPERTIES WORKING_DIRECTORY C:/Users/every/OneDrive/Documents/Programming/raytracer/build)
add_test( [==[Subtracting Colors]==] C:/Users/every/OneDrive/Documents/Programming/raytracer/build/Debug/test2.exe [==[Subtracting Colors]==]  )
set_tests_properties( [==[Subtracting Colors]==] PROPERTIES WORKING_DIRECTORY C:/Users/every/OneDrive/Documents/Programming/raytracer/build)
add_test( [==[Color x Scalar]==] C:/Users/every/OneDrive/Documents/Programming/raytracer/build/Debug/test2.exe [==[Color x Scalar]==]  )
set_tests_properties( [==[Color x Scalar]==] PROPERTIES WORKING_DIRECTORY C:/Users/every/OneDrive/Documents/Programming/raytracer/build)
add_test( [==[Multiplying Colors]==] C:/Users/every/OneDrive/Documents/Programming/raytracer/build/Debug/test2.exe [==[Multiplying Colors]==]  )
set_tests_properties( [==[Multiplying Colors]==] PROPERTIES WORKING_DIRECTORY C:/Users/every/OneDrive/Documents/Programming/raytracer/build)
set( test2_TESTS Color [==[Adding Colors]==] [==[Subtracting Colors]==] [==[Color x Scalar]==] [==[Multiplying Colors]==])
