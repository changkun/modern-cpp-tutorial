---
title: 第 9 章 其他杂项
type: book-zh-cn
order: 9
---

# 第 9 章 其他杂项

[TOC]

## 9.1 新类型

### `long long int`

`long long int` 并不是 C++11 最先引入的，其实早在 C99，
`long long int` 就已经被纳入 C 标准中，所以大部分的编译器早已支持。
C++11 的工作则是正式把它纳入标准库，
规定了一个 `long long int` 类型至少具备 64 位的比特数。

## 9.2 noexcept 的修饰和操作

C++ 相比于 C 的一大优势就在于 C++ 本身就定义了一套完整的异常处理机制。
然而在 C++11 之前，几乎没有人去使用在函数名后书写异常声明表达式，
从 C++11 开始，这套机制被弃用，所以我们不去讨论也不去介绍以前这套机制是如何工作如何使用，
你更不应该主动去了解它。

C++11 将异常的声明简化为以下两种情况：

1. 函数可能抛出任何异常
2. 函数不能抛出任何异常

并使用 `noexcept` 对这两种行为进行限制，例如：

```cpp
void may_throw(); // 可能抛出异常
void no_throw() noexcept; // 不可能抛出异常
```

如果使用 `noexcept` 标记过的函数进行可能抛出异常的操作，编译器会在通过异常退出函数的路径上插入 `std::terminate()` 的调用，以使得程序终止运行。

`noexcept` 还能够做操作符，用于操作一个表达式，当表达式无异常时，返回 `true`，否则返回 `false`。

```cpp
#include <iostream>
void may_throw() {
    throw true;
}
auto non_block_throw = []{
    may_throw();
};
void no_throw() noexcept {
    return;
}

auto block_throw = []() noexcept {
    no_throw();
};
int main()
{
    std::cout << std::boolalpha
        << "may_throw() noexcept? " << noexcept(may_throw()) << std::endl
        << "no_throw() noexcept? " << noexcept(no_throw()) << std::endl
        << "lmay_throw() noexcept? " << noexcept(non_block_throw()) << std::endl
        << "lno_throw() noexcept? " << noexcept(block_throw()) << std::endl;
    return 0;
}
```

`noexcept` 修饰完一个函数之后能够起到封锁异常扩散的功效，如果内部产生异常，外部也不会触发。例如：

```cpp
try {
    may_throw();
} catch (...) {
    std::cout << "捕获异常, 来自 may_throw()" << std::endl;
}
try {
    non_block_throw();
} catch (...) {
    std::cout << "捕获异常, 来自 non_block_throw()" << std::endl;
}
try {
    block_throw();
} catch (...) {
    std::cout << "捕获异常, 来自 block_throw()" << std::endl;
}
```

最终输出为：

```
捕获异常, 来自 may_throw()
捕获异常, 来自 non_block_throw()
```

## 9.3 字面量

### 原始字符串字面量

传统 C++ 里面要编写一个充满特殊字符的字符串其实是非常痛苦的一件事情，
比如一个包含 HTML 本体的字符串需要添加大量的转义符，
例如一个Windows 上的文件路径经常会：`C:\\File\\To\\Path`。

C++11 提供了原始字符串字面量的写法，可以在一个字符串前方使用 `R` 来修饰这个字符串，
同时，将原始字符串使用括号包裹，例如：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = R"(C:\File\To\Path)";
    std::cout << str << std::endl;
    return 0;
}
```

### 自定义字面量

C++11 引进了自定义字面量的能力，通过重载双引号后缀运算符实现：

```cpp
// 字符串字面量自定义必须设置如下的参数列表
std::string operator"" _wow1(const char *wow1, size_t len) {
    return std::string(wow1)+"woooooooooow, amazing";
}

std::string operator"" _wow2 (unsigned long long i) {
    return std::to_string(i)+"woooooooooow, amazing";
}

int main() {
    auto str = "abc"_wow1;
    auto num = 1_wow2;
    std::cout << str << std::endl;
    std::cout << num << std::endl;
    return 0;
}
```

自定义字面量支持四种字面量：

1. 整型字面量：重载时必须使用 `unsigned long long`、`const char *`、模板字面量算符参数，在上面的代码中使用的是前者；
2. 浮点型字面量：重载时必须使用 `long double`、`const char *`、模板字面量算符；
3. 字符串字面量：必须使用 `(const char *, size_t)` 形式的参数表；
4. 字符字面量：参数只能是 `char`, `wchar_t`, `char16_t`, `char32_t` 这几种类型。

## 9.4 内存对齐

C++ 11 引入了两个新的关键字 `alignof` 和 `alignas` 来支持对内存对齐进行控制。
`alignof` 关键字能够获得一个与平台相关的 `std::size_t` 类型的值，用于查询该平台的对齐方式。
当然我们有时候并不满足于此，甚至希望自定定义结构的对齐方式，同样，C++ 11 还引入了 `alignas`
来重新修饰某个结构的对齐方式。我们来看两个例子：

```cpp
#include <iostream>

