#include <gtest/gtest.h>
#include "davis_list.h"
TEST(ListTest, DefaultConstructors)
{  
    davis::list<int> lst1;
    EXPECT_TRUE(lst1.empty());
}
TEST(ListTest, FillConstructors)
{
    davis::list<int> lst2(1000000);
    EXPECT_EQ(lst2.size(), 1000000);
    for (davis::list<int>::iterator it = lst2.begin(); it != lst2.end(); it++)
    {
        EXPECT_EQ(*it, 0);
    }
    EXPECT_FALSE(lst2.empty());
}
TEST(ListTest, FillConstructorsVal)
{
    davis::list<int> lst3(1000000, 672323);
    EXPECT_EQ(lst3.size(), 1000000);
    EXPECT_EQ(lst3.front(), 672323);
    EXPECT_EQ(lst3.back(), 672323);
}
TEST(ListTest, RangeConstructors)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::list<int> lst3(arr, arr + 5);
    EXPECT_EQ(lst3.size(), 5);
    int cnt=0;
    for (davis::list<int>::iterator it = lst3.begin(); it != lst3.end(); it++)
    {
        EXPECT_EQ(*it, cnt++);
    }
}
TEST(ListTest, CopyConstructors)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::list<int> lst(arr, arr + 5);
    davis::list<int> lst3(lst);
    EXPECT_EQ(lst3.size(), 5);
    int cnt = 0;
    for (davis::list<int>::iterator it = lst3.begin(); it != lst3.end(); it++)
    {
        EXPECT_EQ(*it, cnt++);
    }
}

TEST(ListTest, Operators)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::list<int> lst(arr, arr + 5);
    davis::list<int> lst3;
    lst3=lst;
    EXPECT_EQ(lst3.size(), 5);
    int cnt = 0;
    for (davis::list<int>::iterator it = lst3.begin(); it != lst3.end(); it++)
    {
        EXPECT_EQ(*it, cnt++);
    }
    davis::list<int> lst4(1000,100);
    lst4 = lst;
    EXPECT_EQ(lst4.size(), 5);
    cnt = 0;
    for (davis::list<int>::iterator it = lst4.begin(); it != lst4.end(); it++)
    {
        EXPECT_EQ(*it, cnt++);
    }

    EXPECT_TRUE(lst4 == lst3);
    EXPECT_FALSE(lst4 != lst3);
    lst3.push_front(12312);
    EXPECT_TRUE(lst4 < lst3);
    EXPECT_TRUE(lst4 <= lst3);
    EXPECT_FALSE(lst4 > lst3);
    EXPECT_FALSE(lst4 >= lst3);

}

TEST(ListTest, Iterators)
{
    //在构造函数部分测试过了
}

TEST(ListTest, Capacity)
{
    davis::list<int> lst;
    EXPECT_EQ(lst.max_size(),size_t(-1));
}

TEST(ListTest, ElementAccess)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::list<int> lst(arr, arr + 5);
    EXPECT_EQ(lst.front(),0);
    EXPECT_EQ(lst.back(),4);
}

TEST(ListTest, Modifiers)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::list<int> lst;
    lst.assign(arr,arr+5);
    int cnt=0;
    for (davis::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        EXPECT_EQ(*it, cnt++);
    }
    davis::list<int> lst2;
    lst2.assign(10, 5);
    for (davis::list<int>::iterator it = lst2.begin(); it != lst2.end(); it++)
    {
        EXPECT_EQ(*it,5);
    }
    lst2.push_back(10);
    EXPECT_EQ(lst2.size(),11);
    EXPECT_EQ(lst2.back(), 10);
    lst2.push_front(10);
    EXPECT_EQ(lst2.size(), 12);
    EXPECT_EQ(lst2.front(), 10);
    lst2.pop_back();
    EXPECT_EQ(lst2.size(), 11);
    EXPECT_EQ(lst2.back(), 5);
    lst2.pop_front();
    EXPECT_EQ(lst2.size(), 10);
    EXPECT_EQ(lst2.front(), 5);
    lst2.insert(lst2.begin(),1000);
    EXPECT_EQ(lst2.front(), 1000);
    lst2.insert(lst2.begin(),5000,1000);
    EXPECT_EQ(lst2.size(), 5011);
    EXPECT_EQ(lst2.front(), 1000);
    lst2.insert(lst2.begin(), lst.begin(),lst.end());
    EXPECT_EQ(lst2.size(), 5016);
    EXPECT_EQ(lst2.front(), 0);

    lst2.erase(lst2.begin(),lst2.end());
    EXPECT_EQ(lst2.size(), 0);
    lst.erase(lst.begin());

    EXPECT_EQ(lst.size(), 4);
    EXPECT_EQ(lst.front(), 1);

    EXPECT_TRUE(lst2.empty());
    EXPECT_FALSE(lst.empty());

    lst2.swap(lst);
    EXPECT_TRUE(lst.empty());
    EXPECT_FALSE(lst2.empty());
    lst2.clear();
    EXPECT_TRUE(lst2.empty());
    lst2.resize(10000);
    EXPECT_EQ(lst2.size(), 10000);
    for (davis::list<int>::iterator it = lst2.begin(); it != lst2.end(); it++)
    {
        EXPECT_EQ(*it, 0);
    }
    lst2.resize(5000);
    EXPECT_EQ(lst2.size(), 5000);
    for (davis::list<int>::iterator it = lst2.begin(); it != lst2.end(); it++)
    {
        EXPECT_EQ(*it, 0);
    }
    lst2.resize(10000,5000);
    cnt=0;
    EXPECT_EQ(lst2.size(), 10000);
    for (davis::list<int>::iterator it = lst2.begin(); it != lst2.end(); it++)
    {
        cnt++;
        if(cnt>5000)
            EXPECT_EQ(*it, 5000);
        else
            EXPECT_EQ(*it, 0);
    }
    lst2.clear();
    EXPECT_TRUE(lst2.empty());
}
TEST(ListTest, Operations)
{
    int arr[10]={0,1,2,3,4,5,6,7,8,9};
    davis::list<int> lst(arr,arr+5);
    davis::list<int> lst2;
    lst2.splice(lst2.begin(),lst);
    EXPECT_TRUE(lst.empty());
    EXPECT_FALSE(lst2.empty());
    EXPECT_EQ(lst2.size(),5);
    davis::list<int> lst3(arr, arr + 1);
    lst2.splice(lst2.begin(), lst3,lst3.begin());
    EXPECT_TRUE(lst3.empty());
    EXPECT_FALSE(lst2.empty());
    EXPECT_EQ(lst2.size(), 6);
    lst2.remove(0);
    EXPECT_EQ(lst2.size(), 4);
    lst2.remove_if([](const int& a){return a<3;});
    EXPECT_EQ(lst2.size(), 2);
    int arr2[5]={1,1,3,3,4};
    davis::list<int> lst4(arr2,arr2+5);
    lst4.unique();
    EXPECT_EQ(lst4.size(), 3);
    int arr3[5] = {0, 1, 3, 3, 6};
    davis::list<int> lst5(arr3, arr3 + 5);
    lst4.merge(lst5);
    EXPECT_EQ(lst4.size(),8);
    EXPECT_EQ(lst4.front(),0);
    EXPECT_EQ(lst4.back(), 6);
    lst4.reverse();
    EXPECT_EQ(lst4.front(), 6);
    EXPECT_EQ(lst4.back(), 0);
    lst4.sort();
    EXPECT_EQ(lst4.front(), 0);
    EXPECT_EQ(lst4.back(), 6);
}
