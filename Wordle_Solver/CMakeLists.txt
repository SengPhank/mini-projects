cmake_minimum_required(VERSION 3.14)
project(WordleSolver)

# Set minimum C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add your source files
add_executable(WordleSolver 
    main.cpp 
    src/All_Words.cpp
    )

# Add include path
target_include_directories(WordleSolver PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(WordleSolver PRIVATE ${CMAKE_SOURCE_DIR})
configure_file(data/Wordle_Words.json Wordle_Words.json COPYONLY)
