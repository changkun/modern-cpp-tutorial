---
title: "Chapter 04 Containers"
type: book-en-us
order: 4
---

# Chapter 04 Containers

[TOC]

## 4.1 Linear Container

### `std::array`

When you see this container, you will have this problem:

1. Why introduce `std::array` instead of `std::vector` directly?
2. Already have a traditional array, why use `std::array`?

First, answer the first question. Unlike `std::vector`, the size of the `std::array` object is fixed. If the container size is fixed, then the `std::array` container can be used first.
Also, since `std::vector` is automatically expanded, when a large amount of data is stored, and the container is deleted,
The container does not automatically return the corresponding memory of the deleted element. In this case, you need to manually run `shrink_to_fit()` to release this part of the memory.

```cpp
std::vector<int> v;
std::cout << "size:" << v.size() << std::endl;         // output 0
std::cout << "capacity:" << v.capacity() << std::endl; // output 0

// As you can see, the storage of std::vector is automatically managed and
// automatically expanded as needed.
// But if there is not enough space, you need to redistribute more memory,
// and reallocating memory is usually a performance-intensive operation.
v.push_back(1);
v.push_back(2);
v.push_back(3);
std::cout << "size:" << v.size() << std::endl;         // output 3
std::cout << "capacity:" << v.capacity() << std::endl; // output 4

// The auto-expansion logic here is very similar to Golang's slice.
v.push_back(4);
v.push_back(5);
std::cout << "size:" << v.size() << std::endl;         // output 5
std::cout << "capacity:" << v.capacity() << std::endl; // output 8

// As can be seen below, although the container empties the element,
// the memory of the emptied element is not returned.
v.clear();
std::cout << "size:" << v.size() << std::endl;         // output 0
std::cout << "capacity:" << v.capacity() << std::endl; // output 8

// Additional memory can be returned to the system via the shrink_to_fit() call
v.shrink_to_fit();
std::cout << "size:" << v.size() << std::endl;         // output 0
std::cout << "capacity:" << v.capacity() << std::endl; // output 0
```

The second problem is much simpler. Using `std::array` can make the code more "modern" and encapsulate some manipulation functions, such as getting the array size and checking if it is not empty, and also using the standard friendly. Container algorithms in the library, such as `std::sort`.

Using `std::array` is as simple as specifying its type and size:

```cpp
std::array<int, 4> arr = {1, 2, 3, 4};

arr.empty(); // check if container is empty
arr.size();  // return the size of the container

// iterator support
for (auto &i : arr)
{
    // ...
}

// use lambda expression for sort
std::sort(arr.begin(), arr.end(), [](int a, int b) {
    return b < a;
});

// array size must be constexpr
constexpr int len = 4;
std::array<int, len> arr = {1, 2, 3, 4};

// illegal, different than C-style array, std::array will not deduce to T*
// int *arr_p = arr;
```

When we started using `std::array`, it was inevitable that we would encounter a C-style compatible interface. There are three ways to do this:

```cpp
void foo(int *p, int len) {
    return;
}

std::array<int, 4> arr = {1,2,3,4};

// C-stype parameter passing
// foo(arr, arr.size()); // illegal, cannot convert implicitly
foo(&arr[0], arr.size());
foo(arr.data(), arr.size());

// use `std::sort`
std::sort(arr.begin(), arr.end());
```

### `std::forward_list`

`std::forward_list` is a list container, and the usage is similar to `std::list`, so we don't spend a lot of time introducing it.

Need to know is that, unlike the implementation of the doubly linked list of `std::list`, `std::forward_list` is implemented using a singly linked list.
Provides element insertion of `O(1)` complexity, does not support fast random access (this is also a feature of linked lists),
It is also the only container in the standard library container that does not provide the `size()` method. Has a higher space utilization than `std::list` when bidirectional iteration is not required.

## 4.2 Unordered Container

We are already familiar with the ordered container `std::map`/`std::set` in traditional C++. These elements are internally implemented by red-black trees.
The average complexity of inserts and searches is `O(log(size))`. When inserting an element, the element size is compared according to the `<` operator and the element is determined to be the same.
And select the appropriate location to insert into the container. When traversing the elements in this container, the output will be traversed one by one in the order of the `<` operator.

The elements in the unordered container are not sorted, and the internals is implemented by the Hash table. The average complexity of inserting and searching for elements is `O(constant)`,
Significant performance gains can be achieved without concern for the order of the elements inside the container.

C++11 introduces two sets of unordered containers: `std::unordered_map`/`std::unordered_multimap` and
`std::unordered_set`/`std::unordered_multiset`.

