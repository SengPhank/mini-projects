cmake_minimum_required(VERSION 3.14)
project(WordleProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch nlohmann/json header-only library
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3 # or latest stable
)
FetchContent_MakeAvailable(json)

# Build your executable from Wordle.cpp
add_executable(Wordle Wordle.cpp)

# Link the JSON library
target_link_libraries(Wordle PRIVATE nlohmann_json::nlohmann_json)

# Copy the JSON data file to the build directory so the program can find it
configure_file(Wordle_List.json Wordle_List.json COPYONLY)
