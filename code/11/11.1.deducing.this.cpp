//
// 11.1.deducing.this.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// C++23 "deducing this": an explicit object parameter lets one function
// template serve as const/non-const and lvalue/rvalue overloads at once.
struct Counter {
    int value = 0;
    // `this Self&& self` deduces the cv-/ref-qualification of the object.
    template <typename Self>
    auto&& get(this Self&& self) {
        return self.value;
    }
};

int main() {
    Counter c{42};
    std::cout << c.get() << std::endl; // 42
}
