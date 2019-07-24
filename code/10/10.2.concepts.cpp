//
// 10.2.concepts.cpp
// chapter 10 cpp20
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//


#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

 template<typename T>
concept bool Stringable = requires(T a){
    {a.to_string()} -> string;
};

 template<typename T>
concept bool HasStringFunc = requires(T a){
    { to_string(a) } -> string;
};

struct Person {
    double height, weight;
    Person(double a, double b) : height(a), weight(b) {}
    string to_string(){
        return "weight: "+ std::to_string(weight) + ", height: "+ std::to_string(height);
	}
};


namespace std {

string to_string(list<int> l){
    string s = "";
    for(int a : l ){
        s+=(" " + to_string(a) + " ");
    }
    return s;
}

}

string to_string(std::vector<int> v){
    string s = "";
    for(int a : v ){
        s += (" " +  to_string(a) + " ");
    }
    return s;
}


 void print(Stringable a){
    std::cout << a.to_string() << std::endl;
}

 void print(HasStringFunc a){
    std::cout << to_string(a) << std::endl;
}

 int main() {
    std::list<int> l {1, 2, 3};
    Person p(57, 170.0);
    std::vector<int> v { 34, 23, 34, 56, 78};

    print(p); // uses concept Stringable
    print(l);
    print(3); // uses concept HasStringFunc
    // print(v); // error
    return 0;
}