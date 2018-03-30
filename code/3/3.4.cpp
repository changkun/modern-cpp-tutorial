//
// 3.4.cpp
// c++1x tutorial
//
// created by changkun at changkun.de
//
// 移动语义

#include <iostream>
class A {
public:
    int *pointer;
    A():pointer(new int(1)) { std::cout << "构造" << pointer << std::endl; }
    A(A& a):pointer(new int(*a.pointer)) { std::cout << "拷贝" << pointer << std::endl; }    // 无意义的对象拷贝
    A(A&& a):pointer(a.pointer) { a.pointer = nullptr;std::cout << "移动" << pointer << std::endl; }
    ~A(){ std::cout << "析构" << pointer << std::endl; delete pointer; }
};
// 防止编译器优化
A return_rvalue(bool test) {
    A a,b;
    if(test) return a;
    else return b;
}
int main() {
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
    
    return 0;
}
