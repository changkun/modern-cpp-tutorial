# 高速上手现代 C++ 11/14/17

> 正在向全面介绍 C++17 特性的内容过度

## 目录

- [**序言**](./0-preface.md)
- [**第 1 章 迈向 C++11/14/17**](./1-intro.md)
    + 1.1 被弃用的特性
    + 1.2 与 C 的兼容性
    + 进一步阅读的参考文献
- **第二章 语言可用性的强化**
    + `nullptr` 与 `constexpr`
    + 类型推导
        + `auto`
        + `decltype`
        + 尾返回类型、`auto` 与 `decltype` 配合

        <!--+ decltype(auto) (C++14)-->

    + 区间迭代
        + 基于范围的 for 循环
    + 初始化列表
        + `std::initializer_list`
        + 统一初始化语法
    + 模板增强
        + 外部模板
        + 尖括号 `>` 
        + 类型别名模板
        + 变长参数模板
    + 面向对象增强
        + 委托构造
        + 继承构造
        + 显式虚函数重载
            + `override`
            + `final`
        + 显式禁用默认函数
    + 强类型枚举
- **第三章 语言运行期的强化**
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
- **第四章 对标准库的扩充: 新增容器**
    + `std::array`
    + `std::forward_list`
    + `std::unordered_set`
    + `std::unordered_map`
    + `std::tuple`
        + 基本操作
        + 运行期索引
        + 合并与迭代
- **第五章 对标准库的扩充: 智能指针和引用计数**
    + RAII 与引用计数
    + `std::shared_ptr`
    + `std::unique_ptr`
    + `std::weak_ptr`
- **第六章 对标准库的扩充: 正则表达式库**
    + 正则表达式简介
        + 普通字符
        + 特殊字符
        + 限定符
    + `std::regex` 及其相关
        + `std::regex`
        + `std::regex_match`
        + `std::match_results`
- **第七章 对标准库的扩充: 语言级线程支持**
    + `std::thread`
    + `std::mutex`
    + `std::unique_lock`
    + `std::future`
    + `std::packaged_task`
    + `std::condition_variable`
- **第八章 其他杂项**
    + 新类型
        + `long long int`
    + `noexcept` 的修饰和操作
    + 字面量
        + 原始字符串字面量
        + 自定义字面量
- **第九章 扩展主题: C++17 简介**
    + 主要入选特性
        + 非类型模板参数的 `auto` 
        + `std::variant<>`
        + 结构化绑定(Structured bindings)
        + 变量声明的强化
    + 未入选特性
        + Concepts

返回目录 | 上一章 | [下一章：序言](./0-preface.md)

## 许可

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本书系[欧长坤](https://github.com/changkun)著，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](http://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../LICENSE)。