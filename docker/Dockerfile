FROM node:latest

LABEL "maintainer"="Changkun Ou <hi[at]changkun.de>"
LABEL "repository"="https://github.com/changkun/modern-cpp-tutorial"
LABEL "homepage"="https://changkun.de/modern-cpp/"

# For Unicode
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

WORKDIR /modern-cpp-tutorial

# Node & Npm & Python3 are from node:latest
# Install Texlive & Pandoc
RUN apt update && \
    apt install wget texlive-full -y && \
    wget https://github.com/jgm/pandoc/releases/download/2.7.3/pandoc-2.7.3-1-amd64.deb && \
    dpkg -i pandoc-2.7.3-1-amd64.deb
