cmake_minimum_required(VERSION 3.14)
project(WordleSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files
add_executable(WordleSolver main.cpp All_Words.cpp)

# Add include path
target_include_directories(WordleSolver PRIVATE ${CMAKE_SOURCE_DIR})
configure_file(Wordle_Words.json Wordle_Words.json COPYONLY)
