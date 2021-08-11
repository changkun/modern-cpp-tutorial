---
title: "Chapter 07 Parallelism and Concurrency"
type: book-en-us
order: 7
---

# Chapter 07 Parallelism and Concurrency

[TOC]

## 7.1 Basic of Parallelism

`std::thread` is used to create an execution thread instance, so it is the basis for all concurrent programming. It needs to include the `<thread>` header file when using it.
It provides a number of basic thread operations, such as `get_id()` to get the thread ID of the thread being created, use `join()` to join a thread, etc., for example:

```cpp
#include <iostream>
#include <thread>

int main() {
    std::thread t([](){
        std::cout << "hello world." << std::endl;
    });
    t.join();
    return 0;
}
```

## 7.2 Mutex and Critical Section

We have already learned the basics of concurrency technology in the operating system, or the database, and `mutex` is one of the cores.
C++11 introduces a class related to `mutex`, with all related functions in the `<mutex>` header file.

`std::mutex` is the most basic `mutex` class in C++11, and you can create a mutex by instantiating `std::mutex`.
It can be locked by its member function `lock()`, and `unlock()` can be unlocked.
But in the process of actually writing the code, it is best not to directly call the member function,
Because calling member functions, you need to call `unlock()` at the exit of each critical section, and of course, exceptions.
At this time, C++11 also provides a template class `std::lock_guard` for the RAII syntax for the mutex.

RAII guarantees the exceptional security of the code while keeping the simplicity of the code.

```cpp
#include <iostream>
#include <thread>

int v = 1;

void critical_section(int change_v) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    // execute contention works
    v = change_v;

    // mtx will be released after leaving the scope
}

int main() {
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();

    std::cout << v << std::endl;
    return 0;
}
```

Because C++ guarantees that all stack objects will be destroyed at the end of the declaration period, such code is also extremely safe.
Whether `critical_section()` returns normally or if an exception is thrown in the middle, a stack rollback is thrown, and `unlock()` is automatically called.

And `std::unique_lock` is more flexible than `std::lock_guard`, `std::unique_lock` is more flexible.
Objects of `std::unique_lock` manage the locking and unlocking operations on the `mutex` object with exclusive ownership (no other `unique_lock` objects owning the ownership of a `mutex` object). So in concurrent programming, it is recommended to use `std::unique_lock`.

`std::lock_guard` cannot explicitly call `lock` and `unlock`, and `std::unique_lock` can be called anywhere after the declaration.
It can reduce the scope of the lock and provide higher concurrency.

If you use the condition variable `std::condition_variable::wait` you must use `std::unique_lock` as a parameter.

For instance:

```cpp
#include <iostream>
#include <thread>

int v = 1;

void critical_section(int change_v) {
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    // do contention operations
    v = change_v;
    std::cout << v << std::endl;
    // release the lock
    lock.unlock();

    // during this period,
    // others are allowed to acquire v

    // start another group of contention operations
    // lock again
    lock.lock();
    v += 1;
    std::cout << v << std::endl;
}

int main() {
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();
    return 0;
}
```

## 7.3 Future

The Future is represented by `std::future`, which provides a way to access the results of asynchronous operations. This sentence is very difficult to understand.
To understand this feature, we need to understand the multi-threaded behavior before C++11.

Imagine if our main thread A wants to open a new thread B to perform some of our expected tasks and return me a result.
At this time, thread A may be busy with other things and have no time to take into account the results of B.
So we naturally hope to get the result of thread B at a certain time.

Before the introduction of `std::future` in C++11, the usual practice is:
Create a thread A, start task B in thread A, send an event when it is ready, and save the result in a global variable.
The main function thread A is doing other things. When the result is needed, a thread is called to wait for the function to get the result of the execution.

The `std::future` provided by C++11 simplifies this process and can be used to get the results of asynchronous tasks.
Naturally, we can easily imagine it as a simple means of thread synchronization, namely the barrier.

To see an example, we use extra `std::packaged_task`, which can be used to wrap any target that can be called for asynchronous calls. For example:

```cpp
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
```

After encapsulating the target to be called, you can use `get_future()` to get a `std::future` object to implement thread synchronization later.

## 7.4 Condition Variable

The condition variable `std::condition_variable` was born to solve the deadlock and was introduced when the mutex operation was not enough.
For example, a thread may need to wait for a condition to be true to continue execution.
A dead wait loop can cause all other threads to fail to enter the critical section so that when the condition is true, a deadlock occurs.
Therefore, the `condition_variable` instance is created primarily to wake up the waiting thread and avoid deadlocks.
`notify_one()` of `std::condition_variable` is used to wake up a thread;
`notify_all()` is to notify all threads. Below is an example of a producer and consumer model:

