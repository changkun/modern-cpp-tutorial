---
title: Chapter 09 Minor Features
type: book-en-us
order: 9
---

# Chapter 09 Minor Features

[TOC]

## 9.1 New Type

### `long long int`

`long long int` is not the first to be introduced in C++11.
As early as C99, `long long int` has been included in the C standard,
so most compilers already support it.
C++11 now formally incorporate it into the standard library,
specifying a `long long int` type with at least 64 bits.

## 9.2 `noexcept` and Its Operations

One of the big advantages of C++ over C is that
C++ itself defines a complete set of exception handling mechanisms.
However, before C++11, almost no one used to write an exception declaration expression after the function name.
Starting from C++11, this mechanism was deprecated,
so we will not discuss or introduce the previous mechanism.
How to work and how to use it, you should not take the initiative to understand it.

C++11 simplifies exception declarations into two cases:

1. The function may throw any exceptions
2. The function can't throw any exceptions

And use `noexcept` to limit these two behaviors, for example:

```cpp
void may_throw();           // May throw any exception
void no_throw() noexcept;   // Cannot throw any exception
```

If a function modified with `noexcept` is thrown,
the compiler will use `std::terminate()` to
immediately terminate the program.

`noexcept` can also be used as an operator to manipulate an expression.
When the expression has no exception, it returns `true`,
otherwise, it returns `false`.

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

`noexcept` can modify the function of blocking exceptions
after modifying a function. If an exception is generated internally,
the external will not trigger. For instance:

```cpp
try {
    may_throw();
} catch (...) {
    std::cout << "exception captured from may_throw()" << std::endl;
}
try {
    non_block_throw();
} catch (...) {
    std::cout << "exception captured from non_block_throw()" << std::endl;
}
try {
    block_throw();
} catch (...) {
    std::cout << "exception captured from block_throw()" << std::endl;
}
```

The final output is:

```
exception captured, from may_throw()
exception captured, from non_block_throw()
```

## 9.3 Literal

### Raw String Literal

In traditional C++, it is very painful to write a string full of
special characters. For example, a string containing HTML ontology
needs to add a large number of escape characters.
For example, a file path on Windows often as: `C:\\Path\\To\\File`.

C++11 provides the original string literals,
which can be decorated with `R` in front of a string,
and the original string is wrapped in parentheses, for example:

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = R"(C:\Path\To\File)";
    std::cout << str << std::endl;
    return 0;
}
```

### Custom Literal

C++11 introduces the ability to customize literals by
overloading the double quotes suffix operator:

```cpp
// String literal customization must be set to the following parameter list
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

Custom literals support four literals:

1. Integer literal: When overloading, you must use `unsigned long long`, `const char *`, and template literal operator parameters. The former is used in the above code;
2. Floating-point literals: You must use `long double`, `const char *`, and template literals when overloading;
3. String literals: A parameter table of the form `(const char *, size_t)` must be used;
4. Character literals: Parameters can only be `char`, `wchar_t`, `char16_t`, `char32_t`.

## 9.4 Memory Alignment

C++ 11 introduces two new keywords, `alignof` and `alignas`, to support control of memory alignment.
The `alignof` keyword can get a platform-dependent value of type `std::size_t` to query the alignment of the platform.
Of course, we are sometimes not satisfied with this, and even want to customize the alignment of the structure. Similarly, C++ 11 introduces `alignas`.
To reshape the alignment of a structure. Let's look at two examples:

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

where `std::max_align_t` requires the same alignment for each scalar type, so it has almost no difference in maximum scalars.
In turn, the result on most platforms is `long double`, so the alignment requirement for `AlignasStorage` we get here is 8 or 16.

## Conclusion

Several of the features introduced in this section are those that
use more frequent features from modern C++ features that
have not yet been introduced. `noexcept` is the most important feature.
One of its features is to prevent the spread of anomalies,
effective Let the compiler optimize our code to the maximum extent possible.

[Table of Content](./toc.md) | [Previous Chapter](./08-filesystem.md) | [Next Chapter: Outlook: Introduction of C++20](./10-cpp20.md)

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).
