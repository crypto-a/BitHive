cmake_minimum_required(VERSION 3.27)
project(BitHive C)

set(CMAKE_C_STANDARD 11)

add_executable(
        BitHive
        src/main.c
        src/buffer.c
        src/compiler.c
)

