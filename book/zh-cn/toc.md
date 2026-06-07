# 现代 C++ 教程：高速上手 C++11 到 C++26

## 目录

- [**序言**](./00-preface.md)
- [**第 1 章 迈向现代 C++**](./01-intro.md)
    + 1.1 被弃用的特性
    + 1.2 与 C 的兼容性
    + 进一步阅读的参考文献
- [**第 2 章 语言可用性的强化**](./02-usability.md)
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
      - 非类型模板参数推导
    + 2.6 面向对象
      - 委托构造
      - 继承构造
      - 显式虚函数重载
      - override
      - final
      - 显式禁用默认函数
      - 强类型枚举
- [**第 3 章 语言运行期的强化**](./03-runtime.md)
    + 3.1 lambda 表达式
        + 基础
        + 泛型
    + 3.2 函数对象包装器
        + std::function
        + std::bind 和 std::placeholder
    + 3.3 右值引用
        + 左值、右值的纯右值、将亡值、右值
        + 右值引用和左值引用
        + 移动语义
        + 完美转发
- [**第 4 章 标准库: 容器**](./04-containers.md)
    + 4.1 线性容器
        + `std::array`
        + `std::forward_list`
    + 4.2 无序容器
        + `std::unordered_set`
        + `std::unordered_map`
    + 4.3 元组 `std::tuple`
        + 基本操作
        + 运行期索引 `std::variant`
        + 合并与迭代
- [**第 5 章 标准库: 指针**](./05-pointers.md)
    + 5.1 RAII 与引用计数
    + 5.2 `std::shared_ptr`
    + 5.3 `std::unique_ptr`
    + 5.4 `std::weak_ptr`
- [**第 6 章 标准库: 正则表达式**](./06-regex.md)
    + 6.1 正则表达式简介
        + 普通字符
        + 特殊字符
        + 限定符
    + 6.2 `std::regex` 及其相关
        + `std::regex`
        + `std::regex_match`
        + `std::match_results`
- [**第 7 章 并行与并发**](./07-thread.md)
    + 7.1 并行基础
    + 7.2 互斥量与临界区
    + 7.3 期物
    + 7.4 条件变量
    + 7.5 原子操作与内存模型
        + 原子操作
        + 一致性模型
        + 内存顺序
- [**第 8 章 文件系统**](./08-filesystem.md)
    + 8.1 文档与链接
    + 8.2 `std::filesystem`
- [**第 9 章 其他杂项**](./09-others.md)
    + 9.1 新类型
        + `long long int`
    + 9.2 `noexcept` 的修饰和操作
    + 9.3 字面量
        + 原始字符串字面量
        + 自定义字面量
    + 9.4 内存对齐
- [**第 10 章 C++20**](./10-cpp20.md)
    + 10.1 概念与约束
    + 10.2 模块
    + 10.3 范围
    + 10.4 协程
- [**第 11 章 C++23**](./11-cpp23.md)
    + 11.1 语言特性
      - 显式对象形参（Deducing this）
      - if consteval
      - 多维下标运算符
      - auto(x) 与静态 operator()
      - [[assume]]
    + 11.2 标准库
      - std::expected
      - std::print 与 std::println
      - std::mdspan
      - std::flat_map 与 std::flat_set
      - 范围库的增强
- [**第 12 章 C++26（展望）**](./12-cpp26.md)
    + 12.1 语言特性
      - 静态反射（Reflection）
      - 契约（Contracts）
      - 形参包索引
      - 带原因的 = delete
      - 占位符 _
    + 12.2 标准库
      - std::execution
      - 饱和算术
      - 其他库设施
- [**附录 1：进一步阅读的学习材料**](./appendix1.md)
- [**附录 2：现代 C++ 的最佳实践**](./appendix2.md)
- [**附录 3：现代 C++ 特性索引**](./appendix3.md)

返回目录 | 上一章 | [下一章：序言](./00-preface.md)

## 许可

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本书系[欧长坤](https://github.com/changkun)著，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](https://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../../LICENSE)。