```cpp
#include <queue>
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>


int main() {
    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;  // notification sign

    auto producer = [&]() {
        for (int i = 0; ; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "producing " << i << std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all();
        }
    };
    auto consumer = [&]() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            while (!notified) {  // avoid spurious wakeup
                cv.wait(lock);
            }

            // temporal unlock to allow producer produces more rather than
            // let consumer hold the lock until its consumed.
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // consumer is slower
            lock.lock();
            if (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << std::endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    std::thread p(producer);
    std::thread cs[2];
    for (int i = 0; i < 2; ++i) {
        cs[i] = std::thread(consumer);
    }
    p.join();
    for (int i = 0; i < 2; ++i) {
        cs[i].join();
    }
    return 0;
}
```

It is worth mentioning that although we can use `notify_one()` in the producer, it is not recommended to use it here.
Because in the case of multiple consumers, our consumer implementation simply gives up the lock holding, which makes it possible for other consumers to compete for this lock, to better utilize the concurrency between multiple consumers. Having said that, but in fact because of the exclusivity of `std::mutex`,
We simply can't expect multiple consumers to be able to produce content in a parallel consumer queue, and we still need a more granular approach.

## 7.5 Atomic Operation and Memory Model

Careful readers may be tempted by the fact that the example of the producer-consumer model in the previous section may have compiler optimizations that cause program errors.
For example, the boolean `notified` is not modified by `volatile`, and the compiler may have optimizations for this variable, such as the value of a register.
As a result, the consumer thread can never observe the change of this value. This is a good question. To explain this problem, we need to further discuss the concept of the memory model introduced from C++11. Let's first look at a question. What is the output of the following code?

```cpp
#include <thread>
#include <iostream>

int main() {
    int a = 0;
    volatile int flag = 0;

    std::thread t1([&]() {
        while (flag != 1);

        int b = a;
        std::cout << "b = " << b << std::endl;
    });

    std::thread t2([&]() {
        a = 5;
        flag = 1;
    });

    t1.join();
    t2.join();
    return 0;
}
```

Intuitively, `a = 5;` seems in `t2` seems to always execute before `flag = 1;`, and `while (flag != 1)` in `t1` seems to guarantee `std ::cout << "b = " << b << std::endl;` will not be executed before the mark is changed. Logically, it seems that the value of `b` should be equal to 5.
But the actual situation is much more complicated than this, or the code itself is undefined behavior because, for `a` and `flag`, they are read and written in two parallel threads.
There has been competition. Also, even if we ignore competing for reading and writing, it is still possible to receive out-of-order execution of the CPU and the impact of the compiler on the rearrangement of instructions.
Cause `a = 5` to occur after `flag = 1`. Thus `b` may output 0.

### Atomic Operation

`std::mutex` can solve the problem of concurrent read and write, but the mutex is an operating system-level function.
This is because the implementation of a mutex usually contains two basic principles:

1. Provide automatic state transition between threads, that is, "lock" state
2. Ensure that the memory of the manipulated variable is isolated from the critical section during the mutex operation

This is a very strong set of synchronization conditions, in other words when it is finally compiled into a CPU instruction, it will behave like a lot of instructions (we will look at how to implement a simple mutex later).
This seems too harsh for a variable that requires only atomic operations (no intermediate state).

The research on synchronization conditions has a very long history, and we will not go into details here. Readers should understand that under the modern CPU architecture, atomic operations at the CPU instruction level are provided.
Therefore, in the C + + 11 multi-threaded shared variable reading and writing, the introduction of the `std::atomic` template, so that we instantiate an atomic type, will be a
Atomic type read and write operations are minimized from a set of instructions to a single CPU instruction. E.g:

```cpp
std::atomic<int> counter;
```

And provides basic numeric member functions for atomic types of integers or floating-point numbers, for example,
Including `fetch_add`, `fetch_sub`, etc., and the corresponding `+`, `-` version is provided by overload.
For example, the following example:

```cpp
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> count = {0};

int main() {
    std::thread t1([](){
        count.fetch_add(1);
    });
    std::thread t2([](){
        count++;        // identical to fetch_add
        count += 1;     // identical to fetch_add
    });
    t1.join();
    t2.join();
    std::cout << count << std::endl;
    return 0;
}
```

Of course, not all types provide atomic operations because the feasibility of atomic operations depends on the architecture of the CPU and whether the type structure being instantiated satisfies the memory alignment requirements of the architecture, so we can always pass `std::atomic<T>::is_lock_free` to check if the atom type needs to support atomic operations, for example:

```cpp
#include <atomic>
#include <iostream>

struct A {
    float x;
    int y;
    long long z;
};

int main() {
    std::atomic<A> a;
    std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    return 0;
}
```

### Concistency Model

Multiple threads executing in parallel, discussed at some macro level, can be roughly considered a distributed system.
In a distributed system, any communication or even local operation takes a certain amount of time, and even unreliable communication occurs.

