cmake_minimum_required(VERSION 3.19)
project("minishell" C)

set(CMAKE_C_STANDARD 99)

add_executable("minishell" srcs/main.c srcs/parser.c includes/parser.h srcs/executor.c srcs/subsystem.c includes/minishell.h srcs/command.c srcs/lexar.c includes/color.h srcs/ft_echo.c srcs/ft_pwd.c)