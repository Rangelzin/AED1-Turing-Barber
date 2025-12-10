cmake_minimum_required(VERSION 3.10)
project(TuringBarber VERSION 1.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(turing_barber ${SOURCES})

set_target_properties(turing_barber PROPERTIES 
   
    OUTPUT_NAME "turing_barber"
    
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)