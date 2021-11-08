//
// 10.1.without.concepts.cpp
// chapter 10 cpp20
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int>arr{9,6,4,8,7,3,5,1,2};
    sort(arr.begin(),arr.end());
    for(int n:arr)
    {
       cout<<n<<" ";
    }
    return 0;
}
