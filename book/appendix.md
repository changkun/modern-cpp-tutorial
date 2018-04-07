# 附录：进一步阅读的学习材料

首先，恭喜你阅读完本书 🎉 ！笔者希望本书有提起你对现代 C++ 的兴趣。

正如本书引言部分提到的，本书只是一本带你快速领略现代 C++ 特性的读物，而非进阶学习实践『黑魔法』的内容。笔者当然也想到了这个需求，只是这样的内容非常艰深，鲜有受众。在此，笔者列出一些能够帮助你在此书基础之上进一步学习现代 C++ 的资料。

- [C++ 参考](http://en.cppreference.com/w)
- [CppCon YouTube 频道](https://www.youtube.com/user/CppCon/videos)
- [每位程序员都需要知道的内存知识(英文)](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)



需要支持以下内容：

- 语言级 bug 与修订

  + 表达式评估顺序
  + 类型系统改进 Type Punning
  + 弃用和删除的功能

- 语言增强

  + [x] 结构化绑定 Structured bindings
  + [ ] inline 变量 `inline` variables
  + [x] 新的控制结构 `constexpr` if
  + [ ] 新的聚合规则
  + [ ] `constexpr` 改进
  + [ ] 强制性 RVO 和复制 elision, Guaranteed copy elision
- 模板增强
  + [x] 折叠表达式 Fold expressions
  + [ ] 类模板参数推导 Class template deduction
  + [ ] `auto` non-type template parameters
- 库增强
  + [ ] `std::string_view`, `std::byte`
  + [ ] `std::any`, `std::variant`, `std::optional`
  + [ ] 容器改进 container 改进
  + [ ] thread 并行 STL 算法
  + [ ] 文件系统库
- 其他特性
  + [ ] Selection statements with initializers
  + [ ] Compile-time conditional statements
  + [ ] Unary `statuc_assert`
  + [ ] Nested namespace deinitions
  + [ ] Preprocessor predicate for header testing
  + [ ] Polymorphic allocators and memory resources
  + [ ] Aligned `new`
  + [ ] Improved insertion and splicing for associative constrainers
  + [ ] Math special functions
  + [ ] Variable templates for metafunctions
  + [ ] Boolean logic metafunctions
...

