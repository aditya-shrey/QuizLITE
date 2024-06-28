cmake_minimum_required(VERSION 3.27)
project(QuizLITE)

set(CMAKE_CXX_STANDARD 23)

find_package(SQLite3 REQUIRED)

add_executable(QuizLITE main.cpp
        User/UserSessionInfo.h
        User/UserSessionInfo.cpp
        Database/DatabaseManager.cpp
        Database/DatabaseManager.h
)
target_link_libraries(QuizLITE SQLite::SQLite3)


