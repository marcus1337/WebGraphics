mkdir -p build
cp -r ./html ./build
mkdir -p ./build/emsdk

echo "Downloading and installing emscripten..."
git clone https://github.com/emscripten-core/emsdk.git build/emsdk
./build/emsdk/emsdk install latest
./build/emsdk/emsdk activate latest
source ./emsdk/emsdk_env.sh

echo "Building WebAssembly files..."
emcmake cmake -B./build -S./src
cd build && emmake make

echo "Moving files to website folder www..."
mkdir -p www
mv Simple_App.js Simple_App.wasm www
cp ../html/canvas.js ../html/index.css ../html/index.html www

echo "You can now view the website by starting 'index.html' in www with a 'live-server.'"

