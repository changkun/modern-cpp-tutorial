//
// 4.1.linear.container.cpp
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <array>
#include <vector>

void foo(int *p, int len) {
    for (int i = 0; i != len; ++i) {
        std::cout << p[i] << std::endl;
    }
}

int main() {
    std::vector<int> v;
    std::cout << "size:" << v.size() << std::endl;         // output 0
    std::cout << "capacity:" << v.capacity() << std::endl; // output 0

    // As you can see, the storage of std::vector is automatically managed and 
    // automatically expanded as needed.
    // But if there is not enough space, you need to redistribute more memory, 
    // and reallocating memory is usually a performance-intensive operation.
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::cout << "size:" << v.size() << std::endl;         // output 3
    std::cout << "capacity:" << v.capacity() << std::endl; // output 4

    // The auto-expansion logic here is very similar to Golang's slice.
    v.push_back(4);
    v.push_back(5);
    std::cout << "size:" << v.size() << std::endl;         // output 5
    std::cout << "capacity:" << v.capacity() << std::endl; // output 8

    // As can be seen below, although the container empties the element, 
    // the memory of the emptied element is not returned.
    v.clear();                                             
    std::cout << "size:" << v.size() << std::endl;         // output 0
    std::cout << "capacity:" << v.capacity() << std::endl; // output 8

    // Additional memory can be returned to the system via the shrink_to_fit() call
    v.shrink_to_fit();
    std::cout << "size:" << v.size() << std::endl;         // output 0
    std::cout << "capacity:" << v.capacity() << std::endl; // output 0


    std::array<int, 4> arr= {1,4,3,2};
    
    //int len = 4;
    //std::array<int, len> arr = {1,2,3,4}; // illegal, size of array must be constexpr
    
    // C style parameter passing
    // foo(arr, arr.size());           // illegal, cannot convert implicitly
    foo(&arr[0], arr.size());
    foo(arr.data(), arr.size());

    // more usage
    std::sort(arr.begin(), arr.end());
    for(auto &i : arr)
        std::cout << i << std::endl;
    
    return 0;
}
