#include <iostream>
#include <vector>
#include "davis_allocate.h"
#include "davis_vector.h"
using namespace std;
int main()
{
    cout << "Hello MiniSTL" << endl;
    int ia[5] = {0, 1, 2, 3, 4};
    DAVIS::vector<int> test(5, 1);
    for (int i = 0; i < test.size(); i++)
    {
        cout << test[i] << ' ';
    }
    // vector<int, DAVIS::allocator<int>> iv(ia, ia + 5);
    // for (vector<int, DAVIS::allocator<int>>::iterator it = iv.begin(); it != iv.end(); it++)
    // {
    //     cout << *it << ' ';
    // }
    cout << endl;
    return 0;
}