cmake_minimum_required(VERSION 3.25)
project(c_review C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

add_executable(linked_list_quiz linked_list_quiz.c)
