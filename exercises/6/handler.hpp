//
// handler.hpp
// web_server
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial/
//

#include "server.base.hpp"
#include <fstream>

using namespace std;
using namespace Web;

template<typename SERVER_TYPE>
void start_server(SERVER_TYPE &server) {
    // resources request

    // processing POST /string, return the string from POST
    server.resource["^/string/?$"]["POST"] = [](ostream& response, Request& request) {
        // fetch string from istream (*request.content)
        stringstream ss;
        *request.content >> ss.rdbuf();     // read request to stringstream
        string content=ss.str();

        // return response
        response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
    };

    // process GET request from /info, return response
    server.resource["^/info/?$"]["GET"] = [](ostream& response, Request& request) {
        stringstream content_stream;
        content_stream << "<h1>Request:</h1>";
        content_stream << request.method << " " << request.path << " HTTP/" << request.http_version << "<br>";
        for(auto& header: request.header) {
            content_stream << header.first << ": " << header.second << "<br>";
        }

        // get the length of content_stream (use content.tellp() to get)
        content_stream.seekp(0, ios::end);

        response <<  "HTTP/1.1 200 OK\r\nContent-Length: " << content_stream.tellp() << "\r\n\r\n" << content_stream.rdbuf();
    };

    // process GET request for /match/[digit+numbers], e.g. GET request is /match/abc123, will return abc123
    server.resource["^/match/([0-9a-zA-Z]+)/?$"]["GET"] = [](ostream& response, Request& request) {
        string number=request.path_match[1];
        response << "HTTP/1.1 200 OK\r\nContent-Length: " << number.length() << "\r\n\r\n" << number;
    };

    // peocess default GET request; anonymous function will be called if no other matches
    // response files in folder web/
    // default: index.html
    server.default_resource["^/?(.*)$"]["GET"] = [](ostream& response, Request& request) {
        string filename = "www/";

        string path = request.path_match[1];

        // forbidden use `..` access content outside folder web/
        size_t last_pos = path.rfind(".");
        size_t current_pos = 0;
        size_t pos;
        while((pos=path.find('.', current_pos)) != string::npos && pos != last_pos) {
            current_pos = pos;
            path.erase(pos, 1);
            last_pos--;
        }

        filename += path;
        ifstream ifs;
        // folder inspection across platform
        if(filename.find('.') == string::npos) {
            if(filename[filename.length()-1]!='/')
                filename+='/';
            filename += "index.html";
        }
        ifs.open(filename, ifstream::in);

        if(ifs) {
            ifs.seekg(0, ios::end);
            size_t length=ifs.tellg();

            ifs.seekg(0, ios::beg);

            // copy file to response-stream , shouldn't use for large files
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n" << ifs.rdbuf();

            ifs.close();
        } else {
            // return unable to open if file doesn't exists
            string content="Could not open file "+filename;
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
        }
    };

    // start HTTP(S) server
    server.start();
}
