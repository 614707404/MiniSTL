#include <gtest/gtest.h>
#include "davis_deque.h"
int arr[10]={0,1,2,3,4,5,6,7,8,9};
TEST(DequeTest, Constructors)
{
    davis::deque<int> deq1;
    EXPECT_EQ(deq1.size(),0);
    EXPECT_TRUE(deq1.empty());

    davis::deque<int> deq2(100);
    EXPECT_EQ(deq2.size(), 100);
    EXPECT_EQ(deq2[99],0);

    davis::deque<int> deq3(101,667);
    EXPECT_EQ(deq3.size(), 101);
    EXPECT_EQ(deq3[100], 667);

    davis::deque<int> deq4(arr,arr+7);
    EXPECT_EQ(deq4.size(), 7);
    EXPECT_EQ(deq4[6], 6);

    davis::deque<int> deq5(deq4);
    EXPECT_EQ(deq5.size(), 7);
    EXPECT_EQ(deq5[6], 6);
}

TEST(DequeTest, Operators)
{
    davis::deque<int> deq1(arr, arr + 7);
    davis::deque<int> deq2;
    deq2=deq1;
    EXPECT_EQ(deq2.size(), 7);
    EXPECT_EQ(deq2[6], 6);

    EXPECT_TRUE(deq2==deq1);
    deq2[0]++;
    EXPECT_TRUE(deq2 > deq1);
    EXPECT_FALSE(deq2 < deq1);
    EXPECT_TRUE(deq2 >= deq1);
    EXPECT_FALSE(deq2 <= deq1);
}

TEST(DequeTest, Iterators)
{
    davis::deque<int> deq(arr, arr + 7);
    EXPECT_EQ(*deq.begin(), 0);
    EXPECT_EQ(*(deq.end()-1), 6);
    EXPECT_EQ(*deq.cbegin(), 0);
    EXPECT_EQ(*(deq.cend()-1), 6);
}

TEST(DequeTest, Capacity)
{
    davis::deque<int> deq(arr, arr + 7);
    EXPECT_EQ(deq.size(),7);
    EXPECT_EQ(deq.max_size(), size_t(-1));
    deq.resize(3);
    EXPECT_EQ(deq.size(), 3);
    deq.resize(50,663);
    EXPECT_EQ(deq.size(), 50);
    EXPECT_EQ(deq[40], 663);
    EXPECT_FALSE(deq.empty());
    deq.clear();
    EXPECT_TRUE(deq.empty());
}

TEST(DequeTest, ElementAccess)
{
    davis::deque<int> deq(arr, arr + 7);
    EXPECT_EQ(deq[4],4);
    EXPECT_EQ(deq.at(4), 4);
    EXPECT_EQ(deq.front(), 0);
    EXPECT_EQ(deq.back(), 6);
}

TEST(DequeTest, Modifiers)
{
    davis::deque<int> deq1;
    deq1.assign(arr,arr+6);
    EXPECT_EQ(deq1.size(), 6);
    EXPECT_EQ(deq1.front(), 0);
    EXPECT_EQ(deq1.back(), 5);
    davis::deque<int> deq2;
    deq2.assign(164,6);
    EXPECT_EQ(deq2.size(), 164);
    EXPECT_EQ(deq2.front(), 6);
    EXPECT_EQ(deq2.back(), 6);
    deq1.push_front(614);
    EXPECT_EQ(deq1.size(), 7);
    EXPECT_EQ(deq1.front(), 614);
    deq1.push_back(707);
    EXPECT_EQ(deq1.size(), 8);
    EXPECT_EQ(deq1.back(), 707);
    deq1.pop_back();
    deq1.pop_front();
    EXPECT_EQ(deq1.size(), 6);
    EXPECT_EQ(deq1.front(), 0);
    EXPECT_EQ(deq1.back(), 5);
    for(int i=0;i<deq1.size();i++)
    {
        EXPECT_EQ(deq1[i],i);
    }
    deq1.insert(deq1.begin(),1000);
    EXPECT_EQ(deq1.front(), 1000);
    EXPECT_EQ(deq1.back(), 5);
    EXPECT_EQ(deq1.size(), 7);
    deq1.insert(deq1.begin(), 5000000,2000);
    EXPECT_EQ(deq1[5000000], 1000);
    EXPECT_EQ(deq1.front(), 2000);
    EXPECT_EQ(deq1.back(), 5);
    EXPECT_EQ(deq1.size(), 5000007);
    deq1.insert(deq1.begin(),arr,arr+5);
    EXPECT_EQ(deq1[5], 2000);
    EXPECT_EQ(deq1.front(), 0);
    EXPECT_EQ(deq1.back(), 5);
    EXPECT_EQ(deq1.size(), 5000012);
    deq1.erase(deq1.begin(),deq1.begin()+5000005);
    EXPECT_EQ(deq1.size(), 7);
    EXPECT_EQ(deq1.front(), 1000);
    EXPECT_EQ(deq1.back(), 5);
    deq1.erase(deq1.begin());
    EXPECT_EQ(deq1.size(), 6);
    EXPECT_EQ(deq1.front(), 0);
    EXPECT_EQ(deq1.back(), 5);
    davis::deque<int> deq3(deq2);
    deq1.swap(deq2);
    EXPECT_TRUE(deq1==deq3);
}