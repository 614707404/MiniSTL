#include <gtest/gtest.h>
#include "davis_multiset.h"
bool msetfncomp(int lhs, int rhs) { return lhs < rhs; };
struct msetclasscomp
{
    bool operator()(const int &lhs, const int &rhs) const
    {
        return lhs < rhs;
    }
};
TEST(MultiSetTest, Constructor)
{
    davis::multiset<int> first;
    EXPECT_EQ(first.size(), 0);
    EXPECT_TRUE(first.empty());
    first.insert(10);
    first.insert(30);
    first.insert(50);
    first.insert(70);
    EXPECT_EQ(first.size(), 4);
    EXPECT_FALSE(first.empty());
    davis::multiset<int> second(first.begin(), first.end());
    EXPECT_EQ(second.size(), 4);
    EXPECT_EQ(*second.begin(), 10);
    davis::multiset<int> third(second);
    davis::multiset<int, msetclasscomp> fourth;
    bool (*fnptr)(int, int) = msetfncomp;
    davis::multiset<int, bool (*)(int, int)> fifth(fnptr);
    davis::multiset<int> sixth;
    sixth = first;
    EXPECT_EQ(sixth.size(), 4);
    EXPECT_FALSE(sixth.empty());
}
TEST(MultiSetTest, Iterators)
{
    davis::multiset<int> first;
    first.insert(1);
    first.insert(2);
    first.insert(3);
    first.insert(4);

    auto it = first.begin();
    int cnt = 0;
    while (it != first.end())
    {
        EXPECT_EQ(*it++, ++cnt);
    }
}
TEST(MultiSetTest, Modifiers)
{
    davis::multiset<int> first;
    first.insert(0);
    first.insert(1);
    first.insert(2);
    first.insert(3);
    first.insert(5);
    first.insert(4);
    auto it = first.begin();
    int cnt = 0;
    while (it != first.end())
    {
        EXPECT_EQ(*it++, cnt++);
    }
    EXPECT_EQ(cnt, first.size());
    first.erase(0);
    first.erase(2);
    first.erase(5);
    EXPECT_EQ(*first.begin(), 1);
    EXPECT_EQ(*--first.end(), 4);
    davis::multiset<int> second;
    first.swap(second);
    EXPECT_EQ(*second.begin(), 1);
    EXPECT_EQ(*--second.end(), 4);
    EXPECT_TRUE(first.empty());
    second.clear();
    EXPECT_TRUE(second.empty());
    second.insert(0);
    second.insert(0);
    second.insert(0);
    second.insert(0);
    EXPECT_EQ(second.size(), 4);
}
TEST(MultiSetTest, Operations)
{
    davis::multiset<int> first;
    first.insert(0);
    first.insert(1);
    first.insert(2);
    first.insert(3);
    EXPECT_EQ(first.find(25), first.end());
    EXPECT_EQ(first.find(0), first.begin());
    EXPECT_EQ(first.count(25), 0);
    EXPECT_EQ(first.count(2), 1);
    EXPECT_EQ(first.lower_bound(0), first.begin());
    EXPECT_EQ(first.lower_bound(0), first.begin());
    EXPECT_EQ(first.lower_bound(25), first.end());
    EXPECT_EQ(first.upper_bound(0), ++first.begin());
    EXPECT_EQ(first.lower_bound(25), first.end());
    EXPECT_EQ(first.equal_range(0).first, first.begin());
    EXPECT_EQ(first.equal_range(0).second, ++first.begin());
    EXPECT_EQ(first.equal_range(25).first, first.end());
    EXPECT_EQ(first.equal_range(25).second, first.end());
}