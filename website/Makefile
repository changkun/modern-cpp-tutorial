all: clean
	node install.js
	python3 filter.py
	cp ../assets/cover-2nd.png ./src/modern-cpp/assets/cover-2nd.png
	cp ../assets/alipay.jpg ./src/modern-cpp/assets/alipay.jpg
	cp ../assets/wechat.jpg ./src/modern-cpp/assets/wechat.jpg
	cp ../DONATE.md ./src/modern-cpp/about/
	cp -r ../assets/figures ./src/modern-cpp/assets/figures
	cp -r ../exercises ./src/modern-cpp/book/
	cp -r ../code ./src/modern-cpp/book/
	hexo generate
	mv public/index.html public/modern-cpp/index.html
s: all
	node_modules/serve/bin/serve.js ./public
clean:
	rm -rf ./src/modern-cpp/assets/cover-2nd.png
	rm -rf ./src/modern-cpp/assets/figures
	rm -rf public db.json src/modern-cpp/book
	rm -rf ./src/modern-cpp/assets/alipay.jpg
	rm -rf ./src/modern-cpp/assets/wechat.jpg
	rm -rf ./src/modern-cpp/about/donate.md