cmake_minimum_required(VERSION 3.22)
project(Laborator_2_4 C)

set(CMAKE_C_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(Laborator_2_4 main.c repo.c repo.h domain.h domain.c service.c service.h tests.h tests.c validate.h validate.c ui.h ui.c)

