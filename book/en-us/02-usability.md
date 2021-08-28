---
title: "Chapter 02: Language Usability Enhancements"
type: book-en-us
order: 2
---

# Chapter 02: Language Usability Enhancements

[TOC]

When we declare, define a variable or constant, and control the flow of code,
object-oriented functions, template programming, etc., before the runtime,
it may happen when writing code or compiler compiling code.
To this end, we usually talk about **language usability**,
which refers to the language behavior that occurred before the runtime.

## 2.1 Constants

### nullptr

The purpose of `nullptr` appears to replace `NULL`. In a sense,
traditional C++ treats `NULL` and `0` as the same thing,
depending on how the compiler defines NULL,
and some compilers define NULL as `((void*)0)` Some will define it directly as `0`.

C++ **does not allow** to implicitly convert `void *` to other types.
But if the compiler tries to define `NULL` as `((void*)0)`, then in the following code:

```cpp
char *ch = NULL;
```

C++ without the `void *` implicit conversion has to define `NULL` as `0`.
This still creates a new problem. Defining `NULL` to 0 will cause the overloading feature in `C++` to be confusing.
Consider the following two `foo` functions:

```cpp
void foo(char*);
void foo(int);
```

Then the `foo(NULL);` statement will call `foo(int)`, which will cause the code to be counterintuitive.

To solve this problem, C++11 introduced the `nullptr` keyword, which is specifically used to distinguish null pointers, 0. The type of `nullptr` is `nullptr_t`, which can be implicitly converted to any pointer or member pointer type, and can be compared equally or unequally with them.

You can try to compile the following code using clang++:

```cpp
#include <iostream>
#include <type_traits>

void foo(char *);
void foo(int);

int main() {
    if (std::is_same<decltype(NULL), decltype(0)>::value)
        std::cout << "NULL == 0" << std::endl;
    if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
        std::cout << "NULL == (void *)0" << std::endl;
    if (std::is_same<decltype(NULL), std::nullptr_t>::value)
        std::cout << "NULL == nullptr" << std::endl;

    foo(0);          // will call foo(int)
    // foo(NULL);    // doesn't compile
    foo(nullptr);    // will call foo(char*)
    return 0;
}

void foo(char *) {
    std::cout << "foo(char*) is called" << std::endl;
}
void foo(int i) {
    std::cout << "foo(int) is called" << std::endl;
}
```

The outputs are:

```bash
foo(int) is called
foo(char*) is called
```

From the output we can see that `NULL` is different from `0` and `nullptr`.
So, develop the habit of using `nullptr` directly.

