title = '高速上手 C++11/14/17'
filename = 'modern-cpp-tutorial'
outputname='modern-cpp-tutorial'

all: pdf

pdf: markdown
	@echo "Compiling PDF file..."
	@pandoc -s $(filename).md -o $(filename).pdf \
		--title-prefix $(title) \
		--listings -H meta/cpp-listings.tex \
		--template=meta/template.tex \
		--normalize \
		--smart \
		--latex-engine=`which xelatex`
	@echo "Done."
	@rm *.md

markdown:
	@echo "Copy markdown files..."
	@cp -r ../book/* .
	@echo "Aggregating markdown files..."
	@python3 aggregator.py

clean:
	rm -rf *.md *.pdf

.PHONY: markdown pdf clean