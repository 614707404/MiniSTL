#include <gtest/gtest.h>
#include "davis_algorithm.h"
#include "davis_vector.h"
TEST(AlgorithmTest, ForEachTest)
{
    struct Display
    {
        void operator()(int &i) { i = 1; }
    } display;
    int arr[10] = {0};
    davis::for_each(arr,arr+10,display);
    for (int _ = 0; _ < 10; ++_)
    {
        EXPECT_EQ(arr[_],1);
    }
}
TEST(AlgorithmTest, FindTest)
{
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    EXPECT_EQ(*davis::find(arr,arr+10,5),5);
}
TEST(AlgorithmTest, FindIfTest)
{
    struct EqualFive
    {
        bool operator()(int i) { return i == 5; }
    }ef;
    
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(*davis::find_if(arr, arr + 10, ef), 5);
}
TEST(AlgorithmTest, FindEndTest)
{
    struct EqualHalf
    {
        bool operator()(const int &l, const int &r)
        {
            return l == r / 2;
            ;
        }
    } eh;

    int arr[10] = {0, 1, 2, 3, 1, 2, 3, 7, 8, 9};
    int arr2[3] = {1, 2, 3};
    int arr3[3] = {2, 4, 6};
    EXPECT_EQ(davis::find_end(arr, arr + 10, arr2, arr2 + 3) - arr, 4);
    EXPECT_EQ(davis::find_end(arr, arr + 10, arr3, arr3 + 3, eh) - arr, 4);
}
TEST(AlgorithmTest, FindFirstOfTest)
{
    struct EqualHalf
    {
        bool operator()(const int &l, const int &r)
        {
            return l == r / 2;
            ;
        }
    } eh;

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[3] = {1, 54, 3};
    int arr3[3] = {22, 4, 6};
    EXPECT_EQ(davis::find_first_of(arr, arr + 10, arr2, arr2 + 3) - arr, 1);
    EXPECT_EQ(davis::find_first_of(arr, arr + 10, arr3, arr3 + 3, eh) - arr, 2);
}
TEST(AlgorithmTest, AdjacentFindTest)
{
    struct EqualHalf
    {
        bool operator()(const int &l, const int &r)
        {
            return l == r / 2;
            ;
        }
    } eh;

    int arr[10] = {10, 1, 2, 3, 3, 5, 6, 7, 8, 9};
    EXPECT_EQ(davis::adjacent_find(arr, arr + 10) - arr, 3);
    EXPECT_EQ(davis::adjacent_find(arr, arr + 10, eh) - arr, 1);
}
TEST(AlgorithmTest, CountTest)
{
    int arr[10] = {10, 1, 2, 3, 3, 5, 6, 7, 8, 9};
    EXPECT_EQ(davis::count(arr, arr + 10, 3), 2);
}
TEST(AlgorithmTest, CountIfTest)
{
    struct EqualSix
    {
        bool operator()(const int &l)
        {
            return l == 6;
            ;
        }
    } es;
    int arr[10] = {10, 1, 2, 3, 3, 5, 6, 7, 8, 9};
    EXPECT_EQ(davis::count_if(arr, arr + 10,es ), 1);
}
TEST(AlgorithmTest, MissMatchTest)
{
    struct Equal
    {
        bool operator()(const int &l,const int& r)
        {
            return l == r;
        }
    } eq;
    int arr[10] = {10, 1, 2, 3, 3, 5, 6, 7, 8, 9};
    int arr2[10] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(davis::mismatch(arr, arr + 10, arr2).first - arr, 4);
    EXPECT_EQ(davis::mismatch(arr, arr + 10, arr2, eq).first - arr, 4);
    EXPECT_EQ(davis::mismatch(arr, arr + 10, arr2).second - arr2, 4);
    EXPECT_EQ(davis::mismatch(arr, arr + 10, arr2, eq).second - arr2, 4);
}
TEST(AlgorithmTest, EqualTest)
{
    struct Equal
    {
        bool operator()(const int &l, const int &r)
        {
            return l == r;
        }
    } eq;
    int arr[10] = {10, 1, 2, 3, 3, 5, 6, 7, 8, 9};
    int arr2[10] = {10, 1, 2, 3, 3, 5, 6, 7, 8, 9};
    int arr3[10] = {10, 1, 2, 3, 3, 5, 6, 7, 8, 10};
    EXPECT_TRUE(davis::equal(arr, arr + 10, arr2));
    EXPECT_TRUE(davis::equal(arr, arr + 10, arr2, eq));
    EXPECT_FALSE(davis::equal(arr, arr + 10, arr3));
    EXPECT_FALSE(davis::equal(arr, arr + 10, arr3, eq));
}
TEST(AlgorithmTest, SearchTest)
{
    struct Equal
    {
        bool operator()(const int &l, const int &r)
        {
            return l == r;
        }
    } eq;
    int arr[10] = {10, 1, 2, 3, 3, 5, 6, 7, 8, 9};
    int arr2[10] = {1, 2, 3};
    EXPECT_EQ(davis::search(arr, arr + 10, arr2, arr2 + 3) - arr, 1);
    EXPECT_EQ(davis::search(arr, arr + 10, arr2, arr2 + 3) - arr, 1);
}
TEST(AlgorithmTest, SearchNTest)
{
    struct Equal
    {
        bool operator()(const int &l, const int &r)
        {
            return l == r;
        }
    } eq;
    int arr[10] = {10, 1, 2, 3, 3, 3, 6, 7, 8, 9};
    int arr2[10] = {1, 2, 3};
    EXPECT_EQ(davis::search_n(arr, arr + 10, 3, 3) - arr, 3);
    EXPECT_EQ(davis::search_n(arr, arr + 10, 3, 3, eq) - arr, 3);
}
TEST(AlgorithmTest, CopyTest)
{

    int arr[10] = {10, 1, 2, 3, 3, 3, 6, 7, 8, 9};
    int arr2[10];
    davis::copy(arr,arr+10,arr2);
    for(int i=0;i<10;++i){
        EXPECT_EQ(arr[i],arr2[i]);
    }
}
TEST(AlgorithmTest, CopyBackwardTest)
{

    int arr[10] = {0, 1, 2, 3, 3, 3, 6, 7, 8, 9};
    int arr2[10];
    davis::copy_backward(arr, arr + 10, arr2+10);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], arr2[i]);
    }
}
TEST(AlgorithmTest, SwapTest)
{

    char a='a';
    char b='b';
    davis::swap(a,b);
    EXPECT_EQ(a, 'b');
    EXPECT_EQ(b, 'a');
}
TEST(AlgorithmTest, SwapRangeTest)
{

    int arr[10] = {0, 4, 5, 6, 1, 2, 3, 7, 8, 9};
    davis::swap_ranges(arr+1,arr+4,arr+4);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}
