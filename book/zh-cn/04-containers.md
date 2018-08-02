---
title: 第 4 章 标准库：容器
type: book-zh-cn
order: 4
---

# 第 4 章 标准库：容器

> 内容修订中

[TOC]

## 4.1 std::array 和 std::forward\_list

### std::array

看到这个容器的时候肯定会出现这样的问题：

1. 为什么要引入 `std::array` 而不是直接使用 `std::vector`？
2. 已经有了传统数组，为什么要用 `std::array`?

先回答第一个问题，`std::vector` 太强大了，以至于我们没有必要为了去敲碎一个鸡蛋而用一个钉锤。使用 `std::array` 保存在栈内存中，相比堆内存中的 `std::vector`，我们就能够灵活的访问这里面的元素，从而获得更高的性能；同时正式由于其堆内存存储的特性，有些时候我们还需要自己负责释放这些资源。

而第二个问题就更加简单，使用`std::array`能够让代码变得更加现代，且封装了一些操作函数，同时还能够友好的使用标准库中的容器算法等等，比如 `std::sort`。

`std::array` 会在编译时创建一个固定大小的数组，`std::array` 不能够被隐式的转换成指针，使用 `std::array` 很简单，只需指定其类型和大小即可：

```cpp
std::array<int, 4> arr= {1,2,3,4};

int len = 4;
std::array<int, len> arr = {1,2,3,4}; // 非法, 数组大小参数必须是常量表达式
```

当我们开始用上了 `std::array` 时，难免会遇到要将其兼容 C 风格的接口，这里有三种做法：

```cpp
void foo(int *p, int len) {
    return;
}

std::array<int, 4> arr = {1,2,3,4};

// C 风格接口传参
// foo(arr, arr.size()); // 非法, 无法隐式转换
foo(&arr[0], arr.size());
foo(arr.data(), arr.size());

// 使用 `std::sort`
std::sort(arr.begin(), arr.end());
```

### std::forward\_list

`std::forward_list` 是一个列表容器，使用方法和 `std::list` 基本类似，因此我们就不花费篇幅进行介绍了。

需要知道的是，和 `std::list` 的双向链表的实现不同，`std::forward_list` 使用单向链表进行实现，提供了 `O(1)` 复杂度的元素插入，不支持快速随机访问（这也是链表的特点），也是标准库容器中唯一一个不提供 `size()` 方法的容器。当不需要双向迭代时，具有比 `std::list` 更高的空间利用率。

## 4.2 无序容器

我们已经熟知了传统 C++ 中的有序容器 `std::map`/`std::set`，这些元素内部通过红黑树进行实现，插入和搜索的平均复杂度均为 `O(log(size))`。在插入元素时候，会根据 `<` 操作符比较元素大小并判断元素是否相同，并选择合适的位置插入到容器中。当对这个容器中的元素进行遍历时，输出结果会按照 `<` 操作符的顺序来逐个遍历。

而无序容器中的元素是不进行排序的，内部通过 Hash 表实现，插入和搜索元素的平均复杂度为 `O(constant)`，在不关心容器内部元素顺序时，能够获得显著的性能提升。

C++11 引入了两组无序容器：`std::unordered_map`/`std::unordered_multimap` 和 `std::unordered_set`/`std::unordered_multiset`。

它们的用法和原有的 `std::map`/`std::multimap`/`std::set`/`set::multiset` 基本类似，由于这些容器我们已经很熟悉了，便不一一举例，我们直接来比较一下`std::map`和`std::unordered_map`：

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

int main() {
    // 两组结构按同样的顺序初始化
    std::unordered_map<int, std::string> u = {
        {1, "1"},
        {3, "3"},
        {2, "2"}
    };
    std::map<int, std::string> v = {
        {1, "1"},
        {3, "3"},
        {2, "2"}
    };

    // 分别对两组结构进行遍历
    std::cout << "std::unordered_map" << std::endl;
    for( const auto & n : u)
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

    std::cout << std::endl;
    std::cout << "std::map" << std::endl;
    for( const auto & n : v)
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
}
```

最终的输出结果为：

```
std::unordered_map
Key:[2] Value:[2]
Key:[3] Value:[3]
Key:[1] Value:[1]