Their usage is basically similar to the original `std::map`/`std::multimap`/`std::set`/`set::multiset`
Since these containers are already familiar to us, we will not compare them one by one. Let's compare `std::map` and `std::unordered_map` directly:

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

int main() {
    // initialized in same order
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

    // iterates in the same way
    std::cout << "std::unordered_map" << std::endl;
    for( const auto & n : u)
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

    std::cout << std::endl;
    std::cout << "std::map" << std::endl;
    for( const auto & n : v)
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
}
```

The final output is:

```txt
std::unordered_map
Key:[2] Value:[2]
Key:[3] Value:[3]
Key:[1] Value:[1]

std::map
Key:[1] Value:[1]
Key:[2] Value:[2]
Key:[3] Value:[3]
```

## 4.3 Tuples

Programmers who have known Python should be aware of the concept of tuples. Looking at the containers in traditional C++, except for `std::pair`
there seems to be no ready-made structure to store different types of data (usually we will define the structure ourselves).
But the flaw of `std::pair` is obvious, only two elements can be saved.

### Basic Operations

There are three core functions for the use of tuples:

1. `std::make_tuple`: construct tuple
2. `std::get`: Get the value of a position in the tuple
3. `std::tie`: tuple unpacking

```cpp
#include <tuple>
#include <iostream>

auto get_student(int id) {
    if (id == 0)
        return std::make_tuple(3.8, 'A', "John");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "Jack");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "Ive");

    // it is not allowed to return 0 directly
    // return type is std::tuple<double, char, std::string>
    return std::make_tuple(0.0, 'D', "null");
}

int main() {
    auto student = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: "   << std::get<0>(student) << ", "
              << "Grade: " << std::get<1>(student) << ", "
              << "Name: "  << std::get<2>(student) << '\n';

    double gpa;
    char grade;
    std::string name;

    // unpack tuples
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: "   << gpa << ", "
              << "Grade: " << grade << ", "
              << "Name: "  << name << '\n';
}
```

`std::get` In addition to using constants to get tuple objects, C++14 adds usage types to get objects in tuples:

```cpp
std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
std::cout << std::get<std::string>(t) << std::endl;
std::cout << std::get<double>(t) << std::endl; // illegal, runtime error
std::cout << std::get<3>(t) << std::endl;
```

### Runtime Indexing

If you think about it, you might find the problem with the above code. `std::get<>` depends on a compile-time constant, so the following is not legal:

```cpp
int index = 1;
std::get<index>(t);
```

So what do you do? The answer is to use `std::variant<>` (introduced by C++ 17) to provide type template parameters for `variant<>`
You can have a `variant<>` to accommodate several types of variables provided (in other languages, such as Python/JavaScript, etc., as dynamic types):

```cpp
#include <variant>
template <size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...>& tpl, size_t i) {
    if constexpr (n >= sizeof...(T))
        throw std::out_of_range("越界.");
    if (i == n)
        return std::variant<T...>{ std::in_place_index<n>, std::get<n>(tpl) };
    return _tuple_index<(n < sizeof...(T)-1 ? n+1 : 0)>(tpl, i);
}
template <typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
    return _tuple_index<0>(tpl, i);
}
template <typename T0, typename ... Ts>
std::ostream & operator<< (std::ostream & s, std::variant<T0, Ts...> const & v) {
    std::visit([&](auto && x){ s << x;}, v);
    return s;
}
```

So we can:

```cpp
int i = 1;
std::cout << tuple_index(t, i) << std::endl;
```

### Merge and Iteration

Another common requirement is to merge two tuples, which can be done with `std::tuple_cat`:

```cpp
auto new_tuple = std::tuple_cat(get_student(1), std::move(t));
```

You can immediately see how quickly you can traverse a tuple? But we just introduced how to index a `tuple` by a very number at runtime, then the traversal becomes simpler.
First, we need to know the length of a tuple, which can:

```cpp
template <typename T>
auto tuple_len(T &tpl) {
    return std::tuple_size<T>::value;
}
```

This will iterate over the tuple:

```cpp
for(int i = 0; i != tuple_len(new_tuple); ++i)
    // runtime indexing
    std::cout << tuple_index(new_tuple, i) << std::endl;
```

## Conclusion

This chapter briefly introduces the new containers in modern C++. Their usage is similar to that of the existing containers in C++. It is relatively simple, and you can choose the containers you need to use according to the actual scene, to get better performance.

Although `std::tuple` is effective, the standard library provides limited functionality and there is no way to meet the requirements of runtime indexing and iteration. Fortunately, we have other methods that we can implement on our own.

[Table of Content](./toc.md) | [Previous Chapter](./03-runtime.md) | [Next Chapter: Smart Pointers and Memory Management](./05-pointers.md)

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).
