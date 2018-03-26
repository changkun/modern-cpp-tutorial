//
// 2.1.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// nullptr

#include <iostream>

void foo(char *);
void foo(int);

int main() {
    
    if(NULL == (void *)0)
        std::cout << "NULL == 0" << std::endl;  // 该行将输出
    else
        std::cout << "NULL != 0" << std::endl;
    
    foo(0);         // 调用 foo(int)
    //foo(NULL);    // 该行不能通过编译
    foo(nullptr);   // 调用 foo(char*)
    
    return 0;
}
void foo(char *ch) {
    std::cout << "call foo(char*)" << std::endl;
}
void foo(int i) {
    std::cout << "call foo(int)" << std::endl;
}
