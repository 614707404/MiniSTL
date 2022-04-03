#include<iostream>
#include<vector>
#include"davis_alloc.h"
using namespace std;
int main(){
    cout<<"Hello MiniSTL"<<endl;
    int ia[5]={0,1,2,3,4};
    unsigned int i;
    vector<int,DAVIS::allocator<int>> iv(ia,ia+5);
    for(i = 0;i<iv.size();i++){
        cout<<iv[i]<<' ';
    }
    cout<<endl;
    return 0;
}