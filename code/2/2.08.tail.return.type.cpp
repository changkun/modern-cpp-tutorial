//
// 2.8.tail.return.type.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <type_traits>

// before c++11
template<typename R, typename T, typename U>
R add(T x, U y) {
    return x + y;
}
// after c++11
template<typename T, typename U>
auto add2(T x, U y) -> decltype(x+y){
    return x + y;
}
// after c++14
template<typename T, typename U>
auto add3(T x, U y){
    return x + y;
}

int main() {

    // before c++11
    int z = add<int, int, int>(1, 2);
    std::cout << z << std::endl;

    // after c++11
    auto w = add2<int, double>(1, 2.0);
    if (std::is_same<decltype(w), double>::value) {
        std::cout << "w is double: ";
    }
    std::cout << w << std::endl;

    // after c++14
    auto q = add3<double, int>(1.0, 2);
    std::cout << "q: " << q << std::endl;

    return 0;
}