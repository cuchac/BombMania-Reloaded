#!/bin/bash -ex

docker build - -t bombmania-build:latest < Dockerfile

docker run --rm -v $PWD:/src bombmania-build:latest bash -c "mkdir -p /src/build; cd /src/build; cmake ..; make;"

docker run --rm -v $PWD:/src -e DISPLAY -e XAUTHORITY -e BOMBMANIA_DATA_PATH=./res/ -v /tmp/.X11-unix:/tmp/.X11-unix -v $XAUTHORITY:$XAUTHORITY bombmania-build:latest bash -c "cd /src/; ./build/src/bombmania"