In addition, in the above code, we used `decltype` and
`std::is_same` which are modern C++ syntax.
In simple terms, `decltype` is used for type derivation,
and `std::is_same` is used to compare the equality of the two types.
We will discuss them in detail later in the [decltype](#decltype) section.

### constexpr

C++ itself already has the concept of constant expressions, such as 1+2,
3\*4. Such expressions always produce the same result without any side effects.
If the compiler can directly optimize and embed these expressions into the program at
compile-time, it will increase the performance of the program. A very obvious example
is in the definition phase of an array:

```cpp
#include <iostream>
#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}
constexpr int len_foo_constexpr() {
    return 5;
}

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}


int main() {
    char arr_1[10];                      // legal
    char arr_2[LEN];                     // legal

    int len = 10;
    // char arr_3[len];                  // illegal

    const int len_2 = len + 1;
    constexpr int len_2_constexpr = 1 + 2 + 3;
    // char arr_4[len_2];                // illegal, but ok for most of the compilers
    char arr_4[len_2_constexpr];         // legal

    // char arr_5[len_foo()+5];          // illegal
    char arr_6[len_foo_constexpr() + 1]; // legal

    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    std::cout << fibonacci(10) << std::endl;

    return 0;
}
```

In the above example, `char arr_4[len_2]` may be confusing because `len_2` has been defined as a constant.
Why is `char arr_4[len_2]` still illegal?
This is because the length of the array in the C++ standard must be a constant expression,
and for `len_2`, this is a `const` constant, not a constant expression,
so even if this behavior is supported by most compilers, but it is an illegal behavior,
we need to use the `constexpr` feature introduced in C++11, which will be introduced next,
to solve this problem; for `arr_5`, before C++98 The compiler cannot know that `len_foo()`
actually returns a constant at runtime, which causes illegal production.

> Note that most compilers now have their compiler optimizations.
> Many illegal behaviors become legal under the compiler's optimization.
> If you need to reproduce the error, you need to use the old version of the compiler.

C++11 provides `constexpr` to let the user explicitly declare that the function or
object constructor will become a constant expression at compile time.
This keyword explicitly tells the compiler that it should verify that `len_foo`
should be a compile-time constant expression. Constant expression.

In addition, the function of `constexpr` can use recursion:

```cpp
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}
```

Starting with C++14,
the constexpr function can use simple statements such as local variables,
loops, and branches internally.
For example, the following code cannot be compiled under the C++11 standard:

```cpp
constexpr int fibonacci(const int n) {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}
```

To do this, we can write a simplified version like this
to make the function available from C++11:

```cpp
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}
```

## 2.2 Variables and initialization

### if-switch

In traditional C++, the declaration of a variable can declare a temporary variable `int`
even though it can be located anywhere, even within a `for` statement,
but there is always no way to declare a temporary variable in the `if` and `switch` statements.
E.g:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4};

    // since c++17, can be simplified by using `auto`
    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
    if (itr != vec.end()) {
        *itr = 3;
    }

    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
        itr != vec.end()) {
        *itr = 4;
    }

    // should output: 1, 4, 3, 4. can be simplified using `auto`
    for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element)
        std::cout << *element << std::endl;
}
```

In the above code, we can see that the `itr` variable is defined in the scope of
the entire `main()`, which causes us to rename the other when a variable need to traverse
the entire `std::vectors` again. C++17 eliminates this limitation so that
we can do this in if(or switch):

```cpp
if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
    itr != vec.end()) {
    *itr = 4;
}
```

Is it similar to the Go?

### Initializer list

Initialization is a very important language feature,
the most common one is when the object is initialized.
In traditional C++, different objects have different initialization methods,
such as ordinary arrays, PODs (**P**lain **O**ld **D**ata,
i.e. classes without constructs, destructors, and virtual functions)
Or struct type can be initialized with `{}`,
which is what we call the initialization list.
For the initialization of the class object,
you need to use the copy construct,
or you need to use `()`.
These different methods are specific to each other and cannot be generic.
E.g:

```cpp
#include <iostream>
#include <vector>

class Foo {
public:
    int value_a;
    int value_b;
    Foo(int a, int b) : value_a(a), value_b(b) {}
};

int main() {
    // before C++11
    int arr[3] = {1, 2, 3};
    Foo foo(1, 2);
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "foo:" << foo.value_a << ", " << foo.value_b << std::endl;
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}
```

To solve this problem,
C++11 first binds the concept of the initialization list to the type
and calls it `std::initializer_list`,
allowing the constructor or other function to use the initialization list
like a parameter, which is the initialization of class objects provides
a unified bridge between normal arrays and POD initialization methods,
such as:

```cpp
#include <initializer_list>
#include <vector>
class MagicFoo {
public:
    std::vector<int> vec;
    MagicFoo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin();
             it != list.end(); ++it)
            vec.push_back(*it);
    }
};
int main() {
    // after C++11
    MagicFoo magicFoo = {1, 2, 3, 4, 5};

    std::cout << "magicFoo: ";
    for (std::vector<int>::iterator it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) std::cout << *it << std::endl;
}
```

This constructor is called the initialize list constructor, and the type with
this constructor will be specially taken care of during initialization.

In addition to the object construction, the initialization list can also
be used as a formal parameter of a normal function, for example:

```Cpp
public:
    void foo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin();
            it != list.end(); ++it) vec.push_back(*it);
    }

magicFoo.foo({6,7,8,9});
```

Second, C++11 also provides a uniform syntax for initializing arbitrary objects, such as:

```cpp
Foo foo2 {3, 4};
```

### Structured binding

Structured bindings provide functionality similar to the multiple return values
provided in other languages. In the chapter on containers,
we will learn that C++11 has added a `std::tuple` container for
constructing a tuple that encloses multiple return values. But the flaw
is that C++11/14 does not provide a simple way to get and define
the elements in the tuple from the tuple,
although we can unpack the tuple using `std::tie`
But we still have to be very clear about how many objects this tuple contains,
what type of each object is, very troublesome.

C++17 completes this setting,
and the structured bindings let us write code like this:

```cpp
#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

