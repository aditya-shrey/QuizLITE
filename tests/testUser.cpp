#include "../User/UserSession.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

class CoutRedirect {
public:
    CoutRedirect(std::streambuf* new_buffer)
        : old(std::cout.rdbuf(new_buffer))
    {
    }
    ~CoutRedirect() { std::cout.rdbuf(old); }

private:
    std::streambuf* old;
};

class UserSessionTest : public ::testing::Test {
protected:
    void SetUp() override
    {
#ifdef TESTING
        UserSession::resetInstance();
        userSession = UserSession::getUserSession();
#endif
    }

    void TearDown() override
    {
#ifdef TESTING
        UserSession::resetInstance();
        unsetenv("TEST_ENV");
#endif
    }

    UserSession* userSession {};
};

TEST_F(UserSessionTest, SingletonTest)
{
    UserSession* userSession1 = UserSession::getUserSession();
    UserSession* userSession2 = UserSession::getUserSession();

    EXPECT_EQ(userSession1, userSession2);
}

TEST_F(UserSessionTest, CreateAndCheckStudySet)
{
    EXPECT_TRUE(userSession->createStudySet("Shortcuts"));
    EXPECT_TRUE(userSession->existsStudySet("Shortcuts"));
}

TEST_F(UserSessionTest, DeleteStudySet)
{
    userSession->createStudySet("SetToDelete");
    EXPECT_TRUE(userSession->deleteStudySet("SetToDelete"));
    EXPECT_FALSE(userSession->existsStudySet("SetToDelete"));
}

TEST_F(UserSessionTest, AddAndDeleteFromStudySet)
{
    userSession->createStudySet("SetForAddDelete");
    EXPECT_TRUE(userSession->addToStudySet("SetForAddDelete", "Key1", "Value1"));
    EXPECT_TRUE(userSession->deleteFromStudySet("SetForAddDelete", "Key1"));
}

TEST_F(UserSessionTest, IsSetNamesTableEmpty)
{
    EXPECT_TRUE(userSession->emptyAllSets());
    EXPECT_TRUE(userSession->isSetNamesTableEmpty());
    userSession->createStudySet("NonEmptySet");
    EXPECT_FALSE(userSession->isSetNamesTableEmpty());
}

TEST_F(UserSessionTest, UpdateScore)
{
    userSession->createStudySet("ScoreSet");
    userSession->addToStudySet("ScoreSet", "Key1", "Value1");
    EXPECT_TRUE(userSession->updateScore("ScoreSet", "Key1", true));
}

TEST_F(UserSessionTest, GetTableKeyValues)
{
    userSession->createStudySet("KeyValueSet");
    userSession->addToStudySet("KeyValueSet", "Key1", "Value1");
    auto keyValues = userSession->getTableKeyValues("KeyValueSet");
    ASSERT_EQ(keyValues.size(), 1);
    EXPECT_EQ(keyValues[0].first, "Key1");
    EXPECT_EQ(keyValues[0].second, "Value1");
}

TEST_F(UserSessionTest, GetLowestAccuracies)
{
    userSession->createStudySet("AccuracySet");
    userSession->addToStudySet("AccuracySet", "Key1", "Value1");
    auto accuracies = userSession->getLowestAccuracies("AccuracySet", 1);
    ASSERT_EQ(accuracies.size(), 1);
    EXPECT_EQ(std::get<0>(accuracies[0]), "Key1");
}

TEST_F(UserSessionTest, GetRandomEntries)
{
    userSession->createStudySet("RandomSet");
    userSession->addToStudySet("RandomSet", "Key1", "Value1");
    auto randomEntries = userSession->getRandomEntries("RandomSet", 1);
    ASSERT_EQ(randomEntries.size(), 1);
    EXPECT_EQ(randomEntries[0].first, "Key1");
}

TEST_F(UserSessionTest, EmptyAllSets)
{
    userSession->createStudySet("SetToEmpty");
    EXPECT_TRUE(userSession->emptyAllSets());
    EXPECT_TRUE(userSession->isSetNamesTableEmpty());
}

TEST_F(UserSessionTest, PrintDatabaseTable)
{
    userSession->createStudySet("PrintSet");
    userSession->addToStudySet("PrintSet", "Key1", "Value1");

    std::ostringstream oss;
    CoutRedirect redirect(oss.rdbuf());
    userSession->printDatabaseTable("PrintSet");

    std::string output = oss.str();
    EXPECT_NE(output.find("Key1"), std::string::npos);
    EXPECT_NE(output.find("Value1"), std::string::npos);
}

TEST_F(UserSessionTest, GetTable)
{
    userSession->createStudySet("TableSet");
    userSession->addToStudySet("TableSet", "Key1", "Value1");
    auto tableData = userSession->getTable("TableSet");
    ASSERT_EQ(tableData.size(), 1);
    EXPECT_EQ(std::get<1>(tableData[0]), "Key1");
    EXPECT_EQ(std::get<2>(tableData[0]), "Value1");
}

TEST_F(UserSessionTest, GetStudySetSize_EmptySet)
{
    userSession->createStudySet("EmptySet");
    int size = userSession->getStudySetSize("EmptySet");
    EXPECT_EQ(size, 0);
}

TEST_F(UserSessionTest, GetStudySetSize_NonEmptySet)
{
    userSession->createStudySet("NonEmptySet");
    userSession->addToStudySet("NonEmptySet", "Key1", "Value1");
    userSession->addToStudySet("NonEmptySet", "Key2", "Value2");

    int size = userSession->getStudySetSize("NonEmptySet");
    EXPECT_EQ(size, 2);
}
