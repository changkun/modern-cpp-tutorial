'use strict';

// Helpers shared by every template: which edition a page belongs to, the
// words each edition uses, and the small rewrites applied to a chapter's
// rendered HTML. Hexo loads every file in a theme's scripts/ directory.

const UI = {
  en: {
    htmlLang: 'en',
    site: 'Modern C++ Tutorial',
    tagline: 'C++11 to C++26 On the Fly',
    author: 'Changkun Ou',
    byline: 'Changkun Ou',
    edition: 'Second Edition',
    blurb: 'A fast, comprehensive guide to the features of modern C++, from C++11 through C++26. It explains not only how each feature works, but the problem it was introduced to solve.',
    start: 'Start reading',
    pdf: 'PDF',
    downloadPdf: 'Download PDF',
    epub: 'EPUB',
    contents: 'Contents',
    book: 'Book',
    about: 'About',
    onThisPage: 'On this page',
    prev: 'Previous',
    next: 'Next',
    menu: 'Table of contents',
    skip: 'Skip to content',
    other: '中文',
    otherTitle: '阅读中文版',
    otherPref: 'zh',
    edit: 'Edit this page',
    issue: 'Report an issue',
    donate: 'Donate',
    copy: 'Copy',
    copied: 'Copied',
    license: 'Text <a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/">CC BY-NC-ND 4.0</a> · Code <a href="https://opensource.org/licenses/MIT">MIT</a>',
    bookType: 'book-en-us',
    aboutType: 'about-en',
    pdfFile: 'pdf/modern-cpp-tutorial-en-us.pdf',
    epubFile: 'epub/modern-cpp-tutorial-en-us.epub',
    cover: 'assets/cover-2nd-en-web.jpg',
    donateHref: '/modern-cpp/about/en/donate.html',
    coverAlt: 'Modern C++ Tutorial book cover',
    logo: 'assets/cover-2nd-en-logo.png',
    home: '/modern-cpp/en/'
  },
  zh: {
    htmlLang: 'zh-CN',
    site: '现代 C++ 教程',
    tagline: '高速上手 C++11 到 C++26',
    author: '欧长坤',
    byline: '欧长坤 著',
    edition: '第二版',
    blurb: '高速上手现代 C++ 特性的全面教程，覆盖 C++11 到 C++26。不只讲每个特性怎么用，也讲清它为解决什么问题而诞生。',
    start: '开始阅读',
    pdf: 'PDF',
    downloadPdf: '下载 PDF',
    epub: 'EPUB',
    contents: '目录',
    book: '正文',
    about: '关于',
    onThisPage: '本页目录',
    prev: '上一章',
    next: '下一章',
    menu: '目录',
    skip: '跳到正文',
    other: 'EN',
    otherTitle: 'Read in English',
    otherPref: 'en',
    edit: '在 GitHub 上编辑此页',
    issue: '报告问题',
    donate: '资助作者',
    copy: '复制',
    copied: '已复制',
    license: '正文采用 <a rel="license" href="https://creativecommons.org/licenses/by-nc-nd/4.0/">CC BY-NC-ND 4.0</a> 协议，代码采用 <a href="https://opensource.org/licenses/MIT">MIT</a> 协议',
    bookType: 'book-zh-cn',
    aboutType: 'about',
    pdfFile: 'pdf/modern-cpp-tutorial-zh-cn.pdf',
    epubFile: 'epub/modern-cpp-tutorial-zh-cn.epub',
    cover: 'assets/cover-2nd-web.jpg',
    donateHref: '/modern-cpp/about/donate.html',
    coverAlt: '现代 C++ 教程封面',
    logo: 'assets/cover-2nd-logo.png',
    home: '/modern-cpp/'
  }
};

const REPO = 'https://github.com/changkun/modern-cpp-tutorial';

// One stamp per build, appended to the stylesheet and script URLs so a
// redeploy is never served a stale copy from a reader's cache.
const BUILD = Date.now().toString(36);

function isIndex(page) {
  return page.layout === 'index' || page.path === 'index.html';
}

function mcppLang(page) {
  const t = page.type || '';
  return t === 'book-en-us' || t === 'about-en' ? 'en' : 'zh';
}

// The same page in the other edition: a chapter or About page has a twin at
// the mirrored path; anything else goes to the other landing.
function otherHref(page) {
  const p = page.path || '';
  if (p.indexOf('zh-cn/') !== -1) return '/' + p.replace('zh-cn/', 'en-us/').replace(/index\.html$/, '');
  if (p.indexOf('en-us/') !== -1) return '/' + p.replace('en-us/', 'zh-cn/').replace(/index\.html$/, '');
  if (p.indexOf('/about/en/') !== -1) return '/' + p.replace('/about/en/', '/about/');
  if (p.indexOf('/about/') !== -1) return '/' + p.replace('/about/', '/about/en/');
  return mcppLang(page) === 'en' ? UI.zh.home : UI.en.home;
}

