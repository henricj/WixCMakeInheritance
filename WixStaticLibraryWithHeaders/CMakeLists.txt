# CMakeList.txt : CMake project for WixCMakeInheritance, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

# Add source to this project's executable.
add_library (WixSomeStaticLibrary STATIC "some_wsl.cpp" "some_wsl.h")

# TODO: Add tests and install targets if needed.

