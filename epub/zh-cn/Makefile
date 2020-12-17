title = '现代 C++ 教程：高速上手 C++11/14/17/20'
filename = 'modern-cpp-tutorial'
outputname='modern-cpp-tutorial'
revision = $(shell git describe --always --tags)
date = $(shell date +'%Y.%m.%d-%H:%M')
all: revision epub

revision:
	@echo '---' >> meta.markdown
	@echo 'title: "现代 C++ 教程：高速上手 C++11/14/17/20"' >> meta.markdown
	@echo 'author: 欧长坤 <hi[at]changkun.de>' >> meta.markdown
	@echo 'subtitle: |' >> meta.markdown
	@echo '  此文件的内容可能过期，请检查本书网站 <https://changkun.de/modern-cpp> 及 GitHub 仓库<https://github.com/changkun/modern-cpp-tutorial> 以获取最新内容。最后更新：${date}' >> meta.markdown
	@echo 'rights: © Ou Changkun, CC BY-NC-ND 4.0.' >> meta.markdown
	@echo 'ibooks:' >> meta.markdown
	@echo '  - version: ${revision}' >> meta.markdown
	@echo '---' >> meta.markdown

epub: markdown
	@echo "Compiling PDF file..."
	pandoc -f markdown+smart --toc -t epub -o $(filename).epub \
		--highlight-style haddock \
		--epub-cover-image ../../assets/cover-2nd.png \
		--title-prefix $(title) \
		meta.markdown \
		00-preface.md.markdown \
		01-intro.md.markdown \
		02-usability.md.markdown \
		03-runtime.md.markdown \
		04-containers.md.markdown \
		05-pointers.md.markdown \
		06-regex.md.markdown \
		07-thread.md.markdown \
		08-filesystem.md.markdown \
		09-others.md.markdown \
		10-cpp20.md.markdown \
		appendix1.md.markdown \
		appendix2.md.markdown
	@echo "Done."
	rm -f *.md *.markdown

markdown:
	@echo "Copy markdown files..."
	cp -r ../../book/zh-cn/* .
	@echo "Aggregating markdown files..."
	python3 filter.py

clean:
	rm -rf *.md *.markdown

.PHONY: markdown epub clean