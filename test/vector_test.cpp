#include <gtest/gtest.h>
#include "davis_vector.h"

//  测试各类构造函数
TEST(VectorTest, Constuctors)
{
    
    int arr[10]={0,1,2,3,4,5,6,7,8,9};
    // default
    davis::vector<int> vec1;
    EXPECT_EQ(vec1.size(),0);
    EXPECT_EQ(vec1.capacity(), 0);

    // fill
    davis::vector<int> vec2(40);
    EXPECT_EQ(vec2.size(), 40);
    EXPECT_EQ(vec2.capacity(), 40);
    EXPECT_EQ(vec2.front(), 0);
    EXPECT_EQ(vec2.back(), 0);

    davis::vector<int> vec3(10, 1);
    EXPECT_EQ(vec3.size(), 10);
    EXPECT_EQ(vec3.capacity(), 10);
    EXPECT_EQ(vec3.front(), 1);
    EXPECT_EQ(vec3.back(), 1);
    // range
    davis::vector<int> vec4(arr, arr + 5);
    EXPECT_EQ(vec4.size(), 5);
    EXPECT_EQ(vec4.capacity(), 5);
    EXPECT_EQ(vec4.front(), 0);
    EXPECT_EQ(vec4.back(), 4);

    // copy
    davis::vector<int> vec5(vec4);
    EXPECT_EQ(vec5.size(), 5);
    EXPECT_EQ(vec5.capacity(), 5);
    EXPECT_EQ(vec5.front(), 0);
    EXPECT_EQ(vec5.back(), 4);

}

TEST(VectorTest, Operators)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::vector<int> vec1(arr, arr + 8);
    // operator=
    davis::vector<int> vec2;
    vec2 = vec1;
    // operator==
    EXPECT_TRUE(vec1 == vec2);

    vec2.front() = vec2.back();
    // operator!=
    EXPECT_TRUE(vec1 != vec2);
    // operator>
    EXPECT_TRUE(vec2 > vec1);
    // operator<
    EXPECT_FALSE(vec2 < vec1);
    // operator>
    EXPECT_TRUE(vec2 >= vec1);
    // operator<
    EXPECT_FALSE(vec2 <= vec1);
}

TEST(VectorTest, Iterators)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::vector<int> vec1(arr, arr + 10);
    EXPECT_EQ(*vec1.begin(), 0);
    EXPECT_EQ(*(vec1.end() - 1), 9);
    EXPECT_EQ(*vec1.cbegin(), 0);
    EXPECT_EQ(*(vec1.cend() - 1), 9);
}
TEST(VectorTest, Capacity)
{
    davis::vector<int> vec1(100);
    EXPECT_EQ(vec1.size(), 100);
    EXPECT_EQ(vec1.capacity(), 100);
    vec1.push_back(1);
    EXPECT_EQ(vec1.size(),101);
    EXPECT_EQ(vec1.capacity(), 200);
    EXPECT_EQ(vec1.max_size(), size_t(-1)/sizeof(int));
    vec1.resize(50);
    EXPECT_EQ(vec1.size(), 50);
    EXPECT_EQ(vec1.capacity(), 200);
    vec1.resize(400,1);
    EXPECT_EQ(vec1.front(), 0);
    EXPECT_EQ(vec1.back(), 1);
    EXPECT_EQ(vec1.size(), 400);
    EXPECT_EQ(vec1.capacity(), 400);
}
TEST(VectorTest, ElementAccess)
{
    davis::vector<int> vec1;
    for (int i = 0; i < 10000; i++)
    {
        vec1.push_back(i);
    }
    for (int i = 0; i < 10000; i++)
    {
        EXPECT_EQ(vec1[i], i);
        EXPECT_EQ(vec1.at(i), i);
        EXPECT_EQ(vec1.front(), 0);
        EXPECT_EQ(vec1.back(), 10000 - 1);
    }
    int * __ptr=vec1.data();
    *__ptr = 10;
    ++__ptr;
    *__ptr = 20;
    __ptr[2] = 100;
    EXPECT_EQ(vec1[0], 10);
    EXPECT_EQ(vec1[1], 20);
    EXPECT_EQ(vec1[3], 100);
}
TEST(VectorTest, Modifiers)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::vector<int> vec1;
    vec1.assign(arr,arr+10);
    EXPECT_EQ(vec1.size(), 10);
    EXPECT_EQ(vec1.capacity(), 10);
    EXPECT_EQ(vec1.front(), 0);
    EXPECT_EQ(vec1.back(), 9);
    davis::vector<int> vec2;
    vec2.assign(100,161);
    EXPECT_EQ(vec2.size(), 100);
    EXPECT_EQ(vec2.front(), 161);
    EXPECT_EQ(vec2.back(), 161);
    davis::vector<int> vec3;
    for (int i = 0; i < 10000; i++)
    {
        vec3.push_back(i);
    }
    EXPECT_EQ(vec3.size(), 10000);
    EXPECT_EQ(vec3.front(), 0);
    EXPECT_EQ(vec3.back(), 9999);
    for (int i = 0; i < 5000; i++)
    {
        vec3.pop_back();
    }
    EXPECT_EQ(vec3.size(), 5000);
    EXPECT_EQ(vec3.front(), 0);
    EXPECT_EQ(vec3.back(), 4999);
    davis::vector<int> vec4(arr,arr+10);

    vec4.insert(vec4.begin()+5,10000);
    EXPECT_EQ(vec4[5],10000);
    EXPECT_EQ(vec4.size(), 11);

    vec4.insert(vec4.begin() + 5, 10, 10000);
    EXPECT_EQ(vec4[5], 10000);
    EXPECT_EQ(vec4.size(), 21);

    vec4.insert(vec4.begin(),arr,arr+5);
    EXPECT_EQ(vec4[5], 0);
    EXPECT_EQ(vec4.size(), 26);

    vec4.erase(vec4.begin());
    EXPECT_EQ(vec4.front(), 1);
    EXPECT_EQ(vec4.size(), 25);

    vec4.erase(vec4.begin(),vec4.begin()+5);
    EXPECT_EQ(vec4.front(), 1);
    EXPECT_EQ(vec4.size(), 20);

    vec4.swap(vec3);
    EXPECT_EQ(vec4.size(), 5000);
    EXPECT_EQ(vec4.front(), 0);
    EXPECT_EQ(vec4.back(), 4999);
    EXPECT_EQ(vec3.front(), 1);
    EXPECT_EQ(vec3.size(), 20);
}