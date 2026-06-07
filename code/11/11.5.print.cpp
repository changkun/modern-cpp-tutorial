//
// 11.5.print.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <print>

// C++23 <print> offers std::print/std::println: type-safe, std::format
// based output without iostream chaining.
int main() {
    std::println("Hello, {}!", "C++23");
    std::println("{} + {} = {}", 1, 2, 1 + 2);
}
