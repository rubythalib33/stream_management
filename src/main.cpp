#include <iostream>
#include <chrono>
#include <thread>
#include "../include/camera/stream_management.h"

int main() {
    // Create a new StreamManagement object
    StreamManagement stream_manager;

    // Add a camera with id 1 and URL "/app/camera1.mp4"
    stream_manager.add_camera(1, "/app/sample_video/cars.mp4");

    // Wait for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Get the frame from a camera with id 1 (this will return an empty string since the camera was deleted)
    std::string frame = stream_manager.get_frame_by_id(1);
    std::cout << "Frame from camera 1: " << frame << std::endl;


    // Update the camera with id 1 to use URL "/app/camera2.mp4"
    stream_manager.update_camera(1, "/app/sample_video/cars.mp4");

    // Wait for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Delete the camera with id 1
    stream_manager.delete_camera(1);

    return 0;
}