int main() {
    auto [x, y, z] = f();
    std::cout << x << ", " << y << ", " << z << std::endl;
    return 0;
}
```

The `auto` type derivation is described in the
[auto type inference](#auto) section.

## 2.3 Type inference

In traditional C and C++, the types of parameters must be clearly defined, which does not help us to quickly encode, especially when we are faced with a large number of complex template types, we must indicate the type of variables to proceed. Subsequent coding, which not only slows down our development efficiency but also makes the code stinking and long.

C++11 introduces the two keywords `auto` and `decltype` to implement type derivation, letting the compiler worry about the type of the variable. This makes C++ the same as other modern programming languages, in a way that provides the habit of not having to worry about variable types.

### auto

`auto` has been in C++ for a long time, but it always exists as an indicator of a storage type, coexisting with `register`. In traditional C++, if a variable is not declared as a `register` variable, it is automatically treated as an `auto` variable. And with `register` being deprecated (used as a reserved keyword in C++17 and later used, it doesn't currently make sense), the semantic change to `auto` is very natural.

One of the most common and notable examples of type derivation using `auto` is the iterator. You should see the lengthy iterative writing in traditional C++ in the previous section:

```cpp
// before C++11
// cbegin() returns vector<int>::const_iterator
// and therefore itr is type vector<int>::const_iterator
for(vector<int>::const_iterator it = vec.cbegin(); itr != vec.cend(); ++it)
```

When we have `auto`:

```cpp
#include <initializer_list>
#include <vector>
#include <iostream>

class MagicFoo {
public:
    std::vector<int> vec;
    MagicFoo(std::initializer_list<int> list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            vec.push_back(*it);
        }
    }
};

int main() {
    MagicFoo magicFoo = {1, 2, 3, 4, 5};
    std::cout << "magicFoo: ";
    for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
    return 0;
}
```

Some other common usages:

```cpp
auto i = 5;              // i as int
auto arr = new auto(10); // arr as int *
```

Since C++ 20, `auto` can even be used as function arguments. Consider
the following example:

```cpp
int add(auto x, auto y) {
    return x+y;
}

auto i = 5; // type int
auto j = 6; // type int
std::cout << add(i, j) << std::endl;
```

> **Note**: `auto` cannot be used to derive array types yet:
>
> ```cpp
> auto auto_arr2[10] = {arr};   // illegal, can't infer array type
>
> 2.6.auto.cpp:30:19: error: 'auto_arr2' declared as array of 'auto'
>     auto auto_arr2[10] = {arr};
> ```

### decltype

The `decltype` keyword is used to solve the defect that the auto keyword
can only type the variable. Its usage is very similar to `typeof`:

```cpp
decltype(expression)
```

Sometimes we may need to calculate the type of an expression, for example:

```cpp
auto x = 1;
auto y = 2;
decltype(x+y) z;
```

You have seen in the previous example that
`decltype` is used to infer the usage of the type.
The following example is to determine
if the above variables `x, y, z` are of the same type:

```cpp
if (std::is_same<decltype(x), int>::value)
    std::cout << "type x == int" << std::endl;
if (std::is_same<decltype(x), float>::value)
    std::cout << "type x == float" << std::endl;
if (std::is_same<decltype(x), decltype(z)>::value)
    std::cout << "type z == type x" << std::endl;
