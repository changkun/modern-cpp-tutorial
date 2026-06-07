//
// 3.8.copy.elision.cpp
// chapter 03 runtime enhancement
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// A type that can be neither copied nor moved
struct NonMovable {
    NonMovable() { std::cout << "constructed" << std::endl; }
    NonMovable(const NonMovable&) = delete;
    NonMovable(NonMovable&&) = delete;
};

// Returning a prvalue is well-formed since C++17 thanks to guaranteed
// copy elision: no copy or move constructor is required here.
NonMovable make() {
    return NonMovable{};
}

int main() {
    NonMovable n = make(); // initialized directly, no copy/move
    (void)n;
}
