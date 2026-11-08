HOST ?= changkunde
DEST ?= /www/changkun.de/modern-cpp/

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
# Build and publish to https://changkun.de/modern-cpp/, as the other books
# on changkun.de publish. The PDF and EPUB are built apart (make pdf epub in
# the repository's root, into public/modern-cpp/pdf and epub), so --delete
# leaves the published ones alone; new ones here still replace them.
deploy: all
	$(MAKE) upload
upload:
	rsync -az --delete --filter='P /pdf/***' --filter='P /epub/***' public/modern-cpp/ $(HOST):$(DEST)
	@echo "published to https://changkun.de/modern-cpp/"
s: all
	npx serve ./public
clean:
	rm -rf ./src/modern-cpp/assets/figures \
		./src/modern-cpp/assets/alipay.jpg \
		./src/modern-cpp/assets/wechat.jpg \
		./src/modern-cpp/code \
		./src/modern-cpp/exercises \
		public db.json src/modern-cpp/zh-cn src/modern-cpp/en-us

.PHONY: all s deploy upload clean
