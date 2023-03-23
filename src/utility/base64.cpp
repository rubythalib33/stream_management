#include "../../include/utility/base64.h"
#include <vector>
#include <algorithm>

std::string frame_to_base64(cv::Mat frame) {
    std::vector<uchar> buffer;
    std::vector<int> params{cv::IMWRITE_JPEG_QUALITY, 90};
    cv::imencode(".jpg", frame, buffer, params);
    auto base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    std::string base64_string;
    int i = 0;
    int j = 0;
    uint8_t char_array_3[3];
    uint8_t char_array_4[4];
    auto in_len = buffer.size();
    auto input = buffer.data();
    while (in_len--) {
        char_array_3[i++] = *(input++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for(i = 0; i < 4; i++) {
                base64_string += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }
    if (i) {
        for(j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
            ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
            ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for(j = 0; j < i + 1; j++) {
            base64_string += base64_chars[char_array_4[j]];
        }
        while((i++ < 3)) {
            base64_string += '=';
        }
    }
    return base64_string;
}
