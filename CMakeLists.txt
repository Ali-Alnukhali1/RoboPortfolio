cmake_minimum_required(VERSION 3.10)
project(RoboBank_Portfolio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Shared library for your project
add_library(RoboBankLib
    src/BaseAccount.cpp
    src/CheckingAccount.cpp
    src/SavingsAccount.cpp
    src/Portfolio.cpp
    src/RoboLedger.cpp
    src/robocalculator.cpp
)

target_include_directories(RoboBankLib
        PUBLIC include
        PRIVATE src)

target_compile_options(RoboBankLib PRIVATE -Wall -Wextra -pedantic)

# Main executable
add_executable(RoboBank_Portfolio src/main.cpp)
target_link_libraries(RoboBank_Portfolio PRIVATE RoboBankLib)
target_compile_options(RoboBank_Portfolio PRIVATE -Wall -Wextra -pedantic)


# Tests executable
find_package(GTest REQUIRED)
add_executable(tests tests/tests.cpp)
target_link_libraries(tests PRIVATE RoboBankLib GTest::GTest GTest::Main pthread)
target_compile_options(tests PRIVATE -Wall -Wextra -pedantic)

#To run from the folder tests not build
set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)