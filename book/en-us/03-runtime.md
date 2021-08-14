---
title: "Chapter 03: Language Runtime Enhancements"
type: book-en-us
order: 3
---

# Chapter 03: Language Runtime Enhancements

[TOC]

## 3.1 Lambda Expression

Lambda expressions are one of the most important features in modern C++, and Lambda expressions provide a feature like anonymous functions.
Anonymous functions are used when a function is needed, but you don’t want to use a name to call a function. There are many, many scenes like this.
So anonymous functions are almost standard in modern programming languages.

### Basics

The basic syntax of a Lambda expression is as follows:

```
[capture list] (parameter list) mutable(optional) exception attribute -> return type {
// function body
}
```

The above grammar rules are well understood except for the things in `[capture list]`,
except that the function name of the general function is omitted.
The return value is in the form of a `->`
(we have already mentioned this in the tail return type earlier in the previous section).

The so-called capture list can be understood as a type of parameter.
The internal function body of a lambda expression cannot use variables outside
the body of the function by default.
At this time, the capture list can serve to transfer external data.
According to the behavior passed,
the capture list is also divided into the following types:

#### 1. Value capture

Similar to parameter passing, the value capture is based on the fact that
the variable can be copied, except that the captured variable is copied
when the lambda expression is created, not when it is called:

```cpp
void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // At this moment, stored_value == 1, and value == 100.
    // Because copy_value has copied when its was created.
}
```

#### 2. Reference capture

Similar to a reference pass, the reference capture saves the reference and the value changes.

```cpp
void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // At this moment, stored_value == 100, value == 100.
    // Because copy_value stores reference
}
```

#### 3. Implicit capture

Manually writing a capture list is sometimes very complicated.
This mechanical work can be handled by the compiler.
At this point, you can write a `&` or `=` to the compiler to
declare the reference or value capture.

To summarize, capture provides the ability for lambda expressions
to use external values. The four most common forms of
capture lists can be:

- \[\] empty capture list
- \[name1, name2, ...\] captures a series of variables
- \[&\] reference capture, let the compiler deduce the reference list by itself
- \[=\] value capture, let the compiler deduce the value list by itself

#### 4. Expression capture

> This section needs to understand the rvalue references and smart pointers that
> will be mentioned later.

The value captures and reference captures mentioned above are variables that have been
declared in the outer scope, so these capture methods capture the lvalue
and not capture the rvalue.

C++14 gives us the convenience of allowing the captured members to be initialized
with arbitrary expressions, which allows the capture of rvalues.
The type of the captured variable being declared is judged according to the expression,
and the judgment is the same as using `auto`:

```cpp
#include <iostream>
#include <memory>  // std::make_unique
#include <utility> // std::move

void lambda_expression_capture() {
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };
    std::cout << add(3,4) << std::endl;
}
```

In the above code, `important` is an exclusive pointer that cannot be caught by value capture using `=`.
At this time we need to transfer it to the rvalue and
initialize it in the expression.

### Generic Lambda

In the previous section, we mentioned that the `auto` keyword cannot be used
in the parameter list because it would conflict with the functionality of the template.
But Lambda expressions are not ordinary functions, so Lambda expressions are not templated.
This has caused us some trouble: the parameter table cannot be generalized,
and the parameter table type must be clarified.

Fortunately, this trouble only exists in C++11, starting with C++14.
The formal parameters of the Lambda function can use the `auto` keyword
to generate generic meanings:

```cpp
void lambda_generic() {
    auto generic = [](auto x, auto y) {
        return x+y;
    };

    std::cout << generic(1, 2) << std::endl;
    std::cout << generic(1.1, 2.2) << std::endl;
}
```

## 3.2 Function Object Wrapper

Although the features are part of the standard library and not found in runtime,
it enhances the runtime capabilities of the C++ language.
This part of the content is also very important, so put it here for the introduction.

### `std::function`

