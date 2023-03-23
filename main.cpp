#include <opencv2/opencv.hpp>
#include <iostream>
#include "include/utility/base64.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // Open video file
    VideoCapture cap("/app/sample_video/cars.mp4");

    // Check if video file opened successfully
    if(!cap.isOpened()) {
        cout << "Error opening video file" << endl;
        return -1;
    }

    // Loop through frames
    Mat frame;
    while(cap.read(frame)) {
        // Print shape of frame and its Base64 representation
        cout << "Frame shape: " << frame.size() << endl;
        cout << "Frame Base64: " << frame_to_base64(frame) << endl;
    }

    // Release resources
    cap.release();
    return 0;
}
