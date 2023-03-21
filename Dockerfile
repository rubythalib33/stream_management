# Base image
FROM ubuntu:20.04

WORKDIR /app

# Update packages and install dependencies
RUN apt-get update && \
    apt-get install -y python3 python3-pip python3-dev build-essential \
                       cmake git libgtk2.0-dev pkg-config libavcodec-dev \
                       libavformat-dev libswscale-dev libv4l-dev \
                       libxvidcore-dev libx264-dev libjpeg-dev \
                       libpng-dev libtiff-dev gfortran openexr \
                       libatlas-base-dev python3-numpy \
                       libtbb2 libtbb-dev libdc1394-22-dev \
                       libopenexr-dev libgstreamer-plugins-base1.0-dev \
                       libgstreamer1.0-dev

# Clone OpenCV repository and checkout version
RUN git clone https://github.com/opencv/opencv.git && \
    cd opencv && \
    git checkout tags/4.5.4

# Build and install OpenCV
RUN cd opencv && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
          -D CMAKE_INSTALL_PREFIX=/usr/local \
          -D WITH_GSTREAMER=ON \
          -D WITH_LIBV4L=ON \
          -D BUILD_opencv_python3=ON \
          -D PYTHON_EXECUTABLE=/usr/bin/python3 \
          -D PYTHON_INCLUDE_DIR=/usr/include/python3.8 \
          -D PYTHON_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.8.so \
          .. && \
    make -j4 && \
    make install

# Set environment variable
ENV PYTHONPATH=/usr/local/lib/python3.8/dist-packages:$PYTHONPATH

# Cleanup
RUN cd .. && \
    rm -rf opencv
