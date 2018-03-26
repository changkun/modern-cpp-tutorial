//
// 3.6.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// 完美转发

#include <iostream>
#include <utility>
void reference(int& v) {
    std::cout << "左值引用" << std::endl;
}
void reference(int&& v) {
    std::cout << "右值引用" << std::endl;
}
template <typename T>
void pass(T&& v) {
    std::cout << "普通传参:";
    reference(v);
    std::cout << "std::move 传参:";
    reference(std::move(v));
    std::cout << "std::forward 传参:";
    reference(std::forward<T>(v));
    
}
int main() {
    std::cout << "传递右值:" << std::endl;
    pass(1);
    
    std::cout << "传递左值:" << std::endl;
    int v = 1;
    pass(v);
    
    return 0;
}
