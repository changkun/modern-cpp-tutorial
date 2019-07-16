//
// server_https.hpp
// web_server
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial/
//

#ifndef SERVER_HTTPS_HPP
#define	SERVER_HTTPS_HPP

#include "server.http.hpp"
#include <boost/asio/ssl.hpp>

namespace Web {

    // define HTTPS type
    typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> HTTPS;

    // define HTTPS service, template type is HTTPS
    template<>
    class Server<HTTPS> : public ServerBase<HTTPS> {
    public:
        // a HTTPS server requires two more parameters: certificate file and private key file
        Server(unsigned short port, size_t num_threads,
               const std::string& cert_file, const std::string& private_key_file) :
          ServerBase<HTTPS>::ServerBase(port, num_threads),
          context(boost::asio::ssl::context::sslv23) {
            // use certificate file
            context.use_certificate_chain_file(cert_file);
            // use private key file, we need pass a new parameter to specify the format
            context.use_private_key_file(private_key_file, boost::asio::ssl::context::pem);
        }

    private:
        // compare to HTTP server, we must define ssl context object
        boost::asio::ssl::context context;

        // the difference between HTTPS and HTTP server
        // is the construct difference of socket object
        // HTTPS will encrypt the IO stream socket
        // thus, accept() method must initialize ssl context
        void accept() {
            // create a new socket for current connection
            // shared_ptr is used for passing temporal object to anonymous function
            // socket will be deduce as std::shared_ptr<HTTPS>
            auto socket = std::make_shared<HTTPS>(m_io_service, context);

            acceptor.async_accept(
                (*socket).lowest_layer(),
                [this, socket](const boost::system::error_code& ec) {
                    // accept a new connection
                    accept();

                    // if no error
                    if(!ec) {
                        (*socket).async_handshake(boost::asio::ssl::stream_base::server,
                            [this, socket](const boost::system::error_code& ec) {
                            if(!ec) process_request_and_respond(socket);
                        });
                    }
            });
        }
    };
}

#endif	/* SERVER_HTTPS_HPP */
