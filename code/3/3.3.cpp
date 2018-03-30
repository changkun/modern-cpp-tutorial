//
// 3.3.cpp
// c++1x tutorial
//
// created by changkun at changkun.de
//
// 右值引用 rvalue reference


#include <iostream>
#include <string>

void reference(std::string& str) {
    std::cout << "左值" << std::endl;
}
void reference(std::string&& str) {
    std::cout << "右值" << std::endl;
}

int main()
{
    std::string  lv1 = "string,";       // lv1 是一个左值
    // std::string&& r1 = s1;           // 非法, 右值引用不能引用左值
    std::string&& rv1 = std::move(lv1); // 合法, std::move可以将左值转移为右值
    std::cout << rv1 << std::endl;      // string,
    
    const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的申明周期
    // lv2 += "Test";                   // 非法, 引用的右值无法被修改
    std::cout << lv2 << std::endl;      // string,string
    
    std::string&& rv2 = lv1 + lv2;      // 合法, 右值引用延长临时对象声明周期
    rv2 += "string";                      // 合法, 非常量引用能够修改临时变量
    std::cout << rv2 << std::endl;      // string,string,string,
    
    reference(rv2);                     // 输出左值
    
    return 0;
}
