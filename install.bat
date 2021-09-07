@ECHO Off
if exist build\ (
    cd build
  
) else (
    mkdir build && cd build
)
conan install ..

cd ..
