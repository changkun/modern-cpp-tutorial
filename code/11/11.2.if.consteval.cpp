//
// 11.2.if.consteval.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// C++23 `if consteval` chooses a branch depending on whether the call
// happens during constant evaluation.
constexpr int compute(int x) {
    if consteval {
        return x * 2; // taken during constant evaluation
    } else {
        return x * 3; // taken at run time
    }
}

int main() {
    constexpr int a = compute(10); // compile time -> 20
    int b = compute(10);           // run time     -> 30
    std::cout << a << " " << b << std::endl;
}
