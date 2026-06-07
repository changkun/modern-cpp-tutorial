//
// 11.9.small.features.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <bit>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// A function object whose call operator is static (C++23): no implicit
// object parameter, so it can be called without an instance overhead.
struct Add {
    static int operator()(int a, int b) { return a + b; }
};

int main() {
    // auto(x): an explicit decay-copy that produces a prvalue copy.
    std::vector<int> v{1, 2, 3};
    auto copy = auto(v);
    std::cout << "copy size: " << copy.size() << '\n';

    // static operator()
    std::cout << "Add: " << Add{}(2, 3) << '\n';

    // std::string::contains (C++23)
    std::string s = "modern c++";
    std::cout << "contains: " << s.contains("c++") << '\n';

    // std::byteswap (C++23)
    std::cout << std::hex << "byteswap: "
              << std::byteswap(std::uint16_t{0x1234}) << std::dec << '\n';

    // [[assume]] gives the optimizer a precondition it may rely on.
    int x = 10;
    [[assume(x > 0)]];
    std::cout << "x = " << x << '\n';
}