```

Among them, `std::is_same<T, U>` is used to determine whether
the two types `T` and `U` are equal. The output is:

```
type x == int
type z == type x
```

### tail type inference

You may think that when we introduce `auto`, we have already mentioned that `auto` cannot be used for function arguments for type derivation. Can `auto` be used to derive the return type of a function? Still consider an example of an add function, which we have to write in traditional C++:

```cpp
template<typename R, typename T, typename U>
R add(T x, U y) {
    return x+y;
}
```

> Note: There is no difference between typename and class in the template parameter list. Before the keyword typename appears, class is used to define the template parameters. However, when defining a variable with [nested dependency type](http://en.cppreference.com/w/cpp/language/dependent_name#The_typename_disambiguator_for_dependent_names) in the template, you need to use typename to eliminate ambiguity.

Such code is very ugly because the programmer must explicitly
indicate the return type when using this template function.
But in fact, we don't know what kind of operation
the `add()` function will do, and what kind of return type to get.

This problem was solved in C++11. Although you may immediately
react to using `decltype` to derive the type of `x+y`,
write something like this:

```cpp
decltype(x+y) add(T x, U y)
```

But in fact, this way of writing can not be compiled.
This is because `x` and `y` have not been defined
when the compiler reads decltype(x+y).
To solve this problem, C++11 also introduces a trailing return type,
which uses the auto keyword to post the return type:

```cpp
template<typename T, typename U>
auto add2(T x, U y) -> decltype(x+y){
    return x + y;
}
```

The good news is that from C++14 it is possible to directly derive the return value of
a normal function, so the following way becomes legal:

```cpp
template<typename T, typename U>
auto add3(T x, U y){
    return x + y;
}
```

You can check if the type derivation is correct:

```cpp
// after c++11
auto w = add2<int, double>(1, 2.0);
if (std::is_same<decltype(w), double>::value) {
    std::cout << "w is double: ";
}
std::cout << w << std::endl;

// after c++14
auto q = add3<double, int>(1.0, 2);
std::cout << "q: " << q << std::endl;
```

### decltype(auto)

`decltype(auto)` is a slightly more complicated use of C++14.

> To understand it you need to know the concept of parameter forwarding
> in C++, which we will cover in detail in the
> [Language Runtime Hardening](./03-runtime.md) chapter,
> and you can come back to the contents of this section later.

In simple terms, `decltype(auto)` is mainly used to derive
the return type of a forwarding function or package,
which does not require us to explicitly specify
the parameter expression of `decltype`.
Consider the following example, when we need to wrap the following
two functions:

```cpp
std::string  lookup1();
std::string& lookup2();
```

In C++11:

```cpp
std::string look_up_a_string_1() {
    return lookup1();
}
std::string& look_up_a_string_2() {
    return lookup2();
}
```

With `decltype(auto)`, we can let the compiler do this annoying parameter forwarding:

```cpp
decltype(auto) look_up_a_string_1() {
    return lookup1();
}
decltype(auto) look_up_a_string_2() {
    return lookup2();
}
```

## 2.4 Control flow

### if constexpr

As we saw at the beginning of this chapter, we know that C++11 introduces the `constexpr` keyword, which compiles expressions or functions into constant results. A natural idea is that if we introduce this feature into the conditional judgment, let the code complete the branch judgment at compile-time, can it make the program more efficient? C++17 introduces the `constexpr` keyword into the `if` statement, allowing you to declare the condition of a constant expression in your code. Consider the following code:

```cpp
#include <iostream>

template<typename T>
auto print_type_info(const T& t) {
    if constexpr (std::is_integral<T>::value) {
        return t + 1;
    } else {
        return t + 0.001;
    }
}
int main() {
    std::cout << print_type_info(5) << std::endl;
    std::cout << print_type_info(3.14) << std::endl;
}
```

At compile time, the actual code will behave as follows:

```cpp
int print_type_info(const int& t) {
    return t + 1;
}
double print_type_info(const double& t) {
    return t + 0.001;
}
int main() {
    std::cout << print_type_info(5) << std::endl;
    std::cout << print_type_info(3.14) << std::endl;
}
```

### Range-based for loop

Finally, C++11 introduces a range-based iterative method, and we can write loops that are as concise
as Python, and we can further simplify the previous example:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4};
    if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) *itr = 4;
    for (auto element : vec)
        std::cout << element << std::endl; // read only
    for (auto &element : vec) {
        element += 1;                      // writeable
    }
    for (auto element : vec)
        std::cout << element << std::endl; // read only
}
```

## 2.5 Templates

C++ templates have always been a special art of the language, and templates can even be used independently as a new language. The philosophy of the template is to throw all the problems that can be processed at compile time into the compile time, and only deal with those core dynamic services at runtime, to greatly optimize the performance of the runtime. Therefore, templates are also regarded by many as one of the black magic of C++.

### Extern templates

