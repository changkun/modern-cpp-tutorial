# changkun.de/modern-cpp

Welcome to Modern C++ Tutorial! This site is built with [hexo](http://hexo.io/). Site content is written in Markdown format located in `../book`. And all static files will be built into `./public`, which is served by a nginx server at [changkun.de](https://changkun.de).

## Requirements

- node.js
- npm

## Developing

Start from the terminal:

```
$ make    # build
$ make s  # start serve
```

Note that:

1. `make` command will check and install all dependencies for you, then build the website into `/public`;
2. `make s` command will serve the static files inside `/public` folder.
3. when you changed the website content, you will need re-compile the website, which means you need use `make` again.

## On Translations

The website is originally in German, but we are currently working on support more languages, such as English and Mandarin Chinese.

### Mandarin Chinese

* Translation directory - [/v2/modern-cpp/](./src/modern-cpp/cn/)

## English

- Translation directory - [/v2/en/](./src/v2/en/)

## Contributors

- [Ou Changkun](https://changkun.de)