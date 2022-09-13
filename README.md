## About

This repo is supposed to be a cross-platform lightweight general-purpose game library. It can run on Windows, Linux, and the web via Emscripten. It is a work in progress but the goal is to have a library in some ways similar to [RayLib](https://github.com/raysan5/raylib), to make it easier to quickly create 2D or perhaps even 3D games using OpenGL.

## Installation

### Build on Linux (Emscripten/Docker)
To build without Docker just mimic the instructions in [Dockerfile](Dockerfile).
```bat
apt-get install docker.io
git clone git@github.com:marcus1337/WebGraphics.git && cd WebGraphics
docker build -t webgraphics .
docker run -p 8080:8080 --name webgraphics_server -d webgraphics
```
After having started the ``webgraphics_server`` container open any browser, i.e. Chrome, Edge, FireFox, and enter ``http://localhost:8080/``. To see debug-text press ``F12``.

### Build on Linux (Ubuntu)

```bat
apt-get install cmake
apt-get install mesa-utils
apt-get install freeglut3-dev
apt-get install libglew-dev
apt-get install libfreetype6-dev
apt-get install libglfw3-dev
apt-get install libxinerama-dev
apt-get install libxcursor-dev 
apt-get install libxi-dev 
apt-get install libsdl2-dev
git clone git@github.com:marcus1337/WebGraphics.git && cd WebGraphics
git submodule update --init --recursive 
mkdir build && cd build 
cmake ../src/ && make
```
Note: default cmake version on Ubuntu might be too low.