#ifndef STREAM_MANAGEMENT_H
#define STREAM_MANAGEMENT_H

#include <vector>
#include "camera.h"
#include <chrono>
#include <thread>

class StreamManagement {
public:
    StreamManagement() = default;
    ~StreamManagement() = default;

    void add_camera(int id, const std::string& url_path);
    void update_camera(int id, const std::string& url_path);
    void delete_camera(int id);
    const std::string& get_frame_by_id(int id) const;

private:
    std::vector<Camera> cameras_;
};

#endif  // STREAM_MANAGEMENT_H
