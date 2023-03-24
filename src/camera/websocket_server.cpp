#include "../../include/camera/websocket_server.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

WebsocketServer::WebsocketServer(uint16_t port)
    : port_(port), timer_(io_service_, boost::asio::chrono::milliseconds(100)) {
    server_.init_asio();
    server_.set_message_handler(std::bind(&WebsocketServer::on_message, this,
    std::placeholders::_1, std::placeholders::_2));
}

void WebsocketServer::run() {
    server_.listen(port_);
    server_.start_accept();
    async_wait();
    server_.run();
}

void WebsocketServer::async_wait() {
    timer_.async_wait([this](const boost::system::error_code& error) {
        if (!error) {
            std::cout << "Waiting..." << std::endl;
            timer_.expires_after(boost::asio::chrono::milliseconds(100));
            async_wait();
        }
    });
}

void WebsocketServer::on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
    process_message(msg->get_payload(), hdl);
}

void WebsocketServer::process_message(const std::string& message, websocketpp::connection_hdl hdl) {
    try {
        boost::property_tree::ptree pt;
        std::istringstream ss(message);
        boost::property_tree::read_json(ss, pt);
            std::string command = pt.get<std::string>("command");

    if (command == "create_camera") {
        int id = pt.get<int>("id");
        std::string url_path = pt.get<std::string>("url_path");
        stream_management_.add_camera(id, url_path);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else if (command == "update_camera") {
        int id = pt.get<int>("id");
        std::string url_path = pt.get<std::string>("url_path");
        stream_management_.update_camera(id, url_path);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else if (command == "delete_camera") {
        int id = pt.get<int>("id");
        stream_management_.delete_camera(id);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else if (command == "retrieve_stream") {
        int id = pt.get<int>("id");
        std::string frame = stream_management_.get_frame_by_id(id);
        server_.send(hdl, frame, websocketpp::frame::opcode::binary);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else {
        throw std::runtime_error("Unknown command");
    }
} catch (const std::exception& e) {
    std::string error_message = "Error processing message: " + std::string(e.what());
    server_.send(hdl, error_message, websocketpp::frame::opcode::text);
}
}