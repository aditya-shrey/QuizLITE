//
// Created by Aditya Shrey on 6/27/24.
//

#ifndef QUIZLITE_DATABASEMANAGER_H
#define QUIZLITE_DATABASEMANAGER_H

#include <iostream>
#include <sqlite3.h>
#include <string>

class DatabaseManager {
private:
    sqlite3* db;
    std::string dbName;

    static DatabaseManager* instancePtr;

    explicit DatabaseManager(std::string databaseName);

public:
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    static DatabaseManager* getDatabaseManager(const std::string& databaseName);

    bool openDatabase();
    void closeDatabase();
    bool executeQuery(const std::string& query);

    void printDatabase(const std::string& tableName);
};

#endif //QUIZLITE_DATABASEMANAGER_H
