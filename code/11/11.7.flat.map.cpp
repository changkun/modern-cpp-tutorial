//
// 11.7.flat.map.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <flat_map>
#include <iostream>

// std::flat_map is an associative container backed by sorted contiguous
// storage (by default two vectors). It trades slower insertion for fast
// lookup and cache-friendly iteration.
int main() {
    std::flat_map<int, const char*> m;
    m.insert({3, "three"});
    m.insert({1, "one"});
    m.insert({2, "two"});
    for (const auto& [k, v] : m) // iterated in sorted key order
        std::cout << k << " => " << v << '\n';
}
