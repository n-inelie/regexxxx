cmake_minimum_required(VERSION 3.29.0)
project(regexxxx VERSION 0.1.0)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic -glldb")
set(CMAKE_LINKER "/usr/local/bin/mold")

file(GLOB SOURCES src/*.c)

add_executable(regexxxx ${SOURCES})

