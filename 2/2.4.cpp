//
// 2.4.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// 区间迭代

#include <iostream>
#include <vector>

int main() {
    int array[] = {1,2,3,4,5};
    for(auto &x : array) {
        std::cout << x << std::endl;
    }

    // 传统 C++ 写法
    std::vector<int> arr(5, 100);
    for(std::vector<int>::iterator i = arr.begin(); i != arr.end(); ++i) {
        std::cout << *i << std::endl;
    }
    
    // C++11 写法
    // & 启用了引用, 如果没有则对 arr 中的元素只能读取不能修改
    for(auto &i : arr) {
        std::cout << i << std::endl;
    }
    return 0;
}