struct Storage {
    char      a;
    int       b;
    double    c;
    long long d;
};

struct alignas(std::max_align_t) AlignasStorage {
    char      a;
    int       b;
    double    c;
    long long d;
};

int main() {
    std::cout << alignof(Storage) << std::endl;
    std::cout << alignof(AlignasStorage) << std::endl;
    return 0;
}
```

其中 `std::max_align_t` 要求每个标量类型的对齐方式严格一样，因此它几乎是最大标量没有差异，
进而大部分平台上得到的结果为 `long double`，因此我们这里得到的 `AlignasStorage` 的对齐要求是 8 或 16。

### 过对齐类型的动态分配

在 C++17 之前，`new` 表达式无法保证满足**过对齐 (over-aligned)** 类型（即对齐要求超过 `alignof(std::max_align_t)` 的类型）的对齐需求，使用这类类型常常需要借助平台特定的 `posix_memalign`、`_aligned_malloc` 等手段。C++17 引入了接受 `std::align_val_t` 参数的 `operator new` / `operator delete` 重载，使得 `new` 表达式在为过对齐类型分配内存时会自动选用对齐版本：

```cpp
struct alignas(64) Aligned {
    double v[8];
};

Aligned* p = new Aligned; // C++17：自动使用对齐版本的 operator new
// 此时 reinterpret_cast<std::uintptr_t>(p) % 64 == 0
delete p;
```

## 9.5 类型双关与 `std::bit_cast`

「类型双关」(type punning) 指的是把同一段内存按另一种类型重新解读，常见于底层编程（例如读取浮点数的位模式）。许多人习惯用 `reinterpret_cast` 通过指针或引用来做这件事：

```cpp
float f = 3.14f;
std::uint32_t bits = *reinterpret_cast<std::uint32_t*>(&f); // 未定义行为！
```

但这违反了**严格别名规则 (strict aliasing rule)**：除了 `char`、`unsigned char` 与 `std::byte` 之外，通过与对象实际类型不兼容的左值去访问该对象是未定义行为，编译器在优化时完全可以假设这种情况不会发生。

正确且可移植的做法是使用 `std::memcpy`（在任何标准下都合法）：

```cpp
std::uint32_t bits;
std::memcpy(&bits, &f, sizeof bits); // 良好定义
```

C++20 进一步提供了 `std::bit_cast`（位于 `<bit>`），它以良好定义的方式重新解读对象表示，语义更清晰，并且可以用于常量表达式：

```cpp
#include <bit>
auto bits = std::bit_cast<std::uint32_t>(f); // 要求两个类型大小相同且可平凡复制
float back = std::bit_cast<float>(bits);
```

## 9.6 数学特殊函数

C++17 在 `<cmath>` 中引入了一组数学特殊函数（special mathematical functions），例如 `std::riemann_zeta`、`std::beta`、`std::assoc_legendre`、`std::cyl_bessel_j` 等，便于科学计算与机器学习相关领域使用：

```cpp
#include <cmath>
double z = std::riemann_zeta(2.0); // ≈ 1.6449 (即 π²/6)
```

> 需要注意的是，这些特殊函数属于标准的一部分，但**各标准库实现的支持程度不一**：libstdc++ (GCC) 提供了完整实现，而 libc++ (Clang) 在很长时间内并未实现它们。因此上面的代码不一定能在所有工具链上编译，使用前请确认你的标准库支持情况。

## 总结

本节介绍的几个特性是从仍未介绍的现代 C++ 新特性里使用频次较靠前的特性了，`noexcept` 是最为重要的特性，它的一个功能在于能够阻止异常的扩散传播，有效的让编译器最大限度的优化我们的代码。

[返回目录](./toc.md) | [上一章](./08-filesystem.md) | [下一章 展望：C++20 简介](./10-cpp20.md)

## 许可

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本教程由[欧长坤](https://github.com/changkun)撰写，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](https://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../../LICENSE)。
