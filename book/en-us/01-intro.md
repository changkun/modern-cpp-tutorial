---
Title: Chapter 1 Towards C++11/14/17
Type: book-en-us
Order: 1
---

# Chapter 1 Towards C++11/14/17

[TOC]

**Compilation Environment**: This book will use `clang++` as the only compiler used, and always use the `-std=c++17` as compilation flag in your code.

```bash
→ clang++ -v
Apple LLVM version 9.1.0 (clang-902.0.39.1)
Target: x86_64-apple-darwin17.5.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

## 1.1 Deprecated Features

Before learning C++1x, let's take a look at the main features that have been deprecated since C++11:

> **Note**: Deprecation is not completely unusable, it is only intended to imply that programmers will disappear from future standards and should be avoided. However, the deprecated features are still part of the standard library, and most of the features are actually "permanently" reserved for compatibility reasons.

- **The string literal constant is no longer allowed to be assigned to a `char *`. If you need to assign and initialize a `char *` with a string literal constant, you should use `const char *` or `auto`.**
```cpp
 char *str = "hello world!"; // A deprecation warning will appear
```
- **C++98 exception description, `unexpected_handler`, `set_unexpected()` and other related features are deprecated and should use `noexcept`.**

- **`auto_ptr` is deprecated and `unique_ptr` should be used.**

- **`register` keyword is deprecated and can be used but no longer has any practical meaning.**

- The `++` operation of the **`bool` type is deprecated.**

- **If a class has a destructor, the properties for which it generates copy constructors and copy assignment operators are deprecated.**

- **C language style type conversion is deprecated (i.e. using `(convert_type)`) before variables, and `static_cast`, `reinterpret_cast`, `const_cast` should be used for type conversion. **

- **In particular, some of the C standard libraries that can be used are deprecated in the latest C++17 standard, such as `<ccomplex>`, `<cstdalign>`, `<cstdbool>` and `<ctgmath>`**

- ……and many more

There are also other features such as parameter binding (C++11 provides `std::bind` and `std::function`), `export`, etc. are also deprecated. These features mentioned above** If you have never used or heard of it, please don't try to understand them. You should move closer to the new standard and learn new features directly. After all, technology is moving forward.

## 1.2 Compatibility with C

For some force majeure and historical reasons, we had to use some C code (even old C code) in C++, such as Linux system calls. Before the advent of C++1x, most people talked about "what is the difference between C and C++". Generally speaking, in addition to answering object-oriented class features and template features of generic programming, there is no other opinion, even Directly answering "almost" is also a big one. The Wayne diagram in Figure 1.2 roughly answers the C and C++ related compatibility.

![Figure 1.2: C and C++ compatibility](../../assets/figures/comparison.png)

From now on, you should have the idea that "**C++ is not a superset of C**" in your mind (and not from the beginning, later [References for further reading](# further reading references) The difference between C++98 and C99 is given). When writing C++, you should also avoid using programming styles such as `void*` whenever possible. When you have to use C, you should pay attention to the use of `extern "C"`, separate the C code from the C++ code, and then unify the link, for example:

```cpp
// foo.h
#ifdef __cplusplus
extern "C" {
#endif

int add(int x, int y);

#ifdef __cplusplus
}
#endif

// foo.c
int add(int x, int y) 
{
    return x+y;
}

// 1.1.cpp
#include "foo.h"
#include <iostream>
#include <functional>

int main() 
{
    [out = std::ref(std::cout << "Result from C code: " << add(1, 2))]()
    {
        out.get() << ".\n";
    }();

    return 0;
}
```
You should first compile the C code with `gcc`:

```bash
gcc -c foo.c
```

Compile the foo.o file and link the C++ code to the `.o` file using `clang++` (or both compile to `.o` and then unlink):

```bash
clang++ 1.1.cpp foo.o -std=c++17 -o 1.1
```

Of course, you can use `Makefile` to compile the above code:

```makefile
C = gcc
CXX = clang++

SOURCE_C = foo.c
OBJECTS_C = foo.o

SOURCE_CXX = 1.1.cpp

TARGET = 1.1
LDFLAGS_COMMON = -std=c++17

all:
	$(C) -c $(SOURCE_C)
	$(CXX) $(SOURCE_CXX) $(OBJECTS_C) $(LDFLAGS_COMMON) -o $(TARGET)
clean:
	rm -rf *.o $(TARGET)
```
> Note: Indentation in Makefile is a tab instead of a space character. If you copy this code directly into your editor, the tab may automatically be replaced. Please ensure the indentation in Makefile is done by tabs only.

> If you don't know the how to use Makefile. In this tutorial, you don't have to build complicated codes. You can also read this book by simply using `clang++ -std=c++17` on the command line.

If you are new to modern C++, you probably still won't understand the small piece of code above, namely:

```cpp
[out = std::ref(std::cout << "Result from C code: " << add(1, 2))]()
{
    out.get() << ".\n";
}();
```
Don't worry, the following chapters in this book will explain the above code.

[Back to Contents](./toc.md)| [Previous Chapter](./00-preface.md) | [Next Chapter](./01-intro.md)

## Further reading 

1. [C++ Language Guide by Bjarne Stroustrup](https://www.amazon.com/Tour-2nd-Depth-Bjarne-Stroustrup/dp/0134997832)
2. [History of C++ ](http://en.cppreference.com/w/cpp/language/history)
3. [Support for C++ 1x features in compilers such as GCC/Clang](http://en.cppreference.com/w/cpp/compiler_support)
4. [The difference between C++98 and C99](http://david.tribble.com/text/cdiffs.htm#C99-vs-CPP98)

## License

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License Agreement" style="border-width:0" src ="https://i.creativecommons.org/l/by-nc-nd/4.0/80x15.png" /></a>

This book is originally written by [Ou Changkun](https://github.com/changkun) in Chinese and is translated by [Swastik Baranwal](https://github.com/Delta456) in English, using [Creative Commons](http://creativecommons.org/licenses/by-Nc-nd/4.0/) license. The code in the project is open source using the MIT protocol, see [License](../../LICENSE).
