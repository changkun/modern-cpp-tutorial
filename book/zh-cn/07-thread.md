---
title: 第 7 章 标准库：线程与并发
type: book-zh-cn
order: 7
---

# 第 7 章 标准库：线程与并发

> 内容修订中

[TOC]

## 7.1 std::thread

`std::thread` 用于创建一个执行的线程实例，所以它是一切并发编程的基础，使用时需要包含 `<thread>` 头文件，它提供了很多基本的线程操作，例如`get_id()`来获取所创建线程的线程 ID，例如使用 `join()` 来加入一个线程等等，例如：

```cpp
#include <iostream>
#include <thread>
void foo() {
    std::cout << "hello world" << std::endl;
}
int main() {
    std::thread t(foo);
    t.join();
    return 0;
}
```

## 7.2 std::mutex, std::unique\_lock

我们在操作系统的相关知识中已经了解过了有关并发技术的基本知识，mutex 就是其中的核心之一。C++11引入了 mutex 相关的类，其所有相关的函数都放在 `<mutex>` 头文件中。

`std::mutex` 是 C++11 中最基本的 `mutex` 类，通过实例化 `std::mutex` 可以创建互斥量，而通过其成员函数 `lock()` 可以仅此能上锁，`unlock()` 可以进行解锁。但是在在实际编写代码的过程中，最好不去直接调用成员函数，因为调用成员函数就需要在每个临界区的出口处调用 `unlock()`，当然，还包括异常。这时候 C++11 还为互斥量提供了一个 RAII 语法的模板类`std::lock_gurad`。RAII 在不失代码简洁性的同时，很好的保证了代码的异常安全性。

在 RAII 用法下，对于临界区的互斥量的创建只需要在作用域的开始部分，例如：

```cpp
void some_operation(const std::string &message) {
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);

    // ...操作

    // 当离开这个作用域的时候，互斥锁会被析构，同时unlock互斥锁
    // 因此这个函数内部的可以认为是临界区
}
```

由于 C++保证了所有栈对象在声明周期结束时会被销毁，所以这样的代码也是异常安全的。无论 `some_operation()` 正常返回、还是在中途抛出异常，都会引发堆栈回退，也就自动调用了 `unlock()`。

而 `std::unique_lock` 则相对于 `std::lock_guard` 出现的，`std::unique_lock` 更加灵活，`std::unique_lock` 的对象会以独占所有权（没有其他的 `unique_lock` 对象同时拥有某个 `mutex` 对象的所有权）的方式管理 `mutex` 对象上的上锁和解锁的操作。所以在并发编程中，推荐使用 `std::unique_lock`。

`std::lock_guard` 不能显式的调用 `lock` 和 `unlock`， 而 `std::unique_lock` 可以在声明后的任意位置调用 ，可以缩小锁的作用范围，提供更高的并发度。

如果你用到了条件变量 `std::condition_variable::wait` 则必须使用 `std::unique_lock` 作为参数。

例如：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void block_area() {
std::unique_lock<std::mutex> lock(mtx);
    //...临界区
lock.unlock();
    //...some other code 
lock.lock(); //  can lock again
}
int main() {
    std::thread thd1(block_area);

    thd1.join();

    return 0;
}
```

## 7.3 std::future, std::packaged\_task

`std::future` 则是提供了一个访问异步操作结果的途径，这句话很不好理解。为了理解这个特性，我们需要先理解一下在 C++11之前的多线程行为。

试想，如果我们的主线程 A 希望新开辟一个线程 B 去执行某个我们预期的任务，并返回我一个结果。而这时候，线程 A 可能正在忙其他的事情，无暇顾及 B 的结果，所以我们会很自然的希望能够在某个特定的时间获得线程 B 的结果。

在 C++11 的 `std::future` 被引入之前，通常的做法是：创建一个线程A，在线程A里启动任务 B，当准备完毕后发送一个事件，并将结果保存在全局变量中。而主函数线程 A 里正在做其他的事情，当需要结果的时候，调用一个线程等待函数来获得执行的结果。

而 C++11 提供的 `std::future` 简化了这个流程，可以用来获取异步任务的结果。自然地，我们很容易能够想象到把它作为一种简单的线程同步手段。

此外，`std::packaged_task` 可以用来封装任何可以调用的目标，从而用于实现异步的调用。例如：

```cpp
#include <iostream>
#include <future>
#include <thread>

int main()
{
    // 将一个返回值为7的 lambda 表达式封装到 task 中
    // std::packaged_task 的模板参数为要封装函数的类型
    std::packaged_task<int()> task([](){return 7;});
    // 获得 task 的 future
    std::future<int> result = task.get_future(); // 在一个线程中执行 task
    std::thread(std::move(task)).detach(); std::cout << "Waiting...";
    result.wait();
    // 输出执行结果
    std::cout << "Done!" << std:: endl << "Result is " << result.get() << '\n';
}
```

在封装好要调用的目标后，可以使用 `get_future()` 来获得一个 `std::future` 对象，以便之后实施线程同步。

## 7.4 std::condition_variable

`std::condition_variable` 是为了解决死锁而生的。当互斥操作不够用而引入的。比如，线程可能需要等待某个条件为真才能继续执行，而一个忙等待循环中可能会导致所有其他线程都无法进入临界区使得条件为真时，就会发生死锁。所以，`condition_variable` 实例被创建出现主要就是用于唤醒等待线程从而避免死锁。`std::condition_variable`的 `notify_one()` 用于唤醒一个线程；`notify_all()` 则是通知所有线程。下面是一个生产者和消费者模型的例子：

```cpp
#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>

int main()
{
    // 生产者数量
    std::queue<int> produced_nums;
    // 互斥锁
    std::mutex m;
    // 条件变量
    std::condition_variable cond_var;
    // 结束标志
    bool done = false;
    // 通知标志
    bool notified = false;

    // 生产者线程
    std::thread producer([&]() {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // 创建互斥锁
        std::unique_lock<std::mutex> lock(m);
        std::cout << "producing " << i << '\n';
        produced_nums.push(i);
        notified = true;
        // 通知一个线程
        cond_var.notify_one();
    }
    done = true;
    notified = true;
    cond_var.notify_one();
});

// 消费者线程
std::thread consumer([&]() {
    std::unique_lock<std::mutex> lock(m);
    while (!done) {
        while (!notified) { // 循环避免虚假唤醒
            cond_var.wait(lock);
        }
        while (!produced_nums.empty()) {
            std::cout << "consuming " << produced_nums.front() << '\n';
            produced_nums.pop();
        }
        notified = false;
    }
});

producer.join();
consumer.join();
}
```

## 总结

C++11 语言层提供了并发编程的相关支持，本节简单的介绍了 `std::thread`/`std::mutex`/`std::future` 这些并发编程中不可回避的重要工具。

> 本节提到的内容足以让我们使用不超过 100 行代码编写一个简单的线程池库，请参考习题 TODO

[返回目录](./toc.md) | [上一章](./06-regex.md) | [下一章 标准库：文件系统](./08-filesystem.md)

## 进一步阅读的参考资料

1. [C++ 并发编程\(中文版\)](https://www.gitbook.com/book/chenxiaowei/cpp_concurrency_in_action/details)
2. [线程支持库文档](http://en.cppreference.com/w/cpp/thread)
3. [100 行 C++ 代码实现线程池](https://www.shiyanlou.com/teacher/courses/565)


## 许可

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本教程由[欧长坤](https://github.com/changkun)撰写，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](http://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../LICENSE)。
