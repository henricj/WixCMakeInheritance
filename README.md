Getting MSVC arm64 builds working for another much more complicated CMake project
inspired this simplified test project.  Since this turned out to be less than simple,
the result is preserved here.

Three projects are built:  A shared library, a static library, and an executable
that uses the shared library.  An MSI is generated that optionally installs the 
files needed for using the shared library.  Finally, a bootstrapper is built that
first makes sure the VC++ Redistributable for the target architecture is installed
before installing the MSI (downloading the `vc_redist.[arch].exe` from Microsoft
if needed).

The bootstapper still needs to be built manually.  This can be done like so, when run
from a command prompt starting from the project's root directory and set up to build
the desired architecture (e.g., with
`VsDevCmd.bat -arch=arm64 -host_arch=x64 -startdir=none`):
```
md out\build\arm64-Release
cd out\build\arm64-Release
cmake -G Ninja -v -DTARGET_PROCESSOR_NAME=arm64 -DCMAKE_BUILD_TYPE="RelWithDebInfo" ..\..\..
cmake --build . -v
cpack -G WIX -v
candle -arch arm64 ..\..\..\bundle.wxs ..\..\..\vcredist.wxs -ext WixBalExtension -ext WixUtilExtension -dTargetMsiPath=WixCMakeInheritance-arm64.msi
light bundle.wixobj vcredist.wixobj -ext WixBalExtension -ext WixUtilExtension -b ..\..\.. -o InstallWCM-arm64.exe
```
Opening the root directory in Visual Studio 2019 and doing a "Build All" will perform
the steps up to (but not including) cpack.

Note that `TARGET_PROCESSOR_NAME` should be `x86`, `x64` or `arm64`.  Ideally,
`CMAKE_SYSTEM_PROCESSOR` should be able to do this, but that turned out to be
more difficult than expected.  The WIX tools need to be in the `PATH` and a recent
build of WIX 3.14 is needed for ARM64 support.  If Chocolatey is installed, then its
deprecated `cpack` command may need to be removed to avoid
interfering with CMake's cpack.

These examples were shamelessly exploited:
* VC++ Redist from: https://gist.github.com/nathancorvussolis/6852ba282647aeb0c5c00e742e28eb48
* General CPackWIX examples: https://github.com/ngladitz/cmake-wix-testsuite
