---
title: 第 8 章 文件系统
type: book-zh-cn
order: 8
---

# 第 8 章 文件系统

[TOC]

文件系统库提供了文件系统、路径、常规文件、目录等等相关组件进行操作的相关功能。和正则表达式库类似，它也是最先由 boost 发起，并最终在 C++17 中被合并为 C++ 标准的众多库之一。该库的全部内容位于头文件 `<filesystem>` 中的 `std::filesystem` 命名空间下，惯例上会为其引入一个简短的别名：

```cpp
#include <filesystem>
namespace fs = std::filesystem;
```

> 在某些较老的工具链（如 GCC 8 之前）中，使用文件系统库还需要额外链接 `-lstdc++fs`（或 LLVM 的 `-lc++fs`）；现代编译器已不再需要。

## 8.1 路径 `std::filesystem::path`

`std::filesystem::path` 是整个库的核心，它以一种可移植的方式表示文件路径，并屏蔽了不同操作系统在路径分隔符（如 `/` 与 `\`）上的差异。`path` 可以由字符串构造，并通过 `operator/` 来拼接路径片段：

```cpp
fs::path p = "/usr/local";
p /= "bin";              // 现在 p 为 /usr/local/bin
fs::path q = p / "clang"; // 拼接但不修改 p
```

值得强调的是，`path` 仅仅是对路径的**语法**表示，构造一个 `path` 并不会访问磁盘，也不要求该路径真实存在。它提供了一组用于分解路径的成员函数：

```cpp
fs::path p = "/usr/local/hello.txt";
p.filename();    // "hello.txt"
p.stem();        // "hello"
p.extension();   // ".txt"
p.parent_path(); // "/usr/local"
```

## 8.2 查询文件状态

库提供了一系列**非成员函数**用于查询路径对应的实际文件，它们都接受一个 `path` 参数：

```cpp
fs::exists(p);            // 路径是否存在
fs::is_regular_file(p);   // 是否为常规文件
fs::is_directory(p);      // 是否为目录
fs::file_size(p);         // 文件大小（字节）
fs::last_write_time(p);   // 最后修改时间
```

需要注意的是，这些会真正访问文件系统的操作在出错时（例如路径不存在、权限不足）会**抛出 `std::filesystem::filesystem_error` 异常**。库为几乎每个此类函数都提供了一个接受 `std::error_code&` 的重载版本，用于以非异常的方式获取错误：

```cpp
std::error_code ec;
auto size = fs::file_size(p, ec); // 出错时不抛异常，错误写入 ec
if (ec) {
    std::cout << "无法获取大小：" << ec.message() << std::endl;
}
```

## 8.3 遍历目录

`std::filesystem::directory_iterator` 用于遍历一个目录下的直接条目，而 `recursive_directory_iterator` 则会递归地遍历整个目录树。两者都可以直接用于基于范围的 for 循环，迭代得到的元素是 `directory_entry`：

```cpp
for (const auto& entry : fs::directory_iterator(dir)) {
    std::cout << entry.path() << std::endl;
}

// 递归遍历整棵目录树
for (const auto& entry : fs::recursive_directory_iterator(dir)) {
    if (entry.is_regular_file())
        std::cout << entry.path() << " (" << entry.file_size() << ")\n";
}
```

`directory_entry` 会缓存它所对应的文件状态，因此 `entry.is_regular_file()`、`entry.file_size()` 等成员函数往往比对其路径再次调用非成员函数更高效。

## 8.4 创建、复制与删除

库还提供了一组用于修改文件系统的操作：

```cpp
fs::create_directories(p / "a" / "b"); // 递归创建目录（中间目录不存在时一并创建）
fs::copy_file(src, dst);               // 复制单个文件
fs::copy(src, dst, fs::copy_options::recursive); // 递归复制目录
fs::rename(old_path, new_path);        // 重命名 / 移动
fs::remove(p);                         // 删除单个文件或空目录
fs::remove_all(p);                     // 递归删除，返回被删除的条目数
```

## 8.5 一个完整的例子

下面的例子综合演示了上述操作。为了让示例自包含、可重复运行，我们在系统临时目录下创建一个专用的工作目录，并在结束时清理：

```cpp
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    // 在系统临时目录下创建一个专用的工作目录，使示例自包含且可重复运行
    const fs::path base = fs::temp_directory_path() / "modern-cpp-fs-demo";
    fs::remove_all(base);                  // 清理上一次运行的残留
    fs::create_directories(base / "sub");  // 递归创建中间目录

    // 创建一个文件
    std::ofstream(base / "hello.txt") << "hello, filesystem";

    // 路径分解（不访问磁盘）
    const fs::path p = base / "hello.txt";
    std::cout << "filename:  " << p.filename()    << "\n";
    std::cout << "extension: " << p.extension()   << "\n";
    std::cout << "parent:    " << p.parent_path() << "\n";

    // 查询文件
    std::cout << "exists:          " << fs::exists(p)          << "\n";
    std::cout << "is_regular_file: " << fs::is_regular_file(p) << "\n";
    std::cout << "file_size:       " << fs::file_size(p)       << "\n";

    // 递归遍历目录树
    std::cout << "entries:\n";
    for (const auto& entry : fs::recursive_directory_iterator(base))
        std::cout << "  " << entry.path() << "\n";

    // 复制后重命名
    fs::copy_file(p, base / "copy.txt");
    fs::rename(base / "copy.txt", base / "renamed.txt");

    // 清理
    fs::remove_all(base);
    std::cout << "after cleanup, exists: " << fs::exists(base) << "\n";
}
```

[返回目录](./toc.md) | [上一章](./07-thread.md) | [下一章 其他杂项](./09-others.md)

## 许可

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本教程由[欧长坤](https://github.com/changkun)撰写，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](https://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../../LICENSE)。
