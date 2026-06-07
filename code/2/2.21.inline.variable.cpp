//
// 2.21.inline.variable.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

struct Widget {
    // C++17: define and initialize a static data member inside the class
    static inline int count = 0;
    Widget() { ++count; }
};

// C++17: an inline variable can be safely defined in a header and
// included by multiple translation units without violating the ODR
inline int global_value = 42;

int main() {
    Widget a, b, c;
    std::cout << "Widget::count = " << Widget::count << std::endl; // 3
    std::cout << "global_value = " << global_value << std::endl;   // 42
}
