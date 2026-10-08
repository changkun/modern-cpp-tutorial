all: clean
	node install.js
	python3 filter.py
	cp ../assets/alipay.jpg ./src/modern-cpp/assets/alipay.jpg
	cp ../assets/wechat.jpg ./src/modern-cpp/assets/wechat.jpg
	cp -r ../assets/figures ./src/modern-cpp/assets/figures
	cp -r ../exercises ./src/modern-cpp/
	cp -r ../code ./src/modern-cpp/
	npx hexo generate
	mv public/index.html public/modern-cpp/index.html
	rm -rf public/_generated_home_stub
s: all
	node_modules/serve/bin/serve.js ./public
clean:
	rm -rf ./src/modern-cpp/assets/figures \
		./src/modern-cpp/assets/alipay.jpg \
		./src/modern-cpp/assets/wechat.jpg \
		./src/modern-cpp/code \
		./src/modern-cpp/exercises \
		public db.json src/modern-cpp/zh-cn src/modern-cpp/en-us