The essence of a Lambda expression is an object of a class type (called a closure type)
that is similar to a function object type (called a closure object).
When the capture list of a Lambda expression is empty, the closure object
can also be converted to a function pointer value for delivery, for example:

```cpp
#include <iostream>
using foo = void(int);  // function pointer
void functional(foo f) {
    f(1);
}
int main() {
    auto f = [](int value) {
        std::cout << value << std::endl;
    };
    functional(f);  // call by function pointer
    f(1);           // call by lambda expression
    return 0;
}
```

The above code gives two different forms of invocation, one is to call Lambda
as a function type, and the other is to directly call a Lambda expression.
In C++11, these concepts are unified.
The type of object that can be called is collectively called the callable type.
This type is introduced by `std::function`.

C++11 `std::function` is a generic, polymorphic function wrapper
whose instances can store, copy, and call any target entity that can be called.
It is also an existing callable to C++. A type-safe package of entities (relatively,
the call to a function pointer is not type-safe), in other words,
a container of functions. When we have a container for functions,
we can more easily handle functions and function pointers as objects. e.g:

```cpp
#include <functional>
#include <iostream>

int foo(int para) {
    return para;
}

int main() {
    // std::function wraps a function that take int paremeter and returns int value
    std::function<int(int)> func = foo;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1+value+important;
    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
}
```

### `std::bind` and `std::placeholder`

And `std::bind` is used to bind the parameters of the function call.
It solves the requirement that we may not always be able to get all the parameters
of a function at one time. Through this function, we can Part of the call parameters
are bound to the function in advance to become a new object,
and then complete the call after the parameters are complete. e.g:

```cpp
int foo(int a, int b, int c) {
    ;
}
int main() {
    // bind parameter 1, 2 on function foo, and use std::placeholders::_1 as placeholder
    // for the first parameter.
    auto bindFoo = std::bind(foo, std::placeholders::_1, 1,2);
    // when call bindFoo, we only need one param left
    bindFoo(1);
}
```

> **Tip:** Note the magic of the `auto` keyword. Sometimes we may not be familiar
> with the return type of a function, but we can circumvent this problem by using `auto`.

## 3.3 rvalue Reference

rvalue references are one of the important features introduced by C++11
that are synonymous with Lambda expressions. Its introduction solves
a large number of historical issues in C++.
Eliminating extra overhead such as `std::vector`, `std::string`,
and making the function object container `std::function` possible.

### lvalue, rvalue, prvalue, xvalue

To understand what the rvalue reference is all about, you must have a clear
understanding of the lvalue and the rvalue.

**lvalue, left value**, as the name implies, is the value to the left of the assignment
symbol. To be precise, an lvalue is a persistent object that still exists after
an expression (not necessarily an assignment expression).

**Rvalue, right value**, the value on the right refers to the temporary object
that no longer exists after the expression ends.

In C++11, in order to introduce powerful rvalue references,
the concept of rvalue values ​​is further divided into:
prvalue, and xvalue.

**pvalue, pure rvalue**, purely rvalue, either purely literal,
such as `10`, `true`; either the result of the evaluation is equivalent to
a literal or anonymous temporary object, for example `1+2`.
Temporary variables returned by non-references, temporary variables generated
by operation expressions, original literals, and Lambda expressions
are all pure rvalue values.

Note that a string literal became rvalue in a class, and remains an lvalue in other cases (e.g., in a function)：

```cpp
class Foo {
        const char*&& right = "this is a rvalue";
public:
        void bar() {
            right = "still rvalue"; // the string literal is a rvalue
        }
};

int main() {
    const char* const &left = "this is an lvalue"; // the string literal is an lvalue
}
```

**xvalue, expiring value** is the concept proposed by C++11 to introduce
rvalue references (so in traditional C++, pure rvalue and rvalue are the same concepts),
a value that is destroyed but can be moved.

It would be a little hard to understand the xvalue,
let's look at the code like this:

```cpp
std::vector<int> foo() {
    std::vector<int> temp = {1, 2, 3, 4};
    return temp;
}

std::vector<int> v = foo();
```