In traditional C++, templates are instantiated by the compiler only when they are used. In other words, as long as a fully defined template is encountered in the code compiled in each compilation unit (file), it will be instantiated. This results in an increase in compile time due to repeated instantiations. Also, we have no way to tell the compiler not to trigger the instantiation of the template.

To this end, C++11 introduces an external template that extends the syntax of the original mandatory compiler to instantiate a template at a specific location, allowing us to explicitly tell the compiler when to instantiate the template:

```cpp
template class std::vector<bool>;          // force instantiation
extern template class std::vector<double>; // should not instantiation in current file
```

### The ">"

In the traditional C++ compiler, `>>` is always treated as a right shift operator. But actually we can easily write the code for the nested template:

```cpp
std::vector<std::vector<int>> matrix;
```

This is not compiled under the traditional C++ compiler,
and C++11 starts with continuous right angle brackets that become legal
and can be compiled successfully.
Even the following writing can be compiled by:

```cpp
template<bool T>
class MagicType {
    bool magic = T;
};

// in main function:
std::vector<MagicType<(1>2)>> magic; // legal, but not recommended
```

### Type alias templates

Before you understand the type alias template, you need to understand the difference between "template" and "type". Carefully understand this sentence: **Templates are used to generate types.** In traditional C++, `typedef` can define a new name for the type, but there is no way to define a new name for the template. Because the template is not a type. E.g:

```cpp
template<typename T, typename U>
class MagicType {
public:
    T dark;
    U magic;
};

// not allowed
template<typename T>
typedef MagicType<std::vector<T>, std::string> FakeDarkMagic;
```

C++11 uses `using` to introduce the following form of writing, and at the same time supports the same effect as the traditional `typedef`:

> Usually, we use `typedef` to define the alias syntax: `typedef original name new name; `, but the definition syntax for aliases such as function pointers is different, which usually causes a certain degree of difficulty for direct reading.

```cpp
typedef int (*process)(void *);
using NewProcess = int(*)(void *);
template<typename T>
using TrueDarkMagic = MagicType<std::vector<T>, std::string>;

int main() {
    TrueDarkMagic<bool> you;
}
```

### Variadic templates

The template has always been one of C++'s unique **Black Magic**.
In traditional C++,
both a class template and a function template could only accept
a fixed set of template parameters as specified;
C++11 added a new representation, allowing any number,
template parameters of any category,
and there is no need to fix the number of parameters when defining.

```cpp
template<typename... Ts> class Magic;
```

The template class Magic object can accept an unrestricted number of typename as
a formal parameter of the template, such as the following definition:

```cpp
class Magic<int,
            std::vector<int>,
            std::map<std::string,
            std::vector<int>>> darkMagic;
```

Since it is arbitrary, a template parameter with a number of 0 is also possible: `class Magic<> nothing;`.

If you do not want to generate 0 template parameters, you can manually define at least one template parameter:

```cpp
template<typename Require, typename... Args> class Magic;
```

The variable length parameter template can also be directly adjusted to the template function.
The `printf` function in the traditional C, although it can also reach the call of an indefinite number of formal parameters, is not class safe. In addition to the variable-length parameter functions that define class safety, C++11 can also make printf-like functions naturally handle objects that are not self-contained. In addition to the use of `...` in the template parameters to indicate the indefinite length of the template parameters, the function parameters also use the same representation to represent the indefinite length parameters, which provides a convenient means for us to simply write variable length parameter functions, such as:

```cpp
template<typename... Args> void printf(const std::string &str, Args... args);
```

Then we define variable length template parameters,
how to unpack the parameters?

First, we can use `sizeof...` to calculate the number of arguments:

```cpp
#include <iostream>
template<typename... Ts>
void magic(Ts... args) {
    std::cout << sizeof...(args) << std::endl;
}
```

We can pass any number of arguments to the `magic` function:

```cpp
magic();      // 0
magic(1);     // 1
magic(1, ""); // 2
```

Second, the parameters are unpacked. So far there is no simple way to process
the parameter package, but there are two classic processing methods:

**1. Recursive template function**

Recursion is a very easy way to think of and the most classic approach. This method continually recursively passes template parameters to the function, thereby achieving the purpose of recursively traversing all template parameters:

```cpp
#include <iostream>
template<typename T0>
void printf1(T0 value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
    std::cout << value << std::endl;
    printf1(args...);
}
int main() {
    printf1(1, 2, "123", 1.1);
    return 0;
}
```

