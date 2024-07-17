#include "../Database/DatabaseManager.h"
#include <gtest/gtest.h>

class DatabaseManagerTest : public ::testing::Test {
protected:
  void SetUp() override {
#ifdef TESTING
    DatabaseManager::resetInstance();
    dbManager = DatabaseManager::getDatabaseManager(":memory:");
    dbManager->openDatabase();
#endif
  }
  void TearDown() override {
#ifdef TESTING
    dbManager->closeDatabase();
    DatabaseManager::resetInstance();
    unsetenv("TEST_ENV");
#endif
  }

  DatabaseManager *dbManager{};
};

TEST_F(DatabaseManagerTest, SingletonInstance) {
  DatabaseManager *dbManager1 = DatabaseManager::getDatabaseManager(":memory:");
  DatabaseManager *dbManager2 = DatabaseManager::getDatabaseManager(":memory:");
  EXPECT_EQ(dbManager1, dbManager2);
}

TEST_F(DatabaseManagerTest, OpenDatabase) {
  EXPECT_TRUE(dbManager->openDatabase());
}

TEST_F(DatabaseManagerTest, CloseDatabase) {
  dbManager->closeDatabase();
  dbManager->closeDatabase(); // This is just for testing multiple close calls
}

TEST_F(DatabaseManagerTest, ExecuteQuery) {
  EXPECT_EQ(dbManager->executeQuery("CREATE TABLE test (name TEXT);"),
            SQLITE_OK);
  EXPECT_EQ(
      dbManager->executeQuery("INSERT INTO test (name) VALUES ('Alice');"),
      SQLITE_OK);
  EXPECT_EQ(dbManager->executeQuery("INSERT INTO test (name) VALUES ('Bob');"),
            SQLITE_OK);
}

TEST_F(DatabaseManagerTest, ExecuteQueryWithResults) {
  dbManager->executeQuery("CREATE TABLE test (name TEXT);");
  dbManager->executeQuery("INSERT INTO test (name) VALUES ('Alice');");
  dbManager->executeQuery("INSERT INTO test (name) VALUES ('Bob');");

  std::vector<std::map<std::string, std::string>> results =
      dbManager->executeQueryWithResults("SELECT * FROM test;");
  ASSERT_EQ(results.size(), 2);
  EXPECT_EQ(results[0]["name"], "Alice");
  EXPECT_EQ(results[1]["name"], "Bob");
}

TEST_F(DatabaseManagerTest, IsTableEmpty) {
  dbManager->executeQuery("CREATE TABLE test (name TEXT);");
  EXPECT_TRUE(dbManager->isTableEmpty("test"));

  dbManager->executeQuery("INSERT INTO test (name) VALUES ('Alice');");
  EXPECT_FALSE(dbManager->isTableEmpty("test"));
}
