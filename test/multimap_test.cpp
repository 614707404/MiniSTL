#include <gtest/gtest.h>
#include "davis_multimap.h"
bool mfncomp(char lhs,char rhs){return lhs<rhs;};
struct mclasscomp{
    bool operator()(const char& lhs,const char& rhs) const
    {
        return lhs<rhs;
    }
};
TEST(MultiMaptest,Constructor){
    davis::multimap<char, int> first;
    EXPECT_EQ(first.size(), 0);
    EXPECT_TRUE(first.empty());
    first.insert(std::make_pair('a', 10));
    first.insert(std::make_pair('b', 30));
    first.insert(std::make_pair('c', 50));
    first.insert(std::make_pair('d', 70));
    EXPECT_EQ(first.size(), 4);
    EXPECT_FALSE(first.empty());
    davis::multimap<char,int> second(first.begin(),first.end());
    EXPECT_EQ(second.size(), 4);
    EXPECT_EQ((*second.begin()).second, 10);
    davis::multimap<char, int> third(second);
    davis::multimap<char, int, mclasscomp> fourth;
    bool (*fnptr)(char,char)=mfncomp;
    davis::multimap<char,int,bool(*)(char,char)> fifth(fnptr);
    davis::multimap<char, int> sixth;
    sixth=first;
    EXPECT_EQ(sixth.size(), 4);
    EXPECT_FALSE(sixth.empty());
}
TEST(MultiMaptest, Iterators)
{
    davis::multimap<char, int> first;
    first.insert(std::make_pair('a', 1));
    first.insert(std::make_pair('b', 2));
    first.insert(std::make_pair('c', 3));
    first.insert(std::make_pair('d', 4));

    auto it=first.begin();
    int cnt=0;
    while(it!=first.end()){
        EXPECT_EQ((*it++).second,++cnt);
    }
}
TEST(MultiMaptest, Modifiers)
{
    davis::multimap<char, int> first;
    first.insert(std::make_pair('a', 0));
    first.insert(std::make_pair('b', 1));
    first.insert(std::make_pair('c', 2));
    first.insert(std::make_pair('d', 3));

    std::pair<char,int> f('f',5);
    first.insert(f);
    std::pair<char, int> e('e', 4);
    first.insert(e);
    auto it = first.begin();
    int cnt = 0;
    while (it != first.end())
    {
        EXPECT_EQ((*it++).second, cnt++);
    }
    EXPECT_EQ(cnt,first.size());
    first.erase('a');
    first.erase('c');
    first.erase('f');
    EXPECT_EQ((*first.begin()).second, 1);
    EXPECT_EQ((*--first.end()).second, 4);
    davis::multimap<char,int> second;
    first.swap(second);
    EXPECT_EQ((*second.begin()).second, 1);
    EXPECT_EQ((*--second.end()).second, 4);
    EXPECT_TRUE(first.empty());
    second.clear();
    EXPECT_TRUE(second.empty());
    second.insert(std::make_pair('a', 0));
    second.insert(std::make_pair('a', 1));
    second.insert(std::make_pair('a', 2));
    second.insert(std::make_pair('a', 3));
    EXPECT_EQ(second.size(), 4);
}
TEST(MultiMaptest, Operations)
{
    davis::multimap<char, int> first;
    first.insert(std::make_pair('c', 0));
    first.insert(std::make_pair('d', 1));
    first.insert(std::make_pair('e', 2));
    first.insert(std::make_pair('f', 3));
    EXPECT_EQ(first.find('z'), first.end());
    EXPECT_EQ(first.find('c'), first.begin());
    EXPECT_EQ(first.count('z'), 0);
    EXPECT_EQ(first.count('c'), 1);
    EXPECT_EQ(first.lower_bound('a'), first.begin());
    EXPECT_EQ(first.lower_bound('c'), first.begin());
    EXPECT_EQ(first.lower_bound('z'), first.end());
    EXPECT_EQ(first.upper_bound('a'), first.begin());
    EXPECT_EQ(first.lower_bound('z'), first.end());
    EXPECT_EQ(first.equal_range('c').first, first.begin());
    EXPECT_EQ(first.equal_range('c').second, ++first.begin());
    EXPECT_EQ(first.equal_range('z').first, first.end());
    EXPECT_EQ(first.equal_range('z').second, first.end());
}