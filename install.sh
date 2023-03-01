#!/bin/bash
set -e
mkdir LSD
mkdir Bin
cd ./Lib
./bootstrap
./configure --prefix=`pwd|sed 's/...$//'`/LSD
make
make install
cd ../Agent
./bootstrap
./configure --with-librcsc=`pwd`/../LSD/
mkdir .binary
cd .binary
cmake ..
make -j $(nproc) 1>/dev/null
