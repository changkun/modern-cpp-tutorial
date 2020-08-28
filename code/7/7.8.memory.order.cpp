//
// 7.8.memory.order.cpp
// chapter 7 parallelism and concurrency
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

using namespace std;
using namespace std::chrono;

const int N = 10000;

void relaxed_order() {
    cout << "relaxed_order: " << endl;

    atomic<int> counter = {0};
    vector<thread> vt;
    for (int i = 0; i < N; ++i) {
        vt.emplace_back([&](){
            counter.fetch_add(1, memory_order_relaxed);
        });
    }
    auto t1 = high_resolution_clock::now();
    for (auto& t : vt) {
        t.join();
    }
    auto t2 = high_resolution_clock::now();
    auto duration = ( t2 - t1 ).count();
    cout << "relaxed order speed: " << duration / N << "ns" << endl;
}

void release_consume_order() {
    cout << "release_consume_order: " << endl;

    atomic<int*> ptr;
    int v;
    thread producer([&]() {
        int* p = new int(42);
        v = 1024;
        ptr.store(p, memory_order_release);
    });
    thread consumer([&]() {
        int* p;
        while(!(p = ptr.load(memory_order_consume)));

        cout << "p: " << *p << endl;
        cout << "v: " << v << endl;
    });
    producer.join();
    consumer.join();
}

void release_acquire_order() {
    cout << "release_acquire_order: " << endl;

    int v;
    atomic<int> flag = {0};
    thread release([&]() {
        v = 42;
        flag.store(1, memory_order_release);
    });
    thread acqrel([&]() {
        int expected = 1; // must before compare_exchange_strong
        while(!flag.compare_exchange_strong(expected, 2, memory_order_acq_rel)) {
            expected = 1; // must after compare_exchange_strong
        }
        // flag has changed to 2
    });
    thread acquire([&]() {
        while(flag.load(memory_order_acquire) < 2);

        cout << "v: " << v << endl; // must be 42
    });
    release.join();
    acqrel.join();
    acquire.join();
}

void sequential_consistent_order() {
    cout << "sequential_consistent_order: " << endl;

    atomic<int> counter = {0};
    vector<thread> vt;
    for (int i = 0; i < N; ++i) {
        vt.emplace_back([&](){
            counter.fetch_add(1, memory_order_seq_cst);
        });
    }
    auto t1 = high_resolution_clock::now();
    for (auto& t : vt) {
        t.join();
    }
    auto t2 = high_resolution_clock::now();
    auto duration = ( t2 - t1 ).count();
    cout << "sequential consistent speed: " << duration / N << "ns" << endl;
}

int main() {
    relaxed_order();
    release_consume_order();
    release_acquire_order();
    sequential_consistent_order();
    return 0;
}