# CMakeList.txt : CMake project for WixCMakeInheritance, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

include(CPackComponent)

# Add source to this project's executable.
add_executable (WixCMakeInheritance "WixCMakeInheritance.cpp" "WixCMakeInheritance.h")

target_link_libraries(WixCMakeInheritance PUBLIC SomeSharedLibrary PRIVATE WixSomeStaticLibrary )

# TODO: Add tests and install targets if needed.

install(TARGETS WixCMakeInheritance
    RUNTIME DESTINATION bin COMPONENT applications
    ARCHIVE DESTINATION lib COMPONENT sdk
    PUBLIC_HEADER DESTINATION include COMPONENT sdk
    )

include(CPack)
