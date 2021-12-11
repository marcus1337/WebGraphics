## Build on Linux (Ubuntu)

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
git submodule update --init --recursive 
mkdir Build && cd Build 
cmake ../src/ && make
```
