//
// Created by Aditya Shrey on 6/26/24.
//

#ifndef QUIZLITE_USERSESSIONINFO_H
#define QUIZLITE_USERSESSIONINFO_H

#include <iostream>

class UserSessionInfo {
private:
    std::string studySet;
    int sessionType = 0;

    static UserSessionInfo* instancePtr;

    UserSessionInfo() = default;
public:
    UserSessionInfo(const UserSessionInfo& obj) = delete;
    UserSessionInfo& operator=(const UserSessionInfo& obj) = delete;

    static UserSessionInfo* getUserSessionInfo();

    void setStudySet(std::string setName);

    void setSessionType(int sessionNum);

    void setValues(std::string setName, int sessionNum);

    void getValues() const;

};

#endif //QUIZLITE_USERSESSIONINFO_H
