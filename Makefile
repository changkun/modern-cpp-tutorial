NAME=modern-cpp-tutorial
DOCKER_ENV=changkun/$(NAME):build-env
TARGET = pdf epub
LANGS = zh-cn en-us
ALL_BUILDS = website $(TARGET)

# dep

all: $(ALL_BUILDS)

$(TARGET): $(LANGS)
	mkdir -p website/public/modern-cpp/$@/
	for lang in $^ ; do \
		cd $@/$${lang} && make && make clean && cd ../..; \
		mv $@/$${lang}/$(NAME).$@ website/public/modern-cpp/$@/$(NAME)-$${lang}.$@; \
	done

website:
	cd website && make

build:
	docker run --rm -v `pwd`:/$(NAME) $(DOCKER_ENV) make 

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