//
// 2.7.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// 面向对象增强

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
    
    // 委托构造
    Base(std::string s, int v) : Base(s) {
        value = v;
    }
    
    // 终止重载
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
    
    // 继承构造
    Subclass(double f, int v, std::string s) : Base(s, v) {
        floating = f;
    }
    
    // 显式重载
    virtual void foo(int v) override {
        std::cout << v << std::endl;
        value = v;
    }
};  // 合法 final

// class Subclass2 : Subclass {
// };  // 非法, Subclass 已 final
// class Subclass3 : Base {
//    void foo(); // 非法, foo 已 final
// }

int main() {
    // Subclass oops; // 非法, 默认构造已删除
    Subclass s(1.2, 3, "abc");
    
    s.foo(1);
    
    std::cout << s.floating << std::endl;
    std::cout << s.value << std::endl;
    std::cout << s.str << std::endl;
}
