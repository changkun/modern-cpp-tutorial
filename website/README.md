# changkun.de/modern-cpp

Welcome to Modern C++ Tutorial! This site is built with [hexo](http://hexo.io/). Site content was written in Markdown format located in `../book`. And all static files will be built into `./public`, which is served by a nginx server at [changkun.de](https://changkun.de).

## Requirements

- node.js
- npm

## Developing

Start from the terminal:

```
$ make    # build
$ make s  # start serve
$ make deploy  # build and rsync public/modern-cpp/ to changkunde:/www/changkun.de/modern-cpp/
```
