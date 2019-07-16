//
// server_base.hpp
// web_server
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial/
//

#ifndef SERVER_BASE_HPP
#define SERVER_BASE_HPP

#include <boost/asio.hpp>

#include <regex>
#include <unordered_map>
#include <thread>

namespace Web {
    struct Request {
        // request method, POST, GET; path; HTTP version
        std::string method, path, http_version;
        // use smart pointer for reference counting of content
        std::shared_ptr<std::istream> content;
        // hash container, key-value dict
        std::unordered_map<std::string, std::string> header;
        // use regular expression for path match
        std::smatch path_match;
    };

    // use typedef simplify resource type
    typedef std::map<std::string, std::unordered_map<std::string,
    std::function<void(std::ostream&, Request&)>>> resource_type;

    // socket_type is HTTP or HTTPS
    template <typename socket_type>
    class ServerBase {
    public:
        resource_type resource;
        resource_type default_resource;

        // construct server, initalize port, default: 1 thread
        ServerBase(unsigned short port, size_t num_threads = 1) :
            endpoint(boost::asio::ip::tcp::v4(), port),
            acceptor(m_io_service, endpoint),
            num_threads(num_threads) {}

        void start() {
            // default resource in the end of vector, as response method
            for(auto it = resource.begin(); it != resource.end(); it++) {
                all_resources.push_back(it);
            }
            for(auto it = default_resource.begin(); it != default_resource.end(); it++) {
                all_resources.push_back(it);
            }

            // socket connection
            accept();

            // if num_threads>1, then m_io_service.run()
            // it will start (num_threads-1) threads as thread pool
            for(size_t c = 1;c < num_threads; c++) {
                threads.emplace_back([this](){
                    m_io_service.run();
                });
            }

            // main thread
            m_io_service.run();

            // wait for other threads finish
            for(auto& t: threads)
                t.join();
        }
    protected:
        // io_service is a dispatcher in asio library, all asynchronous io events are dispatched by it
        // in another word, constructor of IO object need a io_service object as parameter
        boost::asio::io_service m_io_service;
        // IP address, port and protocol version as a endpoint, and generated on serverside
        // tcp::acceptor object, wait for connection
        boost::asio::ip::tcp::endpoint endpoint;
        // thus, a acceptor object requires io_service and endpoint as parameters
        boost::asio::ip::tcp::acceptor acceptor;

        // server side threads
        size_t num_threads;
        std::vector<std::thread> threads;

        // all resource will be append to the end of vector, and created in start()
        std::vector<resource_type::iterator> all_resources;

        // requires to implement this method for different type of server
        virtual void accept() {}

        void process_request_and_respond(std::shared_ptr<socket_type> socket) const {
            // created cache for async_read_untile()
            // shared_ptr will use for passing object to anonymous function
            // the type will be deduce as std::shared_ptr<boost::asio::streambuf>
            auto read_buffer = std::make_shared<boost::asio::streambuf>();

            boost::asio::async_read_until(*socket, *read_buffer, "\r\n\r\n",
            [this, socket, read_buffer](const boost::system::error_code& ec, size_t bytes_transferred) {
                if(!ec) {
                    // Note: read_buffer->size() always equal to bytes_transferred, the document of Boost indicates:
                    // after async_read_until operation, streambuf contains some extra data out of delimiter
                    // thus, the best way is to read and parse the content from the left of read_buffer, then append the content of async_read
                    size_t total = read_buffer->size();

                    // convert istream to string-lines
                    std::istream stream(read_buffer.get());

                    // deduce the type of std::shared_ptr<Request>
                    auto request = std::make_shared<Request>();
                    *request = parse_request(stream);

                    size_t num_additional_bytes = total-bytes_transferred;

                    // if satisfy then also read
                    if(request->header.count("Content-Length")>0) {
                        boost::asio::async_read(*socket, *read_buffer,
                        boost::asio::transfer_exactly(stoull(request->header["Content-Length"]) - num_additional_bytes),
                        [this, socket, read_buffer, request](const boost::system::error_code& ec, size_t bytes_transferred) {
                            if(!ec) {
                                // pointer as istream object stored in read_buffer
                                request->content = std::shared_ptr<std::istream>(new std::istream(read_buffer.get()));
                                respond(socket, request);
                            }
                        });
                    } else {
                        respond(socket, request);
                    }
                }
            });
        }

        Request parse_request(std::istream& stream) const {
            Request request;

            std::regex e("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");

            std::smatch sub_match;

            // read method, path and http version from the frist line
            std::string line;
            getline(stream, line);
            line.pop_back();
            if(std::regex_match(line, sub_match, e)) {
                request.method       = sub_match[1];
                request.path         = sub_match[2];
                request.http_version = sub_match[3];

                bool matched;
                e="^([^:]*): ?(.*)$";
                // parse head information
                do {
                    getline(stream, line);
                    line.pop_back();
                    matched=std::regex_match(line, sub_match, e);
                    if(matched) {
                        request.header[sub_match[1]] = sub_match[2];
                    }

                } while(matched==true);
            }
            return request;
        }

        void respond(std::shared_ptr<socket_type> socket, std::shared_ptr<Request> request) const {
            // response after search requested path and method
            for(auto res_it: all_resources) {
                std::regex e(res_it->first);
                std::smatch sm_res;
                if(std::regex_match(request->path, sm_res, e)) {
                    if(res_it->second.count(request->method)>0) {
                        request->path_match = move(sm_res);

                        // will be deduce to std::shared_ptr<boost::asio::streambuf>
                        auto write_buffer = std::make_shared<boost::asio::streambuf>();
                        std::ostream response(write_buffer.get());
                        res_it->second[request->method](response, *request);

                        // capture write_buffer in lambda, make sure it can be destroyed after async_write
                        boost::asio::async_write(*socket, *write_buffer,
                        [this, socket, request, write_buffer](const boost::system::error_code& ec, size_t bytes_transferred) {
                            // HTTP 1.1 connection
                            if(!ec && stof(request->http_version)>1.05)
                                process_request_and_respond(socket);
                        });
                        return;
                    }
                }
            }
        }

    };

    template<typename socket_type>
    class Server : public ServerBase<socket_type> {};
}
#endif /* SERVER_BASE_HPP */