In such code, as far as the traditional understanding is concerned,
the return value `temp` of the function `foo` is internally created
and then assigned to `v`, whereas when `v` gets this object, the entire `temp` is copied.
And then destroy `temp`, if this `temp` is very large, this will cause a lot of extra
overhead (this is the problem that traditional C++ has been criticized for).
In the last line, `v` is the lvalue, and the value returned by `foo()` is
the rvalue (which is also a pure rvalue).

However, `v` can be caught by other variables, and the return value generated by `foo()`
is used as a temporary value. Once copied by `v`, it will be destroyed immediately, and
cannot be obtained or modified. The xvalue defines behavior in which temporary values ​​can be
identified while being able to be moved.

After C++11, the compiler did some work for us, where the lvalue `temp`
is subjected to this implicit rvalue conversion,
equivalent to `static_cast<std::vector<int> &&>(temp)`,
where `v` here moves the value returned by `foo` locally.
This is the move semantics we will mention later.

### rvalue reference and lvalue reference

To get a xvalue, you need to use the declaration of the rvalue reference: `T &&`,
where `T` is the type.
The statement of the rvalue reference extends the lifecycle of this temporary value,
and as long as the variable is alive, the xvalue will continue to survive.

C++11 provides the `std::move` method to unconditionally convert
lvalue parameters to rvalues.
With it we can easily get a rvalue temporary object, for example:

```cpp
#include <iostream>
#include <string>

void reference(std::string& str) {
    std::cout << "lvalue" << std::endl;
}
void reference(std::string&& str) {
    std::cout << "rvalue" << std::endl;
}

int main()
{
    std::string  lv1 = "string,";       // lv1 is a lvalue
    // std::string&& r1 = s1;           // illegal, rvalue can't ref to lvalue
    std::string&& rv1 = std::move(lv1); // legal, std::move can convert lvalue to rvalue
    std::cout << rv1 << std::endl;      // string,

    const std::string& lv2 = lv1 + lv1; // legal, const lvalue reference can extend temp variable's lifecycle
    // lv2 += "Test";                   // illegal, const ref can't be modified
    std::cout << lv2 << std::endl;      // string,string,

    std::string&& rv2 = lv1 + lv2;      // legal, rvalue ref extend lifecycle
    rv2 += "string";                    // legal, non-const reference can be modified
    std::cout << rv2 << std::endl;      // string,string,string,string

    reference(rv2);                     // output: lvalue

    return 0;
}
```

`rv2` refers to an rvalue, but since it is a reference,
`rv2` is still an lvalue.

Note that there is a very interesting historical issue here,
let's look at the following code:

```cpp
#include <iostream>

int main() {
    // int &a = std::move(1); // illegal, non-const lvalue reference cannot ref rvalue
    const int &b = std::move(1); // legal, const lvalue reference can

    std::cout << b << std::endl;
}
```

The first question, why not allow non-linear references to bind to non-lvalues?
This is because there is a logic error in this approach:

```cpp
void increase(int & v) {
    v++;
}
void foo() {
    double s = 1;
    increase(s);
}
```

Since `int&` can't reference a parameter of type `double`,
you must generate a temporary value to hold the value of `s`.
Thus, when `increase()` modifies this temporary value,
`s` itself is not modified after the call is completed.

The second question, why do constant references allow binding to non-lvalues?
The reason is simple because Fortran needs it.

### Move semantics

Traditional C++ has designed the concept of copy/copy for class objects
through copy constructors and assignment operators,
but to implement the movement of resources,
The caller must use the method of copying and then destructing first,
otherwise, you need to implement the interface of the mobile object yourself.
Imagine moving your home directly to your new home instead of
copying everything (rebuy) to your new home.
Throwing away (destroying) all the original things is a very anti-human thing.

Traditional C++ does not distinguish between the concepts of "mobile" and "copy",
resulting in a large amount of data copying, wasting time and space.
The appearance of rvalue references solves the confusion of these two concepts,
for example:

