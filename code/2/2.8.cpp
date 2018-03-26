//
// 2.8.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// 强类型枚举

#include <iostream>
template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

// 如果两个都定义为 value1 和 value2，将引发重定义错误
enum Left {
    left_value1 = 1,
    left_value2
};
enum Right {
    right_value1 = 1,
    right_value2
};

enum class new_enum : unsigned int{
    value1,
    value2,
    value3 = 100,
    value4 = 100
};

int main() {
    
    if (Left::left_value1 == Right::right_value2) {
        std::cout << "Left::value1 == Right::value2" << std::endl;
    }
    
    // 引发编译错误
    // if(new_enum::value1 == 1) {
    //     std::cout << "true!" << std::endl;
    // }
    if (new_enum::value3 == new_enum::value4) {
        std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
    }
    
    std::cout << new_enum::value3 << std::endl;
    
    
    return 0;
}
