//
// 2.2.constexpr.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
//

#include <iostream>

int len_foo() {
    int i = 2;
    return i;
}
constexpr int len_foo_constexpr() {
    return 5;
}

// error in C++11 due to more than one return statement, okay C++14 and above
constexpr int fibonacci(const int n) {
     if(n == 1) return 1;
     if(n == 2) return 1;
     return fibonacci(n-1) + fibonacci(n-2);
}

// ok in C++11, single return
constexpr int fibonacci2(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}


int main() {
    const int len =10;
    char arr_1[10];                      // legal
    char arr_2[len];                     // legal

    int len2 = 10;
    //char arr_3[len2];                  // illegal, container sizes must be constexpr

    const int len3 = len + 1;
    constexpr int len3_constexpr = 1 + 2 + 3;
   // char arr_4[len3];                // illegal, but ok for most of the compilers
    char arr_4[len3_constexpr];         // legal

    // char arr_5[len_foo()+5];          // illegal
    char arr_6[len_foo_constexpr() + 1]; // legal
    
    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    std::cout << fibonacci(10) << std::endl;

    return 0;
}
