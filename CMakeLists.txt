cmake_minimum_required(VERSION 3.10)
project(RoboBank_Portfolio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SRC_FILES
    src/main.cpp
    src/BaseAccount.cpp
    src/CheckingAccount.cpp
    src/SavingsAccount.cpp
    src/Portfolio.cpp
    src/RoboLedger.cpp
    src/robocalculator.cpp
    src/IAccount.cpp
)

# Create executable
add_executable(RoboBank_Portfolio ${SRC_FILES})


target_compile_options(RoboBank_Portfolio PRIVATE -Wall -Wextra -pedantic)

target_include_directories(RoboBank_Portfolio PRIVATE src)
# Link Google Test
find_package(GTest REQUIRED)
target_link_libraries(RoboBank_Portfolio PRIVATE GTest::GTest GTest::Main pthread)