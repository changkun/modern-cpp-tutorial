//
// 2.28.sfinae.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <type_traits>
#include <vector>

// SFINAE ("Substitution Failure Is Not An Error"): when substituting
// template arguments produces an invalid type/expression in the
// immediate context, that overload is silently removed from the
// candidate set instead of causing a hard error.

// 1) Constrain with std::enable_if: this overload exists only for
//    integral types.
template <typename T,
          typename = std::enable_if_t<std::is_integral_v<T>>>
void describe(T) {
    std::cout << "integral" << std::endl;
}

// 2) Expression SFINAE: this overload participates only if `c.size()`
//    is a valid expression.
template <typename T>
auto has_size(const T& c) -> decltype(c.size(), std::true_type{}) {
    return std::true_type{};
}
std::false_type has_size(...) { return std::false_type{}; }

int main() {
    describe(42); // integral

    std::cout << std::boolalpha;
    std::cout << has_size(std::vector<int>{1, 2, 3}) << std::endl; // true
    std::cout << has_size(42) << std::endl;                        // false
}
