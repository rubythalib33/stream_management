#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "stream_management.h"
#include <boost/asio.hpp>

class WebsocketServer {
public:
    WebsocketServer(uint16_t port);
    void run();

private:
    void on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);
    void process_message(const std::string& message, websocketpp::connection_hdl hdl);
    void async_wait();

    uint16_t port_;
    websocketpp::server<websocketpp::config::asio> server_;
    StreamManagement stream_management_;
    boost::asio::io_service io_service_;
    boost::asio::steady_timer timer_;
};

#endif  // WEBSOCKET_SERVER_H
