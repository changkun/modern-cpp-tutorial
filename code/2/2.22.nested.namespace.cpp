//
// 2.22.nested.namespace.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// C++17: define nested namespaces in a single line
namespace A::B::C {
    int value = 1;
}

int main() {
    std::cout << "A::B::C::value = " << A::B::C::value << std::endl; // 1
}
