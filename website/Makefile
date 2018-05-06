all:
	rm -rf public db.json
	node install.js
	rm -rf src/modern-cpp/book
	python3 filter.py
	rm -rf ./src/modern-cpp/assets/cover-2nd.png
	rm -rf ./src/modern-cpp/assets/figures
	cp ../assets/cover-2nd.png ./src/modern-cpp/assets/cover-2nd.png
	cp -r ../assets/figures ./src/modern-cpp/assets/figures
	hexo generate
	mv public/index.html public/modern-cpp/index.html
s:
	node_modules/serve/bin/serve.js ./public
clean:
	rm -rf ./src/modern-cpp/assets/cover-2nd.png
	rm -rf ./src/modern-cpp/assets/figures
	rm -rf public db.json src/modern-cpp/book
