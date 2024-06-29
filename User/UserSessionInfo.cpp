//
// Created by Aditya Shrey on 6/26/24.
//

#include "UserSessionInfo.h"
#include <iostream>
#include <utility>

UserSessionInfo *UserSessionInfo::instancePtr = nullptr;

UserSessionInfo::UserSessionInfo() {
  dbManager = DatabaseManager::getDatabaseManager("StudySet.db");

  if (dbManager->openDatabase()) {
    std::cout << "Database opened successfully" << std::endl;
    dbManager->executeQuery("CREATE TABLE IF NOT EXISTS set_names (id INTEGER "
                            "PRIMARY KEY, name TEXT UNIQUE);");
    dbManager->closeDatabase();
  } else {
    std::cerr << "Failed to open database in constructor" << std::endl;
  }
}

UserSessionInfo *UserSessionInfo::getUserSessionInfo() {
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

void UserSessionInfo::printDatabaseTable(const std::string &tableName) {
  if (dbManager->openDatabase()) {
    std::cout << "Printing table: " << tableName << std::endl;
    dbManager->printDatabaseTable(tableName);
    dbManager->closeDatabase();
  } else {
    std::cerr << "Failed to open database for printing table: " << tableName
              << std::endl;
  }
}

bool UserSessionInfo::existsStudySet(const std::string &setName) {
  bool exists = false;
  if (dbManager->openDatabase()) {
    std::string query =
        "SELECT COUNT(*) FROM set_names WHERE name = '" + setName + "';";
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

bool UserSessionInfo::createStudySet(const std::string &setName) {
  bool success = false;
  if (dbManager->openDatabase()) {
    std::string query = "INSERT INTO set_names (name) VALUES (?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(dbManager->db, query.c_str(), -1, &stmt, nullptr) ==
        SQLITE_OK) {
      sqlite3_bind_text(stmt, 1, setName.c_str(), -1, SQLITE_STATIC);
      int result = sqlite3_step(stmt);
      sqlite3_finalize(stmt);

      if (result == SQLITE_DONE) {
        std::string createTableQuery =
            "CREATE TABLE IF NOT EXISTS \"" + setName +
            "\" (id INTEGER PRIMARY KEY, Key TEXT UNIQUE, Value TEXT);";
        if (dbManager->executeQuery(createTableQuery)) {
          success = true;
        } else {
          std::cerr << "SQL error: could not create table for " << setName
                    << std::endl;
        }
      } else {
        std::cout << setName << " already exists or insertion failed. Error: "
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

bool UserSessionInfo::deleteStudySet(const std::string &setName) {
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
    }
    dbManager->closeDatabase();
  } else {
    std::cerr << "Failed to open database for deleteStudySet" << std::endl;
  }
  return success;
}

bool UserSessionInfo::addToStudySet(const std::string &setName,
                                    const std::string &key,
                                    const std::string &value) {
  bool success = false;
  if (dbManager->openDatabase()) {
    std::string query = "INSERT INTO \"" + setName +
                        "\" (Key, Value) VALUES ('" + key + "', '" + value +
                        "');";
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

bool UserSessionInfo::deleteFromStudySet(const std::string &setName,
                                         const std::string &key) {
  bool success = false;
  if (dbManager->openDatabase()) {
    std::string query =
        "DELETE FROM \"" + setName + "\" WHERE Key = '" + key + "';";
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
