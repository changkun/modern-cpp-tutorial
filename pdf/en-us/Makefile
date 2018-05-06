title = 'C++11/14/17 On the Fly'
filename = 'modern-cpp-tutorial'
outputname='modern-cpp-tutorial'

all: pdf

pdf: markdown
	@echo "Compiling PDF file..."
	@pandoc -s $(filename).md -o $(outputname).pdf \
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
	@cp -r ../../book/en-us/* .
	@echo "Aggregating markdown files..."
	@python3 aggregator.py

clean:
	rm -rf *.md *.pdf

.PHONY: markdown pdf clean