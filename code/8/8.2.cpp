//
// 8.2.cpp
// c++1x tutorial
//
// created by changkun at changkun.de
//
// 字面量

#include <iostream>
#include <string>

std::string operator"" _wow1(const char *wow1, size_t len) {
    return std::string(wow1)+"woooooooooow, amazing";
}

std::string operator""_wow2 (unsigned long long i) {
    return std::to_string(i)+"woooooooooow, amazing";
}

int main() {
    std::string str = R"(C:\\What\\The\\Fxxk)";
    std::cout << str << std::endl;
    
    int value = 0b1001010101010;
    std::cout << value << std::endl;
    
    
    auto str = "abc"_wow1;
    auto num = 1_wow2;
    std::cout << str << std::endl;
    std::cout << num << std::endl;
    return 0;
}
