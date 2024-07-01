#include "../User/UserSessionInfo.h"
#include <gtest/gtest.h>

class UserSessionInfoTest : public ::testing::Test {
protected:
    void SetUp() override
    {
#ifdef TESTING
        UserSessionInfo::resetInstance();
        userSessionInfo = UserSessionInfo::getUserSessionInfo();
#endif
    }

    void TearDown() override
    {
#ifdef TESTING
        UserSessionInfo::resetInstance();
        unsetenv("TEST_ENV");
#endif
    }

    UserSessionInfo* userSessionInfo {};
};

TEST_F(UserSessionInfoTest, SingletonInstance)
{
    UserSessionInfo* userSessionInfo1 = UserSessionInfo::getUserSessionInfo();
    UserSessionInfo* userSessionInfo2 = UserSessionInfo::getUserSessionInfo();
    EXPECT_EQ(userSessionInfo1, userSessionInfo2);
}

TEST_F(UserSessionInfoTest, SetAndGetStudySet)
{
    userSessionInfo->setStudySet("TestSet");
    EXPECT_EQ(userSessionInfo->getStudySet(), "TestSet");
}

TEST_F(UserSessionInfoTest, SetAndGetSessionType)
{
    userSessionInfo->setSessionType(1);
    EXPECT_EQ(userSessionInfo->getSessionType(), 1);
}

TEST_F(UserSessionInfoTest, SetValues)
{
    userSessionInfo->setValues("TestSet", 2);
    EXPECT_EQ(userSessionInfo->getStudySet(), "TestSet");
    EXPECT_EQ(userSessionInfo->getSessionType(), 2);
}

TEST_F(UserSessionInfoTest, CreateAndCheckStudySet)
{
    EXPECT_TRUE(userSessionInfo->createStudySet("NewSet"));
    EXPECT_TRUE(userSessionInfo->existsStudySet("NewSet"));
}

TEST_F(UserSessionInfoTest, DeleteStudySet)
{
    userSessionInfo->createStudySet("SetToDelete");
    EXPECT_TRUE(userSessionInfo->deleteStudySet("SetToDelete"));
    EXPECT_FALSE(userSessionInfo->existsStudySet("SetToDelete"));
}

TEST_F(UserSessionInfoTest, AddAndDeleteFromStudySet)
{
    userSessionInfo->createStudySet("SetForAddDelete");
    EXPECT_TRUE(userSessionInfo->addToStudySet("SetForAddDelete", "Key1", "Value1"));
    EXPECT_TRUE(userSessionInfo->deleteFromStudySet("SetForAddDelete", "Key1"));
}

TEST_F(UserSessionInfoTest, IsSetNamesTableEmpty)
{
    EXPECT_TRUE(userSessionInfo->emptyAllSets());
    EXPECT_TRUE(userSessionInfo->isSetNamesTableEmpty());
    userSessionInfo->createStudySet("NonEmptySet");
    EXPECT_FALSE(userSessionInfo->isSetNamesTableEmpty());
}

TEST_F(UserSessionInfoTest, UpdateScore)
{
    userSessionInfo->createStudySet("ScoreSet");
    userSessionInfo->addToStudySet("ScoreSet", "Key1", "Value1");
    EXPECT_TRUE(userSessionInfo->updateScore("ScoreSet", "Key1", true));
}

TEST_F(UserSessionInfoTest, GetTableKeyValues)
{
    userSessionInfo->createStudySet("KeyValueSet");
    userSessionInfo->addToStudySet("KeyValueSet", "Key1", "Value1");
    auto keyValues = userSessionInfo->getTableKeyValues("KeyValueSet");
    ASSERT_EQ(keyValues.size(), 1);
    EXPECT_EQ(keyValues[0].first, "Key1");
    EXPECT_EQ(keyValues[0].second, "Value1");
}

TEST_F(UserSessionInfoTest, GetLowestAccuracies)
{
    userSessionInfo->createStudySet("AccuracySet");
    userSessionInfo->addToStudySet("AccuracySet", "Key1", "Value1");
    auto accuracies = userSessionInfo->getLowestAccuracies("AccuracySet", 1);
    ASSERT_EQ(accuracies.size(), 1);
    EXPECT_EQ(std::get<0>(accuracies[0]), "Key1");
}

TEST_F(UserSessionInfoTest, GetRandomEntries)
{
    userSessionInfo->createStudySet("RandomSet");
    userSessionInfo->addToStudySet("RandomSet", "Key1", "Value1");
    auto randomEntries = userSessionInfo->getRandomEntries("RandomSet", 1);
    ASSERT_EQ(randomEntries.size(), 1);
    EXPECT_EQ(randomEntries[0].first, "Key1");
}

TEST_F(UserSessionInfoTest, EmptyAllSets)
{
    userSessionInfo->createStudySet("SetToEmpty");
    EXPECT_TRUE(userSessionInfo->emptyAllSets());
    EXPECT_TRUE(userSessionInfo->isSetNamesTableEmpty());
}

/**
 * Tests remaining
 *
 *
 */