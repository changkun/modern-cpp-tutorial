//
// 2.24.static.assert.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

int main() {
    // C++17: the message argument of static_assert is optional
    static_assert(sizeof(int) >= 2);
    static_assert(sizeof(int) >= 2, "int must be at least 2 bytes");
    std::cout << "static_assert passed" << std::endl;
}
