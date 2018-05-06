all: pdf website

pdf:
	cd pdf/zh-cn && pwd && make

website:
	cd website && make

serve:
	cd website && make s

clean:
	cd pdf/zh-cn && make clean
	cd website && make clean

.PHONY : pdf website clean