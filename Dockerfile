# Base image
FROM opencvcourses/opencv-docker:latest

WORKDIR /app

# Set timezone to Asia/Jakarta
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Jakarta

# Install Boost
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libboost-system-dev

# Add the application files
ADD . .

# Build and run
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

CMD ["/app/build/main"]
