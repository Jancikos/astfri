# script for building actual project using cmake

echo "Building libast project"

mkdir -p build
cd build

cmake ..

make

echo "Build complete"