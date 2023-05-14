FROM ubuntu:18.04

RUN apt update && \
    apt -y install libcegui-mk2-dev pkg-config g++ freeglut3-dev cmake gdb

RUN apt install -y libglew-dev