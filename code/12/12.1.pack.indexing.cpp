//
// 12.1.pack.indexing.cpp
// chapter 12 cpp26
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// C++26 pack indexing: select an element of a parameter pack directly
// with pack...[N], without recursion or std::tuple gymnastics.
template <typename... Ts>
auto first(Ts... ts) {
    return ts...[0];
}
template <typename... Ts>
auto last(Ts... ts) {
    return ts...[sizeof...(ts) - 1];
}

int main() {
    std::cout << first(1, 2, 3) << std::endl; // 1
    std::cout << last(1, 2, 3) << std::endl;  // 3
}
