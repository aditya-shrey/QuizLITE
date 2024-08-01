#include <gtest/gtest.h>
#include "../StudyingMethods/MultipleChoice.h"
#include <string>
#include <algorithm>

class MultipleChoiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        UserSession::resetInstance();
        userSession = UserSession::getUserSession();
        userSession->createStudySet("TestSet");
        userSession->addToStudySet("TestSet", "Question1", "Answer1");
        userSession->addToStudySet("TestSet", "Question2", "Answer2");
        userSession->addToStudySet("TestSet", "Question3", "Answer3");
        userSession->addToStudySet("TestSet", "Question4", "Answer4");
    }

    void TearDown() override {
        UserSession::resetInstance();
    }

    UserSession* userSession;
};

TEST_F(MultipleChoiceTest, InitializationWithFewEntries) {
    MultipleChoice mc("TestSet", 4, 0);
    std::string getQuestion = mc.getQuestion();
    std::set<std::string> expectedQuestions = {"Question1", "Question2", "Question3", "Question4"};
    EXPECT_TRUE(expectedQuestions.find(getQuestion) != expectedQuestions.end());

    if (getQuestion == "Question1") {
        EXPECT_EQ(mc.getAnswer(), "Answer1");
    } else if (getQuestion == "Question2") {
        EXPECT_EQ(mc.getAnswer(), "Answer2");
    } else if (getQuestion == "Question3") {
        EXPECT_EQ(mc.getAnswer(), "Answer3");
    } else if (getQuestion == "Question4") {
        EXPECT_EQ(mc.getAnswer(), "Answer4");
    } else {
        FAIL() << "Unexpected question";
    }
}

TEST_F(MultipleChoiceTest, GoToNextQuestionBoundary) {
    MultipleChoice mc("TestSet", 2, 2);
    for (int i = 0; i < 3; ++i) {
        mc.goToNextQuestion();
    }
    EXPECT_FALSE(mc.goToNextQuestion());
}

TEST_F(MultipleChoiceTest, GenerateOptionsForSmallSet) {
    MultipleChoice mc("TestSet", 2, 1);
    auto options = mc.generateOptions();
    std::unordered_set<std::string> uniqueOptions{std::get<0>(options), std::get<1>(options), std::get<2>(options), std::get<3>(options)};
    EXPECT_EQ(uniqueOptions.size(), 4);
}

TEST_F(MultipleChoiceTest, GenerateOptionsForLargeSet) {
    // Add six new questions
    for (int i = 5; i <= 10; ++i) {
        userSession->addToStudySet("TestSet", "Question" + std::to_string(i), "Answer" + std::to_string(i));
    }

    MultipleChoice mc("TestSet", 2, 2);
    auto options = mc.generateOptions();
    std::unordered_set<std::string> uniqueOptions{std::get<0>(options), std::get<1>(options), std::get<2>(options), std::get<3>(options)};
    EXPECT_EQ(uniqueOptions.size(), 4);

    // Delete the newly added questions
    for (int i = 5; i <= 10; ++i) {
        userSession->deleteFromStudySet("TestSet", "Question" + std::to_string(i));
    }

    // Verify that the questions have been removed
    auto table = userSession->getTable("TestSet");
    userSession->printDatabaseTable("TestSet");

    for (const auto& row : table) {
        std::string question = std::get<1>(row);
        EXPECT_TRUE(question != "Question5" && question != "Question6" &&
                    question != "Question7" && question != "Question8" &&
                    question != "Question9" && question != "Question10");
    }
}



TEST_F(MultipleChoiceTest, UpdateScoresInTableCorrect) {
    MultipleChoice mc("TestSet", 4, 0);
    for (int i = 0; i < 4; ++i) {
        mc.updateScoresInTable(true);
        mc.goToNextQuestion();
    }
    auto table = userSession->getTable("TestSet");
    for (const auto& row : table) {
        EXPECT_EQ(std::get<3>(row), 1);
        EXPECT_EQ(std::get<4>(row), 1);
    }
}

TEST_F(MultipleChoiceTest, GetQuestionOutOfBounds) {
    MultipleChoice mc("TestSet", 2, 0);
    for (int i = 0; i < 2; ++i) {
        mc.goToNextQuestion();
    }
    EXPECT_NE(mc.getQuestion(), "");
}

TEST_F(MultipleChoiceTest, GetAnswerOutOfBounds) {
    MultipleChoice mc("TestSet", 2, 0);
    for (int i = 0; i < 2; ++i) {
        mc.goToNextQuestion();
    }
    EXPECT_NE(mc.getAnswer(), "");

    userSession->deleteStudySet("TestSet");
}