If we force the operation of a variable `v` between multiple threads to be atomic, that is, any thread after the operation of `v`
Other threads can **synchronize** to perceive changes in `v`, for the variable `v`, which appears as a sequential execution of the program, it does not have any efficiency gains due to the introduction of multithreading. Is there any way to accelerate this properly? The answer is to weaken the synchronization conditions between processes in atomic operations.

In principle, each thread can correspond to a cluster node, and communication between threads is almost equivalent to communication between cluster nodes.
Weakening the synchronization conditions between processes, usually we will consider four different consistency models:

1. Linear consistency: Also known as strong consistency or atomic consistency. It requires that any read operation can read the most recent write of a certain data, and the order of operation of all threads is consistent with the order under the global clock.

   ```
           x.store(1)      x.load()
   T1 ---------+----------------+------>


   T2 -------------------+------------->
                   x.store(2)
   ```

   In this case, thread `T1`, `T2` is twice atomic to `x`, and `x.store(1)` is strictly before `x.store(2)`. `x.store(2)` strictly occurs before `x.load()`. It is worth mentioning that linear consistency requirements for global clocks are difficult to achieve, which is why people continue to study other consistent algorithms under this weaker consistency.

2. Sequential consistency: It is also required that any read operation can read the last data written by the data, but it is not required to be consistent with the order of the global clock.

   ```
           x.store(1)  x.store(3)   x.load()
   T1 ---------+-----------+----------+----->


   T2 ---------------+---------------------->
                 x.store(2)

   or

           x.store(1)  x.store(3)   x.load()
   T1 ---------+-----------+----------+----->


   T2 ------+------------------------------->
         x.store(2)
   ```

   Under the order consistency requirement, `x.load()` must read the last written data, so `x.store(2)` and `x.store(1)` do not have any guarantees, ie As long as `x.store(2)` of `T2` occurs before `x.store(3)`.

3. Causal consistency: its requirements are further reduced, only the sequence of causal operations is guaranteed, and the order of non-causal operations is not required.

   ```
         a = 1      b = 2
   T1 ----+-----------+---------------------------->


   T2 ------+--------------------+--------+-------->
         x.store(3)         c = a + b    y.load()

   or

         a = 1      b = 2
   T1 ----+-----------+---------------------------->


   T2 ------+--------------------+--------+-------->
         x.store(3)          y.load()   c = a + b

   or

        b = 2       a = 1
   T1 ----+-----------+---------------------------->


   T2 ------+--------------------+--------+-------->
         y.load()            c = a + b  x.store(3)
   ```

   The three examples given above are all causal consistent because, in the whole process, only `c` has a dependency on `a` and `b`, and `x` and `y` are not related in this example. (But in actual situations we need more detailed information to determine that `x` is not related to `y`)

