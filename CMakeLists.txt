cmake_minimum_required(VERSION 3.26)
project(projet_c_pgcd C)

set(CMAKE_C_STANDARD 99)

include_directories(src)

add_executable(projet_c_pgcd
        src/grand_entier.c
        src/grand_entier.h
        main.c)
