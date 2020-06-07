# CMakeList.txt : CMake project for WixCMakeInheritance, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

include(CPackComponent)

# Add source to this project's executable.
add_library (SomeSharedLibrary SHARED "Source1.cpp" "some/Source1.h")
target_compile_definitions (SomeSharedLibrary PRIVATE SOMESHAREDLIBRARY_BUILDING_DLL)
target_include_directories(SomeSharedLibrary PUBLIC some)

# TODO: Add tests and install targets if needed.
install(TARGETS SomeSharedLibrary
    RUNTIME DESTINATION bin COMPONENT applications
    ARCHIVE DESTINATION lib COMPONENT sdk
    )
install(FILES some/Source1.h DESTINATION include/some COMPONENT sdk)

include(CPack)
