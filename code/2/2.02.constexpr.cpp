//
// 2.2.constexpr.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}
constexpr int len_foo_constexpr() {
    return 5;
}

// error in c++11
// constexpr int fibonacci(const int n) {
//     if(n == 1) return 1;
//     if(n == 2) return 1;
//     return fibonacci(n-1) + fibonacci(n-2);
// }

// ok
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}


int main() {
    char arr_1[10];                      // legal
    char arr_2[LEN];                     // legal

    int len = 10;
    // char arr_3[len];                  // illegal

    const int len_2 = len + 1;
    constexpr int len_2_constexpr = 1 + 2 + 3;
    // char arr_4[len_2];                // illegal, but ok for most of the compilers
    char arr_4[len_2_constexpr];         // legal

    // char arr_5[len_foo()+5];          // illegal
    char arr_6[len_foo_constexpr() + 1]; // legal
    
    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    std::cout << fibonacci(10) << std::endl;

    return 0;
}
