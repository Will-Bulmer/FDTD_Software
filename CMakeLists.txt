cmake_minimum_required(VERSION 3.10)

# Set the project name
project(FDTD_Software)

# Add the C++ standard. Feel free to adjust to your needs.
set(CMAKE_CXX_STANDARD 17)

# If nlohmann_json is not installed globally and is in a custom path, you can provide the path using the line below
# list(APPEND CMAKE_PREFIX_PATH "path_to_nlohmann_json")

# Find the nlohmann_json and Catch2 packages
find_package(nlohmann_json REQUIRED)
find_package(Catch2 REQUIRED)

# Add your source files
add_executable(runInputTests tests/inputTests.cpp)
add_executable(runMain src/main.cpp)

# Include Directories
target_include_directories(runMain PRIVATE ${CMAKE_SOURCE_DIR}/input)
target_include_directories(runInputTests PRIVATE ${CMAKE_SOURCE_DIR}/tests)

# Link the libraries to your executables
target_link_libraries(runMain PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(runInputTests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(runInputTests PRIVATE Catch2::Catch2)

# Tests
enable_testing()
add_test(NAME inputTests COMMAND runInputTests)
