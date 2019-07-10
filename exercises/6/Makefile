#
# Makefile
# web_server
#
# created by changkun at changkun.de/modern-cpp
#

CXX = g++
EXEC_HTTP = server.http
EXEC_HTTPS = server.https

SOURCE_HTTP = main.http.cpp
SOURCE_HTTPS = main.https.cpp

OBJECTS_HTTP = main.http.o
OBJECTS_HTTPS =  main.https.o

LDFLAGS_COMMON = -std=c++2a -O3 -pthread -lboost_system
LDFLAGS_HTTP =
LDFLAGS_HTTPS = -lssl -lcrypto

LPATH_COMMON = -I/usr/include/boost
LPATH_HTTP =
LPATH_HTTPS = -I/usr/local/opt/openssl/include

LLIB_COMMON = -L/usr/lib
LLIB_HTTPS = -L/usr/local/opt/openssl/lib

all:
	make http
	make https

http:
	$(CXX) $(SOURCE_HTTP) $(LDFLAGS_COMMON) $(LDFLAGS_HTTP) $(LPATH_COMMON) $(LPATH_HTTP) $(LLIB_COMMON) $(LLIB_HTTP) -o $(EXEC_HTTP)
https:
	$(CXX) $(SOURCE_HTTPS) $(LDFLAGS_COMMON) $(LDFLAGS_HTTPS) $(LPATH_COMMON) $(LPATH_HTTPS) $(LLIB_COMMON) $(LLIB_HTTPS) -o $(EXEC_HTTPS)

clean:
	rm -f $(EXEC_HTTP) $(EXEC_HTTPS) *.o
