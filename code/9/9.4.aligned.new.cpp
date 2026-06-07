//
// 9.4.aligned.new.cpp
// chapter 09 others
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <cstdint>
#include <iostream>
#include <new>

// Over-aligned type: its alignment exceeds the default new alignment.
struct alignas(64) Aligned {
    double v[8];
};

int main() {
    // C++17: new automatically uses the aligned operator new for
    // over-aligned types, so the result respects alignof(Aligned).
    Aligned* p = new Aligned;
    std::cout << "alignof  = " << alignof(Aligned) << "\n";
    std::cout << "aligned? = "
              << (reinterpret_cast<std::uintptr_t>(p) % alignof(Aligned) == 0)
              << "\n";
    delete p;
}
