//
// 7.1.cpp
// c++1x tutorial
//
// created by changkun at shiyanlou.com
//
// 线程支持库

#include <iostream>
#include <future>
#include <thread>
void foo() {
    std::cout << "hello world" << std::endl;
}

void foo2() {
    // 将一个返回值为7的 lambda 表达式封装到 task 中
    // std::packaged_task 的模板参数为要封装函数的类型
    std::packaged_task<int()> task([](){return 7;});
    // 获得 task 的 future
    std::future<int> result = task.get_future();    // 在一个线程中执行 task
    std::thread(std::move(task)).detach();    std::cout << "Waiting...";
    result.wait();
    // 输出执行结果
    std::cout << "Done!" << std:: endl << "Result is " << result.get() << '\n';
}

int main() {
    std::thread t(foo);
    
    foo2();
    
    t.join();
    
    return 0;
}
