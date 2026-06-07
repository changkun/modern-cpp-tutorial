//
// 11.4.expected.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <expected>
#include <iostream>
#include <string>

// std::expected<T, E> holds either a value (T) or an error (E),
// expressing fallible operations without exceptions.
std::expected<int, std::string> parse_positive(int x) {
    if (x > 0) return x;
    return std::unexpected("not positive");
}

int main() {
    auto a = parse_positive(42);
    auto b = parse_positive(-1);
    std::cout << (a ? std::to_string(*a) : a.error()) << std::endl; // 42
    std::cout << (b ? std::to_string(*b) : b.error()) << std::endl; // not positive
}
