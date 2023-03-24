#include "../include/camera/websocket_server.h"

int main() {
    try {
        WebsocketServer server(9002);
        server.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
        return 1;
    }
    return 0;
}