cmake_minimum_required(VERSION 3.5)
project(myWatchdog C)

set(CMAKE_C_STANDARD 99)

add_executable(myWatchdog
        main.c
        strtowordtab.c
        )