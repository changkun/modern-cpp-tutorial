all:
	rm -rf public db.json
	node install.js
	rm -rf src/modern-cpp/book
	python3 filter.py
	rm -rf ./src/modern-cpp/images/cover-2nd.png
	cp ../assets/cover-2nd.png ./src/modern-cpp/images/cover-2nd.png
	hexo generate
	mv public/index.html public/modern-cpp/index.html
s:
	node_modules/serve/bin/serve.js ./public
clean:
	rm ./src/modern-cpp/images/cover-2nd.png
	rm -rf src/modern-cpp/book
	rm -rf public db.json
