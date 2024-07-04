//
// Created by Aditya Shrey on 7/4/24.
//

#ifndef QUIZLITE_MULTIPLECHOICE_H
#define QUIZLITE_MULTIPLECHOICE_H

#include "../User/UserSessionInfo.h"
#include "StudyMethods.h"
#include <algorithm>
#include <random>
#include <vector>

class MultipleChoice : public StudyMethods {
private:
    std::vector<std::pair<std::string, std::string>> keyValues;
    size_t currentIndex;
    std::string setName;
    std::vector<std::pair<std::string, std::string>> options;

public:
    MultipleChoice(const std::string& setName);
    void startStudying() override;
    void endStudying() override;
    void displayQuestion() override;
    std::string revealAnswer() override;
    void goToNextQuestion() override;
    void updateScoresInTable(bool isCorrect);
    void generateOptions();
};

#endif // QUIZLITE_MULTIPLECHOICE_H
