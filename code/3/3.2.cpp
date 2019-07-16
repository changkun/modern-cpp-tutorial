//
// 3.2.cpp
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//
// std::function std::bind

#include <functional>
#include <iostream>

using foo = void(int);  // 定义函数指针
void functional(foo f) {
    f(1);
}

int foo2(int para) {
    return para;
}

int foo3(int a, int b, int c) {
    return 0;
}

int main() {
    
    auto f = [](int value) {
        std::cout << value << std::endl;
    };
    functional(f);  // 函数指针调用
    f(1);           // lambda 表达式调用
    
    // std::function 包装了一个返回值为 int, 参数为 int 的函数
    std::function<int(int)> func = foo2;
    
    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1+value+important;
    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
    
    
    // 将参数1,2绑定到函数 foo 上，但是使用 std::placeholders::_1 来对第一个参数进行占位
    auto bindFoo = std::bind(foo3, std::placeholders::_1, 1,2);
    // 这时调用 bindFoo 时，只需要提供第一个参数即可
    bindFoo(1);
    
    
    return 0;
}
