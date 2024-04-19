# script for building actual project using cmake
set -e

echo "Building astfri project"

mkdir -p build
cd build

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug $1 ..
cp compile_commands.json ..

make -j4

echo "Build complete"