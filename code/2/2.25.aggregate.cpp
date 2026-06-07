//
// 2.25.aggregate.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// C++17 relaxed the aggregate rules: an aggregate may now have public
// base classes (which must themselves be aggregates), and can be
// brace-initialized including the base subobject.
struct Base { int a; };
struct Derived : Base { int b; };

int main() {
    Derived d{{1}, 2}; // {a}, b
    std::cout << d.a << ", " << d.b << std::endl; // 1, 2
}
