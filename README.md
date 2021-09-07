Required: 
    Install Cmake , Conan , git
    Window : MSVC or mingw   

Install mingw with msys2:   
pacman -S --needed base-devel mingw-w64-x86_64-toolchain

build ( window && ubuntu)
1 : mkdir build && cd build 
2 : conan install .. ( to install dependence)
3 : conan build .. (to build project)
