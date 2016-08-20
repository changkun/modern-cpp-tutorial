//
// 2.6.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// 模板增强


#include <iostream>
#include <vector>
#include <string>

template class std::vector<bool>;            // 强行实例化
extern template class std::vector<double>;   // 不在该编译文件中实例化模板


template< typename T, typename U, int value>
class SuckType {
public:
    T a;
    U b;
    SuckType():a(value),b(value){}
};
// template< typename T>
// typedef SuckType<std::vector<int>, T, 1> NewType; // 不合法

template <typename T>
using NewType = SuckType<int, T, 1>;                 // 合法

// 默认模板类型
template<typename T = int, typename U = int>
auto add(T x, U y) -> decltype(x+y) {
    return x+y;
}

// sizeof...
template<typename... Args>
void magic(Args... args) {
    std::cout << sizeof...(args) << std::endl;
}


// 1. 递归解参数包
template<typename T>
void printf1(T value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Args>
void printf1(T value, Args... args) {
    std::cout << value << std::endl;
    printf1(args...);
}
// 2.初始化列表展开解参数包
template<typename T, typename... Args>
auto printf2(T value, Args... args) {
    std::cout << value << std::endl;
    return std::initializer_list<T>{([&] {
        std::cout << args << std::endl;
    }(), value)...};
}

int main() {
    
    std::vector<std::vector<int>> wow;      // 注意尖括号
    
    NewType<int> t;
    
    magic();
    magic(1);
    magic(1,"");
    
    printf1(1, 2.3, "abc");
    printf2(1, 2.3, "abc");
    return 0;
}
