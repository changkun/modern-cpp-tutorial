//
// 8.1.filesystem.cpp
// chapter 08 filesystem
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

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
    std::cout << "stem:      " << p.stem()        << "\n";
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
    std::cout << "renamed exists:  " << fs::exists(base / "renamed.txt") << "\n";

    // Clean up.
    fs::remove_all(base);
    std::cout << "after cleanup, exists: " << fs::exists(base) << "\n";
}
