//
// 3.2.function.wrap.cpp
// chapter 03 runtime enhancement
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <functional>
#include <iostream>

using foo = void(int);  // function pointer
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
    functional(f);  // call by function pointer
    f(1);           // call by lambda expression

    // std::function wraps a function that take int paremeter and returns int value
    std::function<int(int)> func = foo2;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1+value+important;
    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;

    // bind parameter 1, 2 on function foo, and use std::placeholders::_1 as placeholder
    // for the first parameter.
    auto bindFoo = std::bind(foo3, std::placeholders::_1, 1,2);
    // when call bindFoo, we only need one param left
    bindFoo(1);

    return 0;
}
