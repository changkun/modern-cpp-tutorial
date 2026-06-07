//
// 4.4.string.view.cpp
// chapter 04 containers
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <string>
#include <string_view>

// std::string_view is a non-owning, read-only view over a character
// sequence; passing it avoids copying and accepts both std::string and
// string literals.
void print(std::string_view sv) {
    std::cout << sv << " (size = " << sv.size() << ")" << std::endl;
}

int main() {
    std::string_view sv = "hello, world";
    print(sv.substr(0, 5)); // "hello", no allocation

    std::string s = "from std::string";
    print(s);               // implicit conversion, no copy

    print("from a literal");
}
