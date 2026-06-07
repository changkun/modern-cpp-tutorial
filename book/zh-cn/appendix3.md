---
title: 附录 3：现代 C++ 特性索引
type: book-zh-cn
order: 15
---

# 附录 3：现代 C++ 特性索引

本附录按标准版本归纳了本书介绍的主要特性，并标注了它们所在的章节，便于你「按版本查阅」或日后快速定位某个特性。如果你已经熟悉某个版本之前的内容，可以直接跳到对应的小节。

## C++11 / C++14

| 特性 | 所在章节 |
|:----|:--------|
| `nullptr` | 第 2 章 |
| `constexpr`（C++14 放宽） | 第 2 章 |
| 初始化列表 `std::initializer_list` | 第 2 章 |
| `auto` 类型推导 | 第 2 章 |
| `decltype` / `decltype(auto)`（C++14） | 第 2 章 |
| 尾返回类型 | 第 2 章 |
| 基于范围的 for 循环 | 第 2 章 |
| 外部模板、别名模板、默认模板参数、变长参数模板 | 第 2 章 |
| 委托构造、继承构造 | 第 2 章 |
| 显式 `override` / `final` | 第 2 章 |
| 显式 `= default` / `= delete` | 第 2 章 |
| 强类型枚举 `enum class` | 第 2 章 |
| SFINAE 与 `std::enable_if` | 第 2 章 |
| Lambda 表达式、泛型 Lambda（C++14） | 第 3 章 |
| `std::function`、`std::bind` | 第 3 章 |
| 右值引用、移动语义、完美转发 | 第 3 章 |
| `std::array`、`std::forward_list`、无序容器、`std::tuple` | 第 4 章 |
| 智能指针 `shared_ptr` / `unique_ptr` / `weak_ptr`、`make_unique`（C++14） | 第 5 章 |
| 正则表达式 `std::regex` | 第 6 章 |
| 线程、互斥量、期物、条件变量、原子与内存模型 | 第 7 章 |
| `long long`、`noexcept`、原始/自定义字面量、内存对齐 | 第 9 章 |

## C++17

| 特性 | 所在章节 |
|:----|:--------|
| 结构化绑定 | 第 2 章 |
| `if` / `switch` 初始化语句 | 第 2 章 |
| `if constexpr` | 第 2 章 |
| 折叠表达式、非类型模板参数的 `auto` 推导 | 第 2 章 |
| 内联变量、嵌套命名空间、`constexpr` lambda | 第 2 章 |
| 单参数 `static_assert`、新的聚合规则 | 第 2 章 |
| 布尔逻辑元函数、`__has_include` | 第 2 章 |
| 强制复制消除 | 第 3 章 |
| `std::string_view`、`std::byte` | 第 4 章 |
| 关联容器的改进（`try_emplace` / `merge` 等）、多态分配器 `std::pmr` | 第 4 章 |
| `std::filesystem` | 第 8 章 |
| 过对齐类型的 `new` | 第 9 章 |
| 数学特殊函数 | 第 9 章 |

## C++20

| 特性 | 所在章节 |
|:----|:--------|
| 概念与约束（Concepts） | 第 10 章 |
| 模块（Modules） | 第 10 章 |
| 范围（Ranges） | 第 10 章 |
| 协程（Coroutines） | 第 10 章 |
| `std::bit_cast` | 第 9 章 |

## C++23

| 特性 | 所在章节 |
|:----|:--------|
| 显式对象形参（Deducing this） | 第 11 章 |
| `if consteval`、多维下标运算符 | 第 11 章 |
| `auto(x)`、静态 `operator()`、`[[assume]]` | 第 11 章 |
| `std::expected` | 第 11 章 |
| `std::print` / `std::println` | 第 11 章 |
| `std::mdspan`、`std::flat_map` / `std::flat_set` | 第 11 章 |
| 范围库的增强（`zip` 等）、`string::contains`、`std::byteswap` | 第 11 章 |

## C++26（展望）

| 特性 | 所在章节 |
|:----|:--------|
| 静态反射（Reflection） | 第 12 章 |
| 契约（Contracts） | 第 12 章 |
| 形参包索引、带原因的 `= delete`、占位符 `_` | 第 12 章 |
| `std::execution`（发送者 / 接收者） | 第 12 章 |
| 饱和算术 | 第 12 章 |

[返回目录](./toc.md) | [上一章](./appendix2.md)

## 许可

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本教程由[欧长坤](https://github.com/changkun)撰写，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](https://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../../LICENSE)。
