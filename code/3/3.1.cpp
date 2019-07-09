//
// 3.1.cpp
// modern c++ tutorial
//
// created by changkun at changkun.de
//
// lambda expression

#include <iostream>
#include <utility>

void learn_lambda_func_1() {
    int value_1 = 1;
    auto copy_value_1 = [value_1] {
        return value_1;
    };
    value_1 = 100;
    auto stored_value_1 = copy_value_1();
    std::cout << "stored_value_1=" << stored_value_1 << std::endl;
    // 这时, stored_value_1 == 1, 而 value_1 == 100.
    // 因为 copy_value_1 在创建时就保存了一份 value_1 的拷贝
}

void learn_lambda_func_2() {
    int value_2 = 1;
    auto copy_value_2 = [&value_2] {
        return value_2;
    };
    value_2 = 100;
    auto stored_value_2 = copy_value_2();
    std::cout << "stored_value_2=" << stored_value_2 << std::endl;
    // 这时, stored_value_2 == 100, value_2 == 100.
    // 因为 copy_value_2 保存的是引用
}

int main() {
    learn_lambda_func_1();
    learn_lambda_func_2();
    
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };
    std::cout << add(3,4) << std::endl;
    
    // 泛型 lambda
    auto generic = [](auto x, auto y) {
        return x+y;
    };
    
    generic(1, 2);
    generic(1.1, 2.2);
    return 0;
}
