//
// 12.4.saturation.cpp
// chapter 12 cpp26
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <limits>
#include <numeric>

// C++26 saturation arithmetic clamps to the type's range instead of
// wrapping around on overflow.
int main() {
    int hi = std::numeric_limits<int>::max();
    std::cout << std::add_sat(hi, 1) << std::endl;  // clamps to INT_MAX
    std::cout << std::sub_sat(0, 1) << std::endl;   // -1 (no clamp needed)
    std::cout << std::mul_sat(hi, 2) << std::endl;  // clamps to INT_MAX
}
