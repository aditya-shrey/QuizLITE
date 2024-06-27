#include <iostream>
#include <utility>

#include "User/UserSessionInfo.h"
//#include <sqlite3.h>
//
//void createTables(sqlite3* db) {
//    const char* createStatsTableSQL = "CREATE TABLE IF NOT EXISTS VocabularyStats ("
//                                      "set_id INTEGER PRIMARY KEY AUTOINCREMENT, "
//                                      "set_name TEXT NOT NULL, "
//                                      "word_count INTEGER NOT NULL);";
//
//    const char* createSet1TableSQL = "CREATE TABLE IF NOT EXISTS Set1Words ("
//                                     "word_id INTEGER PRIMARY KEY AUTOINCREMENT, "
//                                     "word TEXT NOT NULL, "
//                                     "definition TEXT NOT NULL);";
//
//    const char* createSet2TableSQL = "CREATE TABLE IF NOT EXISTS Set2Words ("
//                                     "word_id INTEGER PRIMARY KEY AUTOINCREMENT, "
//                                     "word TEXT NOT NULL, "
//                                     "definition TEXT NOT NULL);";
//
//    char* errMsg = 0;
//    int rc = sqlite3_exec(db, createStatsTableSQL, nullptr, nullptr, &errMsg);
//
//    if (rc != SQLITE_OK) {
//        std::cerr << "SQL error creating VocabularyStats table: " << errMsg << std::endl;
//        sqlite3_free(errMsg);
//    }
//
//    rc = sqlite3_exec(db, createSet1TableSQL, nullptr, nullptr, &errMsg);
//
//    if (rc != SQLITE_OK) {
//        std::cerr << "SQL error creating Set1Words table: " << errMsg << std::endl;
//        sqlite3_free(errMsg);
//    }
//
//    rc = sqlite3_exec(db, createSet2TableSQL, nullptr, nullptr, &errMsg);
//
//    if (rc != SQLITE_OK) {
//        std::cerr << "SQL error creating Set2Words table: " << errMsg << std::endl;
//        sqlite3_free(errMsg);
//    }
//}
//
//void printTableContents(sqlite3* db, const std::string& tableName) {
//    std::string selectSQL = "SELECT * FROM " + tableName + ";";
//    sqlite3_stmt* stmt;
//    int rc = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
//
//    if (rc != SQLITE_OK) {
//        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
//        return;
//    }
//
//    std::cout << "Contents of table " << tableName << ":" << std::endl;
//
//    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
//        int word_id = sqlite3_column_int(stmt, 0);
//        const unsigned char* word = sqlite3_column_text(stmt, 1);
//        const unsigned char* definition = sqlite3_column_text(stmt, 2);
//
//        std::cout << "Word ID: " << word_id << ", Word: " << word << ", Definition: " << definition << std::endl;
//    }
//
//    if (rc != SQLITE_DONE) {
//        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
//    }
//
//    sqlite3_finalize(stmt);
//}
//
//int main() {
//    sqlite3* db;
//    int rc = sqlite3_open("vocabularyDB.db", &db);
//
//    if (rc) {
//        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//        return 1;
//    }
//
//    createTables(db);
//
//    // Example of inserting data into VocabularyStats
//    std::string addStatsSQL = "INSERT INTO VocabularyStats (set_name, word_count) VALUES ('Set 1', 100);";
//    char* errMsg = 0;
//    rc = sqlite3_exec(db, addStatsSQL.c_str(), nullptr, nullptr, &errMsg);
//
//    if (rc != SQLITE_OK) {
//        std::cerr << "SQL error inserting into VocabularyStats: " << errMsg << std::endl;
//        sqlite3_free(errMsg);
//    }
//
//    // Example of inserting data into Set1Words
//    std::string addWordSQL = "INSERT INTO Set1Words (word, definition) VALUES ('abate', 'become less intense or widespread');";
//    rc = sqlite3_exec(db, addWordSQL.c_str(), nullptr, nullptr, &errMsg);
//
//    if (rc != SQLITE_OK) {
//        std::cerr << "SQL error inserting into Set1Words: " << errMsg << std::endl;
//        sqlite3_free(errMsg);
//    }
//
//    // Print the contents of Set1Words
//    printTableContents(db, "Set1Words");
//
//    sqlite3_close(db);
//    return 0;
//}


int main() {
    std::cout << "Starting QuizLITE session.\n" << std::endl;

    UserSessionInfo* userSession = UserSessionInfo::getUserSessionInfo();

    userSession->setValues("Erika", 1);
    userSession->getValues();

    return 0;
}