**2. Variable parameter template expansion**

You should feel that this is very cumbersome. Added support for variable parameter template expansion in C++17, so you can write `printf` in a function:

```cpp
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}
```

> In fact, sometimes we use variable parameter templates, but we don't necessarily need to traverse the parameters one by one. We can use the features of `std::bind` and perfect forwarding to achieve the binding of functions and parameters, thus achieving success. The purpose of the call.

**3. Initialize list expansion**

Recursive template functions are standard practice, but the obvious drawback is that you must define a function that terminates recursion.

Here is a description of the black magic that is expanded using the initialization list:

```cpp
template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
    std::cout << value << std::endl;
    (void) std::initializer_list<T>{([&args] {
        std::cout << args << std::endl;
    }(), value)...};
}
```

In this code, the initialization list provided in C++11 and the properties of the Lambda expression (mentioned in the next section) are additionally used.

By initializing the list, `(lambda expression, value)...` will be expanded. Due to the appearance of the comma expression, the previous lambda expression is executed first, and the output of the parameter is completed.
To avoid compiler warnings, we can explicitly convert `std::initializer_list` to `void`.

### Fold expression

In C++ 17, this feature of the variable length parameter is further brought to the expression, consider the following example:

```cpp
#include <iostream>
template<typename ... T>
auto sum(T ... t) {
    return (t + ...);
}
int main() {
    std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}
```

### Non-type template parameter deduction

What we mainly mentioned above is a form of template parameters: type template parameters.

```cpp
template <typename T, typename U>
auto add(T t, U u) {
    return t+u;
}
```

The parameters of the template `T` and `U` are specific types.
But there is also a common form of template parameter that allows different literals
to be template parameters, i.e. non-type template parameters:

```cpp
template <typename T, int BufSize>
class buffer_t {
public:
    T& alloc();
    void free(T& item);
private:
    T data[BufSize];
}

buffer_t<int, 100> buf; // 100 as template parameter
```

In this form of template parameters, we can pass `100` as a parameter to the template.
After C++11 introduced the feature of type derivation, we will naturally ask, since the template parameters here.
Passing with a specific literal, can the compiler assist us in type derivation,
By using the placeholder `auto`, there is no longer a need to explicitly specify the type?
Fortunately, C++17 introduces this feature, and we can indeed use the `auto` keyword to let the compiler assist in the completion of specific types of derivation.
E.g:

```cpp
template <auto value> void foo() {
    std::cout << value << std::endl;
    return;
}

int main() {
    foo<10>();  // value as int
}
```

## 2.6 Object-oriented

### Delegate constructor

C++11 introduces the concept of a delegate construct, which allows a constructor to call another constructor
in a constructor in the same class, thus simplifying the code:

```cpp
#include <iostream>
class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() { // delegate Base() constructor
        value2 = value;
    }
};

int main() {
    Base b(2);
    std::cout << b.value1 << std::endl;
    std::cout << b.value2 << std::endl;
}
```

### Inheritance constructor

In traditional C++, constructors need to pass arguments one by one if they need inheritance, which leads to inefficiency. C++11 introduces the concept of inheritance constructors using the keyword using:

```cpp
#include <iostream>
class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() { // delegate Base() constructor
        value2 = value;
    }
};
class Subclass : public Base {
public:
    using Base::Base; // inheritance constructor
};
int main() {
    Subclass s(3);
    std::cout << s.value1 << std::endl;
    std::cout << s.value2 << std::endl;
}
```

### Explicit virtual function overwrite

In traditional C++, it is often prone to accidentally overloading virtual functions. E.g:

```cpp
struct Base {
    virtual void foo();
};
struct SubClass: Base {
    void foo();
};
```

`SubClass::foo` may not be a programmer trying to overload a virtual function, just adding a function with the same name. Another possible scenario is that when the virtual function of the base class is deleted, the subclass owns the old function and no longer overloads the virtual function and turns it into a normal class method, which has catastrophic consequences.

C++11 introduces the two keywords `override` and `final` to prevent this from happening.

### override

When overriding a virtual function, introducing the `override` keyword will explicitly tell the compiler to overload, and the compiler will check if the base function has such a virtual function, otherwise it will not compile:

