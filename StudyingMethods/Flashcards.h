//
// Created by Aditya Shrey on 7/4/24.
//

#ifndef QUIZLITE_FLASHCARDS_H
#define QUIZLITE_FLASHCARDS_H

#include "StudyMethods.h"
#include "../User/UserSessionInfo.h"

class Flashcards : public StudyMethods {
private:
    std::vector<std::pair<std::string, std::string>> keyValues;
    size_t currentIndex;
    std::string setName;

public:
    Flashcards(const std::string& setName);
    void startStudying() override;
    void endStudying() override;
    void displayQuestion() override;
    std::string revealAnswer() override;
    void goToNextQuestion() override;
};

#endif //QUIZLITE_FLASHCARDS_H
