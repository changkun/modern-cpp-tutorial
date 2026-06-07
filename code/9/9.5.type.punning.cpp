//
// 9.5.type.punning.cpp
// chapter 09 others
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <bit>
#include <cstdint>
#include <cstring>
#include <iostream>

int main() {
    float f = 3.14f;

    // Reinterpreting an object's bytes via a different type through a
    // pointer/reference cast violates the strict-aliasing rule and is
    // undefined behavior:
    //   std::uint32_t bad = *reinterpret_cast<std::uint32_t*>(&f); // UB

    // Portable and always-valid approach (any standard): std::memcpy.
    std::uint32_t bits;
    std::memcpy(&bits, &f, sizeof bits);

    // C++20: std::bit_cast does the same well-defined reinterpretation
    // and is usable in constant expressions.
    auto bits2 = std::bit_cast<std::uint32_t>(f);

    std::cout << std::hex << bits << " == " << bits2 << std::dec
              << " : " << (bits == bits2) << "\n";
    std::cout << "round-trip: " << std::bit_cast<float>(bits2) << "\n";
}
