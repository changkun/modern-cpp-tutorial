//
// 6.1.regex.cpp
// chapter 06 regular expression
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//

#include <iostream>
#include <string>
#include <regex>
using namespace std;
int main() {
    string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
    // In C++, `\` will be used as an escape character in the string. 
    // In order for `\.` to be passed as a regular expression, 
    // it is necessary to perform second escaping of `\`, thus we have `\\.`
    regex txt_regex("[a-z]+\\.txt");
    for (const auto &fname: fnames)
        cout << fname << ": " << regex_match(fname, txt_regex) << endl;
    
   regex base_regex("([a-z]+)\\.txt");
    smatch base_match;
    for(const auto &fname: fnames) {
        if (regex_match(fname, base_match, base_regex)) {
            // the first element of std::smatch matches the entire string
            // the second element of std::smatch matches the first expression with brackets
            if (base_match.size() == 2) {
                string base = base_match[1].str();
                cout << "sub-match[0]: " << base_match[0].str() << endl;
                cout << fname << " sub-match[1]: " << base <<endl;
            }
        }
    }
    
    return 0;
}
