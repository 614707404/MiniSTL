#include <iostream>
#include <ctime>
#include "davis_allocate.h"
#include "davis_vector.h"
using namespace std;
int main()
{
    srand((unsigned)time(NULL));
    cout << "Hello MiniSTL" << endl;
    int ia[5] = {0, 1, 2, 3, 4};
    DAVIS::vector<int> test;
    for(int i=0;i<100;i++){
        test.push_back(static_cast<int>(rand()));
    }
    for(int num:test){
        cout<<num<<' ';
    }
    cout << endl;
    return 0;
}