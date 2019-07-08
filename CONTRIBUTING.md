# 如何参与贡献

[![](https://img.shields.io/badge/chat-%E4%BA%A4%E6%B5%81-667ed5.svg)](./assets/community.md) 

## 提交 Issue

『C++ 11/14/17/20』的 issue 用于追踪书中存在的原则性的描述错误、存在的 `typo` 错误，以及向本书作者提问等。

- 通常情况下，你可能会发现书中某个段落存在错别字、语义错误、文法错误等。
这都是 `typo` 错误。如果该错误已经对你的阅读造成了一定障碍，
你也强烈的认为该 `typo` 也会影响到其他人的阅读，
那么非常欢迎[提交 issue](https://github.com/changkun/modern-cpp-tutorial/issues) 
来报告 `typo` 错误。

- 对于书中存在的原则性错误，例如对源码进行分析的内容产生明显的错误、
且内容对其他人会产生严重的误导，请不要犹豫，
立即[提交 issue](https://github.com/changkun/modern-cpp-tutorial/issues) 来报告此错误，以免继续传播错误的知识。
如果可以，也请附上相关改进说明。通常情况下，如果存在这类问题，我们鼓励你一并提交改进 PR。

- 如果你在阅读本书的时候发现有部分内容难于理解，也欢迎[提交 issue](https://github.com/changkun/modern-cpp-tutorial/issues) 来询问作者表达你的疑惑。
作者会根据实际情况重新优化这一部分的内容，进而帮助他人更易阅读这部分的内容。

- 我们也欢迎你提交针对本书内容的相关建议，具体来说如果你认为书中未涉及的某个模块或者文件的源码值得讨论，也欢迎 [提交 issue](https://github.com/changkun/go-under-the-hood/issues) 来进一步讨论。

## 提交 Pull request

『C++ 11/14/17/20』是一本开源书籍，任何人都可以参与贡献自己 PR。但在提交 PR 之前请仔细阅读下面的说明：

- 当你认为需要提交一个 PR 时，请确保 [issue 列表](https://github.com/changkun/modern-cpp-tutorial/issues)中，已经包含了你想要解决的问题。
如果没有，请参考**提交 Issue** 一节中的描述，提交你的 issue，再提交你的 PR。

- 当你准备提交一个 typo 错误的 PR 时，请确保你的 PR 改进了 **超过 50 个汉字(或英文单词)** 的 `typo` 错误，否则请不要提交 PR。
- 对于一个修复原则性错误的 PR，请不要犹豫，笔者对此表示非常感谢！
- 如果非常喜欢本书，以至于希望参与本书的合著，成为作者，请发邮件询问：`hi at changkun dot us`。

本仓库提供了多种阅读方式，如果你提交一个 Pull request，则请确保你检查的如下的 checklist：

- [ ] 只改动原书正文 `book` 下的部分内容，不涉及代码片段的修改，则无需进行修改
- [ ] 如果同时还改动了正文中的代码片段，则需要同步 `code` 文件夹下对应的代码片段
- [ ] 如果改动还涉及习题的设计，则需要同步 `exercises` 文件夹下的内容
