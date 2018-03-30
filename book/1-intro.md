# 第一章 C++11/14/17 简介

## 一、被弃用的特性

在学习 C++1x 之前，我们先了解一下从 C++11 开始，被弃用的主要特性：

> **注意**：弃用不等于废弃，只是用于暗示程序员这些特性将从未来的标准中消失，应该尽量避免使用。但是，已弃用的特性依然是标准库的一部分，并且出于兼容性的考虑，这些特性其实会『永久』保留。

- **如果一个类有析构函数，为其生成拷贝构造函数和拷贝赋值运算符的特性被弃用了。**

- **不再允许字符串字面值常量赋值给一个 `char *`。如果需要用字符串字面值常量赋值和初始化一个 `char *`，应该使用 `const char *` 或者 `auto`。**

```cpp
char *str = "hello world!"; // 将出现弃用警告
```

- **C++98 异常说明、 `unexcepted_handler`、`set_unexpected()` 等相关特性被弃用，应该使用 `noexcept`。**

- **`auto_ptr` 被弃用，应使用 `unique_ptr`。**

- **`register` 关键字被弃用。**

- **`bool` 类型的 `++` 操作被弃用。**

- **C 语言风格的类型转换被弃用，应该使用 `static_cast`、`reinterpret_cast`、`const_cast` 来进行类型转换。**

还有一些其他诸如参数绑定（C++11 提供了 `std::bind` 和 `std::function`）、`export` 等特性也均被弃用。前面提到的这些特性**如果你从未使用或者听说过，也请不要尝试去了解他们，应该向新标准靠拢**，直接学习新特性。毕竟，技术是向前发展的。

## 二、与 C 的兼容性

出于一些不可抗力、历史原因，我们不得不在 C++ 中使用一些 C 语言代码（甚至古老的 C 语言代码），例如 Linux 系统调用。在 C++11 出现之前，大部分人当谈及 『C 与 C++ 的区别是什么』时，普遍除了回答面向对象的类特性、泛型编程的模板特性外，就没有其他的看法了，甚至直接回答『差不多』，也是大有人在。下面的韦恩图大致上回答了 C 和 C++ 相关的兼容情况：

![](../assets/comparison.png)

从现在开始，你的脑子里应该树立 **『C++ 不是 C 的一个超集』**这个观念（而且从一开始就不是，后面的进一步阅读的参考文献中给出了 C++98 和 C99 之间的区别）。在编写 C++ 时，也应该尽可能的避免使用诸如 `void*` 之类的程序风格。而在不得不使用 C 时，应该注意使用 `extern "C"` 这种特性，将 C 语言的代码与 C++代码进行分离编译，再统一链接这种做法，例如：

```c
// foo.h
#ifdef __cplusplus
extern "C" {
#endif

int add(int x, int y);

#ifdef __cplusplus
}
#endif

// foo.c
int add(int x, int y) {
reutrn x+y;
}

// main.cpp
#include "foo.h"
int main() {
add(1, 2);
return 0;
}
```
应先使用 `gcc` 编译 C 语言的代码：

```bash
gcc -c foo.c
```
编译出 foo.o 文件，再使用 `g++` 将 C++代码和 `.o` 文件链接起来（或者都编译为 `.o` 再统一链接）：

```bash
g++ main.cpp foo.o -o main
```

## 进一步阅读的参考资料

1. C++ 语言导学. Bjarne Stroustrup
2. [C++ 历史](http://en.cppreference.com/w/cpp/language/history)
3. [C++ 1x 特性在 GCC/Clang等编译器中的支持情况](http://en.cppreference.com/w/cpp/compiler_support)
4. [C++98 与 C99 之间的区别](http://david.tribble.com/text/cdiffs.htm#C99-vs-CPP98)

## 许可

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本教程由[欧长坤](https://github.com/changkun)撰写，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](http://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../LICENSE)。