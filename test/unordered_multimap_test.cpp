#include <gtest/gtest.h>
#include "davis_unordered_multimap.h"
TEST(UnorderedMultiMapTest, Constructor)
{
    davis::unordered_multimap<int, int> first;
    EXPECT_EQ(first.size(), 0);
    EXPECT_TRUE(first.empty());
    first.insert(std::pair<int, int>(10, 10));
    first.insert(std::pair<int, int>(30, 30));
    first.insert(std::pair<int, int>(50, 50));
    first.insert(std::pair<int, int>(70, 70));
    davis::unordered_multimap<int, int> second(first.begin(), first.end());
    EXPECT_EQ(second.size(), 4);
    davis::unordered_multimap<int, int> third(second);
    EXPECT_EQ(second.size(), 4);
}
TEST(UnorderedMultiMapTest, Iterators)
{
    davis::unordered_multimap<int, int> first;
    first.insert(std::pair<int, int>(1, 10));
    first.insert(std::pair<int, int>(3, 30));
    first.insert(std::pair<int, int>(5, 50));
    first.insert(std::pair<int, int>(7, 70));
    EXPECT_FALSE(first.find(1) == first.end());
    EXPECT_FALSE(first.find(3) == first.end());
    EXPECT_FALSE(first.find(5) == first.end());
    EXPECT_FALSE(first.find(7) == first.end());
}
TEST(UnorderedMultiMapTest, Modifiers)
{
    davis::unordered_multimap<int, int> first;
    first.insert(std::pair<int, int>(1, 10));
    first.insert(std::pair<int, int>(3, 30));
    first.insert(std::pair<int, int>(5, 50));
    first.insert(std::pair<int, int>(7, 70));
    EXPECT_FALSE(first.find(1) == first.end());
    EXPECT_FALSE(first.find(3) == first.end());
    EXPECT_FALSE(first.find(5) == first.end());
    EXPECT_FALSE(first.find(7) == first.end());
    first.erase(1);
    first.erase(3);
    EXPECT_FALSE(first.find(1) != first.end());
    EXPECT_FALSE(first.find(3) != first.end());
    EXPECT_FALSE(first.find(5) == first.end());
    EXPECT_FALSE(first.find(7) == first.end());

    davis::unordered_multimap<int, int> second;
    first.swap(second);
    EXPECT_TRUE(first.empty());
    EXPECT_EQ(second.size(), 2);
    EXPECT_FALSE(second.find(1) != second.end());
    EXPECT_FALSE(second.find(3) != second.end());
    EXPECT_FALSE(second.find(5) == second.end());
    EXPECT_FALSE(second.find(7) == second.end());
    second.clear();
    EXPECT_TRUE(second.empty());
    second.insert(std::pair<int, int>(1, 10));
    second.insert(std::pair<int, int>(1, 30));
    second.insert(std::pair<int, int>(1, 50));
    second.insert(std::pair<int, int>(1, 70));
    EXPECT_EQ(second.size(), 4);
    EXPECT_EQ(second.count(1), 4);
    EXPECT_EQ(second.count(3), 0);
    EXPECT_EQ(second.count(5), 0);
    EXPECT_EQ(second.count(7), 0);
    EXPECT_EQ(second.count(-1), 0);
    EXPECT_EQ(second.count(-3), 0);
    EXPECT_EQ(second.count(-5), 0);
    EXPECT_EQ(second.count(-7), 0);
}
