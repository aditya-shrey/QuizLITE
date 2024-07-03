#include <iostream>
#include "User/UserSessionInfo.h"
#include "Menu/MainWindow.h"
#include <QApplication>

int main(int argc, char **argv) {
    std::cout << "Starting QuizLITE session.\n" << std::endl;

    UserSessionInfo* userSession = UserSessionInfo::getUserSessionInfo();

//    std::cout << "Attempting to create table: " << setName << std::endl;
//    std::string createTableQuery = "CREATE TABLE IF NOT EXISTS \"" + setName + "\" (id INTEGER PRIMARY KEY, Key TEXT UNIQUE, Value TEXT);";
//    int tableResult = dbManager->executeQuery(createTableQuery);
//    std::cout << "Table creation result: " << tableResult << std::endl;

//    std::string setName = "Math 101";
//    DatabaseManager* databaseManager = DatabaseManager::getDatabaseManager("StudySets.db");
//    databaseManager->openDatabase();
//    std::cout << "Attempting to create table: " << setName << std::endl;
//    std::string createTableQuery = "CREATE TABLE IF NOT EXISTS \"" + setName + "\" (id INTEGER PRIMARY KEY, Key TEXT UNIQUE, Value TEXT);";
//    int tableResult = databaseManager->executeQuery(createTableQuery);
//    std::cout << "Table creation result: " << tableResult << std::endl;

    std::cout << "before adding sets" << std::endl;
    userSession->printDatabaseTable("set_names");

    if (!userSession->existsStudySet("Math101")) {
        userSession->createStudySet("Math101");
    }
    if (!userSession->existsStudySet("Math201")) {
        userSession->createStudySet("Math201");
    }

    std::cout << "after adding sets" << std::endl;
    userSession->printDatabaseTable("set_names");

    userSession->deleteStudySet("Math201");

    std::cout << "after deleting sets" << std::endl;
    userSession->printDatabaseTable("set_names");

    std::cout << "before adding math101" << std::endl;
    userSession->printDatabaseTable("\'Math101\'");

    userSession->addToStudySet("Math101", "Plus", "+");

    std::cout << "after adding math101" << std::endl;
    userSession->printDatabaseTable("Math101");

    userSession->deleteFromStudySet("Math101", "Plus");

    std::cout << "after deleting plys math101" << std::endl;
    userSession->printDatabaseTable("Math101");


    // Qt Interface
     QApplication app (argc, argv);
     MainWindow window;
     window.show();

     return app.exec();
}