cmake_minimum_required(VERSION 3.18)
project(QuizLITE)

# Set compiler flags.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors -g")


# Make sure we have cloned googletest.
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} -C ${PROJECT_SOURCE_DIR} submodule update --init --recursive)
    execute_process(COMMAND ${GIT_EXECUTABLE} -C ${PROJECT_SOURCE_DIR}/lib/googletest checkout tags/release-1.8.1)
endif()

# Define all testing related content here
enable_testing()

# Bring in GoogleTest
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850  # release-1.12.1
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
include_directories(${googletest_SOURCE_DIR}/googletest/include)

find_package(SQLite3 REQUIRED)
find_package(GTest REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()


add_executable(QuizLITE
        main.cpp
        User/UserSessionInfo.h
        User/UserSessionInfo.cpp
        Database/DatabaseManager.h
        Database/DatabaseManager.cpp
        Menu/MainWindow.h
        Menu/MainWindow.cpp
)
target_link_libraries(QuizLITE SQLite::SQLite3)
target_link_libraries(QuizLITE
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
)


# Test executables
add_executable(TestExecutables
        tests/main.cpp
        tests/testDatabase.cpp
        Database/DatabaseManager.cpp
        Database/DatabaseManager.h
        tests/testUser.cpp
        User/UserSessionInfo.h
        User/UserSessionInfo.cpp
)
target_link_libraries(TestExecutables
        GTest::GTest
        GTest::Main
        SQLite::SQLite3
)

# Define TESTING macro for test build
target_compile_definitions(TestExecutables PRIVATE TESTING)

# Add tests to CTest
add_test(NAME TestExecutables COMMAND TestExecutables)

# Custom target to run tests with verbose output
add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS TestExecutables
)