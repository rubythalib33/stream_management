# Base image
FROM opencvcourses/opencv-docker:latest

WORKDIR /app

# Set timezone to Asia/Jakarta
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Jakarta


ADD main.cpp .
ADD CMakeLists.txt .
ADD sample_video .

# Build and run
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

CMD ["/app/build/main"]