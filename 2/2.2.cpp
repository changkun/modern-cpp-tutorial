//
// 2.2.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// constexpr

#include <iostream>
#define LEN 10

constexpr int len_foo() {
    return 5;
}

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1)+fibonacci(n-2);
}

int main() {
    char arr_1[10];
    
    char arr_2[LEN];
    
    const int len = 10;
    char arr_3[len];
    
    char arr_5[len_foo()+5];
    
    std::cout << fibonacci(10) << std::endl;
    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    
    return 0;
}
