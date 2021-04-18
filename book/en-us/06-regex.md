---
title: "Chapter 06 Regular Expression"
type: book-en-us
order: 6
---

# Chapter 06 Regular Expression

[TOC]

## 6.1 Introduction

Regular expressions are not part of the C++ language and therefore we only briefly
introduced it here.

Regular expressions describe a pattern of string matching.
The general use of regular expressions is mainly to achieve
the following three requirements:

1. Check if a string contains some form of substring;
2. Replace the matching substrings;
3. Take the eligible substring from a string.

Regular expressions are text patterns consisting of ordinary characters (such as a to z)
and special characters. A pattern describes one or more strings to match when searching for text.
Regular expressions act as a template to match a character pattern to the string being searched.

### Ordinary characters

Normal characters include all printable and unprintable characters that are not explicitly specified as metacharacters. This includes all uppercase
and lowercase letters, all numbers, all punctuation, and some other symbols.

### Special characters

A special character is a character with special meaning in a regular expression and is also the core matching syntax of a regular expression. See the table below:

| Special characters | Description                                                                                                                                                                                                                                                                                                |
| :----------------: | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|        `$`         | Matches the end position of the input string.                                                                                                                                                                                                                                                              |
|      `(`,`)`       | Marks the start and end of a subexpression. Subexpressions can be obtained for later use.                                                                                                                                                                                                                  |
|        `*`         | Matches the previous subexpression zero or more times.                                                                                                                                                                                                                                                     |
|        `+`         | Matches the previous subexpression one or more times.                                                                                                                                                                                                                                                      |
|        `.`         | Matches any single character except the newline character `\n`.                                                                                                                                                                                                                                            |
|        `[`         | Marks the beginning of a bracket expression.                                                                                                                                                                                                                                                               |
|        `?`         | Matches the previous subexpression zero or one time, or indicates a non-greedy qualifier.                                                                                                                                                                                                                  |
|        `\`         | Marks the next character as either a special character, or a literal character, or a backward reference, or an octal escape character. For example, `n` Matches the character `n`. `\n` matches newline characters. The sequence `\\` Matches the `'\'` character, while `\(` matches the `'('` character. |
|        `^`         | Matches the beginning of the input string, unless it is used in a square bracket expression, at which point it indicates that the set of characters is not accepted.                                                                                                                                       |
|        `{`         | Marks the beginning of a qualifier expression.                                                                                                                                                                                                                                                             |
|        `\|`        | Indicates a choice between the two.                                                                                                                                                                                                                                                                        |

### Quantifiers

The qualifier is used to specify how many times a given component of a regular expression must appear to satisfy the match. See the table below:

| Character | Description                                                                                                                                                                                                                                                                                                       |
| :-------: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|    `*`    | matches the previous subexpression zero or more times. For example, `foo*` matches `fo` and `foooo`. `*` is equivalent to `{0,}`.                                                                                                                                                                                 |
|    `+`    | matches the previous subexpression one or more times. For example, `foo+` matches `foo` and `foooo` but does not match `fo`. `+` is equivalent to `{1,}`.                                                                                                                                                         |
|    `?`    | matches the previous subexpression zero or one time. For example, `Your(s)?` can match `Your` in `Your` or `Yours`. `?` is equivalent to `{0,1}`.                                                                                                                                                                 |
|   `{n}`   | `n` is a non-negative integer. Matches the determined `n` times. For example, `o{2}` cannot match `o` in `for`, but can match two `o` in `foo`.                                                                                                                                                                   |
|  `{n,}`   | `n` is a non-negative integer. Match at least `n` times. For example, `o{2,}` cannot match `o` in `for`, but matches all `o` in `foooooo`. `o{1,}` is equivalent to `o+`. `o{0,}` is equivalent to `o*`.                                                                                                          |
|  `{n,m}`  | `m` and `n` are non-negative integers, where `n` is less than or equal to `m`. Matches at least `n` times and matches up to `m` times. For example, `o{1,3}` will match the first three `o` in `foooooo`. `o{0,1}` is equivalent to `o?`. Note that there can be no spaces between the comma and the two numbers. |

With these two tables, we can usually read almost all regular expressions.

## 6.2 `std::regex` and Its Related

The most common way to match string content is to use regular expressions. Unfortunately, in traditional C++, regular expressions have not been supported by the language level, and are not included in the standard library. C++ is a high-performance language. In the development of background services, the use of regular expressions is also used when judging URL resource links. The most mature and common practice in the industry.

The general solution is to use the regular expression library of `boost`. C++11 officially incorporates the processing of regular expressions into the standard library, providing standard support from the language level and no longer relying on third parties.

The regular expression library provided by C++11 operates on the `std::string` object, and the pattern `std::regex` (essentially `std::basic_regex`) is initialized and matched by `std::regex_match` Produces `std::smatch` (essentially the `std::match_results` object).

We use a simple example to briefly introduce the use of this library. Consider the following regular expression:

- `[az]+\.txt`: In this regular expression, `[az]` means matching a lowercase letter, `+` can match the previous expression multiple times, so `[az]+` can Matches a string of lowercase letters. In the regular expression, a `.` means to match any character, and `\.` means to match the character `.`, and the last `txt` means to match `txt` exactly three letters. So the content of this regular expression to match is a text file consisting of pure lowercase letters.

`std::regex_match` is used to match strings and regular expressions, and there are many different overloaded forms. The simplest form is to pass `std::string` and a `std::regex` to match. When the match is successful, it will return `true`, otherwise, it will return `false`. For example:

```cpp
#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};
    // In C++, `\` will be used as an escape character in the string. In order for `\.` to be passed as a regular expression, it is necessary to perform second escaping of `\`, thus we have `\\.`
    std::regex txt_regex("[a-z]+\\.txt");
    for (const auto &fname: fnames)
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << std::endl;
}
```

Another common form is to pass in the three arguments `std::string`/`std::smatch`/`std::regex`.
The essence of `std::smatch` is actually `std::match_results`.
In the standard library, `std::smatch` is defined as `std::match_results<std::string::const_iterator>`,
which means `match_results` of a substring iterator type.
Use `std::smatch` to easily get the matching results, for example:

```cpp
std::regex base_regex("([a-z]+)\\.txt");
std::smatch base_match;
for(const auto &fname: fnames) {
    if (std::regex_match(fname, base_match, base_regex)) {
        // the first element of std::smatch matches the entire string
        // the second element of std::smatch matches the first expression with brackets
        if (base_match.size() == 2) {
            std::string base = base_match[1].str();
            std::cout << "sub-match[0]: " << base_match[0].str() << std::endl;
            std::cout << fname << " sub-match[1]: " << base << std::endl;
        }
    }
}
```

The output of the above two code snippets is:

```
foo.txt: 1
bar.txt: 1
test: 0
a0.txt: 0
AAA.txt: 0
sub-match[0]: foo.txt
foo.txt sub-match[1]: foo
sub-match[0]: bar.txt
bar.txt sub-match[1]: bar
```

## Conclusion

This section briefly introduces the regular expression itself,
and then introduces the use of the regular expression library
through a practical example based on the main requirements of
using regular expressions.

## Exercise

In web server development, we usually want to serve some routes that satisfy a certain condition.
Regular expressions are one of the tools to accomplish this.
Given the following request structure:

```cpp
struct Request {
    // request method, POST, GET; path; HTTP version
    std::string method, path, http_version;
    // use smart pointer for reference counting of content
    std::shared_ptr<std::istream> content;
    // hash container, key-value dict
    std::unordered_map<std::string, std::string> header;
    // use regular expression for path match
    std::smatch path_match;
};
```

Requested resource type:

```cpp
typedef std::map<
    std::string, std::unordered_map<
        std::string,std::function<void(std::ostream&, Request&)>>> resource_type;
```

And server template:

```cpp
template <typename socket_type>
class ServerBase {
public:
    resource_type resource;
    resource_type default_resource;

    void start() {
        // TODO
    }
protected:
    Request parse_request(std::istream& stream) const {
        // TODO
    }
}
```

Please implement the member functions `start()` and `parse_request`. Enable server template users to specify routes as follows:

```cpp
template<typename SERVER_TYPE>
void start_server(SERVER_TYPE &server) {

    // process GET request for /match/[digit+numbers], e.g. GET request is /match/abc123, will return abc123
    server.resource["fill_your_reg_ex"]["GET"] = [](ostream& response, Request& request) {
        string number=request.path_match[1];
        response << "HTTP/1.1 200 OK\r\nContent-Length: " << number.length() << "\r\n\r\n" << number;
    };

    // peocess default GET request; anonymous function will be called if no other matches
    // response files in folder web/
    // default: index.html
    server.default_resource["fill_your_reg_ex"]["GET"] = [](ostream& response, Request& request) {
        string filename = "www/";

        string path = request.path_match[1];

        // forbidden use `..` access content outside folder web/
        size_t last_pos = path.rfind(".");
        size_t current_pos = 0;
        size_t pos;
        while((pos=path.find('.', current_pos)) != string::npos && pos != last_pos) {
            current_pos = pos;
            path.erase(pos, 1);
            last_pos--;
        }

        // (...)
    };

    server.start();
}
```

An suggested solution can be found [here](../../exercises/6).

[Table of Content](./toc.md) | [Previous Chapter](./05-pointers.md) | [Next Chapter: Threads and Concurrency](./07-thread.md)

## Further Readings

1. [Comments from `std::regex`'s author](http://zhihu.com/question/23070203/answer/84248248)
2. [Library document of Regular Expression](http://en.cppreference.com/w/cpp/regex)

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).
