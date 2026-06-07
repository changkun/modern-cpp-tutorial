//
// 12.3.placeholder.cpp
// chapter 12 cpp26
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// C++26 makes `_` a placeholder name: it can be re-declared in the same
// scope, signaling "I don't care about this value".
int main() {
    auto _ = 1; // first binding
    auto _ = 2; // OK in C++26: re-declaration of the placeholder
    std::cout << "placeholders introduced" << std::endl;
}
