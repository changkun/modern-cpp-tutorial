//
// 2.3.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// auto/decltype/尾返回类型/返回类型推导


#include <iostream>

// 传统 C++
template <typename R, typename T, typename U>
R add1(T x, U y) {
    return x+y;
}

// 尾返回类型
template <typename T, typename U>
auto add2(T x, U y) -> decltype(x+y) {
    return x+y;
}

// C++14 返回类型推导
template <typename T, typename U>
auto add3(T x, U y) {
    return x+y;
}

int main() {
    auto i = 5;
    
    int arr[10] = {0};
    auto auto_arr = arr;        // 正确，对整个类型进行推导
    //auto auto_arr2[10] = arr; // 错误,  无法推导数组元素类型

    auto x = 1;
    auto y = 2;
    decltype(x+y) z1;
    //auto z2;                  // 错误, 无法推导

    
    std::cout << add1<int, int, int>(1,1) << std::endl;
    std::cout << add1<int, int>(1,1) << std::endl;
    std::cout << add1<int, int>(1,1) << std::endl;
    
    
    return 0;
}
