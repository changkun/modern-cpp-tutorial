//
// 4.1.cpp
// c++1x tutorial
//
// created by changkun at changkun.de
//
// std::array

#include <iostream>
#include <array>

void foo(int *p, int len) {
    for (int i = 0; i != len; ++i) {
        std::cout << p[i] << std::endl;
    }
}

int main() {
    std::array<int, 4> arr= {1,4,3,2};
    
    //int len = 4;
    //std::array<int, len> arr = {1,2,3,4}; // 非法, 数组大小参数必须是常量表达式
    
    // C 风格接口传参
    // foo(arr, arr.size());           // 非法, 无法隐式转换
    foo(&arr[0], arr.size());
    foo(arr.data(), arr.size());
    
    // 更多接口使用
    std::sort(arr.begin(), arr.end());
    for(auto &i : arr)
        std::cout << i << std::endl;
    
    return 0;
}
