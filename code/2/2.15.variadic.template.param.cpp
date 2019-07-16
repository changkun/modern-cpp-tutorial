//
// 2.15.variadic.template.param.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <vector>
#include <string>

// sizeof...
template<typename... Ts>
void magic(Ts... args) {
    std::cout << sizeof...(args) << std::endl;
}


// 1. recursive parameter unpack
template<typename T0>
void printf1(T0 value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
    std::cout << value << std::endl;
    printf1(args...);
}

// 2. variadic template parameter unfold
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}

// 3. parameter unpack using initializer_list
template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
    std::cout << value << std::endl;
    (void) std::initializer_list<T>{([&args] {
        std::cout << args << std::endl;
    }(), value)...};
}

int main() {
    magic();
    magic(1);
    magic(1,"");
    
    printf1(1, 2, "123", 1.1);
    printf2(1, 2.3, "abc");
    printf3(111, 123, "alpha", 1.2);
    return 0;
}