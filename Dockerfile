#This script starts up a website that runs the cpp App code.
#Downloads and compiles lua dependency using emscripten.

FROM ubuntu:20.04
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install build-essential -y
RUN apt-get install python3 -y
RUN apt-get install git -y

ADD https://github.com/Kitware/CMake/releases/download/v3.24.1/cmake-3.24.1-linux-x86_64.sh /cmake-3.24.1-Linux-x86_64.sh
RUN mkdir /opt/cmake
RUN sh /cmake-3.24.1-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
RUN cmake --version

RUN mkdir /project
COPY . /project
RUN rm /project/external/lib/emscripten/liblua.a

WORKDIR /
RUN git clone https://github.com/emscripten-core/emsdk.git
WORKDIR /emsdk
RUN /emsdk/emsdk install latest
RUN /emsdk/emsdk activate latest

RUN mkdir /lua_build
WORKDIR /lua_build
ADD https://www.lua.org/ftp/lua-5.4.4.tar.gz /lua_build/lua-5.4.4.tar.gz
RUN tar -xf ./lua-5.4.4.tar.gz
WORKDIR /lua_build/lua-5.4.4
RUN ["/bin/bash", "-c", "source /emsdk/emsdk_env.sh && make generic CC='emcc -s WASM=1'"]

RUN cp /lua_build/lua-5.4.4/src/liblua.a /project/external/lib/emscripten/
RUN mkdir /project/build
WORKDIR /project/build
RUN ["/bin/bash", "-c", "source /emsdk/emsdk_env.sh && emcmake cmake /project/src && emmake make"]

RUN mv /project/build/AniLib.js /project/html/
RUN mv /project/build/AniLib.wasm /project/html/

WORKDIR /project/html
EXPOSE 8080
CMD ["python3", "-m", "http.server", "8080"]