```cpp
#include <iostream>
class A {
public:
    int *pointer;
    A():pointer(new int(1)) {
        std::cout << "construct" << pointer << std::endl;
    }
    A(A& a):pointer(new int(*a.pointer)) {
        std::cout << "copy" << pointer << std::endl;
    } // meaningless object copy
    A(A&& a):pointer(a.pointer) {
        a.pointer = nullptr;
        std::cout << "move" << pointer << std::endl;
    }
    ~A(){
        std::cout << "destruct" << pointer << std::endl;
        delete pointer;
    }
};
// avoid compiler optimization
A return_rvalue(bool test) {
    A a,b;
    if(test) return a; // equal to static_cast<A&&>(a);
    else return b;     // equal to static_cast<A&&>(b);
}
int main() {
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
    return 0;
}
```

In the code above:

1. First construct two `A` objects inside `return_rvalue`, and get the output of the two constructors;
2. After the function returns, it will generate a xvalue, which is referenced by the moving structure of `A` (`A(A&&)`), thus extending the life cycle, and taking the pointer in the rvalue and saving it to `obj`. In the middle, the pointer to the xvalue is set to `nullptr`, which prevents the memory area from being destroyed.

This avoids meaningless copy constructs and enhances performance.
Let's take a look at an example involving a standard library:

```cpp
#include <iostream> // std::cout
#include <utility>  // std::move
#include <vector>   // std::vector
#include <string>   // std::string

int main() {

    std::string str = "Hello world.";
    std::vector<std::string> v;

    // use push_back(const T&), copy
    v.push_back(str);
    // "str: Hello world."
    std::cout << "str: " << str << std::endl;

    // use push_back(const T&&), no copy
    // the string will be moved to vector, and therefore std::move can reduce copy cost
    v.push_back(std::move(str));
    // str is empty now
    std::cout << "str: " << str << std::endl;

    return 0;
}
```

### Perfect forwarding

As we mentioned earlier, the rvalue reference of a declaration is actually an lvalue.
This creates problems for us to parameterize (pass):

```cpp
#include <iostream>
#include <utility>
void reference(int& v) {
    std::cout << "lvalue reference" << std::endl;
}
void reference(int&& v) {
    std::cout << "rvalue reference" << std::endl;
}
template <typename T>
void pass(T&& v) {
    std::cout << "          normal param passing: ";
    reference(v);
}
int main() {
    std::cout << "rvalue pass:" << std::endl;
    pass(1);

    std::cout << "lvalue pass:" << std::endl;
    int l = 1;
    pass(l);

    return 0;
}
```

For `pass(1)`, although the value is the rvalue, since `v` is a reference, it is also an lvalue.
Therefore `reference(v)` will call `reference(int&)` and output lvalue.
For `pass(l)`, `l` is an lvalue, why is it successfully passed to `pass(T&&)`?

This is based on the **reference collapsing rule**: In traditional C++, we are not able to continue to reference a reference type.
However,
C++ has relaxed this practice with the advent of rvalue references,
resulting in a reference collapse rule that allows us to reference references,
both lvalue and rvalue. But follow the rules below:

| Function parameter type | Argument parameter type | Post-derivation function parameter type |
| :---------------------: | :---------------------: | :-------------------------------------: |
|           T&            |       lvalue ref        |                   T&                    |
|           T&            |       rvalue ref        |                   T&                    |
|           T&&           |       lvalue ref        |                   T&                    |
|           T&&           |       rvalue ref        |                   T&&                   |

Therefore, the use of `T&&` in a template function may not be able to make an rvalue reference, and when a lvalue is passed, a reference to this function will be derived as an lvalue.
More precisely, ** no matter what type of reference the template parameter is, the template parameter can be derived as a right reference type** if and only if the argument type is a right reference.
This makes `v` successful delivery of lvalues.

Perfect forwarding is based on the above rules. The so-called perfect forwarding is to let us pass the parameters,
Keep the original parameter type (lvalue reference keeps lvalue reference, rvalue reference keeps rvalue reference).
To solve this problem, we should use `std::forward` to forward (pass) the parameters:

