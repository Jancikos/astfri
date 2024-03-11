# script for building actual project using cmake

set -e

echo "Building libast project"

mkdir -p build
cd build

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cp compile_commands.json ..

# make

echo "Build complete"