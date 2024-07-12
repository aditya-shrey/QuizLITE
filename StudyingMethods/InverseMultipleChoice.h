//
// Created by Aditya Shrey on 7/4/24.
//

#ifndef QUIZLITE_INVERSEMULTIPLECHOICE_H
#define QUIZLITE_INVERSEMULTIPLECHOICE_H

#include "../User/UserSession.h"
#include "StudyMethods.h"
#include <algorithm>
#include <random>
#include <vector>

/**
 * @class InverseMultipleChoice
 * @brief Implementation of StudyMethods for inverse multiple choice questions.
 */
class InverseMultipleChoice : public StudyMethods {
public:
    /**
     * @brief Constructor for InverseMultipleChoice.
     *
     * @param setName Name of the set of questions.
     * @param numLowestAccuracies Number of questions with the lowest accuracies.
     * @param numRandomEntries Number of random entries.
     */
    explicit InverseMultipleChoice(const std::string& setName, int numLowestAccuracies, int numRandomEntries);

    /**
     * @brief Get the current question.
     *
     * @return The current question as a string.
     */
    std::string getQuestion() override;

    /**
     * @brief Get the answer to the current question.
     *
     * @return The answer to the current question as a string.
     */
    std::string getAnswer() override;

    /**
     * @brief Move to the next question.
     *
     * @return True if it updated index else false.
     */
    bool goToNextQuestion() override;

    /**
     * @brief Generate options for the current question.
     *
     * @return A tuple containing four options.
     */
    std::tuple<std::string, std::string, std::string, std::string> generateOptions();

    /**
     * @brief Update the scores in the table based on whether the answer was correct.
     *
     * @param isCorrect Boolean indicating if the answer was correct.
     */
    void updateScoresInTable(bool isCorrect);

private:
    /**
     * @brief Stores the flashcards as pairs of questions and answers.
     */
    std::vector<std::pair<std::string, std::string>> keyValues;

    /**
     * @brief The current index of the flashcard being displayed.
     */
    uint32_t currentIndex;

    /**
     * @brief The name of the flashcard set.
     */
    std::string setName;

    friend class TestableInverseMultipleChoice;
};

#endif // QUIZLITE_INVERSEMULTIPLECHOICE_H
