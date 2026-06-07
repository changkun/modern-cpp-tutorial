---
title: 附录 2：现代 C++ 的最佳实践
type: book-zh-cn
order: 13
---

# 附录 2：现代 C++ 的最佳实践

这篇附录我们来简单谈一谈现代 C++ 的最佳实践。这里的许多思考主要吸收自[《Effective Modern C++》](https://www.amazon.cn/dp/B016OFO492/)、[《C++ 风格指南》](http://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)，以及由 Bjarne Stroustrup 与 Herb Sutter 维护的 [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)。本附录旨在总结一些被广泛认可的最佳实践，帮助你保证代码的整体质量。

## 常用工具

优秀的工具能在问题进入生产环境之前就将其拦截：

- **开启警告，并将其视为错误。** 使用 `-Wall -Wextra`（也可考虑 `-Wpedantic`）进行编译；`-Werror` 可以避免警告不断累积。
- **在测试时运行各类消毒器 (sanitizer)。** AddressSanitizer（`-fsanitize=address`）、UndefinedBehaviorSanitizer（`-fsanitize=undefined`）与 ThreadSanitizer（`-fsanitize=thread`）能够在运行期捕获内存错误、未定义行为以及数据竞争。
- **自动格式化与静态检查。** `clang-format` 保证风格一致，`clang-tidy` 则能发现易错模式并给出现代化改写建议。
- **使用现代构建系统与包管理器**，例如 CMake 搭配 vcpkg 或 Conan，让构建可复现。
- **快速实验**：借助 [Compiler Explorer](https://godbolt.org/) 查看生成的汇编，并对比不同编译器与标准版本的行为。

## 代码风格

一致的代码风格能让代码库更易于阅读与维护：

- 选定一份风格指南并在整个项目中始终如一地遵循；一致性本身比具体如何选择更重要。
- 坚持 `const` 正确性：只要变量、成员函数或参数无需修改状态，就将其标记为 `const`。
- 使用 `auto` 来避免冗余地书写类型，但不要以牺牲可读性为代价——要让读者依然能够看懂名字的含义。
- 优先使用标准库（容器、算法、`std::string`）而非自行实现的等价物。

## 整体性能

- **先测量，再优化。** 使用性能分析器找出真正的热点，而不是凭猜测；过早优化既浪费精力又损害可读性。
- **避免不必要的拷贝。** 用 `const&` 传递大对象；当确实需要一份拷贝时，可按值接收再 `std::move`；在已知最终大小时对容器调用 `reserve()`。
- **让编译器帮你。** 按值返回局部对象并依赖（强制的）复制消除，而不是通过输出参数返回。
- 对拷贝代价高昂的类型优先使用移动语义，并记住 `std::move` 只是一次类型转换，而非真正的「移动」操作。

## 代码安全

- **用 RAII 管理资源。** 把每一种资源（内存、文件、锁、套接字）都封装进一个析构时会释放它的对象中。
- **优先使用智能指针**（`std::unique_ptr`、`std::shared_ptr`）而非裸 `new`/`delete`；避免持有所有权的裸指针。
- **避免未定义行为**：不要越界访问、不要有符号溢出、不要释放后使用、不要违反严格别名规则（参见 §9.5）。消毒器有助于检测这些问题。
- 当边界很重要时，优先使用 `std::span`、`std::array` 与 `.at()` 而非裸指针和不做检查的下标；并用具名的 C++ 类型转换替代 C 风格转换。

## 可维护性

- 让函数保持短小、职责单一；优先使用标准算法而非手写循环，以清晰地表达意图。
- 让接口难以被误用：使用强类型与枚举类，而非裸的 `int`/`bool` 标志。
- 编写测试并持续运行，以便尽早发现回归。
- 注释要解释「为什么」，而非「做了什么」：代码本身已经说明了它在做什么。

## 可移植性

- 当确切的大小很重要时，使用 `<cstdint>` 中的定宽整数类型（如 `std::int32_t`）；不要假设 `int` 是 32 位，也不要假设 `char` 是有符号的。
- 避免依赖实现定义的、平台相关的行为；当不得不依赖时，将其隔离在一层小小的抽象之后。
- 优先使用标准库而非平台特定的 API（例如 `<filesystem>`、`<thread>`、`<chrono>`），让同一份代码可以跨平台构建。
- 当字节序很重要时，显式地查询它（C++20 的 `std::endian`），而不是假设是小端或大端。

[返回目录](./toc.md) | [上一章](./11-appendix1.md)

## 许可

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本书系[欧长坤](https://github.com/changkun)著，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](https://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../../LICENSE)。