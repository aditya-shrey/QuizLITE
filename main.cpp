#include <iostream>
#include <utility>

#include "User/UserSessionInfo.h"
#include "Database/DatabaseManager.h"


int main() {
    std::cout << "Starting QuizLITE session.\n" << std::endl;

    UserSessionInfo* userSession = UserSessionInfo::getUserSessionInfo();

    userSession->setValues("AnimalsStudySet", 0);
    std::cout << "Study session is " << userSession->getStudySet() << std::endl;

    // Access the database
    DatabaseManager* dbManager = DatabaseManager::getDatabaseManager("example.db");
    if (dbManager->openDatabase()) {
        dbManager->executeQuery("CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, name TEXT);");
        dbManager->executeQuery("INSERT INTO test (name) VALUES ('Sample Name');");
        dbManager->printDatabase("test");
        dbManager->closeDatabase();
    }

    return 0;
}