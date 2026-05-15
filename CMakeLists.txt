cmake_minimum_required(VERSION 4.2)
project(OOP)

set(CMAKE_CXX_STANDARD 20)

add_executable(OOP main.cpp)
add_executable(assignment01
        assignments/assignment-01/main_assignment_01.cpp
        assignments/assignment-01/Person.cpp
        assignments/assignment-01/Student.cpp
        assignments/assignment-01/Instructor.cpp
        assignments/assignment-01/Course.cpp
        assignments/assignment-01/Laptop.cpp
        assignments/StudentProfile.cpp
)
