//
// Created by Aditya Shrey on 7/4/24.
//

#ifndef QUIZLITE_STUDYMETHODS_H
#define QUIZLITE_STUDYMETHODS_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

/**
 * @class StudyMethods
 * @brief Abstract base class for study methods.
 */
class StudyMethods {
public:
    /**
     * @brief Get the current question.
     *
     * @return The current question as a string.
     */
    virtual std::string getQuestion() = 0;

    /**
     * @brief Get the answer to the current question.
     * @return The answer to the current question as a string.
     */
    virtual std::string getAnswer() = 0;

    /**
     * @brief Move to the next question.
     *
     * @return True if it updated index else false.
     */
    virtual bool goToNextQuestion() = 0;

    /**
     * @brief Virtual destructor for StudyMethods.
     */
    virtual ~StudyMethods() = default;
};

#endif // QUIZLITE_STUDYMETHODS_H
