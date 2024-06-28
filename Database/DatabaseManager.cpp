//
// Created by Aditya Shrey on 6/27/24.
//

#include "DatabaseManager.h"
#include <utility>

DatabaseManager* DatabaseManager::instancePtr = nullptr;

DatabaseManager::DatabaseManager(std::string databaseName) : db(nullptr), dbName(std::move(databaseName)) {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

DatabaseManager* DatabaseManager::getDatabaseManager(const std::string& databaseName) {
    if (instancePtr == nullptr) {
        instancePtr = new DatabaseManager(databaseName);
    }
    return (instancePtr);
}

bool DatabaseManager::openDatabase() {
    int result = sqlite3_open(dbName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void DatabaseManager::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::executeQuery(const std::string& query) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}

static int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << (azColName[i] ? azColName[i] : "NULL") << ": "
                  << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << "\n";
    return 0;
}

void DatabaseManager::printDatabase(const std::string& tableName) {
    std::string query = "SELECT * FROM " + tableName;
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), callback, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}