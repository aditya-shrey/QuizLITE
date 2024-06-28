#include <iostream>
#include <utility>

#include "User/UserSessionInfo.h"

int main() {
    std::cout << "Starting QuizLITE session.\n" << std::endl;

    UserSessionInfo* userSession = UserSessionInfo::getUserSessionInfo();

    std::cout << "before adding sets" << std::endl;
    userSession->printDatabaseTable("set_names");

    if (!userSession->existsStudySet("Math101")) {
        userSession->createStudySet("Math101");
    }
    if (!userSession->existsStudySet("Math201")) {
        userSession->createStudySet("Math201");
    }

    std::cout << "before adding sets" << std::endl;
    userSession->printDatabaseTable("set_names");

    userSession->deleteStudySet("Math201");

    std::cout << "before adding sets" << std::endl;
    userSession->printDatabaseTable("set_names");

    std::cout << "before adding math101" << std::endl;
    userSession->printDatabaseTable("Math101");

    userSession->addToStudySet("Math101", "Plus", "+");

    std::cout << "after adding math101" << std::endl;
    userSession->printDatabaseTable("Math101");

    userSession->deleteFromStudySet("Math101", "Plus");

    std::cout << "after deleting plys math101" << std::endl;
    userSession->printDatabaseTable("Math101");


    return 0;
}