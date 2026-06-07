//
// 2.26.bool.metafunctions.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <type_traits>

// C++17 logical metafunctions compose other type traits.
template <typename T>
constexpr bool is_signed_integral =
    std::conjunction_v<std::is_integral<T>, std::is_signed<T>>;

int main() {
    static_assert(is_signed_integral<int>);
    static_assert(!is_signed_integral<unsigned>);
    static_assert(std::disjunction_v<std::is_integral<float>,
                                     std::is_floating_point<float>>);
    static_assert(std::negation_v<std::is_floating_point<int>>);
    std::cout << "all logical metafunction assertions passed" << std::endl;
}