```cpp
struct Base {
    virtual void foo(int);
};
struct SubClass: Base {
    virtual void foo(int) override; // legal
    virtual void foo(float) override; // illegal, no virtual function in super class
};
```

### final

`final` is to prevent the class from being continued to inherit and to terminate
the virtual function to continue to be overloaded.

```cpp
struct Base {
    virtual void foo() final;
};
struct SubClass1 final: Base {
}; // legal

struct SubClass2 : SubClass1 {
}; // illegal, SubClass1 has final

struct SubClass3: Base {
    void foo(); // illegal, foo has final
};
```

### Explicit delete default function

In traditional C++, if the programmer does not provide it, the compiler will default to generating default constructors, copy constructs, assignment operators, and destructors for the object. Besides, C++ also defines operators such as `new` `delete` for all classes. This part of the function can be overridden when the programmer needs it.

This raises some requirements: the ability to accurately control the generation of default functions cannot be controlled. For example, when copying a class is prohibited, the copy constructor and the assignment operator must be declared as `private`. Trying to use these undefined functions will result in compilation or link errors, which is a very unconventional way.

Also, the default constructor generated by the compiler cannot exist at the same time as the user-defined constructor. If the user defines any constructor, the compiler will no longer generate the default constructor, but sometimes we want to have both constructors at the same time, which is awkward.

C++11 provides a solution to the above requirements, allowing explicit declarations to take or reject functions that come with the compiler. E.g:

```cpp
class Magic {
    public:
    Magic() = default; // explicit let compiler use default constructor
    Magic& operator=(const Magic&) = delete; // explicit declare refuse constructor
    Magic(int magic_number);
}
```

### Strongly typed enumerations

In traditional C++, enumerated types are not type-safe, and enumerated types are treated as integers, which allows two completely different enumerated types to be directly compared (although the compiler gives the check, but not all), ** Even the enumeration value names of different enum types in the same namespace cannot be the same**, which is usually not what we want to see.

C++11 introduces an enumeration class and declares it using the syntax of `enum class`:

```cpp
enum class new_enum : unsigned int {
    value1,
    value2,
    value3 = 100,
    value4 = 100
};
```

The enumeration thus defined implements type safety. First, it cannot be implicitly converted to an integer, nor can it be compared to integer numbers, and it is even less likely to compare enumerated values of different enumerated types. But if the values specified are the same between the same enumerated values, then you can compare:

```cpp
if (new_enum::value3 == new_enum::value4) { // true
    std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
}
```

In this syntax, the enumeration type is followed by a colon and a type keyword to specify the type of the enumeration value in the enumeration, which allows us to assign a value to the enumeration (int is used by default when not specified).

And we want to get the value of the enumeration value, we will have to explicitly type conversion, but we can overload the `<<` operator to output, you can collect the following code snippet:

```cpp
#include <iostream>
template<typename T>
std::ostream& operator<<(
    typename std::enable_if<std::is_enum<T>::value,
        std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
```

At this point, the following code will be able to be compiled:

```cpp
std::cout << new_enum::value3 << std::endl
```

## Conclusion

This section introduces the enhancements to language usability in modern C++, which I believe are the most important features that almost everyone needs to know and use:

1. Auto type derivation
2. Scope for iteration
3. Initialization list
4. Variable parameter template

## Exercises

1. Using structured binding, implement the following functions with just one line of function code:

   ```cpp
   #include <string>
   #include <map>
   #include <iostream>

   template <typename Key, typename Value, typename F>
   void update(std::map<Key, Value>& m, F foo) {
       // TODO:
   }
   int main() {
       std::map<std::string, long long int> m {
           {"a", 1},
           {"b", 2},
           {"c", 3}
       };
       update(m, [](std::string key) {
           return std::hash<std::string>{}(key);
       });
       for (auto&& [key, value] : m)
           std::cout << key << ":" << value << std::endl;
   }
   ```

2. Try to implement a function for calculating the mean with [Fold Expression](#Fold-expression), allowing any arguments to be passed in.

> Refer to the answer [see this](../../exercises/2).

[Table of Content](./toc.md) | [Previous Chapter](./01-intro.md) | [Next Chapter: Language Runtime Enhancements](./03-runtime.md)

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).
