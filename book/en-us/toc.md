# C++ 11/14/17/20 On The Fly

## Table of Contents

- [**Preface**](./00-preface.md)
- [**Chapter 01 Towards Modern C++**](./01-intro.md)
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
      - Non-type template parameter deduction
    + 2.6 Object-oriented
      - Delegate constructor
      - Inheritance constructor
      - Explicit virtual function overwrite
      - override
      - final
      - Explicit delete default function
      - Strongly typed enumerations
- [**Chapter 03 Language Runtime Enhancements**](./03-runtime.md)
    + 3.1 Lambda expression
        + Basics
        + Generics
    + 3.2 Function object wrapper
        + std::function
        + std::bind/std::placeholder
    + 3.3 rvalue reference
        + lvalue, rvalue, prvalue, xvalue
        + rvalue reference and lvalue reference
        + Move semantics
        + Perfect forwarding
- [**Chapter 04 Containers**](./04-containers.md)
    + 4.1 Linear containers
        + `std::array`
        + `std::forward_list`
    + 4.2 Unordered containers
        + `std::unordered_set`
        + `std::unordered_map`
    + 4.3 Tuples `std::tuple`
        + basic operation
        + runtime indexing `std::variant`
        + merge and iteration
- [**Chapter 05 Smart Pointers and Memory Management**](./05-pointers.md)
    + 5.1 RAII and reference counting
    + 5.2 `std::shared_ptr`
    + 5.3 `std::unique_ptr`
    + 5.4 `std::weak_ptr`
- [**Chapter 06 Regular Expression**](./06-regex.md)
    + 6.1 Introduction
        + Ordinary characters
        + Special characters
        + Quantifiers
    + 6.2 `std::regex` and its related
        + `std::regex`
        + `std::regex_match`
        + `std::match_results`
- [**Chapter 07 Parallelism and Concurrency**](./07-thread.md)
    + 7.1 Basic of Parallelism
    + 7.2 Mutex and Critical Section
    + 7.3 Futures
    + 7.4 Condition Variable
    + 7.5 Atomic Operation and Memory Model
        + Atomic Operation
        + Consistency Model
        + Memory Orders
- [**Chapter 08 File System**](./08-filesystem.md)
    + 8.1 Documents and links
    + 8.2 `std::filesystem`
- [**Chapter 09 Minor Features**](./09-others.md)
    + 9.1 New Types
        + `long long int`
    + 9.2 `noexcept` and Its Operations
    + 9.3 Literal
        + Raw String Literal
        + Custom String Literal
    + 9.4 Memory Alignment
- [**Chapter 10 Outlook: Introduction of C++20**](./10-cpp20.md)
    + 10.1 Concept
    + 10.2 Range
    + 10.3 Module
    + 10.4 Coroutine
    + 10.5 Transaction Memory
- [**Appendix 1: Further Study Materials**](./appendix1.md)
- [**Appendix 2: Modern C++ Best Practices**](./appendix2.md)

Table of Content | Last Chapter | [Next Chapter: Preface](./00-preface.md)

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).