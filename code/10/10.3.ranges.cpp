//
// 10.3.ranges.cpp
// chapter 10 cpp20
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6};

    // Range adaptors compose lazily with the pipe operator: keep the
    // even numbers, then square them. Nothing is computed until iterated.
    auto result = v | std::views::filter([](int x) { return x % 2 == 0; })
                    | std::views::transform([](int x) { return x * x; });

    for (int x : result) std::cout << x << ' '; // 4 16 36
    std::cout << std::endl;
}