```cpp
#include <iostream>
#include <utility>
void reference(int& v) {
    std::cout << "lvalue reference" << std::endl;
}
void reference(int&& v) {
    std::cout << "rvalue reference" << std::endl;
}
template <typename T>
void pass(T&& v) {
    std::cout << "          normal param passing: ";
    reference(v);
    std::cout << "       std::move param passing: ";
    reference(std::move(v));
    std::cout << "    std::forward param passing: ";
    reference(std::forward<T>(v));
    std::cout << "static_cast<T&&> param passing: ";
    reference(static_cast<T&&>(v));
}
int main() {
    std::cout << "rvalue pass:" << std::endl;
    pass(1);

    std::cout << "lvalue pass:" << std::endl;
    int l = 1;
    pass(l);

    return 0;
}
```

The outputs are:

```
rvalue pass:
          normal param passing: lvalue reference
       std::move param passing: rvalue reference
    std::forward param passing: rvalue reference
static_cast<T&&> param passing: rvalue reference
lvalue pass:
          normal param passing: lvalue reference
       std::move param passing: rvalue reference
    std::forward param passing: lvalue reference
static_cast<T&&> param passing: lvalue reference
```

Regardless of whether the pass parameter is an lvalue or an rvalue, the normal pass argument will forward the argument as an lvalue.
So `std::move` will always accept an lvalue, which forwards the call to `reference(int&&)` to output the rvalue reference.

Only `std::forward` does not cause any extra copies and ** perfectly forwards ** (passes) the arguments of the function to other functions that are called internally.

`std::forward` is the same as `std::move`, and nothing is done. `std::move` simply converts the lvalue to the rvalue.
`std::forward` is just a simple conversion of the parameters. From the point of view of the phenomenon,
`std::forward<T>(v)` is the same as `static_cast<T&&>(v)`.

Readers may be curious as to why a statement can return values for two types of returns.
Let's take a quick look at the concrete implementation of `std::forward`. `std::forward` contains two overloads:

```cpp
template<typename _Tp>
constexpr _Tp&& forward(typename std::remove_reference<_Tp>::type& __t) noexcept
{ return static_cast<_Tp&&>(__t); }

template<typename _Tp>
constexpr _Tp&& forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
{
    static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
        " substituting _Tp is an lvalue reference type");
    return static_cast<_Tp&&>(__t);
}
```

In this implementation, the function of `std::remove_reference` is to eliminate references in the type.
And `std::is_lvalue_reference` is used to check if the type derivation is correct, in the second implementation of `std::forward`.
Check that the received value is indeed an lvalue, which in turn reflects the collapse rule.

When `std::forward` accepts an lvalue, `_Tp` is deduced to the lvalue, so the return value is the lvalue; and when it accepts the rvalue,
`_Tp` is derived as an rvalue reference, and based on the collapse rule, the return value becomes the rvalue of `&& + &&`.
It can be seen that the principle of `std::forward` is to make clever use of the differences in template type derivation.

At this point, we can answer the question: Why is `auto&&` the safest way to use looping statements?
Because when `auto` is pushed to a different lvalue and rvalue reference, the collapsed combination with `&&` is perfectly forwarded.

## Conclusion

This chapter introduces the most important runtime enhancements in modern C++, and I believe that all the features mentioned in this section are worth knowing:

Lambda expression

1. Function object container std::function
2. rvalue reference

[Table of Content](./toc.md) | [Previous Chapter](./02-usability.md) | [Next Chapter: Containers](./04-containers.md)

## Further Readings

- [Bjarne Stroustrup, The Design and Evolution of C++](https://www.amazon.com/Design-Evolution-C-Bjarne-Stroustrup/dp/0201543303)

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work was written by [Ou Changkun](https://changkun.de) and licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>. The code of this repository is open sourced under the [MIT license](../../LICENSE).
