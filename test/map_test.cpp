#include <gtest/gtest.h>
#include "davis_map.h"
bool fncomp(char lhs,char rhs){return lhs<rhs;};
struct classcomp{
    bool operator()(const char& lhs,const char& rhs) const
    {
        return lhs<rhs;
    }
};
TEST(Maptest,Constructor){
    davis::map<char, int> first;
    EXPECT_EQ(first.size(), 0);
    EXPECT_TRUE(first.empty());
    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;
    EXPECT_EQ(first.size(), 4);
    EXPECT_FALSE(first.empty());
    davis::map<char,int> second(first.begin(),first.end());
    EXPECT_EQ(second.size(), 4);
    EXPECT_EQ((*second.begin()).second, 10);
    davis::map<char, int> third(second);
    davis::map<char, int, classcomp> fourth;
    bool (*fnptr)(char,char)=fncomp;
    davis::map<char,int,bool(*)(char,char)> fifth(fnptr);
    davis::map<char, int> sixth;
    sixth=first;
    EXPECT_EQ(sixth.size(), 4);
    EXPECT_FALSE(sixth.empty());
}
TEST(Maptest, Iterators)
{
    davis::map<char, int> first;
    first['a'] = 1;
    first['b'] = 2;
    first['c'] = 3;
    first['d'] = 4;
    auto it=first.begin();
    int cnt=0;
    while(it!=first.end()){
        EXPECT_EQ((*it++).second,++cnt);
    }
}
TEST(Maptest, Modifiers)
{
    davis::map<char, int> first;
    first['a'] = 0;
    first['b'] = 1;
    first['c'] = 2;
    first['d'] = 3;

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
    davis::map<char,int> second;
    first.swap(second);
    EXPECT_EQ((*second.begin()).second, 1);
    EXPECT_EQ((*--second.end()).second, 4);
    EXPECT_TRUE(first.empty());
    second.clear();
    EXPECT_TRUE(second.empty());
}
TEST(Maptest, Operations)
{
    davis::map<char, int> first;
    first['c'] = 0;
    first['d'] = 1;
    first['e'] = 2;
    first['f'] = 3;
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