---
title: "Appendix 3: Modern C++ Feature Index"
type: book-en-us
order: 15
---

# Appendix 3: Modern C++ Feature Index

This appendix groups the main features covered in this book by standard version and notes the chapter where each appears, so you can browse "by version" or quickly locate a feature later. If you are already familiar with the content of a given version, feel free to jump straight to the section you need.

## C++11 / C++14

| Feature | Chapter |
|:--------|:--------|
| `nullptr` | Chapter 2 |
| `constexpr` (relaxed in C++14) | Chapter 2 |
| Initializer lists (`std::initializer_list`) | Chapter 2 |
| `auto` type deduction | Chapter 2 |
| `decltype` / `decltype(auto)` (C++14) | Chapter 2 |
| Tail return type | Chapter 2 |
| Range-based for loop | Chapter 2 |
| External / alias / default / variadic templates | Chapter 2 |
| Delegating and inheriting constructors | Chapter 2 |
| Explicit `override` / `final` | Chapter 2 |
| Explicit `= default` / `= delete` | Chapter 2 |
| Strongly-typed enums (`enum class`) | Chapter 2 |
| SFINAE and `std::enable_if` | Chapter 2 |
| Lambda expressions, generic lambdas (C++14) | Chapter 3 |
| `std::function`, `std::bind` | Chapter 3 |
| Rvalue references, move semantics, perfect forwarding | Chapter 3 |
| `std::array`, `std::forward_list`, unordered containers, `std::tuple` | Chapter 4 |
| Smart pointers `shared_ptr` / `unique_ptr` / `weak_ptr`, `make_unique` (C++14) | Chapter 5 |
| Regular expressions (`std::regex`) | Chapter 6 |
| Threads, mutexes, futures, condition variables, atomics & memory model | Chapter 7 |
| `long long`, `noexcept`, raw/user-defined literals, memory alignment | Chapter 9 |

## C++17

| Feature | Chapter |
|:--------|:--------|
| Structured bindings | Chapter 2 |
| `if` / `switch` init-statements | Chapter 2 |
| `if constexpr` | Chapter 2 |
| Fold expressions, `auto` non-type template parameters | Chapter 2 |
| Inline variables, nested namespaces, `constexpr` lambda | Chapter 2 |
| Single-argument `static_assert`, new aggregate rules | Chapter 2 |
| Boolean logic metafunctions, `__has_include` | Chapter 2 |
| Guaranteed copy elision | Chapter 3 |
| `std::string_view`, `std::byte` | Chapter 4 |
| Associative container improvements (`try_emplace` / `merge` …), `std::pmr` | Chapter 4 |
| `std::filesystem` | Chapter 8 |
| `new` for over-aligned types | Chapter 9 |
| Mathematical special functions | Chapter 9 |

## C++20

| Feature | Chapter |
|:--------|:--------|
| Concepts and constraints | Chapter 10 |
| Modules | Chapter 10 |
| Ranges | Chapter 10 |
| Coroutines | Chapter 10 |
| `std::bit_cast` | Chapter 9 |

## C++23

| Feature | Chapter |
|:--------|:--------|
| Deducing `this` (explicit object parameter) | Chapter 11 |
| `if consteval`, multidimensional subscript | Chapter 11 |
| `auto(x)`, static `operator()`, `[[assume]]` | Chapter 11 |
| `std::expected` | Chapter 11 |
| `std::print` / `std::println` | Chapter 11 |
| `std::mdspan`, `std::flat_map` / `std::flat_set` | Chapter 11 |
| Ranges additions (`zip` …), `string::contains`, `std::byteswap` | Chapter 11 |

## C++26 (outlook)

| Feature | Chapter |
|:--------|:--------|
| Static reflection | Chapter 12 |
| Contracts | Chapter 12 |
| Pack indexing, `= delete` with a reason, the placeholder `_` | Chapter 12 |
| `std::execution` (senders / receivers) | Chapter 12 |
| Saturation arithmetic | Chapter 12 |

[Table of Content](./toc.md) | [Previous Chapter](./appendix2.md)

## Licenses

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).
