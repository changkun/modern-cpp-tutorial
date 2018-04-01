#include <iostream>

template<typename T0>
void printf(T0 value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Args>
void printf(T value, Args... args) {
    std::cout << value << std::endl;
    printf(args...);
}

template<typename T0, typename... T>
void printf_short(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf(t...);
}
int main() {
    printf_short(1, 2, "123", 1.1);
    return 0;
}