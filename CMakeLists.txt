cmake_minimum_required(VERSION 3.12)
project(texteditor)

set(CMAKE_CXX_STANDARD 17)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})

add_executable(texteditor main.cpp utils.h)

target_link_libraries(texteditor ${FLTK_LIBRARIES})


