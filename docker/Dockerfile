#base image
FROM ubuntu:latest

#install the requred dependencies for my project
#cmake and c++ and git 
RUN apt-get update && apt-get install -y \
    build-essential\
    g++ \
    cmake\
    git \
    make \
    && rm -rf /var/lib/apt/lists/*

#set the working directory in the docker
WORKDIR /app

#install google tests (used for testing)
RUN git clone https://github.com/google/googletest.git && \
    cd googletest && mkdir build && cd build && \
    cmake .. && make && make install &&\
    rm -rf googletest

#copy the source files for the main projects and the tests
COPY CMakeLists.txt .
COPY src/ ./src

#Build the project
RUN mkdir -p build &&\
    cd build &&\
    cmake .. && \
    make

#run the main file and run the tests file
CMD ["sh","-c","./build/RoboBank_Portfolio && ./build/tests"]



