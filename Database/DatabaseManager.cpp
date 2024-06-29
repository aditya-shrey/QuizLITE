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

bool DatabaseManager::executeQuery(const std::string& query) const {
    if (!db) {
        std::cerr << "Database not open or not initialized" << std::endl;
        return false;
    }

    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << (errorMessage ? errorMessage : "Unknown error") << std::endl;
        if (errorMessage) {
            sqlite3_free(errorMessage);
        }
        return false;
    }
    return true;
}

static int callbackStore(void* data, int argc, char** argv, char** azColName) {
    auto* rows = static_cast<std::vector<std::map<std::string, std::string>>*>(data);
    std::map<std::string, std::string> row;
    for (int i = 0; i < argc; i++) {
        row[azColName[i]] = argv[i] ? argv[i] : "NULL";
    }
    rows->push_back(row);
    return 0;
}

std::vector<std::map<std::string, std::string>> DatabaseManager::executeQueryWithResults(const std::string& query) {
    std::vector<std::map<std::string, std::string>> rows;
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), callbackStore, &rows, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    return rows;
}

static int callbackPrint(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << (azColName[i] ? azColName[i] : "NULL") << ": "
                  << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << "\n";
    return 0;
}

void DatabaseManager::printDatabaseTable(const std::string& tableName) const {
    std::string query = "SELECT * FROM " + tableName;
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), callbackPrint, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}