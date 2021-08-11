//
// 3.1.lambda.basic.cpp
// chapter 03 runtime enhancement
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//


#include <iostream>
#include <memory>  // std::make_unique
#include <utility> // std::move

void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // At this moment, stored_value == 1, and value == 100.
    // Because copy_value has copied when its was created.
}

void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // At this moment, stored_value == 100, value == 100.
    // Because copy_value stores reference
}

void lambda_expression_capture() {
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };
    std::cout << add(3,4) << std::endl;
}

void lambda_generic() {
    auto generic = [](auto x, auto y) {
        return x+y;
    };
    
    std::cout << generic(1, 2) << std::endl;
    std::cout << generic(1.1, 2.2) << std::endl;
}

int main() {
    lambda_value_capture();
    lambda_reference_capture();
    lambda_expression_capture();
    lambda_generic();
    return 0;
}
