cmake_minimum_required(VERSION 3.25)
project(c_review C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

add_executable(linked_list_quiz linked_list_quiz.c)
add_executable(linked_list_quiz2 linked_list_quiz2.c)
add_executable(linked_list_quiz2_circular_doubly_linked_list linked_list_quiz2_circular_doubly_linked_list.c)
add_executable(next_pow2 next_pow2.c)
add_executable(count_utf8 count_utf8.c)
