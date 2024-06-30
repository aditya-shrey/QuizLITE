//
// Created by Aditya Shrey on 6/26/24.
//
#include "UserSessionInfo.h"
#include <iostream>
#include <utility>

UserSessionInfo* UserSessionInfo::instancePtr = nullptr;

UserSessionInfo::UserSessionInfo()
{
    dbManager = DatabaseManager::getDatabaseManager("A0000001.db");
    if (dbManager->openDatabase()) {
        if (dbManager->executeQuery(
                "CREATE TABLE IF NOT EXISTS set_names (id INTEGER "
                "PRIMARY KEY, name TEXT UNIQUE);")
            != SQLITE_OK) {
            std::cerr << "Failed to create table set_names" << std::endl;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database in constructor" << std::endl;
    }
}

UserSessionInfo* UserSessionInfo::getUserSessionInfo()
{
    if (instancePtr == nullptr) {
        instancePtr = new UserSessionInfo();
    }
    return instancePtr;
}

void UserSessionInfo::setStudySet(std::string setName)
{
    studySet = std::move(setName);
}

void UserSessionInfo::setSessionType(int sessionNum)
{
    sessionType = sessionNum;
}

void UserSessionInfo::setValues(std::string setName, int sessionNum)
{
    setStudySet(std::move(setName));
    setSessionType(sessionNum);
}

[[nodiscard]] std::string UserSessionInfo::getStudySet() const
{
    return studySet;
}

[[nodiscard]] int UserSessionInfo::getSessionType() const
{
    return sessionType;
}

void UserSessionInfo::printDatabaseTable(const std::string& tableName)
{
    if (dbManager->openDatabase()) {
        std::cout << "Printing table: " << tableName << std::endl;
        dbManager->printDatabaseTable(tableName);
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for printing table: " << tableName
                  << std::endl;
    }
}

bool UserSessionInfo::existsStudySet(const std::string& setName)
{
    bool exists = false;
    if (dbManager->openDatabase()) {
        std::string query = "SELECT COUNT(*) FROM set_names WHERE name = '" + setName + "';";
        auto results = dbManager->executeQueryWithResults(query);
        if (!results.empty() && results[0]["COUNT(*)"] == "1") {
            exists = true;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for existsStudySet" << std::endl;
    }
    return exists;
}

bool UserSessionInfo::createStudySet(const std::string& setName)
{
    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "INSERT INTO set_names (name) VALUES (?);";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(dbManager->db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, setName.c_str(), -1, SQLITE_STATIC);
            int result = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            if (result == SQLITE_DONE) {
                std::string createTableQuery = "CREATE TABLE IF NOT EXISTS \"" + setName + "\" (id INTEGER PRIMARY KEY, Key TEXT UNIQUE, Value TEXT, TotalCorrect INTEGER, TimesAsked INTEGER);";
                if (dbManager->executeQuery(createTableQuery) == SQLITE_OK) {
                    success = true;
                } else {
                    std::cerr << "SQL error: could not create table for " << setName
                              << std::endl;
                }
            } else {
                std::cerr << setName << " already exists or insertion failed. Error: "
                          << sqlite3_errmsg(dbManager->db) << std::endl;
            }
        } else {
            std::cerr << "SQL error: failed to prepare insert query. Error: "
                      << sqlite3_errmsg(dbManager->db) << std::endl;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for createStudySet" << std::endl;
    }
    return success;
}

bool UserSessionInfo::deleteStudySet(const std::string& setName)
{
    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "DELETE FROM set_names WHERE name = '" + setName + "';";
        int result = dbManager->executeQuery(query);
        if (result == SQLITE_OK) {
            std::string dropTableQuery = "DROP TABLE IF EXISTS \"" + setName + "\";";
            int dropResult = dbManager->executeQuery(dropTableQuery);
            if (dropResult == SQLITE_OK) {
                success = true;
            } else {
                std::cerr << "SQL error: could not drop table for " << setName
                          << ". Error: " << sqlite3_errmsg(dbManager->db) << std::endl;
            }
        } else {
            std::cerr << "SQL error: could not delete from set_names for " << setName
                      << ". Error: " << sqlite3_errmsg(dbManager->db) << std::endl;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for deleteStudySet" << std::endl;
    }
    return success;
}

bool UserSessionInfo::addToStudySet(const std::string& setName, const std::string& key, const std::string& value)
{
    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "INSERT INTO \"" + setName + "\" (Key, Value, TotalCorrect, TimesAsked) VALUES ('" + key + "', '" + value + "', 0, 1);";
        int result = dbManager->executeQuery(query);
        if (result == SQLITE_OK) {
            success = true;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for addToStudySet" << std::endl;
    }
    return success;
}

bool UserSessionInfo::deleteFromStudySet(const std::string& setName, const std::string& key)
{
    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "DELETE FROM \"" + setName + "\" WHERE Key = '" + key + "';";
        int result = dbManager->executeQuery(query);
        if (result == SQLITE_OK) {
            success = true;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for deleteFromStudySet" << std::endl;
    }
    return success;
}

bool UserSessionInfo::isSetNamesTableEmpty()
{
    if (dbManager->openDatabase())
        return dbManager->isTableEmpty("set_names");
    return false;
}

bool UserSessionInfo::updateScore(const std::string& setName, const std::string& key, bool isCorrect)
{
    if (!existsStudySet(setName)) {
        std::cerr << "Study set " << setName << " does not exist." << std::endl;
        return false;
    }

    bool success = false;
    if (dbManager->openDatabase()) {
        std::string query = "UPDATE \"" + setName + "\" SET TimesAsked = TimesAsked + 1";
        if (isCorrect) {
            query += ", TotalCorrect = TotalCorrect + 1";
        }
        query += " WHERE Key = '" + key + "';";
        int result = dbManager->executeQuery(query);
        if (result == SQLITE_OK) {
            success = true;
        } else {
            std::cerr << "SQL error: could not update score for " << key << " in " << setName << ". Error: "
                      << sqlite3_errmsg(dbManager->db) << std::endl;
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for updateScore" << std::endl;
    }
    return success;
}

std::vector<std::pair<std::string, std::string>> UserSessionInfo::getTableKeyValues(const std::string& setName)
{
    std::vector<std::pair<std::string, std::string>> keyValues;
    if (!existsStudySet(setName)) {
        std::cerr << "Study set " << setName << " does not exist." << std::endl;
        return keyValues;
    }

    if (dbManager->openDatabase()) {
        std::string query = "SELECT Key, Value FROM \"" + setName + "\";";
        auto results = dbManager->executeQueryWithResults(query);
        for (const auto& row : results) {
            keyValues.emplace_back(row.at("Key"), row.at("Value"));
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for getTableKeyValues" << std::endl;
    }
    return keyValues;
}

std::vector<std::tuple<std::string, std::string, float>> UserSessionInfo::getLowestAccuracies(const std::string& setName, int x)
{
    std::vector<std::tuple<std::string, std::string, float>> lowestAccuracies;
    if (!existsStudySet(setName)) {
        std::cerr << "Study set " << setName << " does not exist." << std::endl;
        return lowestAccuracies;
    }

    if (dbManager->openDatabase()) {
        std::string query = "SELECT Key, Value, (TotalCorrect * 1.0 / TimesAsked) as Accuracy "
                            "FROM \""
            + setName + "\" "
                        "ORDER BY Accuracy ASC LIMIT "
            + std::to_string(x) + ";";
        auto results = dbManager->executeQueryWithResults(query);
        for (const auto& row : results) {
            lowestAccuracies.emplace_back(row.at("Key"), row.at("Value"), std::stof(row.at("Accuracy")));
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for getLowestAccuracies" << std::endl;
    }
    return lowestAccuracies;
}

std::vector<std::pair<std::string, std::string>> UserSessionInfo::getRandomEntries(const std::string& setName, int x)
{
    std::vector<std::pair<std::string, std::string>> randomEntries;
    if (!existsStudySet(setName)) {
        std::cerr << "Study set " << setName << " does not exist." << std::endl;
        return randomEntries;
    }

    if (dbManager->openDatabase()) {
        std::string query = "SELECT Key, Value FROM \"" + setName + "\" ORDER BY RANDOM() LIMIT " + std::to_string(x) + ";";
        auto results = dbManager->executeQueryWithResults(query);
        for (const auto& row : results) {
            randomEntries.emplace_back(row.at("Key"), row.at("Value"));
        }
        dbManager->closeDatabase();
    } else {
        std::cerr << "Failed to open database for getRandomEntries" << std::endl;
    }
    return randomEntries;
}