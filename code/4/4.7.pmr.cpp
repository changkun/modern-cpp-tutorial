//
// 4.7.pmr.cpp
// chapter 04 containers
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <array>
#include <cstddef>
#include <iostream>
#include <memory_resource>
#include <vector>

int main() {
    // A monotonic_buffer_resource hands out memory from a fixed buffer
    // (here on the stack) and frees nothing until destroyed. The pmr
    // container allocates through the resource instead of the heap.
    std::array<std::byte, 1024> buffer;
    std::pmr::monotonic_buffer_resource pool{buffer.data(), buffer.size()};

    std::pmr::vector<int> v{&pool};
    for (int i = 0; i < 5; ++i) v.push_back(i);

    for (int x : v) std::cout << x << ' ';
    std::cout << std::endl;
}
