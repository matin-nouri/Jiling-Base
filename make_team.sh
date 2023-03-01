#!/bin/bash
set -e
cd ./Agent/.binary
rm -rf *
cmake ..
make -j $(nproc) 1>/dev/null
