#!/bin/sh

set -e

echo "Target platform: $1"

# Build mumei
cd /mumei
export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/opt/ros/humble/lib/x86_64-linux-gnu:/opt/ros/humble/lib/aarch64-linux-gnu:$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH
cmake -DBUILD_TYPE=$1 -DUSE_PINOCCHIO=1 -DCMAKE_PREFIX_PATH=/opt/ros/humble -Bbuild
cmake --build build --parallel --target install
cd build && ctest --output-on-failure

# add export command to .bashrc
echo "export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/opt/ros/humble/lib/x86_64-linux-gnu:/opt/ros/humble/lib/aarch64-linux-gnu:$LD_LIBRARY_PATH" >> ~/.bashrc
