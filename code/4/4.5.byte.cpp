//
// 4.5.byte.cpp
// chapter 04 containers
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <cstddef>
#include <iostream>

// std::byte (C++17) represents a byte of raw memory. Unlike char or
// unsigned char, it is not an arithmetic type: only bitwise operators
// are defined, which prevents accidental arithmetic on raw bytes.
int main() {
    std::byte b{0b0000'1100}; // 12
    b <<= 2;                  // 48
    b |= std::byte{0b0000'0001};
    std::cout << std::to_integer<int>(b) << std::endl; // 49
}
