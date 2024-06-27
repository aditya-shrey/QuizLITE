//
// Created by Aditya Shrey on 6/26/24.
//

#include "UserSessionInfo.h"

#include <utility>

UserSessionInfo* UserSessionInfo::instancePtr = nullptr;

UserSessionInfo* UserSessionInfo::getUserSessionInfo() {
    if (instancePtr == nullptr) {
        instancePtr = new UserSessionInfo();
    }
    return instancePtr;
}

void UserSessionInfo::setStudySet(std::string setName) {
    this->studySet = std::move(setName);
}

void UserSessionInfo::setSessionType(int sessionNum) {
    this->sessionType = sessionNum;
}

void UserSessionInfo::setValues(std::string setName, int sessionNum) {
    this->setStudySet(std::move(setName));
    this->setSessionType(sessionNum);
}

void UserSessionInfo::getValues() const {
    std::cout << this->studySet << ", " << this->sessionType << std::endl;
}