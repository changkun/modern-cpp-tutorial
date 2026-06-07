//
// 11.8.ranges.zip.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// C++23 added many range adaptors. views::zip iterates several ranges in
// lockstep, yielding tuples of corresponding elements.
int main() {
    std::vector<std::string> names{"a", "b", "c"};
    std::vector<int> scores{90, 80, 70};

    for (auto&& [name, score] : std::views::zip(names, scores))
        std::cout << name << ": " << score << '\n';
}
