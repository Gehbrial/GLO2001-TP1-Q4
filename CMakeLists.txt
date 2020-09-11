cmake_minimum_required(VERSION 3.13)
project(GLO2001_TP1_Q4 C)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(GLO2001_TP1_Q4
        main.c)

target_link_libraries(${PROJECT_NAME} pthread)
