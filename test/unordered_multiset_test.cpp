#include <gtest/gtest.h>
#include "davis_unordered_multiset.h"
TEST(UnorderedMultiSetTest, Constructor)
{
    davis::unordered_multiset<int> first;
    EXPECT_EQ(first.size(), 0);
    EXPECT_TRUE(first.empty());
    first.insert(10);
    first.insert(30);
    first.insert(50);
    first.insert(70);
    davis::unordered_multiset<int> second(first.begin(), first.end());
    EXPECT_EQ(second.size(), 4);
    davis::unordered_multiset<int> third(second);
    EXPECT_EQ(second.size(), 4);
}
TEST(UnorderedMultiSetTest, Iterators)
{
    davis::unordered_multiset<int> first;
    first.insert(1);
    first.insert(2);
    first.insert(3);
    first.insert(4);
    EXPECT_FALSE(first.find(1) == first.end());
    EXPECT_FALSE(first.find(2) == first.end());
    EXPECT_FALSE(first.find(3) == first.end());
    EXPECT_FALSE(first.find(4) == first.end());
}
TEST(UnorderedMultiSetTest, Modifiers)
{
    davis::unordered_multiset<int> first;
    first.insert(0);
    first.insert(1);
    first.insert(2);
    first.insert(3);
    first.insert(5);
    first.insert(4);
    EXPECT_FALSE(first.find(0) == first.end());
    EXPECT_FALSE(first.find(1) == first.end());
    EXPECT_FALSE(first.find(2) == first.end());
    EXPECT_FALSE(first.find(3) == first.end());
    EXPECT_FALSE(first.find(4) == first.end());
    EXPECT_FALSE(first.find(5) == first.end());
    first.erase(0);
    first.erase(2);
    first.erase(5);
    EXPECT_FALSE(first.find(0) != first.end());
    EXPECT_FALSE(first.find(1) == first.end());
    EXPECT_FALSE(first.find(2) != first.end());
    EXPECT_FALSE(first.find(3) == first.end());
    EXPECT_FALSE(first.find(4) == first.end());
    EXPECT_FALSE(first.find(5) != first.end());

    davis::unordered_multiset<int> second;
    first.swap(second);
    EXPECT_TRUE(first.empty());
    EXPECT_EQ(second.size(), 3);
    EXPECT_FALSE(second.find(0) != second.end());
    EXPECT_FALSE(second.find(1) == second.end());
    EXPECT_FALSE(second.find(2) != second.end());
    EXPECT_FALSE(second.find(3) == second.end());
    EXPECT_FALSE(second.find(4) == second.end());
    EXPECT_FALSE(second.find(5) != second.end());
    second.clear();
    EXPECT_TRUE(second.empty());
    second.insert(0);
    second.insert(0);
    second.insert(1);
    second.insert(1);
    EXPECT_EQ(second.size(), 4);
    EXPECT_EQ(second.count(0), 2);
    EXPECT_EQ(second.count(1), 2);
    EXPECT_EQ(second.count(2), 0);
    EXPECT_EQ(second.count(3), 0);
    EXPECT_EQ(second.count(4), 0);
    EXPECT_EQ(second.count(5), 0);
}
