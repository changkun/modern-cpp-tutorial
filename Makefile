DOCKER_ENV=changkun/modern-cpp-tutorial:build-env
LANGS = zh-cn en-us
ALL_BUILDS = pdf website

# dep

all: $(ALL_BUILDS)

pdf: $(LANGS)
$(LANGS):
	cd pdf/$@ && make && make clean

website:
	cd website && make

build:
	docker run --rm -v `pwd`:/modern-cpp-tutorial -it $(DOCKER_ENV) make 

# dev

build-env:
	docker build -t $(DOCKER_ENV) -f ./docker/Dockerfile .

serve:
	cd website && make s

clean:
	cd pdf/zh-cn && make clean
	cd pdf/en-us && make clean
	cd website && make clean
	docker images -f "dangling=true" -q | xargs docker rmi -f
	docker image prune -f

.PHONY : $(LANGS) $(ALL_BUILDS) serve build-env build-all clean