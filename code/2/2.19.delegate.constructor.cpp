//
// 2.19.constructor.cpp
// chapter 2 language usability
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <string>
class Base {
public:
    std::string str;
    int value;
    Base() = delete;
    Base(std::string s) {
        str = s;
    }
    
    // delegate constructor
    Base(std::string s, int v) : Base(s) {
        value = v;
    }
    
    // final constructor
    virtual void foo() final {
        return;
    }
    virtual void foo(int v) {
        value = v;
    }
};
class Subclass final : public Base {
public:
    double floating;
    Subclass() = delete;
    
    // inherit constructor
    Subclass(double f, int v, std::string s) : Base(s, v) {
        floating = f;
    }
    
    // explifict constructor
    virtual void foo(int v) override {
        std::cout << v << std::endl;
        value = v;
    }
};  // legal final

// class Subclass2 : Subclass {
// };  // illegal, Subclass has final
// class Subclass3 : Base {
//    void foo(); // illegal, foo has final
// }

int main() {
    // Subclass oops; // illegal, default constructor has deleted
    Subclass s(1.2, 3, "abc");
    
    s.foo(1);
    
    std::cout << s.floating << std::endl;
    std::cout << s.value << std::endl;
    std::cout << s.str << std::endl;
}
