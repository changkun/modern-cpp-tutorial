//
// 2.5.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// 初始化列表


#include <initializer_list>

class Foo {
private:
    int value;
public:
    Foo(int) {}
};

class Magic {
public:
    Magic(std::initializer_list<int> list) {}
};

void func(std::initializer_list<int> list) {
    return;
}

int main() {
    int arr[3] = {1,2,3};       // 列表初始化
    Foo foo(1);                 // 普通构造初始化
    
    Magic magic = {1,2,3,4,5};  // 使用 initialize_list
    func({1,2,3});
}