TEST(AlgorithmTest, IterSwapTest)
{

    davis::vector<int> a;
    a.push_back(1);
    a.push_back(0);

    davis::iter_swap(a.begin(),a.begin()+1);
    EXPECT_EQ(a[0], 0);
    EXPECT_EQ(a[1], 1);
}

TEST(AlgorithmTest, TransformTest)
{
    struct Operator1
    {
        int operator()(int& a){
            return a/2;
        }
    }op;
    struct Operator2
    {
        int operator()(int &a, int &b)
        {
            return a - b;
        }
    } op2;
    int arr[10] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
    int arr2[10];
    davis::transform(arr, arr + 10, arr2, op);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr2[i], i);
    }
    int arr3[10];
    davis::transform(arr, arr + 10, arr2, arr3,op2);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr3[i], i);
    }
}
TEST(AlgorithmTest, ReplaceTest)
{
    int arr[10] = {0, 1, 2, 3, 13, 5, 6, 7, 8, 9};
    davis::replace(arr,arr+10,13,4);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}
TEST(AlgorithmTest, ReplaceIfTest)
{
    struct equal
    {
        bool operator()(int& a){
            return a==13;
        }
    }eq;
    
    int arr[10] = {0, 1, 2, 3, 13, 5, 6, 7, 8, 9};
    davis::replace_if(arr, arr + 10, eq, 4);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}
