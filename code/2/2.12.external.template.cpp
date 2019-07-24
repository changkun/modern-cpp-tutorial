//
// 2.12.external.template.cpp
// chapter 2 language usability
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <vector>

template class std::vector<bool>;           // forcely instantiation
extern template class std::vector<double>;  // external template for avoiding instantiation in this file

template<bool T> class MagicType {
    bool magic = T;
};

int main() {
    // the >> in template
    std::vector<std::vector<int>> matrix;
    std::vector<MagicType<(1>2)>> magic; // legal, but not recommended
}