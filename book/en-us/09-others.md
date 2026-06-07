---
title: Chapter 09: Minor Features
type: book-en-us
order: 9
---

# Chapter 09: Minor Features

[TOC]

## 9.1 New Type

*(since C++11)*

### `long long int`

`long long int` is not the first to be introduced in C++11.
As early as C99, `long long int` has been included in the C standard,
so most compilers already support it.
C++11 now formally incorporate it into the standard library,
specifying a `long long int` type with at least 64 bits.

## 9.2 `noexcept` and Its Operations

*(since C++11)*

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

If a function marked `noexcept` performs an operation that possibly throws an exception,
the compiler will insert a `std::terminate()` call to the path exiting the function via an exception,
in order to make the program terminate.

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

*(since C++11)*

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

*(since C++11)*

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

### Dynamic allocation of over-aligned types

Before C++17, a `new` expression could not guarantee the alignment requirement of an **over-aligned** type (one whose alignment exceeds `alignof(std::max_align_t)`); using such types often required platform-specific facilities such as `posix_memalign` or `_aligned_malloc`. C++17 introduced `operator new` / `operator delete` overloads taking a `std::align_val_t`, so a `new` expression automatically selects the aligned version when allocating an over-aligned type:

```cpp
struct alignas(64) Aligned {
    double v[8];
};

Aligned* p = new Aligned; // C++17: automatically uses the aligned operator new
// now reinterpret_cast<std::uintptr_t>(p) % 64 == 0
delete p;
```

## 9.5 Type punning and `std::bit_cast`

*(since C++20)*

"Type punning" means reinterpreting the same memory as a different type, common in low-level code (e.g. reading the bit pattern of a floating-point number). Many people reach for `reinterpret_cast` through a pointer or reference:

```cpp
float f = 3.14f;
std::uint32_t bits = *reinterpret_cast<std::uint32_t*>(&f); // undefined behavior!
```

But this violates the **strict-aliasing rule**: except through `char`, `unsigned char`, or `std::byte`, accessing an object via an lvalue of a type incompatible with the object's actual type is undefined behavior, and the optimizer is free to assume it never happens.

The correct, portable approach is `std::memcpy` (valid under any standard):

```cpp
std::uint32_t bits;
std::memcpy(&bits, &f, sizeof bits); // well-defined
```

C++20 further provides `std::bit_cast` (in `<bit>`), which reinterprets the object representation in a well-defined way with clearer semantics and can be used in constant expressions:

```cpp
#include <bit>
auto bits = std::bit_cast<std::uint32_t>(f); // both types must be the same size and trivially copyable
float back = std::bit_cast<float>(bits);
```

## 9.6 Mathematical special functions

*(since C++17)*

C++17 added a set of mathematical special functions to `<cmath>` — such as `std::riemann_zeta`, `std::beta`, `std::assoc_legendre`, and `std::cyl_bessel_j` — useful in scientific computing and machine-learning related domains:

```cpp
#include <cmath>
double z = std::riemann_zeta(2.0); // ~ 1.6449 (i.e. pi^2 / 6)
```

> Note that although these special functions are part of the standard, **standard-library support varies**: libstdc++ (GCC) provides a complete implementation, while libc++ (Clang) did not implement them for a long time. The code above therefore may not compile on every toolchain; check your standard library's support before using them.

## Conclusion

Several of the features introduced in this section are those that
use more frequent features from modern C++ features that
have not yet been introduced. `noexcept` is the most important feature.
One of its features is to prevent the spread of anomalies,
effective Let the compiler optimize our code to the maximum extent possible.

[Table of Content](./toc.md) | [Previous Chapter](./08-filesystem.md) | [Next Chapter: C++20](./10-cpp20.md)

## Licenses

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).
