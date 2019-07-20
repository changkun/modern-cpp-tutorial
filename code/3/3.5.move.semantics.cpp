//
// 3.5.move.semantics.cpp
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
class A {
public:
    int *pointer;
    A():pointer(new int(1)) { 
        std::cout << "construct" << pointer << std::endl; 
    }
    A(A& a):pointer(new int(*a.pointer)) { 
        std::cout << "copy" << pointer << std::endl; 
    } // meaningless object copy
    A(A&& a):pointer(a.pointer) { 
        a.pointer = nullptr;
        std::cout << "move" << pointer << std::endl; 
    }
    ~A(){ 
        std::cout << "destruct" << pointer << std::endl; 
        delete pointer; 
    }
};
// avoid compiler optimization
A return_rvalue(bool test) {
    A a,b;
    if(test) return a; // equal to static_cast<A&&>(a);
    else return b;     // equal to static_cast<A&&>(b);
}
int main() {
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
    return 0;
}