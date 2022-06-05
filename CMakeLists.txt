cmake_minimum_required(VERSION 3.5)

project(01.lesson_6)

add_executable(lesson_6 
    list_container.hpp
    serial_container.hpp
    singly_linked_list_container.hpp
    util.hpp
    main.cpp
)

set_target_properties(lesson_6 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS lesson_6)