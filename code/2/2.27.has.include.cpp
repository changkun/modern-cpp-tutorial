//
// 2.27.has.include.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>

// C++17: __has_include is a preprocessor operator that checks whether a
// header is available, enabling portable conditional inclusion.
#if __has_include(<optional>)
#  include <optional>
#  define HAS_OPTIONAL 1
#else
#  define HAS_OPTIONAL 0
#endif

int main() {
    std::cout << "<optional> available: " << HAS_OPTIONAL << std::endl;
#if HAS_OPTIONAL
    std::optional<int> o = 42;
    std::cout << "value: " << o.value() << std::endl;
#endif
}
