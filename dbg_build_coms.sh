rm -rf target/debug
mkdir target/debug
cd target/debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug
#cmake -G "MinGW Makefiles" ../.. -DCMAKE_BUILD_TYPE=Debug
make -j4
cd ../..








