#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // Open video file
    VideoCapture cap("/app/1.mp4");

    // Check if video file opened successfully
    if(!cap.isOpened()) {
        cout << "Error opening video file" << endl;
        return -1;
    }

    // Loop through frames
    Mat frame;
    while(cap.read(frame)) {
        // Print shape of frame
        cout << "Frame shape: " << frame.size() << endl;
    }

    // Release resources
    cap.release();
    return 0;
}
