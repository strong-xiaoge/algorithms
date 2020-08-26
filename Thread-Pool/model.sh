# !/bin/bash
set -e
# set -x
cd ./build
cmake ..
make -j4
cd ..

echo -e '\n'run the executable file ...
./bin/threadpool
