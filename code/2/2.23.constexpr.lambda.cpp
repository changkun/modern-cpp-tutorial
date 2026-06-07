//
// 2.23.constexpr.lambda.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

int main() {
    // C++17: a lambda that satisfies the constant-expression requirements
    // is implicitly constexpr and can be evaluated at compile time
    constexpr auto add = [](int a, int b) { return a + b; };
    static_assert(add(1, 2) == 3, "evaluated at compile time");

    constexpr int result = add(3, 4);
    std::cout << "result = " << result << std::endl; // 7
}