std::map
Key:[1] Value:[1]
Key:[2] Value:[2]
Key:[3] Value:[3]
```

## 4.3 元组 std::tuple

了解过 Python 的程序员应该知道元组的概念，纵观传统 C++ 中的容器，除了 `std::pair` 外，似乎没有现成的结构能够用来存放不同类型的数据（通常我们会自己定义结构）。但 `std::pair` 的缺陷是显而易见的，只能保存两个元素。

### 元组基本操作

关于元组的使用有三个核心的函数：

1. `std::make_tuple`: 构造元组
2. `std::get`: 获得元组某个位置的值
3. `std::tie`: 元组拆包

```cpp
#include <tuple>
#include <iostream>

auto get_student(int id)
{
// 返回类型被推断为 std::tuple<double, char, std::string>

if (id == 0)
    return std::make_tuple(3.8, 'A', "张三");
if (id == 1)
    return std::make_tuple(2.9, 'C', "李四");
if (id == 2)
    return std::make_tuple(1.7, 'D', "王五");
    return std::make_tuple(0.0, 'D', "null");
    // 如果只写 0 会出现推断错误, 编译失败
}

int main()
{
    auto student = get_student(0);
    std::cout << "ID: 0, "
    << "GPA: " << std::get<0>(student) << ", "
    << "成绩: " << std::get<1>(student) << ", "
    << "姓名: " << std::get<2>(student) << '\n';

    double gpa;
    char grade;
    std::string name;

    // 元组进行拆包
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
    << "GPA: " << gpa << ", "
    << "成绩: " << grade << ", "
    << "姓名: " << name << '\n';
}
```

`std::get` 除了使用常量获取元组对象外，C++14 增加了使用类型来获取元组中的对象：

```cpp
std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
std::cout << std::get<std::string>(t) << std::endl;
std::cout << std::get<double>(t) << std::endl; // 非法, 引发编译期错误
std::cout << std::get<3>(t) << std::endl;
```

### 运行期索引

如果你仔细思考一下可能就会发现上面代码的问题，`std::get<>` 依赖一个编译期的常量，所以下面的方式是不合法的：

```cpp
int index = 1;
std::get<index>(t);
```

那么要怎么处理？答案是，**标准库做不到**。这里介绍一个使用 `boost::variant` 配合变长模板参数的黑魔法：

```cpp
#include <boost/variant.hpp>
template <size_t n, typename... T>
boost::variant<T...> _tuple_index(size_t i, const std::tuple<T...>& tpl) {
if (i == n)
    return std::get<n>(tpl);
else if (n == sizeof...(T) - 1)
    throw std::out_of_range("越界.");
else
    return _tuple_index<(n < sizeof...(T)-1 ? n+1 : 0)>(i, tpl);
}
template <typename... T>
boost::variant<T...> tuple_index(size_t i, const std::tuple<T...>& tpl) {
    return _tuple_index<0>(i, tpl);
}
```

这样我们就能：

```cpp
int i = 1;
std::cout << tuple_index(i, t) << std::endl;
```

### 元组合并与遍历

还有一个常见的需求就是合并两个元组，这可以通过 `std::tuple_cat` 来实现：

```cpp
auto new_tuple = std::tuple_cat(get_student(1), std::move(t));
```

马上就能够发现，应该如何快速遍历一个元组？但是我们刚才介绍了如何在运行期通过非常数索引一个 `tuple` 那么遍历就变得简单了，首先我们需要知道一个元组的长度，可以：

```cpp
template <typename T>
auto tuple_len(T &tpl) {
    return std::tuple_size<T>::value;
}
```

这样就能够对元组进行迭代了：

```cpp
// 迭代
for(int i = 0; i != tuple_len(new_tuple); ++i)
    // 运行期索引
    std::cout << tuple_index(i, new_tuple) << std::endl;
```

## 总结

本节简单介绍了 C++11/14 中新增的容器，它们的用法和传统 C++ 中已有的容器类似，相对简单，可以根据实际场景丰富的选择需要使用的容器，从而获得更好的性能。

`std::tuple` 虽然有效，但是标准库提供的功能有限，没办法满足运行期索引和迭代的需求，好在我们还有其他的方法可以自行实现。

[返回目录](./toc.md) | [上一章](./03-runtime.md) | [下一章 标准库：指针](./05-pointers.md)

## 许可

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

本教程由[欧长坤](https://github.com/changkun)撰写，采用[知识共享署名-非商业性使用-禁止演绎 4.0 国际许可协议](http://creativecommons.org/licenses/by-nc-nd/4.0/)许可。项目中代码使用 MIT 协议开源，参见[许可](../../LICENSE)。
