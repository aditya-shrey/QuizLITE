#include <gtest/gtest.h>
#include "../User/UserSessionInfo.h"
#include <iostream>
#include <sstream>

// Helper function to capture output and verify table contents
std::string captureTableOutput(const std::string& tableName) {
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    UserSessionInfo::getUserSessionInfo()->printDatabaseTable(tableName);

    std::cout.rdbuf(p_cout_streambuf);
    return oss.str();
}

// Test fixture for UserSessionInfo
class UserSessionInfoTest : public ::testing::Test {
protected:
    void SetUp() override {
        session = UserSessionInfo::getUserSessionInfo();
        ASSERT_EQ(session->isSetNamesTableEmpty(), true);
    }

    void TearDown() override {
        delete session;
        session = nullptr;
    }

    UserSessionInfo* session;
};

TEST_F(UserSessionInfoTest, TestSetStudySet) {
    session->setStudySet("TestSet");
    ASSERT_EQ(session->getStudySet(), "TestSet");
}

TEST_F(UserSessionInfoTest, TestSetSessionType) {
    session->setSessionType(2);
    ASSERT_EQ(session->getSessionType(), 2);
}

TEST_F(UserSessionInfoTest, TestSetValues) {
    session->setValues("TestSet", 3);
    ASSERT_EQ(session->getStudySet(), "TestSet");
    ASSERT_EQ(session->getSessionType(), 3);
}

TEST_F(UserSessionInfoTest, TestCreateStudySet) {
    bool success = session->createStudySet("TestSet");
    ASSERT_TRUE(success);
    std::string output = captureTableOutput("set_names");
    ASSERT_NE(output.find("TestSet"), std::string::npos);
}

TEST_F(UserSessionInfoTest, TestExistsStudySet) {
    session->createStudySet("TestSet");
    bool exists = session->existsStudySet("TestSet");
    ASSERT_TRUE(exists);
}

TEST_F(UserSessionInfoTest, TestDeleteStudySet) {
    session->createStudySet("TestSet");
    bool success = session->deleteStudySet("TestSet");
    ASSERT_TRUE(success);
    bool exists = session->existsStudySet("TestSet");
    ASSERT_FALSE(exists);
}

TEST_F(UserSessionInfoTest, TestAddToStudySet) {
    session->createStudySet("TestSet");
    bool success = session->addToStudySet("TestSet", "Key1", "Value1");
    ASSERT_TRUE(success);
    std::string output = captureTableOutput("TestSet");
    ASSERT_NE(output.find("Key1"), std::string::npos);
    ASSERT_NE(output.find("Value1"), std::string::npos);
}

TEST_F(UserSessionInfoTest, TestDeleteFromStudySet) {
    session->createStudySet("TestSet");
    session->addToStudySet("TestSet", "Key1", "Value1");
    bool success = session->deleteFromStudySet("TestSet", "Key1");
    ASSERT_TRUE(success);
    std::string output = captureTableOutput("TestSet");
    ASSERT_EQ(output.find("Key1"), std::string::npos);
}

TEST_F(UserSessionInfoTest, TestIsSetNamesTableEmpty) {
    session->createStudySet("TestSet");
    ASSERT_FALSE(session->isSetNamesTableEmpty());
    session->deleteStudySet("TestSet");
    ASSERT_TRUE(session->isSetNamesTableEmpty());
}

TEST_F(UserSessionInfoTest, TestUpdateScore) {
    session->createStudySet("TestSet");
    session->addToStudySet("TestSet", "Key1", "Value1");
    bool success = session->updateScore("TestSet", "Key1", true);
    ASSERT_TRUE(success);
    std::string output = captureTableOutput("TestSet");
    ASSERT_NE(output.find("1"), std::string::npos);
}

TEST_F(UserSessionInfoTest, TestGetTableKeyValues) {
    session->createStudySet("TestSet");
    session->addToStudySet("TestSet", "Key1", "Value1");
    auto keyValues = session->getTableKeyValues("TestSet");
    ASSERT_EQ(keyValues.size(), 1);
    ASSERT_EQ(keyValues[0].first, "Key1");
    ASSERT_EQ(keyValues[0].second, "Value1");
}

TEST_F(UserSessionInfoTest, TestGetLowestAccuracies) {
    session->createStudySet("TestSet");
    session->addToStudySet("TestSet", "Key1", "Value1");
    session->updateScore("TestSet", "Key1", false);
    auto accuracies = session->getLowestAccuracies("TestSet", 1);
    ASSERT_EQ(accuracies.size(), 1);
    ASSERT_EQ(std::get<0>(accuracies[0]), "Key1");
}

TEST_F(UserSessionInfoTest, TestGetRandomEntries) {
    session->createStudySet("TestSet");
    session->addToStudySet("TestSet", "Key1", "Value1");
    session->addToStudySet("TestSet", "Key2", "Value2");
    auto randomEntries = session->getRandomEntries("TestSet", 2);
    ASSERT_EQ(randomEntries.size(), 2);
}
