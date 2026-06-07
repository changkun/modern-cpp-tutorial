//
// 10.4.coroutine.cpp
// chapter 10 cpp20
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <coroutine>
#include <iostream>
#include <optional>

// A minimal lazy generator coroutine. C++20 provides only the language
// machinery (co_yield/co_await/co_return) plus the <coroutine> support
// library; the user (or a library) supplies the promise_type. C++23
// adds a ready-made std::generator.
template <typename T>
struct Generator {
    struct promise_type {
        T current;
        Generator get_return_object() {
            return Generator{handle::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T value) { current = value; return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
    using handle = std::coroutine_handle<promise_type>;
    handle h;
    explicit Generator(handle h) : h(h) {}
    ~Generator() { if (h) h.destroy(); }
    Generator(const Generator&) = delete;
    Generator(Generator&& o) noexcept : h(o.h) { o.h = {}; }

    std::optional<T> next() {
        if (!h || h.done()) return std::nullopt;
        h.resume();
        if (h.done()) return std::nullopt;
        return h.promise().current;
    }
};

Generator<int> range(int a, int b) {
    for (int i = a; i < b; ++i)
        co_yield i;
}

int main() {
    auto g = range(1, 5);
    while (auto v = g.next()) std::cout << *v << ' '; // 1 2 3 4
    std::cout << std::endl;
}
