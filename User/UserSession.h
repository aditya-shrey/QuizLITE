//
// Created by Aditya Shrey on 6/26/24.
//
#ifndef QUIZLITE_UserSession_H
#define QUIZLITE_UserSession_H

#include "../Database/DatabaseManager.h"
#include <iostream>
#include <utility>

/**
 * @class UserSession
 * @brief Singleton class to manage user session information.
 */
class UserSession {
public:
    /**
     * @brief Gets the singleton instance of UserSession.
     *
     * @return Pointer to the singleton instance.
     */
    static UserSession* getUserSession();

    /**
     * @brief Checks if a study set exists in the database.
     *
     * @param setName The name of the study set to check.
     * @return True if the study set exists, false otherwise.
     */
    bool existsStudySet(const std::string& setName);

    /**
     * @brief Creates a new study set in the database.
     *
     * @param setName The name of the study set to create.
     * @return True if the study set was created successfully, false otherwise.
     */
    bool createStudySet(const std::string& setName);

    /**
     * @brief Deletes a study set from the database.
     *
     * @param setName The name of the study set to delete.
     * @return True if the study set was deleted successfully, false otherwise.
     */
    bool deleteStudySet(const std::string& setName);

    /**
     * @brief Adds a key-value pair to a study set in the database.
     *
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
     *
     * @param setName The name of the study set to delete the key-value pair from.
     * @param key The key to delete.
     * @return True if the key-value pair was deleted successfully, false
     * otherwise.
     */
    bool deleteFromStudySet(const std::string& setName, const std::string& Key);

    /**
     * @brief Checks if the set_names table is empty.
     *
     * @return True if the set_names table is empty, false otherwise.
     */
    bool isSetNamesTableEmpty();

    /**
     * @brief Updates the score for a given setName and key.
     *
     * @param setName The name of the study set.
     * @param key The key to update.
     * @param isCorrect True if the answer is correct, false otherwise.
     * @return True if the score was updated successfully, false otherwise.
     */
    bool updateScore(const std::string& setName, const std::string& key, bool isCorrect);

    std::vector<std::pair<std::string, std::string>> getTableKeyValues(const std::string& setName);

    /**
     * @brief Gets all data from a study set table.
     *
     * @param setName Name of the study set.
     * @return Vector of tuples containing id, key, value, total correct, and times asked.
     */
    std::vector<std::tuple<int, std::string, std::string, int, int>> getTable(const std::string& setName);

    /**
     * @brief Retrieves the contents of the set_names table.
     *
     * @return A vector of maps where each map represents a row in the set_names table.
     */
    std::vector<std::map<std::string, std::string>> getMainTable();

    /**
     * @brief Retrieves x number of entries with the lowest accuracies given a set.
     *
     * @param setName The name of the study set.
     * @param x The number of lowest accuracy entries to retrieve.
     * @return A vector of tuples representing key, value, and accuracy.
     */
    std::vector<std::tuple<std::string, std::string, float>> getLowestAccuracies(const std::string& setName, int x);

    /**
     * @brief Retrieves x number of random values from the set.
     *
     * @param setName The name of the study set.
     * @param x The number of random values to retrieve.
     * @return A vector of pairs representing key-value pairs.
     */
    std::vector<std::pair<std::string, std::string>> getRandomEntries(const std::string& setName, int x);

    /**
     * @brief Drops all study sets in the database.
     *
     * @return True if all sets were dropped successfully, false otherwise.
     */
    bool emptyAllSets();

    /**
     * @brief Prints all rows of a specified table in the database to the console.
     *
     * @param tableName The name of the table to print.
     */
    void printDatabaseTable(const std::string& tableName);

    /**
     * @brief Gets the size of a study set in the database.
     *
     * @param setName The name of the study set.
     * @return The size of the study set.
     */
    int getStudySetSize(const std::string& setName);

    UserSession(const UserSession& obj) = delete;
    UserSession& operator=(const UserSession& obj) = delete;

private:
    /**
     * @brief Name of the study set for the current session.
     */
    std::string studySet; // Name of study set.

    /**
     * @brief Session type identifier.
     */
    int sessionType = 0; // Type of study set.

    /**
     * @brief Pointer to the database manager.
     */
    DatabaseManager* dbManager;

    /**
     * @brief Pointer to the singleton instance.
     */
    static UserSession* instancePtr;

    /**
     * @brief Private constructor for singleton pattern.
     */
    UserSession();

#ifdef TESTING
    /**
     * @brief Resets the singleton instance of UserSession.
     */
    static void resetInstance();
#endif

    friend class UserSessionTest;
    friend class MultipleChoiceTest;
    friend class InverseMultipleChoiceTest;
};

#endif // QUIZLITE_UserSession_H
