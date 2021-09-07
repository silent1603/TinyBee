@ECHO Off
cd build
conan install ..
start bin/TinyLB.exe
cd ..
