cmake_minimum_required(VERSION 3.23)
project(snake_jeu_allegro C)

set(CMAKE_C_STANDARD 99)

add_executable(snake_jeu_allegro main.c)
target_link_libraries(snake_jeu_allegro -lmingw32 -lalleg44)
