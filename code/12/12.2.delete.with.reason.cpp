//
// 12.2.delete.with.reason.cpp
// chapter 12 cpp26
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// C++26 lets a deleted function carry a reason, which the compiler
// reports if the function is selected.
void use_span(int* p, int n);
void use_span(std::nullptr_t) = delete("pass a real buffer, not nullptr");

int main() {
    int buf[3] = {1, 2, 3};
    use_span(buf, 3);
    // use_span(nullptr); // error: call to deleted function: pass a real buffer, not nullptr
    std::cout << "ok" << std::endl;
}

void use_span(int* p, int n) {
    for (int i = 0; i < n; ++i) std::cout << p[i] << ' ';
    std::cout << std::endl;
}
