#include <camera/stream_management.h>

void StreamManagement::add_camera(int id, const std::string& url_path) {
    // Create a new camera object
    Camera camera(id, url_path);

    // Start the camera thread
    camera.start();

    // give time to the camera to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Add the camera to the vector of cameras
    cameras_.push_back(camera);
}

void StreamManagement::update_camera(int id, const std::string& url_path) {
    // Find the camera with the given id
    for (auto& camera : cameras_) {
        if (camera.get_id_camera() == id) {
            std::cout << "update camera " << id << std::endl;
            // Stop the current camera thread
            camera.stop();

            // Update the camera's URL
            camera.set_url_path(url_path);

            // Start the new camera thread
            camera.start();

            // give time to the camera to start
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            // Exit the loop since we found the camera
            break;
        }
    }
}

void StreamManagement::delete_camera(int id) {
    // Find the camera with the given id
    for (auto it = cameras_.begin(); it != cameras_.end(); ++it) {
        if (it->get_id_camera() == id) {
            std::cout << "delete camera " << id << std::endl;
            // Stop the camera thread
            it->stop();

            // Remove the camera from the vector
            cameras_.erase(it);

            // give time to the camera to start
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            // Exit the loop since we found the camera
            break;
        }
    }
}

const std::string& StreamManagement::get_frame_by_id(int id) const {
    // Find the camera with the given id
    for (const auto& camera : cameras_) {
        if (camera.get_id_camera() == id) {
            // Get the current frame from the camera
            std::cout << "getFrame from camera " << id  << std::endl;
            // give time to the camera to start
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            return camera.get_current_frame();
        }
    }

    // Return an empty string if the camera is not found
    static const std::string empty_frame = "";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return empty_frame;
}
