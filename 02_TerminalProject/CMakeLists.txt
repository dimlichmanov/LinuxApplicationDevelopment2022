cmake_minimum_required(VERSION 3.16)
project(LinuxApplicationDevelopment2022 C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)


add_executable(task2 Show.c)
target_include_directories(${CURSES_INCLUDE_DIR} task2)