all: clean
	node install.js
	python3 filter.py
	cp ../assets/cover-2nd.png ./src/modern-cpp/assets/cover-2nd.png
	cp ../assets/cover-2nd-logo.png ./src/modern-cpp/assets/cover-2nd-logo.png
	cp ../assets/cover-2nd-en.png ./src/modern-cpp/assets/cover-2nd-en.png
	cp ../assets/cover-2nd-en-logo.png ./src/modern-cpp/assets/cover-2nd-en-logo.png
	cp ../assets/alipay.jpg ./src/modern-cpp/assets/alipay.jpg
	cp ../assets/wechat.jpg ./src/modern-cpp/assets/wechat.jpg
	cp ../assets/donate.md ./src/modern-cpp/about/
	cp ../assets/community.md ./src/modern-cpp/about/
	cp -r ../assets/figures ./src/modern-cpp/assets/figures
	cp -r ../exercises ./src/modern-cpp/
	cp -r ../code ./src/modern-cpp/
	npx hexo generate
	mv public/index.html public/modern-cpp/index.html
s: all
	node_modules/serve/bin/serve.js ./public
clean:
	rm -rf ./src/modern-cpp/assets/cover-2nd.png \
		./src/modern-cpp/assets/cover-2nd-en.png \
		./src/modern-cpp/assets/cover-2nd-logo.png \
		./src/modern-cpp/assets/cover-2nd-en-logo.png \
		./src/modern-cpp/assets/figures \
		./src/modern-cpp/assets/alipay.jpg \
		./src/modern-cpp/assets/wechat.jpg \
		./src/modern-cpp/about/donate.md \
		./src/modern-cpp/about/community.md \
		./src/modern-cpp/code \
		./src/modern-cpp/exercises \
		public db.json src/modern-cpp/zh-cn src/modern-cpp/en-us
