//
// main.cpp
//
// exercise solution - chapter 7
// modern cpp tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial/
//

#include <iostream> // std::cout, std::endl

#include <vector>   // std::vector
#include <string>   // std::string
#include <future>   // std::future
#include <thread>   // std::this_thread::sleep_for
#include <chrono>   // std::chrono::seconds

#include "thread_pool.hpp"

int main()
{
    // create a thread pool with max. 4 concurrency threads
    ThreadPool pool(4);
    // create execution results list
    std::vector< std::future<std::string> > results;

    // start eight thread task
    for(int i = 0; i < 8; ++i) {
        // add all task to result list
        results.emplace_back(
            // ass print task to thread pool
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                // wait a sec when the previous line is out
                std::this_thread::sleep_for(std::chrono::seconds(1));
                // keep output and return the status of execution
                std::cout << "world " << i << std::endl;
                return std::string("---thread ") + std::to_string(i) + std::string(" finished.---");
            })
        );
    }

    // outputs
    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}
