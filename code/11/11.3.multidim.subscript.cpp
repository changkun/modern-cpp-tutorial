//
// 11.3.multidim.subscript.cpp
// chapter 11 cpp23
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <cstddef>
#include <iostream>

// C++23 allows operator[] to take multiple subscripts.
struct Matrix2x3 {
    int data[6] = {};
    int& operator[](std::size_t r, std::size_t c) { return data[r * 3 + c]; }
};

int main() {
    Matrix2x3 m;
    m[1, 2] = 7;
    std::cout << m[1, 2] << std::endl; // 7
}
