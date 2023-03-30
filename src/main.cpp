#include <iostream>
#include <thread>
#include <chrono>
#include <camera/stream_management.h>

int main() {
    // Create a StreamManagement object
    StreamManagement stream_mgmt;

    // Add cameras with IDs and URL paths
    stream_mgmt.add_camera(1, "/app/sample_video/cars.mp4");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    stream_mgmt.add_camera(2, "/app/sample_video/cars.mp4");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Get 20 frames from camera 1
    for (int i = 0; i < 20; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        const std::string& frame = stream_mgmt.get_frame_by_id(1);
        std::cout << "Frame " << i + 1 << " from camera 1: " << frame << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // Delete a camera by its ID
    stream_mgmt.delete_camera(2);

    return 0;
}
