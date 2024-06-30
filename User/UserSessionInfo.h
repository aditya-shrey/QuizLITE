//
// Created by Aditya Shrey on 6/26/24.
//
#ifndef QUIZLITE_USERSESSIONINFO_H
#define QUIZLITE_USERSESSIONINFO_H

#include "../Database/DatabaseManager.h"
#include <iostream>

/**
 * @class UserSessionInfo
 * @brief Singleton class to manage user session information.
 */
class UserSessionInfo {
public:
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
     * @brief Returns the name of the study set.
     */
    [[nodiscard]] std::string getStudySet() const;

    /**
     * @brief Returns the type of study set.
     */
    [[nodiscard]] int getSessionType() const;

    /**
     * @brief Prints all rows of a specified table in the database to the console.
     * @param tableName The name of the table to print.
     */
    void printDatabaseTable(const std::string& tableName);

    /**
     * @brief Checks if a study set exists in the database.
     * @param setName The name of the study set to check.
     * @return True if the study set exists, false otherwise.
     */
    bool existsStudySet(const std::string& setName);

    /**
     * @brief Creates a new study set in the database.
     * @param setName The name of the study set to create.
     * @return True if the study set was created successfully, false otherwise.
     */
    bool createStudySet(const std::string& setName);

    /**
     * @brief Deletes a study set from the database.
     * @param setName The name of the study set to delete.
     * @return True if the study set was deleted successfully, false otherwise.
     */
    bool deleteStudySet(const std::string& setName);

    /**
     * @brief Adds a key-value pair to a study set in the database.
     * @param setName The name of the study set to add the key-value pair to.
     * @param key The key to add.
     * @param value The value to associate with the key.
     * @return True if the key-value pair was added successfully, false otherwise.
     */
    bool addToStudySet(const std::string& setName,
        const std::string& Key,
        const std::string& Value);

    /**
     * @brief Deletes a key-value pair from a study set in the database.
     * @param setName The name of the study set to delete the key-value pair from.
     * @param key The key to delete.
     * @return True if the key-value pair was deleted successfully, false
     * otherwise.
     */
    bool deleteFromStudySet(const std::string& setName, const std::string& Key);

    /**
     * @brief Checks if the set_names table is empty.
     * @return True if the set_names table is empty, false otherwise.
     */
    bool isSetNamesTableEmpty();

    /**
     * @brief Updates the score for a given setName and key.
     * @param setName The name of the study set.
     * @param key The key to update.
     * @param isCorrect True if the answer is correct, false otherwise.
     * @return True if the score was updated successfully, false otherwise.
     */
    bool updateScore(const std::string& setName, const std::string& key, bool isCorrect);

    std::vector<std::pair<std::string, std::string>> getTableKeyValues(const std::string& setName);

    /**
     * @brief Retrieves x number of entries with the lowest accuracies given a set.
     * @param setName The name of the study set.
     * @param x The number of lowest accuracy entries to retrieve.
     * @return A vector of tuples representing key, value, and accuracy.
     */
    std::vector<std::tuple<std::string, std::string, float>> getLowestAccuracies(const std::string& setName, int x);

    /**
     * @brief Retrieves x number of random values from the set.
     * @param setName The name of the study set.
     * @param x The number of random values to retrieve.
     * @return A vector of pairs representing key-value pairs.
     */
    std::vector<std::pair<std::string, std::string>> getRandomEntries(const std::string& setName, int x);

    /**
     * @brief Drops all study sets in the database.
     * @return True if all sets were dropped successfully, false otherwise.
     */
    bool emptyAllSets();

    UserSessionInfo(const UserSessionInfo& obj) = delete;
    UserSessionInfo& operator=(const UserSessionInfo& obj) = delete;

private:
    std::string studySet; // Name of study set.
    int sessionType = 0; // Type of study set.

    DatabaseManager* dbManager;
    static UserSessionInfo* instancePtr; // Pointer to singleton instance.

    /**
     * @brief Private constructor to prevent instantiation.
     */
    UserSessionInfo();

    /**
     * @brief Resets the singleton instance of UserSessionInfo.
     */
    static void resetInstance();

    friend class UserSessionInfoTest;
};

#endif // QUIZLITE_USERSESSIONINFO_H
