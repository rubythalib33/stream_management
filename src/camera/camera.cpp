#include <camera/camera.h>

using namespace cv;
using namespace std;

Camera::Camera(int id_camera, const string& url_path)
    : id_camera_(id_camera), url_path_(url_path), is_running_(false) {}

Camera::~Camera() {
    stop();
}

void Camera::start() {
    if (is_running_) {
        return;
    }

    is_running_ = true;
    std::cout << "start camera " << id_camera_ << std::endl;
    thread_ = thread(&Camera::run, this);
}

void Camera::stop() {
    if (!is_running_) {
        return;
    }

    is_running_ = false;
    thread_.join();
}

int Camera::get_id_camera() const {
    return id_camera_;
}

const string& Camera::get_url_path() const {
    return url_path_;
}

bool Camera::set_url_path(const string& url_path) {
    if (is_running_) {
        return false;
    }
    url_path_ = url_path;
    return true;
}

const string& Camera::get_current_frame() const {
    lock_guard<mutex> lock(mutex_);
    return current_frame_;
}

void Camera::run() {
    VideoCapture cap(url_path_);
    std::cout << "run camera " << id_camera_ << std::endl;

    if (!cap.isOpened()) {
        cerr << "Error opening camera " << id_camera_ << endl;
        return;
    }

    Mat frame;
    while (is_running_) {
        if (!cap.read(frame)) {
            cerr << "Error reading frame from camera " << id_camera_ << endl;
            break;
        }
        std::cout << "Running frame from camera " << id_camera_ << std::endl;
        string base64_frame = frame_to_base64(frame);

        lock_guard<mutex> lock(mutex_);
        current_frame_ = base64_frame;
        // give time sleep
        this_thread::sleep_for(chrono::milliseconds(30));
    }

    cap.release();
}
