cmake_minimum_required(VERSION 3.26)
project(itp-project)

set(CMAKE_C_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.c" "src/functions/*.c" "include/*.h")
add_library(mylib STATIC ${SOURCES})

add_executable(itp-project src/main.c)
target_link_libraries(itp-project mylib)