TEST(AlgorithmTest, ReplaceCopyTest)
{
    int arr[10] = {0, 1, 2, 3, 13, 5, 6, 7, 8, 9};
    int arr2[10];
    davis::replace_copy(arr, arr + 10, arr2,13, 4);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr2[i], i);
    }
}
TEST(AlgorithmTest, ReplaceCopyIfTest)
{
    struct equal
    {
        bool operator()(int &a)
        {
            return a == 13;
        }
    } eq;

    int arr[10] = {0, 1, 2, 3, 13, 5, 6, 7, 8, 9};
    int arr2[10];
    davis::replace_copy_if(arr, arr + 10, arr2,eq, 4);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr2[i], i);
    }
}
TEST(AlgorithmTest, GenerateTest)
{
    struct Generator
    {
        int operator()(){
            return 0;
        }
    }g;
    
    int arr[10];
    davis::generate(arr,arr+10,g);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], 0);
    }
    int arr2[10] = {0, 1, 2, 3, 13, 5, 6, 7, 8, 9};
    davis::generate_n(arr2, 5, g);
    for (int i = 0; i < 10; ++i)
    {
        if (i < 5)
            EXPECT_EQ(arr2[i], 0);
        else
            EXPECT_EQ(arr2[i], i);
    }
}

TEST(AlgorithmTest, RemoveTest)
{
    int arr[11] = {0, 1, 2, 3, 13,4, 5, 6, 7, 8, 9};
    davis::remove(arr, arr + 11, 13);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}
TEST(AlgorithmTest, RemoveIfTest)
{
    struct equal
    {
        bool operator()(int &a)
        {
            return a == 13;
        }
    } eq;

    int arr[11] = {0, 1, 2, 3, 13, 4,5, 6, 7, 8, 9};
    davis::remove_if(arr, arr + 11, eq);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
}
TEST(AlgorithmTest, RemoveCopyTest)
{
    int arr[11] = {0, 1, 2, 3, 13, 4,5, 6, 7, 8, 9};
    int arr2[10];
    davis::remove_copy(arr, arr + 11, arr2, 13);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr2[i], i);
    }
}
TEST(AlgorithmTest, RemoveCopyIfTest)
{
    struct equal
    {
        bool operator()(int &a)
        {
            return a == 13;
        }
    } eq;

    int arr[11] = {0, 1, 2, 3, 13, 4,5, 6, 7, 8, 9};
    int arr2[10];
    davis::remove_copy_if(arr, arr + 11, arr2, eq);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr2[i], i);
    }
}
TEST(AlgorithmTest, UniqueTest)
{
    struct equal
    {
        bool operator()(int &a ,int &b)
        {
            return a == b;
        }
    } eq;

    int arr[12] = {0, 1,1 ,2,2, 3, 4, 5, 6, 7, 8, 9};
    davis::unique(arr, arr + 12);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
    int arr2[12] = {0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9};
    davis::unique(arr2, arr2 + 12,eq);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr2[i], i);
    }
}
TEST(AlgorithmTest, UniqueCopyTest)
{
    struct equal
    {
        bool operator()(int &a, int &b)
        {
            return a == b;
        }
    } eq;

    int arr[12] = {0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr_1[10];
    davis::unique_copy(arr, arr + 12,arr_1);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr_1[i], i);
    }
    int arr2[12] = {0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr_2[10];
    davis::unique_copy(arr2, arr2 + 12, arr_2, eq);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr_2[i], i);
    }
}
TEST(AlgorithmTest, ReverseTest)
{
    int arr[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    davis::reverse(arr, arr + 10);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
    int arr2[10];
    davis::reverse_copy(arr,arr+10,arr2);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr2[i], 9-i);
    }
}
TEST(AlgorithmTest, RotateTest)
{
    int arr[10] = {4, 5, 6, 7, 8, 9, 0, 1, 2, 3};
    davis::rotate(arr, arr + 5,arr+10);
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
    // int arr2[10];
    // davis::reverse_copy(arr, arr + 10, arr2);
    // for (int i = 0; i < 10; ++i)
    // {
    //     EXPECT_EQ(arr2[i], 9 - i);
    // }
}