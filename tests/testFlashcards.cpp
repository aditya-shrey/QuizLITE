#include "../StudyingMethods/Flashcards.h"
#include "../User/UserSessionInfo.h"
#include <gtest/gtest.h>

class FlashcardsTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        auto userSession = UserSessionInfo::getUserSessionInfo();
        userSession->createStudySet("Math");
        userSession->addToStudySet("Math", "2+2", "4");
        userSession->addToStudySet("Math", "3*3", "9");
        userSession->addToStudySet("Math", "sqrt(16)", "4");
    }
};

TEST_F(FlashcardsTest, TestGetQuestionAndAnswer)
{
    Flashcards flashcards("Math");
    ASSERT_EQ(flashcards.getQuestion(), "2+2");
    ASSERT_EQ(flashcards.getAnswer(), "4");
    flashcards.goToNextQuestion();
    ASSERT_EQ(flashcards.getQuestion(), "3*3");
    ASSERT_EQ(flashcards.getAnswer(), "9");
}

TEST_F(FlashcardsTest, TestGoToNextQuestion)
{
    Flashcards flashcards("Math");
    flashcards.goToNextQuestion();
    flashcards.goToNextQuestion();
    ASSERT_EQ(flashcards.getQuestion(), "sqrt(16)");
    ASSERT_EQ(flashcards.getAnswer(), "4");
}