// Split a chapter title into its label and its name:
// "Chapter 02: Language Usability Enhancements", "第 2 章 语言可用性的强化",
// "Appendix 1: …", "附录 1：…". A title without a label ("Preface") is kept whole.
function chapterParts(title) {
  const s = String(title || '');
  const m = /^((?:Chapter|Appendix)\s+\d+)\s*[:：]\s*([\s\S]+)$/.exec(s)
    || /^(附录\s*\d+)\s*[:：]\s*([\s\S]+)$/.exec(s)
    || /^(第\s*\d+\s*章)\s*([\s\S]+)$/.exec(s);
  // The preface is chapter zero, as its file name (00-preface) says.
  if (!m) return { label: '', num: /^(Preface|序言)$/.test(s) ? '00' : '', name: s };
  const n = Number(m[1].match(/\d+/)[0]);
  const appendix = /Appendix|附录/.test(m[1]);
  return { label: m[1], num: appendix ? 'A' + n : String(n).padStart(2, '0'), name: m[2] };
}

// The label shown on a code block, by its fence language. Plain text has none.
const LANGS = { cpp: 'C++', 'c++': 'C++', c: 'C', bash: 'Shell', sh: 'Shell', shell: 'Shell', console: 'Shell', plaintext: '', text: '', '': '', makefile: 'Makefile', cmake: 'CMake', json: 'JSON', python: 'Python' };

const esc = (s) => String(s).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');
const stripTags = (s) => String(s).replace(/<[^>]+>/g, '').trim();

// Rewrites of a page's rendered HTML that the Markdown cannot express.
function enhanceContent(html, title) {
  let out = String(html || '');

  // The chapter heading: its label set above the name.
  let hasH1 = false;
  out = out.replace(/<h1([^>]*)>(?:<a [^>]*class="headerlink"[^>]*><\/a>)?([\s\S]*?)<\/h1>/, (all, attrs, inner) => {
    hasH1 = true;
    const p = chapterParts(inner);
    return p.label
      ? `<h1${attrs}><span class="chapter-num">${p.label}</span>${p.name}</h1>`
      : `<h1${attrs}>${inner}</h1>`;
  });
  // About pages have no h1 and often repeat their title as the first h2.
  if (!hasH1 && title) {
    out = out.replace(/<h2[^>]*>(?:<a [^>]*class="headerlink"[^>]*><\/a>)?([\s\S]*?)<\/h2>/, (all, inner) =>
      stripTags(inner) === String(title) ? '' : all);
    out = `<h1>${esc(title)}</h1>` + out;
  }

  // "(since C++11)" / "（C++11）" under a feature heading becomes a tag.
  out = out.replace(/<p><em>[(（]((?:since )?C\+\+[^<]*?)[)）]<\/em><\/p>/g,
    '<p class="since"><span>$1</span></p>');

  // Wide tables scroll inside the column instead of widening the page.
  out = out.replace(/<table>/g, '<div class="table-wrap"><table>').replace(/<\/table>/g, '</table></div>');

  // Code blocks get a box that carries the language label and, with script,
  // a copy button; the box itself does not scroll, so neither do they.
  out = out.replace(/<pre><code class="hljs ?([\w+-]*)">([\s\S]*?)<\/code><\/pre>/g, (all, lang, code) => {
    const label = LANGS[lang.toLowerCase()] ?? lang;
    return `<div class="code"${label ? ` data-lang="${esc(label)}"` : ''}><pre><code class="hljs ${lang}">${code}</code></pre></div>`;
  });

  return out;
}

// The pages of one kind (a book edition, an About section) in reading order.
// The English landing shares its edition's type, so only titled pages count.
function pagesOf(type) {
  return this.site.pages.find({ type: type }).sort('order').toArray()
    .filter((p) => p.title && p.layout !== 'index');
}

// The page's source on GitHub, for "Edit this page".
function sourceUrl(page) {
  const src = page.source || '';
  const m = /^modern-cpp\/(zh-cn|en-us)\/([^/]+)\/index\.md$/.exec(src);
  if (m) return `${REPO}/blob/master/book/${m[1]}/${m[2]}.md`;
  if (src) return `${REPO}/blob/master/website/src/${src}`;
  return REPO;
}

hexo.extend.helper.register('mcpp_lang', mcppLang);
hexo.extend.helper.register('mcpp_ui', (page) => UI[mcppLang(page)]);
hexo.extend.helper.register('mcpp_other_href', otherHref);
hexo.extend.helper.register('mcpp_chapter', chapterParts);
hexo.extend.helper.register('mcpp_enhance', enhanceContent);
hexo.extend.helper.register('mcpp_pages', pagesOf);
hexo.extend.helper.register('mcpp_source_url', sourceUrl);
hexo.extend.helper.register('mcpp_repo', () => REPO);
hexo.extend.helper.register('mcpp_is_index', isIndex);
hexo.extend.helper.register('mcpp_build', () => BUILD);
