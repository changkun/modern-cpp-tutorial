//
// 2.9.decltype.auto.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

template<int i>
struct Int {};

constexpr auto iter(Int<0>) -> Int<0>;

template<int i>
constexpr auto iter(Int<i>) {
    return iter(Int<i-1>{});
}

int main() {
    decltype(iter(Int<10>{})) a;
}