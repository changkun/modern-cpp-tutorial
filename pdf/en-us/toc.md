# C++ 11/14/17 On The Fly

> This book adapting to C++17 and translating to English

## Table of Contents

- [**Preface**](./00-preface.md)
- [**Chapter 01 Towards C++11/14/17**](./01-intro.md)
    + 1.1 Deprecated Features
    + 1.2 Compatibility with C
    + Further Readings
- [**Chapter 02 Language Usability Enhancements**](./02-usability.md)
    + 2.1 Constants
      - nullptr
      - constexpr
    + 2.2 Variables & Initialization
      - Conditional Statement
      - Initializer List
      - Structured binding
    + 2.3 Type Deduction
      - auto
      - decltype
      - Tail return type
      - decltype(auto)
    + 2.4 Control Flow
      - if constexpr
      - Range-based for loop
    + 2.5 Templates
      - External templates
      - The ">"
      - Type alias templates
      - Default template parameters
      - Variadic templates
      - Fold expression
    + 2.6 Object-oriented
      - Delegate constructor
      - Inheritance constructor
      - Explicit virtual function overwrite
      - override
      - final
      - Explicit delete default function
      - Strongly typed enumerations
- [**Chapter 03 Language Runtime Enhancements**](./03-runtime.md)
    + Lambda expression
        + Basics
            + Value capture
            + Reference capture
            + Implicit capture
            + Expression capture
        + Generic lambda
    + Function object wrapper
        + std::function
        + std::bind/std::placeholder
    + rvalue reference
        + lvalue, rvalue, prvalue, xvalue
        + rvalue reference & lvalue reference
        + Move semantics
        + Perfect forwarding
- [**Chapter 04 Sandard Library: Containers**](./04-containers.md)
    + `std::array`
    + `std::forward_list`
    + `std::unordered_set`
    + `std::unordered_map`
    + `std::tuple`
        + basic operation
        + runtime indexing
        + merge and iteration
- [**Chapter 05 Sandard Library: Pointers**](./05-pointers.md)
    + RAII and reference counting
    + `std::shared_ptr`
    + `std::unique_ptr`
    + `std::weak_ptr`
- [**Chapter 06 Sandard Library: Regular Expression**](./06-regex.md)
    + Regular Expression Introduction
        + Normal characters
        + Special characters
        + Determinative
    + `std::regex`
        + `std::regex`
        + `std::regex_match`
        + `std::match_results`
- [**Chapter 07 Sandard Library: Threads and Concurrency**](./07-thread.md)
    + `std::thread`
    + `std::mutex`
    + `std::unique_lock`
    + `std::future`
    + `std::packaged_task`
    + `std::condition_variable`
- [**Chapter 08 Sandard Library: File System**](./08-filesystem.md)
- [**Chapter 09 Minor Features**](./09-others.md)
    + New Types
        + `long long int`
    + `noexcept`
    + Literal
        + Raw string literal
        + Custom string literal
    + Math Library
- [**Chapter 10 Outlook: Introduction of C++20**](./10-cpp20.md)
    + Concept
    + Range
    + Module
    + Coroutine
- [**Appendix: Further Study Materials**](./appendix.md)

Table of Content | Last Chapter | [Next Chapter: Preface](./00-preface.md)

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work is written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](./LICENSE).