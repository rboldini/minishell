cmake_minimum_required(VERSION 3.19)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c parser.c parser.h executor.c subsystem.c minishell.h)