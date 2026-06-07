//
// 2.11.for.loop.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstddef>

// A minimal custom container: any type that provides usable begin()/end()
// (whose iterators support !=, * and pre-++) can be used with range-based for,
// because the loop is just syntactic sugar over those operations.
struct IntRange {
    int* data;
    std::size_t n;
    int* begin() const { return data; }
    int* end()   const { return data + n; }
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4};
    if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) *itr = 4;
    for (auto element : vec)
        std::cout << element << std::endl; // read only
    for (auto &element : vec) {
        element += 1;                      // writeable
    }
    for (auto element : vec)
        std::cout << element << std::endl; // read only

    // range-based for over a user-defined container
    int arr[] = {10, 20, 30};
    IntRange range{arr, 3};
    for (auto&& x : range)
        std::cout << x << ' ';
    std::cout << std::endl;
}