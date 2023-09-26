cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(my_cp)
set(cp_files main.c src/copy_files.c src/getopt_while.c include/copy_files.h include/getopt_while.h)
add_executable(my_cp ${cp_files})