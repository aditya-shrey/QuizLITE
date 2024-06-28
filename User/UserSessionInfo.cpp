//
// Created by Aditya Shrey on 6/26/24.
//

#include "UserSessionInfo.h"
#include <utility>

UserSessionInfo* UserSessionInfo::instancePtr = nullptr;

UserSessionInfo::UserSessionInfo() {
    dbManager = DatabaseManager::getDatabaseManager("StudySets.db");

    if (dbManager->openDatabase()) {
        dbManager->executeQuery("CREATE TABLE IF NOT EXISTS set_names  (id INTEGER PRIMARY KEY, name TEXT UNIQUE);");
        dbManager->closeDatabase();
    }
}

UserSessionInfo* UserSessionInfo::getUserSessionInfo() {
    if (instancePtr == nullptr) {
        instancePtr = new UserSessionInfo();
    }
    return instancePtr;
}

void UserSessionInfo::setStudySet(std::string setName) {
    studySet = std::move(setName);
}

void UserSessionInfo::setSessionType(int sessionNum) {
    sessionType = sessionNum;
}

void UserSessionInfo::setValues(std::string setName, int sessionNum) {
    setStudySet(std::move(setName));
    setSessionType(sessionNum);
}

[[nodiscard]] std::string UserSessionInfo::getStudySet() const {
    return studySet;
}

[[nodiscard]] int UserSessionInfo::getSessionType() const {
    return sessionType;
}

void UserSessionInfo::printDatabaseTable(const std::string& tableName) {
    if (dbManager->openDatabase()) {
        dbManager->printDatabaseTable(tableName);
        dbManager->closeDatabase();
    }
}

bool UserSessionInfo::existsStudySet(const std::string& setName) {
    bool exists = false;
    if (dbManager->openDatabase()) {
        std::string query = "SELECT COUNT(*) FROM set_names WHERE name = '" + setName + "';";
        auto results = dbManager->executeQueryWithResults(query);
        if (!results.empty() && results[0]["COUNT(*)"] == "1") {
            exists = true;
        }
        dbManager->closeDatabase();
    }
    return exists;
}

bool UserSessionInfo::createStudySet(const std::string& setName) {
    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "INSERT INTO set_names (name) VALUES ('" + setName + "');";
        int result = dbManager->executeQuery(query);
        if (result == SQLITE_OK) {
            std::string createTableQuery = "CREATE TABLE IF NOT EXISTS \"" + setName + "\" (id INTEGER PRIMARY KEY, Key TEXT UNIQUE, Value TEXT);";
            int tableResult = dbManager->executeQuery(createTableQuery);
            if (tableResult == SQLITE_OK) {
                success = true;
            } else {
                std::cerr << "SQL error: could not create table for " << setName << ". Error: " << sqlite3_errmsg(dbManager->db) << std::endl;
            }
        } else {
            std::cerr << "SQL error: could not insert into set_names. Error: " << sqlite3_errmsg(dbManager->db) << std::endl;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database." << std::endl;
    }
    return success;
}

bool UserSessionInfo::deleteStudySet(const std::string& setName) {
    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "DELETE FROM set_names WHERE name = '" + setName + "';";
        int result = dbManager->executeQuery(query);
        if (result == SQLITE_OK) {
            std::string dropTableQuery = "DROP TABLE IF EXISTS \"" + setName + "\";";
            success = dbManager->executeQuery(dropTableQuery);
            if (!success) {
                std::cerr << "SQL error: could not drop table for " << setName << std::endl;
            }
        } else {
            std::cerr << "SQL error: " << sqlite3_errmsg(dbManager->db) << std::endl;
        }
        dbManager->closeDatabase();
    }
    return success;
}

bool UserSessionInfo::addToStudySet(const std::string& setName, const std::string& key, const std::string& value) {
    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "INSERT INTO \"" + setName + "\" (Key, Value) VALUES ('" + key + "', '" + value + "');";
        success = dbManager->executeQuery(query);
        if (!success) {
            std::cerr << "SQL error: " << sqlite3_errmsg(dbManager->db) << std::endl;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database." << std::endl;
    }
    return success;
}

bool UserSessionInfo::deleteFromStudySet(const std::string& setName, const std::string& key) {
    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "DELETE FROM \"" + setName + "\" WHERE Key = '" + key + "';";
        success = dbManager->executeQuery(query);
        if (!success) {
            std::cerr << "SQL error: " << sqlite3_errmsg(dbManager->db) << std::endl;
        }
        dbManager->closeDatabase();
    }
    return success;
}

bool UserSessionInfo::tableExists() {
    std::string query = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='set_names'";
    dbManager->openDatabase();
    dbManager->executeQuery(query);
    dbManager->closeDatabase();
}
