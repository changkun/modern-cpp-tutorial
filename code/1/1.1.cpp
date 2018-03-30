//
// 1.1.cpp
//
// chapter 1 introduction
// c++1x tutorial
//
// created by changkun at changkun.de
//

#include "foo.h"
#include <iostream>
#include <functional>

int main() {
    [out = std::ref(std::cout << "Result from C code: " << add(1, 2))](){
        out.get() << ".\n";
    }();
    return 0;
}
