//
// 11.6.mdspan.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <array>
#include <iostream>
#include <mdspan>

// std::mdspan is a non-owning multidimensional view over contiguous
// storage; it does not allocate, it just reinterprets the layout.
int main() {
    std::array<int, 6> storage{1, 2, 3, 4, 5, 6};
    std::mdspan m(storage.data(), 2, 3); // 2 x 3 view

    for (std::size_t i = 0; i < m.extent(0); ++i) {
        for (std::size_t j = 0; j < m.extent(1); ++j)
            std::cout << m[i, j] << ' ';
        std::cout << '\n';
    }
}
