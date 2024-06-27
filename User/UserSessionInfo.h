//
// Created by Aditya Shrey on 6/26/24.
//

#ifndef QUIZLITE_USERSESSIONINFO_H
#define QUIZLITE_USERSESSIONINFO_H

#include <iostream>

/**
 * @class UserSessionInfo
 * @brief Singleton class to manage user session information.
 */
class UserSessionInfo {
private:
    std::string studySet; // Name of study set.
    int sessionType = 0; // Type of study set.

    static UserSessionInfo* instancePtr; // Pointer to singleton instance.

    /**
     * @brief Private constructor to prevent instantiation.
     */
    UserSessionInfo() = default;
public:
    UserSessionInfo(const UserSessionInfo& obj) = delete;
    UserSessionInfo& operator=(const UserSessionInfo& obj) = delete;

    /**
     * @brief Gets the singleton instance of UserSessionInfo.
     * @return Pointer to the singleton instance.
     */
    static UserSessionInfo* getUserSessionInfo();

    /**
     * @brief Sets the name of the study set.
     * @param setName The name of the study set.
     */
    void setStudySet(std::string setName);

    /**
     * @brief Sets the session type.
     * @param sessionNum The type of the session.
     */
    void setSessionType(int sessionNum);

    /**
     * @brief Sets the values of the study set name and session type.
     * @param setName The name of the study set.
     * @param sessionNum The type of the session.
     */
    void setValues(std::string setName, int sessionNum);

    /**
     * @brief Prints the values of the study set name and session type.
     */
    void getValues() const;

};

#endif //QUIZLITE_USERSESSIONINFO_H
