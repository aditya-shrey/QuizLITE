//
// Created by Aditya Shrey on 7/4/24.
//

#ifndef QUIZLITE_FLASHCARDS_H
#define QUIZLITE_FLASHCARDS_H

#include "../User/UserSession.h"
#include "StudyMethods.h"

/**
 * @class Flashcards
 * @brief A class to manage flashcard-based study methods.
 *
 * This class provides functionality to study using flashcards,
 * which involves displaying questions, revealing answers, and
 * navigating through a set of flashcards.
 */
class Flashcards : public StudyMethods {
public:
    /**
     * @brief Constructs a new Flashcards object.
     *
     * @param setName The name of the flashcard set.
     */
    explicit Flashcards(const std::string& setName);

    /**
     * @brief Retrieves the current question.
     *
     * This method overrides the getQuestion method from the
     * StudyMethods class to display the answer to the current question.
     *
     * @return std::string The current question as a string.
     */
    std::string getQuestion() override;

    /**
     * @brief Reveals the answer to the current question.
     *
     * This method overrides the getAnswer method from the
     * StudyMethods class to display the answer to the current question.
     *
     * @return std::string The answer to the current question as a string.
     */
    std::string getAnswer() override;

    /**
     * @brief Moves to the next question in the flashcard set.
     *
     * This method overrides the goToNextQuestion method from the
     * StudyMethods class to proceed to the next question.
     *
     * @return True if it updated index else false.
     */
    bool goToNextQuestion() override;

    /**
     * @brief Moves to the previous question in the flashcard set.
     *
     * @return True if it updated index else false.
     */
    bool goToPrevQuestion();

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
};

#endif // QUIZLITE_FLASHCARDS_H
