#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <thread>
#include <mutex>
#include <opencv2/opencv.hpp>
#include "../utility/base64.h"

class Camera {
public:
    Camera(int id_camera, const std::string& url_path);
    ~Camera();
    // Copy constructor
    Camera(const Camera& other) : id_camera_(other.id_camera_), url_path_(other.url_path_) {
        // Lock the other camera's mutex to ensure that the current
        // frame is not modified during the copy
        std::lock_guard<std::mutex> lock(other.mutex_);

        // Copy the current frame
        current_frame_ = other.current_frame_;
    }

    // Copy assignment operator
    Camera& operator=(const Camera& other) {
        // Lock both cameras' mutexes to ensure that the current
        // frame is not modified during the copy
        std::lock(mutex_, other.mutex_);

        // Unlock the mutexes automatically when the function exits
        std::lock_guard<std::mutex> lock_this(mutex_, std::adopt_lock);
        std::lock_guard<std::mutex> lock_other(other.mutex_, std::adopt_lock);

        // Copy the camera data
        id_camera_ = other.id_camera_;
        url_path_ = other.url_path_;
        current_frame_ = other.current_frame_;

        return *this;
    }

    void start();
    void stop();

    int get_id_camera() const;
    const std::string& get_url_path() const;
    bool set_url_path(const std::string& url_path);
    const std::string& get_current_frame() const;

private:
    int id_camera_;
    std::string url_path_;
    std::string current_frame_;
    bool is_running_;
    std::thread thread_;
    mutable std::mutex mutex_;

    void run();
};

#endif // CAMERA_H
