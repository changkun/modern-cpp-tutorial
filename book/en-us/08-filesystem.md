---
title: "Chapter 08: File System"
type: book-en-us
order: 8
---

# Chapter 08: File System

[TOC]

The file system library provides functions related to
the operation of the file system, path, regular files, directories, and so on.
Similar to the regular expression library, it was one of the first libraries
to be launched by boost and eventually merged into the C++ standard in C++17.
Its entire contents live in the `<filesystem>` header under the
`std::filesystem` namespace, for which a short alias is conventionally introduced:

```cpp
#include <filesystem>
namespace fs = std::filesystem;
```

> On some older toolchains (e.g. GCC before version 8), using the filesystem
> library also required linking against `-lstdc++fs` (or LLVM's `-lc++fs`);
> modern compilers no longer need this.

## 8.1 The path `std::filesystem::path`

`std::filesystem::path` is the heart of the library. It represents a file path in a
portable way and hides the differences between operating systems in their path
separators (such as `/` and `\`). A `path` can be constructed from a string and
composed with `operator/`:

```cpp
fs::path p = "/usr/local";
p /= "bin";               // p is now /usr/local/bin
fs::path q = p / "clang"; // composes without modifying p
```

It is worth emphasizing that a `path` is only a **syntactic** representation of a
path: constructing one neither touches the disk nor requires the path to actually
exist. It provides a set of member functions for decomposing a path:

```cpp
fs::path p = "/usr/local/hello.txt";
p.filename();    // "hello.txt"
p.stem();        // "hello"
p.extension();   // ".txt"
p.parent_path(); // "/usr/local"
```

## 8.2 Querying file status

The library provides a set of **non-member functions** for querying the actual
file a path refers to; each takes a `path` argument:

```cpp
fs::exists(p);            // does the path exist
fs::is_regular_file(p);   // is it a regular file
fs::is_directory(p);      // is it a directory
fs::file_size(p);         // file size in bytes
fs::last_write_time(p);   // last modification time
```

Note that these operations, which genuinely access the file system, **throw a
`std::filesystem::filesystem_error`** on failure (e.g. the path does not exist or
permission is denied). For nearly every such function the library provides an
overload taking a `std::error_code&`, to report errors without exceptions:

```cpp
std::error_code ec;
auto size = fs::file_size(p, ec); // does not throw on error; writes to ec
if (ec) {
    std::cout << "cannot get size: " << ec.message() << std::endl;
}
```

## 8.3 Iterating directories

`std::filesystem::directory_iterator` iterates over the immediate entries of a
directory, while `recursive_directory_iterator` walks the entire directory tree.
Both can be used directly in a range-based for loop, yielding `directory_entry`
elements:

```cpp
for (const auto& entry : fs::directory_iterator(dir)) {
    std::cout << entry.path() << std::endl;
}

// recursively walk the whole tree
for (const auto& entry : fs::recursive_directory_iterator(dir)) {
    if (entry.is_regular_file())
        std::cout << entry.path() << " (" << entry.file_size() << ")\n";
}
```

A `directory_entry` caches the status of the file it refers to, so member functions
such as `entry.is_regular_file()` and `entry.file_size()` are often more efficient
than calling the non-member functions again on its path.

## 8.4 Creating, copying, and removing

The library also offers a set of operations that modify the file system:

```cpp
fs::create_directories(p / "a" / "b"); // create directories recursively
fs::copy_file(src, dst);               // copy a single file
fs::copy(src, dst, fs::copy_options::recursive); // copy a directory recursively
fs::rename(old_path, new_path);        // rename / move
fs::remove(p);                         // remove a single file or empty directory
fs::remove_all(p);                     // remove recursively, returns the count removed
```

## 8.5 A complete example

The following example combines the operations above. To keep it self-contained and
repeatable, we create a dedicated working directory under the system temporary
directory and clean it up at the end:

```cpp
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    // Work in a private scratch directory so the example is
    // self-contained and repeatable.
    const fs::path base = fs::temp_directory_path() / "modern-cpp-fs-demo";
    fs::remove_all(base);                  // clean up any previous run
    fs::create_directories(base / "sub");  // creates intermediate dirs

    // Create a file.
    std::ofstream(base / "hello.txt") << "hello, filesystem";

    // Path decomposition (no filesystem access required).
    const fs::path p = base / "hello.txt";
    std::cout << "filename:  " << p.filename()    << "\n";
    std::cout << "extension: " << p.extension()   << "\n";
    std::cout << "parent:    " << p.parent_path() << "\n";

    // Query the file.
    std::cout << "exists:          " << fs::exists(p)          << "\n";
    std::cout << "is_regular_file: " << fs::is_regular_file(p) << "\n";
    std::cout << "file_size:       " << fs::file_size(p)       << "\n";

    // Recursively iterate the directory tree.
    std::cout << "entries:\n";
    for (const auto& entry : fs::recursive_directory_iterator(base))
        std::cout << "  " << entry.path() << "\n";

    // Copy, then rename.
    fs::copy_file(p, base / "copy.txt");
    fs::rename(base / "copy.txt", base / "renamed.txt");

    // Clean up.
    fs::remove_all(base);
    std::cout << "after cleanup, exists: " << fs::exists(base) << "\n";
}
```

[Table of Content](./toc.md) | [Previous Chapter](./07-thread.md) | [Next Chapter: Minor Features](./09-others.md)

## Further Readings

## Licenses

<a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).