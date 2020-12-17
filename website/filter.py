# !/usr/bin/env python3
# author: changkun<hi[at]changkun.de>
import os
import re

source_dir = [
    '../book/zh-cn/',
    '../book/en-us/'
]

destination_dir = [
    './src/modern-cpp/zh-cn/',
    './src/modern-cpp/en-us/'
]

chapters = ['00-preface.md', '01-intro.md',  '02-usability.md', '03-runtime.md', '04-containers.md', '05-pointers.md', '06-regex.md', '07-thread.md', '08-filesystem.md', '09-others.md', '10-cpp20.md', 'appendix1.md', 'appendix2.md']

ignores = ['TOC', '返回目录', '许可', 'license', 'Table of Content', 'License']

for index, source in enumerate(source_dir):
    for chapter in chapters:
        dst_filepath = destination_dir[index] + chapter[:-3]
        os.makedirs(dst_filepath)
        print(dst_filepath)
        print(dst_filepath + '/index.md')
        with open(source+chapter, 'r', encoding='utf-8') as source_file:
            with open(dst_filepath + '/index.md', 'w', encoding='utf-8') as output_file:
                for line in source_file:
                    if any(keyword in line for keyword in ignores):
                        continue
                    else:
                        output_file.write(re.sub(r'(./)(.*?)(.md)', r'../\2/index.html', line))
