#include <iostream>
#include <memory>

void foo(std::shared_ptr<int> i)
{
    (*i)++;
}


//struct Base {
//    Base() { std::cout << "  Base::Base()\n"; }
//    ~Base() { std::cout << "  Base::~Base()\n"; }
//};
//
//struct Subclass: public Base {
//    Subclass() { std::cout << "  Subclass::Subclass()\n"; }
//    ~Subclass() { std::cout << "  Subclass::~Subclass()\n"; }
//};
//
//void thr(std::shared_ptr<Base> p)
//{
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::shared_ptr<Base> lp = p; // 即使引用计数增加也是线程安全的
//    {
//        static std::mutex io_mutex;
//        std::lock_guard<std::mutex> lk(io_mutex);
//        std::cout << "local pointer in a thread:\n"
//        << "  lp.get() = " << lp.get()
//        << ", lp.use_count() = " << lp.use_count() << '\n';
//    }
//}

int main()
{
    // auto pointer = new int(10); // 非法, 不允许直接赋值
    // 构造了一个 std::shared_ptr
    auto pointer = std::make_shared<int>(10);
    auto pointer2 = pointer;    // 引用计数+1
    auto pointer3 = pointer;    // 引用计数+1
    
    
    foo(pointer);
    std::cout << *pointer << std::endl; // 11
    int *p = pointer.get();             // 这样不会增加引用计数
    
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;

    pointer2.reset();
    std::cout << "reset pointer2:" << std::endl;
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;
    
    pointer3.reset();
    std::cout << "reset pointer3:" << std::endl;
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;
    // std::cout << *pointer << std::endl; // 引用计数为0时, 非法访问
    
    
    // 离开作用域前，pointer 会被析构，引用计数减为0, 从而释放内存
    return 0;
}
