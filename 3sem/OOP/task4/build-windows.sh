mkdir -p build-win && cd build-win
cmake -DCMAKE_TOOLCHAIN_FILE=../mingw.cmake ..
make -j$(nproc)
