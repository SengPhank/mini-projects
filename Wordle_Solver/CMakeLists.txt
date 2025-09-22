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
    src/Helper.cpp
    src/Possible_Words.cpp
    src/gui/Frame.cpp
)

# Link wxWidgets
target_link_libraries(WordleSolver PRIVATE ${wxWidgets_LIBRARIES})

# Add include path
target_include_directories(WordleSolver PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(WordleSolver PRIVATE ${CMAKE_SOURCE_DIR})

# Copy data file to build dir
configure_file(data/Wordle_Words.json Wordle_Words.json COPYONLY)
