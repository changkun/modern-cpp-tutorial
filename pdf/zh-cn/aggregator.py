# !/usr/bin/env python3
# author: changkun<hi[at]changkun.de>

import os, io

chapters = ['00-preface.md', '01-intro.md',  '02-usability.md', '03-runtime.md', '04-containers.md', '05-pointers.md', '06-regex.md', '07-thread.md', '08-filesystem.md', '09-others.md', '10-cpp20.md', 'appendix1.md', 'appendix2.md']

ignores = ['TOC', '返回目录', '许可', 'license']

head = """---
title: "现代 C++ 教程：高速上手 C++11/14/17/20"
author: 欧长坤 <hi[at]changkun.de>
copyright: cc-by-nc-nd 4.0
---
"""

with io.open('modern-cpp-tutorial.md', 'w', encoding='utf8') as outfile:
    outfile.write(head)
    for chapter in chapters:
        if os.path.isfile(chapter):
            with open(chapter) as ch:
                outfile.write('\n')
                for line in ch:
                    if any(keyword in line for keyword in ignores):
                        continue
                    else:
                        outfile.write(line)