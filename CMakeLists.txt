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
        User/UserSession.h
        User/UserSession.cpp
        Database/DatabaseManager.cpp
        Database/DatabaseManager.h
        StudyingMethods/StudyMethods.h
        StudyingMethods/Flashcards.cpp
        StudyingMethods/Flashcards.h
        StudyingMethods/MultipleChoice.cpp
        StudyingMethods/MultipleChoice.h
        StudyingMethods/InverseMultipleChoice.cpp
        StudyingMethods/InverseMultipleChoice.h
        Interface/MainWindow.cpp
        Interface/MainWindow.h
        Interface/LibraryPage.cpp
        Interface/LibraryPage.h
        Interface/CreateSetPage.cpp
        Interface/CreateSetPage.h
        Interface/AddQuestionsPage.cpp
        Interface/AddQuestionsPage.h
        Interface/EnterSetPage.cpp
        Interface/EnterSetPage.h
        Interface/MCPage.cpp
        Interface/InverseMCPage.cpp
        Interface/InverseMCPage.h
        Interface/FlashcardPage.cpp
        Interface/FlashcardPage.h
        Menu/Shortcuts.cpp
        Menu/Shortcuts.h
        Syncing/Github.cpp
        Syncing/Github.h
        Syncing/Google.cpp
        Syncing/Google.h
)

target_link_libraries(QuizLITE
        SQLite::SQLite3
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
        User/UserSession.h
        User/UserSession.cpp
        tests/testFlashcards.cpp
        StudyingMethods/StudyMethods.h
        StudyingMethods/Flashcards.cpp
        StudyingMethods/Flashcards.h
        StudyingMethods/MultipleChoice.cpp
        StudyingMethods/MultipleChoice.h
        StudyingMethods/InverseMultipleChoice.cpp
        StudyingMethods/InverseMultipleChoice.h
        tests/testMultipleChoice.cpp
        tests/testInverseMultipleChoice.cpp
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


