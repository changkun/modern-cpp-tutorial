//
// 4.6.associative.improvements.cpp
// chapter 04 containers
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> m;

    // try_emplace: only inserts if the key is absent; does not touch
    // the mapped value (or move from arguments) when the key exists.
    m.try_emplace(1, "one");
    m.try_emplace(1, "uno"); // no effect, key 1 already present

    // insert_or_assign: inserts, or overwrites the existing value.
    m.insert_or_assign(1, "ONE");
    m.insert_or_assign(2, "TWO");

    // extract: detach a node without copying/moving the element, then
    // merge nodes from another map.
    std::map<int, std::string> other;
    other.insert(m.extract(2)); // move node 2 into `other`

    std::map<int, std::string> more{{3, "three"}};
    m.merge(more); // splice nodes from `more` into `m`

    for (const auto& [k, v] : m)
        std::cout << k << " => " << v << "\n";
    std::cout << "other has key 2: " << other.count(2) << "\n";
}
