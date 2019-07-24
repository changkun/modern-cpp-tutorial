//
// 7.4.futures.cpp
// chapter 7 parallelism and concurrency
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <thread>
#include <future>

int main() {
    // pack a lambda expression that returns 7 into a std::packaged_task
    std::packaged_task<int()> task([](){return 7;});
    // get the future of task
    std::future<int> result = task.get_future();    // run task in a thread
    std::thread(std::move(task)).detach();
    std::cout << "waiting...";
    result.wait(); // block until future has arrived
    // output result
    std::cout << "done!" << std:: endl << "future result is " << result.get() << std::endl;
    return 0;
}