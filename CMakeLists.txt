# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project ("WixCMakeInheritance" VERSION 0.1.2)

message(STATUS "Version: ${CMAKE_PROJECT_VERSION}")
message(STATUS "Processor: ${TARGET_PROCESSOR_NAME}")

set(CPACK_GENERATOR WIX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

include(GNUInstallDirs)
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_BINDIR})
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_LIBDIR})
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/stage/${CMAKE_INSTALL_LIBDIR})
endif()

message(STATUS "Runtime: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Library: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "Archive: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

# Include sub-projects.
add_subdirectory ("SomeSharedLibrary")
add_subdirectory ("WixStaticLibraryWithHeaders")
add_subdirectory ("WixCMakeInheritance")

include(CPackComponent)

if(WIN32)
    if(TARGET_PROCESSOR_NAME STREQUAL x86)
        set(CPACK_WIX_UPGRADE_GUID "C4A8A30B-A811-41FC-AF74-1E8D317EBAB0")
    elseif(TARGET_PROCESSOR_NAME STREQUAL x64)
        set(CPACK_WIX_UPGRADE_GUID "A6066D2B-B2B8-4C2C-9807-DAB97D848407")
        set(TARGET_PROCESSOR_NAME x64)
    elseif(TARGET_PROCESSOR_NAME STREQUAL arm64)
        set(CPACK_WIX_UPGRADE_GUID "1C4B0BF6-C1B5-4BBF-B647-B3166C3AD021")
    else()
        message(ERROR "Unknown system processor ${TARGET_PROCESSOR_NAME}")
    endif()

    set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_VERSION} (${TARGET_PROCESSOR_NAME})")
    if(TARGET_MSI_NAME)
        set(CPACK_PACKAGE_FILE_NAME "${TARGET_MSI_NAME}")
    else()
        set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${TARGET_PROCESSOR_NAME}")
    endif()

    set(CPACK_WIX_CANDLE_EXTRA_FLAGS -arch ${TARGET_PROCESSOR_NAME})
    set(CPACK_WIX_TEMPLATE "${CMAKE_CURRENT_SOURCE_DIR}/wix-arm64.template.in")

    set (CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}")

    set_property(INSTALL "bin/$<TARGET_FILE_NAME:WixCMakeInheritance>"
        PROPERTY CPACK_START_MENU_SHORTCUTS "WixCMakeInheritance"
    )

    set(CPACK_WIX_PROPERTY_ALLUSERS 1)
endif()

cpack_add_component(applications
    DISPLAY_NAME " Application"
    DESCRIPTION "An application"
)

cpack_add_component(sdk
    DISPLAY_NAME "SDK"
    DESCRIPTION "The SDK"
    GROUP "Development"
)

cpack_add_component_group(Runtime)

cpack_add_component_group(Development
    DESCRIPTION "All of the tools you'll ever need to develop software"
)

#set(CPACK_COMPONENT_GROUP_DEVELOPMENT_PARENT_GROUP "Runtime")
#unset(CPACK_COMPONENT_APPLICATIONS_REQUIRED)

set(CPACK_ALL_INSTALL_TYPES Full Developer)

set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)

include(CPack)

