#!/bin/bash
set -e
cd Lib
make -j $(nproc) 1>/dev/null
make install
