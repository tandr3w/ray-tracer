add_test( Translation [==[C:/Users/every/OneDrive/Documents/My Stuff/Programming/Raytracer/build/Debug/test5.exe]==] Translation  )
set_tests_properties( Translation PROPERTIES WORKING_DIRECTORY [==[C:/Users/every/OneDrive/Documents/My Stuff/Programming/Raytracer/build]==])
add_test( [==[Translation Does Not Affect Vectors]==] [==[C:/Users/every/OneDrive/Documents/My Stuff/Programming/Raytracer/build/Debug/test5.exe]==] [==[Translation Does Not Affect Vectors]==]  )
set_tests_properties( [==[Translation Does Not Affect Vectors]==] PROPERTIES WORKING_DIRECTORY [==[C:/Users/every/OneDrive/Documents/My Stuff/Programming/Raytracer/build]==])
add_test( Scaling [==[C:/Users/every/OneDrive/Documents/My Stuff/Programming/Raytracer/build/Debug/test5.exe]==] Scaling  )
set_tests_properties( Scaling PROPERTIES WORKING_DIRECTORY [==[C:/Users/every/OneDrive/Documents/My Stuff/Programming/Raytracer/build]==])
add_test( Reflection [==[C:/Users/every/OneDrive/Documents/My Stuff/Programming/Raytracer/build/Debug/test5.exe]==] Reflection  )
set_tests_properties( Reflection PROPERTIES WORKING_DIRECTORY [==[C:/Users/every/OneDrive/Documents/My Stuff/Programming/Raytracer/build]==])
set( test5_TESTS Translation [==[Translation Does Not Affect Vectors]==] Scaling Reflection)
