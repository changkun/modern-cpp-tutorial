//
// 3.4.historical.cpp
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
using namespace std;
int main() {
    // int &a = std::move(1); // illegal, non-const lvalue reference cannot ref rvalue
    const int &b = move(1); // legal, const lvalue reference can

    cout << b << endl;
}
