//
// 7.6.bad.example.cpp
// chapter 7 parallelism and concurrency
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <thread>
#include <iostream>
using namespace std;

int main() {
    int a = 0;
    volatile int flag = 0;

    thread t1([&]() {
        while (flag != 1);

        int b = a;
        cout << "b = " << b << std::endl;
    });

    thread t2([&]() {
        a = 5;
        flag = 1;
    });

    t1.join();
    t2.join();
    return 0;
}