4. Final Consistency: It is the weakest consistency requirement. It only guarantees that an operation will be observed at a certain point in the future, but does not require the observed time. So we can even strengthen this condition a bit, for example, to specify that the time observed for an operation is always bounded. Of course, this is no longer within our discussion.

   ```
       x.store(3)  x.store(4)
   T1 ----+-----------+-------------------------------------------->


   T2 ---------+------------+--------------------+--------+-------->
            x.read()      x.read()           x.read()   x.read()
   ```

   In the above case, if we assume that the initial value of x is 0, then the four times ``x.read()` in `T2` may be but not limited to the following:

   ```
   3 4 4 4 // The write operation of x was quickly observed
   0 3 3 4 // There is a delay in the observed time of the x write operation
   0 0 0 4 // The last read read the final value of x, but the previous changes were not observed.
   0 0 0 0 // The write operation of x is not observed in the current time period, but the situation that x is 4 can be observed at some point in the future.
   ```

### Memory Orders

To achieve the ultimate performance and achieve consistency of various strength requirements, C++11 defines six different memory sequences for atomic operations. The option `std::memory_order` expresses four synchronization models between multiple threads:

1. Relaxed model: Under this model, atomic operations within a single thread are executed sequentially, and instruction reordering is not allowed, but the order of atomic operations between different threads is arbitrary. The type is specified by `std::memory_order_relaxed`. Let's look at an example:

   ```cpp
   std::atomic<int> counter = {0};
   std::vector<std::thread> vt;
   for (int i = 0; i < 100; ++i) {
       vt.emplace_back([&](){
           counter.fetch_add(1, std::memory_order_relaxed);
       });
   }

   for (auto& t : vt) {
       t.join();
   }
   std::cout << "current counter:" << counter << std::endl;
   ```

2. Release/consumption model: In this model, we begin to limit the order of operations between processes. If a thread needs to modify a value, but another thread will have a dependency on that operation of the value, that is, the latter depends. former. Specifically, thread A has completed three writes to `x`, and thread `B` relies only on the third `x` write operation, regardless of the first two write behaviors of `x`, then `A ` When active `x.release()` (ie using `std::memory_order_release`), the option `std::memory_order_consume` ensures that `B` observes `A` when calling `x.load()` Three writes to `x`. Let's look at an example:

   ```cpp
   // initialize as nullptr to prevent consumer load a dangling pointer
   std::atomic<int*> ptr(nullptr);
   int v;
   std::thread producer([&]() {
       int* p = new int(42);
       v = 1024;
       ptr.store(p, std::memory_order_release);
   });
   std::thread consumer([&]() {
       int* p;
       while(!(p = ptr.load(std::memory_order_consume)));

       std::cout << "p: " << *p << std::endl;
       std::cout << "v: " << v << std::endl;
   });
   producer.join();
   consumer.join();
   ```

3. Release/Acquire model: Under this model, we can further tighten the order of atomic operations between different threads, specifying the timing between releasing `std::memory_order_release` and getting `std::memory_order_acquire`. **All** write operations before the release operation is visible to any other thread, i.e., happens before.

   As you can see, `std::memory_order_release` ensures that a write before a release does not occur after the release operation, which is a **backward barrier**, and `std::memory_order_acquire` ensures that a subsequent read or write after a acquire does not occur before the acquire operation, which is a **forward barrier**.
   For the `std::memory_order_acq_rel` option, combines the characteristics of the two barriers and determines a unique memory barrier, such that reads and writes of the current thread will not be rearranged across the barrier.
 
   Let's check an example:

   ```cpp
   std::vector<int> v;
   std::atomic<int> flag = {0};
   std::thread release([&]() {
       v.push_back(42);
       flag.store(1, std::memory_order_release);
   });
   std::thread acqrel([&]() {
       int expected = 1; // must before compare_exchange_strong
       while(!flag.compare_exchange_strong(expected, 2, std::memory_order_acq_rel)) {
           expected = 1; // must after compare_exchange_strong
       }
       // flag has changed to 2
   });
   std::thread acquire([&]() {
       while(flag.load(std::memory_order_acquire) < 2);

       std::cout << v.at(0) << std::endl; // must be 42
   });
   release.join();
   acqrel.join();
   acquire.join();
   ```

   In this case we used `compare_exchange_strong`, which is the Compare-and-swap primitive, which has a weaker version, `compare_exchange_weak`, which allows a failure to be returned even if the exchange is successful. The reason is due to a false failure on some platforms, specifically when the CPU performs a context switch, another thread loads the same address to produce an inconsistency. In addition, the performance of `compare_exchange_strong` may be slightly worse than `compare_exchange_weak`, but in most cases, `compare_exchange_strong` should be limited.

4. Sequential Consistent Model: Under this model, atomic operations satisfy sequence consistency, which in turn can cause performance loss. It can be specified explicitly by `std::memory_order_seq_cst`. Let's look at a final example:

   ```cpp
   std::atomic<int> counter = {0};
   std::vector<std::thread> vt;
   for (int i = 0; i < 100; ++i) {
       vt.emplace_back([&](){
           counter.fetch_add(1, std::memory_order_seq_cst);
       });
   }

   for (auto& t : vt) {
       t.join();
   }
   std::cout << "current counter:" << counter << std::endl;
   ```

   This example is essentially the same as the first loose model example. Just change the memory order of the atomic operation to `memory_order_seq_cst`. Interested readers can write their own programs to measure the performance difference caused by these two different memory sequences.

## Conclusion

The C++11 language layer provides support for concurrent programming. This section briefly introduces `std::thread`/`std::mutex`/`std::future`, an important tool that can't be avoided in concurrent programming.
In addition, we also introduced the "memory model" as one of the most important features of C++11.
They provide a critical foundation for standardized high-performance computing for C++.

## Exercises

1. Write a simple thread pool that provides the following features:

   ```cpp
   ThreadPool p(4); // specify four work thread

   // enqueue a task, and return a std::future
   auto f = pool.enqueue([](int life) {
       return meaning;
   }, 42);

   // fetch result from future
   std::cout << f.get() << std::endl;
   ```

2. Use `std::atomic<bool>` to implement a mutex.

[Table of Content](./toc.md) | [Previous Chapter](./06-regex.md) | [Next Chapter: File System](./08-filesystem.md)

## Further Readings

- [C++ 并发编程(中文版)](https://www.amazon.com/dp/1617294691/ref=cm_sw_em_r_mt_dp_U_siEmDbRMMF960)
- [Thread document](http://en.cppreference.com/w/cpp/thread)
- Herlihy, M. P., & Wing, J. M. (1990). Linearizability: a correctness condition for concurrent objects. ACM Transactions on Programming Languages and Systems, 12(3), 463–492. https://doi.org/10.1145/78969.78972

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).`
