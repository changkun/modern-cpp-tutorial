//
// fold.expression.cpp
//
// exercise solution - chapter 2
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
using namespace std;
template<typename ... T>
auto average(T ... t) {
    return (t + ... ) / sizeof...(t);
}
int main() {
    cout << average(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) <<endl;
}
