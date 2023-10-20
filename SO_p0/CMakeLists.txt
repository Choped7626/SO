cmake_minimum_required(VERSION 3.24)
project(SO_p0 C)

set(CMAKE_C_STANDARD 99)

add_executable(SO_p0 P0.c
        lista.c
        lista.h cabeceras.h funciones.c)
