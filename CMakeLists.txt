cmake_minimum_required(VERSION 3.12)
project(hack_emulator)

set(CMAKE_CXX_STANDARD 17)

include_directories(assembler/include)
include_directories(emulator/include)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)

add_executable(assembler
        assembler/include/binary.h
        assembler/include/hack_assembler.hpp
        assembler/include/hack_parser.hpp
        assembler/src/binary.c
        assembler/src/hack_assembler.cpp
        assembler/src/hack_parser.cpp
        assembler/src/main.cpp)

add_executable(emulator
        emulator/include/cpu.h
        emulator/include/emulator.h
        emulator/include/screen.h
        emulator/src/cpu.c
        emulator/src/emulator.c
        emulator/src/main.c
        emulator/src/screen.c)

target_link_libraries(emulator ${SDL2_LIBRARIES})