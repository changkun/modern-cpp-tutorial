---
title: "Appendix 2: Modern C++ Best Practices"
type: book-en-us
order: 14
---

# Appendix 2: Modern C++ Best Practices

In this appendix we briefly discuss the best practices of modern C++. Many of these ideas are distilled from [Effective Modern C++](https://www.amazon.com/dp/1491903996/) and the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html), as well as the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) maintained by Bjarne Stroustrup and Herb Sutter. The goal of this appendix is to summarize widely accepted practices that help ensure the overall quality of your code.

## Common Tools

Good tooling catches a large class of problems before they ever reach production:

- **Enable warnings, and treat them as errors.** Compile with `-Wall -Wextra` (and consider `-Wpedantic`); `-Werror` keeps warnings from accumulating.
- **Run sanitizers during testing.** AddressSanitizer (`-fsanitize=address`), UndefinedBehaviorSanitizer (`-fsanitize=undefined`) and ThreadSanitizer (`-fsanitize=thread`) catch memory errors, undefined behavior, and data races at run time.
- **Format and lint automatically.** `clang-format` keeps style consistent, and `clang-tidy` flags bug-prone patterns and suggests modernizations.
- **Use a modern build system and package manager**, such as CMake together with vcpkg or Conan, to make builds reproducible.
- **Experiment quickly** with [Compiler Explorer](https://godbolt.org/) to inspect the generated assembly and compare compilers and standards.

## Coding Style

A consistent style makes a codebase far easier to read and maintain:

- Pick a style guide and apply it consistently across the whole project; consistency matters more than the specific choices.
- Be `const`-correct: mark variables, member functions, and parameters `const` whenever they do not need to mutate state.
- Use `auto` to avoid redundant type spelling, but not at the cost of readability — keep the reader able to tell what a name means.
- Prefer the standard library (containers, algorithms, `std::string`) over hand-rolled equivalents.

## Overall Performance

- **Measure before you optimize.** Use a profiler to find the real hot spots instead of guessing; premature optimization wastes effort and harms readability.
- **Avoid unnecessary copies.** Pass large objects by `const&`, or take by value and `std::move` when you need a copy anyway; `reserve()` containers when the final size is known.
- **Let the compiler help.** Return local objects by value and rely on (guaranteed) copy elision rather than returning via output parameters.
- Prefer move semantics for expensive-to-copy types, and remember that `std::move` is a cast, not an operation.

## Code Security

- **Manage resources with RAII.** Wrap every resource (memory, files, locks, sockets) in an object whose destructor releases it.
- **Prefer smart pointers** (`std::unique_ptr`, `std::shared_ptr`) over raw `new`/`delete`; avoid owning raw pointers.
- **Avoid undefined behavior**: no out-of-bounds access, no signed overflow, no use-after-free, no strict-aliasing violations (see §9.5). Sanitizers help detect these.
- Prefer `std::span`, `std::array`, and `.at()` over raw pointers and unchecked indexing when bounds matter, and avoid C-style casts in favor of the named C++ casts.

## Maintainability

- Keep functions small and focused on a single responsibility; prefer standard algorithms over hand-written loops to express intent clearly.
- Make interfaces hard to misuse: use strong types and enum classes instead of bare `int`/`bool` flags.
- Write tests, and run them continuously so regressions are caught early.
- Document *why*, not *what*: the code already says what it does.

## Portability

- Use fixed-width integer types (`std::int32_t`, etc.) from `<cstdint>` when the exact size matters; do not assume `int` is 32 bits or that `char` is signed.
- Avoid implementation-defined and platform-specific behavior; when you must depend on it, isolate it behind a small abstraction.
- Prefer the standard library over platform-specific APIs (e.g. `<filesystem>`, `<thread>`, `<chrono>`) so the same code builds across platforms.
- When byte order matters, query it explicitly (`std::endian` in C++20) rather than assuming little- or big-endian.

[Table of Content](./toc.md) | [Previous Chapter](./appendix1.md)

## Licenses

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).