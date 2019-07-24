//
// main_http.cpp
// web_server
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial/
//

#include <iostream>
#include "server.http.hpp"
#include "handler.hpp"

using namespace Web;

int main() {
    // HTTP server runs in port 12345 HTTP, enable 4 threads
    Server<HTTP> server(12345, 4);
    std::cout << "Server starting at port: 12345" << std::endl;
    start_server<Server<HTTP>>(server);
    return 0;
}
