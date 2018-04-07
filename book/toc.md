# 高速上手 C++ 11/14/17

> 正在向全面介绍 C++17 特性的内容过度

## 目录

- [**序言**](./0-preface.md)
- [**第 1 章 迈向 C++11/14/17**](./1-intro.md)
    + 1.1 被弃用的特性
    + 1.2 与 C 的兼容性
    + 进一步阅读的参考文献
- [**第二章 语言可用性的强化**](./2-usability.md)
    + 2.1 常量
      - nullptr
      - constexpr
    + 2.2 变量及其初始化
      - if/switch 变量声明强化
      - 初始化列表
      - 结构化绑定
    + 2.3 类型推导
      - auto
      - decltype
      - 尾返回类型
      - decltype(auto)
    + 2.4 控制流
      - if constexpr
      - 区间 for 迭代
    + 2.5 模板
      - 外部模板
      - 尖括号 ">"
      - 类型别名模板
      - 默认模板参数
      - 变长参数模板
      - 折叠表达式
    + 2.6 面向对象
      - 委托构造
      - 继承构造
      - 显式虚函数重载
      - override
      - final
      - 显式禁用默认函数
      - 强类型枚举
- [**第三章 语言运行期的强化**](./3-runtime.md)
    + lambda 表达式
        + lambda 表达式基础
            + 值捕获
            + 引用捕获
            + 隐式捕获
            + 表达式捕获
        + 泛型 lambda
    + 函数对象包装器
        + std::function
        + std::bind/std::placeholder
    + 右值引用
        + 左值、右值的纯右值、将亡值、右值
        + 右值引用和左值引用
        + 移动语义
        + 完美转发
- [**第四章 标准库: 容器**](./4-containers.md)
    + `std::array`
    + `std::forward_list`
    + `std::unordered_set`
    + `std::unordered_map`
    + `std::tuple`
        + 基本操作
        + 运行期索引
        + 合并与迭代
- [**第五章 标准库: 指针**](./5-pointers.md)
    + RAII 与引用计数
    + `std::shared_ptr`
    + `std::unique_ptr`
    + `std::weak_ptr`
- [**第六章 标准库: 正则表达式**](./6-regex.md)
    + 正则表达式简介
        + 普通字符
        + 特殊字符
        + 限定符
    + `std::regex` 及其相关
        + `std::regex`
        + `std::regex_match`
        + `std::match_results`
- [**第七章 标准库: 线程与并发**](./7-thread.md)
    + `std::thread`
    + `std::mutex`
    + `std::unique_lock`
    + `std::future`
    + `std::packaged_task`
    + `std::condition_variable`
- [**第八章 标准库: 文件系统**](./8-filesystem.md)
- [**第九章 其他杂项**](./9-others.md)
    + 新类型
        + `long long int`
    + `noexcept` 的修饰和操作
    + 字面量
        + 原始字符串字面量
        + 自定义字面量
    + 数学库
- [**第十章 展望: C++20 简介**](./10-cpp20.md)
    + Concept
    + Range
    + Module
    + Coroutine


返回目录 | 上一章 | [下一章：序言](./0-preface.md)

## 许可

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本书系[欧长坤](https://github.com/changkun)著，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](http://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../LICENSE)。